#include "driver_vendor.h"

#if defined(CONFIG_DISPLAY_DRIVER_SSD168X)

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

// #include "esp_system.h"
#include "esp_timer.h"

#include "display_private.h"

#include "driver/gpio.h"
// #include "driver/spi_master.h"

#include <esp_lcd_panel_ops.h>

#include "ui_events.h"
#include "logger_common.h"
#include "esp_lcd_panel_ssd168x.h"

#ifdef CONFIG_SSD168X_PANEL_SSD1681
#include "ssd1681_waveshare_1in54_lut.h"
static const char *TAG = "display_drv.ssd1681";
#else
#include "ssd1680_waveshare_2in13_lut.h"
static const char *TAG = "display_drv.ssd1680";
#endif

#if defined(CONFIG_DISPLAY_SPI1_HOST)
# define SPIx_HOST SPI1_HOST
#elif defined(CONFIG_DISPLAY_SPI2_HOST)
# define SPIx_HOST SPI2_HOST
#elif defined(CONFIG_DISPLAY_SPI3_HOST)
# define SPIx_HOST SPI3_HOST
#else
# error "SPI host 1 2 or 3 must be selected"
#endif

#define PIN_NUM_SCLK           CONFIG_DISPLAY_SPI_CLK
#define PIN_NUM_MOSI           CONFIG_DISPLAY_SPI_MOSI
#define PIN_NUM_EPD_DC         CONFIG_DISPLAY_SPI_DC
#define PIN_NUM_EPD_RST        CONFIG_DISPLAY_SPI_RST
#define PIN_NUM_EPD_CS         CONFIG_DISPLAY_SPI_CS
#define PIN_NUM_EPD_BUSY       CONFIG_DISPLAY_SPI_BUSY

#define LCD_PIXEL_CLOCK_HZ     (20 * 1000 * 1000)

// Bit number used to represent command and parameter
#define LCD_CMD_BITS           8
#define LCD_PARAM_BITS         8

#define LVGL_TICK_PERIOD_MS    10

static SemaphoreHandle_t panel_refreshing_sem = NULL;

#ifdef CONFIG_DISPLAY_USE_LVGL
#define LBUFSZ LCD_RESOLUTION
#if (LVGL_VERSION_MAJOR < 9)
static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
static lv_disp_drv_t disp_drv;      // contains callback functions
// lv_color_t buf1[LBUFSZ] = {0};
#else
#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_I1)) /*will be 2 for RGB565 */
// uint8_t buf1[LBUFSZ] = {0};
#endif
static lv_disp_t *lv_disp = NULL;
static bool is_initialized_lvgl = false;
// static uint32_t update_count = 0;
#else
static int rotated = DISP_ROT_90;
#endif
static uint8_t converted_buffer_black[LCD_PIXELS_MEM_ALIGNED] = {0};

//static uint8_t *converted_buffer_red;

static esp_lcd_panel_handle_t panel_handle = NULL;
static esp_lcd_panel_io_handle_t io_handle = NULL;
#ifdef CONFIG_SSD168X_PANEL_SSD1681
static uint8_t fast_refresh_lut[] = SSD1681_WAVESHARE_1IN54_V2_LUT_FAST_REFRESH_KEEP;
#else
static uint8_t fast_refresh_lut[] = SSD1680_WAVESHARE_2IN13_V2_LUT_FAST_REFRESH_O;
#endif
static bool init_requested = true;
static epaper_panel_init_mode_t init_mode = INIT_MODE_FULL_2;
// const unsigned char clear_img[LCD_PIXELS_MEM_ALIGNED] = { [0 ... LCD_PIXELS_MEM_ALIGNED-1] = 0xFF };
uint32_t flush_count = 0;
uint32_t last_flush_ms = 0;

IRAM_ATTR bool _flush_ready_callback(const esp_lcd_panel_handle_t handle, const void *edata, void *user_data)
{
#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *) user_data;
    lv_disp_flush_ready(disp_driver);
#else
    lv_display_t *disp = (lv_display_t *) user_data;
    lv_display_flush_ready(disp);
#endif
#endif
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(panel_refreshing_sem, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE) {
        return true;
    }
    return false;
}

static esp_err_t _request_full_update() {
    ILOG(TAG, "[%s]", __func__);
    init_mode = INIT_MODE_FULL_1;
    init_requested = true;
    return ESP_OK;
}

static esp_err_t _request_fast_update() {
    ILOG(TAG, "[%s]", __func__);
    init_mode = INIT_MODE_FULL_2;
    init_requested = true;
    return ESP_OK;
}

static esp_err_t _request_partial_update() {
    ILOG(TAG, "[%s]", __func__);
    init_mode = INIT_MODE_PARTIAL;
    init_requested = false;
    return ESP_OK;
}

#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
static lv_disp_drv_t * lv_get_driver() {
    return &disp_drv;
}
#endif

static lv_disp_t * lv_get() {
    return lv_disp;
}
#endif

static uint32_t _flush_count() {
    ILOG(TAG, "[%s]", __func__);
    return flush_count;
}

static uint32_t _last_flush_ms() {
    ILOG(TAG, "[%s]", __func__);
    return last_flush_ms;
}

static esp_err_t _set_rotation(int r) {
    ILOG(TAG, "[%s] %d", __func__, r);
    if(r > DISP_ROT_270)
        return ESP_ERR_INVALID_ARG;
#if defined(CONFIG_DISPLAY_USE_LVGL)
#if (LVGL_VERSION_MAJOR < 9)
    if(disp_drv.rotated != r) {
        disp_drv.rotated = r;
        if(lv_disp) {
            lv_disp_drv_update(lv_disp, &disp_drv); //this is critical!
            if(lv_scr_act()) {
                lv_obj_invalidate(lv_scr_act());
            }
        }
    }
#else
    if(lv_disp && r!=lv_display_get_rotation(lv_disp)) {
        lv_display_set_rotation(lv_disp, r);
        // lv_disp_drv_update(lv_disp, &disp_drv); //this is critical!
        if(lv_scr_act()) {
            lv_obj_invalidate(lv_scr_act());
        }
    }
#endif

#if (C_LOG_LEVEL < 2)
    if(lv_disp) {
        DLOG(TAG, "[%s] New orientation is %d:, rotated flag is :%d, hor_res is: %d, ver_res is: %d\n", __func__,
#if (LVGL_VERSION_MAJOR < 9)
            (int)r, disp_drv.rotated, lv_disp_get_hor_res(lv_disp), lv_disp_get_ver_res(lv_disp));
#else
            (int)r, lv_display_get_rotation(lv_disp), lv_display_get_horizontal_resolution(lv_disp), lv_display_get_vertical_resolution(lv_disp));
#endif
    }
#endif
#else
    if(r!=rotated) {
        rotated = r;
    }
#if (C_LOG_LEVEL < 2)
    DLOG(TAG, "[%s] New orientation is %d:, rotated flag is :%d\n", __func__, (int)r, rotated);
#endif
#endif
    return ESP_OK;
}

static int _get_rotation() {
    ILOG(TAG, "[%s]", __func__);
#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
    return disp_drv.rotated;
#else
return lv_display_get_rotation(lv_disp); 
#endif
#else
    return rotated;
#endif
}

static esp_err_t _turn_off(esp_lcd_panel_handle_t panel_handle) {
    ILOG(TAG, "[%s]", __func__);
    if(epaper_panel_shut_down(panel_handle)) {
        return ESP_FAIL;
    }
    return ESP_OK;
}

static esp_err_t _turn_on(esp_lcd_panel_handle_t panel_handle) {
    ILOG(TAG, "[%s]", __func__);
    const char *x = "e-Paper display...";
    UNUSED_PARAMETER(x);
    if(init_requested) {
#if (C_LOG_LEVEL < 3)
        ILOG(TAG, "[%s] %s %s with init mode 0x%02x", "Reset/Init", __func__, x, init_mode);
#endif
        if(flush_count > 0) {
            if(_turn_off(panel_handle)) {
                return ESP_FAIL;
            }
        }
        if(esp_lcd_panel_reset(panel_handle)) {
            return ESP_FAIL;
        }
        delay_ms(50);
        if(epaper_panel_init_screen_ssd168x(panel_handle, init_mode, 0)) {
            return ESP_FAIL;
        }
        init_mode = INIT_MODE_FULL_2;
        delay_ms(50);
    }
    if(esp_lcd_panel_disp_on_off(panel_handle, true)) {
        return ESP_FAIL;
    }
    if(!init_requested) {
        ILOG(TAG, "[%s] %s %s", "Refresh", __func__, x);
        if(epaper_panel_set_custom_lut_ssd168x(panel_handle, fast_refresh_lut, 159)) {
            return ESP_FAIL;
        }
    }
    else {
        init_requested = false;
    }
    return ESP_OK;
}

static esp_err_t _refresh_and_turn_off(esp_lcd_panel_handle_t panel_handle, int rotated, m_area_t *area, uint8_t *color_map) {
    ILOG(TAG, "[%s]", __func__);
    if(rotated == DISP_ROT_NONE || rotated == DISP_ROT_180) {
        if(esp_lcd_panel_swap_xy(panel_handle, false)) {
            return ESP_FAIL;
        }
#ifdef CONFIG_DISPLAY_USE_LVGL
        if(esp_lcd_panel_invert_color(panel_handle, false)) {
            return ESP_FAIL;
        }
#endif
    }
    else {
        if(esp_lcd_panel_swap_xy(panel_handle, true)) {
            return ESP_FAIL;
        }
#ifdef CONFIG_DISPLAY_USE_LVGL
        if(esp_lcd_panel_invert_color(panel_handle, true)) {
            return ESP_FAIL;
        }
#endif
    }

    if(rotated == DISP_ROT_NONE) {
        if(esp_lcd_panel_mirror(panel_handle, false, false)) {
            return ESP_FAIL;
        } // x inc y inc
    }
    else if(rotated == DISP_ROT_90) {
        if(esp_lcd_panel_mirror(panel_handle, true, false)) {
            return ESP_FAIL;
        } // x *dec y inc
    }
    else if(rotated == DISP_ROT_180) {
        if(esp_lcd_panel_mirror(panel_handle, true, true)) {
            return ESP_FAIL;
        } // x *dec y *dec
    }
    else { // DISP_ROT_270 (270 degrees)
        if(esp_lcd_panel_mirror(panel_handle, false, true)) {
            return ESP_FAIL;
        } // x inc y *dec
    }

    if(epaper_panel_set_bitmap_color_ssd168x(panel_handle, SSD168X_EPAPER_BITMAP_BLACK)) {
        return ESP_FAIL;
    }
    if(esp_lcd_panel_draw_bitmap(panel_handle,  area->x1,  area->y1, area->x2 + 1, area->y2 + 1, color_map)) {
        return ESP_FAIL;
    }
    if(epaper_panel_refresh_screen_ssd168x(panel_handle, 0xcf)) {
        return ESP_FAIL;
    }
    if(epaper_panel_set_bitmap_color_ssd168x(panel_handle, SSD168X_EPAPER_BITMAP_RED)) {
        return ESP_FAIL;
    }
    if(esp_lcd_panel_draw_bitmap(panel_handle,  area->x1,  area->y1, area->x2 + 1, area->y2 + 1, color_map)) {
        return ESP_FAIL;
    }
    if(epaper_panel_update_full_screen_ssd168x(panel_handle)) {
        return ESP_FAIL;
    }
    // if(esp_lcd_panel_disp_on_off(panel_handle, false)) {
    //         return ESP_FAIL;
    // }
    return ESP_OK;
}

#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
#define MYINT int
#define MYINT_D "d"
static void _lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
#else
static inline uint8_t LV_ATTRIBUTE_FAST_MEM get_bit(const uint8_t * buf, int32_t bit_idx)
{
    return (buf[bit_idx / 8] >> (7 - (bit_idx % 8))) & 1;
}
#define MYINT int32_t
#define MYINT_D PRId32
static void _lvgl_flush_cb(lv_display_t *dspl, const lv_area_t *area, uint8_t *color_map)
#endif
{
#if (C_LOG_LEVEL < 2)
    DLOG(TAG, "[%s] display_drv_get_width(lv_get_driver()) %d\n", __func__, display_drv_get_width(display_drv_get()));
#endif
    // IMEAS_START();
#if (LVGL_VERSION_MAJOR < 9)
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] x1:%hd y1:%hd, x2:%hd y2:%hd", __func__, area->x1, area->y1, area->x2, area->y2);
#endif
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
#else
    ILOG(TAG, "[%s] x1:%ld y1:%ld, x2:%ld y2:%ld", __func__, area->x1, area->y1, area->x2, area->y2);
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) lv_display_get_user_data(dspl);
#endif
    MYINT offsetx1 = area->x1;
    MYINT offsetx2 = area->x2;
    MYINT offsety1 = area->y1;
    MYINT offsety2 = area->y2;
    // Used to vertical traverse lvgl framebuffer
    MYINT len_x = abs(offsetx1 - offsetx2)+1;
    MYINT len_y = abs(offsety1 - offsety2)+1;
    int rotated = _get_rotation();
#if (LVGL_VERSION_MAJOR >= 9)
#if (LV_COLOR_DEPTH == 1)
    uint8_t * buf = color_map+8;
#else
    uint8_t * buf = color_map;
#endif
#endif
#if defined(CONFIG_SSD168X_PANEL_SSD1680)
    if(rotated==DISP_ROT_270 || rotated==DISP_ROT_90) len_y = BYTE_PADDING(len_y);
    else len_x = BYTE_PADDING(len_x);
#endif
    // else len_x = BYTE_PADDING(len_x);
    // --- Convert buffer from color to monochrome bitmap
    MYINT len_bits = (len_x * len_y);
#if (LVGL_VERSION_MAJOR < 9)
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] turned on, next load buffer wit rotation %d", __func__,drv->rotated);
#endif
#else
    ILOG(TAG, "[%s] turned on, next load buffer wit rotation %d", __func__,display_get_rotation(dspl));
#endif
    memset(converted_buffer_black, 0x00, (len_bits / 8));
    // esp_event_post(UI_EVENT, UI_EVENT_FLUSH_START, 0, 0, portMAX_DELAY);
    for (MYINT i = len_bits-1, i8, j=0; i >=0; i--,j++) {
        i8 = i / 8;
        uint8_t bit_index = i % 8;
        if(rotated == DISP_ROT_90 || rotated == DISP_ROT_270) {
        // NOTE: Set bits of converted_buffer[] FROM LOW ADDR TO HIGH ADDR, FROM HSB TO LSB
        // NOTE: 1 means BLACK/RED, 0 means WHITE
        // Horizontal traverse lvgl framebuffer (by row)
#if (LVGL_VERSION_MAJOR < 9)
          converted_buffer_black[i8] |= (((lv_color_brightness(color_map[((i*len_x)%len_bits) + i/len_y])) > 250) << (7 - (bit_index)));
#else
          // converted_buffer_black[i8] |= (((buf[((i*len_x)%len_bits) + i/len_y])) << (7 - (bit_index)));
          converted_buffer_black[i8] |= get_bit(buf,(((i*len_x)%len_bits) + i/len_y)) << (7 - (bit_index));
#endif
        }
        else {
        // Vertical traverse lvgl framebuffer (by column), needs to uncomment len_x and len_y
        // NOTE: If your screen rotation requires setting the pixels vertically, you could use the code below
#if (LVGL_VERSION_MAJOR < 9)
          converted_buffer_black[i8] |= (((lv_color_brightness(color_map[i])) <= 250) << (7 - (bit_index)));
#else
          // converted_buffer_black[i8] |= (((buf[i])) << (7 - (bit_index)));
          converted_buffer_black[i8] |= get_bit(buf, i) << (7 - (bit_index));
#endif
        }
#if defined(CONFIG_SSD168X_PANEL_SSD1680)
        if(bit_index==0 && j>8 && (rotated == DISP_ROT_90 || rotated == DISP_ROT_180)) {
            uint8_t current_byte = converted_buffer_black[i8+1];
            uint8_t prev_byte = (i8 >= 0 ) ? converted_buffer_black[i8] : 0;
            converted_buffer_black[i8+1] = ((current_byte >> (6)) | (prev_byte << (2))) & 0xFF;
        }
#endif
    }
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] turn on, len x:%"MYINT_D", y:%"MYINT_D" bits: %"MYINT_D"", __func__, len_x, len_y, len_bits);
#endif
    bool ir = init_requested;
    _turn_on(panel_handle);
    // --- Draw bitmap
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] refresh and turn off", __func__);
#endif
    _refresh_and_turn_off(panel_handle, rotated, &((m_area_t) {offsetx1, offsety1, offsetx2, offsety2}), converted_buffer_black);
    if(ir) {
        _turn_on(panel_handle);
        _refresh_and_turn_off(panel_handle, rotated, &((m_area_t) {offsetx1, offsety1, offsetx2, offsety2}), converted_buffer_black);
    }

    // IMEAS_END(TAG, "[%s] area %d x %d flush took %llu us", __func__, len_x, len_y);
    flush_count++;
    last_flush_ms = get_millis();
    esp_event_post(UI_EVENT, UI_EVENT_FLUSH_DONE, 0, 0, portMAX_DELAY);
}

#if (LVGL_VERSION_MAJOR < 9)
static void _lvgl_wait_cb(struct _lv_disp_drv_t *disp_drv)
#else
static void _lvgl_wait_cb(lv_display_t *disp)
#endif
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

static bool lock(int timeout_ms) {
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
    if(!panel_refreshing_sem)
        return true;
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTake(panel_refreshing_sem, timeout_ticks) == pdTRUE;
}

static void unlock(void) {
    if(panel_refreshing_sem)
        xSemaphoreGive(panel_refreshing_sem);
}

#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
static void set_px_cb(lv_disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
{
    uint16_t byte_index = (x >> 3u) + (y * LCD_ROW_LEN);
    uint8_t bit_index = x & 0x07u;

    if (color.full) {
        SETBIT(buf[byte_index], 7 - bit_index);
    } else {
        CLRBIT(buf[byte_index], 7 - bit_index);
    }
}
#endif

#if (LVGL_VERSION_MAJOR < 9)
static void _init_cb(lv_disp_drv_t *disp_drv) {
    ILOG(TAG, "[%s]", __func__);
    // Set the callback functions
    disp_drv->hor_res = LCD_H_RES;
    disp_drv->ver_res = LCD_V_RES;
    disp_drv->rotated = DISP_ROT_270;
    // NOTE: The ssd168x e-paper is monochrome and 1 byte represents 8 pixels
    // so full_refresh is MANDATORY because we cannot set position to bitmap at pixel level
    disp_drv->full_refresh = 1;
    disp_drv->direct_mode = 1;
    disp_drv->sw_rotate = 0;
    disp_drv->user_data = panel_handle;
    // alloc bitmap buffer to draw
    //converted_buffer_black = heap_caps_malloc(LCD_PIXELS_MEM_ALIGNED, MALLOC_CAP_DMA);
    //converted_buffer_red = heap_caps_malloc(LCD_PIXELS_MEM_ALIGNED, MALLOC_CAP_DMA);
    disp_drv->flush_cb = _lvgl_flush_cb;
    disp_drv->wait_cb = _lvgl_wait_cb;
    // disp_drv->set_px_cb = set_px_cb;
    // disp_drv->drv_update_cb = epaper_lvgl_port_update_callback;
}
#else
static void _init_cb(lv_display_t *disp) {
    ILOG(TAG, "[%s]", __func__);
    lv_display_set_rotation(disp, DISP_ROT_270);
    // NOTE: The ssd168x e-paper is monochrome and 1 byte represents 8 pixels
    // so full_refresh is MANDATORY because we cannot set position to bitmap at pixel level
    // lv_disp_set_full_refresh(disp, true);
    // lv_disp_set_direct_mode(disp, 1);
    // lv_disp_set_sw_rotate(disp, false);
    lv_display_set_user_data(disp, panel_handle);
    lv_display_set_flush_cb(disp, _lvgl_flush_cb);
    lv_display_set_flush_wait_cb(disp, _lvgl_wait_cb);
    // lv_display_set_color_format(disp, LV_COLOR_FORMAT_I8);
}
#endif

/**
 * @brief Initialize the screen
 * 
 */
#if (LVGL_VERSION_MAJOR < 9)
static void init_screen(void (*cb)(lv_disp_drv_t *)) {
#else
static void init_screen(void (*cb)(lv_display_t*)) {
#endif
    ILOG(TAG, "[%s]", __func__);
    // --- Initialize LVGL
#if (C_LOG_LEVEL < 3)
    ESP_LOGI(TAG, "Initialize LVGL library");
#endif
    lv_init();
    // uint32_t fb_size = EPD_BUFFER_SIZE, pix_buf_size = LCD_H_RES * LCD_V_RES / 5;
    // alloc draw buffers used by LVGL
    // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
    size_t bufsz = LBUFSZ;
#if (C_LOG_LEVEL < 4)
    WLOG(TAG, "Allocate %dKb memory for LVGL buffers" , (bufsz>>10)); // bufsz is in bytes, so we divide by 1024 to get Kb
#endif
    static lv_color_t *buf[2] = {NULL, NULL};
	for (int i = 0; i < 1; i++) {
		buf[i] = heap_caps_malloc(bufsz * sizeof(lv_color_t), MALLOC_CAP_DMA);
		assert(buf[i] != NULL);
	}
#if (LVGL_VERSION_MAJOR < 9)
    lv_disp_draw_buf_init(&disp_buf, buf[0], buf[1], bufsz);
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    cb(&disp_drv);
#if (C_LOG_LEVEL < 3)
    ESP_LOGI(TAG, "Register display driver / create display to LVGL");
#endif
    lv_disp = lv_disp_drv_register(&disp_drv);
#else
    ESP_LOGI(TAG, "Create display for LVGL");
    lv_disp = lv_display_create(LCD_H_RES, LCD_V_RES);
    cb(lv_disp);
    lv_display_set_buffers(lv_disp, buf[0], buf[1], bufsz, LV_DISPLAY_RENDER_MODE_FULL);
    
#endif
    is_initialized_lvgl = true;

    // init lvgl tick
#if (C_LOG_LEVEL < 3)
    ESP_LOGI(TAG, "Install LVGL tick timer");
#endif
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &increase_lvgl_tick,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;
    if(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer)) {
        return;
    }
    if(esp_timer_start_periodic(lvgl_tick_timer, MS_TO_US(LVGL_TICK_PERIOD_MS))) {
        return;
    }
}
#endif

static void _lv_init() {
    ILOG(TAG, "[%s]", __func__);
    if(disp_drv.user_data == NULL) {
        // --- Register the e-Paper refresh done callback
    #ifdef CONFIG_DISPLAY_USE_LVGL
        epaper_panel_callbacks_t cbs = {
            .on_epaper_refresh_done = _flush_ready_callback
        };
    #if (LVGL_VERSION_MAJOR < 9)
        epaper_panel_register_event_callbacks_ssd168x(panel_handle, &cbs, &disp_drv);
    #else
        epaper_panel_register_event_callbacks_ssd168x(panel_handle, &cbs, lv_disp);
    #endif
    #else
        epaper_panel_register_event_callbacks_ssd168x(panel_handle, &cbs, 0);
        rotated = DISP_ROT_270;
    #endif
        init_screen(_init_cb);
    }
}

static esp_lcd_panel_handle_t _new() {
    ILOG(TAG, "[%s]", __func__);
    panel_refreshing_sem = xSemaphoreCreateBinary();
    xSemaphoreGive(panel_refreshing_sem);

    esp_err_t err = 0;
    // Initialize GPIOs direction & initial states
#if (PIN_NUM_EPD_CS >= 0)
    gpio_set_direction(PIN_NUM_EPD_CS, GPIO_MODE_OUTPUT);
    err = gpio_set_level(PIN_NUM_EPD_CS, 1);
    if(err) {
        ESP_LOGE(TAG, "[%s] err: %s", __func__, esp_err_to_name(err));
    }
#endif
#if (PIN_NUM_EPD_DC >= 0)
    gpio_set_direction(PIN_NUM_EPD_DC, GPIO_MODE_OUTPUT);
    err = gpio_set_level(PIN_NUM_EPD_DC, 1);
    if(err) {
        ESP_LOGE(TAG, "[%s] err: %s", __func__, esp_err_to_name(err));
    }
#endif
#if (PIN_NUM_EPD_RST >= 0)
    gpio_set_direction(PIN_NUM_EPD_RST, GPIO_MODE_OUTPUT);
    err = gpio_set_level(PIN_NUM_EPD_RST, 1);
    if(err) {
        ESP_LOGE(TAG, "[%s] err: %s", __func__, esp_err_to_name(err));
    }
#endif
#if (PIN_NUM_EPD_BUSY >= 0)
    gpio_set_direction(PIN_NUM_EPD_BUSY, GPIO_MODE_INPUT);
    gpio_set_pull_mode(PIN_NUM_EPD_BUSY, GPIO_PULLUP_ONLY);
#endif

    ESP_LOGI(TAG, "Initialize SPI bus");
    spi_bus_config_t buscfg = {
        .sclk_io_num = PIN_NUM_SCLK,
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_RESOLUTION,
    };
    if(spi_bus_initialize(SPIx_HOST, &buscfg, SPI_DMA_CH_AUTO)) {
        ESP_LOGE(TAG, "Failed to initialize bus");
        return NULL;
    }

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
    if(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t) SPIx_HOST, &io_config, &io_handle)) {
        ESP_LOGE(TAG, "Failed to create panel io");
        return NULL;
    }

    // --- Create esp_lcd panel
    esp_lcd_ssd168x_config_t lcd_ssd168x_config = {
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
        .vendor_config = &lcd_ssd168x_config
    };
    gpio_install_isr_service(0);
    if(esp_lcd_new_panel_ssd168x(io_handle, &panel_config, &panel_handle)) {
        ESP_LOGE(TAG, "Failed to create panel");
        return NULL;
    }

    // // --- Reset the display
    // ESP_LOGI(TAG, "Resetting e-Paper display...");
    // if(esp_lcd_panel_reset(panel_handle)) {
    //     ESP_LOGE(TAG, "Failed to reset panel");
    //     return NULL;
    // }
    // delay_ms(100);
    // // --- Initialize panel
    // ESP_LOGI(TAG, "Initializing e-Paper display...");
    // if(esp_lcd_panel_init(panel_handle)) {
    //     ESP_LOGE(TAG, "Failed to init panel");
    //     return NULL;
    // }
#if (LCD_H_GAP>0) || (LCD_V_GAP>0)
    esp_lcd_panel_set_gap(panel_handle, LCD_H_GAP, LCD_V_GAP);
#endif
    delay_ms(100);
    // display_lv_init();
    
    return panel_handle;
}

static void _del() {
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

display_driver_op_t display_driver_ssd168x_op = {
    .new = _new,
    .del = _del,
    .set_rotation = _set_rotation,
    .get_rotation = _get_rotation,
    .lock = lock,
    .unlock = unlock,
    .epd_request_fast_update = _request_fast_update,
    .epd_request_full_update = _request_full_update,
    .epd_request_partial_update = _request_partial_update,
    .epd_refresh_and_turn_off = _refresh_and_turn_off,
    .epd_turn_on = _turn_on,
    .epd_turn_off = _turn_off,
    .epd_flush_count = _flush_count,
    .epd_last_flush_ms = _last_flush_ms,
#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
    .get_driver = lv_get_driver,
    #else
    .get_driver = 0,
    #endif
    .get = lv_get,
    .lv_init = _lv_init,
#endif
};

#endif

