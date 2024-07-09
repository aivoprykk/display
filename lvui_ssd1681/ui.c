// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: squareline_proj_2_13_01

#include "ui.h"
#include "ui_helpers.h"
#include "../display_private.h"

///////////////////// VARIABLES ////////////////////

static const char *TAG = "ui_ssd1680";

// SCREEN: ui_SpeedScreen
void ui_SpeedScreen_screen_init(void);
//lv_obj_t *ui_SpeedScreen = 0;


// SCREEN: ui_InfoScreen
void ui_InfoScreen_screen_init(void);
//lv_obj_t *ui_InfoScreen = 0;

// SCREEN: ui_InitScreen
void ui_InitScreen_screen_init(void);
//lv_obj_t *ui_InitScreen = 0;


// SCREEN: ui_StatsScreen
void ui_StatsScreen_screen_init(int rows, int cols);
//lv_obj_t *ui_StatsScreen = 0;

// SCREEN: ui_SleepScreen
void ui_SleepScreen_screen_init(void);
//lv_obj_t *ui_SleepScreen = 0;

lv_obj_t *ui____initial_actions0;

void ui_init( void )
{
    ui_common_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    // lv_disp_load_scr( ui_SpeedScreen);
}

void ui_deinit() {
    if(ui____initial_actions0)
        lv_obj_del(ui____initial_actions0);
    ui_common_deinit();
}

#if defined(USE_2BPP_FONT)
const lv_font_t * ui_status_font_default = &ui_font_OswaldRegular20p2;
#else
const lv_font_t * ui_status_font_default = &ui_font_OswaldRegular20p4;
#endif

void ui_status_panel_init(ui_screen_t *parent) {
    ILOG(TAG, "[%s]", __func__);
    if ( ui_status_panel.self != NULL)
        return;
#if defined(STATUS_PANEL_V1)
    ui_status_panel_create(parent->status_cnt);
#else
    ui_status_panel.self = lv_statusbar_create(parent->status_cnt);
#endif
    lv_obj_t * obj = ui_status_panel.self;
    lv_obj_set_x(obj, 0);
    lv_obj_set_y(obj, 0);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(obj, lv_color_hex(0x0D0D0D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0x0D0D0D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, parent->status_font ? parent->status_font : ui_status_font_default, LV_PART_MAIN | LV_STATE_DEFAULT);
}

#if (CONFIG_DISPLAY_LOG_LEVEL<=1 || defined(DEBUG))
static void print_lv_mem_mon() {
    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    printf("used: %6lu (%3hhu %%), frag: %3hhu %%, biggest free: %6d\n", mon.total_size - mon.free_size,
            mon.used_pct,
            mon.frag_pct,
            (int)mon.free_biggest_size);
}
#else
#define print_lv_mem_mon() do{}while(0)
#endif

void loadSleepScreen() {
    ILOG(TAG, "[%s]", __func__);
    if (ui_sleep_screen.screen.self == 0) {
#if defined(USE_2BPP_FONT)
        ui_sleep_screen.font.normal = &ui_font_OpenSansSemiBold16p2;
        ui_sleep_screen.font.title = &ui_font_SFDistantGalaxyRegular16p2;
        ui_sleep_screen.screen.status_font = &ui_font_OswaldRegular14p2;
#else
        ui_sleep_screen.font.normal = &ui_font_OpenSansSemiBold16p4;
        ui_sleep_screen.font.title = &ui_font_SFDistantGalaxyRegular16p4;
        ui_sleep_screen.screen.status_font = &ui_font_OswaldRegular14p4;
#endif
    }
    ui_SleepScreen_screen_init();
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_sleep_screen.screen.self){
        lv_scr_load(ui_sleep_screen.screen.self);
    }
    print_lv_mem_mon();
}

void loadInfoScreen() {
    ILOG(TAG, "[%s]", __func__);
    if (ui_info_screen.screen.self == 0) {
#if defined(USE_2BPP_FONT)
        ui_info_screen.font.title = &ui_font_OswaldRegular24p2;
        ui_info_screen.font.info = &ui_font_OswaldRegular16p2;
#else
        ui_info_screen.font.title = &ui_font_OswaldRegular24p4;
        ui_info_screen.font.info = &ui_font_OswaldRegular16p4;
#endif
    }
    ui_InfoScreen_screen_init();
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_info_screen.screen.self){
        lv_scr_load(ui_info_screen.screen.self);
    }
    print_lv_mem_mon();
}

void loadInitScreen() {
    ILOG(TAG, "[%s]", __func__);
    if (ui_init_screen.screen.self == 0) {
#if defined(USE_2BPP_FONT)
        ui_init_screen.font.title = &ui_font_OswaldRegular24p2;
#else
        ui_init_screen.font.title = &ui_font_OswaldRegular24p4;
#endif
    }
    ui_InitScreen_screen_init();
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_init_screen.screen.self){
        lv_scr_load(ui_init_screen.screen.self);
    }
    print_lv_mem_mon();
}

void loadRecordScreen() {
    ILOG(TAG, "[%s]", __func__);
    if (ui_record_screen.screen.self == 0) {
#if defined(USE_2BPP_FONT)
        ui_record_screen.font.info = &ui_font_OswaldRegular20p2;
        ui_record_screen.font.title = &ui_font_OpenSansBold28p2;
#else
        ui_record_screen.font.info = &ui_font_OswaldRegular20p4;
        ui_record_screen.font.title = &ui_font_OpenSansBold28p4;
#endif
    }
    ui_RecordScreen_screen_init();
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_record_screen.screen.self){
        lv_scr_load(ui_record_screen.screen.self);
    }
    print_lv_mem_mon();
}

void loadSpeedScreen() {
    ILOG(TAG, "[%s]", __func__);
    if (ui_speed_screen.screen.self == 0) {
#if defined(USE_2BPP_FONT)
        ui_speed_screen.font.main = &ui_font_OpenSansBold84p2;
        ui_speed_screen.font.title = &ui_font_OpenSansBold36p2;
        ui_speed_screen.font.info = &ui_font_OswaldRegular16p2;
        ui_speed_screen.screen.status_font = &ui_font_OswaldRegular14p2;
#else
        ui_speed_screen.font.main = &ui_font_OpenSansBold84p4;
        ui_speed_screen.font.title = &ui_font_OpenSansBold36p4;
        ui_speed_screen.font.info = &ui_font_OswaldRegular16p4;
        ui_speed_screen.screen.status_font = &ui_font_OswaldRegular14p4;
#endif
    }
    ui_SpeedScreen_screen_init();
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_speed_screen.screen.self){
        lv_scr_load(ui_speed_screen.screen.self);
    }
    print_lv_mem_mon();
}

void loadStatsScreen(int rows, int cols) {
    ILOG(TAG, "[%s]", __func__);
    if (ui_stats_screen.screen.self == 0) {
#if defined(USE_2BPP_FONT)
        ui_stats_screen.font.title_small = &ui_font_OpenSansBold24p2;
        ui_stats_screen.font.title = &ui_font_OpenSansBold28p2;
        ui_stats_screen.font.title_big = &ui_font_OpenSansBold60p2;
        ui_stats_screen.font.info = &ui_font_OswaldRegular16p2;
#else
        ui_stats_screen.font.title_small = &ui_font_OpenSansBold24p4;
        ui_stats_screen.font.title = &ui_font_OpenSansBold28p4;
        ui_stats_screen.font.title_big = &ui_font_OpenSansBold60p4;
        ui_stats_screen.font.info = &ui_font_OswaldRegular16p4;
#endif
    }
    ui_StatsScreen_screen_init(rows, cols);
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_stats_screen.screen.self){
        lv_scr_load(ui_stats_screen.screen.self);
    }
    print_lv_mem_mon();
}

void showSleepScreen() {
    loadSleepScreen();
}

void showRecordScreen() {
    loadRecordScreen();
}


void showLowBatScreen() {
    loadInitScreen();
    lv_obj_t* img = ui_init_screen.init_img;
    const lv_img_dsc_t *img_src = &battery_horiz_bold_48px;
    if(lv_img_get_src(img) != img_src) {
        lv_img_set_src(img, img_src);
        lv_obj_set_style_img_recolor(img, lv_color_hex(0xEECE44), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor_opa(img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_y(img, lv_pct(-5));
        lv_obj_add_flag(ui_init_screen.init_lbl, LV_OBJ_FLAG_HIDDEN);
    }
}

void showPushScreen(int push) {
    loadInitScreen();
    lv_obj_t* img = ui_init_screen.init_img;
    const lv_img_dsc_t *img_src = push==1 ? &ui_img_radio_button_partial_fill0_wght400_grad0_opsz24_png : push==2 ? &ui_img_radio_button_checked_fill0_wght400_grad0_opsz24_png : &ui_img_radio_button_unchecked_fill0_wght400_grad0_opsz24_png;
    if(lv_img_get_src(img) != img_src) {
        lv_img_set_src(img, img_src);
        lv_obj_set_y(img, lv_pct(-5));
        lv_obj_add_flag(ui_init_screen.init_lbl, LV_OBJ_FLAG_HIDDEN);
    }
}

void showGpsTroubleScreen() {
    loadInitScreen();
    lv_obj_t* img = ui_init_screen.init_img;
    const lv_img_dsc_t *img_src = &near_me_disabled_bold_48px;
    if(lv_img_get_src(img) != img_src) {
        lv_img_set_src(img, img_src);
        lv_obj_set_y(img, lv_pct(-10));
        lv_obj_clear_flag(ui_init_screen.init_lbl, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_init_screen.init_lbl, "GPS Failure");
    }
}

void showSdTroubleScreen() {
    loadInitScreen();
    lv_obj_t* img = ui_init_screen.init_img;
    const lv_img_dsc_t *img_src = &sd_trouble_bold_48px;
    if(lv_img_get_src(img) != img_src) {
        lv_img_set_src(img, img_src);
        lv_obj_set_y(img, lv_pct(-10));
        lv_obj_clear_flag(ui_init_screen.init_lbl, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_init_screen.init_lbl, "SD Failure");
    }
}

void showSaveSessionScreen() {
    loadInitScreen();
    lv_obj_t* img = ui_init_screen.init_img;
    const lv_img_dsc_t *img_src = &save_bold_48px;
    if(lv_img_get_src(img) != img_src) {
        lv_img_set_src(img, img_src);
        lv_obj_set_y(img, lv_pct(-10));
        lv_obj_clear_flag(ui_init_screen.init_lbl, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_init_screen.init_lbl, "Save Session");
    }
}

void showBootScreen(const char* title) {
    loadInitScreen();
    lv_obj_t* img = ui_init_screen.init_img;
    const lv_img_dsc_t *img_src = &espidf_logo_v2_48px;
    if(lv_img_get_src(img) != img_src) {
        lv_img_set_src(img, img_src);
    }
    if (title){
        if(lv_obj_has_flag(ui_init_screen.init_lbl, LV_OBJ_FLAG_HIDDEN))
            lv_obj_clear_flag(ui_init_screen.init_lbl, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_y(img, lv_pct(-10));
    } else {
        if(!lv_obj_has_flag(ui_init_screen.init_lbl, LV_OBJ_FLAG_HIDDEN))
            lv_obj_add_flag(ui_init_screen.init_lbl, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_y(img, lv_pct(-5));
    }
    const char *lbl_txt = lv_label_get_text(ui_init_screen.init_lbl);
    if(title && (!lbl_txt || (lbl_txt && strcmp(lbl_txt, title) != 0)))
        lv_label_set_text(ui_init_screen.init_lbl, title);
}

void showWifiScreen(const char * title, const char * info) {
    loadInfoScreen();
    lv_obj_t* img = ui_info_screen.info_img;
    const lv_img_dsc_t *img_src = &wifi_bold_48px;
    if(lv_img_get_src(img) != img_src) {
        lv_img_set_src(img, img_src);
        if(lv_img_get_angle(img) != 0)
            lv_img_set_angle(img, 0);
    }
    const char *lbl_txt = lv_label_get_text(ui_info_screen.info_lbl);
    if(title && (!lbl_txt || (lbl_txt && strcmp(lbl_txt, title) != 0)))
        lv_label_set_text(ui_info_screen.info_lbl, title);
    lbl_txt = lv_label_get_text(ui_info_screen.info_secondary_lbl);
    if(title && (!lbl_txt || (lbl_txt && strcmp(lbl_txt, title) != 0)))
        lv_label_set_text(ui_info_screen.info_secondary_lbl, info);
}

void showGpsScreen(const char* title, const char* info, const lv_img_dsc_t *img_src, int angle) {
    loadInfoScreen();
    lv_obj_t* img = ui_info_screen.info_img;
    if(!img_src)
        img_src = &near_me_bold_48px;
    if(lv_img_get_src(img) != img_src) {
        lv_img_set_src(img, img_src);
    }
    if(lv_img_get_angle(img) != angle)
        lv_img_set_angle(img, angle);
    const char *lbl_txt = lv_label_get_text(ui_info_screen.info_lbl);
    if(title && (!lbl_txt || (lbl_txt && strcmp(lbl_txt, title) != 0)))
        lv_label_set_text(ui_info_screen.info_lbl, title);
    lbl_txt = lv_label_get_text(ui_info_screen.info_secondary_lbl);
    if(title && (!lbl_txt || (lbl_txt && strcmp(lbl_txt, title) != 0)))
        lv_label_set_text(ui_info_screen.info_secondary_lbl, info);
}

void showSpeedScreen() {
    loadSpeedScreen();
}

void showStatsScreen12() {
    loadStatsScreen(2,102);
}

void showStatsScreen22() {
    loadStatsScreen(2,2);
}

void showStatsScreen32() {
    loadStatsScreen(3,2);
}
