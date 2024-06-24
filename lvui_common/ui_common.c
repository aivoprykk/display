// LVGL version: 8.3.6
// Project name: lilygo_tdisplay_s3_04

#include "ui_common.h"
#include "ui_helpers.h"
#include "logger_common.h"


static const char *TAG = "ui_common";
TIMER_INIT

// const lv_style_const_prop_t style_plain_panel_props[] = {
//     LV_STYLE_CONST_PAD_BOTTOM(0),
//     LV_STYLE_CONST_PAD_TOP(0),
//     LV_STYLE_CONST_PAD_LEFT(0),
//     LV_STYLE_CONST_PAD_RIGHT(0),
//     LV_STYLE_CONST_BORDER_OPA(LV_OPA_COVER),
//     LV_STYLE_CONST_TEXT_OPA(LV_OPA_COVER),
//     LV_STYLE_CONST_RADIUS(0),
//     {0}};

// const lv_style_const_prop_t style_text_small_props[] = {
//     LV_STYLE_CONST_TEXT_FONT(&ui_font_OswaldRegular12p4),
//     {0}};

// const lv_style_const_prop_t style_text_normal_props[] = {
//     LV_STYLE_CONST_TEXT_FONT(&ui_font_OswaldRegular16p4),
//     {0}};

// const lv_style_const_prop_t style_text_large_props[] = {
//     LV_STYLE_CONST_TEXT_FONT(&ui_font_OswaldRegular24p2),
//     {0}};

// const lv_style_const_prop_t style_text_oswald_regular_20_props[] = {
//     LV_STYLE_CONST_TEXT_FONT(&ui_font_OswaldRegular20p4),
//     {0}};

// const lv_style_const_prop_t style_text_oswald_regular_24_props[] = {
//     LV_STYLE_CONST_TEXT_FONT(&ui_font_OswaldRegular24p4),
//     {0}};

// const lv_style_const_prop_t style_text_monserrat_16_props[] = {
//     LV_STYLE_CONST_TEXT_FONT(LV_FONT_MONTSERRAT_16),
//     {0}};

// #if defined(CONFIG_DISPLAY_DRIVER_ST7789)
// const lv_style_const_prop_t style_text_bigger_props[] = {
//     LV_STYLE_CONST_TEXT_FONT(&ui_font_OswaldRegular36p4),
//     {0}};
// const lv_style_const_prop_t style_text_biggest_props[] = {
//     LV_STYLE_CONST_TEXT_FONT(&ui_font_OswaldRegular120p4),
//     {0}};
// #else
// const lv_style_const_prop_t style_text_bigger_props[] = {
//     LV_STYLE_CONST_TEXT_FONT(&ui_font_OpenSansBold32p4),
//     {0}};
// const lv_style_const_prop_t style_text_morebigger_props[] = {
//     LV_STYLE_CONST_TEXT_FONT(&ui_font_OpenSansBold60p2),
//     {0}};
// const lv_style_const_prop_t style_text_biggest_props[] = {
//     LV_STYLE_CONST_TEXT_FONT(&ui_font_OpenSansBold84p4),
//     {0}};
// #endif

// const lv_style_const_prop_t style_border_none_props[] = {
//     LV_STYLE_CONST_BORDER_SIDE(LV_BORDER_SIDE_NONE),
//     LV_STYLE_CONST_BORDER_WIDTH(0),
//     {0}};

// const lv_style_const_prop_t style_border_bottom_props[] = {
//     LV_STYLE_CONST_BORDER_SIDE(LV_BORDER_SIDE_BOTTOM),
//     LV_STYLE_CONST_BORDER_WIDTH(1),
//     {0}};

// const lv_style_const_prop_t style_border_top_props[] = {
//     LV_STYLE_CONST_BORDER_SIDE(LV_BORDER_SIDE_TOP),
//     LV_STYLE_CONST_BORDER_WIDTH(1),
//     {0}};

// const lv_style_const_prop_t style_border_right_props[] = {
//     LV_STYLE_CONST_BORDER_SIDE(LV_BORDER_SIDE_RIGHT),
//     LV_STYLE_CONST_BORDER_WIDTH(1),
//     {0}};

// const lv_style_const_prop_t style_border_full_props[] = {
//     LV_STYLE_CONST_BORDER_SIDE(LV_BORDER_SIDE_FULL),
//     LV_STYLE_CONST_BORDER_WIDTH(1),
//     {0}};

// LV_STYLE_CONST_INIT(style_plain_panel, style_plain_panel_props);
// LV_STYLE_CONST_INIT(style_text_oswald_regular_20, style_text_oswald_regular_20_props);
// LV_STYLE_CONST_INIT(style_text_oswald_regular_24, style_text_oswald_regular_24_props);
// LV_STYLE_CONST_INIT(style_border_none, style_border_none_props);
// LV_STYLE_CONST_INIT(style_border_bottom, style_border_bottom_props);
// LV_STYLE_CONST_INIT(style_border_top, style_border_top_props);
// LV_STYLE_CONST_INIT(style_border_right, style_border_right_props);
// LV_STYLE_CONST_INIT(style_border_full, style_border_full_props);

// LV_STYLE_CONST_INIT(style_text_small, style_text_small_props);
// LV_STYLE_CONST_INIT(style_text_normal, style_text_normal_props);
// LV_STYLE_CONST_INIT(style_text_large, style_text_large_props);
// LV_STYLE_CONST_INIT(style_text_bigger, style_text_bigger_props);
// LV_STYLE_CONST_INIT(style_text_morebigger, style_text_morebigger_props);
// LV_STYLE_CONST_INIT(style_text_biggest, style_text_biggest_props);
// LV_STYLE_CONST_INIT(style_text_monserrat_16, style_text_monserrat_16_props);

// lv_style_t style_plain_container;
// lv_style_t style_statusbar;
// lv_style_t style_speed_big_panel;

void ui_create_styles(void) {
    // lv_style_ptr_t s = &style_plain_container;
    // lv_style_init(s);
    // lv_style_set_pad_all(s, 0);
    // lv_style_set_border_opa(s, LV_OPA_COVER);
    // lv_style_set_text_opa(s, LV_OPA_COVER);
    // lv_style_set_radius(s, 0);
    // lv_style_set_text_color(s, lv_color_black());
    // lv_style_set_bg_color(s, lv_color_white());
    // lv_style_set_bg_opa(s, LV_OPA_COVER);
    // lv_style_set_border_side(s, LV_BORDER_SIDE_NONE);
    // lv_style_set_border_width(s, 0);
    // lv_style_set_width(s, LV_PCT(100));

    // s = &style_statusbar;
    // lv_style_init(s);
    // lv_style_set_border_side(s, LV_BORDER_SIDE_TOP);
    // lv_style_set_border_width(s, 1);
    // lv_style_set_text_font(s, &ui_font_OswaldRegular16p4);
}

lv_obj_t* ui_StatusPanel = 0;

#if defined(STATUS_PANEL_V1)
ui_status_panel_t ui_status_panel = {0};
void ui_StatusPanel_load(ui_screen_t* parent, int8_t viewmode) {
    LOGR
    if(!parent->has_status_cnt)
        return;
    if(ui_StatusPanel != NULL && 
    (viewmode != ui_status_panel.viewmode)) {
        ui_StatusPanel_unload();
    }
    if((void *) ui_status_panel.parent != (void*) &ui_info_screen.screen && ui_StatusPanel != NULL)
        return;
    ui_status_panel.viewmode = viewmode;
    if (ui_StatusPanel == NULL)
        ui_StatusPanel_init(parent);
    else
        lv_obj_set_parent(ui_StatusPanel, parent->status_cnt);
    ui_status_panel.parent = parent;
}

lv_obj_t* ui_StatusPanel_create_B(lv_obj_t* parent) {
    LOGR
    lv_obj_t *panel, *l, *right;
    panel = ui_common_panel_init(parent, 100, 100);
    lv_obj_set_align(panel, LV_ALIGN_BOTTOM_LEFT);
    // if (!ui_status_panel.viewmode) {
    //     lv_obj_set_style_border_width(panel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    //     lv_obj_set_style_border_side(panel, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
    // }
    lv_obj_set_style_pad_left(panel, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(panel, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(panel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    l = lv_label_create(panel);
    lv_obj_set_width(l, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(l, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_align(l, LV_ALIGN_LEFT_MID);
    lv_label_set_text(l, "00:00");
    ui_status_panel.time_label = l;
    
    if (ui_status_panel.viewmode==0) {
        l = lv_label_create(panel);
        lv_obj_set_width(l, LV_SIZE_CONTENT);   /// 1
        lv_obj_set_height(l, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_y(l, 0);
        lv_obj_set_x(l, lv_pct(-48));
        lv_obj_set_align(l, LV_ALIGN_RIGHT_MID);
        lv_label_set_text(l, "19.0C");
        ui_status_panel.temp_label = l;
    }

    if (ui_status_panel.viewmode==0||ui_status_panel.viewmode==2) {
        l = lv_label_create(panel);
        lv_obj_set_width(l, LV_SIZE_CONTENT);   /// 1
        lv_obj_set_height(l, LV_SIZE_CONTENT);  /// 1
        lv_obj_align(l, LV_ALIGN_RIGHT_MID, lv_pct(-35), 0);
        if(ui_status_panel.viewmode==0){
            lv_obj_set_style_text_font(l, LV_FONT_DEFAULT, 0);
            lv_label_set_text(l, LV_SYMBOL_GPS);
            // lv_obj_set_style_pad_top(l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        lv_obj_set_style_pad_right(l, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        ui_status_panel.gps_image = l;
    }

    if (ui_status_panel.viewmode==0) {
        l = lv_label_create(panel);
        lv_obj_set_width(l, LV_SIZE_CONTENT);   /// 1
        lv_obj_set_height(l, LV_SIZE_CONTENT);  /// 1
        lv_obj_align(l, LV_ALIGN_RIGHT_MID, lv_pct(-28), 0);
        lv_obj_set_style_text_font(l, LV_FONT_DEFAULT, 0);
        lv_label_set_text(l, LV_SYMBOL_SD_CARD);
        lv_obj_set_style_pad_right(l, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        // lv_obj_set_style_pad_top(l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        ui_status_panel.sdcard_image = l;
    }

    right = ui_common_panel_init(panel, 30, 100);
    lv_obj_set_align(right, LV_ALIGN_RIGHT_MID);
    lv_obj_set_flex_flow(right, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(right, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

    if (ui_status_panel.viewmode==0) {
        l = lv_label_create(right);
        lv_obj_set_width(l, LV_SIZE_CONTENT);   /// 1
        lv_obj_set_height(l, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_align(l, LV_ALIGN_RIGHT_MID);
        lv_obj_set_style_text_font(l, LV_FONT_DEFAULT, 0);
        lv_label_set_text(l, LV_SYMBOL_BATTERY_FULL);
        // lv_obj_set_style_transform_angle(l, 900, 0);
        lv_obj_set_style_pad_right(l, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_top(l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        ui_status_panel.bat_image = l;
    }
    l = lv_label_create(right);
    lv_obj_set_width(l, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(l, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_align(l, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(l, "100%");
    ui_status_panel.bat_label = l;

    return panel;
}

void ui_StatusPanel_unload(void) {
    LOGR
    if (ui_StatusPanel != NULL) {
        lv_obj_clean(ui_StatusPanel);
        lv_obj_del(ui_StatusPanel);
        ui_StatusPanel = NULL;
        //ui_status_panel.parent->status_cnt = 0;
        //uint8_t vmc = ui_status_panel.viewmode;
        memset(&ui_status_panel, 0, sizeof(ui_status_panel));
        //ui_status_panel.viewmode = vmc;
    }
}
#else

void ui_StatusPanel_load(ui_screen_t* parent, int8_t viewmode) {
    LOGR
    if(!parent->has_status_cnt)
        return;
    if (ui_StatusPanel == NULL)
        ui_StatusPanel_init(parent);
    else{
        lv_obj_set_parent(ui_StatusPanel, parent->status_cnt);
    }
    const lv_font_t *font = parent->status_font ? parent->status_font : ui_status_font_default;
    if(lv_obj_get_style_text_font(ui_StatusPanel, LV_PART_MAIN | LV_STATE_DEFAULT) != font)
        lv_obj_set_style_text_font(ui_StatusPanel, font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_statusbar_set_mode(ui_StatusPanel, viewmode);
}

void ui_StatusPanel_unload(void) {
    LOGR
    if (ui_StatusPanel != NULL) {
        lv_obj_clean(ui_StatusPanel);
        lv_obj_del(ui_StatusPanel);
        ui_StatusPanel = NULL;
    }
}

#endif

void showSleepScreen() {
    TIMER_S
    loadSleepScreen();
    TIMER_E
}


void showLowBatScreen() {
    LOGR
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
    LOGR
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
    LOGR
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

void showBootScreen(const char* title) {
    LOGR
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
    LOGR
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

void showGpsScreen(const char* title, const char* info, int angle) {
    LOGR
    loadInfoScreen();
    lv_obj_t* img = ui_info_screen.info_img;
    const lv_img_dsc_t *img_src = &near_me_bold_48px;
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
    LOGR
    loadSpeedScreen();
}

void showStatsScreen12() {
    LOGR
    loadStatsScreen(2,102);
    //ui_StatusPanel_load(ui_StatusPanel);
}

void showStatsScreen22() {
    LOGR
    loadStatsScreen(2,2);
    //ui_StatusPanel_load(ui_StatusPanel);
}

void showStatsScreen32() {
    LOGR
    loadStatsScreen(3,2);
    //ui_StatusPanel_load(ui_StatusPanel);
}

void ui_common_init(void) {
    LOGR
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t* dispp = lv_disp_get_default();
#ifdef CONFIG_DISPLAY_DRIVER_ST7789
    lv_theme_t* theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
#else
    lv_theme_t* theme = lv_theme_mono_init(dispp, false, LV_FONT_DEFAULT);
#endif
    lv_disp_set_theme(dispp, theme);
    ui_create_styles();
}

void ui_common_deinit() {
    LOGR
    ui_StatusPanel_unload();
}

lv_obj_t * ui_common_panel_init(lv_obj_t * parent, uint8_t w, uint8_t h) {
    lv_obj_t * panel = lv_obj_create(parent);
    lv_obj_remove_style_all(panel);
    if(w > 0)
        lv_obj_set_width(panel, lv_pct(w));
    if(h > 0)
        lv_obj_set_height(panel, lv_pct(h));
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    return panel;
}

lv_obj_t * ui_common_screen_init(ui_screen_t * screen) {
    LOGR
    lv_obj_t * scr = lv_obj_create(NULL);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    if(screen->has_status_cnt) {
        lv_obj_t *panel = ui_common_panel_init(scr, 100, 18);
        lv_obj_set_y(panel, -4); // for DEPG0213BN, visible height is 128-6=122
        lv_obj_set_align(panel, LV_ALIGN_BOTTOM_LEFT);
        screen->status_cnt = panel;
    }
    return scr;
}
