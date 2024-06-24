#ifndef A08B2B7F_0863_44B8_914C_1D6D1F6CB108
#define A08B2B7F_0863_44B8_914C_1D6D1F6CB108

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>
#include <stdint.h>

typedef void (*lv_cell_cb_t)(int32_t);

typedef struct {
    lv_obj_t obj;
    lv_obj_t *title_label;
    void(*title_cb)(const char*);
    lv_obj_t *info_label;
    void(*info_cb)(const char*);
} lv_cell_t;

lv_obj_t *lv_cell_create(lv_obj_t *parent);

void lv_cell_set_title(lv_obj_t *cell, const char * title);
void lv_cell_set_info(lv_obj_t *cell, const char * info);
void lv_cell_set_text_styles(lv_obj_t *cell, const lv_style_t * title_style, const lv_style_t * info_style);
void lv_cell_set_info_align(lv_obj_t *obj, lv_align_t align, lv_coord_t offset_x, lv_coord_t offset_y);
void lv_cell_set_title_x(lv_obj_t *obj, lv_coord_t offset_x);
void lv_cell_set_data(lv_obj_t *obj, const char *title, const char *info);

#ifdef __cplusplus
} /*extern "C"*/
#endif


#endif /* A08B2B7F_0863_44B8_914C_1D6D1F6CB108 */
