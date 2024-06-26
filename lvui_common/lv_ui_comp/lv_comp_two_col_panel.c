#include "lv_comp_two_col_panel.h"
#include "ui_common.h"
#include <core/lv_obj_class.h>
#include "logger_common.h"
#include "driver_vendor.h"
#include "esp_log.h"

#define MY_CLASS &lv_two_col_panel_class
static const char TAG[] = "lv_two_col_panel";
TIMER_INIT

static void lv_two_col_panel_constructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    TIMER_S
    LV_ASSERT_MALLOC(obj);
    if (obj == NULL) goto end;
    lv_two_col_panel_t *panel = (lv_two_col_panel_t *)obj;
    lv_obj_remove_style_all(obj);
    lv_obj_set_width(obj, LV_PCT(100));
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    // lv_obj_add_style(obj, (lv_style_ptr_t)&style_border_bottom, 0);
    
    panel->left_panel = lv_cell_create(obj);
    lv_obj_set_size(panel->left_panel, LV_PCT(50)-1, LV_PCT(100));
    lv_obj_align(panel->left_panel, LV_ALIGN_DEFAULT, 0, 0);
    // lv_obj_add_style(panel->left_panel, (lv_style_ptr_t)&style_border_right, 0);
    
    panel->right_panel = lv_cell_create(obj);
    lv_obj_set_size(panel->right_panel, LV_PCT(50)-1, LV_PCT(100));
    lv_obj_align(panel->right_panel, LV_ALIGN_DEFAULT, LV_PCT(50), 0);
    end:
    TIMER_E
}

static void lv_two_col_panel_destructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    lv_obj_clean(obj);
}

static void lv_two_col_panel_event(const lv_obj_class_t *class_p, lv_event_t *e) {
    ESP_LOGD(TAG, "lv_two_col_panel_event %d", e->code);
    switch(e->code) {
        case LV_EVENT_CHILD_CHANGED:
            ESP_LOGD(TAG, "LV_EVENT_CHILD_CHANGED");
            break;
        case LV_EVENT_SIZE_CHANGED:
            ESP_LOGD(TAG, "LV_EVENT_SIZE_CHANGED");
            break;
        case LV_EVENT_VALUE_CHANGED:
            ESP_LOGD(TAG, "LV_EVENT_VALUE_CHANGED");
            break;
        case LV_EVENT_STYLE_CHANGED:
            ESP_LOGD(TAG, "LV_EVENT_STYLE_CHANGED");
            break;
        case LV_EVENT_LAYOUT_CHANGED:
            ESP_LOGD(TAG, "LV_EVENT_LAYOUT_CHANGED");
            break;
        default:
            break;
    }
}

const lv_obj_class_t lv_two_col_panel_class = {.constructor_cb = lv_two_col_panel_constructor,
                                               .destructor_cb = lv_two_col_panel_destructor,
                                               .event_cb = lv_two_col_panel_event,
                                               .width_def = LV_PCT(100),
                                               .height_def = LV_PCT(100),
                                               .instance_size = sizeof(lv_two_col_panel_t),
                                               .base_class = &lv_obj_class};

lv_obj_t *lv_two_col_panel_create(lv_obj_t *parent) {
    LOGR

    lv_obj_t *obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    LV_ASSERT_MALLOC(obj);
    if (obj == NULL) return NULL;
    return obj;
}

void lv_two_col_panel_set_data(lv_obj_t *obj, const char *left_title, const char *left_info, const char *right_title, const char *right_info) {
    lv_two_col_panel_t *panel = (lv_two_col_panel_t *)obj;
    lv_cell_set_data(panel->left_panel, left_title, left_info);
    lv_cell_set_data(panel->right_panel, right_title, right_info);
}

void lv_two_col_panel_set_left_data(lv_obj_t *obj, const char *title, const char *info) {
    lv_two_col_panel_t *panel = (lv_two_col_panel_t *)obj;
    lv_cell_set_data(panel->left_panel, title, info);
}

void lv_two_col_panel_set_right_data(lv_obj_t *obj, const char *title, const char *info) {
    lv_two_col_panel_t *panel = (lv_two_col_panel_t *)obj;
    lv_cell_set_data(panel->right_panel, title, info);
}

void lv_two_col_panel_set_text_styles(lv_obj_t *obj, const lv_style_t *style_title, const lv_style_t *style_info) {
    lv_two_col_panel_t *panel = (lv_two_col_panel_t *)obj;
    lv_cell_set_text_styles(panel->left_panel, style_title, style_info);
    lv_cell_set_text_styles(panel->right_panel, style_title, style_info);
}

void lv_two_col_panel_set_info_align(lv_obj_t *obj, lv_align_t align, lv_coord_t offset_x, lv_coord_t offset_y) {
    lv_two_col_panel_t *panel = (lv_two_col_panel_t *)obj;
    lv_cell_set_info_align(panel->left_panel, align, offset_x, offset_y);
    lv_cell_set_info_align(panel->right_panel, align, offset_x, offset_y);
}

void lv_two_col_panel_set_title_x_offset(lv_obj_t *obj, lv_coord_t offset_x) {
    lv_two_col_panel_t *panel = (lv_two_col_panel_t *)obj;
    lv_cell_set_title_x(panel->left_panel, offset_x);
    lv_cell_set_title_x(panel->right_panel, offset_x);
}