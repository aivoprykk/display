#include "lv_comp_statusbar.h"
#include "ui_common.h"

#include <core/lv_obj_class.h>
// #include "driver_vendor.h"
// #include "esp_heap_task_info.h"
#include "esp_log.h"
#include "logger_common.h"
#include "lvgl.h"

#define MY_CLASS &lv_statusbar_class

const static char *TAG = "lv_comp_statusbar";
static void lv_statusbar_destructor(const lv_obj_class_t *class_p, lv_obj_t *obj);
static void lv_statusbar_constructor(const lv_obj_class_t *class_p, lv_obj_t *obj);
static void lv_statusbar_event(const lv_obj_class_t *class_p, lv_event_t *e);

const lv_obj_class_t lv_statusbar_class = {
    .constructor_cb = lv_statusbar_constructor,
    .event_cb = lv_statusbar_event,
    .destructor_cb = lv_statusbar_destructor,
    .width_def = LV_PCT(100),
    .height_def = LV_PCT(100),
    .instance_size = sizeof(lv_statusbar_t),
    .base_class = &lv_obj_class};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t *lv_statusbar_create(lv_obj_t *parent) {
    LOGR
    lv_obj_t * obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

/**********************
 *   setters
 **********************/

void lv_statusbar_set_time(lv_obj_t *obj, const char *time) {
    lv_statusbar_t *panel = (lv_statusbar_t *)obj;
    lv_label_set_text(panel->time_label, time);
}

void lv_statusbar_set_temp(lv_obj_t *obj, const char *temp) {
    lv_statusbar_t *panel = (lv_statusbar_t *)obj;
    lv_label_set_text(panel->temp_label, temp);
}

void lv_statusbar_toggle_gps(lv_obj_t *obj, bool gps) {
    lv_statusbar_t *panel = (lv_statusbar_t *)obj;
    if (gps) {
        if(lv_obj_has_flag(panel->gps_image, LV_OBJ_FLAG_HIDDEN))
            lv_obj_clear_flag(panel->gps_image, LV_OBJ_FLAG_HIDDEN);
    } else {
        if(!lv_obj_has_flag(panel->gps_image, LV_OBJ_FLAG_HIDDEN))
            lv_obj_add_flag(panel->gps_image, LV_OBJ_FLAG_HIDDEN);
    }
}

void lv_statusbar_toggle_sdcard(lv_obj_t *obj, bool sdcard) {
    lv_statusbar_t *panel = (lv_statusbar_t *)obj;
    if (sdcard) {
        if(lv_obj_has_flag(panel->sdcard_image, LV_OBJ_FLAG_HIDDEN))
            lv_obj_clear_flag(panel->sdcard_image, LV_OBJ_FLAG_HIDDEN);
    } else {
        if(!lv_obj_has_flag(panel->sdcard_image, LV_OBJ_FLAG_HIDDEN))
            lv_obj_add_flag(panel->sdcard_image, LV_OBJ_FLAG_HIDDEN);
    }
}

void lv_statusbar_toggle_bat_image(lv_obj_t *obj, bool charging) {
    lv_statusbar_t *panel = (lv_statusbar_t *)obj;
    if (charging) {
        if(lv_obj_has_flag(panel->bat_image, LV_OBJ_FLAG_HIDDEN))
            lv_label_set_text(panel->bat_image, LV_SYMBOL_CHARGE);
    } else {
        if(!lv_obj_has_flag(panel->bat_image, LV_OBJ_FLAG_HIDDEN))
            lv_label_set_text(panel->bat_image, LV_SYMBOL_USB);
    }
}

void lv_statusbar_set_bat(lv_obj_t *obj, const char *bat) {
    lv_statusbar_t *panel = (lv_statusbar_t *)obj;
    lv_label_set_text(panel->bat_label, bat);
}

void lv_statusbar_set_mode(lv_obj_t *obj, uint8_t mode) {
    LOGR
    lv_statusbar_t *panel = (lv_statusbar_t *)obj;
    if(panel->viewmode == mode) return;
    else panel->viewmode = mode;
    if(mode==0) {
        if(lv_obj_has_flag(panel->bat_image, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_clear_flag(panel->bat_image, LV_OBJ_FLAG_HIDDEN);
        }
        if(lv_obj_has_flag(panel->sdcard_image, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_clear_flag(panel->sdcard_image, LV_OBJ_FLAG_HIDDEN);
        }
        if(lv_obj_has_flag(panel->temp_label, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_clear_flag(panel->temp_label, LV_OBJ_FLAG_HIDDEN);
        }
    }
    else {
        if(!lv_obj_has_flag(panel->bat_image, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_add_flag(panel->bat_image, LV_OBJ_FLAG_HIDDEN);
        }
        if(!lv_obj_has_flag(panel->sdcard_image, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_add_flag(panel->sdcard_image, LV_OBJ_FLAG_HIDDEN);
        }
        if(!lv_obj_has_flag(panel->temp_label, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_add_flag(panel->temp_label, LV_OBJ_FLAG_HIDDEN);
        }
    }
    if(mode == 1) {
        if(!lv_obj_has_flag(panel->gps_image, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_add_flag(panel->gps_image, LV_OBJ_FLAG_HIDDEN);
        }
    }
    else {
        if(lv_obj_has_flag(panel->gps_image, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_clear_flag(panel->gps_image, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

// static void label_event_cb(lv_event_t * e) {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * label = lv_event_get_target(e);
//     if(!lv_obj_has_flag(label, LV_OBJ_FLAG_HIDDEN)) return;
//     if(code == LV_EVENT_STYLE_CHANGED || code == LV_EVENT_SIZE_CHANGED) {
//         // lv_label_set_text(label, NULL);
//     }
// }

static void lv_statusbar_constructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    LOGR
    LV_ASSERT_MALLOC(obj);
    if (obj == NULL)
        return;
    
    lv_statusbar_t *panel = (lv_statusbar_t *)obj;
    panel->viewmode = 0;
    // memset(panel, 0, sizeof(lv_statusbar_t));

    lv_obj_t *p;

    lv_obj_remove_style_all(obj);
    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
    lv_obj_align(obj, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);     /// Flags
    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    panel->time_label = lv_label_create(obj);
    lv_obj_set_size(panel->time_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
    lv_obj_align(panel->time_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_label_set_text(panel->time_label, "00:00");
    // lv_obj_add_event_cb(panel->time_label, label_event_cb, LV_EVENT_ALL, NULL);

    panel->temp_label = lv_label_create(obj);
    lv_obj_set_size(panel->temp_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
    lv_obj_align(panel->temp_label, LV_ALIGN_RIGHT_MID, lv_pct(-48), 0);
    lv_label_set_text(panel->temp_label, "11.0C");
    // lv_obj_add_event_cb(panel->temp_label, label_event_cb, LV_EVENT_ALL, NULL);

    p = lv_obj_create(obj);
    lv_obj_remove_style_all(p);
    panel->right_panel = p;
    lv_obj_set_size(p, LV_PCT(48), LV_PCT(100));
    lv_obj_align(p, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_radius(p, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(p, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(p, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(p, LV_OBJ_FLAG_SCROLLABLE);  /// Flags

    panel->gps_image = lv_label_create(p);
    lv_obj_set_size(panel->gps_image, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
    lv_obj_align(panel->gps_image, LV_ALIGN_RIGHT_MID, lv_pct(-30), 0);
    lv_label_set_text(panel->gps_image, LV_SYMBOL_GPS);
    lv_obj_set_style_text_font(panel->gps_image, LV_FONT_DEFAULT, 0);
    lv_obj_set_style_pad_right(panel->gps_image, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(panel->gps_image, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_add_event_cb(panel->gps_image, label_event_cb, LV_EVENT_ALL, NULL);

    panel->sdcard_image = lv_label_create(p);
    lv_obj_set_size(panel->sdcard_image, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
    lv_obj_align(panel->sdcard_image, LV_ALIGN_RIGHT_MID, lv_pct(-20), 0);
    lv_label_set_text(panel->sdcard_image, LV_SYMBOL_SD_CARD);
    lv_obj_set_style_text_font(panel->sdcard_image, LV_FONT_DEFAULT, 0);
    lv_obj_set_style_pad_right(panel->sdcard_image, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(panel->sdcard_image, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_add_event_cb(panel->sdcard_image, label_event_cb, LV_EVENT_ALL, NULL);

    panel->bat_image = lv_label_create(p);
    lv_obj_set_size(panel->bat_image, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
    lv_obj_align(panel->bat_image, LV_ALIGN_RIGHT_MID, lv_pct(-10), 0);
    lv_label_set_text(panel->bat_image, LV_SYMBOL_BATTERY_FULL);
    lv_obj_set_style_text_font(panel->bat_image, LV_FONT_DEFAULT, 0);
    lv_obj_set_style_pad_right(panel->bat_image, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(panel->bat_image, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_add_event_cb(panel->bat_image, label_event_cb, LV_EVENT_ALL, NULL);

    panel->bat_label = lv_label_create(p);
    lv_obj_set_size(panel->bat_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
    lv_obj_align(panel->bat_label, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_label_set_text(panel->bat_label, "100%");
    // lv_obj_add_event_cb(panel->bat_label, label_event_cb, LV_EVENT_ALL, NULL);

    // return obj;
}

static void lv_statusbar_destructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    LOGR
}

static void lv_statusbar_event(const lv_obj_class_t *class_p, lv_event_t *e) {
    LOGR
    switch (e->code) {
        case LV_EVENT_STYLE_CHANGED:
            ESP_LOGD(TAG, "LV_EVENT_STYLE_CHANGED");
            break;
        case LV_EVENT_CHILD_CHANGED:
            ESP_LOGD(TAG, "LV_EVENT_CHILD_CHANGED");
            break;
        case LV_EVENT_SIZE_CHANGED:
            ESP_LOGD(TAG, "LV_EVENT_SIZE_CHANGED");
            break;
        case LV_EVENT_VALUE_CHANGED:
            ESP_LOGD(TAG, "LV_EVENT_VALUE_CHANGED");
            break;
        case LV_EVENT_LAYOUT_CHANGED:
            ESP_LOGD(TAG, "LV_EVENT_LAYOUT_CHANGED");
            break;
        default:
            break;
    }
}

#undef MY_CLASS
