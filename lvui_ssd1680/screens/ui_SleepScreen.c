
#include "../ui.h"

ui_sleep_screen_t ui_sleep_screen = {0};
static const char * TAG = "ui_sleep_screen";

static lv_obj_t * ui_Cell(lv_obj_t *cnt, int w, int col, ui_cell_t *cell) {
    lv_obj_t * panel = ui_common_panel_init(cnt, w, 100);

    // lv_obj_t *info_cnt =  ui_common_panel_init(panel, wi, 100);
    // lv_obj_set_align(info_cnt, LV_ALIGN_LEFT_MID);
    
    lv_obj_t *info_lbl = lv_label_create(panel);
    lv_obj_set_width(info_lbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(info_lbl, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_align(info_lbl, LV_ALIGN_LEFT_MID);
    lv_label_set_text(info_lbl, "R5:");
    if(col>0)
        lv_obj_set_style_pad_left(info_lbl, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    cell->info = info_lbl;

    // lv_obj_t *title_cnt = ui_common_panel_init(panel, wt, 100);
    // lv_obj_set_align(title_cnt, LV_ALIGN_RIGHT_MID);
    
    lv_obj_t *title_lbl = lv_label_create(panel);
    lv_obj_set_width(title_lbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(title_lbl, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_align(title_lbl, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(title_lbl, "109.09");
    cell->title = title_lbl;

    return panel;
}

static lv_obj_t *load(lv_obj_t *parent) {
    lv_obj_t *panel = ui_common_panel_init(parent, 100, 83);

    lv_obj_set_style_pad_left(panel, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(panel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#ifdef CONFIG_DISPLAY_DRIVER_SSD1681
    lv_obj_t *right_container =  ui_common_panel_init(panel, 20, 100);
#else
    lv_obj_t *right_container =  ui_common_panel_init(panel, 30, 100);
#endif
    lv_obj_set_align(right_container, LV_ALIGN_TOP_RIGHT);
    
    lv_obj_t *up_img = lv_img_create(right_container);
    lv_img_set_src(up_img, &sb_48px);
    lv_obj_set_width(up_img, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(up_img, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_x(up_img, 0);
    lv_obj_set_y(up_img, -24);
    lv_obj_set_align(up_img, LV_ALIGN_CENTER);
    // lv_obj_add_flag(up_img, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
    lv_obj_clear_flag(up_img, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    ui_sleep_screen.up_img = up_img;

    lv_obj_t *bottom_img = lv_img_create(right_container);
    lv_img_set_src(bottom_img, &gunsails_48px);
    lv_obj_set_width(bottom_img, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(bottom_img, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_x(bottom_img, 0);
    lv_obj_set_y(bottom_img, 27);
    lv_obj_set_align(bottom_img, LV_ALIGN_CENTER);
    // lv_obj_add_flag(bottom_img, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
    lv_obj_clear_flag(bottom_img, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    ui_sleep_screen.bottom_img = bottom_img;

#ifdef CONFIG_DISPLAY_DRIVER_SSD1681
    lv_obj_t *left_container =  ui_common_panel_init(panel, 85, 100);
#else
    lv_obj_t *left_container =  ui_common_panel_init(panel, 80, 100);
#endif
    lv_obj_set_style_text_font(left_container, ui_sleep_screen.font.normal, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *rows[6]={0}; // , *cols[2]={0};
    int numrows = 6, h = 100/(numrows+1);
    for (int i = 0, ypos = 0; i < numrows; ++i, ypos += h) {


        rows[i] = ui_common_panel_init(left_container, 100, 0);
        lv_obj_set_x(rows[i], 0);
        lv_obj_clear_flag(rows[i], LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_height(rows[i], lv_pct(h));
        lv_obj_set_y(rows[i], lv_pct(ypos));
        lv_obj_set_flex_flow(rows[i], LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(rows[i], LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

        for (int j = 0; j < 2; ++j) {
            // cols[j] = 
            ui_Cell(rows[i], j==0 ? 35 : 46, j, &ui_sleep_screen.cells[i][j]);
        }
    }
    lv_obj_t *title_lbl = lv_label_create(left_container);
    lv_obj_set_y(title_lbl, lv_pct(84));
    lv_obj_set_width(title_lbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(title_lbl, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_align(title_lbl, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(title_lbl, "#MY ID");
    lv_obj_set_style_text_font(title_lbl, ui_sleep_screen.font.title, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_sleep_screen.myid = title_lbl;

    return panel;
}

static void unload() {
    if(ui_sleep_screen.screen.main_cnt == NULL) return;
    lv_obj_clean(ui_sleep_screen.screen.main_cnt);
    lv_obj_del(ui_sleep_screen.screen.main_cnt);
    ui_sleep_screen.screen.main_cnt = NULL;
    ui_sleep_screen.myid = NULL;
    ui_sleep_screen.up_img = NULL;
    ui_sleep_screen.bottom_img = NULL;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 2; ++j) {
            memset(&ui_sleep_screen.cells[i][j], 0, sizeof(ui_cell_t));
        }
    }
}

void ui_SleepScreen_screen_init(void) {
    if(!ui_sleep_screen.screen.self) {
        ui_sleep_screen.screen.has_status_cnt = 1;
        ui_sleep_screen.screen.status_viewmode = 1;
        ui_sleep_screen.screen.load = load;
        ui_sleep_screen.screen.unload = unload;
        ui_common_screen_init(&ui_sleep_screen.screen);
    }
    ui_flush_screens(&ui_sleep_screen.screen);
    if(ui_sleep_screen.screen.main_cnt == NULL)
        ui_sleep_screen.screen.main_cnt = load(ui_sleep_screen.screen.self);
    ui_status_panel_load(&ui_sleep_screen.screen);
}