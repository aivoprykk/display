#ifndef EF04F767_437A_498D_8595_AE999C55B241
#define EF04F767_437A_498D_8595_AE999C55B241

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_lcd_panel_vendor.h"

#ifdef CONFIG_DISPLAY_USE_LVGL
#include "ui.h"
#endif

typedef struct m_area_s {
    int x1;
    int y1;
    int x2;
    int y2;
} m_area_t;

typedef enum m_rot_e {
    DISP_ROT_NONE = 0,
    DISP_ROT_90 = 1,
    DISP_ROT_180 = 2,
    DISP_ROT_270 = 3,
} m_rot_t;

// esp_lcd_panel_handle_t display_ssd1681_new();
// void display_ssd1681_del();
// esp_err_t display_epd_ssd1681_request_full_update();
// esp_err_t display_epd_ssd1681_request_fast_update();

esp_lcd_panel_handle_t display_ssd168x_new();
void display_ssd168x_del();
esp_err_t display_epd_ssd168x_request_full_update();
esp_err_t display_epd_ssd168x_request_fast_update();
esp_err_t display_epd_ssd168x_set_rotation(int r);
bool lock_ssd168x(int timeout_ms);
void unlock_ssd168x();
esp_err_t display_epd_ssd168x_refresh_and_turn_off(esp_lcd_panel_handle_t panel_handle, int rotated, m_area_t *area, uint8_t *color_map);
esp_err_t display_epd_ssd168x_turn_on(esp_lcd_panel_handle_t panel_handle);

#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
#define lv_display_t lv_disp_t
#define lv_image_dsc_t lv_img_dsc_t
#endif

lv_disp_t * display_ssd1680_get();

#if (LVGL_VERSION_MAJOR < 9)
lv_disp_drv_t * display_ssd1680_get_driver();
inline int display_get_rotation(lv_disp_drv_t * disp_drv) { return disp_drv->rotated; }
inline int display_get_width(lv_disp_t * disp) { return lv_disp_get_hor_res(disp); }
inline int display_get_height(lv_disp_t * disp) { return lv_disp_get_ver_res(disp); }
#else
#define display_get_rotation lv_display_get_rotation
inline int display_get_width(lv_disp_t * disp) { return lv_display_get_horizontal_resolution(disp); }
inline int display_get_height(lv_disp_t * disp) { return lv_display_get_vertical_resolution(disp); }
#endif
#endif

esp_lcd_panel_handle_t display_st7789_new();
void display_st7789_del();
bool lock_st7789(int timeout_ms);
void unlock_st7789();
void driver_st7789_bl_set(uint8_t brightness_percent);
esp_err_t driver_st7789_set_rotation(int r);

#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
lv_disp_drv_t * display_st7789_get_driver();
#endif
lv_disp_t * display_st7789_get();
#endif

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
#define LCD_H_GAP (6)
#define LCD_V_GAP (0)
#endif
#if defined(CONFIG_DISPLAY_DRIVER_SSD1681) || defined(CONFIG_DISPLAY_DRIVER_SSD1680)
#define display_new display_ssd168x_new
#define display_del display_ssd168x_del
#define display_epd_request_full_update display_epd_ssd168x_request_full_update
#define display_epd_request_fast_update display_epd_ssd168x_request_fast_update
#define display_set_rotation display_epd_ssd168x_set_rotation
#ifdef CONFIG_DISPLAY_USE_LVGL
// #define display_get_driver display_ssd1680_get_driver
#define display_get display_ssd1680_get
#endif
#define _lvgl_lock lock_ssd168x
#define _lvgl_unlock unlock_ssd168x
#endif
#if defined(CONFIG_DISPLAY_DRIVER_ST7789)
#define LCD_H_RES (320)               // horizontal
#define LCD_V_RES (170)               // vertical
#define LCD_H_GAP (0)
#define LCD_V_GAP (35)
#define display_new display_st7789_new
#define display_del display_st7789_del
#define display_epd_request_full_update(a) ((void)0)
#define display_epd_request_fast_update(a) ((void)0)
#define display_set_rotation(a) driver_st7789_set_rotation(a)
#ifdef CONFIG_DISPLAY_USE_LVGL
// #define display_get_driver display_st7789_get_driver
#define display_get display_st7789_get
#endif
#define _lvgl_lock lock_st7789
#define _lvgl_unlock unlock_st7789
#endif

#define LCD_RESOLUTION  (LCD_H_RES * LCD_V_RES)
#define LCD_ROW_LEN     (LCD_H_RES / 8)           // gates for x resolution
#define LCD_PIXELS      (LCD_V_RES * LCD_ROW_LEN) // total pixels

#define BYTE_PADDING(w) (((w + 7u) / 8 ) * 8) // Align to nearest 8 bits
#define LCD_PIXELS_MEM_ALIGNED (BYTE_PADDING(LCD_H_RES) * BYTE_PADDING(LCD_V_RES) / 8)

#define H_NORM_PX_VISIBLE(h_scr_percent) ((int16_t)((LCD_H_VISIBLE / 100.0) * (h_scr_percent)))
#define V_NORM_PX(v_scr_percent) ((int16_t)((LCD_V_RES / 100.0) * (v_scr_percent)))

#if defined(CONFIG_DISPLAY_DRIVER_ST7789)
#define LCD_BUF_SIZE (LCD_PIXELS/10)
#else
#define LCD_BUF_SIZE (LCD_PIXELS)
#endif

#define L_LVGL_TASK_MAX_DELAY_MS 50
#define L_LVGL_TASK_MIN_DELAY_MS 1

#ifdef __cplusplus
}
#endif


#endif /* EF04F767_437A_498D_8595_AE999C55B241 */
