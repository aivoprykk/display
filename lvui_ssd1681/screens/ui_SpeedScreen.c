// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: squareline_proj_1_54_02

#include "../ui.h"

void ui_SpeedScreen_screen_init(void)
{
    ui_SpeedScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SpeedScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_text_font(ui_SpeedScreen, &ui_font_OswaldRegular24p2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SpeedSecondaryPanel = lv_obj_create(ui_SpeedScreen);
    lv_obj_set_height(ui_SpeedSecondaryPanel, 95);
    lv_obj_set_width(ui_SpeedSecondaryPanel, lv_pct(100));
    lv_obj_set_x(ui_SpeedSecondaryPanel, 0);
    lv_obj_set_y(ui_SpeedSecondaryPanel, -3);
    lv_obj_clear_flag(ui_SpeedSecondaryPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_width(ui_SpeedSecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SpeedSecondaryPanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SpeedSecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SpeedSecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SpeedSecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SpeedSecondaryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SpeedSecondaryPanel, &ui_font_OswaldRegular16p2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LeftPanel = ui_SmallDataPanel_create(ui_SpeedSecondaryPanel);
    lv_obj_set_height(ui_LeftPanel, 40);
    lv_obj_set_width(ui_LeftPanel, lv_pct(100));
    lv_obj_set_x(ui_LeftPanel, 3);
    lv_obj_set_y(ui_LeftPanel, 7);

    lv_obj_set_style_text_font(ui_comp_get_child(ui_LeftPanel, UI_COMP_SMALLDATAPANEL_DATALABEL),
                               &ui_font_OswaldRegular40p2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RightPanel = ui_SmallDataPanel_create(ui_SpeedSecondaryPanel);
    lv_obj_set_height(ui_RightPanel, 40);
    lv_obj_set_width(ui_RightPanel, lv_pct(100));
    lv_obj_set_x(ui_RightPanel, 3);
    lv_obj_set_y(ui_RightPanel, 54);

    lv_obj_set_style_text_font(ui_comp_get_child(ui_RightPanel, UI_COMP_SMALLDATAPANEL_DATALABEL),
                               &ui_font_OswaldRegular40p2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SpeedStatusPanelWrapper = lv_obj_create(ui_SpeedScreen);
    lv_obj_set_width(ui_SpeedStatusPanelWrapper, lv_pct(100));
    lv_obj_set_height(ui_SpeedStatusPanelWrapper, lv_pct(11));
    lv_obj_set_align(ui_SpeedStatusPanelWrapper, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_SpeedStatusPanelWrapper, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_width(ui_SpeedStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SpeedStatusPanelWrapper, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SpeedStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SpeedStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SpeedStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SpeedStatusPanelWrapper, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SpeedStatusPanel = ui_StatusPanel_create(ui_SpeedStatusPanelWrapper);
    lv_obj_set_x(ui_SpeedStatusPanel, 0);
    lv_obj_set_y(ui_SpeedStatusPanel, 0);





    ui_SpeedMainPanel = ui_BigDataPanel_create(ui_SpeedScreen);
    lv_obj_set_width(ui_SpeedMainPanel, lv_pct(100));
    lv_obj_set_height(ui_SpeedMainPanel, lv_pct(60));
    lv_obj_set_x(ui_SpeedMainPanel, 0);
    lv_obj_set_y(ui_SpeedMainPanel, lv_pct(38));
    lv_obj_set_style_bg_color(ui_SpeedMainPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SpeedMainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SpeedMainPanel, &ui_font_OswaldRegular16p2, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_font(ui_comp_get_child(ui_SpeedMainPanel, UI_COMP_BIGDATAPANEL_DATALABEL),
                               &ui_font_OswaldRegular80p2, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_x(ui_comp_get_child(ui_SpeedMainPanel, UI_COMP_BIGDATAPANEL_INFOLABEL), 163);
    lv_obj_set_y(ui_comp_get_child(ui_SpeedMainPanel, UI_COMP_BIGDATAPANEL_INFOLABEL), 50);
    lv_obj_clear_flag(ui_comp_get_child(ui_SpeedMainPanel, UI_COMP_BIGDATAPANEL_INFOLABEL),
                      LV_OBJ_FLAG_HIDDEN);      /// Flags

    ui_SpeedBar = lv_bar_create(ui_SpeedScreen);
    lv_bar_set_value(ui_SpeedBar, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_SpeedBar, 0, LV_ANIM_OFF);
    lv_obj_set_height(ui_SpeedBar, 5);
    lv_obj_set_width(ui_SpeedBar, lv_pct(100));
    lv_obj_set_x(ui_SpeedBar, 0);
    lv_obj_set_y(ui_SpeedBar, 91);
    lv_obj_set_style_radius(ui_SpeedBar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SpeedBar, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SpeedBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_SpeedBar, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SpeedBar, lv_color_hex(0x000000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SpeedBar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

}
