#ifndef F0ECA8C3_6869_4ED6_A941_F279E95283B9
#define F0ECA8C3_6869_4ED6_A941_F279E95283B9

#include "lvgl.h"
#include "sdkconfig.h"

#include "ui_events.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STATUS_PANEL_V1 1
#if defined(STATUS_PANEL_V1)
typedef struct ui_status_panel_s {
    struct ui_screen_s *parent;
    lv_obj_t *self;
    lv_obj_t *time_label;
    lv_obj_t *temp_label;
    lv_obj_t *gps_image;
    lv_obj_t *sdcard_image;
    lv_obj_t *bat_image;
    lv_obj_t *bat_label;
    lv_obj_t *left_panel;
    lv_obj_t *right_panel;
    uint8_t viewmode;
} ui_status_panel_t;
#else
#include "lv_comp_statusbar.h"
#endif

typedef struct ui_cell_s {
    lv_obj_t * info;
    lv_obj_t * title;
} ui_cell_t;

typedef struct ui_screen_s {
    lv_obj_t *self;
    lv_obj_t *main_cnt;
    lv_obj_t *status_cnt;
    bool has_status_cnt;
    const lv_font_t *status_font;
    uint8_t status_viewmode;
    void (*init)(struct ui_screen_s*);
    void (*show)(struct ui_screen_s*);
    void (*unload)(void);
    lv_obj_t *(*load)(lv_obj_t *parent);
} ui_screen_t;

typedef struct ui_sleep_screen_s {
    ui_screen_t screen;
    ui_cell_t cells[6][2]; // rows x cols
    lv_obj_t *myid;
    lv_obj_t *up_img;
    lv_obj_t *bottom_img;
    struct {
        const lv_font_t *main;
        const lv_font_t *normal;
        const lv_font_t *title;
    } font;
} ui_sleep_screen_t;

typedef struct ui_speed_screen_s {
    ui_screen_t screen;
    ui_cell_t cells[1][2]; // rows x cols
    lv_obj_t *speed;
    lv_obj_t *bar;
    struct {
        const lv_font_t *main;
        const lv_font_t *info;
        const lv_font_t *title;
    } font;
} ui_speed_screen_t;

typedef struct ui_info_screen_s {
    ui_screen_t screen;
    lv_obj_t *info_lbl;
    lv_obj_t *info_secondary_lbl;
    lv_obj_t *info_img;
    struct {
        const lv_font_t *info;
        const lv_font_t *title;
    } font;
} ui_info_screen_t;

typedef struct ui_init_screen_s {
    ui_screen_t screen;
    lv_obj_t *init_lbl;
    lv_obj_t *init_img;
    struct {
        const lv_font_t *title;
    } font;
} ui_init_screen_t;

typedef struct ui_stats_screen_s {
    ui_screen_t screen;
    ui_cell_t cells[6][3]; // rows x cols
    uint8_t rows;
    uint8_t cols;
    struct {
        const lv_font_t *info;
        const lv_font_t *title_small;
        const lv_font_t *title;
        const lv_font_t *title_big;
    } font;
} ui_stats_screen_t;

typedef struct ui_record_screen_s {
    ui_screen_t screen;
    lv_obj_t *info_lbl;
    lv_obj_t *cur_lbl;
    lv_obj_t *prev_lbl;
    struct {
        const lv_font_t *info;
        const lv_font_t *title;
    } font;
} ui_record_screen_t;

#if defined(STATUS_PANEL_V1)
extern ui_status_panel_t ui_status_panel;
#endif
extern ui_sleep_screen_t ui_sleep_screen;
extern ui_speed_screen_t ui_speed_screen;
extern ui_info_screen_t ui_info_screen;
extern ui_init_screen_t ui_init_screen;
extern ui_stats_screen_t ui_stats_screen;
extern ui_record_screen_t ui_record_screen;

lv_obj_t * ui_common_screen_init(ui_screen_t * screen);

LV_IMG_DECLARE( near_me_bold_48px);
LV_IMG_DECLARE( near_me_disabled_bold_48px);
LV_IMG_DECLARE( wifi_bold_48px);
LV_IMG_DECLARE( save_bold_48px);
LV_IMG_DECLARE( sd_trouble_bold_48px);
LV_IMG_DECLARE( battery_horiz_bold_48px);
LV_IMG_DECLARE( espidf_logo_v2_48px);
LV_IMG_DECLARE( gunsails_48px);
// LV_IMG_DECLARE( jp_48px);
LV_IMG_DECLARE( sb_48px);
// LV_IMG_DECLARE( ui_img_sd_card_fill0_wght400_grad0_opsz24_png);   // assets/sd_card_FILL0_wght400_GRAD0_opsz24.png
// LV_IMG_DECLARE( ui_img_navigation_fill0_wght400_grad0_opsz24_png);   // assets/navigation_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE( ui_img_radio_button_checked_fill0_wght400_grad0_opsz24_png);   // assets/radio_button_checked_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE( ui_img_radio_button_partial_fill0_wght400_grad0_opsz24_png);   // assets/radio_button_partial_FILL0_wght400_GRAD0_opsz24.png
LV_IMG_DECLARE( ui_img_radio_button_unchecked_fill0_wght400_grad0_opsz24_png);   // assets/radio_button_unchecked_FILL0_wght400_GRAD0_opsz24.png

#define USE_2BPP_FONT 1

#if defined(USE_2BPP_FONT)

// LV_FONT_DECLARE(ui_font_OswaldRegular12p2);
LV_FONT_DECLARE(ui_font_OswaldRegular14p2);
LV_FONT_DECLARE(ui_font_OswaldRegular16p2);
LV_FONT_DECLARE(ui_font_OswaldRegular20p2);
LV_FONT_DECLARE(ui_font_OswaldRegular24p2);

// #if defined (CONFIG_DISPLAY_DRIVER_ST7789)

// LV_FONT_DECLARE(ui_font_OswaldRegular36p4);
// LV_FONT_DECLARE(ui_font_OswaldRegular120p4);

// #else

LV_FONT_DECLARE(ui_font_OpenSansBold24p2);
LV_FONT_DECLARE(ui_font_OpenSansBold28p2);
LV_FONT_DECLARE(ui_font_OpenSansBold36p2);
LV_FONT_DECLARE(ui_font_OpenSansBold60p2);
LV_FONT_DECLARE(ui_font_OpenSansBold84p2);

LV_FONT_DECLARE(ui_font_OpenSansSemiBold16p2);

// LV_FONT_DECLARE(ui_font_SFDistantGalaxyRegular14p2);
LV_FONT_DECLARE(ui_font_SFDistantGalaxyRegular16p2);

// #endif

#else

LV_FONT_DECLARE(ui_font_OswaldRegular14p4);
LV_FONT_DECLARE(ui_font_OswaldRegular16p4);
LV_FONT_DECLARE(ui_font_OswaldRegular20p4);
LV_FONT_DECLARE(ui_font_OswaldRegular24p4);

LV_FONT_DECLARE(ui_font_OpenSansBold24p4);
LV_FONT_DECLARE(ui_font_OpenSansBold28p4);
LV_FONT_DECLARE(ui_font_OpenSansBold36p4);
LV_FONT_DECLARE(ui_font_OpenSansBold60p4);
LV_FONT_DECLARE(ui_font_OpenSansBold84p4);

LV_FONT_DECLARE(ui_font_OpenSansSemiBold16p4);

LV_FONT_DECLARE(ui_font_SFDistantGalaxyRegular16p4);


#endif

typedef lv_style_t* lv_style_ptr_t;

// extern const lv_style_t style_plain_panel;

// extern const lv_style_t style_text_small;
// extern const lv_style_t style_text_normal;
// extern const lv_style_t style_text_large;

// extern const lv_style_t style_text_bigger;
// extern const lv_style_t style_text_morebigger;
// extern const lv_style_t style_text_biggest;

// extern const lv_style_t style_text_oswald_regular_20;
// extern const lv_style_t style_text_oswald_regular_24;
// extern const lv_style_t style_text_monserrat_16;

// extern const lv_style_t style_border_none;
// extern const lv_style_t style_border_bottom;
// // extern const lv_style_t style_border_top;
// extern const lv_style_t style_border_right;
// extern const lv_style_t style_border_full;

// extern lv_style_t style_plain_container;
// extern lv_style_t style_statusbar;
// extern lv_style_t style_speed_big_panel;

// extern lv_obj_t * ui_StatusPanel;
extern const lv_font_t * ui_status_font_default;

void ui_common_deinit();
void ui_common_init(void);
lv_obj_t * ui_common_panel_init(lv_obj_t * parent, uint8_t w, uint8_t h);

lv_obj_t * ui_status_panel_create(lv_obj_t *parent);
void ui_status_panel_init(ui_screen_t * parent);
void ui_status_panel_load(ui_screen_t *parent);
void ui_status_panel_delete(void);
void ui_status_panel_update();

// SCREEN: ui_SpeedScreen
void ui_SpeedScreen_screen_init(void);

// SCREEN: ui_InfoScreen
void ui_InfoScreen_screen_init(void);

// SCREEN: ui_InitScreen
void ui_InitScreen_screen_init(void);

// SCREEN: ui_RecordScreen
void ui_RecordScreen_screen_init(void);

// SCREEN: ui_StatsScreen
void ui_StatsScreen_screen_init(int rows, int cols);

// SCREEN: ui_SleepScreen
void ui_SleepScreen_screen_init(void);

void loadSleepScreen();
void loadInfoScreen();
void loadRecordScreen();
void loadInitScreen();
void loadSpeedScreen();
void loadStatsScreen(int rows, int cols);

void showSleepScreen();
void showLowBatScreen();
void showWifiScreen(const char * title, const char * info);
void showBootScreen(const char * title);
void showGpsScreen(const char * title, const char * info, const lv_img_dsc_t *img_src, int angle);
void showGpsTroubleScreen();
void showSdTroubleScreen();
void showSaveSessionScreen();
void showSpeedScreen();
void showStatsScreen();
void showStatsScreen12();
void showStatsScreen22();
void showStatsScreen32();
void showPushScreen(int push);
void showRecordScreen();
void ui_flush_screens(ui_screen_t * screen);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* F0ECA8C3_6869_4ED6_A941_F279E95283B9 */
