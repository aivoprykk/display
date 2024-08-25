#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_timer.h"

#include "esp_err.h"
#include "esp_log.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"

#include <esp_lcd_panel_ops.h>
// #include <esp_lcd_panel_io.h>
// #include <esp_lcd_panel_vendor.h>

#include "driver_vendor.h"
#include "ui_events.h"
#include "display_private.h"
#include "logger_common.h"
#include "esp_lcd_panel_ssd168x.h"

#ifdef CONFIG_DISPLAY_DRIVER_SSD1681
#include "ssd1681_waveshare_1in54_lut.h"
static const char *TAG = "display_drv.ssd1681";
#else
#include "ssd1680_waveshare_2in13_lut.h"
static const char *TAG = "display_drv.ssd1680";
#endif

#if defined(CONFIG_HAS_BOARD_LILYGO_EPAPER_T5)
#define LCD_HOST SPI3_HOST
#else
#define LCD_HOST SPI2_HOST
#endif

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

#define LVGL_TICK_PERIOD_MS    100

static SemaphoreHandle_t panel_refreshing_sem = NULL;

#ifdef CONFIG_DISPLAY_USE_LVGL
static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
static lv_disp_drv_t disp_drv;      // contains callback functions
static lv_disp_t *lv_disp = NULL;
lv_color_t buf1[LCD_RESOLUTION] = {0};
static bool is_initialized_lvgl = false;
// static uint32_t update_count = 0;
#else
static int rotated = DISP_ROT_90;
#endif
static uint8_t converted_buffer_black[LCD_PIXELS_MEM_ALIGNED] = {0};

//static uint8_t *converted_buffer_red;

static esp_lcd_panel_handle_t panel_handle = NULL;
static esp_lcd_panel_io_handle_t io_handle = NULL;
#ifdef CONFIG_DISPLAY_DRIVER_SSD1681
static uint8_t fast_refresh_lut[] = SSD1681_WAVESHARE_1IN54_V2_LUT_FAST_REFRESH_KEEP;
#else
static uint8_t fast_refresh_lut[] = SSD1680_WAVESHARE_2IN13_V2_LUT_FAST_REFRESH_KEEP;
#endif
static bool init_requested = true;
static epaper_panel_init_mode_t init_mode = INIT_MODE_FULL_2;
// const unsigned char clear_img[LCD_PIXELS_MEM_ALIGNED] = { [0 ... LCD_PIXELS_MEM_ALIGNED-1] = 0xFF };

IRAM_ATTR bool epaper_flush_ready_callback(const esp_lcd_panel_handle_t handle, const void *edata, void *user_data)
{
#ifdef CONFIG_DISPLAY_USE_LVGL
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *) user_data;
    lv_disp_flush_ready(disp_driver);
#endif
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(panel_refreshing_sem, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE) {
        return true;
    }
    return false;
}

esp_err_t display_epd_ssd168x_request_full_update()
{
    ILOG(TAG, "[%s]", __func__);
    init_mode = INIT_MODE_FULL_1;
    init_requested = true;
    return ESP_OK;
}

esp_err_t display_epd_ssd168x_request_fast_update()
{
    ILOG(TAG, "[%s]", __func__);
    init_mode = INIT_MODE_FULL_2;
    init_requested = true;
    return ESP_OK;
}

#ifdef CONFIG_DISPLAY_USE_LVGL
lv_disp_drv_t * display_ssd1680_get_driver()
{
    return &disp_drv;
}

lv_disp_t * display_ssd1680_get()
{
    return lv_disp;
}
#endif

esp_err_t display_epd_ssd168x_set_rotation(int r) {
    ILOG(TAG, "[%s] %d", __func__, r);
    if(r > DISP_ROT_270)
        return ESP_ERR_INVALID_ARG;
#if defined(CONFIG_DISPLAY_USE_LVGL)
    if(r!=disp_drv.rotated) {
        disp_drv.rotated = r;
        lv_disp_drv_update(lv_disp, &disp_drv); //this is critical!
        if(lv_scr_act()) {
            lv_obj_invalidate(lv_scr_act());
        }
    }
#if (CONFIG_DISPLAY_LOG_LEVEL < 2)
    printf("New orientation is %d:, rotated flag is :%d, hor_res is: %d, ver_res is: %d\r\n", \
        (int)r, disp_drv.rotated, lv_disp_get_hor_res(lv_disp), lv_disp_get_ver_res(lv_disp));
#endif
#else
    if(r!=rotated) {
        rotated = r;
    }
#if (CONFIG_DISPLAY_LOG_LEVEL < 2)
    printf("New orientation is %d:, rotated flag is :%d\r\n", (int)r, rotated);
#endif
#endif
    return ESP_OK;
}

esp_err_t display_epd_ssd168x_turn_on(esp_lcd_panel_handle_t panel_handle)
{
    ILOG(TAG, "[%s]", __func__);
    const char *x = "e-Paper display...";
    UNUSED_PARAMETER(x);
    if(init_requested) {
        ILOG(TAG, "[%s] %s %s with init mode 0x%02x", "Reset/Init", __func__, x, init_mode);
        ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
        delay_ms(50);
        ESP_ERROR_CHECK(epaper_panel_init_screen_ssd168x(panel_handle, init_mode, 0));
        init_mode = INIT_MODE_FULL_2;
        delay_ms(50);
    }
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
    if(!init_requested) {
        ILOG(TAG, "[%s] %s %s", "Refresh", __func__, x);
        ESP_ERROR_CHECK(epaper_panel_set_custom_lut_ssd168x(panel_handle, fast_refresh_lut, 159));
    }
    if(init_requested) init_requested = false;
    return ESP_OK;
}

esp_err_t display_epd_ssd168x_refresh_and_turn_off(esp_lcd_panel_handle_t panel_handle, int rotated, m_area_t *area, uint8_t *color_map)
{
    ILOG(TAG, "[%s]", __func__);
    if(rotated == DISP_ROT_NONE || rotated == DISP_ROT_180) {
        ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, false));
#ifdef CONFIG_DISPLAY_USE_LVGL
        ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, false));
#endif
    }
    else {
        ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, true));
#ifdef CONFIG_DISPLAY_USE_LVGL
        ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));
#endif
    }

    if(rotated == DISP_ROT_NONE) {
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, false, false)); // x inc y inc
    }
    else if(rotated == DISP_ROT_90) {
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, false)); // x *dec y inc
    }
    else if(rotated == DISP_ROT_180) {
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, true)); // x *dec y *dec
    }
    else { // DISP_ROT_270 (270 degrees)
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, false, true)); // x inc y *dec
    }

    ESP_ERROR_CHECK(epaper_panel_set_bitmap_color_ssd168x(panel_handle, SSD168X_EPAPER_BITMAP_BLACK));
    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle,  area->x1,  area->y1, area->x2 + 1, area->y2 + 1, color_map));
    ESP_ERROR_CHECK(epaper_panel_set_bitmap_color_ssd168x(panel_handle, SSD168X_EPAPER_BITMAP_RED));
    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle,  area->x1,  area->y1, area->x2 + 1, area->y2 + 1, color_map));
    ESP_ERROR_CHECK(epaper_panel_refresh_screen_ssd168x(panel_handle, 0));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, false));
    return ESP_OK;
}

#ifdef CONFIG_DISPLAY_USE_LVGL
static void epaper_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
#if (CONFIG_DISPLAY_LOG_LEVEL < 2)
    printf("flush_cb: display_get_width(display_get_driver()) %d\n", display_get_width(display_get()));
#endif
    ILOG(TAG, "[%s] x1:%hd y1:%hd, x2:%hd y2:%hd", __func__, area->x1, area->y1, area->x2, area->y2);
    IMEAS_START();
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // Used to vertical traverse lvgl framebuffer
    int len_x = abs(offsetx1 - offsetx2)+1;
    int len_y = abs(offsety1 - offsety2)+1;
#if defined(CONFIG_DISPLAY_DRIVER_SSD1680)
    if(drv->rotated==LV_DISP_ROT_270 || drv->rotated==LV_DISP_ROT_90) len_y = BYTE_PADDING(len_y);
    else len_x = BYTE_PADDING(len_x);
#endif
    // else len_x = BYTE_PADDING(len_x);
    // --- Convert buffer from color to monochrome bitmap
    int len_bits = (len_x * len_y);
    ILOG(TAG, "[%s] turn on, len x:%hd, y:%hd bits: %d, orig_len_x: %hd, orig_len_y: %hd", __func__, len_x, len_y, len_bits, abs(offsetx1 - offsetx2), abs(offsety1 - offsety2));
    display_epd_ssd168x_turn_on(panel_handle);
    ILOG(TAG, "[%s] turned on, next load buffer wit rotation %d", __func__,drv->rotated);
    memset(converted_buffer_black, 0x00, (len_bits / 8));
    for (int i = len_bits-1, i8, j=0; i >=0; i--,j++) {
        i8 = i / 8;
        uint8_t bit_index = i % 8;
        if(drv->rotated == LV_DISP_ROT_90 || drv->rotated == LV_DISP_ROT_270) {
        // NOTE: Set bits of converted_buffer[] FROM LOW ADDR TO HIGH ADDR, FROM HSB TO LSB
        // NOTE: 1 means BLACK/RED, 0 means WHITE
        // Horizontal traverse lvgl framebuffer (by row)
          converted_buffer_black[i8] |= (((lv_color_brightness(color_map[((i*len_x)%len_bits) + i/len_y])) > 250) << (7 - (bit_index)));
        }
        else{
        // Vertical traverse lvgl framebuffer (by column), needs to uncomment len_x and len_y
        // NOTE: If your screen rotation requires setting the pixels vertically, you could use the code below
          converted_buffer_black[i8] |= (((lv_color_brightness(color_map[i])) <= 250) << (7 - (bit_index)));
        }
#if defined(CONFIG_DISPLAY_DRIVER_SSD1680)
        if(bit_index==0 && j>8 && (drv->rotated == DISP_ROT_90 || drv->rotated == DISP_ROT_180)) {
            uint8_t current_byte = converted_buffer_black[i8+1];
            uint8_t prev_byte = (i8 >= 0 ) ? converted_buffer_black[i8] : 0;
            converted_buffer_black[i8+1] = ((current_byte >> (6)) | (prev_byte << (2))) & 0xFF;
        }
#endif
    }
    // --- Draw bitmap
    ILOG(TAG, "[%s] refresh and turn off", __func__);
    display_epd_ssd168x_refresh_and_turn_off(panel_handle, drv->rotated, &((m_area_t) {offsetx1, offsety1, offsetx2, offsety2}), converted_buffer_black);
    IMEAS_END(TAG, "[%s] area %d x %d flush took %llu us", __func__, len_x, len_y);
    esp_event_post(UI_EVENT, UI_EVENT_FLUSH_DONE, 0, 0, portMAX_DELAY);
}

static void epaper_lvgl_wait_cb(struct _lv_disp_drv_t *disp_drv)
{
    if(panel_refreshing_sem)
        xSemaphoreTake(panel_refreshing_sem, portMAX_DELAY);
}

static unsigned long prior_tick_Millis=0;
// the following is a key element required for v9.0 vs v8.x
// you must keep track of the time otherwise really odd behavior will result from the widgets and device
static void handleTicks(void){
    lv_timer_handler(); /* let the GUI do its work */
    unsigned long tickMillis = get_millis()-prior_tick_Millis;
    prior_tick_Millis=get_millis();
    lv_tick_inc(tickMillis);
    //yield();
}

static void increase_lvgl_tick(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

#endif

bool lock_ssd168x(int timeout_ms) {
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
    if(!panel_refreshing_sem)
        return true;
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTake(panel_refreshing_sem, timeout_ticks) == pdTRUE;
}

void unlock_ssd168x(void) {
    if(panel_refreshing_sem)
        xSemaphoreGive(panel_refreshing_sem);
}

#ifdef CONFIG_DISPLAY_USE_LVGL
#define BIT_SET(a, b)       ((a) |= (1u << (b)))
#define BIT_CLEAR(a, b)     ((a) &= ~(1u << (b)))
static void set_px_cb(lv_disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
{
    uint16_t byte_index = (x >> 3u) + (y * LCD_ROW_LEN);
    uint8_t bit_index = x & 0x07u;

    if (color.full) {
        BIT_SET(buf[byte_index], 7 - bit_index);
    } else {
        BIT_CLEAR(buf[byte_index], 7 - bit_index);
    }
}

void display_ssd168x_init_cb(lv_disp_drv_t *disp_drv) {
    ILOG(TAG, "[%s]", __func__);
    // Set the callback functions
    disp_drv->hor_res = LCD_H_RES;
    disp_drv->ver_res = LCD_V_RES;
    disp_drv->rotated = DISP_ROT_270;
    // NOTE: The ssd168x e-paper is monochrome and 1 byte represents 8 pixels
    // so full_refresh is MANDATORY because we cannot set position to bitmap at pixel level
    disp_drv->full_refresh = true;
    disp_drv->direct_mode = 1;
    disp_drv->sw_rotate = false;
    disp_drv->user_data = panel_handle;
    // alloc bitmap buffer to draw
    //converted_buffer_black = heap_caps_malloc(LCD_PIXELS_MEM_ALIGNED, MALLOC_CAP_DMA);
    //converted_buffer_red = heap_caps_malloc(LCD_PIXELS_MEM_ALIGNED, MALLOC_CAP_DMA);
    disp_drv->flush_cb = epaper_lvgl_flush_cb;
    disp_drv->wait_cb = epaper_lvgl_wait_cb;
    // disp_drv->set_px_cb = set_px_cb;
    // disp_drv->drv_update_cb = epaper_lvgl_port_update_callback;
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
    // uint32_t fb_size = EPD_BUFFER_SIZE, pix_buf_size = LCD_H_RES * LCD_V_RES / 5;
    // alloc draw buffers used by LVGL
    // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
    size_t bufsz = LCD_RESOLUTION;
    ESP_LOGI(TAG, "Allocate %dkb memory for LVGL buffers" , (bufsz/1024));
    // lv_color_t *buf1 = heap_caps_malloc(bufsz * sizeof(lv_color_t), MALLOC_CAP_DMA);
    // assert(buf1);
    // lv_color_t *buf2 = heap_caps_malloc(bufsz * sizeof(lv_color_t), MALLOC_CAP_DMA);
    // assert(buf2);
    // initialize LVGL draw buffers
    lv_disp_draw_buf_init(&disp_buf, buf1, 0, bufsz);
    // initialize LVGL display driver
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;

    cb(&disp_drv);

    ESP_LOGI(TAG, "Register display driver to LVGL");
    //lv_disp_t *disp = 
    lv_disp = lv_disp_drv_register(&disp_drv);
    is_initialized_lvgl = true;

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
}
#endif

esp_lcd_panel_handle_t display_ssd168x_new() {
    ILOG(TAG, "[%s]", __func__);
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
        ESP_LOGE(TAG, "[%s] err: %s", __func__, esp_err_to_name(err));
    }
    err = gpio_set_level(PIN_NUM_EPD_DC, 1);
    if(err) {
        ESP_LOGE(TAG, "[%s] err: %s", __func__, esp_err_to_name(err));
    }
    err = gpio_set_level(PIN_NUM_EPD_RST, 1);
    if(err) {
        ESP_LOGE(TAG, "[%s] err: %s", __func__, esp_err_to_name(err));
    }

    ESP_LOGI(TAG, "Initialize SPI bus");
    spi_bus_config_t buscfg = {
        .sclk_io_num = PIN_NUM_SCLK,
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_RESOLUTION,
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

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
    esp_lcd_ssd168x_config_t epaper_ssd168x_config = {
        .busy_gpio_num = PIN_NUM_EPD_BUSY,
        .non_copy_mode = true,
        .height = LCD_V_RES,
        .width = LCD_H_RES,
        .buffer_size = LCD_PIXELS_MEM_ALIGNED,
        // .clear_img = clear_img,
    };
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = PIN_NUM_EPD_RST,
        .flags.reset_active_high = false,
        .vendor_config = &epaper_ssd168x_config
    };
    gpio_install_isr_service(0);
    ESP_ERROR_CHECK(esp_lcd_new_panel_ssd168x(io_handle, &panel_config, &panel_handle));

    // // --- Reset the display
    // ESP_LOGI(TAG, "Resetting e-Paper display...");
    // ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    // delay_ms(100);
    // // --- Initialize panel
    // ESP_LOGI(TAG, "Initializing e-Paper display...");
    // ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
#if (LCD_H_GAP>0) || (LCD_V_GAP>0)
    esp_lcd_panel_set_gap(panel_handle, LCD_H_GAP, LCD_V_GAP);
#endif
    delay_ms(100);
    // --- Register the e-Paper refresh done callback
    epaper_panel_callbacks_t cbs = {
        .on_epaper_refresh_done = epaper_flush_ready_callback
    };
#ifdef CONFIG_DISPLAY_USE_LVGL
    epaper_panel_register_event_callbacks_ssd168x(panel_handle, &cbs, &disp_drv);
    init_screen(display_ssd168x_init_cb);
#else
    epaper_panel_register_event_callbacks_ssd168x(panel_handle, &cbs, 0);
    rotated = DISP_ROT_270;
#endif    
    //ui_init();
    return panel_handle;
}

void display_ssd168x_del() {
    ILOG(TAG, "[%s]", __func__);
#ifdef CONFIG_DISPLAY_USE_LVGL
    lv_deinit();
#endif
    esp_lcd_panel_del(panel_handle);
    panel_handle = NULL;
    esp_lcd_panel_io_del(io_handle);
    io_handle = NULL;
    // heap_caps_free(converted_buffer_black);
    // converted_buffer_black = NULL;
    // heap_caps_free(converted_buffer_red);
    vSemaphoreDelete(panel_refreshing_sem);
    panel_refreshing_sem = NULL;
}

