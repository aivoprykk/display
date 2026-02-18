#ifndef C1BEE8A4_839A_4BFD_B010_B2F998E485F8
#define C1BEE8A4_839A_4BFD_B010_B2F998E485F8

#ifdef __cplusplus
extern "C" {
#endif

#include "driver_vendor.h"
#include "sdkconfig.h"
#include "lvgl_compat.h"
#if (defined(CONFIG_LOGGER_USE_GLOBAL_LOG_LEVEL) && CONFIG_LOGGER_GLOBAL_LOG_LEVEL < CONFIG_DISPLAY_LOG_LEVEL)
#define C_LOG_LEVEL CONFIG_LOGGER_GLOBAL_LOG_LEVEL
#else
#define C_LOG_LEVEL CONFIG_DISPLAY_LOG_LEVEL
#endif
#include "common_log.h"
#include <string.h>
#include "esp_lcd_panel_vendor.h"

// Optimized logging macros for performance-critical display code
#if (C_LOG_LEVEL <= LOG_DEBUG_NUM)
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

#if (C_LOG_LEVEL <= LOG_INFO_NUM)
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
    #define FLUSH_READY_CB(disp_drv) display_lvgl_flush_ready((disp_drv))
    #define DISPLAY_USER_DATA_T display_lvgl_flush_ctx_t
    #define GET_USER_DATA(cb_param) ((esp_lcd_panel_handle_t)display_lvgl_get_user_data((cb_param)))
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
    #define FLUSH_READY_CB(disp) display_lvgl_flush_ready((disp))
    #define DISPLAY_USER_DATA_T display_lvgl_flush_ctx_t
    #define GET_USER_DATA(cb_param) ((esp_lcd_panel_handle_t)display_lvgl_get_user_data((cb_param)))
#endif

#if defined(CONFIG_LCD_IS_EPD)
#define LVGL_TICK_PERIOD_MS 10UL
#define LV_DRAW_BUF_SZ 1 // 1 lvgl draw buf for epd
#define CONV_BUF_SZ 1 // only black
#if (LVGL_VERSION_MAJOR < 9)
#define LBUFSZ LCD_PIXELS_ALIGNED // size of the draw buffer(s) in bytes - for epd full screen pixels is needed
#else
// For LVGL v9 we can use 1 bit per pixel (packed) for EPDs
#define LBUFSZ LCD_PIXELS_MEM_ALIGNED
#endif
void display_handle_driver_error(void);
#else
#define LVGL_TICK_PERIOD_MS 2UL
#define LV_DRAW_BUF_SZ 2 // 2 lvgl draw buf for color display
#define CONV_BUF_SZ 0 // black and red
#define LBUFSZ LCD_BUF_SIZE // size of the draw buffer(s) in bytes
#endif

typedef struct display_driver_op_s {
    esp_lcd_panel_handle_t (*new)(void);
    void (*del)(void);
    esp_err_t (*set_rotation)(int r);
    void (*d_init)(void); 
#if defined(CONFIG_LCD_IS_EPD)
    esp_err_t (*epd_request_full_update)(void);
    esp_err_t (*epd_request_fast_update)(void);
    esp_err_t (*epd_request_partial_update)(void);
    esp_err_t (*epd_refresh_and_turn_off)(esp_lcd_panel_handle_t panel_handle, int rotated, m_area_t *area, uint8_t *color_map);
    // esp_err_t (*epd_turn_on)(esp_lcd_panel_handle_t panel_handle);
    esp_err_t (*epd_turn_off)(esp_lcd_panel_handle_t panel_handle);
    uint32_t (*epd_last_flush_ms)(void);
#else
    void (*bl_set)(uint8_t brightness_percent);
#endif
    uint32_t (*flush_count)(void);
} display_driver_op_t;

#if (CONFIG_SSD168X_PANEL_SSD1681) || (CONFIG_SSD168X_PANEL_SSD1680)
extern display_driver_op_t display_driver_ssd168x_op;
#endif
#if defined(CONFIG_DISPLAY_DRIVER_ST7789)
extern display_driver_op_t display_driver_st7789_op;
#endif

#if defined(CONFIG_DISPLAY_DRIVER_QEMU)
extern display_driver_op_t display_driver_qemu_op;
#endif

#if defined(CONFIG_DISPLAY_DRIVER_RM67162)
extern display_driver_op_t display_driver_rm67162_op;
#endif


typedef struct display_driver_s {
#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
    display_lvgl_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
    display_lvgl_flush_ctx_t disp_drv; // contains callback functions
#else
    lv_color_format_t color_format;      // active LVGL v9 color format
    lv_display_render_mode_t render_mode; // LVGL v9 render mode
    size_t render_buf_size;              // size passed to lv_display_set_buffers()
#endif
    uint8_t *lv_mem_buf[LV_DRAW_BUF_SZ + CONV_BUF_SZ];
    size_t lv_mem_buf_size[LV_DRAW_BUF_SZ + CONV_BUF_SZ];
    display_lvgl_handle_t *lv_disp;
    bool is_initialized_lvgl;
#else
    int rotated;
#endif
    SemaphoreHandle_t lock_mtx;
    SemaphoreHandle_t flush_sem;
    SemaphoreHandle_t flush_complete_sem;
    display_driver_op_t *op;
} display_driver_t;

extern display_driver_t drv;
uint32_t display_drv_get_flush_count();

esp_lcd_panel_handle_t display_drv_new();
void display_drv_del();
bool display_drv_lock(int timeout_ms);
void display_drv_unlock();
void display_drv_init();

#if defined(CONFIG_LCD_IS_EPD)
void display_drv_epd_reset_flush_requested();
bool display_drv_epd_get_flush_requested();
bool display_drv_epd_is_full_refresh_in_progress(void);
void display_drv_epd_signal_no_flush();
esp_err_t display_drv_epd_request_full_update();
esp_err_t display_drv_epd_request_fast_update();
esp_err_t display_drv_epd_request_partial_update();
void display_drv_epd_reset_flush_requested(void);
bool display_drv_epd_get_flush_requested(void);
uint32_t display_drv_epd_get_flush_request_count(void);
void display_drv_epd_signal_no_flush(void);
esp_err_t display_drv_epd_refresh_and_turn_off(esp_lcd_panel_handle_t panel_handle, int rotated, m_area_t *area, uint8_t *color_map);
// esp_err_t display_drv_epd_turn_on(esp_lcd_panel_handle_t panel_handle);
esp_err_t display_drv_epd_turn_off(esp_lcd_panel_handle_t panel_handle);
#else
void display_drv_bl_set(uint8_t brightness_percent);
#endif

#ifdef CONFIG_DISPLAY_USE_LVGL
int init_draw_buffers(size_t lvbuf, uint8_t lvbuf_num, size_t convbuf, uint8_t convbuf_num);
void init_lv_screen(void (*cb)(void *));
#endif

#ifdef __cplusplus
}
#endif

#endif /* C1BEE8A4_839A_4BFD_B010_B2F998E485F8 */
