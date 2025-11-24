#ifndef D1A942CD_8799_44BA_919D_944D3E28E376
#define D1A942CD_8799_44BA_919D_944D3E28E376

#ifdef __cplusplus
extern "C" {
#endif

#include "sdkconfig.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "freertos/FreeRTOS.h"

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

#include "driver_vendor.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_ssd168x.h"
#include "display.h"


void example_lvgl_demo_ui(lv_disp_t *disp);
void ui_demo(void);
void ui_init(void);
void ui_deinit(void);
uint32_t screen_cb(void* arg);
void print_lv_mem_mon();

#ifdef __cplusplus
}
#endif

#endif /* D1A942CD_8799_44BA_919D_944D3E28E376 */
