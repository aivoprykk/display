#include "lv_comp_main_screen.h"
#include <core/lv_obj_class.h>
#include "driver_vendor.h"
#include "logger_common.h"
#include "ui_common.h"
#include "esp_log.h"

#include "lv_comp_info_panel.h"
#include "lv_comp_main_screen.h"
#include "lv_comp_speed_panel.h"
#include "lv_comp_stat_panel.h"
#include "lv_comp_statusbar.h"

// LV_FONT_DECLARE(ui_font_OswaldRegular84p2);
TIMER_INIT
#define MY_CLASS &lv_main_screen_class
static const char TAG[] = "lv_main_screen";
static lv_main_screen_panel_type_t active_panel = 0;
static void lv_main_screen_event(const lv_obj_class_t *class_p, lv_event_t *e) {
    ESP_LOGD(TAG, "lv_main_screen_event %d", e->code);
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

static lv_obj_t *panels[4] = {0};

const lv_obj_class_t lv_main_screen_class = {
    .event_cb = lv_main_screen_event,
    .base_class = &lv_obj_class,
    .width_def = LV_PCT(100),
    .height_def = LV_PCT(100)-4,
    .instance_size = sizeof(lv_main_screen_t)};

lv_obj_t *lv_main_screen_create(lv_obj_t *parent, lv_coord_t width, lv_coord_t height) {
    TIMER_S
    ESP_LOGI(TAG, "lv_main_screen_create %d x %d", width, height);
    lv_obj_t *obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    LV_ASSERT_MALLOC(obj);
    if (obj == NULL)
        goto end;

    lv_main_screen_t *panel = (lv_main_screen_t *)obj;

    lv_obj_remove_style_all(obj);
    lv_obj_set_size(obj, width, height);
    lv_obj_set_align(obj, LV_ALIGN_TOP_LEFT);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    
    lv_obj_t *p;
    for (int i = 0; i < 4; i++) {
        p = lv_obj_create(obj);
        lv_obj_remove_style_all(obj);
        lv_obj_clear_flag(p, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
        lv_obj_set_width(p, LV_PCT(100));
        if (i > 0) {
            //lv_obj_set_pos(p, 0, 0);
            lv_obj_set_align(p, LV_ALIGN_CENTER);
        }
        panels[i] = p;
        if (i == 0) {
            lv_obj_set_pos(p, 0, -4);
            lv_obj_set_align(p, LV_ALIGN_BOTTOM_LEFT);
            lv_obj_set_height(p, LV_PCT(20));
            panel->statusbar = lv_statusbar_create(p);
            p = panel->statusbar;
            // lv_obj_add_style(p, &style_statusbar, 0);
        } else if (i == 1) {
            lv_obj_set_height(p, LV_PCT(100) - 4);
            panel->panel_info = lv_info_panel_create(p, lv_obj_get_width(p), lv_obj_get_height(p));
            p = panel->panel_info;
        } else if (i == 2) {
            lv_obj_set_height(p, LV_PCT(80) - 1);
            panel->panel_stat = lv_stat_panel_create(p, lv_obj_get_width(p), lv_obj_get_height(p));
            p = panel->panel_stat;
            lv_obj_set_pos(p, 0, 0);
        } else if (i == 3) {
            lv_obj_set_height(p, LV_PCT(100) - 4);
           panel->panel_speed = lv_speed_panel_create(p);
            p = panel->panel_speed;
            lv_obj_set_pos(p, 0, 0);
        }
        lv_obj_set_align(p, LV_ALIGN_TOP_LEFT);
        lv_obj_set_size(p, LV_PCT(100), LV_PCT(100));
        if (i > 1)
            lv_obj_add_flag(p, LV_OBJ_FLAG_HIDDEN);
    }
    end:
    TIMER_E
    return obj;
}

void lv_main_screen_show_panel(lv_obj_t *obj, lv_main_screen_panel_type_t panel_type) {
    ESP_LOGD(TAG, "lv_main_screen_show_panel %d", panel_type);
    lv_main_screen_t *screen = (lv_main_screen_t *)obj;
    if (active_panel == panel_type)
        return;
    for (int i = 1; i < 4; i++) {
        if (panels[i] == 0)
            continue;
        switch (panel_type) {
            case LV_MAIN_SCREEN_PANEL_BOOT:
                if (i == 1) {
                    ESP_LOGI(TAG, "LV_MAIN_SCREEN_PANEL_BOOT");
                    lv_obj_set_height(panels[i], LV_PCT(100) - 4);
                    lv_obj_clear_flag(panels[i], LV_OBJ_FLAG_HIDDEN);
                    lv_obj_add_flag(panels[0], LV_OBJ_FLAG_HIDDEN);
                    lv_info_panel_setup_mode(screen->panel_info, 0);
                    active_panel = panel_type;
                    lv_obj_invalidate(panels[i]);
                    continue;
                }
                break;
            case LV_MAIN_SCREEN_PANEL_INFO:
                if (i == 1) {
                    ESP_LOGI(TAG, "LV_MAIN_SCREEN_PANEL_INFO");
                    lv_obj_set_height(panels[i], LV_PCT(80) - 1);
                    lv_obj_clear_flag(screen->panel_info, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(panels[0], LV_OBJ_FLAG_HIDDEN);
                    lv_info_panel_setup_mode(screen->panel_info, 1);
                    active_panel = panel_type;
                    lv_obj_invalidate(panels[i]);
                    continue;
                }
                break;
            case LV_MAIN_SCREEN_PANEL_STAT:
                if (i == 2) {
                    ESP_LOGI(TAG, "LV_MAIN_SCREEN_PANEL_STAT");
                    lv_obj_clear_flag(panels[i], LV_OBJ_FLAG_HIDDEN);
                    lv_obj_add_flag(panels[0], LV_OBJ_FLAG_HIDDEN);
                    active_panel = panel_type;
                    lv_obj_invalidate(panels[i]);
                    continue;
                }
                break;
            case LV_MAIN_SCREEN_PANEL_SPEED:
                if (i == 3) {
                    ESP_LOGI(TAG, "LV_MAIN_SCREEN_PANEL_SPEED");
                    lv_obj_clear_flag(screen->panel_speed, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_add_flag(panels[0], LV_OBJ_FLAG_HIDDEN);
                    active_panel = panel_type;
                    lv_obj_invalidate(panels[i]);
                    continue;
                }
                break;
            default:
                break;
        }
        lv_obj_add_flag(panels[i], LV_OBJ_FLAG_HIDDEN);
    }
    // lv_obj_report_style_change(obj);
}