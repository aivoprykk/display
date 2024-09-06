
#include <stdio.h>

#include "driver_vendor.h"
#include "esp_log.h"

#include "logger_common.h"
#include "str.h"
#include "adc.h"
#include "button.h"
#include "ui_common.h"
#if LVGL_VERSION_MAJOR >= 9
#include "../managed_components/lvgl__lvgl/src/core/lv_refr_private.h"
#endif

static const char *TAG = "lvgl_demo_ui";
static float voltage_bat = 0.0;
#define MINIMUM_VOLTAGE 3.2
#ifdef CONFIG_DISPLAY_DRIVER_SSD1680
LV_IMG_DECLARE(speed_250x122_v23);
LV_IMG_DECLARE(speed_122x250_v23);
const lv_img_dsc_t * img_full_l = &speed_250x122_v23;
const lv_img_dsc_t * img_full_p = &speed_122x250_v23;
#endif
#ifdef CONFIG_DISPLAY_DRIVER_SSD1681
LV_IMG_DECLARE(speed_raw_200x200);
const lv_img_dsc_t * img_full_l = &speed_raw_200x200;
const lv_img_dsc_t * img_full_p = &speed_raw_200x200;
#endif

static void update_bat(uint8_t verbose) {
    voltage_bat = volt_read();
#if defined(DEBUG)
    if (verbose)
        ESP_LOGI(TAG, "[%s] Battery measured (computed:%.02f, required_min:%.02f)\n", __FUNCTION__, voltage_bat, MINIMUM_VOLTAGE);
#endif
}

static int count = 0, angle = 0, full=0;
static float max_speed = 0, avg_speed = 0, cur_speed[5] = {0};
static uint8_t index_speed = 0;

// static void set_angle(void * img, int32_t v)
// {
//     lv_img_set_src(img, &ui_img_near_me_fill0_wght400_grad0_opsz24_png);
//     lv_img_set_angle(img, v);
// }
enum screen_e {
    BOOT_SCREEN = 0,
    BLANK_SCREEN,
    SPLASH_SCREEN,
    SLEEP_SCREEN,
    WIFI_SCREEN,
    GPS_SCREEN,
    SPEED_SCREEN,
    RECORD_SCREEN,
    STATS_SCREEN_3,
    STATS_SCREEN_4,
    STATS_SCREEN_5,
    STATS_SCREEN_6,
    OFF_SCREEN,
    LOW_BAT_SCREEN,
    GPS_FAIL_SCREEN,
    SD_FAIL_SCREEN,
    MAX_SCREENS
};

static void timer_cb(lv_timer_t *timer);
static void load_screen(int noinc);

static SemaphoreHandle_t refreshing_sem = NULL;

static bool button_down = false;
static int rotation = 2, prev_rotation=2; // 180 deg, next from default which is 90 deg eq 1
static void button_cb(int num, l_button_ev_t ev, uint64_t press_time) {
#if defined(DEBUG)
    ESP_LOGI(TAG, "Button %d event: %d time: %llu us", num, ev, press_time);
#endif
    // l_button_t *btn = 0;
    // if(num<1)
    //     btn = &btns[num];
    switch (ev) {
    case L_BUTTON_UP:
        if (xSemaphoreTake(refreshing_sem, portMAX_DELAY) == pdTRUE){
            button_down = false;
            if(prev_rotation!=rotation){
                prev_rotation = rotation;
                load_screen(2);
            }
            else if(count == MAX_SCREENS-1){
                display_epd_request_fast_update();
                load_screen(0);
                load_screen(1);
            }
            else 
                load_screen(0);
            xSemaphoreGive(refreshing_sem);
        }
        break;
    case L_BUTTON_DOWN:
        if (xSemaphoreTake(refreshing_sem, portMAX_DELAY) == pdTRUE){
            button_down = true;
            xSemaphoreGive(refreshing_sem);
        }
        // if(num==0)
        //     showPushScreen(0,"");
        break;
    case L_BUTTON_LONG_PRESS_START:
        if(num==0){
            if (xSemaphoreTake(refreshing_sem, portMAX_DELAY) == pdTRUE){
                display_epd_ssd168x_set_rotation(rotation++%4);
                // showPushScreen(1,"");
                xSemaphoreGive(refreshing_sem);
            }
        }
        break;
    case L_BUTTON_LONG_LONG_PRESS_START:
        // if(num==0)
        //     showPushScreen(2,"");
        --count;
        break;
    default:
        break;
    }
}

#include "esp_random.h"
float randomFloat() {
    uint32_t r = esp_random();               // Generate a random 32-bit number
    float f = (float)r / (float)UINT32_MAX;  // Convert to a float between 0 and 1
    return f * 127;                          // Scale to the range 0-127
}

int randomInteger() {
    uint32_t r = esp_random();  // Generate a random 32-bit number
    return r % 1271;            // Scale to the range 0-1500
}

float averageFloat(float *array, int count) {
    float sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += array[i];
    }
    return sum / count;
}

lv_obj_t * splashScreenLoad() {
    lv_obj_t * splash = ui_common_panel_init(NULL, 0, 0);
    lv_scr_load(splash);
    lv_obj_t *img = lv_img_create(splash);
    lv_obj_set_size(img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    if(rotation % 2)
        lv_img_set_src(img, img_full_p);
    else
        lv_img_set_src(img, img_full_l);
    lv_obj_align(img, LV_ALIGN_TOP_LEFT, 0, 0); 
    return splash;
}

lv_obj_t * blankScreenLoad(bool invert) {
#if defined(DEBUG)
    ESP_LOGI(TAG, "load blank screen with color %s", invert ? "black" : "white");
#endif
    // display_epd_request_full_update();
    lv_obj_t * panel = lv_obj_create(0);
    lv_scr_load(panel);
    lv_obj_remove_style_all(panel);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    lv_obj_set_style_bg_color(panel, invert ? lv_color_black() : lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
    return panel;
}

typedef struct sleep_scr_s {
    float data;
    const char *info;
} sleep_scr_t;

static struct sleep_scr_s sleep_scr_info_fields[2][6] = {
    {
        {100.49, "AV:"},
        {100.49, "R1:"},
        {100.49, "R2:"},
        {100.49, "R3:"},
        {100.49, "R4:"},
        {100.49, "R5:"}
    },
    {
        {101.25, "2sec:"},
        {54.16, "1h:"},
        {95.99, "500m:"},
        {94.81, "NM:"},
        {54.26, "Dist:"},
        {54.99, "Alfa:"}
    }
};
static lv_obj_t * scr = 0;
static uint8_t color = 0;


static void load_screen(int noinc) {
    ESP_LOGI(TAG, "load_screen: %d", noinc);
    update_bat(0);
    char tmp[24] = {0}, *p = tmp;
    // lv_obj_t *panel;
    printf("----------------------------------------\n");
    printf("load_screem: %d\n", count);
    printf("----------------------------------------\n");
    float last_speed = randomFloat();
    cur_speed[index_speed++ % 5] = last_speed;
    if (last_speed > max_speed)
        max_speed = last_speed;
    avg_speed = averageFloat(cur_speed, 5);
    lv_obj_t * lscr = scr;
    if(button_down)
        return;
    
    if(!noinc){
        if (count++ > MAX_SCREENS-2)
            count = 0;
    }
    else if(noinc==2) {
        // ui_uninit_screens();
        // lv_obj_invalidate(lv_scr_act());
    }

    if (count == BLANK_SCREEN) {
        ESP_LOGI(TAG, "load blank screen");
        if(color > 1)
            color = 1;
        scr = blankScreenLoad(color++);
    } else if(count == SLEEP_SCREEN) {
        ESP_LOGI(TAG, "load sleep screen");
        showSleepScreen();
        ui_status_panel_t * statusbar = &ui_status_panel;
        lv_label_set_text(statusbar->time_label, "12:00 2024-01-01");
        lv_label_set_text(statusbar->bat_label, "97%");
        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 2; j++) {
                f2_to_char(sleep_scr_info_fields[j][i].data, p);
                lv_label_set_text(ui_sleep_screen.cells[i][j].title, p);
                lv_label_set_text(ui_sleep_screen.cells[i][j].info, sleep_scr_info_fields[j][i].info);
            }
        }
    }
    else if (count == RECORD_SCREEN) {
        ESP_LOGI(TAG, "load record screen");
        showRecordScreen(0);
    }
    
    else if(count == BOOT_SCREEN) {
        ESP_LOGI(TAG, "load boot screen");
         showBootScreen("Booting");
    }

    else if(count == LOW_BAT_SCREEN) {
        ESP_LOGI(TAG, "load low battery screen");
         showLowBatScreen();
    }

    else if(count == GPS_FAIL_SCREEN) {
        ESP_LOGI(TAG, "load gps fail screen");
         showGpsTroubleScreen();
    }

    else if(count == SD_FAIL_SCREEN) {
        ESP_LOGI(TAG, "load sd fail screen");
         showSdTroubleScreen();
    }

    else if(count == OFF_SCREEN) {
        ESP_LOGI(TAG, "load off screen");
        showSaveSessionScreen("Saving session", "Please wait", "Saving data");
    }

    else if(count == GPS_SCREEN) {
        ESP_LOGI(TAG, "load gps screen");
        showGpsScreen("GPS", "gps test", "gps data", 0, angle);
        // angle += 150;
        // if(angle > 3500)
        // angle = 0;
    }
    else if(count == SPEED_SCREEN){
        ESP_LOGI(TAG, "load speed screen");
        showSpeedScreen();
        lv_label_set_text(ui_speed_screen.speed, "199.9");
        lv_label_set_text(ui_speed_screen.cells[0][0].title, "00.00");
        lv_label_set_text(ui_speed_screen.cells[0][1].title, "00.00");
    }
    
    else if(count == STATS_SCREEN_3) {
        ESP_LOGI(TAG, "load stats screen");
        loadStatsScreen(3,1);
        f2_to_char(last_speed, p);
        lv_label_set_text(ui_stats_screen.cells[0][0].title, p);
        lv_label_set_text(ui_stats_screen.cells[0][0].info, "500M");
    }

    else if(count == STATS_SCREEN_4) {
        ESP_LOGI(TAG, "load stats screen");
        loadStatsScreen(4,1);
        f2_to_char(last_speed, p);
        lv_label_set_text(ui_stats_screen.cells[0][0].title, p);
        lv_label_set_text(ui_stats_screen.cells[0][0].info, "AVG");
    }
    else if(count == STATS_SCREEN_5) {
        ESP_LOGI(TAG, "load stats screen");
        loadStatsScreen(5,1);
        f2_to_char(last_speed, p);
        lv_label_set_text(ui_stats_screen.cells[0][0].title, p);
        lv_label_set_text(ui_stats_screen.cells[0][0].info, "MILE");
    }

    else if(count == STATS_SCREEN_6) {
        ESP_LOGI(TAG, "load stats screen");
        loadStatsScreen(6,1);
        f2_to_char(last_speed, p);
        lv_label_set_text(ui_stats_screen.cells[0][0].title, p);
        lv_label_set_text(ui_stats_screen.cells[0][0].info, "AVG");
    }

   else if(count == WIFI_SCREEN) {
        ESP_LOGI(TAG, "load wifi screen");
        showWifiScreen("majasa","10.0.0.1", "password");
    }
    else if (count == SPLASH_SCREEN) {
        ESP_LOGI(TAG, "load splash screen");
        scr = splashScreenLoad();
    }

   if(lscr) {
    ESP_LOGI(TAG, "delete scr");
        if(lscr==scr)
            scr = 0;
        lv_obj_del(lscr);
    }
    if (_lvgl_lock(-1)) {
        lv_timer_handler();
        _lvgl_unlock();
    }
#if LVGL_VERSION_MAJOR <= 8
    _lv_disp_refr_timer(NULL);
#else
    _lv_display_refr_timer(NULL);
#endif

}

static void timer_cb(lv_timer_t *timer) {
    if(full==0){
        full = 1;
        load_screen(1);
        //display_epd_request_full_update();
    }
    else if(count == 0) {
        display_epd_request_fast_update();
        load_screen(1);
    }
    load_screen(1);
}

void ui_demo(void) {
    button_init();
    btns[0].cb = button_cb;
    init_adc();
    ui_common_init();
    refreshing_sem = xSemaphoreCreateBinary();
    xSemaphoreGive(refreshing_sem);
#if defined(DEBUG)
    ESP_LOGI(TAG, "create timer with 3,5sec interval");
#endif
    lv_disp_t * disp = lv_disp_get_default();
#if LVGL_VERSION_MAJOR <= 8
    lv_timer_del(disp->refr_timer);
    disp->refr_timer = NULL;
#else
    lv_display_delete_refr_timer(disp);
#endif
    timer_cb(0);
}