
#include "display_private.h"
#if defined(CONFIG_DISPLAY_ENABLED)
#include "display.h"
#include "driver_vendor.h"
#include "logger_common.h"
#include "ui_events.h"

static const char *TAG = "display";

// Optimized timeout constants for common semaphore operations
#define DISPLAY_TIMEOUT_MAX portMAX_DELAY
#define DISPLAY_TIMEOUT_IMMEDIATE (TickType_t)0UL

ESP_EVENT_DEFINE_BASE(UI_EVENT);

#if (C_LOG_LEVEL <= LOG_INFO_NUM)
static const char * _ui_event_strings[] = { UI_EVENT_LIST(STRINGIFY)};
const char * ui_event_strings(int id) {
    return id < lengthof(_ui_event_strings) ? _ui_event_strings[id] : "UI_EVENT_UNKNOWN";
}
#else
const char * ui_event_strings(int id) {return "UI_EVENT";}
#endif

#define LCD_UI_TIMER_PERIOD_S 60 // 1 minute periodic timer for UI updates
#if defined(CONFIG_LCD_IS_EPD)
#define DISPLAY_TIMER_TASK_DELAY_MS 10UL
#else
#define DISPLAY_TIMER_TASK_DELAY_MS 10UL
#endif

// --- Forward declarations ---
static bool display_timer_lock(int timeout);
static void display_timer_unlock(void);
static void display_on_draw_complete(void);
void display_on_task_paused(bool paused);
void display_request_alert(void);
void display_request_mandatory(void);
void display_request_optional(void);

typedef struct display_priv_s {
    esp_lcd_panel_handle_t dspl_drv;
    display_t * self;
    int8_t rotation;
    bool display_initialized;
    uint32_t count_last_full_refresh; 
    uint32_t count_last_fast_refresh;
    uint8_t off_screen_count;
    uint8_t off_screen_requested;
    bool task_is_running;
    bool task_not_paused;
    bool task_is_finished;
    uint32_t ms;
    uint8_t ms_cancelled;
    uint8_t timer_created;
    uint16_t shutdown_counter_running;
    SemaphoreHandle_t refreshing_sem;
    SemaphoreHandle_t wake_sem;  // Event-driven wake for paused mode
    SemaphoreHandle_t lifecycle_mutex; // Serialize init/uninit/task start
    TaskHandle_t task_handle;
    TimerHandle_t timer;  // FreeRTOS periodic timer for paused mode
    uint8_t start_task_pause_seq;
    uint16_t periodic_timer_period;
} display_priv_t;

#if defined(CONFIG_LCD_IS_EPD)
#define ROTATION_DEFAULT 1
#else
#define ROTATION_DEFAULT 0
#endif
#define DISPLAY_PRIV_DEFAULTS() { \
    .dspl_drv = NULL, \
    .self = NULL, \
    .rotation = ROTATION_DEFAULT, \
    .display_initialized = false, \
    .count_last_full_refresh = 0, \
    .count_last_fast_refresh = 0, \
    .off_screen_count = 0, \
    .off_screen_requested = 0, \
    .task_is_running = false, \
    .task_not_paused = true, \
    .task_is_finished = false,     \
    .ms = 0, \
    .ms_cancelled = 0, \
    .timer_created = 0, \
    .shutdown_counter_running = 0, \
    .refreshing_sem = NULL, \
    .wake_sem = NULL,\
    .lifecycle_mutex = NULL, \
    .task_handle = 0, \
    .timer = 0, \
    .start_task_pause_seq = 0, \
    .periodic_timer_period = 0, \
}

struct display_priv_s display_priv = DISPLAY_PRIV_DEFAULTS();

// --- Display helpers (now that display_priv is declared) ---
static inline TickType_t _timeout_to_ticks(int timeout) {
    return (timeout == -1) ? DISPLAY_TIMEOUT_MAX : 
           (timeout == 0) ? DISPLAY_TIMEOUT_IMMEDIATE : pdMS_TO_TICKS(timeout);
}

// Serialize lifecycle operations to prevent init/uninit races
static inline void _lifecycle_lock(void) {
    if (!display_priv.lifecycle_mutex) {
        display_priv.lifecycle_mutex = xSemaphoreCreateMutex();
    }
    if (display_priv.lifecycle_mutex) {
        xSemaphoreTake(display_priv.lifecycle_mutex, portMAX_DELAY);
    }
}

static inline void _lifecycle_unlock(void) {
    if (display_priv.lifecycle_mutex) {
        xSemaphoreGive(display_priv.lifecycle_mutex);
    }
}

// Reset display_priv to a safe baseline while preserving lifecycle mutex
static inline void _display_priv_reset_preserve_mutex(void) {
    SemaphoreHandle_t mtx = display_priv.lifecycle_mutex;
    memset(&display_priv, 0, sizeof(struct display_priv_s));
    display_priv.lifecycle_mutex = mtx;
#if defined(CONFIG_LCD_IS_EPD)
    display_priv.rotation = ROTATION_DEFAULT;
#else
    display_priv.rotation = ROTATION_DEFAULT;
#endif
}

static uint32_t _get_buf_update_count(void) {
    return display_priv.self ? display_priv.self->buf_update_count : 0;
}

// Prefer driver/flush counter when available to track actual LVGL frame output
static uint32_t _get_queue_buf_version(void) {
#if defined(CONFIG_LCD_IS_EPD)
    return display_drv_epd_get_flush_count();
#else
    return _get_buf_update_count();
#endif
}

// Check if refresh time matches current buffer count
static bool _refresh_time_match(uint32_t refresh_time) {
    return display_priv.self && refresh_time > 0 && refresh_time == display_priv.self->buf_update_count;
}

// Check if refresh time is pending
static bool _refresh_time_pending(uint32_t refresh_time) {
    return display_priv.self && refresh_time < display_priv.self->buf_update_count;
}

bool display_refresh_lock(int timeout) {
    // FUNC_ENTRYD(TAG);
    if (!display_priv.refreshing_sem) return false;
    return xSemaphoreTake(display_priv.refreshing_sem, _timeout_to_ticks(timeout)) == pdTRUE;
}

void display_refresh_unlock() {
    // FUNC_ENTRYD(TAG);
    if (display_priv.refreshing_sem) {
        xSemaphoreGive(display_priv.refreshing_sem);
    }
}

static uint32_t _lv_timer_handler() {
    FUNC_ENTRY_ARGSD(TAG, " %ld", _get_buf_update_count());
    uint32_t task_delay_ms = L_LVGL_TASK_MAX_DELAY_MS;
    if (display_drv_lock(1000)) {
        task_delay_ms = lv_timer_handler(); 
        display_drv_unlock();
    }
    if (task_delay_ms > L_LVGL_TASK_MAX_DELAY_MS) {
        task_delay_ms = L_LVGL_TASK_MAX_DELAY_MS;
    } else if (task_delay_ms < L_LVGL_TASK_MIN_DELAY_MS) {
        task_delay_ms = L_LVGL_TASK_MIN_DELAY_MS;
    }
    DLOG(TAG, "[%s] done %ld, %lu", __func__, _get_buf_update_count(), task_delay_ms);
    return task_delay_ms;
}

void display_incr_buf_update_count() {
    FUNC_ENTRY_ARGSD(TAG, " %ld", _get_buf_update_count());
    ++display_priv.self->buf_update_count;
}

uint16_t get_offscreen_counter() {
    FUNC_ENTRY_ARGSD(TAG, " %hhu, %ld", display_priv.off_screen_count, display_priv.self ? display_priv.self->buf_update_count : 0);
    return display_priv.off_screen_count;
}

// #define CONFIG_FULL_REFRESH_ON_FIRST_FLUSH
// #define CONFIG_FULL_REFRESH_ON_SECOND_FLUSH
// #define CONFIG_FULL_REFRESH_ON_THIRD_FLUSH

static uint32_t _ui_screen_draw() {
    FUNC_ENTRYD(TAG);
    if(!display_priv.self || !display_priv.self->op || !display_priv.self->op->screen_cb) {
        ELOG(TAG, "Display not initialized properly");
        return 1000; // Retry after 1 second
    }
    DMEAS_START();
    display_drv_lock(0);
    display_drv_unlock();
#if defined(CONFIG_LCD_IS_EPD)
    FUNC_ENTRY_ARGSD(TAG, "update_count=%lu first_flush_done=%hhu task_not_paused=%d epd_flush_count=%lu start_task_pause_seq=%hhu", display_priv.self->buf_update_count, display_priv.self->first_flush_done, display_priv.task_not_paused, display_drv_epd_get_flush_count(), display_priv.start_task_pause_seq);
    if(display_priv.start_task_pause_seq > 1) {
        display_task_pause();
        display_priv.start_task_pause_seq = 0;
    }
    if(display_priv.self->first_flush_done == 0) {
        if(display_drv_epd_get_flush_count() > 0) {
            display_priv.self->first_flush_done = 1;
#if defined(CONFIG_FULL_REFRESH_ON_SECOND_FLUSH)
            goto do_full_refresh;
#endif
        }
    }
    else if(display_priv.self->first_flush_done == 1) {
        if(display_drv_epd_get_flush_count() > 2) {
            DLOG(TAG, "** start pause seq after first flush done **");
            display_task_pause();
            display_priv.self->first_flush_done = 2;
        }
    }
#if !defined(CONFIG_FULL_REFRESH_ON_FIRST_FLUSH)
    if(display_priv.self->first_flush_done)
#endif
    {
#if defined(CONFIG_FULL_REFRESH_ON_THIRD_FLUSH)
        if(display_drv_epd_get_flush_count() == 2) {
            goto do_full_refresh;
        }
#endif
        if(_refresh_time_match(display_priv.self->task_full_refresh_on_time)) {
            DLOG(TAG, "[%s] Full ... count: %lu", __func__, _get_buf_update_count());
            display_request_full_refresh(display_priv.self->task_full_refresh_on_time_force);
            display_task_cancel_req_fast_refresh();
        }
        else if(_refresh_time_match(display_priv.self->task_fast_refresh_on_time)) {
            DLOG(TAG, "[%s] Fast ... count: %lu", __func__, _get_buf_update_count());
            display_request_fast_refresh();
            display_task_cancel_req_full_refresh();
        }
        else {
            DLOG(TAG, "[%s] Partial ... count: %lu", __func__, _get_buf_update_count());
            display_drv_epd_request_partial_update();
        }
    }
#endif
    uint32_t task_delay_ms = display_priv.self->op->screen_cb(0);
     ++display_priv.self->buf_update_count;
    uint32_t timer_delay_ms = _lv_timer_handler();
#if defined(CONFIG_LCD_IS_EPD)
#if (LVGL_VERSION_MAJOR > 8)
#include "../components/lvgl/src/core/lv_refr_private.h"
#endif
    /*Call this anywhere you want to refresh the dirty areas*/
    _lv_disp_refr_timer(NULL);
    if (display_priv.shutdown_counter_running)
        display_priv.off_screen_count++;
    if(display_priv.ms_cancelled) {
        display_priv.ms = 0;
        display_priv.ms_cancelled = 0;
    } else
#else
    if(timer_delay_ms > task_delay_ms)
#endif
        task_delay_ms = timer_delay_ms;
    display_priv.ms = get_millis() + task_delay_ms;

    // Notify queue logic that this draw finished (may trigger next queued request)
#if defined(CONFIG_LCD_IS_EPD)
    display_on_draw_complete();
#endif

    DMEAS_END_ARGS(TAG, "... done. %ld (delay %lu)", display_priv.self->buf_update_count, task_delay_ms);
    return task_delay_ms;
};

void display_set_rotation(int8_t rotation) {
    FUNC_ENTRY_ARGW(TAG, " %d", rotation);
    // Skip if driver not initialized or already torn down
    if (!display_priv.display_initialized || display_priv.dspl_drv == NULL) {
        return;
    }
    if(display_refresh_lock(100)) {
        if(rotation != display_priv.rotation) {
            display_priv.rotation = rotation;
        }
        if(display_drv_get_rotation() != rotation) {
            display_drv_set_rotation(rotation);
        }
        display_refresh_unlock();
    }
}

static void _ui_start(int8_t rotation) {
    if(display_priv.task_is_running) return;
    FUNC_ENTRY(TAG);
    // Prevent driver delete during init by holding driver lock
    if (display_drv_lock(-1)) {
        display_drv_init();
        display_set_rotation(rotation);
        display_drv_unlock();
    } else {
        return;
    }
    display_priv.self->op->ui_init();
#if defined(CONFIG_LCD_IS_EPD)
    /// delete default display refr timer
    lv_disp_t * disp = lv_disp_get_default();
#if LVGL_VERSION_MAJOR <= 8
    lv_timer_del(disp->refr_timer);
    disp->refr_timer = NULL;
#else
    lv_display_delete_refr_timer(disp);
#endif
#endif
    display_priv.task_is_running = true;
    delay_ms(100);
}

static void _ui_task(void *args) {
    FUNC_ENTRY_ARGS(TAG, " starting %hhd", display_priv.rotation);
    _ui_start(display_priv.rotation);
    uint32_t task_delay_ms = _lv_timer_handler();
    while (display_priv.task_is_running) {
        if (display_priv.task_not_paused) {
            // Running: use calculated delay until next refresh (no polling)
            TLOG(TAG, "[%s] running, waiting ms: %lu", __func__, display_priv.ms);
            uint32_t now = get_millis();
            if(now >= display_priv.ms) {
                task_delay_ms = _ui_screen_draw();
            } else {
                // Sleep precisely until next refresh time, but allow fast wake via task notification
                uint32_t sleep_ms = display_priv.ms - now;
                if (sleep_ms > task_delay_ms) sleep_ms = task_delay_ms;
                BaseType_t notified = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(sleep_ms));
                if (notified) {
                    // Immediate update requested while running; draw on next loop iteration
                    display_priv.ms = 0;
                }
            }
        }
#if (defined(CONFIG_LCD_IS_EPD))
        else {
            // Paused: block on semaphore OR task notification with timeout
            // Use 10ms timeout for responsive UI; >10ms becomes perceptible to users
            TLOG(TAG, "[%s] paused, waiting for event", __func__);
            
            // Wait for either semaphore or task notification (fast path for button events)
            BaseType_t notified = xSemaphoreTake(display_priv.wake_sem, pdMS_TO_TICKS(10));
            if (notified == pdFALSE) {
                // Check if we got a task notification instead (from display_task_notify_update)
                notified = ulTaskNotifyTake(pdTRUE, 0);  // Clear notification, no wait
            }
            
            if (notified == pdTRUE) {
                // If we're stopping the task, skip drawing to avoid an extra frame
                if (!display_priv.task_is_running) {
                    continue;
                }
                task_delay_ms = _ui_screen_draw();
            }
            // Timeout is normal when paused - allows task to check running flag every 10ms
        }
#endif
    }
    UNUSED_PARAMETER(task_delay_ms);
#if defined(CONFIG_LCD_IS_EPD)
    display_drv_epd_turn_off(display_priv.dspl_drv);
#endif
    FUNC_ENTRY_ARGS(TAG, " finishing");
    display_priv.task_is_finished = 1;
    display_priv.task_handle = 0;
    vTaskDelete(NULL);
}

#if defined(CONFIG_LCD_IS_EPD)

void display_request_partial_refresh() {
    display_drv_epd_request_partial_update();
}

void display_shut_down() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld", display_priv.self ? display_priv.self->buf_update_count : 0);
    if(display_refresh_lock(100)) {
        display_drv_epd_turn_off(display_priv.dspl_drv);
        display_refresh_unlock();
    }
}

static void _task_req_fast_refresh(int8_t fast_refresh_time) {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld fast_refresh_time: %hhd", _get_buf_update_count(), fast_refresh_time);
    // Caller must hold display_refresh_lock; no nested lock needed
    if(_refresh_time_pending(display_priv.self->task_fast_refresh_on_time) && fast_refresh_time>=0) {
        display_priv.self->task_fast_refresh_on_time = display_priv.self->buf_update_count + fast_refresh_time;
        if(display_priv.self->task_fast_refresh_on_time == display_priv.self->task_full_refresh_on_time) {
            display_priv.self->task_full_refresh_on_time++;
        }
    }
}

// --- Task-aware refresh queue (alerts/mandatory/optional) ---
typedef enum {
    DISPLAY_REFRESH_TYPE_OPTIONAL = 0,
    DISPLAY_REFRESH_TYPE_MANDATORY = 1,
    DISPLAY_REFRESH_TYPE_ALERT = 2
} display_refresh_type_t;

typedef struct {
    uint32_t current_buf_version;
    uint32_t next_buf_version;
    uint8_t current_type : 2;
    uint8_t next_type : 2;
    uint8_t draw_in_progress : 1;
    uint8_t next_pending : 1;
    uint8_t task_paused : 1;
} display_queue_state_t;

static display_queue_state_t display_queue_state = {0};

void display_on_task_paused(bool paused) {
    if (display_refresh_lock(0)) {  // Trylock for non-blocking from button callbacks
        display_queue_state.task_paused = paused;
        display_refresh_unlock();
    }
    // If lock busy, state will sync on next operation
}

// Wake paused task and reset timer period (common pattern extracted)
static inline void _wake_paused_task_and_reset_timer(void) {
    display_priv.ms = 0;
    if (display_priv.wake_sem) {
        xSemaphoreGive(display_priv.wake_sem);
    }
    if (display_priv.timer_created && xTimerIsTimerActive(display_priv.timer)) {
        xTimerReset(display_priv.timer, 0);
    }
}

static void _queue_start_draw(uint32_t buf_version, display_refresh_type_t type) {
    FUNC_ENTRY(TAG);
    display_queue_state.current_buf_version = buf_version;
    display_queue_state.current_type = type;
    display_queue_state.draw_in_progress = true;
    // Schedule fast refresh for CURRENT count (0 offset), not +1
    // When _ui_screen_draw() starts, count hasn't incremented yet, so match check needs current value
    _task_req_fast_refresh(0);
}

void display_request_refresh(uint32_t target_buf_version, display_refresh_type_t type) {
    FUNC_ENTRY_ARGS(TAG, "buf %lu type %d", target_buf_version, type);
    if (display_refresh_lock(100)) {  // Reduced from 1000ms to 100ms for faster response
        FUNC_ENTRY_ARGS(TAG, "locked, buf %lu type %d", target_buf_version, type);
        // If task is running (not paused), bypass queue—LVGL coalesces via _task_req_fast_refresh
        if (!display_queue_state.task_paused) {
            ILOG(TAG, "[%s] task running, direct refresh (no queue) buf %lu", __func__, target_buf_version);
            // Schedule for current count (0 offset) to trigger on next draw immediately
            _task_req_fast_refresh(0);
            // Force immediate check by resetting the delay timer (don't wait up to 1s for next poll)
            display_priv.ms = 0;
            display_refresh_unlock();
            return;
        }

        // Task paused → use event-driven queue
        ILOG(TAG, "[%s] task paused, queue request buf %lu type %d", __func__, target_buf_version, type);

        if (!display_queue_state.draw_in_progress) {
            _queue_start_draw(target_buf_version, type);
            // Wake the paused task immediately and reset timer period
            _wake_paused_task_and_reset_timer();
            display_refresh_unlock();
            // No taskYIELD() - let scheduler handle naturally for lower latency
            return;
        }

        // Draw in progress
        
        // Deduplicate: only skip if queued buffer is LATER than target (stale request)
        // Don't skip if queued buffer == target, as screen content may have changed (push→alert, etc.)
        if (display_queue_state.next_pending && display_queue_state.next_buf_version > target_buf_version) {
            DLOG(TAG, "  → skipped stale (pending buf %lu > target %lu)", display_queue_state.next_buf_version, target_buf_version);
            display_refresh_unlock();
            return;
        }
        
        // If queued buffer == target, allow override based on priority
        if (display_queue_state.next_pending && display_queue_state.next_buf_version == target_buf_version) {
            // Upgrade priority if new request is higher, otherwise replace (content may differ)
            if (type >= display_queue_state.next_type) {
                display_queue_state.next_type = type;
                DLOG(TAG, "  → replaced/upgraded pending queue to type %d (same buf, different content)", type);
            } else {
                DLOG(TAG, "  → kept higher priority pending (type %d > %d)", display_queue_state.next_type, type);
            }
            display_refresh_unlock();
            return;
        }
        
        if (display_queue_state.current_type == DISPLAY_REFRESH_TYPE_ALERT) {
            // Never interrupt an alert; schedule as next
            display_queue_state.next_buf_version = target_buf_version;
            display_queue_state.next_type = type;
            display_queue_state.next_pending = true;
            DLOG(TAG, "  → alert drawing, queued as next");
        } else if (type == DISPLAY_REFRESH_TYPE_ALERT) {
            // Alert overrides whatever was pending next
            display_queue_state.next_buf_version = target_buf_version;
            display_queue_state.next_type = type;
            display_queue_state.next_pending = true;
            DLOG(TAG, "  → alert queued to run next");
        } else if (type == DISPLAY_REFRESH_TYPE_MANDATORY) {
            // Mandatory runs after current
            display_queue_state.next_buf_version = target_buf_version;
            display_queue_state.next_type = type;
            display_queue_state.next_pending = true;
            DLOG(TAG, "  → mandatory queued as next");
        } else {
            // Optional coalesces: replace pending next
            display_queue_state.next_buf_version = target_buf_version;
            display_queue_state.next_type = type;
            display_queue_state.next_pending = true;
            DLOG(TAG, "  → optional set/replaced as next");
        }

        // Always wake paused task so it can service the queued draw promptly
        _wake_paused_task_and_reset_timer();

        display_refresh_unlock();
    }
}

void display_on_draw_complete(void) {
    FUNC_ENTRY(TAG);
    if (display_refresh_lock(100)) {  // Reduced from 1000ms to 100ms
        display_queue_state.draw_in_progress = false;

        if (display_queue_state.next_pending) {
            uint32_t buf = display_queue_state.next_buf_version;
            uint32_t current_buf = _get_queue_buf_version();
            display_refresh_type_t type = display_queue_state.next_type;
            
            // Validate: skip if buffer already at or past target (stale request)
            if (buf <= current_buf) {
                DLOG(TAG, "[%s] skipping stale queued refresh buf %lu (current %lu)", __func__, buf, current_buf);
                display_queue_state.next_pending = false;
                display_refresh_unlock();
                return;
            }
            
            display_queue_state.next_pending = false;
            DLOG(TAG, "[%s] starting queued refresh buf %lu type %d", __func__, buf, type);
            _queue_start_draw(buf, type);
            // Wake task for next draw
            if (display_priv.wake_sem)
                xSemaphoreGive(display_priv.wake_sem);
        } else {
            DLOG(TAG, "[%s] no queued refresh", __func__);
        }

        display_refresh_unlock();
    }
}

void display_request_alert(void) {
    FUNC_ENTRY(TAG);
    display_request_refresh(_get_queue_buf_version() + 1, DISPLAY_REFRESH_TYPE_ALERT);
}

void display_request_mandatory(void) {
    FUNC_ENTRY(TAG);
    display_request_refresh(_get_queue_buf_version() + 1, DISPLAY_REFRESH_TYPE_MANDATORY);
}

void display_request_optional(void) {
    FUNC_ENTRY(TAG);
    display_request_refresh(_get_queue_buf_version() + 1, DISPLAY_REFRESH_TYPE_OPTIONAL);
}

void display_request_fast_refresh() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld", display_priv.self ? display_priv.self->buf_update_count : 0);
    display_drv_epd_request_fast_update();
}

// Shared implementation for non-blocking refresh requests
static void _display_request_refresh_nonblock(display_refresh_type_t type) {
    if (display_refresh_lock(0)) {  // Trylock: returns immediately if busy
        uint32_t target = _get_queue_buf_version() + 1;
        if (!display_queue_state.task_paused) {
            // Task running: just set fast refresh flag
            _task_req_fast_refresh(0);
            display_priv.ms = 0;
        } else {
            // Task paused: queue request
            if (!display_queue_state.draw_in_progress) {
                _queue_start_draw(target, type);
            } else {
                display_queue_state.next_buf_version = target;
                display_queue_state.next_type = type;
                display_queue_state.next_pending = true;
            }
            // Wake paused task
            display_priv.ms = 0;
            if (display_priv.wake_sem) xSemaphoreGive(display_priv.wake_sem);
        }
        display_refresh_unlock();
    }
    // If lock busy, skip - periodic timer will catch state change on next cycle
}

// Non-blocking versions for button callbacks - use trylock to avoid breaking multi-click detection
void display_request_mandatory_nonblock(void) {
    _display_request_refresh_nonblock(DISPLAY_REFRESH_TYPE_MANDATORY);
}

void display_request_alert_nonblock(void) {
    _display_request_refresh_nonblock(DISPLAY_REFRESH_TYPE_ALERT);
}

void display_task_cancel_req_fast_refresh() {
    if(!display_priv.self) return;
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld",display_priv.self->buf_update_count);
    display_priv.self->task_fast_refresh_on_time = 0;
}

static void _task_req_full_refresh(int8_t full_refresh_time, bool full_refresh_force) {
    // Caller must hold display_refresh_lock; no nested lock needed
    if(_refresh_time_pending(display_priv.self->task_full_refresh_on_time) && full_refresh_time >= 0) {
        display_priv.self->task_full_refresh_on_time = display_priv.self->buf_update_count + full_refresh_time;
        display_priv.self->task_full_refresh_on_time_force = full_refresh_force;
    }
    TLOG(TAG, "[%s] buf_update_count: %ld task_full_refresh_on_time: %ld, task_fast_refresh_on_time: %ld", __FUNCTION__, _get_buf_update_count(), display_priv.self->task_full_refresh_on_time, display_priv.self->task_fast_refresh_on_time);
}

void display_request_full_refresh(bool force) {
    if(!display_priv.self) return;
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld force: %d", display_priv.self->buf_update_count, force);
    if(force || display_priv.self->buf_update_count < 5 || display_priv.count_last_full_refresh + 5  < display_priv.self->buf_update_count){
        display_drv_epd_request_full_update();
        display_priv.self->task_full_refresh_on_time = display_priv.self->buf_update_count;
    }
}

void display_task_cancel_req_full_refresh() {
    if(!display_priv.self) return;
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld", display_priv.self->buf_update_count);
    display_priv.self->task_full_refresh_on_time = 0;
    display_priv.self->task_full_refresh_on_time_force = false;
}

static void _periodic_timer_stop() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld", display_priv.self ? display_priv.self->buf_update_count : 0);
    if (display_priv.timer_created) {
        if(xTimerIsTimerActive(display_priv.timer)) {
            FUNC_ENTRY_ARGSD(TAG, " stop periodic timer");
            if(xTimerStop(display_priv.timer, 0) != pdPASS) {
                WLOG(TAG, "[%s] failed to stop periodic timer", __func__);
            }
        }
    }
}

static void _timer_cb(TimerHandle_t xTimer);

static void _periodic_timer_start() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld", display_priv.self ? display_priv.self->buf_update_count : 0);
#if defined(CONFIG_LCD_IS_EPD)
    if(!display_priv.timer_created) {
        uint16_t period_sec = display_priv.periodic_timer_period ? display_priv.periodic_timer_period : LCD_UI_TIMER_PERIOD_S;
        display_priv.timer = xTimerCreate(
            "lcd_periodic",
            pdMS_TO_TICKS(period_sec * 1000),
            pdTRUE,  // auto-reload
            NULL,
            _timer_cb
        );
        if(!display_priv.timer) {
            WLOG(TAG, "[%s] failed to create periodic timer.", __func__);
            return;
        }
        display_priv.timer_created = 1;
    }
#endif
    if(display_priv.timer_created) {
        if(!xTimerIsTimerActive(display_priv.timer)) {
            DLOG(TAG, "[%s] start periodic timer.", __func__);
            xTimerStart(display_priv.timer, 0);
        }
    }
}

#endif

void display_cancel_delay() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld", display_priv.self ? display_priv.self->buf_update_count : 0);
    display_priv.ms=0;
    display_priv.ms_cancelled = 1;
}

uint32_t display_get_buf_update_count() {
    return display_priv.self ? display_priv.self->buf_update_count : 0;
}

#if defined(CONFIG_LCD_IS_EPD)
uint32_t display_get_flush_count() {
    return display_drv_epd_get_flush_count();
}

static void _task_pause_wo_timer() {
    if(!display_priv.self) return;
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld", display_priv.self->buf_update_count);
    display_task_cancel_req_full_refresh();
    if(display_priv.task_not_paused) {
        display_priv.task_not_paused = 0;
        display_priv.self->last_flush_when_paused = display_priv.self->buf_update_count;
    }
}

void display_task_pause() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld", display_priv.self ? display_priv.self->buf_update_count : 0);
    _task_pause_wo_timer();
    display_on_task_paused(true);
    _periodic_timer_start();
}

void display_start_task_pause_seq() {
    FUNC_ENTRY_ARGS(TAG, " pause state: %hhu", display_priv.start_task_pause_seq);
    if(display_priv.task_not_paused) ++display_priv.start_task_pause_seq;
}

void display_cancel_task_pause_seq() {
    FUNC_ENTRY_ARGS(TAG, " pause state: %hhu", display_priv.start_task_pause_seq);
    display_priv.start_task_pause_seq = 0;
}

void display_timer_set_period(uint16_t period) {
    // Period 0 means "reset to default" without caller needing to know default value
    uint16_t actual_period = (period == 0) ? LCD_UI_TIMER_PERIOD_S : period;
    
    if (actual_period == display_priv.periodic_timer_period) {
        return;  // No change, skip update
    }
    display_priv.periodic_timer_period = actual_period;
    if(display_priv.timer_created && xTimerIsTimerActive(display_priv.timer)) {
        FUNC_ENTRY_ARGS(TAG, " change timer period to %hu sec.", actual_period);
        xTimerChangePeriod(display_priv.timer, pdMS_TO_TICKS(actual_period * 1000), 0);
    }
}

uint16_t get_display_timer_period() {
    return  display_priv.periodic_timer_period;
}

void display_task_resume() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %ld", display_priv.self ? display_priv.self->buf_update_count : 0);
    display_task_cancel_req_full_refresh();
    if(display_priv.start_task_pause_seq)
        display_priv.start_task_pause_seq = 0;
    if(!display_priv.task_not_paused) {
        display_priv.task_not_paused = 1;
        // If task was blocked on wake_sem (paused path), release it so the loop can continue
        if (display_priv.wake_sem)
            xSemaphoreGive(display_priv.wake_sem);
    }
    display_on_task_paused(false);
    display_priv.ms = 0;
    if(display_priv.timer_created && xTimerIsTimerActive(display_priv.timer)){
        DLOG(TAG, "[%s] stop periodic timer", __func__);
        xTimerStop(display_priv.timer, 0);
    }
}

bool display_task_is_paused() {
    return display_priv.task_not_paused == 0;
}

static void _timer_cb(TimerHandle_t xTimer) {
    FUNC_ENTRY(TAG);
    // Periodic timer wakes paused task for one optional refresh
    // FreeRTOS timer runs in timer daemon context, not ISR - use regular calls
    if (display_queue_state.task_paused && display_priv.wake_sem) {
        xSemaphoreGive(display_priv.wake_sem);
    }
}
#endif

void display_task_notify_update() {
    // Ultra-fast non-blocking wake for immediate display updates
    // Uses FreeRTOS task notification (fastest IPC, ~0.5µs)
    if (display_priv.task_handle) {
        xTaskNotifyGive(display_priv.task_handle);
    }
}

void display_task_start() {
    FUNC_ENTRY(TAG);
    _lifecycle_lock();
    if(display_priv.task_is_running && display_priv.task_handle) {
        _lifecycle_unlock();
        return;
    }
    if (!display_priv.display_initialized) {
        _lifecycle_unlock();
        return;
    }
    xTaskCreatePinnedToCore(_ui_task, "lcd_ui_task", CONFIG_DISPLAY_TASK_STACK_SIZE, NULL, 5, &display_priv.task_handle, 1);
    _lifecycle_unlock();
}

#if defined(CONFIG_LCD_IS_EPD)
#define SHUT_DOWN_COUNTER_TIMES 300U
#define SHUT_DOWN_COUNTER_DELAY 50U
#else
#define SHUT_DOWN_COUNTER_TIMES 10U
#define SHUT_DOWN_COUNTER_DELAY 50U
#endif

#if defined(CONFIG_LCD_IS_EPD)
void display_wait_for_task() {
    FUNC_ENTRY(TAG);
    IMEAS_START();
    uint32_t delay = SHUT_DOWN_COUNTER_DELAY;
    _periodic_timer_stop();
    display_cancel_delay();
    // Ensure a single final draw using paused, event-driven queue
    if(display_priv.task_is_running) {
        if (display_priv.task_not_paused) {
            // Pause without starting timers to route requests through the queue
            _task_pause_wo_timer();
            display_on_task_paused(true);
        }
    }

    // Compute the target buffer version for the mandatory draw
#if defined(CONFIG_LCD_IS_EPD)
    uint32_t target_buf = display_drv_epd_get_flush_count() + 1;
#else
    uint32_t target_buf = _get_buf_update_count() + 1;
#endif

    // Request a final mandatory draw via paused queue and wake immediately
    display_request_mandatory();
    if (display_priv.wake_sem)
        xSemaphoreGive(display_priv.wake_sem);

    // Wait bounded time until the buffer version reaches the target (specific final draw)
    display_priv.shutdown_counter_running = SHUT_DOWN_COUNTER_TIMES;
    while (display_priv.shutdown_counter_running) {
#if defined(CONFIG_LCD_IS_EPD)
        uint32_t flc = display_drv_epd_get_flush_count();
#else
        uint32_t flc = _get_buf_update_count();
#endif
        if (flc >= target_buf) {
            break; // Mandatory draw has been performed
        }
        DLOG(TAG, "[%s] waiting final draw to buf=%lu, current=%lu, left %hu (*%lu ms)", __func__, (unsigned long)target_buf, (unsigned long)flc, display_priv.shutdown_counter_running, delay);
        delay_ms(delay);
        --display_priv.shutdown_counter_running;
    }

    // Keep task paused without timers after final draw
    _task_pause_wo_timer();
    IMEAS_END(TAG);
}
#endif
#undef SHUT_DOWN_COUNTER_TIMES
#undef SHUT_DOWN_COUNTER_DELAY

static void _ui_stop() {
    if(!display_priv.task_is_running) return;
    FUNC_ENTRY(TAG);
    DMEAS_START();
#if defined(CONFIG_LCD_IS_EPD)
//     display_wait_for_task();
#else
    // Ensure one final draw on LCD before stopping
    display_priv.ms = 0; // trigger immediate draw
    uint32_t target_buf = _get_buf_update_count() + 1;
    uint16_t tries = 10U; // ~500ms total
    while (tries--) {
        if (_get_buf_update_count() >= target_buf) {
            break;
        }
        // Nudge the running task to wake immediately
        display_task_notify_update();
        vTaskDelay(pdMS_TO_TICKS(50));
    }
#endif
    // Unblock paused task to allow clean exit without extra draw
    if (display_priv.wake_sem)
        xSemaphoreGive(display_priv.wake_sem);
    display_cancel_delay();
    display_priv.task_is_running = false;
    uint32_t wait = get_millis() + 15000;
    uint16_t i = 0;
    while (!display_priv.task_is_finished) {
        delay_ms(150);
        if (get_millis() > wait) {
            if(display_priv.task_handle){
                WLOG(TAG, "[%s] task not finished, deleting", __func__);
                vTaskDelete(display_priv.task_handle);
                display_priv.task_handle = 0;
            }
            break;
        }
        ++i;
    }
    display_priv.task_is_finished = false;
    //delay_ms(4000);
#if defined(CONFIG_LCD_IS_EPD)
    if(display_priv.timer){
        DLOG(TAG, "[%s] stop and delete periodic timer", __func__);
        _periodic_timer_stop();
        xTimerDelete(display_priv.timer, 0);
        display_priv.timer = NULL;
        display_priv.timer_created = 0;
    }
#endif
    if(display_priv.self && display_priv.self->op && display_priv.self->op->ui_deinit)
        display_priv.self->op->ui_deinit();
    DMEAS_END_ARGS(TAG, " %hu 150 ms loops", i);
}

struct display_s *display_init(struct display_s *me, struct display_op_s *op) {
    FUNC_ENTRY(TAG);
    _lifecycle_lock();
    if (display_priv.display_initialized) {
        _lifecycle_unlock();
        return me;
    }
#if defined(LOG_LOCAL_LEVEL)
    esp_log_level_set(TAG, LOG_LOCAL_LEVEL);
#endif
    memset(me, 0, sizeof(struct display_s));
    me->op = op;
    display_priv.self = me;
    display_priv.dspl_drv = display_drv_new();

    if(display_priv.dspl_drv)
        display_priv.display_initialized = true;

    if(!display_priv.refreshing_sem)
        display_priv.refreshing_sem = xSemaphoreCreateBinary();
    display_refresh_unlock();
    if(!display_priv.wake_sem)
        display_priv.wake_sem = xSemaphoreCreateBinary();
    _lifecycle_unlock();
    return me;
}

void display_uninit(struct display_s *me) {
    FUNC_ENTRY(TAG);
    // Always lock lifecycle to serialize against init/start
    _lifecycle_lock();

    // Stop UI task if running
    if (display_priv.task_is_running) {
        _ui_stop();
    }

    // Delete driver if created (take driver lock and hold it through delete)
    if (display_priv.dspl_drv) {
        if (display_drv_lock(-1)) {
            // Hold the lock while deleting; semaphore will be deleted inside
            display_drv_del();
        } else {
            // Fallback: delete without lock (should not happen with -1 timeout)
            display_drv_del();
        }
        display_priv.dspl_drv = NULL;
    }

    // Delete semaphores if they exist
    if (display_priv.refreshing_sem != NULL){
        vSemaphoreDelete(display_priv.refreshing_sem);
        display_priv.refreshing_sem = NULL;
    }
    if (display_priv.wake_sem != NULL){
        vSemaphoreDelete(display_priv.wake_sem);
        display_priv.wake_sem = NULL;
    }

    // Reset state but preserve lifecycle mutex
    _display_priv_reset_preserve_mutex();

    if (me) memset(me, 0, sizeof(struct display_s));

    display_priv.display_initialized = false;
    _lifecycle_unlock();
}

#endif
