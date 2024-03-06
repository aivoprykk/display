// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: lilygo_tdisplay_s3_04

#include "../ui.h"

void ui_StatsScreen_screen_init(void)
{
    ui_StatsScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_StatsScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_text_font(ui_StatsScreen, &ui_font_OswaldRegular48b4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsStatusPanelWrapper = lv_obj_create(ui_StatsScreen);
    lv_obj_set_width(ui_StatsStatusPanelWrapper, lv_pct(100));
    lv_obj_set_height(ui_StatsStatusPanelWrapper, lv_pct(15));
    lv_obj_set_align(ui_StatsStatusPanelWrapper, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_clear_flag(ui_StatsStatusPanelWrapper, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_StatsStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_StatsStatusPanelWrapper, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_StatsStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_StatsStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_StatsStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_StatsStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatStatusPanel = ui_StatusPanel_create(ui_StatsStatusPanelWrapper);
    lv_obj_set_x(ui_StatStatusPanel, 0);
    lv_obj_set_y(ui_StatStatusPanel, 0);





    ui_StatsPanel2Row = lv_obj_create(ui_StatsScreen);
    lv_obj_set_width(ui_StatsPanel2Row, lv_pct(100));
    lv_obj_set_height(ui_StatsPanel2Row, lv_pct(85));
    lv_obj_set_x(ui_StatsPanel2Row, 0);
    lv_obj_set_y(ui_StatsPanel2Row, -13);
    lv_obj_set_align(ui_StatsPanel2Row, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_StatsPanel2Row, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_StatsPanel2Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsPanel2Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_StatsPanel2Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_StatsPanel2Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_StatsPanel2Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_StatsPanel2Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel2Row1 = ui_BigDataPanel_create(ui_StatsPanel2Row);
    lv_obj_set_width(ui_Panel2Row1, lv_pct(100));
    lv_obj_set_height(ui_Panel2Row1, lv_pct(62));
    lv_obj_set_x(ui_Panel2Row1, 0);
    lv_obj_set_y(ui_Panel2Row1, 0);
    lv_obj_set_style_border_width(ui_Panel2Row1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel2Row1, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_x(ui_comp_get_child(ui_Panel2Row1, UI_COMP_BIGDATAPANEL_INFOLABEL), -267);
    lv_obj_set_y(ui_comp_get_child(ui_Panel2Row1, UI_COMP_BIGDATAPANEL_INFOLABEL), -14);

    lv_obj_set_x(ui_comp_get_child(ui_Panel2Row1, UI_COMP_BIGDATAPANEL_DATALABEL), 0);
    lv_obj_set_y(ui_comp_get_child(ui_Panel2Row1, UI_COMP_BIGDATAPANEL_DATALABEL), 3);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_Panel2Row1, UI_COMP_BIGDATAPANEL_DATALABEL), &ui_font_OswaldRegular84b4,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel2Row2 = lv_obj_create(ui_StatsPanel2Row);
    lv_obj_set_width(ui_Panel2Row2, lv_pct(100));
    lv_obj_set_height(ui_Panel2Row2, lv_pct(41));
    lv_obj_set_x(ui_Panel2Row2, 0);
    lv_obj_set_y(ui_Panel2Row2, lv_pct(62));
    lv_obj_clear_flag(ui_Panel2Row2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel2Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel2Row2, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel2Row2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2Row2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel2Row2, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel2Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel2Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel2Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel2Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsLeftPanel3 = ui_SmallDataPanel_create(ui_Panel2Row2);
    lv_obj_set_x(ui_StatsLeftPanel3, 0);
    lv_obj_set_y(ui_StatsLeftPanel3, 0);
    lv_obj_set_style_border_color(ui_StatsLeftPanel3, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsLeftPanel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsLeftPanel3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_StatsLeftPanel3, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsLeftPanel3, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsLeftPanel3, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);

    ui_StatsRightPanel3 = ui_SmallDataPanel_create(ui_Panel2Row2);
    lv_obj_set_x(ui_StatsRightPanel3, 161);
    lv_obj_set_y(ui_StatsRightPanel3, 0);
    lv_obj_set_style_border_color(ui_StatsRightPanel3, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsRightPanel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsRightPanel3, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsRightPanel3, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);

    ui_StatsPanel3Row = lv_obj_create(ui_StatsScreen);
    lv_obj_set_width(ui_StatsPanel3Row, lv_pct(100));
    lv_obj_set_height(ui_StatsPanel3Row, lv_pct(85));
    lv_obj_clear_flag(ui_StatsPanel3Row, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_StatsPanel3Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_StatsPanel3Row, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StatsPanel3Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsPanel3Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_StatsPanel3Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_StatsPanel3Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_StatsPanel3Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_StatsPanel3Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel3Row1 = lv_obj_create(ui_StatsPanel3Row);
    lv_obj_set_width(ui_Panel3Row1, lv_pct(100));
    lv_obj_set_height(ui_Panel3Row1, lv_pct(34));
    lv_obj_clear_flag(ui_Panel3Row1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel3Row1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel3Row1, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel3Row1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel3Row1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel3Row1, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel3Row1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel3Row1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel3Row1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel3Row1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsLeftPanel = ui_SmallDataPanel_create(ui_Panel3Row1);
    lv_obj_set_x(ui_StatsLeftPanel, 0);
    lv_obj_set_y(ui_StatsLeftPanel, 0);
    lv_obj_set_style_border_color(ui_StatsLeftPanel, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsLeftPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsLeftPanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_StatsLeftPanel, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsLeftPanel, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsLeftPanel, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);

    ui_StatsRightPanel = ui_SmallDataPanel_create(ui_Panel3Row1);
    lv_obj_set_y(ui_StatsRightPanel, 0);
    lv_obj_set_x(ui_StatsRightPanel, lv_pct(50));
    lv_obj_set_style_border_color(ui_StatsRightPanel, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsRightPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsRightPanel, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsRightPanel, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);

    ui_Panel3Row2 = lv_obj_create(ui_StatsPanel3Row);
    lv_obj_set_width(ui_Panel3Row2, lv_pct(100));
    lv_obj_set_height(ui_Panel3Row2, lv_pct(34));
    lv_obj_set_x(ui_Panel3Row2, 0);
    lv_obj_set_y(ui_Panel3Row2, lv_pct(34));
    lv_obj_clear_flag(ui_Panel3Row2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel3Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel3Row2, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel3Row2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel3Row2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel3Row2, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel3Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel3Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel3Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel3Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsLeftPanel1 = ui_SmallDataPanel_create(ui_Panel3Row2);
    lv_obj_set_x(ui_StatsLeftPanel1, 0);
    lv_obj_set_y(ui_StatsLeftPanel1, 0);
    lv_obj_set_style_border_color(ui_StatsLeftPanel1, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsLeftPanel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsLeftPanel1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_StatsLeftPanel1, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsLeftPanel1, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsLeftPanel1, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);

    ui_StatsRightPanel1 = ui_SmallDataPanel_create(ui_Panel3Row2);
    lv_obj_set_y(ui_StatsRightPanel1, 0);
    lv_obj_set_x(ui_StatsRightPanel1, lv_pct(50));
    lv_obj_set_style_border_color(ui_StatsRightPanel1, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsRightPanel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsRightPanel1, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsRightPanel1, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);

    ui_Panel3Row3 = lv_obj_create(ui_StatsPanel3Row);
    lv_obj_set_width(ui_Panel3Row3, lv_pct(100));
    lv_obj_set_height(ui_Panel3Row3, lv_pct(35));
    lv_obj_set_x(ui_Panel3Row3, 0);
    lv_obj_set_y(ui_Panel3Row3, lv_pct(67));
    lv_obj_clear_flag(ui_Panel3Row3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel3Row3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel3Row3, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel3Row3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel3Row3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel3Row3, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel3Row3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel3Row3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel3Row3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel3Row3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsLeftPanel2 = ui_SmallDataPanel_create(ui_Panel3Row3);
    lv_obj_set_x(ui_StatsLeftPanel2, 0);
    lv_obj_set_y(ui_StatsLeftPanel2, 0);
    lv_obj_set_style_border_color(ui_StatsLeftPanel2, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsLeftPanel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsLeftPanel2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_StatsLeftPanel2, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsLeftPanel2, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsLeftPanel2, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);

    ui_StatsRightPanel2 = ui_SmallDataPanel_create(ui_Panel3Row3);
    lv_obj_set_y(ui_StatsRightPanel2, 0);
    lv_obj_set_x(ui_StatsRightPanel2, lv_pct(50));
    lv_obj_set_style_border_color(ui_StatsRightPanel2, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsRightPanel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsRightPanel2, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsRightPanel2, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);

    ui_StatsPanel4Row = lv_obj_create(ui_StatsScreen);
    lv_obj_set_width(ui_StatsPanel4Row, lv_pct(100));
    lv_obj_set_height(ui_StatsPanel4Row, lv_pct(85));
    lv_obj_add_flag(ui_StatsPanel4Row, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_StatsPanel4Row, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_StatsPanel4Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_StatsPanel4Row, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StatsPanel4Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsPanel4Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_StatsPanel4Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_StatsPanel4Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_StatsPanel4Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_StatsPanel4Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel4Row1 = lv_obj_create(ui_StatsPanel4Row);
    lv_obj_set_width(ui_Panel4Row1, lv_pct(100));
    lv_obj_set_height(ui_Panel4Row1, lv_pct(25));
    lv_obj_clear_flag(ui_Panel4Row1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel4Row1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel4Row1, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel4Row1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel4Row1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel4Row1, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel4Row1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel4Row1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel4Row1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel4Row1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsLeftPanel4 = ui_SmallDataPanel_create(ui_Panel4Row1);
    lv_obj_set_x(ui_StatsLeftPanel4, 0);
    lv_obj_set_y(ui_StatsLeftPanel4, 0);
    lv_obj_set_style_border_color(ui_StatsLeftPanel4, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsLeftPanel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsLeftPanel4, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_StatsLeftPanel4, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsLeftPanel4, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsLeftPanel4, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_StatsLeftPanel4, UI_COMP_SMALLDATAPANEL_DATALABEL),
                               &ui_font_OswaldRegular36b4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsRightPanel4 = ui_SmallDataPanel_create(ui_Panel4Row1);
    lv_obj_set_y(ui_StatsRightPanel4, 0);
    lv_obj_set_x(ui_StatsRightPanel4, lv_pct(50));
    lv_obj_set_style_border_color(ui_StatsRightPanel4, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsRightPanel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsRightPanel4, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsRightPanel4, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_StatsRightPanel4, UI_COMP_SMALLDATAPANEL_DATALABEL),
                               &ui_font_OswaldRegular36b4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel4Row2 = lv_obj_create(ui_StatsPanel4Row);
    lv_obj_set_width(ui_Panel4Row2, lv_pct(100));
    lv_obj_set_height(ui_Panel4Row2, lv_pct(25));
    lv_obj_set_x(ui_Panel4Row2, 0);
    lv_obj_set_y(ui_Panel4Row2, lv_pct(25));
    lv_obj_clear_flag(ui_Panel4Row2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel4Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel4Row2, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel4Row2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel4Row2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel4Row2, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel4Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel4Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel4Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel4Row2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsLeftPanel5 = ui_SmallDataPanel_create(ui_Panel4Row2);
    lv_obj_set_x(ui_StatsLeftPanel5, 0);
    lv_obj_set_y(ui_StatsLeftPanel5, 0);
    lv_obj_set_style_border_color(ui_StatsLeftPanel5, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsLeftPanel5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsLeftPanel5, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_StatsLeftPanel5, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsLeftPanel5, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsLeftPanel5, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_StatsLeftPanel5, UI_COMP_SMALLDATAPANEL_DATALABEL),
                               &ui_font_OswaldRegular36b4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsRightPanel5 = ui_SmallDataPanel_create(ui_Panel4Row2);
    lv_obj_set_y(ui_StatsRightPanel5, 0);
    lv_obj_set_x(ui_StatsRightPanel5, lv_pct(50));
    lv_obj_set_style_border_color(ui_StatsRightPanel5, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsRightPanel5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsRightPanel5, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsRightPanel5, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_StatsRightPanel5, UI_COMP_SMALLDATAPANEL_DATALABEL),
                               &ui_font_OswaldRegular36b4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel4Row3 = lv_obj_create(ui_StatsPanel4Row);
    lv_obj_set_width(ui_Panel4Row3, lv_pct(100));
    lv_obj_set_height(ui_Panel4Row3, lv_pct(25));
    lv_obj_set_x(ui_Panel4Row3, 0);
    lv_obj_set_y(ui_Panel4Row3, lv_pct(50));
    lv_obj_clear_flag(ui_Panel4Row3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel4Row3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel4Row3, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel4Row3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel4Row3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel4Row3, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel4Row3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel4Row3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel4Row3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel4Row3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsLeftPanel6 = ui_SmallDataPanel_create(ui_Panel4Row3);
    lv_obj_set_x(ui_StatsLeftPanel6, 0);
    lv_obj_set_y(ui_StatsLeftPanel6, 0);
    lv_obj_set_style_border_color(ui_StatsLeftPanel6, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsLeftPanel6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsLeftPanel6, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_StatsLeftPanel6, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsLeftPanel6, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsLeftPanel6, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_StatsLeftPanel6, UI_COMP_SMALLDATAPANEL_DATALABEL),
                               &ui_font_OswaldRegular36b4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsRightPanel6 = ui_SmallDataPanel_create(ui_Panel4Row3);
    lv_obj_set_y(ui_StatsRightPanel6, 0);
    lv_obj_set_x(ui_StatsRightPanel6, lv_pct(50));
    lv_obj_set_style_border_color(ui_StatsRightPanel6, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsRightPanel6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsRightPanel6, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsRightPanel6, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_StatsRightPanel6, UI_COMP_SMALLDATAPANEL_DATALABEL),
                               &ui_font_OswaldRegular36b4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel4Row4 = lv_obj_create(ui_StatsPanel4Row);
    lv_obj_set_width(ui_Panel4Row4, lv_pct(100));
    lv_obj_set_height(ui_Panel4Row4, lv_pct(26));
    lv_obj_set_x(ui_Panel4Row4, 0);
    lv_obj_set_y(ui_Panel4Row4, lv_pct(75));
    lv_obj_clear_flag(ui_Panel4Row4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel4Row4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel4Row4, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel4Row4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel4Row4, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel4Row4, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel4Row4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel4Row4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel4Row4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel4Row4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsLeftPanel7 = ui_SmallDataPanel_create(ui_Panel4Row4);
    lv_obj_set_x(ui_StatsLeftPanel7, 0);
    lv_obj_set_y(ui_StatsLeftPanel7, 0);
    lv_obj_set_style_border_color(ui_StatsLeftPanel7, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsLeftPanel7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatsLeftPanel7, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_StatsLeftPanel7, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsLeftPanel7, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsLeftPanel7, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_StatsLeftPanel7, UI_COMP_SMALLDATAPANEL_DATALABEL),
                               &ui_font_OswaldRegular36b4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatsRightPanel7 = ui_SmallDataPanel_create(ui_Panel4Row4);
    lv_obj_set_y(ui_StatsRightPanel7, 0);
    lv_obj_set_x(ui_StatsRightPanel7, lv_pct(50));
    lv_obj_set_style_border_color(ui_StatsRightPanel7, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StatsRightPanel7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_set_x(ui_comp_get_child(ui_StatsRightPanel7, UI_COMP_SMALLDATAPANEL_DATALABEL), 40);
    lv_obj_set_y(ui_comp_get_child(ui_StatsRightPanel7, UI_COMP_SMALLDATAPANEL_DATALABEL), 1);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_StatsRightPanel7, UI_COMP_SMALLDATAPANEL_DATALABEL),
                               &ui_font_OswaldRegular36b4, LV_PART_MAIN | LV_STATE_DEFAULT);

}
