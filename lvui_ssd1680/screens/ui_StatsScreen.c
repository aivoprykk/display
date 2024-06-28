
#include "../ui.h"
#include "logger_common.h"

ui_stats_screen_t ui_stats_screen = {0};
static const char *TAG = "ui_stats_screen";

static lv_obj_t *ui_Cell(lv_obj_t *cnt, int w, int wi, int wt, ui_cell_t *cell) {

    lv_obj_t *panel = ui_common_panel_init(cnt, w, 100);

    lv_obj_t *info_cnt = ui_common_panel_init(panel, wi, 100);
    lv_obj_set_align(info_cnt, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_pad_left(info_cnt, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(info_cnt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(info_cnt, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(info_cnt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(info_cnt, ui_stats_screen.font.info, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *info_lbl = lv_label_create(info_cnt);
    lv_obj_set_width(info_lbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(info_lbl, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_align(info_lbl, LV_ALIGN_LEFT_MID);
    lv_label_set_text(info_lbl, "250mAVG");
    cell->info = info_lbl;

    lv_obj_t *title_cnt = ui_common_panel_init(panel, wt, 100);
    lv_obj_set_align(title_cnt, LV_ALIGN_RIGHT_MID);
    
    lv_obj_t *title_lbl = lv_label_create(title_cnt);
    lv_obj_set_width(title_lbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(title_lbl, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_align(title_lbl, LV_ALIGN_CENTER);
    lv_label_set_text(title_lbl, "99.09");
    cell->title = title_lbl;

    return panel;
}

static lv_obj_t *uiStatsPanelLoad(lv_obj_t *parent, int rowlen, int collen) {
    
    lv_obj_t *panel = ui_common_panel_init(parent, 100, 80);
    
    lv_obj_set_style_pad_left(panel, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(panel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    if(rowlen<4)
    lv_obj_set_style_text_font(panel, ui_stats_screen.font.title, LV_PART_MAIN | LV_STATE_DEFAULT);
    else
    lv_obj_set_style_text_font(panel, ui_stats_screen.font.title_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *rows[7] = {0}, *cols[2] = {0};
    int numrows = rowlen, h = 100 / numrows, numcols = collen, fh=h;
    if (numcols > 100){
        if (numcols > 200)
            numcols -= 200;
        else 
            numcols -= 100;
        if(numcols == 2 && collen < 200) {
            h = 6+(100/3); // 30%
            fh = 100-h; // 70%
        }
    }
    // w = 100 / numcols;
    for (int i = 0, ypos = 0; i < numrows; ++i) {
        if(i>0) ypos += (i==1 ? fh : h);
        rows[i] = ui_common_panel_init(panel, 100, (i==0 ? fh : h));
        lv_obj_set_x(rows[i], 0);
        lv_obj_set_y(rows[i], lv_pct(ypos));
        lv_obj_set_flex_flow(rows[i], LV_FLEX_FLOW_ROW);
        if (i > 0) {
            lv_obj_set_style_border_width(rows[i], 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(rows[i], LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
        }

        if ((collen > 200 && i < 2) || (collen > 100 && i < 1) || collen==1) {
            lv_obj_set_flex_align(rows[i], LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
            if(collen == 1 ) {
                cols[0] = ui_Cell(rows[i], 60, 35, 75, &ui_stats_screen.cells[i][0]);
                lv_obj_set_x(cols[0], lv_pct(-10));
            }
            else
                cols[0] = ui_Cell(rows[i], 100, 20, 85, &ui_stats_screen.cells[i][0]);
            cols[1] = 0;
            if(collen!=1 && fh!=h && i==0) {
                lv_obj_set_style_text_font(ui_stats_screen.cells[i][0].title, ui_stats_screen.font.title_big, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        } else {
            lv_obj_set_flex_align(rows[i], LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
            for (int j = 0; j < numcols; ++j) {
                cols[j] = ui_Cell(rows[i], 50, 35, 65, &ui_stats_screen.cells[i][j]);
                if (j > 0) {
                    lv_obj_set_style_border_width(cols[j], 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_side(cols[j], LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }

    return panel;
}

static lv_obj_t * load(lv_obj_t * parent) {
    LOGR
    return uiStatsPanelLoad(parent, ui_stats_screen.rows , ui_stats_screen.cols);
}

static void unload(void) {
    LOGR
    if (ui_stats_screen.screen.main_cnt == 0) return;
    lv_obj_clean(ui_stats_screen.screen.main_cnt);
    lv_obj_del(ui_stats_screen.screen.main_cnt);
    ui_stats_screen.screen.main_cnt = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; ++j) {
            memset(&ui_stats_screen.cells[i][j], 0, sizeof(ui_cell_t));
        }
    }
}

void ui_StatsScreen_screen_init(int rows, int cols) {
    if (!ui_stats_screen.screen.self){
        ui_stats_screen.screen.has_status_cnt = 1;
        ui_stats_screen.screen.status_viewmode = 0;
        ui_stats_screen.screen.load = load;
        ui_stats_screen.screen.unload = unload;
        ui_common_screen_init(&ui_stats_screen.screen);
    }
    ui_flush_screens(&ui_stats_screen.screen);
    if(cols!=ui_stats_screen.cols || rows!=ui_stats_screen.rows) {
        unload();
    }
    if (ui_stats_screen.screen.main_cnt == 0) {
        ui_stats_screen.rows = rows;
        ui_stats_screen.cols = cols;
        ui_stats_screen.screen.main_cnt = load(ui_stats_screen.screen.self);
    }
    ui_status_panel_load(&ui_stats_screen.screen);
}
