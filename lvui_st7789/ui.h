// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: lilygo_tdisplay_s3_04

#ifndef _LILYGO_TDISPLAY_S3_04_UI_H
#define _LILYGO_TDISPLAY_S3_04_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ui_common.h"


// SCREEN: ui_SpeedScreen
void ui_SpeedScreen_screen_init(void);
extern lv_obj_t * ui_SpeedScreen;
extern lv_obj_t * ui_SpeedPanel;
extern lv_obj_t * ui_SpeedSecondaryPanel;
extern lv_obj_t * ui_LeftPanel;
extern lv_obj_t * ui_RightPanel;
extern lv_obj_t * ui_SpeedMainPanel;
extern lv_obj_t * ui_SpeedStatusPanelWrapper;
extern lv_obj_t * ui_SpeedStatusPanel;
extern lv_obj_t * ui_Speed1Panel;
extern lv_obj_t * ui_Speed1MainPanel;
extern lv_obj_t * ui_Speed1SecondaryPanel;
extern lv_obj_t * ui_RunBar;
extern lv_obj_t * ui_MaxBar;
extern lv_obj_t * ui_MaxInfoLabel;
extern lv_obj_t * ui_RunInfoLabel;
extern lv_obj_t * ui_RunLabel;
extern lv_obj_t * ui_MaxLabel;
// SCREEN: ui_InfoScreen
void ui_InfoScreen_screen_init(void);
extern lv_obj_t * ui_InfoScreen;
extern lv_obj_t * ui_InfoStatusPanelWrapper;
extern lv_obj_t * ui_InfoStatusPanel;
extern lv_obj_t * ui_InfoMainPanel;
extern lv_obj_t * ui_MainImage;
extern lv_obj_t * ui_MainLabel;
extern lv_obj_t * ui_MainLowerLabel;
extern lv_obj_t * ui_InfoInitPanel;
extern lv_obj_t * ui_InitImage;
extern lv_obj_t * ui_InitLabel;
// SCREEN: ui_StatsScreen
void ui_StatsScreen_screen_init(void);
extern lv_obj_t * ui_StatsScreen;
extern lv_obj_t * ui_StatsStatusPanelWrapper;
extern lv_obj_t * ui_StatStatusPanel;
extern lv_obj_t * ui_StatsPanel2Row;
extern lv_obj_t * ui_Stats2Row1FullPanel;
extern lv_obj_t * ui_Stats2Row2Panel;
extern lv_obj_t * ui_Stats2Row2LeftPanel;
extern lv_obj_t * ui_Stats2Row2RightPanel;
extern lv_obj_t * ui_StatsPanel3Row;
extern lv_obj_t * ui_Stats3Row1Panel;
extern lv_obj_t * ui_Stats3Row1LeftPanel;
extern lv_obj_t * ui_Stats3Row1RightPanel;
extern lv_obj_t * ui_Stats3Row2Panel;
extern lv_obj_t * ui_Stats3Row2LeftPanel;
extern lv_obj_t * ui_Stats3Row2RightPanel;
extern lv_obj_t * ui_Stats3Row3Panel;
extern lv_obj_t * ui_Stats3Row3LeftPanel;
extern lv_obj_t * ui_Stats3Row3RightPanel;
extern lv_obj_t * ui____initial_actions0;

LV_IMG_DECLARE(ui_img_near_me_fill0_wght400_grad0_opsz24_png);    // assets/near_me_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE(ui_img_sd_card_fill0_wght400_grad0_opsz24_png);    // assets/sd_card_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE(ui_img_2129950171);    // assets/esp-gps-logo-v2-100px.png
LV_IMG_DECLARE(
    ui_img_radio_button_checked_fill0_wght400_grad0_opsz24_png);    // assets/radio_button_checked_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE(
    ui_img_radio_button_partial_fill0_wght400_grad0_opsz24_png);    // assets/radio_button_partial_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE(
    ui_img_radio_button_unchecked_fill0_wght400_grad0_opsz24_png);    // assets/radio_button_unchecked_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE(
    ui_img_sd_card_alert_fill0_wght400_grad0_opsz24_png);    // assets/sd_card_alert_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE(ui_img_wifi_fill0_wght400_grad0_opsz24_png);    // assets/wifi_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE(
    ui_img_battery_horiz_000_fill0_wght400_grad0_opsz24_png);    // assets/battery_horiz_000_FILL0_wght400_GRAD0_opsz24.png


LV_FONT_DECLARE(ui_font_OswaldRegular108p4);
LV_FONT_DECLARE(ui_font_OswaldRegular120p4);
LV_FONT_DECLARE(ui_font_OswaldRegular12p2);
LV_FONT_DECLARE(ui_font_OswaldRegular12p4);
LV_FONT_DECLARE(ui_font_OswaldRegular24p4);
LV_FONT_DECLARE(ui_font_OswaldRegular30p4);
LV_FONT_DECLARE(ui_font_OswaldRegular36p4);
LV_FONT_DECLARE(ui_font_OswaldRegular48p4);
LV_FONT_DECLARE(ui_font_OswaldRegular84p4);
LV_FONT_DECLARE(ui_font_OswaldRegular108p2);
LV_FONT_DECLARE(ui_font_OswaldRegular108p1);
LV_FONT_DECLARE(ui_font_OswaldRegular120p1);
LV_FONT_DECLARE(ui_font_OswaldRegular120p2);
LV_FONT_DECLARE(ui_font_OswaldRegular84p1);
LV_FONT_DECLARE(ui_font_OswaldRegular84p2);
LV_FONT_DECLARE(ui_font_OswaldRegular48p2);
LV_FONT_DECLARE(ui_font_OswaldRegular48p1);
LV_FONT_DECLARE(ui_font_OswaldRegular24p1);
LV_FONT_DECLARE(ui_font_OswaldRegular24p2);
LV_FONT_DECLARE(ui_font_OswaldRegular30p2);
LV_FONT_DECLARE(ui_font_OswaldRegular30p1);
LV_FONT_DECLARE(ui_font_OswaldRegular36p1);
LV_FONT_DECLARE(ui_font_OswaldRegular36p2);
LV_FONT_DECLARE(ui_font_MaterialIsymbolOutlined24p4);
LV_FONT_DECLARE(ui_font_MaterialIsymbolOutlined14p4);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif