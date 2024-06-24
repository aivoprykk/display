#ifndef F8554E9A_14D4_41A9_8197_57EEC4319BFC
#define F8554E9A_14D4_41A9_8197_57EEC4319BFC

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>
#include <stdint.h>

typedef void (*lv_statusbar_cb_t)(int32_t);

typedef struct {
    lv_obj_t obj;
    lv_obj_t *left_panel;
    lv_obj_t *time_label;
    lv_obj_t *right_panel;
    lv_obj_t *temp_label;
    lv_obj_t *gps_image;
    lv_obj_t *sdcard_image;
    lv_obj_t *bat_image;
    lv_obj_t *bat_label;
    uint8_t viewmode;
} lv_statusbar_t;

lv_obj_t *lv_statusbar_create(lv_obj_t *parent);

void lv_statusbar_set_time(lv_obj_t *obj, const char * time);
void lv_statusbar_set_temp(lv_obj_t *obj, const char * temp);
void lv_statusbar_set_gps(lv_obj_t *obj, bool gps);
void lv_statusbar_set_sdcard(lv_obj_t *obj, bool sdcard);
void lv_statusbar_set_bat(lv_obj_t *obj, const char * bat);
void lv_statusbar_set_bat_image(lv_obj_t *obj, bool charging);
void lv_statusbar_set_mode(lv_obj_t *obj, uint8_t mode);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* F8554E9A_14D4_41A9_8197_57EEC4319BFC */
