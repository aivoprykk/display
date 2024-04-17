#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "esp_system.h"

#include "esp_err.h"
#include "esp_log.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"

#include <esp_lcd_panel_ops.h>
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_vendor.h>

#include "logger_common.h"
#include "driver_vendor.h"
#include "ui.h"

#include "esp_lcd_panel_ssd1680.h"

#include "ssd1680_waveshare_2in13_lut.h"

static const char *TAG = "display_drv.ssd1680";

#ifdef CONFIG_DISPLAY_DRIVER_SSD1680

#define LCD_HOST SPI3_HOST  // ssd on VSPI_HOST

#define PIN_NUM_SCLK           CONFIG_DISPLAY_SPI_CLK
#define PIN_NUM_MOSI           CONFIG_DISPLAY_SPI_MOSI
#define PIN_NUM_MISO           CONFIG_DISPLAY_SPI_MISO
#define PIN_NUM_EPD_DC         CONFIG_DISPLAY_DC
#define PIN_NUM_EPD_RST        CONFIG_DISPLAY_RST
#define PIN_NUM_EPD_CS         CONFIG_DISPLAY_SPI_CS
#define PIN_NUM_EPD_BUSY       CONFIG_DISPLAY_BUSY

#define LCD_PIXEL_CLOCK_HZ     (20 * 1000 * 1000)

// Bit number used to represent command and parameter
#define LCD_CMD_BITS           8
#define LCD_PARAM_BITS         8

#define LVGL_TICK_PERIOD_MS    2

static SemaphoreHandle_t panel_refreshing_sem = NULL;
static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
static lv_disp_drv_t disp_drv;      // contains callback functions

static uint8_t *converted_buffer_black;
static uint8_t *converted_buffer_red;

esp_lcd_panel_handle_t panel_handle = NULL;
esp_lcd_panel_io_handle_t io_handle = NULL;
static uint32_t update_count = 0;
static uint8_t fast_refresh_lut[] = SSD1680_WAVESHARE_2IN13_V2_LUT_FAST_REFRESH_KEEP;

IRAM_ATTR bool epaper_flush_ready_callback(const esp_lcd_panel_handle_t handle, const void *edata, void *user_data)
{
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *) user_data;
    lv_disp_flush_ready(disp_driver);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(panel_refreshing_sem, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE) {
        return true;
    }
    return false;
}

static void epaper_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
    TIMER_S
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // Used to vertical traverse lvgl framebuffer
    // int len_x = abs(offsetx1 - offsetx2) + 1;
    // int len_y = abs(offsety1 - offsety2) + 1;
    // --- Convert buffer from color to monochrome bitmap
    int len_bits = (abs(offsetx1 - offsetx2) + 1) * (abs(offsety1 - offsety2) + 1);

    memset(converted_buffer_black, 0x00, len_bits / 8);
    memset(converted_buffer_red, 0x00, len_bits / 8);
    for (int i = 0; i < len_bits; i++) {
        // NOTE: Set bits of converted_buffer[] FROM LOW ADDR TO HIGH ADDR, FROM HSB TO LSB
        // NOTE: 1 means BLACK/RED, 0 means WHITE
        // Horizontal traverse lvgl framebuffer (by row)
        converted_buffer_black[i / 8] |= (((lv_color_brightness(color_map[i])) < 251) << (7 - (i % 8)));
        converted_buffer_red[i / 8] |= ((((color_map[i].ch.red) > 3) && ((lv_color_brightness(color_map[i])) < 251)) << (7 - (i % 8)));
        // Vertical traverse lvgl framebuffer (by column), needs to uncomment len_x and len_y
        // NOTE: If your screen rotation requires setting the pixels vertically, you could use the code below
        // converted_buffer[i/8] |= (((lv_color_brightness(color_map[((i*len_x)%len_bits) + i/len_y])) > 250) << (7-(i % 8)));
    }
    if(update_count==0)
        ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
    /* 
    else if(update_count==1)
        ESP_ERROR_CHECK(epaper_panel_set_custom_lut(panel_handle, fast_refresh_lut, 159)); */
    // --- Draw bitmap
    ESP_ERROR_CHECK(epaper_panel_set_bitmap_color_ssd1680(panel_handle, SSD1680_EPAPER_BITMAP_BLACK));
    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, converted_buffer_black));
    ESP_ERROR_CHECK(epaper_panel_set_bitmap_color_ssd1680(panel_handle, SSD1680_EPAPER_BITMAP_RED));
    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, converted_buffer_red));
    ESP_ERROR_CHECK(epaper_panel_refresh_screen_ssd1680(panel_handle, update_count>0?2:0));
    ++update_count;
    if(update_count==50) update_count=0;
    TIMER_E
}

static void epaper_lvgl_wait_cb(struct _lv_disp_drv_t *disp_drv)
{
    LOGR
    xSemaphoreTake(panel_refreshing_sem, portMAX_DELAY);
}

/* Rotate display and touch, when rotated screen in LVGL. Called when driver parameters are updated. */
static void epaper_lvgl_port_update_callback(lv_disp_drv_t *drv)
{
    LOGR
    /* esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;

    switch (drv->rotated) {
    case LV_DISP_ROT_NONE:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, false, false);
        break;
    case LV_DISP_ROT_90:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, false, true);
        break;
    case LV_DISP_ROT_180:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, true, true);
        break;
    case LV_DISP_ROT_270:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, true, false);
        break;
    } */
}

static void increase_lvgl_tick(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

bool _lvgl_lock(int timeout_ms) {
    LOGR
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
    //const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return true; // xSemaphoreTake(panel_refreshing_sem, timeout_ticks) == pdTRUE;
}

void _lvgl_unlock(void) {
    LOGR
    //xSemaphoreGiveRecursive(panel_refreshing_sem);
}

esp_lcd_panel_handle_t display_ssd1680_new() {
    TIMER_S
    panel_refreshing_sem = xSemaphoreCreateBinary();
    xSemaphoreGive(panel_refreshing_sem);

    // Initialize GPIOs direction & initial states
    gpio_set_direction(PIN_NUM_EPD_CS, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_NUM_EPD_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_NUM_EPD_RST, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_NUM_EPD_BUSY, GPIO_MODE_INPUT);
    gpio_set_pull_mode(PIN_NUM_EPD_BUSY, GPIO_PULLUP_ONLY);
    esp_err_t err = 0;
    err = gpio_set_level(PIN_NUM_EPD_CS, 1);
    if(err) {
        ESP_LOGE(TAG, "display_ssd1680_new err: %s", esp_err_to_name(err));
    }
    err = gpio_set_level(PIN_NUM_EPD_DC, 1);
    if(err) {
        ESP_LOGE(TAG, "display_ssd1680_new err: %s", esp_err_to_name(err));
    }
    err = gpio_set_level(PIN_NUM_EPD_RST, 1);
    if(err) {
        ESP_LOGE(TAG, "display_ssd1680_new err: %s", esp_err_to_name(err));
    }

    ESP_LOGI(TAG, "Initialize SPI bus");
    spi_bus_config_t buscfg = {
        .sclk_io_num = PIN_NUM_SCLK,
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = EPD_BUFFER_SIZE,
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, 2));

    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = PIN_NUM_EPD_DC,
        .cs_gpio_num = PIN_NUM_EPD_CS,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ,
        .lcd_cmd_bits = LCD_CMD_BITS,
        .lcd_param_bits = LCD_PARAM_BITS,
        .spi_mode = 0,
        .trans_queue_depth = 10,
        .on_color_trans_done = NULL,
    };
    // --- Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t) LCD_HOST, &io_config, &io_handle));

    // --- Create esp_lcd panel
    esp_lcd_ssd1680_config_t epaper_ssd1680_config = {
        .busy_gpio_num = PIN_NUM_EPD_BUSY,
        .non_copy_mode = false,
    };
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = PIN_NUM_EPD_RST,
        .flags.reset_active_high = false,
        .vendor_config = &epaper_ssd1680_config
    };
    gpio_install_isr_service(0);
    ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1680(io_handle, &panel_config, &panel_handle));

    // --- Reset the display
    ESP_LOGI(TAG, "Resetting e-Paper display...");
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    // --- Initialize panel
    ESP_LOGI(TAG, "Initializing e-Paper display...");
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
#if (LCD_H_GAP>0) || (LCD_V_GAP>0)
    //  the gap is LCD panel specific, even panels with the same driver IC, can
    //  have different gap value
    esp_lcd_panel_set_gap(panel_handle, LCD_H_GAP, LCD_V_GAP);
#endif
    // --- Register the e-Paper refresh done callback
    epaper_panel_callbacks_t cbs = {
        .on_epaper_refresh_done = epaper_flush_ready_callback
    };
    epaper_panel_register_event_callbacks_ssd1680(panel_handle, &cbs, &disp_drv);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    // --- Turn on display
    ESP_LOGI(TAG, "Turning e-Paper display on...");
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    // --- Configurate the screen
    // NOTE: the configurations below are all FALSE by default
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, false, false));
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, true));
    esp_lcd_panel_invert_color(panel_handle, false);
    // NOTE: Calling esp_lcd_panel_disp_on_off(panel_handle, true) will reset the LUT to the panel built-in one,
    // custom LUT will not take effect any more after calling esp_lcd_panel_disp_on_off(panel_handle, true)
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
    // Set custom lut
    // NOTE: Setting custom LUT is not necessary. Panel built-in LUT is used calling after esp_lcd_panel_disp_on_off()
    // NOTE: Uncomment code below to see difference between full refresh & fast refresh
    // NOTE: epaper_panel_set_custom_lut() must be called AFTER calling esp_lcd_panel_disp_on_off()
    ESP_ERROR_CHECK(epaper_panel_set_custom_lut_ssd1680(panel_handle, fast_refresh_lut, 159));

    // --- Initialize LVGL
    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();

    uint32_t fb_size = EPD_BUFFER_SIZE, pix_buf_size = LCD_H_RES * LCD_V_RES / 5;
    // alloc draw buffers used by LVGL
    // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
    lv_color_t *buf1 = heap_caps_malloc(pix_buf_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1);
    lv_color_t *buf2 = heap_caps_malloc(pix_buf_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2);
    // alloc bitmap buffer to draw
    converted_buffer_black = heap_caps_malloc(fb_size, MALLOC_CAP_DMA);
    converted_buffer_red = heap_caps_malloc(fb_size, MALLOC_CAP_DMA);
    // initialize LVGL draw buffers
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, pix_buf_size);
    // initialize LVGL display driver
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_H_RES;
    disp_drv.ver_res = LCD_V_RES;
    disp_drv.flush_cb = epaper_lvgl_flush_cb;
    disp_drv.wait_cb = epaper_lvgl_wait_cb;
    disp_drv.drv_update_cb = epaper_lvgl_port_update_callback;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.user_data = panel_handle;
    // NOTE: The ssd1680 e-paper is monochrome and 1 byte represents 8 pixels
    // so full_refresh is MANDATORY because we cannot set position to bitmap at pixel level
    disp_drv.full_refresh = true;
    ESP_LOGI(TAG, "Register display driver to LVGL");
    //lv_disp_t *disp = 
    lv_disp_drv_register(&disp_drv);
    
    // init lvgl tick
    ESP_LOGI(TAG, "Install LVGL tick timer");
    // Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &increase_lvgl_tick,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, LVGL_TICK_PERIOD_MS * 1000));

    ui_init();
    TIMER_E
    return panel_handle;
}

void display_ssd1680_del() {
    LOGR
    lv_deinit();
    esp_lcd_panel_del(panel_handle);
    esp_lcd_panel_io_del(io_handle);
    heap_caps_free(converted_buffer_black);
    heap_caps_free(converted_buffer_red);
    vSemaphoreDelete(panel_refreshing_sem);
}

#endif