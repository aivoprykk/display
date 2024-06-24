#ifndef BA5832DF_0201_4E33_8F90_E1B927DA2D2B
#define BA5832DF_0201_4E33_8F90_E1B927DA2D2B

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>
#include <stdint.h>

typedef void (*lv_info_panel_cb_t)(int32_t);

typedef struct {
    lv_obj_t obj;

    lv_obj_t *title_image;
    lv_obj_t *title_label;
    lv_obj_t *info_label;

} lv_info_panel_t;

lv_obj_t *lv_info_panel_create(lv_obj_t *parent, lv_coord_t width, lv_coord_t height);
void lv_info_panel_setup_mode(lv_obj_t *obj, uint8_t mode);

void lv_info_panel_set_title(lv_obj_t *info_panel, const char * title);
void lv_info_panel_set_info(lv_obj_t *info_panel, const char * secondary);
void lv_info_panel_set_image(lv_obj_t *info_panel, const void * img_src);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* BA5832DF_0201_4E33_8F90_E1B927DA2D2B */
