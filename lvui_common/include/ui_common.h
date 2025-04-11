#ifndef F0ECA8C3_6869_4ED6_A941_F279E95283B9
#define F0ECA8C3_6869_4ED6_A941_F279E95283B9

#ifdef __cplusplus
extern "C" {
#endif

#include "sdkconfig.h"

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#include <string.h>

#include "ui_events.h"

#define STATUS_PANEL_V1 1
#if defined(STATUS_PANEL_V1)
typedef struct ui_status_panel_s {
    struct ui_screen_s *parent;
    lv_obj_t *self;
    lv_obj_t *time_label;
    lv_obj_t *temp_label;
    lv_obj_t *gps_image;
    // lv_obj_t *sdcard_image;
    lv_obj_t *bat_image;
    lv_obj_t *bat_label;
    // lv_obj_t *left_panel;
    // lv_obj_t *right_panel;
    uint8_t viewmode;
} ui_status_panel_t;
#else
#include "lv_comp_statusbar.h"
#endif

typedef struct ui_cell_s {
    lv_obj_t * self;
    lv_obj_t * info;
    lv_obj_t * title;
} ui_cell_t;

typedef struct ui_screen_s {
    lv_obj_t *self;
    lv_obj_t *main_cnt;
    int8_t main_cnt_offset;
    lv_obj_t *status_cnt;
    bool has_status_cnt;
    const lv_font_t *status_font;
    const lv_font_t *status_font_portrait;
    uint8_t status_viewmode;
    void (*init)(struct ui_screen_s*);
    void (*show)(struct ui_screen_s*);
    void (*unload)(void);
    void (*update_dims)(void);
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
    lv_obj_t *top;
    struct {
        const lv_font_t *main;
        const lv_font_t *main_portrait;
        const lv_font_t *info;
        const lv_font_t *title;
        const lv_font_t *title_portrait;
    } font;
} ui_speed_screen_t;

typedef struct ui_info_screen_s {
    ui_screen_t screen;
    lv_obj_t *info_lbl;
    lv_obj_t *info_secondary_lbl;
    lv_obj_t *info_third_lbl;
    lv_obj_t *info_img;
    uint8_t info_screen_mode;
    struct {
        const lv_font_t *info;
        const lv_font_t *title;
    } font;
} ui_info_screen_t;

typedef struct ui_init_screen_s {
    ui_screen_t screen;
    lv_obj_t *init_lbl;
    lv_obj_t *init_img;
    uint8_t init_screen_mode;
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

typedef struct ui_blank_screen_s {
    ui_screen_t screen;
    uint8_t invert;
} ui_blank_screen_t;

#if defined(STATUS_PANEL_V1)
extern ui_status_panel_t ui_status_panel;
#endif
extern ui_sleep_screen_t ui_sleep_screen;
extern ui_speed_screen_t ui_speed_screen;
extern ui_info_screen_t ui_info_screen;
extern ui_init_screen_t ui_init_screen;
extern ui_stats_screen_t ui_stats_screen;
extern ui_record_screen_t ui_record_screen;
extern ui_blank_screen_t ui_blank_screen;

lv_obj_t * ui_common_screen_init(ui_screen_t * screen);

LV_IMG_DECLARE( near_me_bold_48px);
LV_IMG_DECLARE( near_me_disabled_bold_48px);
LV_IMG_DECLARE( wifi_bold_48px);
LV_IMG_DECLARE( save_bold_48px);
LV_IMG_DECLARE( sd_trouble_bold_48px);
LV_IMG_DECLARE( battery_horiz_bold_48px);
LV_IMG_DECLARE( settings_48px);
LV_IMG_DECLARE( update_48px);
LV_IMG_DECLARE( radio_button_checked_24px);
LV_IMG_DECLARE( radio_button_partial_24px);
LV_IMG_DECLARE( radio_button_unchecked_24px);

LV_IMG_DECLARE( espidf_logo_v2_48px);

//sail logos
LV_IMG_DECLARE( ga_logo_n_48px);
LV_IMG_DECLARE( duotone_48px);
LV_IMG_DECLARE( np_48px);
LV_IMG_DECLARE( loftsails_48px);
LV_IMG_DECLARE( gunsails_48px);
LV_IMG_DECLARE( p7_black_48px);
LV_IMG_DECLARE( ns_48px);
LV_IMG_DECLARE( patrik_48px);

extern const lv_img_dsc_t * const sail_logo_img [];

// board logos
LV_IMG_DECLARE( sb_48px);
LV_IMG_DECLARE( fanatic_48px);
LV_IMG_DECLARE( jp_48px);

extern const lv_img_dsc_t * const board_logo_img [];

#define USE_2BPP_FONT 1

#if defined(USE_2BPP_FONT)

LV_FONT_DECLARE(ui_font_OswaldRegular14p2); // sleep screen
LV_FONT_DECLARE(ui_font_OswaldRegular16p2);
LV_FONT_DECLARE(ui_font_OswaldRegular20p2); // statusbar
LV_FONT_DECLARE(ui_font_OswaldRegular24p2);
LV_FONT_DECLARE(ui_font_OswaldRegular36p2);

#if defined (CONFIG_SSD168X_PANEL_SSD1681)
LV_FONT_DECLARE(ui_font_OpenSansBold30p2);
#elif !defined(CONFIG_LCD_IS_EPD)
LV_FONT_DECLARE(ui_font_OswaldRegular48p2); // speed top row, record screen
LV_FONT_DECLARE(ui_font_OswaldRegular100p2); // speed big
#else
LV_FONT_DECLARE(ui_font_OpenSansBold24p2);
LV_FONT_DECLARE(ui_font_OpenSansBold28p2);
#endif
#if !defined(CONFIG_SSD168X_PANEL_SSD1681)
LV_FONT_DECLARE(ui_font_OswaldRegular60p2); // speed big
#endif
#if defined(CONFIG_LCD_IS_EPD)
LV_FONT_DECLARE(ui_font_OpenSansBold36p2); // record screen
LV_FONT_DECLARE(ui_font_OpenSansBold60p2);
#endif


#if defined (CONFIG_SSD168X_PANEL_SSD1681)
LV_FONT_DECLARE(ui_font_OswaldRegular96p2);
#else
LV_FONT_DECLARE(ui_font_OpenSansBold84p2);
#endif

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
LV_FONT_DECLARE(ui_font_OpenSansBold32p4);
LV_FONT_DECLARE(ui_font_OpenSansBold60p4);
#if defined (CONFIG_SSD168X_PANEL_SSD1681)
LV_FONT_DECLARE(ui_font_OswaldRegular96p4);
#else
LV_FONT_DECLARE(ui_font_OpenSansBold84p4);
#endif

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
void ui_status_panel_rearrange(ui_screen_t *parent);
void ui_status_panel_init(ui_screen_t * parent);
void ui_status_panel_load(ui_screen_t *parent);
void ui_status_panel_delete(void);
void ui_status_panel_update();
void ui_status_panel_update_dims(ui_screen_t *parent);

// SCREEN: ui_SpeedScreen
int ui_SpeedScreen_screen_init(void);

// SCREEN: ui_InfoScreen
int ui_InfoScreen_screen_init(void);

// SCREEN: ui_InitScreen
int ui_InitScreen_screen_init(void);

// SCREEN: ui_RecordScreen
void ui_RecordScreen_screen_init(void);

// SCREEN: ui_StatsScreen
void ui_StatsScreen_screen_init(int rows, int cols);

// SCREEN: ui_SleepScreen
void ui_SleepScreen_screen_init(void);

void ui_BlankScreen_screen_init(void);

void loadSleepScreen();

typedef enum info_scr_mode_e {
    INFO_MODE_NONE = 0,
    INFO_MODE_GPS,
    INFO_MODE_WIFI,
    INFO_MODE_FW_UPDATE,
    INFO_MODE_SETTINGS,
    INFO_MODE_SAVE_SESSION,
} info_scr_mode_t;

int loadInfoScreen(info_scr_mode_t mode);
int set_label_text_safe(lv_obj_t * lbl, const char * title, uint8_t enable_hide_lbl);
int set_screen_img(lv_obj_t * scr, const lv_img_dsc_t *img_src, uint16_t angle);
int invert_colors(lv_obj_t * panel, bool invert);
void loadRecordScreen();

typedef enum init_scr_mode_e {
    INIT_MODE_NONE = 0,
    INIT_MODE_BOOT,
    INIT_MODE_SHUTDOWN,
    INIT_MODE_PUSH_BUTTON,
    INIT_MODE_LOW_BAT,
    INIT_MODE_SD_TROUBLE,
    INIT_MODE_GPS_TROUBLE,
} init_scr_mode_t;

int loadInitScreen(init_scr_mode_t mode);
int loadSpeedScreen(void);
void loadStatsScreen(int rows, int cols);
void loadBlankScreen(uint8_t invert);

void showFwUpdateScreen(const char * title, const char * info, const char * desc);
void showSleepScreen(void);
void showLowBatScreen(const char * title);
int showWifiScreen(void);
void showBootScreen(const char * title);
int showGpsScreen(uint16_t angle);
void showGpsTroubleScreen();
void showSdTroubleScreen();
void showSaveSessionScreen(const char * title, const char * info, const char * desc);
int showSpeedScreen();
void showStatsScreen();
void showStatsScreen12();
void showStatsScreen22();
void showStatsScreen32();
void showPushScreen(int push, const char * title);
void showRecordScreen(bool invert_colors);
void showSettingsScreen(const char * title, const char * info, const char * desc);
void showBlankScreen(uint8_t invert);

void ui_flush_screens(ui_screen_t * screen);
void ui_invalidate_screens(void);
void ui_uninit_screens(void);

void ui_set_main_cnt_offset(ui_screen_t * screen, int8_t off);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* F0ECA8C3_6869_4ED6_A941_F279E95283B9 */
