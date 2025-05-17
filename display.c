
#include "display_private.h"
#if defined(CONFIG_DISPLAY_ENABLED)
#include "display.h"
#include "driver_vendor.h"
#include "logger_common.h"

static const char *TAG = "display";
#define LCD_UI_TIMER_PERIOD_S 60
#define DISPLAY_TIMER_TASK_DELAY_MS 10

typedef struct display_priv_s {
    esp_lcd_panel_handle_t dspl_drv;
    display_t * self;
    int8_t rotation;
    bool displayOK;
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
    SemaphoreHandle_t timer_sem;
    TaskHandle_t task_handle;
    esp_timer_handle_t timer;
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
    .displayOK = false, \
    .count_last_full_refresh = 0, \
    .count_last_fast_refresh = 0, \
    .off_screen_count = 0, \
    .off_screen_requested = 0, \
    .task_is_running = true, \
    .task_not_paused = true, \
    .task_is_finished = false,     \
    .ms = 0, \
    .ms_cancelled = 0, \
    .timer_created = 0, \
    .shutdown_counter_running = 0, \
    .refreshing_sem = NULL, \
    .timer_sem = NULL,    \
    .task_handle = 0, \
    .timer = 0, \
    .start_task_pause_seq = 0, \
    .periodic_timer_period = 0, \
}

struct display_priv_s display_priv = DISPLAY_PRIV_DEFAULTS();

bool display_refresh_lock(int timeout) {
    if (!display_priv.refreshing_sem) return false;
    const TickType_t timeout_ticks = (timeout == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout);
    return  xSemaphoreTake(display_priv.refreshing_sem, timeout_ticks) == pdTRUE;
}

void display_refresh_unlock() {
    if (display_priv.refreshing_sem) {
        xSemaphoreGive(display_priv.refreshing_sem);
    }
}

static bool lock_timer(int timeout) {
    if (!display_priv.timer_sem) return false;
    const TickType_t timeout_ticks = (timeout == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout);
    return  xSemaphoreTake(display_priv.timer_sem, timeout_ticks) == pdTRUE;
}

static void unlock_timer() {
    if (display_priv.timer_sem) {
        xSemaphoreGive(display_priv.timer_sem);
    }
}

static uint32_t _lv_timer_handler() {
#if (C_LOG_LEVEL < 2)
    DLOG(TAG, "[%s] %ld\n", __func__, display_priv.self->buf_update_count);
#endif
    uint32_t task_delay_ms = L_LVGL_TASK_MAX_DELAY_MS;
    if (_lvgl_lock(-1)) {
        task_delay_ms = lv_timer_handler(); 
        _lvgl_unlock();
    }
    if (task_delay_ms > L_LVGL_TASK_MAX_DELAY_MS) {
        task_delay_ms = L_LVGL_TASK_MAX_DELAY_MS;
    } else if (task_delay_ms < L_LVGL_TASK_MIN_DELAY_MS) {
        task_delay_ms = L_LVGL_TASK_MIN_DELAY_MS;
    }
#if (C_LOG_LEVEL < 2)
    DLOG(TAG, "[%s] done %ld, %lu\n", __func__, display_priv.self->buf_update_count, task_delay_ms);
#endif
    return task_delay_ms;
}

void display_incr_buf_update_count() {
#if (C_LOG_LEVEL < 2)
    ILOG(TAG, "[%s] %ld", __func__, display_priv.self->buf_update_count);
#endif
    ++display_priv.self->buf_update_count;
}

uint16_t get_offscreen_counter() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] %hhu, %ld", __func__, display_priv.off_screen_count, display_priv.self->buf_update_count);
#endif
    return display_priv.off_screen_count;
}

// #define CONFIG_FULL_REFRESH_ON_FIRST_FLUSH
// #define CONFIG_FULL_REFRESH_ON_SECOND_FLUSH
// #define CONFIG_FULL_REFRESH_ON_THIRD_FLUSH

static uint32_t _ui_screen_draw() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld", __func__, display_priv.self->buf_update_count);
#endif
#if (C_LOG_LEVEL < 2)
    DMEAS_START();
#endif
    _lvgl_lock(0);
    _lvgl_unlock();
#if defined(CONFIG_LCD_IS_EPD)
    if(display_priv.start_task_pause_seq > 1) {
        display_task_pause();
        display_priv.start_task_pause_seq = 0;
    }
    if(display_priv.self->first_flush_done || display_drv_epd_get_flush_count()) {
        if(!display_priv.self->first_flush_done) {
            display_priv.self->first_flush_done = 1;
#if defined(CONFIG_FULL_REFRESH_ON_SECOND_FLUSH)
    goto do_full_refresh;
#endif
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
    if(display_priv.self->buf_update_count && display_priv.self->task_full_refresh_on_time == display_priv.self->buf_update_count) {
#if defined(CONFIG_FULL_REFRESH_ON_SECOND_FLUSH) || defined(CONFIG_FULL_REFRESH_ON_THIRD_FLUSH)
        do_full_refresh:
#endif
#if (C_LOG_LEVEL < 2)
        DLOG(TAG, "[%s] Full ... count: %lu\n", __func__, display_priv.self->buf_update_count);
#endif
        display_request_full_refresh(display_priv.self->task_full_refresh_on_time_force);
        display_task_cancel_req_fast_refresh();
    }
    else if(display_priv.self->task_fast_refresh_on_time == display_priv.self->buf_update_count) {
#if (C_LOG_LEVEL < 2)
        DLOG(TAG, "[%s] Fast ... count: %lu\n", __func__, display_priv.self->buf_update_count);
#endif
        display_request_fast_refresh();
        display_task_cancel_req_full_refresh();
    }
    else {
#if (C_LOG_LEVEL < 2)
        DLOG(TAG, "[%s] Partial ... count: %lu\n", __func__, display_priv.self->buf_update_count);
#endif
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
#if (C_LOG_LEVEL < 2)
    DMEAS_END(TAG, "[%s] ... done. %ld (delay %lu), refr_timer took: %llu us", __FUNCTION__, display_priv.self->buf_update_count, task_delay_ms);
#endif
    return task_delay_ms;
};

void display_set_rotation(int8_t rotation) {
    WLOG(TAG, "[%s] %d", __func__, rotation);
    if(display_refresh_lock(portMAX_DELAY) == pdTRUE) {
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
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s]", __func__);
#endif
    display_drv_lv_init();
    display_set_rotation(rotation);
    ui_init();
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
    delay_ms(200);
}

static void _ui_task(void *args) {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] starting %hhd", __FUNCTION__, display_priv.rotation);
#endif
    _ui_start(display_priv.rotation);
    uint32_t task_delay_ms = _lv_timer_handler();
    while (display_priv.task_is_running) {
        if(display_refresh_lock(portMAX_DELAY) == pdTRUE) {
            display_refresh_unlock();
        }
        if(get_millis() > display_priv.ms) {
            uint8_t mode = display_priv.task_not_paused ? 2 : display_priv.self->task_resumed_for_times ? 1 : 0;
            if (mode) {
#if (C_LOG_LEVEL < 1)
                DLOG(TAG, "[%s] screen draw while %s\n", __FUNCTION__, (mode == 2 ? "not paused" : mode == 1 ? "resumed" : ""));
#endif
                task_delay_ms = _ui_screen_draw();
                if(mode == 1 && display_priv.self->task_resumed_for_times) 
                    --display_priv.self->task_resumed_for_times;
            }
        }
        delay_ms(DISPLAY_TIMER_TASK_DELAY_MS);
    }
    UNUSED_PARAMETER(task_delay_ms);
#if defined(CONFIG_LCD_IS_EPD)
    display_drv_epd_turn_off(display_priv.dspl_drv);
#endif
    ILOG(TAG, "[%s] finishing\n", __FUNCTION__);
    display_priv.task_is_finished = 1;
    display_priv.task_handle = 0;
    vTaskDelete(NULL);
}

void display_request_partial_refresh() {
    display_drv_epd_request_partial_update();
}

void display_shut_down() {
    ILOG(TAG, "[%s] count: %ld", __func__, display_priv.self->buf_update_count);
    if(display_refresh_lock(portMAX_DELAY) == pdTRUE) {
        display_drv_epd_turn_off(display_priv.dspl_drv);
        display_refresh_unlock();
    }
}

static void _task_req_fast_refresh(int8_t fast_refresh_time) {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld fast_refresh_time: %hhd", __func__, display_priv.self->buf_update_count, fast_refresh_time);
#endif
    if(display_refresh_lock(portMAX_DELAY) == pdTRUE) {
        if(display_priv.self->task_fast_refresh_on_time < display_priv.self->buf_update_count && fast_refresh_time>=0) {
            display_priv.self->task_fast_refresh_on_time = display_priv.self->buf_update_count+fast_refresh_time;
            if(display_priv.self->task_fast_refresh_on_time == display_priv.self->task_full_refresh_on_time) {
                display_priv.self->task_full_refresh_on_time++;
            }
        }
        display_refresh_unlock();
    }
}

void display_request_fast_refresh() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld", __func__, display_priv.self->buf_update_count);
#endif
    display_drv_epd_request_fast_update();
}

void display_task_cancel_req_fast_refresh() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld", __func__, display_priv.self->buf_update_count);
#endif
    display_priv.self->task_fast_refresh_on_time = 0;
}

static void _task_req_full_refresh(int8_t full_refresh_time, bool full_refresh_force) {
    if(display_refresh_lock(portMAX_DELAY) == pdTRUE) {
        if(display_priv.self->task_full_refresh_on_time < display_priv.self->buf_update_count && full_refresh_time >= 0) {
            display_priv.self->task_full_refresh_on_time = display_priv.self->buf_update_count + full_refresh_time;
            display_priv.self->task_full_refresh_on_time_force = full_refresh_force;
        }
        display_refresh_unlock();
    }
#if (C_LOG_LEVEL < 1)
    DLOG(TAG, "[%s] count: %ld task_full_refresh_on_time: %ld, task_fast_refresh_on_time: %ld\n", __FUNCTION__, display_priv.self->buf_update_count, display_priv.self->task_full_refresh_on_time, display_priv.self->task_fast_refresh_on_time);
#endif
}

void display_request_full_refresh(bool force) {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld force: %d", __func__, display_priv.self->buf_update_count, force);
#endif
    if(force || display_priv.self->buf_update_count < 1 || display_priv.self->buf_update_count < 5 || display_priv.count_last_full_refresh + 5  < display_priv.self->buf_update_count){
        display_drv_epd_request_full_update();
        display_priv.self->task_full_refresh_on_time = display_priv.self->buf_update_count;
    }
}

void display_task_cancel_req_full_refresh() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld", __func__, display_priv.self->buf_update_count);
#endif
    display_priv.self->task_full_refresh_on_time = 0;
    display_priv.self->task_full_refresh_on_time_force = false;
}

static esp_err_t _task_resume_for_times_wo_timer(uint8_t times, int8_t fast_refresh_time, int8_t full_refresh_time, bool full_refresh_force) {
#if (C_LOG_LEVEL < 2)
    DLOG(TAG, "[%s] count: %ld task_full_refresh_on_time: %ld, task_fast_refresh_on_time: %ld\n", __FUNCTION__, display_priv.self->buf_update_count, display_priv.self->task_full_refresh_on_time, display_priv.self->task_fast_refresh_on_time);
#endif
    if(display_priv.task_is_running) {
        if(display_refresh_lock(portMAX_DELAY) == pdTRUE) {
            //task_resumed_for_times += times;
            if(display_priv.self->task_resumed_for_times < times) {
                display_priv.self->task_resumed_for_times = times;
            }
            display_refresh_unlock();
        }
        if(display_priv.self->task_resumed_for_times>=times){
            if(full_refresh_time>=0) {
                _task_req_full_refresh(full_refresh_time, full_refresh_force);
            }
            if(fast_refresh_time>=0) {
                _task_req_fast_refresh(fast_refresh_time);
            }
            // if(display_priv.self->task_full_refresh_on_time < display_priv.self->buf_update_count && display_priv.self->task_fast_refresh_on_time < display_priv.self->buf_update_count) {
            //     display_drv_epd_request_partial_update();
            // }
            return ESP_OK;
        }
    }
    return ESP_ERR_TIMEOUT;
}

static void _periodic_timer_stop() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld", __func__, display_priv.self->buf_update_count);
#endif
    if (display_priv.timer_created && lock_timer(portMAX_DELAY) == pdTRUE) {
        if(esp_timer_is_active(display_priv.timer)) {
#if (C_LOG_LEVEL < 2)
            ILOG(TAG, "[%s] stop periodic timer count: %ld", __func__, display_priv.self->buf_update_count);
#endif
            if(esp_timer_stop(display_priv.timer)) {
                WLOG(TAG, "[%s] failed to stop periodic timer", __func__);
            }
        }
        unlock_timer();
    }
}

static void _timer_cb(void*arg);

static void _periodic_timer_start() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld", __func__, display_priv.self->buf_update_count);
#endif
#if defined(CONFIG_LCD_IS_EPD)
    if(!display_priv.timer_created) {
        const esp_timer_create_args_t lcd_periodic_timer_args = {
            .callback = &_timer_cb,
            .name = "lcd_periodic",
        };
        if(esp_timer_create(&lcd_periodic_timer_args, &display_priv.timer)){
            WLOG(TAG, "[%s] failed to create periodic timer", __func__);
            return;
        }
     display_priv.timer_created = 1;
    }
#endif
    if(display_priv.timer_created && lock_timer(portMAX_DELAY) == pdTRUE) {
        if(!esp_timer_is_active(display_priv.timer)) {
#if (C_LOG_LEVEL < 2)
            ILOG(TAG, "[%s] start periodic timer count: %ld", __func__, display_priv.self->buf_update_count);
#endif
            esp_timer_start_periodic(display_priv.timer, SEC_TO_US(display_priv.periodic_timer_period ? display_priv.periodic_timer_period : LCD_UI_TIMER_PERIOD_S));
        }
        unlock_timer();
    }
}

void display_task_resume_for_times(uint8_t times, int8_t fast_refresh_time, int8_t full_refresh_time, bool full_refresh_force) {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld times: %hhu, fast_refresh_time: %hhd, full_refresh_time: %hhd, full_refresh_force: %d", __func__, display_priv.self->buf_update_count, times, fast_refresh_time, full_refresh_time, full_refresh_force);
#endif
    if(display_priv.self->task_resumed_for_times>=times || display_priv.task_not_paused) {
#if (C_LOG_LEVEL < 2)
        ILOG(TAG, "[%s] already running times: %hhu, not_paused: %hhu", __func__, times, display_priv.task_not_paused);
#endif
        return;
    }
#if (C_LOG_LEVEL < 3)
    IMEAS_START();
#endif
    if(!_task_resume_for_times_wo_timer(times,fast_refresh_time,full_refresh_time, full_refresh_force)){
        _periodic_timer_stop();
        _periodic_timer_start();
    }
#if (C_LOG_LEVEL < 3)
    IMEAS_END(TAG, "[%s] took %llu us", __FUNCTION__);
#endif
}

void display_cancel_delay() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld", __func__, display_priv.self->buf_update_count);
#endif
    display_priv.ms=0;
    display_priv.ms_cancelled = 1;
}

uint32_t display_get_buf_update_count() {
    return display_priv.self->buf_update_count;
}

uint32_t display_get_flush_count() {
    return display_drv_epd_get_flush_count();
}

static void _task_pause_wo_timer() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld", __func__, display_priv.self->buf_update_count);
#endif
    display_task_cancel_req_full_refresh();
    if(display_priv.task_not_paused) {
        display_priv.task_not_paused = 0;
        display_priv.self->last_flush_when_paused = display_priv.self->buf_update_count;
    }
}

void display_task_pause() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld", __func__, display_priv.self->buf_update_count);
#endif
    _task_pause_wo_timer();
    _periodic_timer_start();
}

void display_start_task_pause_seq() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] pause state: %hhu", __func__, display_priv.start_task_pause_seq);
#endif
    ++display_priv.start_task_pause_seq;
}

void display_cancel_task_pause_seq() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] pause state: %hhu", __func__, display_priv.start_task_pause_seq);
#endif
    display_priv.start_task_pause_seq = 0;
}

void display_timer_set_period(uint16_t period) {
    display_priv.periodic_timer_period = period;
    if(esp_timer_is_active(display_priv.timer)) {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] restart timers for run every %hu sec.", __func__, period);
#endif
        _periodic_timer_stop();
        _periodic_timer_start();
    }
}

uint16_t get_display_timer_period() {
    return  display_priv.periodic_timer_period;
}

void display_task_resume() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] count: %ld", __func__, display_priv.self->buf_update_count);
#endif
    display_task_cancel_req_full_refresh();
    if(display_priv.start_task_pause_seq)
        display_priv.start_task_pause_seq = 0;
    if(!display_priv.task_not_paused)
        display_priv.task_not_paused = 1;
    display_priv.ms = 0;
    if(lock_timer(portMAX_DELAY) == pdTRUE) {
        if(esp_timer_is_active(display_priv.timer)){
#if (C_LOG_LEVEL < 2)
            ILOG(TAG, "[%s] stop periodic timer at count: %ld", __func__, display_priv.self->buf_update_count);
#endif
            esp_timer_stop(display_priv.timer);
        }
        unlock_timer();
    }
}

bool display_task_is_paused() {
    return display_priv.task_not_paused == 0;
}

static void _timer_cb(void*arg) {
    ILOG(TAG, "[%s]", __func__);
    _task_resume_for_times_wo_timer(1, -1, -1, false); // one partial refresh
}

void display_task_start() {
    ILOG(TAG, "[%s]", __func__);
    xTaskCreate(_ui_task, "lcd_ui_task", CONFIG_DISPLAY_TASK_STACK_SIZE, NULL, 5, &display_priv.task_handle);
}

#if defined(CONFIG_LCD_IS_EPD)
#define SHUT_DOWN_COUNTER_TIMES 300U
#define SHUT_DOWN_COUNTER_DELAY 50U
#else
#define SHUT_DOWN_COUNTER_TIMES 10U
#define SHUT_DOWN_COUNTER_DELAY 50U
#endif

void display_wait_for_task() {
    ILOG(TAG, "[%s]", __func__);
    IMEAS_START();
    uint32_t delay = SHUT_DOWN_COUNTER_DELAY;
    _periodic_timer_stop();
    display_cancel_delay();
    if(display_priv.task_is_running && !display_priv.task_not_paused) display_task_resume();
    display_priv.shutdown_counter_running = SHUT_DOWN_COUNTER_TIMES;
    while(!get_offscreen_counter() && display_priv.shutdown_counter_running) {
#if (C_LOG_LEVEL < 2)
        DLOG(TAG, "[%s] left %hu times (*%lu ms) wait for off_screen drawn\n", __func__, display_priv.shutdown_counter_running, delay);
#endif
        delay_ms(delay);
        --display_priv.shutdown_counter_running;
    }
    _task_pause_wo_timer();
    IMEAS_END(TAG, "[%s] took %llu us", __FUNCTION__);
}

#undef SHUT_DOWN_COUNTER_TIMES
#undef SHUT_DOWN_COUNTER_DELAY

static void _ui_stop() {
#if (C_LOG_LEVEL < 2)
    ILOG(TAG, "[%s]", __func__);
    DMEAS_START();
#endif
    display_wait_for_task();
    display_priv.task_is_running = false;
    uint32_t wait = get_millis() + 15000;
    uint16_t i = 0;
    while (!display_priv.task_is_finished) {
        delay_ms(150);
        if (get_millis() > wait) {
            if(display_priv.task_handle){
                WLOG(TAG, "[%s] task not finished, deleting", __func__);
                vTaskDelete(display_priv.task_handle);
            }
            break;
        }
        ++i;
    }
    //delay_ms(4000);
    if(display_priv.timer){
#if (C_LOG_LEVEL < 2)
        DLOG(TAG, "[%s] stop and delete periodic timer\n", __func__);
#endif
        _periodic_timer_stop();
        ESP_ERROR_CHECK(esp_timer_delete(display_priv.timer));
        display_priv.timer = 0;
    }

    ui_deinit();
#if (C_LOG_LEVEL < 2)
    DMEAS_END(TAG, "[%s] %hu 150 ms loops, total %llu us ",  __FUNCTION__, i);
#endif
}

struct display_s *display_init(struct display_s *me, struct display_op_s *op) {
    ILOG(TAG, "[%s]", __func__);
#if defined(LOG_LOCAL_LEVEL)
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
#endif
    if (display_priv.displayOK) return me;
    memset(me, 0, sizeof(struct display_s));
    me->op = op;
    display_priv.self = me;
    display_priv.dspl_drv = display_drv_new();

    if(display_priv.dspl_drv)
        display_priv.displayOK = true;

    display_priv.refreshing_sem = xSemaphoreCreateBinary();
    display_refresh_unlock();
    display_priv.timer_sem = xSemaphoreCreateBinary();
    unlock_timer();

    return me;
}

void display_uninit(struct display_s *me) {
    ILOG(TAG, "[%s]", __func__);
    if (display_priv.displayOK) {
        _ui_stop();
        display_drv_del();
        if (display_priv.refreshing_sem != NULL){
            vSemaphoreDelete(display_priv.refreshing_sem);
            display_priv.refreshing_sem = NULL;
        }
        if (display_priv.timer_sem != NULL){
            vSemaphoreDelete(display_priv.timer_sem);
            display_priv.timer_sem = NULL;
        }
        memset(&display_priv, 0, sizeof(struct display_priv_s));
        memset(me, 0, sizeof(struct display_s));
    }
}

#endif
