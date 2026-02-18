
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
#define DISPLAY_TIMER_TASK_DELAY_MS 10UL
#define DISPLAY_RETRY_DELAY_MS 1000 // Retry delay for failed operations
#define DISPLAY_TASK_WAIT_TIMEOUT_MS 15000 // Max wait for task completion
#define DISPLAY_TASK_WAIT_INTERVAL_MS 150 // Poll interval for task completion
#define DISPLAY_FINAL_DRAW_RETRIES 10U // Retries for final draw on LCD
#define DISPLAY_FINAL_DRAW_INTERVAL_MS 50U // Interval between final draw retries

// --- Forward declarations ---
static void display_on_draw_complete(void);
void display_on_task_paused(bool paused);

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
        if (!display_priv.lifecycle_mutex) {
            ELOG(TAG, "[%s] Failed to create lifecycle mutex", __func__);
            return;
        }
    }
    if (xSemaphoreTake(display_priv.lifecycle_mutex, portMAX_DELAY) != pdTRUE) {
        ELOG(TAG, "[%s] Failed to take lifecycle mutex", __func__);
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

static inline uint32_t _get_buf_update_count(void) {
    return display_drv_get_flush_count();
}

// Prefer driver/flush counter when available to track actual LVGL frame output
static uint32_t _get_queue_buf_version(void) {
    // Only flush_count is used for EPD
    return _get_buf_update_count();
}

// Check if refresh time matches current buffer count
static bool _refresh_time_match(uint32_t refresh_time) {
    return display_priv.self && refresh_time > 0 && refresh_time == _get_buf_update_count();
}

// Check if refresh time is pending
static bool _refresh_time_pending(uint32_t refresh_time) {
    return display_priv.self && refresh_time < _get_buf_update_count();
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
    // FUNC_ENTRY_ARGSD(TAG, " %" PRId32 "", _get_buf_update_count());
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
    FUNC_ENTRY_ARGSD(TAG, " done %" PRIu32 ", %" PRIu32 "", _get_buf_update_count(), task_delay_ms);
    return task_delay_ms;
}

// void display_incr_buf_update_count() {
//     FUNC_ENTRY_ARGSD(TAG, " %" PRId32 "", _get_buf_update_count());
//     ++display_priv.self->buf_update_count;
// }

uint16_t get_offscreen_counter() {
    FUNC_ENTRY_ARGSD(TAG, " %" PRIu8 ", %" PRIu32 "", display_priv.off_screen_count, _get_buf_update_count());
    return display_priv.off_screen_count;
}

// #define CONFIG_FULL_REFRESH_ON_FIRST_FLUSH
// #define CONFIG_FULL_REFRESH_ON_SECOND_FLUSH
// #define CONFIG_FULL_REFRESH_ON_THIRD_FLUSH

static uint32_t _ui_screen_draw() {
    FUNC_ENTRYD(TAG);
    if(!display_priv.self || !display_priv.self->op || !display_priv.self->op->screen_cb) {
        ELOG(TAG, "Display not initialized properly");
        return DISPLAY_RETRY_DELAY_MS;
    }
    DMEAS_START();

#if defined(CONFIG_LCD_IS_EPD)
    FUNC_ENTRY_ARGSD(TAG,
        "update_count=%" PRIu32 " first_flush_done=%" PRIu8 " task_not_paused=%d "
        "start_task_pause_seq=%" PRIu8 "",
        _get_buf_update_count(), display_priv.self->first_flush_done,
        display_priv.task_not_paused,
        display_priv.start_task_pause_seq);
    if(display_priv.start_task_pause_seq > 1) {
        display_task_pause();
        display_priv.start_task_pause_seq = 0;
    }
    if(display_priv.self->first_flush_done == 0) {
        if(_get_buf_update_count() > 0) {
            display_priv.self->first_flush_done = 1;
#if defined(CONFIG_FULL_REFRESH_ON_SECOND_FLUSH)
            goto do_full_refresh;
#endif
        }
    }
    else if(display_priv.self->first_flush_done == 1) {
        if(_get_buf_update_count() > 2) {
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
        if(_get_buf_update_count() == 2) {
            goto do_full_refresh;
        }
#endif
        if(_refresh_time_match(display_priv.self->task_full_refresh_on_time)) {
            FUNC_ENTRY_ARGSD(TAG, " Full ... count: %" PRIu32 "", _get_buf_update_count());
            display_request_full_refresh(display_priv.self->task_full_refresh_on_time_force);
            display_task_cancel_req_fast_refresh();
        }
        else if(_refresh_time_match(display_priv.self->task_fast_refresh_on_time)) {
            FUNC_ENTRY_ARGSD(TAG, " Fast ... count: %" PRIu32 "", _get_buf_update_count());
            display_request_fast_refresh();
            display_task_cancel_req_full_refresh();
        }
        else {
            FUNC_ENTRY_ARGSD(TAG, " Partial ... count: %" PRIu32 "", _get_buf_update_count());
            display_drv_epd_request_partial_update();
        }
    }
#endif
    // buf_update_count merged with flush_count for EPD
    uint32_t task_delay_ms = display_priv.self->op->screen_cb(0);
    uint32_t timer_delay_ms = _lv_timer_handler();
#if defined(CONFIG_LCD_IS_EPD)
#if (LVGL_VERSION_MAJOR > 8)
#include "lvgl.h"
#include "../components/lvgl/src/core/lv_refr.h"
#endif
    /*Call this anywhere you want to refresh the dirty areas*/
    display_drv_epd_reset_flush_requested();
    LV_REFRESH_TIMER(NULL);
    if (display_drv_epd_get_flush_request_count() == 0) {
        // No dirty buffers, LVGL didn't call flush_cb, signal completion
        display_drv_epd_signal_no_flush();
    }
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

    DMEAS_END_ARGS(TAG, "... done. %" PRIu32 " (delay %" PRIu32 ")",
        _get_buf_update_count(), task_delay_ms);
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

#if !defined(CONFIG_LCD_IS_EPD)
void display_bl_set(uint8_t brightness_percent) {
    FUNC_ENTRY_ARGW(TAG, " %d", brightness_percent);
    if(display_refresh_lock(100)) {
        // display_priv.self->op->bl_set(brightness_percent);
        display_drv_bl_set(brightness_percent);
        display_refresh_unlock();
    }
}
#endif

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
    display_lvgl_handle_t *disp = display_lvgl_get_default();
#if LVGL_VERSION_MAJOR > 8
    lv_display_delete_refr_timer(disp);
#else
    lv_timer_del(disp->refr_timer);
    disp->refr_timer = NULL;
#endif
#endif
    display_priv.task_is_running = true;
    delay_ms(100);
}
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

// Atomic flags for deferred refresh requests (lock-free producer, UI task consumer)
static volatile uint32_t s_pending_refresh_flags = 0;

// --- Task-aware refresh queue (alerts/mandatory/optional) ---
typedef enum {
    DISPLAY_REFRESH_TYPE_OPTIONAL = 0,
    DISPLAY_REFRESH_TYPE_MANDATORY = 1,
    DISPLAY_REFRESH_TYPE_ALERT = 2
} display_refresh_type_t;

const char* display_refresh_type_to_string(display_refresh_type_t type) {
    switch (type) {
        case DISPLAY_REFRESH_TYPE_OPTIONAL: return "OPTIONAL";
        case DISPLAY_REFRESH_TYPE_MANDATORY: return "MANDATORY";
        case DISPLAY_REFRESH_TYPE_ALERT: return "ALERT";
        default: return "UNKNOWN";
    }
}

static void print_queue_state(const char *prefix, display_queue_state_t *state) {
    DLOG(TAG, "%s buf_version: current=%" PRIu32 " next=%" PRIu32 " type: current=%s next=%s draw_in_progress=%d next_pending=%d task_paused=%d",
        prefix, state->current_buf_version, state->next_buf_version,
        display_refresh_type_to_string(state->current_type),
        display_refresh_type_to_string(state->next_type),
        state->draw_in_progress, state->next_pending, state->task_paused);
}

// Forward declarations for functions defined later
static void _queue_start_draw(uint32_t buf_version, display_refresh_type_t type);
void display_request_refresh(uint32_t target_buf_version, display_refresh_type_t type);

// Process any pending deferred refresh requests (called from UI task only)
static void _process_pending_flags(void) {
#if defined(CONFIG_LCD_IS_EPD)
    uint32_t flags = __atomic_exchange_n(&s_pending_refresh_flags, 0, __ATOMIC_SEQ_CST);
    if (flags == 0) return;

    FUNC_ENTRY_ARGS(TAG, "processing deferred flags: 0x%" PRIx32 "", flags);

    // Process in priority order: alert > mandatory > optional
    if (flags & (1 << DISPLAY_REFRESH_TYPE_ALERT)) {
        display_request_refresh(_get_queue_buf_version() + 1, DISPLAY_REFRESH_TYPE_ALERT);
        display_request_refresh(_get_queue_buf_version() + 2, DISPLAY_REFRESH_TYPE_OPTIONAL);
    } else if (flags & (1 << DISPLAY_REFRESH_TYPE_MANDATORY)) {
        display_request_refresh(_get_queue_buf_version() + 1, DISPLAY_REFRESH_TYPE_MANDATORY);
    } else if (flags & (1 << DISPLAY_REFRESH_TYPE_OPTIONAL)) {
        display_request_refresh(_get_queue_buf_version() + 1, DISPLAY_REFRESH_TYPE_OPTIONAL);
    }
#endif
}

static void _ui_task(void *args) {
    FUNC_ENTRY_ARGS(TAG, " starting %" PRId8 "", display_priv.rotation);
    _ui_start(display_priv.rotation);
    uint32_t task_delay_ms = _lv_timer_handler();
    while (display_priv.task_is_running) {
        // Process any deferred refresh requests first
        _process_pending_flags();

        if (display_priv.task_not_paused) {
            // Running: use calculated delay until next refresh (no polling)
            TLOG(TAG, "[%s] running, waiting ms: %" PRIu32 "", __func__, display_priv.ms);
            uint32_t now = get_millis();
            if(now >= display_priv.ms) {
                DLOG(TAG, "[%s] timer expired, refreshing now", __func__);
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
            BaseType_t notified = xSemaphoreTake(display_priv.wake_sem, pdMS_TO_TICKS(1000));
            if (notified == pdFALSE) {
                // Check if we got a task notification instead (from display_task_notify_update)
                notified = ulTaskNotifyTake(pdTRUE, 0);  // Clear notification, no wait
            }

            if (notified == pdTRUE) {
                // If we're stopping the task, skip drawing to avoid an extra frame
                if (!display_priv.task_is_running) {
                    continue;
                }
                // Process any deferred refresh requests before drawing
                _process_pending_flags();
                DLOG(TAG, "[%s] event received while paused, refreshing now", __func__);
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
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRId32 "", _get_buf_update_count());
    if(display_refresh_lock(100)) {
        display_drv_epd_turn_off(display_priv.dspl_drv);
        display_refresh_unlock();
    }
}

static void _task_req_fast_refresh(int8_t fast_refresh_time) {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRId32 " fast_refresh_time: %" PRId8 "", _get_buf_update_count(), fast_refresh_time);
    // Caller must hold display_refresh_lock; no nested lock needed
    if(_refresh_time_pending(display_priv.self->task_fast_refresh_on_time) && fast_refresh_time>=0) {
        display_priv.self->task_fast_refresh_on_time = _get_buf_update_count() + fast_refresh_time;
        if(display_priv.self->task_fast_refresh_on_time == display_priv.self->task_full_refresh_on_time) {
            display_priv.self->task_full_refresh_on_time++;
        }
    }
}

static bool _should_request_fast_refresh(display_refresh_type_t type) {
    FUNC_ENTRY_ARGS(TAG, " type: %d", type);
    if (!display_priv.self) {
        return true;
    }
    if (display_priv.self->first_flush_done == 0) {
        return true; // Prime panel with a full refresh before allowing partials
    }
    return type != DISPLAY_REFRESH_TYPE_OPTIONAL;
}

void display_on_task_paused(bool paused) {
    FUNC_ENTRY_ARGS(TAG, " paused: %d", paused);
    if (display_refresh_lock(0)) {  // Trylock for non-blocking from button callbacks
        display_queue_state.task_paused = paused;
        display_refresh_unlock();
    }
    // If lock busy, state will sync on next operation
}

// Wake paused task and reset timer period (common pattern extracted)
static inline void _wake_paused_task_and_reset_timer(void) {
    FUNC_ENTRY(TAG);
    display_priv.ms = 0;
    if (display_priv.wake_sem) {
        xSemaphoreGive(display_priv.wake_sem);
    }
    if (display_priv.timer_created && xTimerIsTimerActive(display_priv.timer)) {
        if (xTimerReset(display_priv.timer, 0) != pdPASS) {
            WLOG(TAG, "[%s] Failed to reset periodic timer", __func__);
        }
    }
}

static void _queue_start_draw(uint32_t buf_version, display_refresh_type_t type) {
    FUNC_ENTRY_ARGS(TAG, "buf %" PRIu32 " type %d", buf_version, type);
    display_queue_state.current_buf_version = buf_version;
    display_queue_state.current_type = type;
    display_queue_state.draw_in_progress = true;
    // Schedule fast refresh only when the draw really needs a full re-init; otherwise keep partial mode
    if (_should_request_fast_refresh(type)) {
        // CURRENT count (0 offset) because _ui_screen_draw() has not incremented buf_update_count yet
        _task_req_fast_refresh(0);
    } else {
        display_task_cancel_req_fast_refresh();
    }
}


void display_request_refresh(uint32_t target_buf_version, display_refresh_type_t type) {
    FUNC_ENTRY_ARGS(TAG, "buf %" PRIu32 " type %d", target_buf_version, type);
    if (display_refresh_lock(100)) {  // Reduced from 1000ms to 100ms for faster response
        FUNC_ENTRY_ARGS(TAG, "locked, buf %" PRIu32 " type %d", target_buf_version, type);
        // If task is running (not paused), bypass queue—LVGL coalesces via _task_req_fast_refresh
        if (!display_queue_state.task_paused) {
            ILOG(TAG, "[%s] task running, direct refresh (no queue) buf %" PRIu32 "", __func__, target_buf_version);
            if (_should_request_fast_refresh(type)) {
                // Don't interrupt a full refresh sequence already in progress
                if (!display_drv_epd_is_full_refresh_in_progress()) {
                    // Schedule for current count (0 offset) to trigger on next draw immediately
                    _task_req_fast_refresh(0);
                } else {
                    DLOG(TAG, "[%s] full refresh in progress, deferring mandatory request", __func__);
                }
            } else {
                // Drop back to partial mode so LVGL only drives a single refresh pass
                display_task_cancel_req_fast_refresh();
            }
            // Force immediate check by resetting the delay timer (don't wait up to 1s for next poll)
            display_priv.ms = 0;
            display_refresh_unlock();
            return;
        }

        // Task paused → use event-driven queue
        ILOG(TAG, "[%s] task paused, queue request buf %" PRIu32 " type %d", __func__, target_buf_version, type);

        if (!display_queue_state.draw_in_progress) {
            _queue_start_draw(target_buf_version, type);
            // Wake the paused task immediately and reset timer period
            _wake_paused_task_and_reset_timer();
            display_refresh_unlock();
            // No taskYIELD() - let scheduler handle naturally for lower latency
            return;
        }

        // Draw in progress

            // Deduplicate: only skip if queued buffer is LATER than target
            // (stale request). Don't skip if queued buffer == target, as screen
            // content may have changed (push→alert, etc.)
        if (display_queue_state.next_pending &&
            display_queue_state.next_buf_version > target_buf_version) {
            DLOG(TAG, "  → skipped stale (pending buf %" PRIu32 " > target %" PRIu32 ")", display_queue_state.next_buf_version, target_buf_version);
            display_refresh_unlock();
            return;
        }

            // If queued buffer == target, allow override based on priority
        if (display_queue_state.next_pending &&
            display_queue_state.next_buf_version == target_buf_version) {
            // Upgrade priority if new request is higher, otherwise replace
            // (content may differ)
            if (type >= display_queue_state.next_type) {
                display_queue_state.next_type = type;
                DLOG(TAG, "  → replaced/upgraded pending queue to type %d "
                    "(same buf, different content)", type);
            } else {
                DLOG(TAG, "  → kept higher priority pending (type %d > %d)",
                    display_queue_state.next_type, type);
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
        print_queue_state("on_draw_complete", &display_queue_state);
        if (display_queue_state.next_pending) {
            uint32_t buf = display_queue_state.next_buf_version;
            uint32_t current_buf = _get_queue_buf_version();
            display_refresh_type_t type = display_queue_state.next_type;

            // Validate: skip if buffer already at or past target (stale request)
            if (buf <= current_buf) {
                FUNC_ENTRY_ARGSD(TAG, "skipping stale queued refresh buf %" PRIu32 " "
                    "(current %" PRIu32 ")", buf, current_buf);
                display_queue_state.next_pending = false;
                display_refresh_unlock();
                return;
            }

            display_queue_state.next_pending = false;
            FUNC_ENTRY_ARGSD(TAG, " starting queued refresh buf %" PRIu32, buf);
            _queue_start_draw(buf, type);
            // Wake task for next draw
            if (display_priv.wake_sem)
                xSemaphoreGive(display_priv.wake_sem);
        } else {
            FUNC_ENTRY_ARGSD(TAG, "no queued refresh");
        }
        display_refresh_unlock();
    }
}

#if defined(CONFIG_LCD_IS_EPD)
void display_handle_driver_error(void) {
    WLOG(TAG, "[%s] driver flush failed, resetting queue", __func__);
    bool wake_task = false;
    if (display_refresh_lock(0)) {
        if (display_queue_state.task_paused) {
            if (display_queue_state.draw_in_progress) {
                uint32_t buf = display_queue_state.current_buf_version;
                display_refresh_type_t type = display_queue_state.current_type;
                display_queue_state.draw_in_progress = false;
                _queue_start_draw(buf, type);
                wake_task = true;
            }
        } else {
            _task_req_fast_refresh(0);
        }
        display_refresh_unlock();
    }
    display_priv.ms = 0;
    if (wake_task && display_priv.wake_sem) {
        xSemaphoreGive(display_priv.wake_sem);
    }
    display_task_notify_update();
}
#endif

void display_request_alert(void) {
    FUNC_ENTRY(TAG);
    display_request_refresh(_get_queue_buf_version() + 1, DISPLAY_REFRESH_TYPE_ALERT);
    display_request_refresh(_get_queue_buf_version() + 2, DISPLAY_REFRESH_TYPE_OPTIONAL);
}

void display_request_mandatory(void) {
    FUNC_ENTRY(TAG);
    display_request_refresh(_get_queue_buf_version() + 1, DISPLAY_REFRESH_TYPE_MANDATORY);
}

void display_request_optional(void) {
    FUNC_ENTRY(TAG);
    display_request_refresh(_get_queue_buf_version() + 1, DISPLAY_REFRESH_TYPE_OPTIONAL);
}

// Deferred refresh API - lock-free producers, UI task consumer
void display_post_optional(const char *reason) {
    FUNC_ENTRY_ARGS(TAG, " reason: %s", reason);
    __atomic_fetch_or(&s_pending_refresh_flags, (1 << DISPLAY_REFRESH_TYPE_OPTIONAL), __ATOMIC_SEQ_CST);
    if (display_priv.wake_sem) xSemaphoreGive(display_priv.wake_sem);
    display_task_notify_update();
}

void display_post_mandatory(const char *reason) {
    FUNC_ENTRY_ARGS(TAG, " reason: %s", reason);
    __atomic_fetch_or(&s_pending_refresh_flags, (1 << DISPLAY_REFRESH_TYPE_MANDATORY), __ATOMIC_SEQ_CST);
    if (display_priv.wake_sem) xSemaphoreGive(display_priv.wake_sem);
    display_task_notify_update();
}

void display_post_alert(const char *reason) {
    FUNC_ENTRY_ARGS(TAG, " reason: %s", reason);
    __atomic_fetch_or(&s_pending_refresh_flags, (1 << DISPLAY_REFRESH_TYPE_ALERT) | (1 << DISPLAY_REFRESH_TYPE_OPTIONAL), __ATOMIC_SEQ_CST);
    if (display_priv.wake_sem) xSemaphoreGive(display_priv.wake_sem);
    display_task_notify_update();
}

void display_request_fast_refresh() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRId32 "", _get_buf_update_count());
    display_drv_epd_request_partial_update();
}

// Shared implementation for non-blocking refresh requests
static void _display_request_refresh_nonblock(display_refresh_type_t type) {
    FUNC_ENTRY_ARGS(TAG, " type %d", type);
    if (display_refresh_lock(0)) {  // Trylock: returns immediately if busy
        uint32_t target = _get_queue_buf_version() + 1;
        if (!display_queue_state.task_paused) {
            if (_should_request_fast_refresh(type)) {
                // Task running: just set fast refresh flag
                _task_req_fast_refresh(0);
            } else {
                display_task_cancel_req_fast_refresh();
            }
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
void display_request_mandatory_nonblock(const char *reason) {
    FUNC_ENTRY_ARGS(TAG, " reason: %s", reason);
    _display_request_refresh_nonblock(DISPLAY_REFRESH_TYPE_MANDATORY);
}

void display_request_alert_nonblock(const char *reason) {
    FUNC_ENTRY_ARGS(TAG, " reason: %s", reason);
    _display_request_refresh_nonblock(DISPLAY_REFRESH_TYPE_ALERT);
}

void display_task_cancel_req_fast_refresh() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRId32 "", _get_buf_update_count());
    if(!display_priv.self) return;
    display_priv.self->task_fast_refresh_on_time = 0;
}

static void _task_req_full_refresh(int8_t full_refresh_time, bool full_refresh_force) {
    FUNC_ENTRY(TAG);
    // Caller must hold display_refresh_lock; no nested lock needed
    if(_refresh_time_pending(display_priv.self->task_full_refresh_on_time) && full_refresh_time >= 0) {
        display_priv.self->task_full_refresh_on_time = _get_buf_update_count() + full_refresh_time;
        display_priv.self->task_full_refresh_on_time_force = full_refresh_force;
    }
    TLOG(TAG, "[%s] buf_update_count: %" PRIu32 " task_full_refresh_on_time: %" PRIu32 ", "
        "task_fast_refresh_on_time: %" PRIu32 "", __FUNCTION__,
        _get_buf_update_count(), display_priv.self->task_full_refresh_on_time,
        display_priv.self->task_fast_refresh_on_time);
}

void display_request_full_refresh(bool force) {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRIu32 " force: %d",
        _get_buf_update_count(), force);
    if(!display_priv.self) return;
    if(force || _get_buf_update_count() < 5 ||
        display_priv.count_last_full_refresh + 5 <
        _get_buf_update_count()){
        display_drv_epd_request_full_update();
        display_priv.self->task_full_refresh_on_time = _get_buf_update_count();
    }
}

void display_task_cancel_req_full_refresh() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRId32 "", _get_buf_update_count());
    if(!display_priv.self) return;
    display_priv.self->task_full_refresh_on_time = 0;
    display_priv.self->task_full_refresh_on_time_force = false;
}

static void _periodic_timer_stop() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRId32 "", _get_buf_update_count());
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
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRId32 "", _get_buf_update_count());
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
            ELOG(TAG, "[%s] Failed to create periodic timer", __func__);
            return;
        }
        display_priv.timer_created = 1;
    }
#endif
    if(display_priv.timer_created) {
        if(!xTimerIsTimerActive(display_priv.timer)) {
            DLOG(TAG, "[%s] start periodic timer.", __func__);
            if (xTimerStart(display_priv.timer, 0) != pdPASS) {
                ELOG(TAG, "[%s] Failed to start periodic timer", __func__);
            }
        }
    }
}

#endif

void display_cancel_delay() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRId32 "", _get_buf_update_count());
    display_priv.ms=0;
    display_priv.ms_cancelled = 1;
}

uint32_t display_get_flush_count() {
    return _get_buf_update_count();
}

#if defined(CONFIG_LCD_IS_EPD)

static void _task_pause_wo_timer() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRId32 "", _get_buf_update_count());
    if(!display_priv.self) return;
    display_task_cancel_req_full_refresh();
    if(display_priv.task_not_paused) {
        display_priv.task_not_paused = 0;
        display_priv.self->last_flush_when_paused = _get_buf_update_count();
    }
}

void display_task_pause() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRId32 "", _get_buf_update_count());
    _task_pause_wo_timer();
    display_on_task_paused(true);
    _periodic_timer_start();
}

void display_start_task_pause_seq() {
    FUNC_ENTRY_ARGS(TAG, " pause state: %" PRIu8 "", display_priv.start_task_pause_seq);
    if(display_priv.task_not_paused) ++display_priv.start_task_pause_seq;
}

void display_cancel_task_pause_seq() {
    FUNC_ENTRY_ARGS(TAG, " pause state: %" PRIu8 "", display_priv.start_task_pause_seq);
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
        FUNC_ENTRY_ARGS(TAG, " change timer period to %" PRIu16 " sec.", actual_period);
        if (xTimerChangePeriod(display_priv.timer,
                pdMS_TO_TICKS(actual_period * 1000), 0) != pdPASS) {
            WLOG(TAG, "[%s] Failed to change timer period", __func__);
        }
    }
}

uint16_t get_display_timer_period() {
    return  display_priv.periodic_timer_period;
}

void display_task_resume() {
    FUNC_ENTRY_ARGS(TAG, " buf_update_count: %" PRId32 "", _get_buf_update_count());
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
        if (xTimerStop(display_priv.timer, 0) != pdPASS) {
            WLOG(TAG, "[%s] Failed to stop periodic timer", __func__);
        }
    }
}

bool display_task_is_paused() {
    return display_priv.task_not_paused == 0;
}

static void _timer_cb(TimerHandle_t xTimer) {
    // FUNC_ENTRY(TAG);
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
#if !defined(CONFIG_FREERTOS_UNICORE)
    BaseType_t task_result = xTaskCreatePinnedToCore(
        _ui_task, "lcd_ui_task", CONFIG_DISPLAY_TASK_STACK_SIZE, NULL, 5,
        &display_priv.task_handle
        , 1);
#else
    BaseType_t task_result = xTaskCreate(
        _ui_task, "lcd_ui_task", CONFIG_DISPLAY_TASK_STACK_SIZE, NULL, 5,
        &display_priv.task_handle);
#endif
    if (task_result != pdPASS) {
        ELOG(TAG, "[%s] Failed to create display task", __func__);
        display_priv.task_handle = NULL;
    }
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
    uint32_t target_buf = _get_buf_update_count() + 1;

    // Request a final mandatory draw via paused queue and wake immediately
    display_request_mandatory();
    if (display_priv.wake_sem)
        xSemaphoreGive(display_priv.wake_sem);

    // Wait bounded time until the buffer version reaches the target (specific final draw)
    display_priv.shutdown_counter_running = SHUT_DOWN_COUNTER_TIMES;
    while (display_priv.shutdown_counter_running) {
        uint32_t flc = _get_buf_update_count();
        if (flc >= target_buf) {
            break; // Mandatory draw has been performed
        }
        DLOG(TAG, "[%s] waiting final draw to buf=%" PRIu32 ", current=%" PRIu32 ", "
            "left %" PRIu16 " (*%" PRIu32 " ms)", __func__, target_buf,
            flc, display_priv.shutdown_counter_running, delay);
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
    FUNC_ENTRY(TAG);
    if(!display_priv.task_is_running) return;
    DMEAS_START();
#if defined(CONFIG_LCD_IS_EPD)
//     display_wait_for_task();
#else
    // Ensure one final draw on LCD before stopping
    display_priv.ms = 0; // trigger immediate draw
    uint32_t target_buf = _get_buf_update_count() + 1;
    uint16_t tries = DISPLAY_FINAL_DRAW_RETRIES;
    while (tries--) {
        if (_get_buf_update_count() >= target_buf) {
            break;
        }
        // Nudge the running task to wake immediately
        display_task_notify_update();
        vTaskDelay(pdMS_TO_TICKS(DISPLAY_FINAL_DRAW_INTERVAL_MS));
    }
#endif
    // Unblock paused task to allow clean exit without extra draw
    if (display_priv.wake_sem)
        xSemaphoreGive(display_priv.wake_sem);
    display_cancel_delay();
    display_priv.task_is_running = false;
    uint32_t wait = get_millis() + DISPLAY_TASK_WAIT_TIMEOUT_MS;
    uint16_t i = 0;
    while (!display_priv.task_is_finished) {
        delay_ms(DISPLAY_TASK_WAIT_INTERVAL_MS);
        if (get_millis() > wait) {
            if(display_priv.task_handle){
                WLOG(TAG, "[%s] Task not finished, deleting", __func__);
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
    DMEAS_END_ARGS(TAG, " %" PRIu16 " 150 ms loops", i);
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

    if(!display_priv.refreshing_sem) {
        display_priv.refreshing_sem = xSemaphoreCreateBinary();
        if (!display_priv.refreshing_sem) {
            ELOG(TAG, "[%s] Failed to create refreshing semaphore", __func__);
            _lifecycle_unlock();
            return NULL;
        }
    }
    display_refresh_unlock();
    if(!display_priv.wake_sem) {
        display_priv.wake_sem = xSemaphoreCreateBinary();
        if (!display_priv.wake_sem) {
            ELOG(TAG, "[%s] Failed to create wake semaphore", __func__);
            _lifecycle_unlock();
            return NULL;
        }
    }
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
