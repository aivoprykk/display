#include "lv_comp_info_panel.h"
#include <core/lv_obj_class.h>
#include "logger_common.h"
#include "ui_common.h"

static const char TAG[] = "lv_info_panel";

LV_IMG_DECLARE(ui_img_1413901806);  // assets\esp-gps-logo-v2-100px.png
// LV_IMG_DECLARE(ui_img_navigation_fill0_wght400_grad0_opsz24_png);  // assets\navigation_FILL0_wght400_GRAD0_opsz24.png

#define MY_CLASS &lv_info_panel_class
TIMER_INIT

static void lv_info_panel_constructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    LOGR
}

void lv_info_panel_setup_mode(lv_obj_t *obj, uint8_t mode) {
    ESP_LOGD(TAG, "lv_info_panel_setup_mode %d", mode);
    lv_info_panel_t *panel = (lv_info_panel_t *)obj;
    lv_obj_t *image = panel->title_image;
    switch (mode) {
        case 0:  // boot
            lv_img_set_src(image, &espidf_logo_v2_48px);
            lv_obj_set_size(image, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
            lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);
            lv_obj_align(panel->title_label, LV_ALIGN_CENTER, 0, 50);
            lv_obj_add_flag(panel->info_label, LV_OBJ_FLAG_HIDDEN);
            break;
        case 1:  // info
            lv_img_set_src(image, &near_me_bold_48px);
            lv_obj_set_size(image, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
            lv_obj_align(image, LV_ALIGN_CENTER, -69, 0);
            lv_obj_align(panel->title_label, LV_ALIGN_CENTER, 0, -12);
            lv_obj_align(panel->info_label, LV_ALIGN_CENTER, 0, 16);
            lv_obj_clear_flag(panel->info_label, LV_OBJ_FLAG_HIDDEN);
        default:
            break;
    }
}

static void lv_info_panel_destructor(const lv_obj_class_t *class_p, lv_obj_t *obj) {
    LOGR
    lv_obj_clean(obj);
}

static void lv_info_panel_event(const lv_obj_class_t *class_p, lv_event_t *e) {
    ESP_LOGD(TAG, "lv_info_panel_event %d", e->code);
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

const lv_obj_class_t lv_info_panel_class = {
    .base_class = &lv_obj_class,
    .constructor_cb = lv_info_panel_constructor,
    .destructor_cb = lv_info_panel_destructor,
    .event_cb = lv_info_panel_event,
    .width_def = LV_PCT(100),
    .height_def = LV_SIZE_CONTENT,
    .instance_size = sizeof(lv_info_panel_t)};

lv_obj_t *lv_info_panel_create(lv_obj_t *parent, lv_coord_t width, lv_coord_t height) {
    TIMER_S
    lv_obj_t *obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);

    LV_ASSERT_MALLOC(obj);
    if (obj == NULL)
        goto end;

    // ESP_LOGI(TAG, "scr %d x %d", lv_obj_get_height(lv_scr_act()), lv_obj_get_width(lv_scr_act()));
    lv_obj_remove_style_all(obj);
    lv_obj_set_size(obj,width, height);
    lv_obj_align(obj, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    // lv_obj_add_style(obj, (lv_style_ptr_t)&style_border_full, 0);
    
    lv_info_panel_t *panel = (lv_info_panel_t *)obj;

    panel->title_image = lv_img_create(obj);
    lv_obj_clear_flag(panel->title_image, LV_OBJ_FLAG_SCROLLABLE);          /// Fla
    lv_obj_align(panel->title_image, LV_ALIGN_CENTER, 0, 0);
    //lv_obj_set_size(panel->title_image, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
    // lv_img_set_src(panel->title_image, &ui_img_2129950171);

    panel->title_label = lv_label_create(obj);
    lv_obj_align(panel->title_label, LV_ALIGN_CENTER, 0, 50);
    //lv_obj_set_size(panel->title_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
    //lv_label_set_text(panel->title_label, "LOGGER");
    // lv_obj_add_style(panel->title_label, (lv_style_ptr_t)&style_text_large, 0);

    panel->info_label = lv_label_create(obj);
    lv_obj_align(panel->info_label, LV_ALIGN_CENTER, 0, 70);
    lv_obj_set_size(panel->info_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);  /// 1
    lv_obj_add_flag(panel->info_label, LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_style(panel->info_label, (lv_style_ptr_t)&style_text_normal, 0);
    TIMER_E
    end:
    return obj;
}

void lv_info_panel_set_title(lv_obj_t *obj, const char *title) {
    lv_info_panel_t *panel = (lv_info_panel_t *)obj;
    lv_label_set_text(panel->title_label, title);
}

void lv_info_panel_set_info(lv_obj_t *obj, const char *info) {
    lv_info_panel_t *panel = (lv_info_panel_t *)obj;
    lv_label_set_text(panel->info_label, info);
}

void lv_info_panel_set_title_image(lv_obj_t *obj, const void *img) {
    lv_info_panel_t *panel = (lv_info_panel_t *)obj;
    lv_img_set_src(panel->title_image, img);
}