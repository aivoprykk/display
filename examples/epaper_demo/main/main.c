
#include "button.h"
#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver_vendor.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_ssd168x.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "logger_common.h"
#include "sdkconfig.h"
#include <inttypes.h>
#include <string.h>

#define S(x) #x
#include "img_bitmap.h"
#ifdef CONFIG_DISPLAY_DRIVER_SSD1680
#include "../../../ssd1680_waveshare_2in13_lut.h"
static const char *TAG = "display_drv.ssd1680";
const uint8_t *img_full_p = speed_raw_122x250;
const uint8_t *img_full_l = speed_raw_250x122;
const char *img_bitmap_p = S(speed_raw_122x250);
const char *img_bitmap_l = S(speed_raw_250x122);
#endif
#ifdef CONFIG_DISPLAY_DRIVER_SSD1681
#include "../../../ssd1681_waveshare_1in54_lut.h"
static const char *TAG = "display_drv.ssd1681";
const uint8_t *img_full_p = speed_raw_200x200;
const uint8_t *img_full_l = speed_raw_200x200;
const char *img_bitmap_p = S(speed_raw_200x200);
const char *img_bitmap_l = S(speed_raw_200x200);
#endif
#undef S
#define LCD_HOST SPI2_HOST

#define WAIT_TIME_MS 5000

// static SemaphoreHandle_t epaper_panel_semaphore = 0;
#ifdef CONFIG_DISPLAY_DRIVER_SSD1680
static uint8_t fast_refresh_lut[] = SSD1680_WAVESHARE_2IN13_V2_LUT_FAST_REFRESH_KEEP;
#endif
#ifdef CONFIG_DISPLAY_DRIVER_SSD1681
static uint8_t fast_refresh_lut[] = SSD1681_WAVESHARE_1IN54_V2_LUT_FAST_REFRESH_KEEP;
#endif

// static bool give_semaphore_in_isr(const esp_lcd_panel_handle_t handle, const void *edata, void *user_data)
// {
//     SemaphoreHandle_t *epaper_panel_semaphore_ptr = user_data;
//     BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//     xSemaphoreGiveFromISR(*epaper_panel_semaphore_ptr, &xHigherPriorityTaskWoken);
//     if (xHigherPriorityTaskWoken == pdTRUE) {
//         portYIELD_FROM_ISR();
//         return true;
//     }
//     return false;
// }

typedef struct m_point_s {
    int x1;
    int y1;
    int x2;
    int y2;
    int gap_x;
} m_point_t;

typedef struct img_p_s {
    m_point_t p;
    m_rot_t rotation;
    bool swap;
    bool invert_color;
    bool partial;
} img_p_t;

enum screen_e { BOOT_SCREEN, SPLASH_SCREEN, BLANK_SCREEN, SLEEP_SCREEN, MAX_SCREENS };

esp_lcd_panel_handle_t panel_handle = NULL;
static SemaphoreHandle_t refreshing_sem = NULL;
static int count = 0;
static bool button_down = false;
static int rotation = 2, prev_rotation = 2; // 180 deg, next from default which is 90 deg eq 1
static void load_screen(int noinc);

static void button_cb(int num, l_button_ev_t ev, uint64_t press_time) {
#if defined(DEBUG)
    ESP_LOGI(TAG, "Button %d event: %d time: %llu us", num, ev, press_time);
#endif
    // l_button_t *btn = 0;
    // if(num<1)
    //     btn = &btns[num];
    switch (ev) {
    case L_BUTTON_UP:
        if (xSemaphoreTake(refreshing_sem, portMAX_DELAY) == pdTRUE) {
            button_down = false;
            if (prev_rotation != rotation) {
                prev_rotation = rotation;
                load_screen(2);
            } else if (count == MAX_SCREENS - 1) {
                // display_epd_request_fast_update();
                load_screen(0);
                // load_screen(1);
            } else
                load_screen(0);
            xSemaphoreGive(refreshing_sem);
        }
        break;
    case L_BUTTON_DOWN:
        if (xSemaphoreTake(refreshing_sem, portMAX_DELAY) == pdTRUE) {
            button_down = true;
            xSemaphoreGive(refreshing_sem);
        }
        // if(num==0)
        //     showPushScreen(0,"");
        break;
    case L_BUTTON_LONG_PRESS_START:
        if (num == 0) {
            if (xSemaphoreTake(refreshing_sem, portMAX_DELAY) == pdTRUE) {
                display_epd_ssd168x_set_rotation(rotation++ % 4);
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

static uint8_t converted_buffer_black[LCD_PIXELS_MEM_ALIGNED] = {0};
static int cx = 0;
void drawImg(esp_lcd_panel_handle_t panel_handle, const uint8_t *img, img_p_t *coord) {
    MEAS_START();
    lock_ssd168x(WAIT_TIME_MS);
    ESP_LOGI(TAG, "Drawing image x1=%hu, y1=%hu, x2=%hu, y2=%hu, rotation=%d", coord->p.x1, coord->p.y1, coord->p.x2,
             coord->p.y2, coord->rotation);
    int offsetx1 = coord->p.x1;
    int offsetx2 = coord->p.x2;
    int offsety1 = coord->p.y1;
    int offsety2 = coord->p.y2;
    // Used to vertical traverse lvgl framebuffer
    int len_x =
        (abs(offsetx1 - offsetx2)); // (coord->rotation == DISP_ROT_NONE || coord->rotation == DISP_ROT_180 ? 8 : 1);
    int len_y =
        (abs(offsety1 - offsety2)); // (coord->rotation == DISP_ROT_90 || coord->rotation == DISP_ROT_270 ? 8 : 1);
    // --- Convert buffer from color to monochrome bitmap
    int len_bits = (len_x * len_y);
    int len_bits_aligned =
        ((coord->rotation == DISP_ROT_NONE || coord->rotation == DISP_ROT_180 ? BYTE_PADDING(len_x) : len_x) *
         (coord->rotation == DISP_ROT_90 || coord->rotation == DISP_ROT_270 ? BYTE_PADDING(len_y) : len_y));
    ESP_LOGI(TAG, "[%s] turn on, len x:%hd, y:%hd bits: %d, aligned: %d", __func__, len_x, len_y, len_bits,
             len_bits_aligned);
    display_epd_ssd168x_turn_on(panel_handle);
    int i8 = 0, len_bits_8 = len_bits / 8, len_bits_aligned_8 = len_bits_aligned / 8;
    ESP_LOGI(TAG, "[%s] turned on, next load buffer wit rotation %d bits_aligned: %d", __func__, coord->rotation, len_bits_8);
    memset(converted_buffer_black, 0x00, (len_bits_aligned_8));
    if(img) {
    for (int i= 0, j = len_bits_aligned-1; j>=0; j--, i++) {
        i8 = j / 8;
        uint8_t img_bit = (j%8);
        if (coord->rotation == DISP_ROT_90 || coord->rotation == DISP_ROT_270) {
            // NOTE: Set bits of converted_buffer[] FROM LOW ADDR TO HIGH ADDR, FROM HSB TO LSB
            // NOTE: 1 means BLACK/RED, 0 means WHITE
            // Horizontal traverse lvgl framebuffer (by row)
            // converted_buffer_black[i8] |= (((img[(((((i)*len_x)%(j)) + (i)/(len_y))/8)] & (1u << (7 - (i % 8))))!=0)
            // << (7 - (i % 8)));
            converted_buffer_black[i8] |= (((img[i8] & (1u << (7 - img_bit))) != 0) << (7 - img_bit));
        } else {
            // Vertical traverse lvgl framebuffer (by column), needs to uncomment len_x and len_y
            // NOTE: If your screen rotation requires setting the pixels vertically, you could use the code below
            // k = len_x/8;
            converted_buffer_black[i8] |= (((img[i8] & (1u << (7 - img_bit))) != 0) << (7 - img_bit));
        }
        if(j%8==0 && i>8 && (coord->rotation == DISP_ROT_90 || coord->rotation == DISP_ROT_180)) {
            int col_padded = BYTE_PADDING(len_y)/8; // col last byte
            uint8_t current_byte = converted_buffer_black[i8+1];
            uint8_t prev_byte = (i8 >= 0 ) ? converted_buffer_black[i8] : 0;
            converted_buffer_black[i8+1] = ((current_byte >> (6)) | (prev_byte << (2))) & 0xFF;
        }
    }
    }
    
    ESP_LOGI(TAG, "[%s] refresh and turn off", __func__);
    display_epd_ssd168x_refresh_and_turn_off(panel_handle, coord->rotation,
                                             &((m_area_t){offsetx1, offsety1, offsetx2, offsety2}),
                                             (uint8_t *)converted_buffer_black);

    unlock_ssd168x();
    MEAS_END(TAG, "[%s] took %llu us", __func__);
}

static void load_screen(int noinc) {
    ESP_LOGI(TAG, "load_screen: %d", noinc);

    if (button_down)
        return;

    if (!noinc) {
        if (count++ > MAX_SCREENS - 2)
            count = 0;
    } else if (noinc == 2) {
        // ui_uninit_screens();
        // lv_obj_invalidate(lv_scr_act());
    }

#ifdef CONFIG_DISPLAY_DRIVER_SSD1681
    m_point_t pt_p = {0, 0, 200, 200, 0};
    m_point_t pt_l = {0, 0, 200, 200, 0};
#elif defined(CONFIG_DISPLAY_DRIVER_SSD1680)
    m_point_t pt_p = {0, 0, 122, 250, 6};
    m_point_t pt_l = {0, 0, 250, 122, 6};
#endif
    if (count == BOOT_SCREEN) {
        ESP_LOGI(TAG, "*** Drawing %s (norot, noswap == portrait), noinvert, fastrefr", img_bitmap_p);
        drawImg(panel_handle, img_full_p, &((img_p_t){pt_p, DISP_ROT_NONE, false, false, true}));
        vTaskDelay(pdMS_TO_TICKS(1000));
    } else 
    if (count == BLANK_SCREEN) {
        ESP_LOGI(TAG, "*** Drawing %s (rot90, noswap == landscape), noinvert, fastrefr", img_bitmap_p);
        drawImg(panel_handle, img_full_p, &((img_p_t){pt_l, DISP_ROT_90, false, false, true}));
        vTaskDelay(pdMS_TO_TICKS(1000));
    } else 
    if (count == SPLASH_SCREEN) {
        ESP_LOGI(TAG, "*** Drawing %s (rot180, noswap == portrait), noinvert, fastrefr", img_bitmap_p);
        drawImg(panel_handle, img_full_p, &((img_p_t){pt_p, DISP_ROT_180, false, false, true}));
        vTaskDelay(pdMS_TO_TICKS(1000));
    } else if (count == SLEEP_SCREEN) {
        ESP_LOGI(TAG, "*** Drawing %s (rot270, noswap == landscape), noinvert, fastrefr", img_bitmap_p);
        drawImg(panel_handle, img_full_p, &((img_p_t){pt_l, DISP_ROT_270, false, false, true}));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    // // --- Draw partial bitmap
    // ESP_LOGI(TAG, "Show image partial");
    // lock_ssd168x(WAIT_TIME_MS);
    // ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, false, false));
    // ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, false));
    // ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, false));
    // ESP_LOGI(TAG, "Drawing bitmap BITMAP_64_128 no mirror ... ");
    // ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, 16, 0, 80, 128, BITMAP_64_128));
    // ESP_ERROR_CHECK(epaper_panel_refresh_screen_ssd168x(panel_handle, 0x0));

    // lock_ssd168x(WAIT_TIME_MS);
    // ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, false, true));
    // ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, false));
    // ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, false));
    // ESP_LOGI(TAG, "Drawing bitmap BITMAP_128_64 mirrored y ...");
    // ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, 16, 64, 144, 128, BITMAP_128_64));
    // ESP_ERROR_CHECK(epaper_panel_refresh_screen_ssd168x(panel_handle, 0x0));

    // lock_ssd168x(WAIT_TIME_MS);
    // ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, false));
    // ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, false));
    // ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, false));
    // ESP_LOGI(TAG, "Drawing bitmap BITMAP_128_64 mirrored x ...");
    // ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, 16, 64, 144, 128, BITMAP_128_64));
    // ESP_ERROR_CHECK(epaper_panel_refresh_screen_ssd168x(panel_handle, 0x0));

    // lock_ssd168x(WAIT_TIME_MS);
    // ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, true));
    // ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, false));
    // ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, false));
    // ESP_LOGI(TAG, "Drawing bitmap BITMAP_128_64 mirrored x and y ...");
    // ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, 16, 0, 144, 64, BITMAP_128_64));
    // ESP_ERROR_CHECK(epaper_panel_refresh_screen_ssd168x(panel_handle, 0x0));

    // vTaskDelay(pdMS_TO_TICKS(5000));
    // ESP_LOGI(TAG, "Go to sleep mode...");
    // esp_lcd_panel_disp_on_off(panel_handle, false);
}

void app_main(void) {
    button_init();
    btns[0].cb = button_cb;

    refreshing_sem = xSemaphoreCreateBinary();
    xSemaphoreGive(refreshing_sem);

    panel_handle = display_new();
    if (!panel_handle) {
        ESP_LOGE(TAG, "Failed to create LCD panel handle");
        return;
    }

    // --- Reset the display
    ESP_LOGI(TAG, "Resetting e-Paper display...");
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    // --- Initialize LCD panel
    ESP_LOGI(TAG, "Initializing e-Paper display...");
    ESP_ERROR_CHECK(epaper_panel_init_screen_ssd168x(panel_handle, INIT_MODE_FULL_1, 0));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    // --- Set the callback function

    load_screen(2);
    load_screen(2);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    vSemaphoreDelete(refreshing_sem);
    display_del(panel_handle);
    button_deinit();
}
