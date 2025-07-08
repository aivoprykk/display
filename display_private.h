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
