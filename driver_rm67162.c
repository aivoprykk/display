#include "display_private.h"
#ifdef CONFIG_DISPLAY_DRIVER_RM67162
#include "driver_vendor.h"

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

#include "esp_lcd_panel_rm67162.h"

#include <logger_common.h>

static const char *TAG = "display_drv.67162";

#if defined(CONFIG_DISPLAY_SPI1_HOST)
# define SPIx_HOST SPI1_HOST
#elif defined(CONFIG_DISPLAY_SPI2_HOST)
# define SPIx_HOST SPI2_HOST
#elif defined(CONFIG_DISPLAY_SPI3_HOST)
# define SPIx_HOST SPI3_HOST
#else
# error "SPI host 1 2 or 3 must be selected"
#endif

#if defined(CONFIG_HWE_DISPLAY_SPI_MODE0)
# define SPI_MODEx (0)
#elif defined(CONFIG_HWE_DISPLAY_SPI_MODE3)
# define SPI_MODEx (2)
#else
# error "SPI MODE0 or MODE3 must be selected"
#endif

#define SPI_D_DMA_CHAN 1

#define LCD_MODULE_CMD_1
#define LCD_PIXEL_CLOCK_HZ CONFIG_HWE_DISPLAY_SPI_FREQUENCY

#define L_LVGL_TICK_PERIOD_MS 2

#define PSRAM_DATA_ALIGNMENT 64

static SemaphoreHandle_t panel_refreshing_sem = NULL;
static lv_disp_draw_buf_t disp_buf = {0};  // contains internal graphic buffer(s) called draw buffer(s)
static lv_disp_drv_t disp_drv = {0};       // contains callback functions
static lv_disp_t *lv_disp = NULL;

static esp_lcd_panel_handle_t panel_handle = NULL;
static esp_lcd_panel_io_handle_t io_handle = NULL;

static bool is_initialized_lvgl = false;

typedef struct {
    uint8_t cmd;
    uint8_t data[14];
    uint8_t len;
} lcd_cmd_t;

static void bl_init() {
    ILOG(TAG, "[%s]", __func__);
#if defined(BL_IS_PWM)
    const ledc_timer_config_t LCD_backlight_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_timer_config(&LCD_backlight_timer);
    const ledc_channel_config_t LCD_backlight_channel = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_FADE_END,
        .timer_sel = LEDC_TIMER_0,
        .gpio_num = CONFIG_DISPLAY_BL,
        .duty = 0,
        .hpoint = 0,
    };
    ledc_channel_config(&LCD_backlight_channel);
    gpio_matrix_out(CONFIG_DISPLAY_BL, SIG_GPIO_OUT_IDX, true, 0);
#else
    gpio_set_direction(CONFIG_DISPLAY_BL, GPIO_MODE_OUTPUT);
    // gpio_set_level(CONFIG_DISPLAY_BL, 1);
#endif
}

/**
 * @brief Set the backlight brightness of the display
 * 
 * @param brightness_percent The brightness of the backlight, expressed as a percentage (0-100)
 */

#if !defined(BL_IS_PWM)
static uint8_t bl_level = 0;
static const uint8_t bl_steps = 16;
#endif

static void _bl_set(uint8_t brightness_percent) {
#if defined(BL_IS_PWM)
    uint32_t duty_cycle = (1 << 8U) / (100 / brightness_percent); // 8-bit resolution
    ILOG(TAG, "[%s] backlight brightness to %hhu eq duty %lu", __func__, brightness_percent, duty_cycle);
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty_cycle);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
#else
    ILOG(TAG, "[%s] backlight brightness to %hhu %%, cur level %hhu of %hhu", __func__, brightness_percent, bl_level, bl_steps);
    uint16_t level;
    if (brightness_percent == 0) {
        gpio_set_level(CONFIG_DISPLAY_BL, 0);
        level = 0;
        goto end;
    }
    if (bl_level == 0) {
        gpio_set_level(CONFIG_DISPLAY_BL, 1);
        vTaskDelay(pdMS_TO_TICKS(1));
        bl_level = bl_steps;
    }
    level = bl_steps * brightness_percent;
    if(level < 100) level=100;
    level /= 100;
    uint8_t from = bl_steps - bl_level;
    uint8_t to = bl_steps - level;
    uint8_t num = (bl_steps + to - from) % bl_steps;
    DLOG(TAG, "[%s] from %d, num %d, to %d\n", __func__, from, to, num);
    for (uint8_t i = 0; i < num; i++) {
        gpio_set_level(CONFIG_DISPLAY_BL, 0);
        gpio_set_level(CONFIG_DISPLAY_BL, 1);
    }
    end:
    bl_level = level;
    vTaskDelay(pdMS_TO_TICKS(1));
#endif
}

#if defined(CONFIG_DISPLAY_USE_LVGL)
#if (LVGL_VERSION_MAJOR < 9)
static lv_disp_drv_t *lv_get_driver() {
    return &disp_drv;
}
#endif
static lv_disp_t *lv_get() {
    return lv_disp;
}
#endif

static esp_err_t driver_set_hw_rotation(int r) {
    if(!panel_handle)
        return ESP_ERR_INVALID_STATE;
    if(r == DISP_ROT_90 || r == DISP_ROT_270) {
        ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, false));
#if (LCD_H_GAP>0) || (LCD_V_GAP>0)
        esp_lcd_panel_set_gap(panel_handle, LCD_V_GAP, LCD_H_GAP);
#endif
    }
    else {
        ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, true));
#if (LCD_H_GAP>0) || (LCD_V_GAP>0)
        esp_lcd_panel_set_gap(panel_handle, LCD_H_GAP, LCD_V_GAP);
#endif
    }
    if(r == DISP_ROT_NONE) {
        esp_lcd_panel_mirror(panel_handle, true, false);
    }
    else if(r == DISP_ROT_90) {
        esp_lcd_panel_mirror(panel_handle, true, true);
    }
    else if(r == DISP_ROT_180) {
        esp_lcd_panel_mirror(panel_handle, false, true);
    }
    else if(r == DISP_ROT_270) {
        esp_lcd_panel_mirror(panel_handle, false, false);
    }
    return ESP_OK;
}

static esp_err_t _set_rotation(int r) {
    ILOG(TAG, "[%s] %d", __func__, r);
    if(r > DISP_ROT_270)
        return ESP_ERR_INVALID_ARG;

#if defined(CONFIG_DISPLAY_USE_LVGL)
    if(r!=disp_drv.rotated) {
        int swap = disp_drv.rotated;
        disp_drv.rotated = r;
        if(lv_disp) {
        lv_disp_drv_update(lv_disp, &disp_drv); //this is critical!
        lv_obj_invalidate(lv_scr_act());
            DLOG(TAG, "[%s] New orientation is %d:, rotated flag is :%d, hor_res is: %d, ver_res is: %d\r\n", __func__, \
        (int)r, swap, lv_disp_get_hor_res(lv_disp), lv_disp_get_ver_res(lv_disp));
        }
#else
        if(r!=rotated) {
            rotated = r;
#endif
        driver_set_hw_rotation(r);
    }
    return ESP_OK;
}

static int _get_rotation(void) {
    ILOG(TAG, "[%s]", __func__);
#if defined(CONFIG_DISPLAY_USE_LVGL)
    return disp_drv.rotated;
#else
    return rotated;
#endif
}

#if (LVGL_VERSION_MAJOR > 8)
static bool IRAM_ATTR color_trans_done(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
	lv_display_t *disp = (lv_display_t*)user_ctx;
	lv_display_flush_ready(disp);
	// Whether a high priority task has been waken up by this function
	return false; 
}
static void disp_flush(lv_display_t *disp_drv, const lv_area_t *area, uint8_t *px_map) {
	esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)lv_display_get_user_data(disp_drv);
	ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, (uint16_t *) px_map));
}
#else
static bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx) {
    if (is_initialized_lvgl) {
        lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
        if(disp_driver)
            lv_disp_flush_ready(disp_driver);
    }
    return false;
}
static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map) {
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)drv->user_data;
    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_map));
}
#endif

static void increase_lvgl_tick(void *arg) {
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(L_LVGL_TICK_PERIOD_MS*1000);
}

static bool lock(int timeout_ms) {
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
    if(!panel_refreshing_sem)
        return true;
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTakeRecursive(panel_refreshing_sem, timeout_ticks) == pdTRUE;
}

static void unlock(void) {
    if(panel_refreshing_sem)
        xSemaphoreGiveRecursive(panel_refreshing_sem);
}

static void display_init_cb(lv_disp_drv_t *disp_drv) {
    ILOG(TAG, "[%s]", __func__);
    // Set the callback functions
    size_t bufsz = SEND_BUF_SIZE; // Send_buf_size
    ILOG(TAG, "[%s] Allocate memory", __func__);
    static lv_color_t *buf[2];
	for (int i = 0; i < 2; i++) {
		buf[i] = heap_caps_malloc(bufsz  * sizeof(lv_color_t), MALLOC_CAP_DMA);
		assert(buf[i] != NULL);
	}
#if LVGL_VERSION_MAJOR > 8
	lv_display_set_buffers(disp, buf[0], buf[1], bufsz, LV_DISPLAY_RENDER_MODE_PARTIAL);
	// lv_disp_set_rotation(disp, DISP_ROT_NONE);

    ESP_ERROR_CHECK(esp_lcd_panel_io_register_event_callbacks(
		io_handle,
		&(esp_lcd_panel_io_callbacks_t) {
			color_trans_done
		},
	    disp));
	lv_display_set_user_data(disp, panel_handle);
	lv_display_set_flush_cb(disp, disp_flush);
#else
    lv_disp_draw_buf_init(&disp_buf, buf[0], buf[1], bufsz);
    lv_disp_drv_init(disp_drv);
    disp_drv->hor_res = LCD_H_RES;
    disp_drv->ver_res = LCD_V_RES;
    disp_drv->draw_buf = &disp_buf;
    disp_drv->user_data = panel_handle;
    disp_drv->flush_cb = lvgl_flush_cb;
    disp_drv->rotated = DISP_ROT_NONE; // fake value to force initial rotation
#endif
}

/**
 * @brief Initialize the screen
 * 
 */
static void init_screen(void (*cb)(lv_disp_drv_t *)) {
    ILOG(TAG, "[%s]", __func__);
    // --- Initialize LVGL
    ILOG(TAG, "[%s] Initialize LVGL library", __func__);
    lv_init();
    // alloc draw buffers used by LVGL
    // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized

    cb(&disp_drv);

    ILOG(TAG, "[%s] Register display driver to LVGL", __func__);
    lv_disp = lv_disp_drv_register(&disp_drv);

    //_set_rotation(DISP_ROT_180);
    
    is_initialized_lvgl = true;

    // init lvgl tick
    ILOG(TAG, "[%s] Install LVGL tick timer", __func__);
    // Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &increase_lvgl_tick,
        .name = "lvgl_tick"};
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, L_LVGL_TICK_PERIOD_MS * 1000));
}

static void _lv_init() {
    ILOG(TAG, "[%s]", __func__);
    if(disp_drv.user_data == NULL) {
        init_screen(display_init_cb);
    }
}

static esp_lcd_panel_handle_t _new() {
    ILOG(TAG, "[%s]", __func__);

    panel_refreshing_sem = xSemaphoreCreateRecursiveMutex();
    xSemaphoreGiveRecursive(panel_refreshing_sem);

    // ESP_ERROR_CHECK(gpio_set_direction(CONFIG_DISPLAY_BL, GPIO_MODE_OUTPUT));
	// ESP_ERROR_CHECK(gpio_set_level(CONFIG_DISPLAY_BL, 1));
    bl_init();
	vTaskDelay(pdMS_TO_TICKS(500));

	ILOG(TAG, "[%s] Initialize SPI bus", __func__);
	ESP_ERROR_CHECK(spi_bus_initialize(SPIx_HOST,
		& (spi_bus_config_t) {
			.data0_io_num = CONFIG_DISPLAY_SPI_A_D0,
			.data1_io_num = CONFIG_DISPLAY_SPI_A_D1,
			.sclk_io_num = CONFIG_DISPLAY_SPI_CLK,
			.data2_io_num = CONFIG_DISPLAY_SPI_A_D2,
			.data3_io_num = CONFIG_DISPLAY_SPI_A_D3,
			.max_transfer_sz = SEND_BUF_SIZE + 8,
			.flags = SPICOMMON_BUSFLAG_MASTER
				| SPICOMMON_BUSFLAG_GPIO_PINS
				| SPICOMMON_BUSFLAG_QUAD,
		},
		SPI_DMA_CH_AUTO
	));
	ILOG(TAG, "[%s] Attach panel IO handle to SPI", __func__);
	ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(
		(esp_lcd_spi_bus_handle_t)SPIx_HOST,
	       	& (esp_lcd_panel_io_spi_config_t) {
			.cs_gpio_num = CONFIG_DISPLAY_SPI_CS,
			.pclk_hz = CONFIG_HWE_DISPLAY_SPI_FREQUENCY,
			.lcd_cmd_bits = 32,
			.lcd_param_bits = 8,
#if (LVGL_VERSION_MAJOR < 9)
            .on_color_trans_done = notify_lvgl_flush_ready,
#endif
#if defined(CONFIG_HWE_DISPLAY_SPI_SPI)
			.spi_mode = 0,
#elif defined(CONFIG_HWE_DISPLAY_SPI_QSPI)
			.spi_mode = 0,
			.flags.quad_mode = 1,
#elif defined(CONFIG_HWE_DISPLAY_SPI_OSPI)
			.spi_mode = 3,
			.flags.octal_mode = 1,
#else
# error "SPI single, quad and octal modes are supported"
#endif
			.trans_queue_depth = 17,
		},
	       	&io_handle
	));

    ESP_ERROR_CHECK(esp_lcd_new_panel_rm67162(
		io_handle,
		& (esp_lcd_panel_dev_config_t) {
			.reset_gpio_num = CONFIG_DISPLAY_SPI_A_RST,
			.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
			.bits_per_pixel = 16,
		},
		&panel_handle
	));
    // --- Reset the display
    ESP_LOGI(TAG, "Resetting rm67162 display...");
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    // --- Initialize panel
    
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    //delay_ms(100);
    // --- Configurate the screen
    // NOTE: the configurations below are all FALSE by default
    // ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
	ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));
	// Rotate 90 degrees clockwise:
	// ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, true));
	// ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, false));
     
    ILOG(TAG, "[%s] Turn on backlight", __func__);
	ESP_ERROR_CHECK(gpio_set_level(CONFIG_DISPLAY_BL, 1));
    
    return panel_handle;
}

static void _del() {
    ILOG(TAG, "[%s]", __func__);

    lv_deinit();
    esp_lcd_panel_del(panel_handle);
    esp_lcd_panel_io_del(io_handle);
    vSemaphoreDelete(panel_refreshing_sem);
    panel_refreshing_sem = NULL;
}

display_driver_op_t display_driver_rm67162_op = {
    .new = _new,
    .del = _del,
    .set_rotation = _set_rotation,
    .get_rotation = _get_rotation,
    .epd_request_fast_update = 0,
    .epd_request_full_update = 0,
    .epd_refresh_and_turn_off = 0,
    .epd_turn_on = 0,
    .lock = lock,
    .unlock = unlock,
    .bl_set = _bl_set,
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