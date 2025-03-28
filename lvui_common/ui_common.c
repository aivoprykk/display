#include "../display_private.h"

#if defined(CONFIG_DISPLAY_ENABLED)
#include "ui_common.h"

ESP_EVENT_DEFINE_BASE(UI_EVENT);

static const char *TAG = "ui_common";

#if (C_LOG_LEVEL < 2)
static const char * _ui_event_strings[] = { UI_EVENT_LIST(STRINGIFY)};
const char * ui_event_strings(int id) {
    return _ui_event_strings[id];
}
#else
const char * ui_event_strings(int id) {return "UI_EVENT";}
#endif

// TIMER_INIT

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

//lv_obj_t* ui_StatusPanel = 0;

#if defined(STATUS_PANEL_V1)
ui_status_panel_t ui_status_panel = {0};
void ui_status_panel_load(ui_screen_t* parent) {
    ILOG(TAG, "[%s]", __func__);
    if(!parent->has_status_cnt)
        return;
    if(ui_status_panel.self != NULL && (parent->status_viewmode != ui_status_panel.viewmode)) {
        ui_status_panel_delete();
    }
    ui_status_panel.viewmode = parent->status_viewmode;
    if (ui_status_panel.self == NULL)
        ui_status_panel_init(parent);
    else {
        lv_obj_set_parent(ui_status_panel.self, parent->status_cnt);
    }
    ui_status_panel.parent = parent;
    lv_obj_set_x(ui_status_panel.self, parent->main_cnt_offset);
}

lv_obj_t* ui_status_panel_create(lv_obj_t* parent) {
    lv_obj_t *panel, *l;
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
    ui_status_panel.self = panel;

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
#if defined(CONFIG_SSD168X_PANEL_SSD1681)
        lv_obj_align(l, LV_ALIGN_RIGHT_MID, lv_pct(-38), 0);
#else
        lv_obj_align(l, LV_ALIGN_RIGHT_MID, lv_pct(-35), 0);
#endif
        // if(ui_status_panel.viewmode==0){
        //     lv_obj_set_style_text_font(l, LV_FONT_DEFAULT, 0);
        //     lv_label_set_text(l, LV_SYMBOL_GPS);
        //     // lv_obj_set_style_pad_top(l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        // }
        // lv_obj_set_style_pad_right(l, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        ui_status_panel.gps_image = l;
    }

    // if (ui_status_panel.viewmode==0) {
    //     l = lv_label_create(panel);
    //     lv_obj_set_width(l, LV_SIZE_CONTENT);   /// 1
    //     lv_obj_set_height(l, LV_SIZE_CONTENT);  /// 1
    //     lv_obj_align(l, LV_ALIGN_RIGHT_MID, lv_pct(-28), 0);
    //     lv_obj_set_style_text_font(l, LV_FONT_DEFAULT, 0);
    //     lv_label_set_text(l, LV_SYMBOL_SD_CARD);
    //     lv_obj_set_style_pad_right(l, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    //     // lv_obj_set_style_pad_top(l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    //     ui_status_panel.sdcard_image = l;
    // }

    // right = ui_common_panel_init(panel, 30, 100);
    // lv_obj_set_align(right, LV_ALIGN_RIGHT_MID);
    // lv_obj_set_flex_flow(right, LV_FLEX_FLOW_ROW);
    // lv_obj_set_flex_align(right, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

    if (ui_status_panel.viewmode==0) {
        l = lv_label_create(panel);
        lv_obj_set_width(l, LV_SIZE_CONTENT);   /// 1
        lv_obj_set_height(l, LV_SIZE_CONTENT);  /// 1
#if defined(CONFIG_SSD168X_PANEL_SSD1681)
        lv_obj_align(l, LV_ALIGN_RIGHT_MID, lv_pct(-25), 0);
#else
        lv_obj_align(l, LV_ALIGN_RIGHT_MID, lv_pct(-20), 0);
#endif
        lv_obj_set_style_text_font(l, LV_FONT_DEFAULT, 0);
        lv_label_set_text(l, LV_SYMBOL_BATTERY_FULL);
        // lv_obj_set_style_transform_angle(l, 900, 0);
        // lv_obj_set_style_pad_right(l, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        // lv_obj_set_style_pad_top(l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        ui_status_panel.bat_image = l;
    }
    l = lv_label_create(panel);
    lv_obj_set_width(l, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(l, LV_SIZE_CONTENT);  /// 1
    lv_obj_align(l, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_label_set_text(l, "100%");
    ui_status_panel.bat_label = l;

    return panel;
}

void ui_status_panel_delete(void) {
    ILOG(TAG, "[%s]", __func__);
    if (ui_status_panel.self != NULL) {
        lv_obj_clean(ui_status_panel.self);
        lv_obj_del(ui_status_panel.self);
        // ui_status_panel.self = NULL;
        // ui_status_panel.parent->status_cnt = 0;
        // uint8_t vmc = ui_status_panel.viewmode;
        memset(&ui_status_panel, 0, sizeof(ui_status_panel));
        // ui_status_panel.viewmode = vmc;
    }
}

#else

void ui_status_panel_create(ui_screen_t* parent, int8_t viewmode) {
    if(!parent->has_status_cnt)
        return;
    if (ui_status_panel.self == NULL)
        ui_status_panel_init(parent);
    else{
        lv_obj_set_parent(ui_status_panel.self, parent->status_cnt);
    }
    const lv_font_t *font = parent->status_font ? parent->status_font : ui_status_font_default;
    if(lv_obj_get_style_text_font(ui_status_panel.self, LV_PART_MAIN | LV_STATE_DEFAULT) != font)
        lv_obj_set_style_text_font(ui_status_panel.self, font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_statusbar_set_mode(ui_status_panel, viewmode);
}

void ui_status_panel_delete(void) {
    if (ui_status_panel.self != NULL) {
        lv_obj_clean(ui_status_panel.self);
        lv_obj_del(ui_status_panel.self);
        ui_status_panel.self = NULL;
    }
}

#endif

void ui_common_init(void) {
    ILOG(TAG, "[%s]", __func__);
    lv_disp_t* dispp = lv_disp_get_default();
#if defined(CONFIG_LCD_IS_EPD)
    lv_theme_t* theme = lv_theme_mono_init(dispp, false, LV_FONT_DEFAULT);
#else
    lv_theme_t* theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
#endif
    lv_disp_set_theme(dispp, theme);
    ui_create_styles();
}

void ui_common_deinit() {
    ui_status_panel_delete();
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
    lv_obj_t * scr = screen->self;
    if(!scr) {
        scr = lv_obj_create(NULL);
        lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
        screen->self = scr;
    }
    if(screen->has_status_cnt) {
        if(!screen->status_cnt) {
            lv_obj_t *panel = ui_common_panel_init(scr, 100, 18);
#ifdef CONFIG_SSD168X_PANEL_SSD1680
            lv_obj_set_y(panel, -4); // for SSD1680, visible height is 128-6=122
#endif
            lv_obj_set_align(panel, LV_ALIGN_BOTTOM_LEFT);
            screen->status_cnt = panel;
        }
        else {
            lv_obj_set_parent(screen->status_cnt, scr);
        }
    }
    return scr;
}

void ui_common_screen_uninit(ui_screen_t * screen) {
    if(screen->self) {
        if(screen->status_cnt) {
            if((lv_obj_get_parent(ui_status_panel.self) == screen->status_cnt)) {
                ui_status_panel_delete();
            }
            screen->status_cnt = NULL;
        }
        lv_obj_clean(screen->self);
        lv_obj_del(screen->self);
        screen->self = NULL;
        screen->main_cnt = NULL;
        
    }
}

static void flush_screen(ui_screen_t * screen, ui_screen_t * screen2) {
    if(screen && screen->main_cnt && screen->unload) {
        if(!screen2 || screen->main_cnt != screen2->main_cnt)
            screen->unload();
    }
}

void ui_uninit_screens(void) {
    ILOG(TAG, "[%s]", __func__);
    ui_common_screen_uninit(&ui_init_screen.screen);
    ui_common_screen_uninit(&ui_info_screen.screen);
    ui_common_screen_uninit(&ui_speed_screen.screen);
    ui_common_screen_uninit(&ui_stats_screen.screen);
    ui_common_screen_uninit(&ui_sleep_screen.screen);
    ui_common_screen_uninit(&ui_record_screen.screen);
}


void ui_flush_screens(ui_screen_t * screen) {
    ILOG(TAG, "[%s]", __func__);
    flush_screen(&ui_init_screen.screen, screen);
    flush_screen(&ui_speed_screen.screen, screen);
    flush_screen(&ui_speed_screen.screen, screen);
    flush_screen(&ui_stats_screen.screen, screen);
    flush_screen(&ui_sleep_screen.screen, screen);
    flush_screen(&ui_record_screen.screen, screen);
}

void ui_set_main_cnt_offset(ui_screen_t * screen, int8_t off) {
    assert(screen);
    screen->main_cnt_offset = off;
}

static void ui_invalidate_screen(ui_screen_t * screen) {
    if(screen && screen->main_cnt) {
        lv_obj_invalidate(screen->main_cnt);
    }
}
void ui_invalidate_screens(void) {
    ILOG(TAG, "[%s]", __func__);
    ui_invalidate_screen(&ui_init_screen.screen);
    ui_invalidate_screen(&ui_info_screen.screen);
    ui_invalidate_screen(&ui_speed_screen.screen);
    ui_invalidate_screen(&ui_stats_screen.screen);
    ui_invalidate_screen(&ui_sleep_screen.screen);
    ui_invalidate_screen(&ui_record_screen.screen);
}

#endif