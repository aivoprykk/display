
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "esp_system.h"

#include "esp_err.h"
#include "esp_log.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"

#include "rom/gpio.h"
#include "driver/gpio.h"
#include "soc/gpio_sig_map.h"
#include "driver/ledc.h"

#include "driver/spi_common.h"
#include "driver/spi_master.h"

#include "display_private.h"
#include <logger_common.h>
#include "driver_vendor.h"

static const char *TAG = "display_drv.st7789";

#ifdef CONFIG_DISPLAY_DRIVER_ST7789

#define LCD_HOST SPI2_HOST  // ssd on HSPI_HOST

#define SPI_D_DMA_CHAN 1

#define PIN_NUM_SCLK           CONFIG_DISPLAY_SPI_CLK
#define PIN_NUM_MOSI           CONFIG_DISPLAY_SPI_MOSI
#define PIN_NUM_MISO           (-1)   // Unused
#define PIN_NUM_DC         CONFIG_DISPLAY_DC
#define PIN_NUM_RST        CONFIG_DISPLAY_RST
#define PIN_NUM_CS         CONFIG_DISPLAY_SPI_CS
#define PIN_NUM_BUSY       CONFIG_DISPLAY_BUSY

#define LCD_MODULE_CMD_1
#define LCD_PIXEL_CLOCK_HZ (6528000UL)  //(6 * 1000 * 1000)

#define L_LVGL_TICK_PERIOD_MS 2

#define PSRAM_DATA_ALIGNMENT 64

static SemaphoreHandle_t panel_refreshing_sem = NULL;
static lv_disp_draw_buf_t disp_buf;  // contains internal graphic buffer(s) called draw buffer(s)
static lv_disp_drv_t disp_drv;       // contains callback functions

//static uint8_t *converted_buffer_black;
//static uint8_t *converted_buffer_red;

//static lv_color_t *lv_disp_buf[LCD_BUF_SIZE_DIV_10];
//static lv_color_t *lv_disp_buf2[LCD_BUF_SIZE_DIV_10];

static esp_lcd_panel_handle_t panel_handle = NULL;
static esp_lcd_panel_io_handle_t io_handle = NULL;
static esp_lcd_i80_bus_handle_t bus_handle = NULL;

static bool is_initialized_lvgl = false;

typedef struct {
    uint8_t cmd;
    uint8_t data[14];
    uint8_t len;
} lcd_cmd_t;

static const lcd_cmd_t lcd_st7789v[] = {
    {0x11, {0}, 0 | 0x80},
    {0x3A, {0X05}, 1},
    {0xB2, {0X0B, 0X0B, 0X00, 0X33, 0X33}, 5},
    {0xB7, {0X75}, 1},
    {0xBB, {0X28}, 1},
    {0xC0, {0X2C}, 1},
    {0xC2, {0X01}, 1},
    {0xC3, {0X1F}, 1},
    {0xC6, {0X13}, 1},
    {0xD0, {0XA7}, 1},
    {0xD0, {0XA4, 0XA1}, 2},
    {0xD6, {0XA1}, 1},
    {0xE0, {0XF0, 0X05, 0X0A, 0X06, 0X06, 0X03, 0X2B, 0X32, 0X43, 0X36, 0X11, 0X10, 0X2B, 0X32}, 14},
    {0xE1, {0XF0, 0X08, 0X0C, 0X0B, 0X09, 0X24, 0X2B, 0X22, 0X43, 0X38, 0X15, 0X16, 0X2F, 0X37}, 14},

};

static void bl_init() {
    ILOG(TAG, "[%s]", __func__);
    const ledc_channel_config_t LCD_backlight_channel = {
        .gpio_num = CONFIG_DISPLAY_BL,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0};
    const ledc_timer_config_t LCD_backlight_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 10000,
        .clk_cfg = LEDC_AUTO_CLK};

    ledc_timer_config(&LCD_backlight_timer);
    ledc_channel_config(&LCD_backlight_channel);
    gpio_matrix_out(CONFIG_DISPLAY_BL, SIG_GPIO_OUT_IDX, true, 0);
}

/**
 * @brief Set the backlight brightness of the display
 * 
 * @param brightness_percent The brightness of the backlight, expressed as a percentage (0-100)
 */
void driver_st7789_bl_set(uint8_t brightness_percent) {
    ILOG(TAG, "[%s] backlight brightness to %hhu", __func__, brightness_percent);
    uint32_t duty_cycle = (254 * brightness_percent) / 100;
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty_cycle);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

static bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx) {
    if (is_initialized_lvgl) {
        lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
        assert(disp_driver);
        lv_disp_flush_ready(disp_driver);
    }
    return false;
}

/**
 * @brief Notify the LVGL driver that a flush is ready
 *
 * @param panel_io The LCD panel I/O handle
 * @param edata The event data
 * @param user_ctx The user context
 * @return Whether the event was handled
 */
static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map) {
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // copy a buffer's content to a specific area of the display
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
}

static void increase_lvgl_tick(void *arg) {
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(L_LVGL_TICK_PERIOD_MS*1000);
}

#if defined(CONFIG_DISPLAY_DRIVER_ST7789)
bool _lvgl_lock(int timeout_ms) {
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTakeRecursive(panel_refreshing_sem, timeout_ticks) == pdTRUE;
}

void _lvgl_unlock(void) {
    xSemaphoreGiveRecursive(panel_refreshing_sem);
}
#endif
void display_st7789_init_cb(lv_disp_drv_t *disp_drv) {
    ILOG(TAG, "[%s]", __func__);
    // Set the callback functions
    disp_drv->hor_res = LCD_H_RES;
    disp_drv->ver_res = LCD_V_RES;
    disp_drv->flush_cb = lvgl_flush_cb;
    // disp_drv->wait_cb = lvgl_wait_cb;
    // disp_drv->drv_update_cb = epaper_lvgl_port_update_callback;
    disp_drv->user_data = panel_handle;
}

/**
 * @brief Initialize the screen
 * 
 */
static void init_screen(void (*cb)(lv_disp_drv_t *)) {
    ILOG(TAG, "[%s]", __func__);
    // --- Initialize LVGL
    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();
    // alloc draw buffers used by LVGL
    // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
    ESP_LOGI(TAG, "Allocate memory");
    size_t bufsz = LCD_BUF_SIZE;
    //memset(lv_disp_buf, 0, sizeof(lv_disp_buf));
    //memset(lv_disp_buf2, 0, sizeof(lv_disp_buf2));
    lv_color_t *buf1 = heap_caps_malloc(bufsz * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1);
    lv_color_t *buf2 = heap_caps_malloc(bufsz * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2);
    // initialize LVGL draw buffers
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, bufsz);
    //lv_disp_draw_buf_init(&disp_buf, &(lv_disp_buf[0]), &(lv_disp_buf2[0]), bufsz);
    // initialize LVGL display driver
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;

    cb(&disp_drv);

    ESP_LOGI(TAG, "Register display driver to LVGL");
    //lv_disp_t *disp = 
    lv_disp_drv_register(&disp_drv);
    is_initialized_lvgl = true;

    // init lvgl tick
    ESP_LOGI(TAG, "Install LVGL tick timer");
    // Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &increase_lvgl_tick,
        .name = "lvgl_tick"};
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, L_LVGL_TICK_PERIOD_MS * 1000));
}

esp_lcd_panel_handle_t display_st7789_new() {
    ILOG(TAG, "[%s]", __func__);

    panel_refreshing_sem = xSemaphoreCreateRecursiveMutex();
    xSemaphoreGiveRecursive(panel_refreshing_sem);

    gpio_set_direction(CONFIG_DISPLAY_RD, GPIO_MODE_OUTPUT);
    gpio_set_level(CONFIG_DISPLAY_RD, 1);
    bl_init();

    esp_lcd_i80_bus_config_t bus_config = {
        .dc_gpio_num = PIN_NUM_DC,
        .wr_gpio_num = CONFIG_DISPLAY_WR,
        .clk_src = LCD_CLK_SRC_PLL160M,
        .data_gpio_nums =
        {
            CONFIG_DISPLAY_D0,
            CONFIG_DISPLAY_D1,
            CONFIG_DISPLAY_D2,
            CONFIG_DISPLAY_D3,
            CONFIG_DISPLAY_D4,
            CONFIG_DISPLAY_D5,
            CONFIG_DISPLAY_D6,
            CONFIG_DISPLAY_D7,
        },
        .bus_width = 8,
        .max_transfer_bytes = LCD_PIXELS * sizeof(uint16_t), // LVGL_LCD_BUF_SIZE * sizeof(uint16_t),
        .psram_trans_align = PSRAM_DATA_ALIGNMENT, // PSRAM_DATA_ALIGNMENT,
        .sram_trans_align = 4,
    };
    ESP_ERROR_CHECK(esp_lcd_new_i80_bus(&bus_config, &bus_handle));

    esp_lcd_panel_io_i80_config_t io_config = {
        .cs_gpio_num = PIN_NUM_CS,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ, // LCD_PIXEL_CLOCK_HZ,
        .trans_queue_depth = 20,
        .on_color_trans_done = notify_lvgl_flush_ready,
        .user_ctx = &disp_drv,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .dc_levels =
        {
            .dc_idle_level = 0,
            .dc_cmd_level = 0,
            .dc_dummy_level = 0,
            .dc_data_level = 1,
        },
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(bus_handle, &io_config, &io_handle));

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = PIN_NUM_RST,
        .color_space = ESP_LCD_COLOR_SPACE_RGB,
        .bits_per_pixel = 16,
        .vendor_config = NULL
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));
    // --- Reset the display
    ESP_LOGI(TAG, "Resetting st7789 display...");
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    // --- Initialize panel
    ESP_LOGI(TAG, "Initializing st7789 display...");
    //#define LCD_CMD_SLPOUT          0x11
    esp_lcd_panel_io_tx_param(io_handle, 0x11, NULL, 0);
    //vTaskDelay(pdMS_TO_TICKS(100));
    // flush color before turn on the display
    uint16_t image[800];
    uint32_t sz = sizeof(image)/sizeof(image[0]);
    for (uint16_t x = 0; x < sz; ++x) {
            image[x] = (15 << 11) | (31 << 5) | 15;
    }
    for (uint16_t i = 0; i < LCD_H_RES; i++) {
        //#define LCD_CMD_RAMWRC          0x3c
        esp_lcd_panel_io_tx_color(io_handle, 0x3c, image, sz);
    }
    //ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    //delay_ms(100);
    // --- Configurate the screen
    // NOTE: the configurations below are all FALSE by default
    esp_lcd_panel_invert_color(panel_handle, true);
    esp_lcd_panel_swap_xy(panel_handle, true);
    esp_lcd_panel_mirror(panel_handle, true, false);
#if (LCD_H_GAP>0) || (LCD_V_GAP>0)
    //  the gap is LCD panel specific, even panels with the same driver IC, can
    //  have different gap value
    esp_lcd_panel_set_gap(panel_handle, LCD_H_GAP, LCD_V_GAP);
#endif
#if defined(LCD_MODULE_CMD_1)
    // send panel init commands
    for (uint8_t i = 0; i < (sizeof(lcd_st7789v) / sizeof(lcd_cmd_t)); i++) {
        esp_lcd_panel_io_tx_param(io_handle, lcd_st7789v[i].cmd, lcd_st7789v[i].data, lcd_st7789v[i].len & 0x7f);
        if (lcd_st7789v[i].len & 0x80)
            delay_ms(120);
    }
    //delay_ms(100);
#endif
        // --- Turn on display
    ESP_LOGI(TAG, "Turning st7789 display on...");
    // #define LCD_CMD_DISPON          0x29
    esp_lcd_panel_io_tx_param(io_handle, 0x29, NULL, 0);
     
    //delay_ms(100);
    init_screen(display_st7789_init_cb);

    ESP_LOGI(TAG, "Create LVGL task");

    //ui_init();

    return panel_handle;
}

void display_st7789_del() {
    ILOG(TAG, "[%s]", __func__);

    lv_deinit();
    esp_lcd_panel_del(panel_handle);
    esp_lcd_panel_io_del(io_handle);
    vSemaphoreDelete(panel_refreshing_sem);
}

#endif