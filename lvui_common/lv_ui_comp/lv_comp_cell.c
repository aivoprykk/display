#include "lv_comp_cell.h"
#include <core/lv_obj_class.h>
#include "driver_vendor.h"
#include "logger_common.h"
#include "ui_common.h"

#define MY_CLASS &lv_cell_class
static const char TAG[] = "lv_cell";
TIMER_INIT

lv_style_t style_cell;

static void lv_cell_constructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    TIMER_S
        
    LV_ASSERT_MALLOC(obj);
    if (obj == NULL)
        goto end;
    lv_obj_remove_style_all(obj);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    
    lv_obj_t *l;
    lv_cell_t *panel = (lv_cell_t *)obj;

    l = lv_label_create(obj);
    panel->title_label = l;
    lv_obj_set_size(l, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
    lv_obj_align(l, LV_ALIGN_CENTER, 0, LV_PCT(10));
    lv_label_set_text(l, "TEXT");

    l = lv_label_create(obj);
    panel->info_label = l;
    lv_obj_set_size(l, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
    lv_obj_align(l, LV_ALIGN_BOTTOM_LEFT, LV_PCT(83), LV_PCT(-9));
    lv_label_set_text(l, "TEXT");
    end:
    TIMER_E
}

static void lv_cell_destructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    LOGR

    lv_obj_clean(obj);
}

static void lv_cell_event(const lv_obj_class_t *class_p, lv_event_t *e) {
    ESP_LOGD(TAG, "lv_cell_event %d", e->code);
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

const lv_obj_class_t lv_cell_class = {
    .base_class = &lv_obj_class,
    .constructor_cb = lv_cell_constructor,
    .destructor_cb = lv_cell_destructor,
    .event_cb = lv_cell_event,
    .width_def = LV_PCT(100),
    .height_def = LV_PCT(100),
    .instance_size = sizeof(lv_cell_t)};

lv_obj_t *lv_cell_create(lv_obj_t *parent) {
    TIMER_S
    lv_obj_t *obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    LV_ASSERT_MALLOC(obj);
    TIMER_E
    return obj;
}

void lv_cell_set_title(lv_obj_t *obj, const char *title) {
    lv_cell_t *cell = (lv_cell_t *)obj;
    lv_label_set_text(cell->title_label, title);
}

void lv_cell_set_info(lv_obj_t *obj, const char *info) {
    lv_cell_t *cell = (lv_cell_t *)obj;
    lv_label_set_text(cell->info_label, info);
}

void lv_cell_set_text_styles(lv_obj_t *obj, const lv_style_t *style_title, const lv_style_t *style_info) {
    lv_cell_t *cell = (lv_cell_t *)obj;
    lv_obj_add_style(cell->title_label, (lv_style_ptr_t)style_title, 0);
    lv_obj_add_style(cell->info_label, (lv_style_ptr_t)style_info, 0);
}

void lv_cell_set_info_align(lv_obj_t *obj, lv_align_t align, lv_coord_t offset_x, lv_coord_t offset_y) {
    lv_cell_t *cell = (lv_cell_t *)obj;
    lv_obj_align(cell->info_label, align, offset_x, offset_y);
}

void lv_cell_set_title_x(lv_obj_t *obj, lv_coord_t offset_x) {
    lv_cell_t *cell = (lv_cell_t *)obj;
    lv_obj_set_x(cell->title_label, offset_x);
}

void lv_cell_set_data(lv_obj_t *obj, const char *title, const char *info) {
    lv_cell_t *cell = (lv_cell_t *)obj;
    lv_label_set_text(cell->title_label, title);
    lv_label_set_text(cell->info_label, info);
}