#ifndef EFF49AF4_007D_4039_B7CF_5AAE1D5C21F2
#define EFF49AF4_007D_4039_B7CF_5AAE1D5C21F2

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>
#include <stdint.h>
#include "lv_comp_cell.h"

typedef void (*lv_two_col_panel_cb_t)(int32_t);

typedef struct {
    lv_obj_t obj;
    lv_obj_t *left_panel;
    lv_obj_t *right_panel;
} lv_two_col_panel_t;

lv_obj_t *lv_two_col_panel_create(lv_obj_t *parent);

void lv_two_col_panel_set_left_data(lv_obj_t *two_col_panel, const char * title, const char * info);
void lv_two_col_panel_set_right_data(lv_obj_t *two_col_panel, const char * title, const char * info);
void lv_two_col_panel_set_data(lv_obj_t *two_col_panel, const char * left_title, const char * left_info, const char * right_title, const char * right_info);
void lv_two_col_panel_set_text_styles(lv_obj_t *two_col_panel, const lv_style_t * left_style, const lv_style_t * right_style);
void lv_two_col_panel_set_info_align(lv_obj_t *obj, lv_align_t align, lv_coord_t offset_x, lv_coord_t offset_y);
void lv_two_col_panel_set_title_x_offset(lv_obj_t *obj, lv_coord_t offset_x);
#ifdef __cplusplus
} /*extern "C"*/
#endif


#endif /* EFF49AF4_007D_4039_B7CF_5AAE1D5C21F2 */
