#ifndef C96ABE12_37F8_4845_AC1A_743C4914F1BB
#define C96ABE12_37F8_4845_AC1A_743C4914F1BB

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>
#include <stdint.h>

typedef void (*lv_stat_panel_cb_t)(int32_t);

typedef struct {
    lv_obj_t obj;

    lv_obj_t *row_panels[8];
    //lv_obj_t *statusbar;
} lv_stat_panel_t;

lv_obj_t *lv_stat_panel_create(lv_obj_t *parent, lv_coord_t width, lv_coord_t height);
void lv_stat_panel_setup_mode(lv_obj_t *obj, uint8_t mode);
// void lv_stat_panel_set_title(lv_obj_t *stat_panel, const char * title);
// void lv_stat_panel_set_info(lv_obj_t *stat_panel, const char * info);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* C96ABE12_37F8_4845_AC1A_743C4914F1BB */
