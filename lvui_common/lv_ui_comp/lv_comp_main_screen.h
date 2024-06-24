#ifndef ABB61C90_84A5_4C62_A248_76D02A98E10F
#define ABB61C90_84A5_4C62_A248_76D02A98E10F

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>
#include <stdint.h>

typedef void (*lv_main_screen_cb_t)(int32_t);

typedef struct {
    lv_obj_t obj;
    lv_obj_t *statusbar;
    lv_obj_t *panel_info;
    lv_obj_t *panel_stat;
    lv_obj_t *panel_speed;
} lv_main_screen_t;

typedef enum {
    LV_MAIN_SCREEN_MODE_NONE = 0,
    LV_MAIN_SCREEN_PANEL_BOOT,
    LV_MAIN_SCREEN_PANEL_INFO,
    LV_MAIN_SCREEN_PANEL_STAT,
    LV_MAIN_SCREEN_PANEL_SPEED,
} lv_main_screen_panel_type_t;

lv_obj_t *lv_main_screen_create(lv_obj_t *parent, lv_coord_t width, lv_coord_t height);
void lv_main_screen_show_panel(lv_obj_t *obj, lv_main_screen_panel_type_t panel_type);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* ABB61C90_84A5_4C62_A248_76D02A98E10F */
