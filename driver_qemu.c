#include "driver_vendor.h"

#if (defined(CONFIG_DISPLAY_ENABLED) && defined(CONFIG_DISPLAY_DRIVER_QEMU))

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "esp_system.h"

#include "display_private.h"

#include "esp_err.h"
#include "esp_log.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_qemu_rgb.h"

#include "rom/gpio.h"
#include "driver/gpio.h"
#include "soc/gpio_sig_map.h"
#include "driver/ledc.h"

#include "driver/spi_common.h"
#include "driver/spi_master.h"

#include <logger_common.h>

static const char *TAG = "display_drv.qemu";

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
static lv_disp_draw_buf_t disp_buf = {0};  // contains internal graphic buffer(s) called draw buffer(s)
static lv_disp_drv_t disp_drv = {0};       // contains callback functions
static lv_disp_t *lv_disp = NULL;

//static uint8_t *converted_buffer_black;
//static uint8_t *converted_buffer_red;

//static lv_color_t *lv_disp_buf[LCD_BUF_SIZE_DIV_10];
//static lv_color_t *lv_disp_buf2[LCD_BUF_SIZE_DIV_10];

static esp_lcd_panel_handle_t panel_handle = NULL;

static bool is_initialized_lvgl = false;

typedef struct {
    uint8_t cmd;
    uint8_t data[14];
    uint8_t len;
} lcd_cmd_t;


lv_disp_drv_t *display_qemu_get_driver() {
    return &disp_drv;
}

lv_disp_t *display_qemu_get() {
    return lv_disp;
}

esp_err_t driver_qemu_set_hw_rotation(int r) {
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

esp_err_t driver_qemu_set_rotation(int r) {
    ILOG(TAG, "[%s] %d", __func__, r);
    if(r > DISP_ROT_270)
        return ESP_ERR_INVALID_ARG;

#if defined(CONFIG_DISPLAY_USE_LVGL)
    if(r!=disp_drv.rotated) {
        int swap = disp_drv.rotated;
        disp_drv.rotated = r;
        if(lv_disp){
            lv_disp_drv_update(lv_disp, &disp_drv); //this is critical!
            lv_obj_invalidate(lv_scr_act());
                DLOG(TAG, "New orientation is %d:, rotated flag is :%d, hor_res is: %d, ver_res is: %d\r\n", \
            (int)r, swap, lv_disp_get_hor_res(lv_disp), lv_disp_get_ver_res(lv_disp));
        }

#else
    if(r!=rotated) {
        rotated = r;
#endif
        driver_qemu_set_hw_rotation(r);
    }
    return ESP_OK;
}

int driver_qemu_get_rotation(void) {
    ILOG(TAG, "[%s]", __func__);
#if defined(CONFIG_DISPLAY_USE_LVGL)
    return disp_drv.rotated;
#else
    return rotated;
#endif
}

static bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx) {
    if (is_initialized_lvgl) {
        lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
        assert(disp_driver);
        lv_disp_flush_ready(disp_driver);
    }
    return false;
}

static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map) {
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // copy a buffer's content to a specific area of the display
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
    // lv_disp_flush_ready(drv);
}

static void increase_lvgl_tick(void *arg) {
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(L_LVGL_TICK_PERIOD_MS*1000);
}

bool lock_qemu(int timeout_ms) {
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
    if(!panel_refreshing_sem)
        return true;
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTakeRecursive(panel_refreshing_sem, timeout_ticks) == pdTRUE;
}

void unlock_qemu(void) {
    if(panel_refreshing_sem)
        xSemaphoreGiveRecursive(panel_refreshing_sem);
}

static size_t lvgl_get_buffers(esp_lcd_panel_handle_t panel_handle, void **buf1, void **buf2)
{
    if (buf2) {
        *buf2 = NULL;
    }
#if CONFIG_QEMU_RGB_PANEL_DEDIC_FB
    ESP_LOGI(TAG, "Use QEMU dedicated frame buffer as LVGL draw buffer");
    ESP_ERROR_CHECK(esp_lcd_rgb_qemu_get_frame_buffer(panel_handle, buf1));
    return LCD_H_RES * LCD_V_RES;
#else
    ESP_LOGI(TAG, "Allocate separate LVGL draw buffer");
    /* Allocate 10 horizontal lines as the frame buffer */
    *buf1 = heap_caps_malloc(LCD_H_RES * 10 * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(*buf1);
    return LCD_H_RES * 10;
#endif // CONFIG_DOUBLE_FB
}

static void display_init_cb(lv_disp_drv_t *disp_drv) {
    ILOG(TAG, "[%s]", __func__);
    // Set the callback functions
    disp_drv->hor_res = LCD_H_RES;
    disp_drv->ver_res = LCD_V_RES;
    disp_drv->flush_cb = lvgl_flush_cb;
    // disp_drv->wait_cb = lvgl_wait_cb;
    // disp_drv->drv_update_cb = epaper_lvgl_port_update_callback;
    disp_drv->user_data = panel_handle;
    disp_drv->rotated = DISP_ROT_NONE; // fake value to force initial rotation
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
    static lv_color_t *buf[2];
	for (int i = 0; i < 2; i++) {
		buf[i] = heap_caps_malloc(bufsz, MALLOC_CAP_DMA);
		assert(buf[i] != NULL);
	}
    lv_disp_draw_buf_init(&disp_buf, buf[0], buf[1], bufsz);
    // initialize LVGL display driver
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;

    cb(&disp_drv);

    #if CONFIG_QEMU_RGB_PANEL_DEDIC_FB
    disp_drv.full_refresh = true; // the full_refresh mode can maintain the synchronization between the two frame buffers
    #endif

    ESP_LOGI(TAG, "Register display driver to LVGL");
    //lv_disp_t *disp = 
    lv_disp = lv_disp_drv_register(&disp_drv);

    driver_qemu_set_rotation(DISP_ROT_180);
    
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

void display_lv_init() {
    ILOG(TAG, "[%s]", __func__);
    if(disp_drv.user_data == NULL) {
        init_screen(display_init_cb);
    }
}

esp_lcd_panel_handle_t display_qemu_new() {
    ILOG(TAG, "[%s]", __func__);

    panel_refreshing_sem = xSemaphoreCreateRecursiveMutex();
    xSemaphoreGiveRecursive(panel_refreshing_sem);

    esp_lcd_rgb_qemu_config_t panel_config = {
        .width = LCD_H_RES,
        .height = LCD_V_RES,
        .bpp = 16,
    };
    ESP_ERROR_CHECK(esp_lcd_new_rgb_qemu(&panel_config, &panel_handle));
    // --- Reset the display
    ESP_LOGI(TAG, "Resetting qemu display...");
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    // --- Initialize panel
    //vTaskDelay(pdMS_TO_TICKS(100));
    // flush color before turn on the display
    // esp_lcd_panel_invert_color(panel_handle, true);
     
    // delay_ms(100);
    // display_lv_init();

    return panel_handle;
}

void display_qemu_del() {
    ILOG(TAG, "[%s]", __func__);

    lv_deinit();
    esp_lcd_panel_del(panel_handle);
    vSemaphoreDelete(panel_refreshing_sem);
    panel_refreshing_sem = NULL;
}

#endif // CONFIG_DISPLAY_ENABLED && CONFIG_DISPLAY_DRIVER_QEMU