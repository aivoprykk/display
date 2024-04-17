// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: squareline_proj_1_54_02

#ifndef _SQUARELINE_PROJ_1_54_02_UI_H
#define _SQUARELINE_PROJ_1_54_02_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ui_common.h"
#include "ui_themes.h"

// SCREEN: ui_SpeedScreen
void ui_SpeedScreen_screen_init(void);
extern lv_obj_t *ui_SpeedScreen;
extern lv_obj_t *ui_SpeedSecondaryPanel;
extern lv_obj_t *ui_LeftPanel;
extern lv_obj_t *ui_RightPanel;
extern lv_obj_t *ui_SpeedStatusPanelWrapper;
extern lv_obj_t *ui_SpeedStatusPanel;
extern lv_obj_t *ui_SpeedMainPanel;
extern lv_obj_t *ui_SpeedBar;
// SCREEN: ui_StatsScreen
void ui_StatsScreen_screen_init(void);
extern lv_obj_t *ui_StatsScreen;
extern lv_obj_t *ui_StatsStatusPanelWrapper;
extern lv_obj_t *ui_StatsStatusPanel;
extern lv_obj_t *ui_StatsPanel2Row;
extern lv_obj_t *ui_Stats2Row1Panel1;
extern lv_obj_t *ui_Stats2Row1FullPanel;
extern lv_obj_t *ui_Stats2Row2Panel;
extern lv_obj_t *ui_Stats2Row2LeftPanel;
extern lv_obj_t *ui_Stats2Row2RightPanel;
extern lv_obj_t *ui_StatsPanel3Row;

// extern lv_obj_t *ui_Stats3Row1Panel;
// extern lv_obj_t *ui_Stats3Row1FullPanel;
// extern lv_obj_t *ui_Stats3Row2Panel;
// extern lv_obj_t *ui_Stats3Row2FullPanel;
// extern lv_obj_t *ui_Stats3Row3Panel;
// extern lv_obj_t *ui_Stats3Row3LeftPanel;
// extern lv_obj_t *ui_Stats3Row3RightPanel;

extern lv_obj_t *ui_Stats3Row1Panel;
extern lv_obj_t *ui_Stats3Row1LeftPanel;
extern lv_obj_t *ui_Stats3Row1RightPanel;
extern lv_obj_t *ui_Stats3Row2Panel;
extern lv_obj_t *ui_Stats3Row2LeftPanel;
extern lv_obj_t *ui_Stats3Row2RightPanel;
extern lv_obj_t *ui_Stats3Row3Panel;
extern lv_obj_t *ui_Stats3Row3LeftPanel;
extern lv_obj_t *ui_Stats3Row3RightPanel;

// extern lv_obj_t *ui_StatsPanel4Row;
// extern lv_obj_t *ui_Stats4Row1Panel;
// extern lv_obj_t *ui_Stats4Row1FullPanel;
// extern lv_obj_t *ui_Stats4Row2Panel;
// extern lv_obj_t *ui_Stats4Row2LeftPanel;
// extern lv_obj_t *ui_Stats4Row2RightPanel;
// extern lv_obj_t *ui_Stats4Row3Panel;
// extern lv_obj_t *ui_Stats4Row3LeftPanel;
// extern lv_obj_t *ui_Stats4Row3RightPanel;
// extern lv_obj_t *ui_Stats4Row4Panel;
// extern lv_obj_t *ui_Stats4Row4LeftPanel;
// extern lv_obj_t *ui_Stats4Row4RightPanel;
// extern lv_obj_t *ui_StatsPanel4Row2;
// extern lv_obj_t *ui_Stats4Row1Panel2;
// extern lv_obj_t *ui_Stats4Row1FullPanel2;
// extern lv_obj_t *ui_Stats4Row2Panel2;
// extern lv_obj_t *ui_Stats4Row2FullPanel2;
// extern lv_obj_t *ui_Stats4Row3Panel2;
// extern lv_obj_t *ui_Stats4Row3LeftPanel2;
// extern lv_obj_t *ui_Stats4Row3RightPanel2;
// extern lv_obj_t *ui_Stats4Row4Panel2;
// extern lv_obj_t *ui_Stats4Row4LeftPanel2;
// extern lv_obj_t *ui_Stats4Row4RightPanel2;
// extern lv_obj_t *ui_StatsPanel5Row;
// extern lv_obj_t *ui_Stats5Row1Panel;
// extern lv_obj_t *ui_Stats5Row1LeftPanel;
// extern lv_obj_t *ui_Stats5Row1RightPanel;
// extern lv_obj_t *ui_Stats5Row2Panel;
// extern lv_obj_t *ui_Stats5Row2LeftPanel;
// extern lv_obj_t *ui_Stats5Row2RightPanel;
// extern lv_obj_t *ui_Stats5Row3Panel;
// extern lv_obj_t *ui_Stats5Row3LeftPanel;
// extern lv_obj_t *ui_Stats5Row3RightPanel;
// extern lv_obj_t *ui_Stats5Row4Panel;
// extern lv_obj_t *ui_Stats5Row4LeftPanel;
// extern lv_obj_t *ui_Stats5Row4RightPanel;
// extern lv_obj_t *ui_Stats5Row5Panel;
// extern lv_obj_t *ui_Stats5Row5LeftPanel;
// extern lv_obj_t *ui_Stats5Row5RightPanel;
// SCREEN: ui_InfoScreen
void ui_InfoScreen_screen_init(void);
extern lv_obj_t *ui_InfoScreen;
extern lv_obj_t *ui_InfoStatusPanelWrapper;
extern lv_obj_t *ui_InfoStatusPanel;
extern lv_obj_t *ui_InfoMainPanel;
extern lv_obj_t *ui_MainImage;
extern lv_obj_t *ui_MainLabel;
extern lv_obj_t *ui_MainLowerLabel;
extern lv_obj_t *ui_InfoInitPanel;
extern lv_obj_t *ui_InitImage;
extern lv_obj_t *ui_InitLabel;
extern lv_obj_t *ui____initial_actions0;

LV_IMG_DECLARE( ui_img_sd_card_fill0_wght400_grad0_opsz24_png);   // assets/sd_card_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE( ui_img_wifi_fill0_wght400_grad0_opsz24_png);   // assets/wifi_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE( ui_img_near_me_fill0_wght400_grad0_opsz24_png);   // assets/near_me_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE( ui_img_2129950171);   // assets/esp-gps-logo-v2-100px.png
LV_IMG_DECLARE( ui_img_battery_horiz_000_fill0_wght400_grad0_opsz24_png);   // assets/battery_horiz_000_FILL0_wght400_GRAD0_opsz24.png
//LV_IMG_DECLARE( ui_img_navigation_fill0_wght400_grad0_opsz24_png);   // assets/navigation_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE( ui_img_radio_button_checked_fill0_wght400_grad0_opsz24_png);   // assets/radio_button_checked_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE( ui_img_radio_button_partial_fill0_wght400_grad0_opsz24_png);   // assets/radio_button_partial_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE( ui_img_radio_button_unchecked_fill0_wght400_grad0_opsz24_png);   // assets/radio_button_unchecked_FILL0_wght400_GRAD0_opsz24.png


// LV_FONT_DECLARE( ui_font_OpenSansBold16p2);
// LV_FONT_DECLARE( ui_font_OpenSansBold16p4);
// LV_FONT_DECLARE( ui_font_OpenSansBold24p2);
// LV_FONT_DECLARE( ui_font_OpenSansBold24p4);
// LV_FONT_DECLARE( ui_font_OpenSansBold30p2);
// LV_FONT_DECLARE( ui_font_OpenSansBold30p4);
// LV_FONT_DECLARE( ui_font_OpenSansBold36p2);
// LV_FONT_DECLARE( ui_font_OpenSansBold40p4);
// LV_FONT_DECLARE( ui_font_OpenSansBold48p4);
// LV_FONT_DECLARE( ui_font_OpenSansBold60p2);
// LV_FONT_DECLARE( ui_font_OpenSansBold72p2);
// LV_FONT_DECLARE( ui_font_OpenSansBold78p2);
// LV_FONT_DECLARE( ui_font_OpenSansBold80p2);
// LV_FONT_DECLARE( ui_font_OpenSansRegular24p2);
// LV_FONT_DECLARE( ui_font_OpenSansRegular36p2);
// LV_FONT_DECLARE( ui_font_OswaldRegular12p2);
LV_FONT_DECLARE( ui_font_OswaldRegular14p2);
//LV_FONT_DECLARE( ui_font_OswaldRegular16p2);
LV_FONT_DECLARE( ui_font_OswaldRegular16p4);
LV_FONT_DECLARE( ui_font_OswaldRegular24p2);
// LV_FONT_DECLARE( ui_font_OswaldRegular24p4);
LV_FONT_DECLARE( ui_font_OswaldRegular30p4);
// LV_FONT_DECLARE( ui_font_OswaldRegular36p2);
LV_FONT_DECLARE( ui_font_OswaldRegular40p2);
//LV_FONT_DECLARE( ui_font_OswaldRegular40p4);
// LV_FONT_DECLARE( ui_font_OswaldRegular48p2);
// LV_FONT_DECLARE( ui_font_OswaldRegular48p4);
//LV_FONT_DECLARE( ui_font_OswaldRegular60p2);
//LV_FONT_DECLARE( ui_font_OswaldRegular72p2);
LV_FONT_DECLARE( ui_font_OswaldRegular80p2);
// LV_FONT_DECLARE( ui_font_OswaldRegular80p4);
// LV_FONT_DECLARE( ui_font_OswaldRegular84p2);
// LV_FONT_DECLARE( ui_font_OswaldRegular96p2);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
