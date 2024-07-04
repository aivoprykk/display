
#include "../ui.h"

ui_speed_screen_t ui_speed_screen = {0};
static const char *TAG = "ui_speed_screen";

static lv_obj_t *ui_Cell(lv_obj_t *parent, int w, ui_cell_t *cell) {

    lv_obj_t *panel = ui_common_panel_init(parent, w, 100), *cnt, *lbl;

    cnt =  ui_common_panel_init(panel, 22, 100);
    lv_obj_align(cnt, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_left(cnt, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cnt, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lbl = lv_label_create(cnt);
    lv_obj_set_width(lbl, LV_SIZE_CONTENT);
    lv_obj_set_height(lbl, LV_SIZE_CONTENT);
    lv_obj_align(lbl, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_label_set_text(lbl, "10S");
    lv_obj_set_style_text_font(lbl, ui_speed_screen.font.info, LV_PART_MAIN | LV_STATE_DEFAULT);
    cell->info = lbl;

    cnt =  ui_common_panel_init(panel, 80, 100);
    lv_obj_set_align(cnt, LV_ALIGN_RIGHT_MID);
    
    lbl = lv_label_create(cnt);
    lv_obj_set_width(lbl, LV_SIZE_CONTENT);
    lv_obj_set_height(lbl, LV_SIZE_CONTENT);
    lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(lbl, "109.09");
    lv_obj_set_style_text_font(lbl, ui_speed_screen.font.title, LV_PART_MAIN | LV_STATE_DEFAULT);
    cell->title = lbl;

    return panel;
}

lv_obj_t * load(lv_obj_t *parent) {
    lv_obj_t *panel = ui_common_panel_init(parent, 100, 100);
    
    // main speed indicator container
    // lv_obj_t *bottom_cnt = lv_obj_create(panel);
    // lv_obj_remove_style_all(bottom_cnt);
    // lv_obj_set_width(bottom_cnt, lv_pct(100));
    // lv_obj_set_height(bottom_cnt, lv_pct(65));
    // lv_obj_align(bottom_cnt, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    // lv_obj_clear_flag(bottom_cnt, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);  /// Flags

    lv_obj_t *main_lbl = lv_label_create(panel);
    lv_obj_set_width(main_lbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(main_lbl, LV_SIZE_CONTENT);  /// 1
    lv_obj_align(main_lbl, LV_ALIGN_CENTER, 0, lv_pct(15));
    lv_label_set_text(main_lbl, "134.90");
    lv_obj_set_style_text_font(main_lbl, ui_speed_screen.font.main, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_speed_screen.speed = main_lbl;

    // top container
    lv_obj_t *top_cnt = lv_obj_create(panel);
    lv_obj_remove_style_all(top_cnt);
    lv_obj_set_width(top_cnt, lv_pct(100));
    lv_obj_set_height(top_cnt, lv_pct(32));
    lv_obj_align(top_cnt, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_flex_flow(top_cnt, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(top_cnt, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(top_cnt, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    lv_obj_set_style_pad_top(top_cnt, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Cell(top_cnt, 50, &ui_speed_screen.cells[0][0]);
    ui_Cell(top_cnt, 50, &ui_speed_screen.cells[0][1]);

    lv_obj_t *bar = lv_bar_create(panel);
    lv_bar_set_value(bar, 25, LV_ANIM_OFF);
    //lv_bar_set_start_value(bar, 0, LV_ANIM_OFF);
    lv_bar_set_range(bar, 0, 240);
    lv_obj_set_height(bar, 4);
    lv_obj_set_width(bar, lv_pct(100));
    lv_obj_set_x(bar, 0);
    lv_obj_set_y(bar, lv_pct(30));
    lv_obj_set_style_radius(bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(bar, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(bar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(bar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(bar, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(bar, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(bar, lv_color_hex(0x000000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(bar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    ui_speed_screen.bar = bar;
    return panel;
}

void unload(void) {
    if(ui_speed_screen.screen.main_cnt == 0) return;
    lv_obj_clean(ui_speed_screen.screen.main_cnt);
    lv_obj_del(ui_speed_screen.screen.main_cnt);
    ui_speed_screen.screen.main_cnt = 0;
    ui_speed_screen.speed = 0;
    ui_speed_screen.bar = 0;
    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            memset(&ui_speed_screen.cells[i][j], 0, sizeof(ui_cell_t));
        }
    }
}

void ui_SpeedScreen_screen_init(void) {
    if(!ui_speed_screen.screen.self){
        ui_speed_screen.screen.has_status_cnt = 1;
        ui_speed_screen.screen.status_viewmode = 2;
        ui_speed_screen.screen.load = load;
        ui_speed_screen.screen.unload = unload;
        ui_common_screen_init(&ui_speed_screen.screen);
    }
    ui_flush_screens(&ui_speed_screen.screen);
    if(ui_speed_screen.screen.main_cnt == 0)
        ui_speed_screen.screen.main_cnt = load(ui_speed_screen.screen.self);
    ui_status_panel_load(&ui_speed_screen.screen);
}
