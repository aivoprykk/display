#ifndef EF04F767_437A_498D_8595_AE999C55B241
#define EF04F767_437A_498D_8595_AE999C55B241

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_DISPLAY_USE_LVGL

#include "esp_lcd_panel_vendor.h"
#include "ui.h"

bool _lvgl_lock(int timeout_ms);
void _lvgl_unlock(void);

// esp_lcd_panel_handle_t display_ssd1681_new();
// void display_ssd1681_del();
// esp_err_t display_epd_ssd1681_request_full_update();
// esp_err_t display_epd_ssd1681_request_fast_update();

esp_lcd_panel_handle_t display_ssd168x_new();
void display_ssd168x_del();
esp_err_t display_epd_ssd168x_request_full_update();
esp_err_t display_epd_ssd168x_request_fast_update();

esp_lcd_panel_handle_t display_st7789_new();
void display_st7789_del();

void driver_st7789_bl_set(uint8_t brightness_percent);

#if defined(CONFIG_DISPLAY_DRIVER_SSD1681)
#define LCD_H_RES (200)               // horizontal
#define LCD_H_VISIBLE (200)           // vertical
#define LCD_V_RES (200)               // vertical
#define LCD_H_GAP (0)
#define LCD_V_GAP (0)
#endif
#if defined(CONFIG_DISPLAY_DRIVER_SSD1680)
#define LCD_H_RES (128)               // horizontal
#define LCD_H_VISIBLE (122)           // vertical
#define LCD_V_RES (250)               // vertical
#define LCD_H_GAP (0)
#define LCD_V_GAP (0)
#endif
#if defined(CONFIG_DISPLAY_DRIVER_SSD1681) || defined(CONFIG_DISPLAY_DRIVER_SSD1680)
#define display_new display_ssd168x_new
#define display_del display_ssd168x_del
#define display_epd_request_full_update display_epd_ssd168x_request_full_update
#define display_epd_request_fast_update display_epd_ssd168x_request_fast_update
#endif
#if defined(CONFIG_DISPLAY_DRIVER_ST7789)
#define LCD_H_RES (320)               // horizontal
#define LCD_V_RES (170)               // vertical
#define LCD_H_GAP (0)
#define LCD_V_GAP (35)
#define display_new display_st7789_new
#define display_del display_st7789_del
#define display_epd_request_full_update(a) ((void)0)
#endif

#define LCD_RESOLUTION  (LCD_H_RES * LCD_V_RES)
#define LCD_ROW_LEN     (LCD_H_RES / 8)           // gates for x resolution
#define LCD_PIXELS      (LCD_V_RES * LCD_ROW_LEN) // total pixels

#define BYTE_PADDING(w) (((w + 7u) / 8 ) * 8) // Align to nearest 8 bits
#define LCD_PIXELS_MEM_ALIGNED (LCD_H_RES * BYTE_PADDING(LCD_V_RES) / 8)

#define H_NORM_PX_VISIBLE(h_scr_percent) ((int16_t)((LCD_H_VISIBLE / 100.0) * (h_scr_percent)))
#define V_NORM_PX(v_scr_percent) ((int16_t)((LCD_V_RES / 100.0) * (v_scr_percent)))

#if defined(CONFIG_DISPLAY_DRIVER_ST7789)
#define LCD_BUF_SIZE (LCD_PIXELS/10)
#else
#define LCD_BUF_SIZE (LCD_PIXELS)
#endif

#define L_LVGL_TASK_MAX_DELAY_MS 50
#define L_LVGL_TASK_MIN_DELAY_MS 1

#endif

#ifdef __cplusplus
}
#endif


#endif /* EF04F767_437A_498D_8595_AE999C55B241 */
