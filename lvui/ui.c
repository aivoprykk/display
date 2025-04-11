#include "ui.h"

#include "../display_private.h"
#include "driver_vendor.h"

///////////////////// VARIABLES ////////////////////

#if defined(CONFIG_DISPLAY_DRIVER_QEMU)
static const char *TAG = "ui_qemu";
#endif
#if defined(CONFIG_DISPLAY_DRIVER_RM67162)
static const char *TAG = "ui_rm67162";
#endif
#ifdef CONFIG_DISPLAY_DRIVER_ST7789
static const char *TAG = "ui_st7789";
#endif
#ifdef CONFIG_SSD168X_PANEL_SSD1680
static const char *TAG = "ui_ssd1680";
#endif
#ifdef CONFIG_SSD168X_PANEL_SSD1681
static const char *TAG = "ui_ssd1681";
#endif


// SCREEN: ui_SpeedScreen
// void ui_SpeedScreen_screen_init(void);
//lv_obj_t *ui_SpeedScreen = 0;


// SCREEN: ui_InfoScreen
// int ui_InfoScreen_screen_init(void);
//lv_obj_t *ui_InfoScreen = 0;

// SCREEN: ui_InitScreen
// void ui_InitScreen_screen_init(void);
//lv_obj_t *ui_InitScreen = 0;


// SCREEN: ui_StatsScreen
// void ui_StatsScreen_screen_init(int rows, int cols);
//lv_obj_t *ui_StatsScreen = 0;

// SCREEN: ui_SleepScreen
// void ui_SleepScreen_screen_init(void);
//lv_obj_t *ui_SleepScreen = 0;

// void ui_BlankScreen_screen_init(void);

lv_obj_t *ui____initial_actions0;

void ui_init( void )
{
    ILOG(TAG, "[%s]", __func__);
    ui_common_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    // lv_disp_load_scr( ui_SpeedScreen);
}

void ui_deinit() {
    ILOG(TAG, "[%s]", __func__);
    if(ui____initial_actions0)
        lv_obj_del(ui____initial_actions0);
    ui_common_deinit();
}

#if defined(USE_2BPP_FONT)
const lv_font_t * ui_status_font_default = &ui_font_OswaldRegular20p2;
const lv_font_t * ui_status_font_default_portrait = &ui_font_OswaldRegular14p2;
#else
const lv_font_t * ui_status_font_default = &ui_font_OswaldRegular20p4;
#endif

void ui_status_panel_rearrange(ui_screen_t *parent) {
    assert(parent);
    ILOG(TAG, "[%s] vm:%hhu", __func__, parent->status_viewmode);
    if (ui_status_panel.self == NULL) return;
    lv_obj_t *l;
    if (parent->status_viewmode == 0)  {
        l = ui_status_panel.temp_label;
        if(lv_obj_has_flag(l, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_clear_flag(l, LV_OBJ_FLAG_HIDDEN);
        }
        l = ui_status_panel.bat_image;
        if(lv_obj_has_flag(l, LV_OBJ_FLAG_HIDDEN)){
            lv_obj_clear_flag(l, LV_OBJ_FLAG_HIDDEN);
        }
    }
    else {
        l = ui_status_panel.temp_label;
        if(!lv_obj_has_flag(l, LV_OBJ_FLAG_HIDDEN))
            lv_obj_add_flag(l, LV_OBJ_FLAG_HIDDEN);
        l = ui_status_panel.bat_image;
        if(!lv_obj_has_flag(l, LV_OBJ_FLAG_HIDDEN))
            lv_obj_add_flag(l, LV_OBJ_FLAG_HIDDEN);
    }
    l = ui_status_panel.gps_image;
    if (parent->status_viewmode == 0 || parent->status_viewmode == 2) {
        if(lv_obj_has_flag(l, LV_OBJ_FLAG_HIDDEN)){
            lv_obj_clear_flag(l, LV_OBJ_FLAG_HIDDEN);
        }
    }
    else {
        if(!lv_obj_has_flag(l, LV_OBJ_FLAG_HIDDEN))
            lv_obj_add_flag(l, LV_OBJ_FLAG_HIDDEN);
    }
    ui_status_panel_update_dims(parent);
}

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
    ui_status_panel_rearrange(parent);
}

void ui_status_panel_update_dims(ui_screen_t *parent) {
#if defined(CONFIG_DISPLAY_DRIVER_ST7789)
    bool is_l = (display_drv_get_width(display_drv_get())>170);
#else
    bool is_l = (display_drv_get_width(display_drv_get())>128);
#endif
    ILOG(TAG, "[%s] l:%hhu", __func__,is_l);
    lv_obj_t *obj = ui_status_panel.self;
    if(obj) {
        if(is_l) { /// landscape || ssd1681
            lv_obj_set_style_text_font(obj, parent->status_font ? parent->status_font : ui_status_font_default, LV_PART_MAIN | LV_STATE_DEFAULT);
            obj = ui_status_panel.gps_image;
            if(obj) {
                if((display_drv_get_width(display_drv_get())>200))
                    lv_obj_set_x(obj, lv_pct(-35));
                else
                    lv_obj_set_x(obj, lv_pct(-38));
            }
            obj = ui_status_panel.bat_image;
            if(obj){
                if((display_drv_get_width(display_drv_get())>200))
                    lv_obj_set_x(obj, lv_pct(-20));
                else
                    lv_obj_set_x(obj, lv_pct(-25));
            }
        } else { /// portrait
            lv_obj_set_style_text_font(obj, parent->status_font_portrait ? parent->status_font_portrait : ui_status_font_default_portrait, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_x(ui_status_panel.gps_image, lv_pct(-50));
            lv_obj_set_x(ui_status_panel.bat_image, lv_pct(-28));
        }
    }
}

#if (C_LOG_LEVEL < 2)
static void print_lv_mem_mon() {
    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
#if LVGL_VERSION_MAJOR < 9
    printf("used: %6lu (%3hhu %%), frag: %3hhu %%, biggest free: %6d\n", mon.total_size - mon.free_size,
#else
    printf("used: %6u (%3u %%), frag: %3u %%, biggest free: %6d\n", mon.total_size - mon.free_size,
#endif
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
        ui_sleep_screen.screen.status_font_portrait = &ui_font_OswaldRegular14p2;
#else
        ui_sleep_screen.font.normal = &ui_font_OpenSansSemiBold16p4;
        ui_sleep_screen.font.title = &ui_font_SFDistantGalaxyRegular16p4;
        ui_sleep_screen.screen.status_font = &ui_font_OswaldRegular14p4;
#endif
    }
    ui_SleepScreen_screen_init();
    // ui_sleep_screen.screen.update_dims();
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_sleep_screen.screen.self){
#if (C_LOG_LEVEL < 3)
            ILOG(TAG, "[%s] load to screen", __func__);
#endif
            lv_scr_load(ui_sleep_screen.screen.self);
    }
    print_lv_mem_mon();
}

int loadInfoScreen(info_scr_mode_t mode) {
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
    int ret = ui_InfoScreen_screen_init();
    // ui_info_screen.screen.update_dims();
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_info_screen.screen.self){
#if (C_LOG_LEVEL < 3)
        ILOG(TAG, "[%s] load to screen", __func__);
#endif
        lv_scr_load(ui_info_screen.screen.self);
        ret = 1;
    }
    if(mode != ui_info_screen.info_screen_mode) {
        ui_info_screen.info_screen_mode = mode;
        ret = 1;
    }
    print_lv_mem_mon();
    return ret;
}

int loadInitScreen(init_scr_mode_t mode) {
    ILOG(TAG, "[%s]", __func__);
    if (ui_init_screen.screen.self == 0) {
#if defined(USE_2BPP_FONT)
        ui_init_screen.font.title = &ui_font_OswaldRegular24p2;
#else
        ui_init_screen.font.title = &ui_font_OswaldRegular24p4;
#endif
    }
    int ret = ui_InitScreen_screen_init();
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_init_screen.screen.self){
#if (C_LOG_LEVEL < 3)
        ILOG(TAG, "[%s] load to screen", __func__);
#endif
        lv_scr_load(ui_init_screen.screen.self);
        ret = 1;
    }
    if(mode != ui_info_screen.info_screen_mode) {
        ui_info_screen.info_screen_mode = mode;
        ret = 1;
    }
    print_lv_mem_mon();
    return ret;
}

void loadRecordScreen() {
    ILOG(TAG, "[%s]", __func__);
    if (ui_record_screen.screen.self == 0) {
#if defined(USE_2BPP_FONT)
        ui_record_screen.font.info = &ui_font_OswaldRegular24p2;
#if !defined(CONFIG_LCD_IS_EPD)
        ui_record_screen.font.title = &ui_font_OswaldRegular48p2;
#else
        ui_record_screen.font.title = &ui_font_OpenSansBold36p2;
#endif
#else
        ui_record_screen.font.info = &ui_font_OswaldRegular24p4;
#if !defined(CONFIG_LCD_IS_EPD)
        ui_record_screen.font.title = &ui_font_OswaldRegular48p4;
#lse
        ui_record_screen.font.title = &ui_font_OpenSansBold36p4;
#endif
#endif
    }
    ui_RecordScreen_screen_init();
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_record_screen.screen.self){
#if (C_LOG_LEVEL < 3)
        ILOG(TAG, "[%s] load to screen", __func__);
#endif
        lv_scr_load(ui_record_screen.screen.self);
    }
    print_lv_mem_mon();
}

int loadSpeedScreen() {
    ILOG(TAG, "[%s]", __func__);
    if (ui_speed_screen.screen.self == 0) {
#if defined(USE_2BPP_FONT)
#ifdef CONFIG_SSD168X_PANEL_SSD1681
        ui_speed_screen.font.main = &ui_font_OswaldRegular96p2;
        ui_speed_screen.font.main_portrait = &ui_font_OswaldRegular96p2;
        ui_speed_screen.font.title = &ui_font_OswaldRegular36p2;
        ui_speed_screen.font.title_portrait = &ui_font_OswaldRegular36p2;
#elif !defined(CONFIG_LCD_IS_EPD)
        ui_speed_screen.font.main = &ui_font_OswaldRegular100p2;
        ui_speed_screen.font.main_portrait = &ui_font_OswaldRegular100p2;
        ui_speed_screen.font.title = &ui_font_OswaldRegular48p2;
        ui_speed_screen.font.title_portrait = &ui_font_OswaldRegular48p2;
#else
        ui_speed_screen.font.main = &ui_font_OpenSansBold84p2;
        ui_speed_screen.font.main_portrait = &ui_font_OswaldRegular60p2;
        ui_speed_screen.font.title = &ui_font_OpenSansBold36p2;
        ui_speed_screen.font.title_portrait = &ui_font_OswaldRegular36p2;
#endif
        ui_speed_screen.font.info = &ui_font_OswaldRegular16p2;
        ui_speed_screen.screen.status_font = &ui_font_OswaldRegular14p2;
#else
#ifdef CONFIG_SSD168X_PANEL_SSD1681
        ui_speed_screen.font.main = &ui_font_OswaldRegular84p4;
        ui_speed_screen.font.title = &ui_font_OswaldRegular36p4;
#elif !defined(CONFIG_LCD_IS_EPD)
        ui_speed_screen.font.main = &ui_font_OswaldRegular100p4;
        ui_speed_screen.font.title = &ui_font_OswaldRegular48p4;
#else
        ui_speed_screen.font.main = &ui_font_OpenSansBold84p4;
        ui_speed_screen.font.title = &ui_font_OpenSansBold36p4;
#endif
        ui_speed_screen.font.info = &ui_font_OswaldRegular16p4;
        ui_speed_screen.screen.status_font = &ui_font_OswaldRegular14p4;
#endif
    }
    int ret = ui_SpeedScreen_screen_init();
    // ui_speed_screen.screen.update_dims();
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_speed_screen.screen.self){
#if (C_LOG_LEVEL < 3)
        ILOG(TAG, "[%s] load to screen", __func__);
#endif
        lv_scr_load(ui_speed_screen.screen.self);
        ret = 1;
    }
    print_lv_mem_mon();
    return ret;
}

void loadStatsScreen(int rows, int cols) {
    ILOG(TAG, "[%s]", __func__);
    if (ui_stats_screen.screen.self == 0) {
#if defined(USE_2BPP_FONT)

#if defined(CONFIG_SSD168X_PANEL_SSD1681)
        ui_stats_screen.font.title_small = &ui_font_OpenSansBold30p2;
        ui_stats_screen.font.title = &ui_font_OswaldRegular36p2;
#elif !defined(CONFIG_LCD_IS_EPD)
        ui_stats_screen.font.title_small = &ui_font_OswaldRegular36p2;
        ui_stats_screen.font.title = &ui_font_OswaldRegular48p2;
#else
        ui_stats_screen.font.title_small = &ui_font_OpenSansBold24p2;
        ui_stats_screen.font.title = &ui_font_OpenSansBold28p2;
#endif

#if !defined(CONFIG_LCD_IS_EPD)
        ui_stats_screen.font.title_big = &ui_font_OswaldRegular60p2;
#else
        ui_stats_screen.font.title_big = &ui_font_OpenSansBold60p2;
#endif

        ui_stats_screen.font.info = &ui_font_OswaldRegular16p2;

#else

#if defined(CONFIG_SSD168X_PANEL_SSD1681)
        ui_stats_screen.font.title_small = &ui_font_OpenSansBold30p4;
        ui_stats_screen.font.title = &ui_font_OswaldRegular36p4;
#elif !defined(CONFIG_LCD_IS_EPD)
        ui_stats_screen.font.title_small = &ui_font_OswaldRegular36p4;
        ui_stats_screen.font.title = &ui_font_OswaldRegular48p4;
#else
        ui_stats_screen.font.title_small = &ui_font_OpenSansBold24p4;
        ui_stats_screen.font.title = &ui_font_OpenSansBold28p4;
#endif

#if !defined(CONFIG_LCD_IS_EPD)
    ui_stats_screen.font.title_big = &ui_font_OswaldRegular60p4;
#else
        ui_stats_screen.font.title_big = &ui_font_OpenSansBold60p4;
#endif

        ui_stats_screen.font.info = &ui_font_OswaldRegular16p4;
#endif

    }
    ui_StatsScreen_screen_init(rows, cols);
    // ui_stats_screen.screen.update_dims();
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_stats_screen.screen.self){
#if (C_LOG_LEVEL < 3)
        ILOG(TAG, "[%s] load to screen", __func__);
#endif
        lv_scr_load(ui_stats_screen.screen.self);
    }
    print_lv_mem_mon();
}

void load_BlankScreen(uint8_t invert) {
    ILOG(TAG, "[%s]", __func__);
    ui_BlankScreen_screen_init();
    ui_blank_screen.invert = invert;
    if(lv_disp_get_scr_act(lv_disp_get_default()) != ui_blank_screen.screen.self){
#if (C_LOG_LEVEL < 3)
        ILOG(TAG, "[%s] load to screen", __func__);
#endif
        lv_scr_load(ui_blank_screen.screen.self);
    }
    print_lv_mem_mon();
}

int set_screen_img(lv_obj_t * img, const lv_img_dsc_t *img_src, uint16_t angle) {
    int ret = 0;
    if(img) {
        if(lv_img_get_src(img) != img_src) {
            lv_img_set_src(img, img_src);
            ret = 1;
        }
        if(lv_img_get_angle(img) != angle) {
            lv_img_set_angle(img, angle);
            ret = 2;
        }
    }
    return ret;
}

int set_label_text_safe(lv_obj_t * lbl, const char * title, uint8_t enable_hide_lbl) {
    if(!lbl) return 0;
    int ret = 0;
    if(title) {
        if(!lv_label_get_text(lbl) || (strcmp(lv_label_get_text(lbl), title) != 0)) {
#if (C_LOG_LEVEL < 2)
            ILOG(TAG,"[%s] set info label text %s", __func__, title);
#endif
            lv_label_set_text(lbl, title);
            ret =1;
            if(enable_hide_lbl && lv_obj_has_flag(lbl, LV_OBJ_FLAG_HIDDEN))
                lv_obj_clear_flag(lbl, LV_OBJ_FLAG_HIDDEN);
        }
    }
    else if(enable_hide_lbl && lv_obj_has_flag(lbl, LV_OBJ_FLAG_HIDDEN) == false) {
        lv_obj_add_flag(lbl, LV_OBJ_FLAG_HIDDEN);
    }
    return ret;
}

int invert_colors(lv_obj_t * panel, bool invert) {
    if(!panel)  return 0;
    if(invert) {
        lv_obj_set_style_bg_color(panel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else {
        lv_obj_set_style_bg_color(panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(panel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    return 1;
}

void showBlankScreen(uint8_t invert) {
    ILOG(TAG, "[%s]", __func__);
    load_BlankScreen(invert);
}

void showSleepScreen() {
    ILOG(TAG, "[%s]", __func__);
    loadSleepScreen();
}

void showRecordScreen(bool invert) {
    ILOG(TAG, "[%s]", __func__);
    loadRecordScreen();
    lv_obj_t* panel = ui_record_screen.screen.main_cnt;
    if(panel == 0)
        return;
    invert_colors(panel, invert);
}

void showFwUpdateScreen(const char * title, const char * info, const char * desc) {
    ILOG(TAG, "[%s]", __func__);
    int n = loadInfoScreen(INFO_MODE_FW_UPDATE);
    if(n) {
        set_screen_img(ui_info_screen.info_img, &update_48px, 0);
    }
    set_label_text_safe(ui_info_screen.info_lbl, title, 0);
    set_label_text_safe(ui_info_screen.info_secondary_lbl, info, 0);
    set_label_text_safe(ui_info_screen.info_third_lbl, desc, 0);
}

void showSettingsScreen(const char * title, const char * info, const char * desc) {
    ILOG(TAG, "[%s]", __func__);
    int n = loadInfoScreen(INFO_MODE_SETTINGS);
    if(n) {
        set_screen_img(ui_info_screen.info_img, &settings_48px, 0);
    }
    set_label_text_safe(ui_info_screen.info_lbl, title, 0);
    set_label_text_safe(ui_info_screen.info_secondary_lbl, info, 0);
    set_label_text_safe(ui_info_screen.info_third_lbl, desc, 0);
}

void showLowBatScreen(const char * title) {
    ILOG(TAG, "[%s]", __func__);
    int n = loadInitScreen(INIT_MODE_LOW_BAT);
    if(n) {
        set_screen_img(ui_init_screen.init_img, &battery_horiz_bold_48px, 0);
#if !defined(CONFIG_LCD_IS_EPD)
        lv_obj_set_style_img_recolor(ui_init_screen.init_img, lv_color_hex(0xEECE44), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor_opa(ui_init_screen.init_img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        lv_obj_set_y(ui_init_screen.init_img, lv_pct(-5));
    }
    set_label_text_safe(ui_init_screen.init_lbl, title, 1);
}

void showPushScreen(int push, const char * title) {
    ILOG(TAG, "[%s]", __func__);
    int n = loadInitScreen(INIT_MODE_PUSH_BUTTON);
    set_screen_img(ui_init_screen.init_img, push==1 ? &radio_button_partial_24px : push==2 ? &radio_button_checked_24px : &radio_button_unchecked_24px, 0);
    if(n) {
        lv_obj_set_y(ui_init_screen.init_img, lv_pct(-5));
    }
    set_label_text_safe(ui_init_screen.init_lbl, title, 1);
}

void showGpsTroubleScreen() {
#if (C_LOG_LEVEL < 2)
    ILOG(TAG, "[%s]", __func__);
#endif
    int n = loadInitScreen(INIT_MODE_GPS_TROUBLE);
    if(n) {
        set_screen_img(ui_init_screen.init_img, &near_me_disabled_bold_48px, 0);
        lv_obj_set_y(ui_init_screen.init_img, lv_pct(-10));
        set_label_text_safe(ui_init_screen.init_lbl, "GPS Failure", 1);
    }
}

void showSdTroubleScreen() {
#if (C_LOG_LEVEL < 2)
    ILOG(TAG, "[%s]", __func__);
#endif
    int n = loadInitScreen(INIT_MODE_SD_TROUBLE);
    if(n) {
        set_screen_img(ui_init_screen.init_img, &sd_trouble_bold_48px, 0);
        lv_obj_set_y(ui_init_screen.init_img, lv_pct(-10));
        set_label_text_safe(ui_init_screen.init_lbl, "SD Failure", 1);
    }
}

void showBootScreen(const char* title) {
#if (C_LOG_LEVEL < 2)
    ILOG(TAG, "[%s] title: %s", __func__, title);
#endif
    int n = loadInitScreen(INIT_MODE_BOOT);
    if(n) {
        set_screen_img(ui_init_screen.init_img, &espidf_logo_v2_48px, 0);
    }
    if (title){
        lv_obj_set_y(ui_init_screen.init_img, lv_pct(-10));
    } else {
        lv_obj_set_y(ui_init_screen.init_img, lv_pct(-5));
    }
    set_label_text_safe(ui_init_screen.init_lbl, title, 1);
}

void showSaveSessionScreen(const char * title, const char * info, const char * desc) {
#if (C_LOG_LEVEL < 2)
    ILOG(TAG, "[%s]", __func__);
#endif
    int n = loadInfoScreen(INFO_MODE_SAVE_SESSION);
    if(n) {
        set_screen_img(ui_info_screen.info_img, &save_bold_48px, 0);
    }
    set_label_text_safe(ui_info_screen.info_lbl, title, 0);
    set_label_text_safe(ui_info_screen.info_secondary_lbl, info, 1);
    set_label_text_safe(ui_info_screen.info_third_lbl, desc, 1);
}

int showWifiScreen() {
#if (C_LOG_LEVEL < 2)
    ILOG(TAG, "[%s] title:%s info:%s", __func__, title, info);
#endif
    int n = loadInfoScreen(INFO_MODE_WIFI);
    if(n) {
        set_screen_img(ui_info_screen.info_img, &wifi_bold_48px, 0);
#if !defined(CONFIG_LCD_IS_EPD)
        lv_obj_set_style_img_recolor(ui_info_screen.info_img, lv_color_hex(0x104951), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor_opa(ui_info_screen.info_img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        lv_label_set_text(ui_info_screen.info_lbl, "WiFi");
        lv_label_set_text(ui_info_screen.info_secondary_lbl, "");
        lv_label_set_text(ui_info_screen.info_third_lbl, "");
    }
    return n;
}

int showGpsScreen(uint16_t angle) {
#if (C_LOG_LEVEL < 2)
    ILOG(TAG, "[%s] title:%s info:%s", __func__, title, info);
#endif
    int n = loadInfoScreen(INFO_MODE_GPS);
    if(n || angle != lv_img_get_angle(ui_info_screen.info_img)) {
        set_screen_img(ui_info_screen.info_img, &near_me_bold_48px, angle);
        if(n) {
            lv_label_set_text(ui_info_screen.info_lbl, "GPS");
            lv_label_set_text(ui_info_screen.info_secondary_lbl, "");
            lv_label_set_text(ui_info_screen.info_third_lbl, "");
        }
    }
    return n;
}

int showSpeedScreen() {
#if (C_LOG_LEVEL < 2)
    ILOG(TAG, "[%s]", __func__);
#endif
    return loadSpeedScreen();
}

void showStatsScreen12() {
#if (C_LOG_LEVEL < 2)
    ILOG(TAG, "[%s]", __func__);
#endif
    loadStatsScreen(2,102);
}

void showStatsScreen22() {
    ILOG(TAG, "[%s]", __func__);
    loadStatsScreen(2,2);
}

void showStatsScreen32() {
    ILOG(TAG, "[%s]", __func__);
    loadStatsScreen(3,2);
}
