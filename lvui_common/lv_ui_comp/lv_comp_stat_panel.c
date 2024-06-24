#include "lv_comp_stat_panel.h"
#include <core/lv_obj_class.h>
#include "logger_common.h"
#include "lv_comp_cell.h"
#include "lv_comp_two_col_panel.h"
#include "ui_common.h"

static const char TAG[] = "lv_stat_panel";
#define MY_CLASS &lv_stat_panel_class
// TIMER_INIT
static void lv_stat_panel_constructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    LOGR
}

void lv_stat_panel_setup_mode(lv_obj_t *obj, uint8_t mode) {
    LOGR 
    
    lv_stat_panel_t *panel = (lv_stat_panel_t *)obj;
    int height = 0, start = 0;
    for (int i = 0; i < 8; i++) {
        if (!panel->row_panels[i])
            continue;
        switch (mode) {
            case 0:  // 3 cells 2 rows
                if (i > 1) {
                    lv_obj_add_flag(panel->row_panels[i], LV_OBJ_FLAG_HIDDEN);
                    continue;
                }
                lv_obj_clear_flag(panel->row_panels[i], LV_OBJ_FLAG_HIDDEN);
                if (i == 0) {
                    height = 65;
                    lv_obj_set_height(panel->row_panels[i], LV_PCT(height));
                    lv_obj_align(panel->row_panels[i], LV_ALIGN_DEFAULT, 0, start);
                    // lv_cell_set_text_styles(panel->row_panels[i], &style_text_morebigger, &style_text_normal);
                    lv_cell_set_info_align(panel->row_panels[i], LV_ALIGN_BOTTOM_LEFT, LV_PCT(1), LV_PCT(-9));
                    start += height;
                } else {
                    height = 100-65;
                    lv_obj_set_height(panel->row_panels[i], LV_PCT(height));
                    lv_obj_set_y(panel->row_panels[i], LV_PCT(start));
                    // lv_two_col_panel_set_text_styles(panel->row_panels[i], &style_text_bigger, &style_text_normal);
                    lv_two_col_panel_set_info_align(panel->row_panels[i], LV_ALIGN_LEFT_MID, 3, 1);
                    lv_two_col_panel_set_title_x_offset(panel->row_panels[i], LV_PCT(12));
                    start += height;
                }

                break;
            case 1:  // 5 cells 3 rows
                if (i > 2) {
                    lv_obj_add_flag(panel->row_panels[i], LV_OBJ_FLAG_HIDDEN);
                    continue;
                }
                lv_obj_clear_flag(panel->row_panels[i], LV_OBJ_FLAG_HIDDEN);
                if (i == 0) {
                    height = 40;
                    lv_obj_set_height(panel->row_panels[i], LV_PCT(height));
                    lv_obj_align(panel->row_panels[i], LV_ALIGN_DEFAULT, 0, start);
                    // lv_cell_set_text_styles(panel->row_panels[i], &style_text_bigger, &style_text_normal);
                    lv_cell_set_info_align(panel->row_panels[i], LV_ALIGN_BOTTOM_LEFT, LV_PCT(1), LV_PCT(-9));
                    start += height;
                } else {
                    height = (100-40) / 2;
                    lv_obj_set_height(panel->row_panels[i], LV_PCT(height));
                    lv_obj_set_y(panel->row_panels[i], LV_PCT(start));
                    // lv_two_col_panel_set_text_styles(panel->row_panels[i], &style_text_bigger, &style_text_normal);
                    lv_two_col_panel_set_info_align(panel->row_panels[i], LV_ALIGN_LEFT_MID, 3, 1);
                    lv_two_col_panel_set_title_x_offset(panel->row_panels[i], LV_PCT(12));
                    start += height;
                }
                break;
            case 2:  // 6 cells 3 rows
                if (i == 0 || i > 3) {
                    lv_obj_add_flag(panel->row_panels[i], LV_OBJ_FLAG_HIDDEN);
                    continue;
                }
                lv_obj_clear_flag(panel->row_panels[i], LV_OBJ_FLAG_HIDDEN);
                height = 100/3;
                lv_obj_set_height(panel->row_panels[i], LV_PCT(height));
                lv_obj_set_y(panel->row_panels[i], LV_PCT(start));
                // lv_two_col_panel_set_text_styles(panel->row_panels[i], &style_text_bigger, &style_text_normal);
                lv_two_col_panel_set_info_align(panel->row_panels[i], LV_ALIGN_LEFT_MID, 3, 1);
                lv_two_col_panel_set_title_x_offset(panel->row_panels[i], LV_PCT(12));
                start += height;

                break;
            case 3:  // 8 cells 4 rows
                if (i == 0 || i > 4) {
                    lv_obj_add_flag(panel->row_panels[i], LV_OBJ_FLAG_HIDDEN);
                    continue;
                }
                lv_obj_clear_flag(panel->row_panels[i], LV_OBJ_FLAG_HIDDEN);
                height = 100/4;
                lv_obj_set_height(panel->row_panels[i], LV_PCT(height));
                lv_obj_set_y(panel->row_panels[i], LV_PCT(start));
                // lv_two_col_panel_set_text_styles(panel->row_panels[i], &style_text_normal, &style_text_normal);
                lv_two_col_panel_set_info_align(panel->row_panels[i], LV_ALIGN_LEFT_MID, 3, 1);
                lv_two_col_panel_set_title_x_offset(panel->row_panels[i], LV_PCT(12));
                start += height;

                break;
            default:
                break;
        }
    }
}

static void lv_stat_panel_destructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    LOGR
        
    lv_obj_clean(obj);
}

static void lv_stat_panel_event(const lv_obj_class_t *class_p, lv_event_t *e) {
    ESP_LOGD(TAG, "lv_stat_panel_event %d", e->code);
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
        case LV_EVENT_REFRESH:
            ESP_LOGD(TAG, "LV_EVENT_REFRESH");
            break;
        default:
            break;
    }
}

const lv_obj_class_t lv_stat_panel_class = {.constructor_cb = lv_stat_panel_constructor,
                                            .destructor_cb = lv_stat_panel_destructor,
                                            .event_cb = lv_stat_panel_event,
                                            .width_def = LV_PCT(100),
                                            .height_def = LV_PCT(100),
                                            .instance_size = sizeof(lv_stat_panel_t),
                                            .base_class = &lv_obj_class};

lv_obj_t *lv_stat_panel_create(lv_obj_t *parent, lv_coord_t width, lv_coord_t height) {
    LOGR 
    
    lv_obj_t *obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    LV_ASSERT_MALLOC(obj);
    if (obj == NULL)
        return NULL;
    lv_stat_panel_t *panel = (lv_stat_panel_t *)obj;
    lv_obj_remove_style_all(obj);
    lv_obj_set_size(obj, width, height);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    //lv_obj_add_style(obj, (lv_style_ptr_t)&style_border_full, 0);
    
    for (int i = 0; i < 8; i++) {
        if (i == 0)
            panel->row_panels[i] = lv_cell_create(obj);
        else if (i < 5)
            panel->row_panels[i] = lv_two_col_panel_create(obj);
        else
            panel->row_panels[i] = NULL;
        if (panel->row_panels[i]) {
            lv_obj_clear_flag(panel->row_panels[i], LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_width(panel->row_panels[i], LV_PCT(100));
        }
    }
    lv_stat_panel_setup_mode(obj, 0);
    return obj;
}