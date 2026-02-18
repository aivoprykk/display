#ifndef D402B1F5_4E1C_4F2C_A033_FECC57E55A42
#define D402B1F5_4E1C_4F2C_A033_FECC57E55A42

#include "sdkconfig.h"

#if defined(CONFIG_DISPLAY_USE_LVGL)

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
#define DISPLAY_LVGL_IS_V8 1
typedef lv_disp_t display_lvgl_handle_t;
typedef lv_disp_drv_t display_lvgl_flush_ctx_t;
typedef lv_disp_draw_buf_t display_lvgl_draw_buf_t;
typedef lv_color_t display_lvgl_color_t;
#define LV_REFRESH_TIMER _lv_disp_refr_timer

static inline display_lvgl_handle_t *display_lvgl_get_default(void) {
    return lv_disp_get_default();
}

static inline void display_lvgl_flush_ready(void *ctx) {
    if (ctx) {
        lv_disp_flush_ready((lv_disp_drv_t *)ctx);
    }
}

static inline void *display_lvgl_get_user_data(void *ctx) {
    const lv_disp_drv_t *drv = (const lv_disp_drv_t *)ctx;
    return drv ? drv->user_data : NULL;
}

static inline bool display_lvgl_flush_is_last(void *ctx) {
    if(!ctx) return true;
    return lv_disp_flush_is_last((lv_disp_drv_t *)ctx);
}
#else
#define DISPLAY_LVGL_IS_V8 0
typedef lv_display_t display_lvgl_handle_t;
typedef lv_display_t display_lvgl_flush_ctx_t;
typedef lv_display_t display_lvgl_draw_buf_t;
typedef uint8_t display_lvgl_color_t;
#define LV_REFRESH_TIMER _lv_display_refr_timer

static inline display_lvgl_handle_t *display_lvgl_get_default(void) {
    return lv_display_get_default();
}

static inline void display_lvgl_flush_ready(void *ctx) {
    if (ctx) {
        lv_display_flush_ready((lv_display_t *)ctx);
    }
}

static inline void *display_lvgl_get_user_data(void *ctx) {
    lv_display_t *disp = (lv_display_t *)ctx;
    return disp ? lv_display_get_user_data(disp) : NULL;
}

static inline bool display_lvgl_flush_is_last(void *ctx) {
    if(!ctx) return true;
    return lv_display_flush_is_last((lv_display_t *)ctx);
}
#endif

#else  // CONFIG_DISPLAY_USE_LVGL

#define DISPLAY_LVGL_IS_V8 0
typedef void display_lvgl_handle_t;
typedef void display_lvgl_flush_ctx_t;
typedef void display_lvgl_draw_buf_t;

static inline display_lvgl_handle_t *display_lvgl_get_default(void) { return NULL; }
static inline void display_lvgl_flush_ready(void *ctx) { (void)ctx; }
static inline void *display_lvgl_get_user_data(void *ctx) { (void)ctx; return NULL; }

#endif // CONFIG_DISPLAY_USE_LVGL

#endif /* D402B1F5_4E1C_4F2C_A033_FECC57E55A42 */
