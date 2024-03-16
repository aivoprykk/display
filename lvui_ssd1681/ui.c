// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: squareline_proj_1_54_02

#include "ui.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_SpeedScreen
void ui_SpeedScreen_screen_init(void);
lv_obj_t * ui_SpeedScreen;
lv_obj_t * ui_SpeedSecondaryPanel;
lv_obj_t * ui_LeftPanel;
lv_obj_t * ui_RightPanel;
lv_obj_t * ui_SpeedStatusPanelWrapper;
lv_obj_t * ui_SpeedStatusPanel;
lv_obj_t * ui_SpeedMainPanel;
lv_obj_t * ui_SpeedBar;


// SCREEN: ui_StatsScreen
void ui_StatsScreen_screen_init(void);
lv_obj_t * ui_StatsScreen;
lv_obj_t * ui_StatsStatusPanelWrapper;
lv_obj_t * ui_StatsStatusPanel;
lv_obj_t * ui_StatsPanel2Row;
lv_obj_t * ui_Stats2Row1Panel1;
lv_obj_t * ui_Stats2Row1FullPanel;
lv_obj_t * ui_Stats2Row2Panel;
lv_obj_t * ui_Stats2Row2LeftPanel;
lv_obj_t * ui_Stats2Row2RightPanel;
lv_obj_t * ui_StatsPanel3Row;
lv_obj_t * ui_Stats3Row1Panel;
lv_obj_t * ui_Stats3Row1FullPanel;
lv_obj_t * ui_Stats3Row2Panel;
lv_obj_t * ui_Stats3Row2FullPanel;
lv_obj_t * ui_Stats3Row3Panel;
lv_obj_t * ui_Stats3Row3LeftPanel;
lv_obj_t * ui_Stats3Row3RightPanel;
lv_obj_t * ui_StatsPanel4Row;
lv_obj_t * ui_Stats4Row1Panel;
lv_obj_t * ui_Stats4Row1FullPanel;
lv_obj_t * ui_Stats4Row2Panel;
lv_obj_t * ui_Stats4Row2LeftPanel;
lv_obj_t * ui_Stats4Row2RightPanel;
lv_obj_t * ui_Stats4Row3Panel;
lv_obj_t * ui_Stats4Row3LeftPanel;
lv_obj_t * ui_Stats4Row3RightPanel;
lv_obj_t * ui_Stats4Row4Panel;
lv_obj_t * ui_Stats4Row4LeftPanel;
lv_obj_t * ui_Stats4Row4RightPanel;
lv_obj_t * ui_StatsPanel4Row2;
lv_obj_t * ui_Stats4Row1Panel2;
lv_obj_t * ui_Stats4Row1FullPanel2;
lv_obj_t * ui_Stats4Row2Panel2;
lv_obj_t * ui_Stats4Row2FullPanel2;
lv_obj_t * ui_Stats4Row3Panel2;
lv_obj_t * ui_Stats4Row3LeftPanel2;
lv_obj_t * ui_Stats4Row3RightPanel2;
lv_obj_t * ui_Stats4Row4Panel2;
lv_obj_t * ui_Stats4Row4LeftPanel2;
lv_obj_t * ui_Stats4Row4RightPanel2;
lv_obj_t * ui_StatsPanel5Row;
lv_obj_t * ui_Stats5Row1Panel;
lv_obj_t * ui_Stats5Row1LeftPanel;
lv_obj_t * ui_Stats5Row1RightPanel;
lv_obj_t * ui_Stats5Row2Panel;
lv_obj_t * ui_Stats5Row2LeftPanel;
lv_obj_t * ui_Stats5Row2RightPanel;
lv_obj_t * ui_Stats5Row3Panel;
lv_obj_t * ui_Stats5Row3LeftPanel;
lv_obj_t * ui_Stats5Row3RightPanel;
lv_obj_t * ui_Stats5Row4Panel;
lv_obj_t * ui_Stats5Row4LeftPanel;
lv_obj_t * ui_Stats5Row4RightPanel;
lv_obj_t * ui_Stats5Row5Panel;
lv_obj_t * ui_Stats5Row5LeftPanel;
lv_obj_t * ui_Stats5Row5RightPanel;


// SCREEN: ui_InfoScreen
void ui_InfoScreen_screen_init(void);
lv_obj_t * ui_InfoScreen;
lv_obj_t * ui_InfoStatusPanelWrapper;
lv_obj_t * ui_InfoStatusPanel;
lv_obj_t * ui_InfoMainPanel;
lv_obj_t * ui_MainImage;
lv_obj_t * ui_MainLabel;
lv_obj_t * ui_MainLowerLabel;
lv_obj_t * ui_InfoInitPanel;
lv_obj_t * ui_InitImage;
lv_obj_t * ui_InitLabel;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_battery_horiz_000_fill0_wght400_grad0_opsz[1] = {&ui_img_battery_horiz_000_fill0_wght400_grad0_opsz24_png};
const lv_img_dsc_t * ui_imgset_navigation_fill0_wght400_grad0_opsz[1] = {&ui_img_navigation_fill0_wght400_grad0_opsz24_png};
const lv_img_dsc_t * ui_imgset_radio_button_checked_fill0_wght400_grad0_opsz[1] = {&ui_img_radio_button_checked_fill0_wght400_grad0_opsz24_png};
const lv_img_dsc_t * ui_imgset_radio_button_partial_fill0_wght400_grad0_opsz[1] = {&ui_img_radio_button_partial_fill0_wght400_grad0_opsz24_png};
const lv_img_dsc_t * ui_imgset_radio_button_unchecked_fill0_wght400_grad0_opsz[1] = {&ui_img_radio_button_unchecked_fill0_wght400_grad0_opsz24_png};
const lv_img_dsc_t * ui_imgset_sd_card_fill0_wght400_grad0_opsz[1] = {&ui_img_sd_card_fill0_wght400_grad0_opsz24_png};
const lv_img_dsc_t * ui_imgset_wifi_fill0_wght400_grad0_opsz[1] = {&ui_img_wifi_fill0_wght400_grad0_opsz24_png};

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    ui_common_init();
    ui_SpeedScreen_screen_init();
    ui_StatsScreen_screen_init();
    ui_InfoScreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_SpeedScreen);
}
