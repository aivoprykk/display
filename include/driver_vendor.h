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

esp_lcd_panel_handle_t display_ssd1681_new();
void display_ssd1681_del();

esp_lcd_panel_handle_t display_ssd1680_new();
void display_ssd1680_del();

esp_lcd_panel_handle_t display_st7789_new();
void display_st7789_del();

void driver_st7789_bl_set(uint8_t brightness_percent);

#if defined(CONFIG_DISPLAY_DRIVER_SSD1681)
#define LCD_H_RES (200)               // horizontal
#define LCD_V_RES (200)               // vertical
#define LCD_H_GAP (0)
#define LCD_V_GAP (0)
#define display_new display_ssd1681_new
#define display_del display_ssd1681_del
#endif
#if defined(CONFIG_DISPLAY_DRIVER_SSD1680)
#define LCD_H_RES (128)               // horizontal
#define LCD_V_RES (250)               // vertical
#define LCD_H_GAP (6)
#define LCD_V_GAP (0)
#define display_new display_ssd1680_new
#define display_del display_ssd1680_del
#endif
#if defined(CONFIG_DISPLAY_DRIVER_ST7789)
#define LCD_H_RES (320)               // horizontal
#define LCD_V_RES (170)               // vertical
#define LCD_H_GAP (0)
#define LCD_V_GAP (35)
#define display_new display_st7789_new
#define display_del display_st7789_del
#endif

#define L_LVGL_TASK_MAX_DELAY_MS 500
#define L_LVGL_TASK_MIN_DELAY_MS 1

#endif

#ifdef __cplusplus
}
#endif


#endif /* EF04F767_437A_498D_8595_AE999C55B241 */
