// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: lilygo_tdisplay_s3_04

#include "../ui.h"

void ui_SpeedScreen_screen_init(void)
{
    ui_SpeedScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SpeedScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_text_color(ui_SpeedScreen, lv_color_hex(0x323232), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SpeedScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SpeedScreen, &ui_font_OswaldRegular36b4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SpeedPanel = lv_obj_create(ui_SpeedScreen);
    lv_obj_set_width(ui_SpeedPanel, lv_pct(100));
    lv_obj_set_height(ui_SpeedPanel, lv_pct(100));
    lv_obj_clear_flag(ui_SpeedPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_SpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_SpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SpeedMainPanel = ui_BigDataPanel_create(ui_SpeedPanel);
    lv_obj_set_width(ui_SpeedMainPanel, lv_pct(100));
    lv_obj_set_height(ui_SpeedMainPanel, lv_pct(60));
    lv_obj_set_x(ui_SpeedMainPanel, 0);
    lv_obj_set_y(ui_SpeedMainPanel, 39);



    ui_SpeedStatusPanelWrapper = lv_obj_create(ui_SpeedPanel);
    lv_obj_set_width(ui_SpeedStatusPanelWrapper, lv_pct(100));
    lv_obj_set_height(ui_SpeedStatusPanelWrapper, lv_pct(15));
    lv_obj_set_align(ui_SpeedStatusPanelWrapper, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_clear_flag(ui_SpeedStatusPanelWrapper, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_SpeedStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_SpeedStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SpeedStatusPanelWrapper, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SpeedStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SpeedStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SpeedStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SpeedStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SpeedStatusPanel = ui_StatusPanel_create(ui_SpeedStatusPanelWrapper);
    lv_obj_set_x(ui_SpeedStatusPanel, 0);
    lv_obj_set_y(ui_SpeedStatusPanel, 0);





    ui_SpeedSecondaryPanel = lv_obj_create(ui_SpeedPanel);
    lv_obj_set_width(ui_SpeedSecondaryPanel, lv_pct(100));
    lv_obj_set_height(ui_SpeedSecondaryPanel, lv_pct(23));
    lv_obj_clear_flag(ui_SpeedSecondaryPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_SpeedSecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_SpeedSecondaryPanel, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_SpeedSecondaryPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_SpeedSecondaryPanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SpeedSecondaryPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SpeedSecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SpeedSecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SpeedSecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SpeedSecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LeftPanel = ui_SmallDataPanel_create(ui_SpeedSecondaryPanel);
    lv_obj_set_x(ui_LeftPanel, 0);
    lv_obj_set_y(ui_LeftPanel, 0);
    lv_obj_set_style_border_width(ui_LeftPanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_LeftPanel, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_RightPanel = ui_SmallDataPanel_create(ui_SpeedSecondaryPanel);
    lv_obj_set_y(ui_RightPanel, 0);
    lv_obj_set_x(ui_RightPanel, lv_pct(50));



    ui_Speed1Panel = lv_obj_create(ui_SpeedScreen);
    lv_obj_set_width(ui_Speed1Panel, lv_pct(100));
    lv_obj_set_height(ui_Speed1Panel, lv_pct(100));
    lv_obj_add_flag(ui_Speed1Panel, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_Speed1Panel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Speed1Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Speed1Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Speed1Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Speed1Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Speed1Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Speed1Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Speed1MainPanel = ui_BigDataPanel_create(ui_Speed1Panel);
    lv_obj_set_x(ui_Speed1MainPanel, 0);
    lv_obj_set_y(ui_Speed1MainPanel, 62);



    ui_Speed1SecondaryPanel = lv_obj_create(ui_Speed1Panel);
    lv_obj_set_height(ui_Speed1SecondaryPanel, 64);
    lv_obj_set_width(ui_Speed1SecondaryPanel, lv_pct(100));
    lv_obj_clear_flag(ui_Speed1SecondaryPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Speed1SecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Speed1SecondaryPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Speed1SecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Speed1SecondaryPanel, lv_color_hex(0x44B8D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Speed1SecondaryPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Speed1SecondaryPanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Speed1SecondaryPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Speed1SecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Speed1SecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Speed1SecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Speed1SecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RunBar = lv_bar_create(ui_Speed1SecondaryPanel);
    lv_bar_set_value(ui_RunBar, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_RunBar, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_RunBar, 150);
    lv_obj_set_height(ui_RunBar, 10);
    lv_obj_set_x(ui_RunBar, -13);
    lv_obj_set_y(ui_RunBar, -9);
    lv_obj_set_align(ui_RunBar, LV_ALIGN_CENTER);

    ui_MaxBar = lv_bar_create(ui_Speed1SecondaryPanel);
    lv_bar_set_value(ui_MaxBar, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_MaxBar, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_MaxBar, 150);
    lv_obj_set_height(ui_MaxBar, 10);
    lv_obj_set_x(ui_MaxBar, -13);
    lv_obj_set_y(ui_MaxBar, 16);
    lv_obj_set_align(ui_MaxBar, LV_ALIGN_CENTER);

    ui_MaxInfoLabel = lv_label_create(ui_Speed1SecondaryPanel);
    lv_obj_set_width(ui_MaxInfoLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MaxInfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MaxInfoLabel, -132);
    lv_obj_set_y(ui_MaxInfoLabel, 16);
    lv_obj_set_align(ui_MaxInfoLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MaxInfoLabel, "MAX");
    lv_obj_set_style_text_font(ui_MaxInfoLabel, &ui_font_OswaldRegular12b4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RunInfoLabel = lv_label_create(ui_Speed1SecondaryPanel);
    lv_obj_set_width(ui_RunInfoLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RunInfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_RunInfoLabel, -132);
    lv_obj_set_y(ui_RunInfoLabel, -10);
    lv_obj_set_align(ui_RunInfoLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_RunInfoLabel, "RUN");
    lv_obj_set_style_text_font(ui_RunInfoLabel, &ui_font_OswaldRegular12b4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RunLabel = lv_label_create(ui_Speed1SecondaryPanel);
    lv_obj_set_width(ui_RunLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RunLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_RunLabel, 114);
    lv_obj_set_y(ui_RunLabel, -15);
    lv_obj_set_align(ui_RunLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_RunLabel, "110.10");

    ui_MaxLabel = lv_label_create(ui_Speed1SecondaryPanel);
    lv_obj_set_width(ui_MaxLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MaxLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MaxLabel, 114);
    lv_obj_set_y(ui_MaxLabel, 16);
    lv_obj_set_align(ui_MaxLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MaxLabel, "110.10");

}
