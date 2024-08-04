
#include "../ui.h"

ui_info_screen_t ui_info_screen = {0};
static const char * TAG = "ui_info_screen";

static lv_obj_t * load(lv_obj_t *parent) {
    lv_obj_t *panel = ui_common_panel_init(parent, 100, 80);
    
    lv_obj_t *label;
    label = lv_label_create(panel);
    lv_obj_set_width(label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_x(label, lv_pct(27));
    lv_obj_set_y(label, lv_pct(-14));
    lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_text_font(label, ui_info_screen.font.title, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_info_screen.info_lbl = label;

    label = lv_label_create(panel);
    lv_obj_set_width(label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_x(label, lv_pct(27));
    lv_obj_set_y(label, lv_pct(11));
    lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_text_font(label, ui_info_screen.font.info, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(label, "");
    ui_info_screen.info_secondary_lbl = label;

    label = lv_label_create(panel);
    lv_obj_set_width(label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_x(label, lv_pct(27));
    lv_obj_set_y(label, lv_pct(30));
    lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_text_font(label, ui_info_screen.font.info, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(label, "");
    ui_info_screen.info_third_lbl = label;

    lv_obj_t *ui_MainImage = lv_img_create(panel);
    lv_img_set_src(ui_MainImage, &near_me_bold_48px);
    lv_obj_set_width(ui_MainImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MainImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_y(ui_MainImage, 0);
    lv_obj_set_x(ui_MainImage, lv_pct(6));
    lv_obj_set_align(ui_MainImage, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_MainImage, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
    lv_obj_clear_flag(ui_MainImage, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    ui_info_screen.info_img = ui_MainImage;

    return panel;
}

static void unload(void) {
    if(ui_info_screen.screen.main_cnt == 0) return;
    lv_obj_clean(ui_info_screen.screen.main_cnt);
    lv_obj_del(ui_info_screen.screen.main_cnt);
    ui_info_screen.screen.main_cnt = 0;
    ui_info_screen.info_lbl = 0;
    ui_info_screen.info_secondary_lbl = 0;
    ui_info_screen.info_img = 0;
}

void ui_InfoScreen_screen_init(void) {
    if(!ui_info_screen.screen.self){
        ui_info_screen.screen.has_status_cnt = 1;
        ui_info_screen.screen.status_viewmode = 0;
        ui_info_screen.screen.load = load;
        ui_info_screen.screen.unload = unload;
        ui_info_screen.screen.self = ui_common_screen_init(&ui_info_screen.screen);
    }
    ui_flush_screens(&ui_info_screen.screen);
    if(ui_info_screen.screen.main_cnt == 0)
        ui_info_screen.screen.main_cnt = load(ui_info_screen.screen.self);
    ui_status_panel_load(&ui_info_screen.screen);
}
