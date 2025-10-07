#include "display_private.h"
#if defined(CONFIG_DISPLAY_ENABLED)
#include "driver_vendor.h"
#include "esp_err.h"
#include "esp_lcd_panel_ops.h"
#include "esp_heap_caps.h"
#ifdef CONFIG_DISPLAY_USE_LVGL
#include "lvgl.h"
#endif

static const char *TAG = "display_drv";

// Pre-calculated timeout values to avoid repeated pdMS_TO_TICKS calculations
#define TIMEOUT_IMMEDIATE 0
#define TIMEOUT_MAX portMAX_DELAY
static const TickType_t timeout_100ms = pdMS_TO_TICKS(100);

// Cached function capabilities to avoid repeated null checks
typedef struct {
    bool epd_request_full_update;
    bool epd_request_fast_update; 
    bool epd_request_partial_update;
    bool epd_flush_count;
    bool epd_refresh_and_turn_off;
    bool epd_turn_on;
    bool epd_turn_off;
    bool bl_set;
    bool set_rotation;
    bool d_init;
} driver_capabilities_t;

static driver_capabilities_t capabilities = {0};

display_driver_t drv = {
#ifdef CONFIG_DISPLAY_USE_LVGL
    .lv_mem_buf = {0},
    .is_initialized_lvgl = false,
    .lv_disp = NULL,
#else
    .rotated = DISP_ROT_90,
#endif
    .sem = 0,
#if defined(CONFIG_DISPLAY_DRIVER_ST7789)
    .op = &display_driver_st7789_op
#elif defined(CONFIG_DISPLAY_DRIVER_RM67162)
    .op = &display_driver_rm67162_op
#elif defined(CONFIG_DISPLAY_DRIVER_QEMU)
    .op = &display_driver_qemu_op
#elif defined(CONFIG_DISPLAY_DRIVER_SSD168X)
    .op = &display_driver_ssd168x_op
#endif
};

esp_lcd_panel_handle_t display_drv_new() {
    if(!drv.op->new) return NULL;
    drv.sem = xSemaphoreCreateBinary();
    xSemaphoreGive(drv.sem);
    
    // Cache function capabilities at initialization to avoid repeated null checks
    capabilities.epd_request_full_update = (drv.op->epd_request_full_update != NULL);
    capabilities.epd_request_fast_update = (drv.op->epd_request_fast_update != NULL);
    capabilities.epd_request_partial_update = (drv.op->epd_request_partial_update != NULL);
    capabilities.epd_flush_count = (drv.op->epd_flush_count != NULL);
    capabilities.epd_refresh_and_turn_off = (drv.op->epd_refresh_and_turn_off != NULL);
    capabilities.epd_turn_on = (drv.op->epd_turn_on != NULL);
    capabilities.epd_turn_off = (drv.op->epd_turn_off != NULL);
#if !defined(CONFIG_LCD_IS_EPD)
    capabilities.bl_set = (drv.op->bl_set != NULL);
#endif
    capabilities.set_rotation = (drv.op->set_rotation != NULL);
    capabilities.d_init = (drv.op->d_init != NULL);
    
    return drv.op->new();
}

void display_drv_del() {
    if(drv.op->del)
        drv.op->del();
    if(drv.sem) {
        vSemaphoreDelete(drv.sem);
        drv.sem = NULL;
    }
}

static bool lock(int timeout_ms) {
    FUNC_ENTRYD(TAG);
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
    if(!drv.sem)
        return true;
        
    TickType_t timeout_ticks;
    // Optimize common timeout values
    if (timeout_ms == -1) {
        timeout_ticks = TIMEOUT_MAX;
    } else if (timeout_ms == 0) {
        timeout_ticks = TIMEOUT_IMMEDIATE;
    } else if (timeout_ms == 100) {
        timeout_ticks = timeout_100ms;
    } else {
        timeout_ticks = pdMS_TO_TICKS(timeout_ms);
    }
    
    return xSemaphoreTake(drv.sem, timeout_ticks) == pdTRUE;
}

static void unlock(void) {
    FUNC_ENTRYD(TAG);
    if(drv.sem)
        xSemaphoreGive(drv.sem);
}

bool display_drv_lock(int timeout_ms) {
    return lock(timeout_ms);
}

void display_drv_unlock() {
    unlock();
}

#if defined(CONFIG_LCD_IS_EPD)

esp_err_t display_drv_epd_request_full_update() {
    return capabilities.epd_request_full_update ? 
           drv.op->epd_request_full_update() : ESP_ERR_NOT_SUPPORTED;
}

esp_err_t display_drv_epd_request_fast_update() {
    return capabilities.epd_request_fast_update ? 
           drv.op->epd_request_fast_update() : ESP_ERR_NOT_SUPPORTED;
}

esp_err_t display_drv_epd_request_partial_update() {
    return capabilities.epd_request_partial_update ? 
           drv.op->epd_request_partial_update() : ESP_ERR_NOT_SUPPORTED;
}

uint32_t display_drv_epd_get_flush_count() {
#if defined(CONFIG_LCD_IS_EPD)
    return capabilities.epd_flush_count ? drv.op->epd_flush_count() : 0;
#else
    return 0;
#endif
}

esp_err_t display_drv_epd_refresh_and_turn_off(esp_lcd_panel_handle_t panel_handle, int rotated, m_area_t *area, uint8_t *color_map) {
    return capabilities.epd_refresh_and_turn_off ? 
           drv.op->epd_refresh_and_turn_off(panel_handle, rotated, area, color_map) : ESP_ERR_NOT_SUPPORTED;
}

esp_err_t display_drv_epd_turn_on(esp_lcd_panel_handle_t panel_handle) {
    return capabilities.epd_turn_on ? 
           drv.op->epd_turn_on(panel_handle) : ESP_ERR_NOT_SUPPORTED;
}

esp_err_t display_drv_epd_turn_off(esp_lcd_panel_handle_t panel_handle) {
    return capabilities.epd_turn_off ? 
           drv.op->epd_turn_off(panel_handle) : ESP_ERR_NOT_SUPPORTED;
}

#else

void display_drv_bl_set(uint8_t brightness_percent) {
    if(capabilities.bl_set)
        drv.op->bl_set(brightness_percent);
}

#endif

static esp_err_t _set_rotation(int r) {
    FUNC_ENTRY_ARGS(TAG, " %d", r);
    if(r > DISP_ROT_270)
        return ESP_ERR_INVALID_ARG;
        
#ifdef CONFIG_DISPLAY_USE_LVGL
    DISPLAY_SET_ROTATION(drv.lv_disp, r);
    if(lv_scr_act()) {
        lv_obj_invalidate(lv_scr_act());
    }

#if (C_LOG_LEVEL < 2)
    if(drv.lv_disp) {
        DLOG(TAG, "[%s] New orientation is %d:, rotated flag is :%d, hor_res is: %d, ver_res is: %d", __func__,
            (int)r, DISPLAY_GET_ROTATION(), DISPLAY_GET_HOR_RES(), DISPLAY_GET_VER_RES()
        );
    }
#endif
#else
    if(r!=drv.rotated) {
        drv.rotated = r;
    }
#if (C_LOG_LEVEL < 2)
    DLOG(TAG, "[%s] New orientation is %d:, rotated flag is :%d", __func__, (int)r, drv.rotated);
#endif
#endif
    return ESP_OK;
}

esp_err_t display_drv_set_rotation(int r) {
    int prev = display_drv_get_rotation();
    int ret = _set_rotation(r);
    if(prev != r && capabilities.set_rotation) ret = drv.op->set_rotation(r);
    return ret;
}

int display_drv_get_rotation() {
    FUNC_ENTRY(TAG);
#ifdef CONFIG_DISPLAY_USE_LVGL
    return DISPLAY_GET_ROTATION();
#else
    return drv.rotated;
#endif
}

#ifdef CONFIG_DISPLAY_USE_LVGL

int display_drv_get_width() { return DISPLAY_GET_HOR_RES(); }
int display_drv_get_height() { return DISPLAY_GET_VER_RES(); }

static void increase_lvgl_tick(void *arg) {
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

void display_drv_init() { if(capabilities.d_init) drv.op->d_init(); }

esp_err_t init_draw_buffers(size_t lvbuf, uint8_t lvbuf_num, size_t convbuf, uint8_t convbuf_num) {
    size_t bufsz;
    esp_err_t ret = ESP_OK;
    for (uint8_t i=0, j=lvbuf_num + convbuf_num; i < j; i++) {
        bufsz = i < lvbuf_num ? lvbuf : convbuf;
#if (C_LOG_LEVEL < 4)
        WLOG(TAG, "Allocate %dKb memory for buf %d" , (bufsz>>10), i);
#endif
		drv.lv_mem_buf[i] = heap_caps_malloc(bufsz, MALLOC_CAP_DMA);
		if(drv.lv_mem_buf[i] == NULL) {
            drv.lv_mem_buf_size[i] = 0;
            ELOG(TAG, "[%s] Failed to allocate memory for buffer %d", __func__, i);
            ret = ESP_ERR_NO_MEM;
        }
        else {
            drv.lv_mem_buf_size[i] = bufsz;
        }
	}
    return ret;
}

void init_lv_screen(void (*cb)(void *)) {
    FUNC_ENTRY(TAG);
    // --- Initialize LVGL
    ILOG(TAG, "Initialize LVGL library");
    lv_init();
    size_t bufsz = LBUFSZ;
    init_draw_buffers(LBUFSZ, LV_DRAW_BUF_SZ, LCD_PIXELS_MEM_ALIGNED, CONV_BUF_SZ);
    uint8_t *buf[2] = {drv.lv_mem_buf[0], (LV_DRAW_BUF_SZ > 1 ? drv.lv_mem_buf[1] : NULL)};
    ILOG(TAG, "Register display driver / create display to LVGL");
#if (LVGL_VERSION_MAJOR < 9)
    lv_disp_draw_buf_init(&drv.disp_buf, buf[0], buf[1], bufsz);
    lv_disp_drv_init(&drv.disp_drv);
    drv.disp_drv.draw_buf = &drv.disp_buf;
    cb(&drv.disp_drv);
    drv.lv_disp = lv_disp_drv_register(&drv.disp_drv);
#else
    drv.lv_disp = lv_display_create(LCD_H_RES, LCD_V_RES);
    cb(drv.lv_disp);
    lv_display_set_buffers(drv.lv_disp, buf[0], buf[1], bufsz, LV_DISPLAY_RENDER_MODE_FULL);
#endif
    drv.is_initialized_lvgl = true;

    // init lvgl tick
    ILOG(TAG, "Install LVGL tick timer");
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

#endif