/*
 */

#include <stdio.h>
#include <esp_lcd_panel_ssd168x.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"

#include "logger_common.h"
#include "driver_vendor.h"

#include "img_bitmap.h"
#ifdef CONFIG_DISPLAY_DRIVER_SSD1680
#include "../../../ssd1680_waveshare_2in13_lut.h"
static const char *TAG = "display_drv.ssd1680";
#endif
#ifdef CONFIG_DISPLAY_DRIVER_SSD1681
#include "../../../ssd1681_waveshare_1in54_lut.h"
static const char *TAG = "example.ssd1681";
#endif

// Using SPI2 in the example
#define LCD_HOST  SPI2_HOST

#define LVGL_TICK_PERIOD_MS    1

// static SemaphoreHandle_t panel_refreshing_sem = NULL;

extern void example_lvgl_demo_ui(lv_disp_t *disp);
extern void ui_demo(void);
extern lv_obj_t *ui_InfoScreen;
// static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
// static lv_disp_drv_t disp_drv;      // contains callback functions

// #ifdef CONFIG_DISPLAY_DRIVER_SSD1680
// static uint8_t fast_refresh_lut[] = SSD1680_WAVESHARE_2IN13_V2_LUT_FAST_REFRESH_KEEP;
// #endif
// #ifdef CONFIG_DISPLAY_DRIVER_SSD1681
// static uint8_t fast_refresh_lut[] = SSD1681_WAVESHARE_1IN54_V2_LUT_FAST_REFRESH_KEEP;
// #endif

// static void clearScreen(esp_lcd_panel_handle_t panel_handle, uint8_t * color_data)
// {
//     MEAS_START();
//     if(lock_ssd168x(1000) == false) {
//         ESP_LOGE(TAG, "Failed to lock the display");
//         return;
//     }
//     ESP_ERROR_CHECK(epaper_panel_clear_screen_ssd168x(panel_handle, color_data, 0xff));
//     MEAS_END(TAG, "[%s] took %llu us",__func__);
// }

// #define BIT_SET(a, b)       ((a) |= (1u << (b)))
// #define BIT_CLEAR(a, b)     ((a) &= ~(1u << (b)))

// /* omitted irrelevant code */
// void my_set_px_cb(lv_disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
// {
//     // printf("x: %d, y: %d, color: %d\n", x, y, color.full);
//     uint16_t byte_index = (x >> 3u) + (y * LCD_ROW_LEN);
//     uint8_t bit_index = x & 0x07u;

//     if (color.full) {
//         BIT_SET(buf[byte_index], 7 - bit_index);
//     } else {
//         BIT_CLEAR(buf[byte_index], 7 - bit_index);
//     }
// }

void app_main(void)
{

    esp_lcd_panel_handle_t panel_handle = display_new();
    if (!panel_handle) {
        ESP_LOGE(TAG, "Failed to create LCD panel handle");
        return;
    }

    ESP_LOGI(TAG, "Display LVGL Demo");
    ui_demo();
    
    while (1) {
        // raise the task priority of LVGL and/or reduce the handler period can improve the performance
        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
