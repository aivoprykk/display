#ifndef EF04F767_437A_498D_8595_AE999C55B241
#define EF04F767_437A_498D_8595_AE999C55B241

#ifdef __cplusplus
extern "C" {
#endif

#include "sdkconfig.h"
#if defined(CONFIG_DISPLAY_ENABLED)

#if defined(CONFIG_DISPLAY_DRIVER_ST7789) || defined(CONFIG_DISPLAY_DRIVER_QEMU)
#undef CONFIG_SSD168X_PANEL_SSD1681
#undef CONFIG_SSD168X_PANEL_SSD1680
#endif

#include <stdbool.h>
#include <stdint.h>

#include "logger_common.h"

#ifdef CONFIG_DISPLAY_USE_LVGL
#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif
#if (LVGL_VERSION_MAJOR < 9)
#define lv_display_t lv_disp_t
#define lv_image_dsc_t lv_img_dsc_t
#endif
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

#if defined(CONFIG_DISPLAY_DRIVER_ST7789)
#define LCD_H_RES (320)               // horizontal
#define LCD_V_RES (170)               // vertical
#define LCD_H_GAP (0)
#define LCD_V_GAP (35)
#endif

#if defined(CONFIG_DISPLAY_DRIVER_QEMU)
#define LCD_H_RES (320)               // horizontal
#define LCD_V_RES (170)               // vertical
#define LCD_H_GAP (0)
#define LCD_V_GAP (0)
#endif

#if defined(CONFIG_DISPLAY_DRIVER_RM67162)
#define LCD_H_RES (536)               // horizontal
#define LCD_V_RES (240)               // vertical
#define LCD_H_GAP (0)
#define LCD_V_GAP (0)
#endif

#if defined(CONFIG_SSD168X_PANEL_SSD1681)
#define LCD_H_RES (200)               // horizontal
#define LCD_V_RES (200)               // vertical
#define LCD_H_GAP (0)
#define LCD_V_GAP (0)
#endif

#if defined(CONFIG_SSD168X_PANEL_SSD1680)
#define LCD_H_RES (128)               // horizontal
#define LCD_V_RES (250)               // vertical
#define LCD_H_GAP (6)
#define LCD_V_GAP (0)
#endif

#define LCD_H_VISIBLE (LCD_H_RES-LCD_H_GAP)           // vertical
#define LCD_V_VISIBLE (LCD_V_RES-LCD_V_GAP)           // horizontal

#define LCD_RESOLUTION  (LCD_H_RES * LCD_V_RES)
#if ((CONFIG_DISPLAY_DRIVER_ST7789) || (CONFIG_DISPLAY_DRIVER_QEMU))
#define LCD_PIXELS      (LCD_RESOLUTION)
#else
#define LCD_ROW_LEN     (LCD_H_RES / 8)           // gates for x resolution
#define LCD_PIXELS      (LCD_V_RES * LCD_ROW_LEN) // total pixels
#endif

#define LCD_PIXELS_ALIGNED (ROUND_UP_TO_8(LCD_H_RES) * ROUND_UP_TO_8(LCD_V_RES))
#define LCD_PIXELS_MEM_ALIGNED (LCD_PIXELS_ALIGNED / 8)

#define H_NORM_PX_VISIBLE(h_scr_percent) ((int16_t)((LCD_H_VISIBLE / 100.0) * (h_scr_percent)))
#define V_NORM_PX(v_scr_percent) ((int16_t)((LCD_V_RES / 100.0) * (v_scr_percent)))

#if ((CONFIG_DISPLAY_DRIVER_ST7789) || (CONFIG_DISPLAY_DRIVER_QEMU))
#define LCD_BUF_SIZE (LCD_H_RES * LCD_V_RES / 10)
#else
#if defined(CONFIG_DISPLAY_DRIVER_RM67162)
#if (CONFIG_DISPLAY_USE_LVGL && LVGFL_VERSION_MAJOR > 8)
#define SEND_BUF_SIZE ((LCD_H_RES * LCD_V_RES  * LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) / 10)
#else
#define SEND_BUF_SIZE (LCD_H_RES * LCD_V_RES / 10)
#endif
#else
#define LCD_BUF_SIZE (LCD_PIXELS)
#endif
#endif


#define L_LVGL_TASK_MAX_DELAY_MS 50
#define L_LVGL_TASK_MIN_DELAY_MS 1

#endif

#ifdef CONFIG_DISPLAY_USE_LVGL
int display_drv_get_width();
int display_drv_get_height();
#endif

int display_drv_set_rotation(int r);
int display_drv_get_rotation(void);

#ifdef __cplusplus
}
#endif


#endif /* EF04F767_437A_498D_8595_AE999C55B241 */
