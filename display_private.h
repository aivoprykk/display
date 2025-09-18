#ifndef C1BEE8A4_839A_4BFD_B010_B2F998E485F8
#define C1BEE8A4_839A_4BFD_B010_B2F998E485F8

#ifdef __cplusplus
extern "C" {
#endif

#include "driver_vendor.h"
#include "sdkconfig.h"
#if (defined(CONFIG_LOGGER_USE_GLOBAL_LOG_LEVEL) && CONFIG_LOGGER_GLOBAL_LOG_LEVEL < CONFIG_DISPLAY_LOG_LEVEL)
#define C_LOG_LEVEL CONFIG_LOGGER_GLOBAL_LOG_LEVEL
#else
#define C_LOG_LEVEL CONFIG_DISPLAY_LOG_LEVEL
#endif
#include "common_log.h"
#include <string.h>

// Optimized logging macros for performance-critical display code
#if (C_LOG_LEVEL < 1)
    #define DISPLAY_DLOG_SIMPLE(tag, msg) DLOG(tag, msg)
    #define DISPLAY_DLOG_1(tag, fmt, a) DLOG(tag, fmt, a) 
    #define DISPLAY_DLOG_2(tag, fmt, a, b) DLOG(tag, fmt, a, b)
    #define DISPLAY_DLOG_3(tag, fmt, a, b, c) DLOG(tag, fmt, a, b, c)
#else
    #define DISPLAY_DLOG_SIMPLE(tag, msg) do { } while(0)
    #define DISPLAY_DLOG_1(tag, fmt, a) do { } while(0)
    #define DISPLAY_DLOG_2(tag, fmt, a, b) do { } while(0) 
    #define DISPLAY_DLOG_3(tag, fmt, a, b, c) do { } while(0)
#endif

#if (C_LOG_LEVEL < 3)
    #define DISPLAY_ILOG_SIMPLE(tag, msg) ILOG(tag, msg)
    #define DISPLAY_ILOG_1(tag, fmt, a) ILOG(tag, fmt, a)
    #define DISPLAY_ILOG_2(tag, fmt, a, b) ILOG(tag, fmt, a, b)
    #define DISPLAY_ILOG_4(tag, fmt, a, b, c, d) ILOG(tag, fmt, a, b, c, d)
#else
    #define DISPLAY_ILOG_SIMPLE(tag, msg) do { } while(0)
    #define DISPLAY_ILOG_1(tag, fmt, a) do { } while(0)
    #define DISPLAY_ILOG_2(tag, fmt, a, b) do { } while(0)
    #define DISPLAY_ILOG_4(tag, fmt, a, b, c, d) do { } while(0)
#endif

// LVGL version compatibility macros to reduce runtime branching
#if (LVGL_VERSION_MAJOR < 9)
    #define LVGL_V8_MODE 1
    #define DISPLAY_GET_ROTATION() (drv.disp_drv.rotated)
    #define DISPLAY_SET_ROTATION(disp, r) do { \
        if(drv.disp_drv.rotated != (r)) { \
            drv.disp_drv.rotated = (r); \
            if(drv.lv_disp) lv_disp_drv_update(drv.lv_disp, &drv.disp_drv); \
        } \
    } while(0)
    #define DISPLAY_GET_HOR_RES() lv_disp_get_hor_res(drv.lv_disp)
    #define DISPLAY_GET_VER_RES() lv_disp_get_ver_res(drv.lv_disp)
    #define FLUSH_READY_CB(disp_drv) lv_disp_flush_ready((lv_disp_drv_t*)(disp_drv))
    #define DISPLAY_USER_DATA_T lv_disp_drv_t
    #define GET_USER_DATA(cb_param) ((esp_lcd_panel_handle_t)((lv_disp_drv_t*)(cb_param))->user_data)
#else
    #define LVGL_V8_MODE 0
    #define DISPLAY_GET_ROTATION() lv_display_get_rotation(drv.lv_disp)
    #define DISPLAY_SET_ROTATION(disp, r) do { \
        if((r) != lv_display_get_rotation(drv.lv_disp)) { \
            lv_display_set_rotation(drv.lv_disp, (r)); \
        } \
    } while(0)
    #define DISPLAY_GET_HOR_RES() lv_display_get_horizontal_resolution(drv.lv_disp)
    #define DISPLAY_GET_VER_RES() lv_display_get_vertical_resolution(drv.lv_disp)
    #define FLUSH_READY_CB(disp) lv_display_flush_ready((lv_display_t*)(disp))
    #define DISPLAY_USER_DATA_T lv_display_t
    #define GET_USER_DATA(cb_param) ((esp_lcd_panel_handle_t)lv_display_get_user_data((lv_display_t*)(cb_param)))
#endif

#if defined(CONFIG_LCD_IS_EPD)
#define LVGL_TICK_PERIOD_MS 10UL
#define LV_DRAW_BUF_SZ 1 // 1 lvgl draw buf for epd
#define CONV_BUF_SZ 1 // only black
#define LBUFSZ LCD_PIXELS_ALIGNED // size of the draw buffer(s) in bytes
#else
#define LVGL_TICK_PERIOD_MS 2UL
#define LV_DRAW_BUF_SZ 2 // 2 lvgl draw buf for color display
#define CONV_BUF_SZ 0 // black and red
#define LBUFSZ LCD_BUF_SIZE // size of the draw buffer(s) in bytes
#endif

typedef struct display_driver_s {
#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
    lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
    lv_disp_drv_t disp_drv;      // contains callback functions
#else
    #define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_I1)) /*will be 2 for RGB565 */
#endif
    uint8_t *lv_mem_buf[LV_DRAW_BUF_SZ + CONV_BUF_SZ];
    lv_disp_t *lv_disp;
    bool is_initialized_lvgl;
#else
    int rotated;
#endif
    SemaphoreHandle_t sem;
    display_driver_op_t *op;
} display_driver_t;

extern display_driver_t drv;
uint32_t display_drv_epd_get_flush_count();

#ifdef CONFIG_DISPLAY_USE_LVGL
int init_draw_buffers(size_t lvbuf, uint8_t lvbuf_num, size_t convbuf, uint8_t convbuf_num);
void init_lv_screen(void (*cb)(void *));
#endif

#ifdef __cplusplus
}
#endif

#endif /* C1BEE8A4_839A_4BFD_B010_B2F998E485F8 */
