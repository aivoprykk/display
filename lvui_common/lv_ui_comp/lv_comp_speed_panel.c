#include "lv_comp_speed_panel.h"
#include "ui_common.h"
#include <core/lv_obj_class.h>
#include "lv_comp_cell.h"
#include "lv_comp_two_col_panel.h"
#include "logger_common.h"
#include "esp_log.h"

//LV_FONT_DECLARE(ui_font_OswaldRegular120p2);

#define MY_CLASS &lv_speed_panel_class
static const char TAG[] = "lv_speed_panel";
TIMER_INIT
static void lv_speed_panel_constructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    TIMER_S
    LV_ASSERT_MALLOC(obj);
    if (obj == NULL) goto end;
    lv_obj_remove_style_all(obj);
    lv_obj_align(obj, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    
    lv_obj_t * p;
    lv_speed_panel_t *panel = (lv_speed_panel_t *)obj;
    
    p = lv_two_col_panel_create(obj);
    panel->secondary_panel = p;
    lv_obj_set_size(p, LV_PCT(100), LV_PCT(33));
    lv_obj_align(p, LV_ALIGN_DEFAULT, 0, 0);
    // lv_two_col_panel_set_text_styles(p, &style_text_bigger, &style_text_small);
    lv_two_col_panel_set_info_align(p, LV_ALIGN_LEFT_MID, 3, 1);
    lv_two_col_panel_set_title_x_offset(p, LV_PCT(12));
    
    p = lv_cell_create(obj);
    panel->main_panel = p;
    lv_obj_set_size(p, LV_PCT(100), LV_PCT(64));
    lv_obj_align(p, LV_ALIGN_DEFAULT, 0, LV_PCT(34));
    // lv_cell_set_text_styles(p, &style_text_biggest, &style_text_small);

    p = lv_bar_create(obj);
    panel->speed_bar = p;
    lv_obj_set_size(p, LV_PCT(100), 5);
    lv_obj_set_pos(p, 0, LV_PCT(33));
    // lv_obj_add_style(p, &style_plain_container, 0);
    lv_bar_set_value(p, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(p, 0, LV_ANIM_OFF);
    lv_obj_set_style_radius(p, 0, LV_PART_INDICATOR| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(p, lv_color_black(), LV_PART_INDICATOR| LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_opa(p, LV_OPA_100, LV_PART_INDICATOR| LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(p, 0, LV_PART_INDICATOR| LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(p, LV_BORDER_SIDE_NONE, LV_PART_INDICATOR| LV_STATE_DEFAULT);
    end:
    TIMER_E
}

static void lv_speed_panel_destructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    LOGR
    lv_obj_clean(obj);
}

static void lv_speed_panel_event(const lv_obj_class_t *class_p, lv_event_t *e) {
    ESP_LOGD(TAG, "lv_speed_panel_event %d", e->code);
    switch (e->code) {
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

const lv_obj_class_t lv_speed_panel_class = {.constructor_cb = lv_speed_panel_constructor,
                                       .destructor_cb = lv_speed_panel_destructor,
                                       .event_cb = lv_speed_panel_event,
                                       .width_def = LV_PCT(100),
                                       .height_def = LV_PCT(100),
                                       .instance_size = sizeof(lv_speed_panel_t),
                                       .base_class = &lv_obj_class};

lv_obj_t *lv_speed_panel_create(lv_obj_t *parent) {
    lv_obj_t *obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    LV_ASSERT_MALLOC(obj);
    return obj;
}