#include <stdio.h>
#include "freertos/FreeRTOS.h"

#include "logger_common.h"
#if defined(CONFIG_LOGGER_USE_GLOBAL_LOG_LEVEL)
#define C_LOG_LEVEL CONFIG_LOGGER_GLOBAL_LOG_LEVEL
#else
#define C_LOG_LEVEL 3
#endif
#include "common_log.h"

#include "display.h"
#include "driver_vendor.h"
#include "ui_events.h"
#include "numstr.h"

static struct display_s display = {0};
static uint8_t screen_auto_refresh = 0;
static const char *TAG = "lvgl_demo";
static int8_t screen_times = 0;
static uint8_t rotation = 0;
static bool running = 1;
static int screen = 0;
static int times = 20;
static int num_calls = 0;
static void ui_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data) {
    if(base == UI_EVENT) {
        switch(id) {
            case UI_EVENT_FLUSH_START:
                ILOG(TAG, "[%s] d %s", __FUNCTION__, ui_event_strings(id));
                break;
            case UI_EVENT_FLUSH_DONE:
                ILOG(TAG, "[%s] d %s", __FUNCTION__, ui_event_strings(id));
                break;
            default:
                break;
        }
    }
}

static esp_err_t events_init() {
    ILOG(TAG, "[%s]", __FUNCTION__);
    if(esp_event_loop_create_default()) return ESP_FAIL;
    if(esp_event_handler_register(UI_EVENT, ESP_EVENT_ANY_ID, ui_event_handler, NULL)){
        WLOG(TAG, "[%s] event reg fail.", __FUNCTION__);
    }
    return ESP_OK;
}

#include "esp_random.h"
float randomFloat() {
    uint32_t r = esp_random();               // Generate a random 32-bit number
    float f = (float)r / (float)UINT32_MAX;  // Convert to a float between 0 and 1
    return f * 127;                          // Scale to the range 0-127
}

static uint32_t show_screen(int full) {
    if(display_get_buf_update_count() >= times) {
        showBlankScreen(0);
        screen = 1;
    }
    else{
        if(full) {
            showSpeedScreen();
            //showSleepScreen();
        }
        char spd[8] = {0};
        float spd_f = randomFloat();
        if(spd_f >= 100) {
            f1_to_char(spd_f, &spd[0]);
        }
        else {
            f2_to_char(spd_f, &spd[0]);
        }
        lv_label_set_text(ui_speed_screen.speed, spd);
    }
    return 50; // Delay
}

static uint32_t screen_cb(void* arg) {
    ILOG(TAG, "[%s]", __func__);
    uint32_t delay = 100;
    if(screen_times == 0 && display_get_buf_update_count() > 0) {
        display_set_rotation(rotation);
        if(rotation == 3) {
            rotation = 0;
        } else {
            rotation++;
        }
    }
    if(display_refresh_lock(portMAX_DELAY) == pdTRUE) {
        if(screen_times < 1 || display_get_buf_update_count() == times) {
           printf("Redraw full screen...\n");
            delay = show_screen(1);
            display_request_fast_refresh();
        } else {
            printf("Redraw partial screen..\n");
            delay = show_screen(0);
            // display_request_partial_refresh();
        }
        if(screen_times > 10) {
            screen_times = 0;
        }
        else screen_times++;
        display_incr_buf_update_count();
        display_refresh_unlock();
    }
    else {
        printf("Failed to lock display for update\n");
    }
    return delay;
}

static display_op_t screen_ops = {
    .screen_cb = screen_cb,
};

void app_main(void) {
    events_init();
    display_init(&display, &screen_ops);
    display_set_rotation(0);
    display_task_start();
    if(!screen_auto_refresh){
       display_task_pause();
    }
    delay_ms(100);
    while (running) {
        printf("--- [%s] ... num_calls: %d screen_times: %d ---\n", __func__, num_calls, screen_times);
        if(!screen_auto_refresh){
            if(num_calls > 0) {
                display_task_resume();
                if(running)
                    vTaskDelay(6000 / portTICK_PERIOD_MS);
            }
            else {
                // first call
                display_task_resume_for_times(1, -1, -1, false);
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }
            ++num_calls;
        }
        if(display_get_buf_update_count() >= times) {
            running = 0;
        }
    }
    printf("Stopping display task...\n");
    display_uninit(&display);
    esp_event_handler_unregister(UI_EVENT, ESP_EVENT_ANY_ID, ui_event_handler);
}
