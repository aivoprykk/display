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
    drv.sem = xSemaphoreCreateRecursiveMutex();
    xSemaphoreGiveRecursive(drv.sem);
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
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
    if(!drv.sem)
        return true;
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTakeRecursive(drv.sem, timeout_ticks) == pdTRUE;
}

static void unlock(void) {
    if(drv.sem)
        xSemaphoreGiveRecursive(drv.sem);
}

bool display_drv_lock(int timeout_ms) {
    return lock(timeout_ms);
}

void display_drv_unlock() {
    unlock();
}

#if defined(CONFIG_LCD_IS_EPD)

esp_err_t display_drv_epd_request_full_update() {
    if(!drv.op->epd_request_full_update) return ESP_ERR_NOT_SUPPORTED;
    return drv.op->epd_request_full_update();
}

esp_err_t display_drv_epd_request_fast_update() {
    if(!drv.op->epd_request_fast_update) return ESP_ERR_NOT_SUPPORTED;
    return drv.op->epd_request_fast_update();
}

esp_err_t display_drv_epd_request_partial_update() {
    if(!drv.op->epd_request_partial_update) return ESP_ERR_NOT_SUPPORTED;
    return drv.op->epd_request_partial_update();
}

uint32_t display_drv_epd_get_flush_count() {
#if defined(CONFIG_LCD_IS_EPD)
    if(!drv.op->epd_flush_count) return 0;
    return drv.op->epd_flush_count();
#else
    return 0;
#endif
}

esp_err_t display_drv_epd_refresh_and_turn_off(esp_lcd_panel_handle_t panel_handle, int rotated, m_area_t *area, uint8_t *color_map) {
    if(! drv.op->epd_refresh_and_turn_off) return ESP_ERR_NOT_SUPPORTED;
    return drv.op->epd_refresh_and_turn_off(panel_handle, rotated, area, color_map);
}

esp_err_t display_drv_epd_turn_on(esp_lcd_panel_handle_t panel_handle) {
    if(! drv.op->epd_turn_on) return ESP_ERR_NOT_SUPPORTED;
    return drv.op->epd_turn_on(panel_handle);
}

esp_err_t display_drv_epd_turn_off(esp_lcd_panel_handle_t panel_handle) {
    if(! drv.op->epd_turn_off) return ESP_ERR_NOT_SUPPORTED;
    return drv.op->epd_turn_off(panel_handle);
}

#else

void display_drv_bl_set(uint8_t brightness_percent) {
    if(drv.op->bl_set)
        drv.op->bl_set(brightness_percent);
}

#endif

static esp_err_t _set_rotation(int r) {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s] %d", __func__, r);
#endif
    if(r > DISP_ROT_270)
        return ESP_ERR_INVALID_ARG;
#if defined(CONFIG_DISPLAY_USE_LVGL)
#if (LVGL_VERSION_MAJOR < 9)
    if(drv.disp_drv.rotated != r) {
        drv.disp_drv.rotated = r;
        if(drv.lv_disp) {
            lv_disp_drv_update(drv.lv_disp, &drv.disp_drv); //this is critical!
            if(lv_scr_act()) {
                lv_obj_invalidate(lv_scr_act());
            }
        }
    }
#else
    if(drv.lv_disp && r!=lv_display_get_rotation(drv.lv_disp)) {
        lv_display_set_rotation(drv.lv_disp, r);
        // lv_disp_drv_update(lv_disp, &disp_drv); //this is critical!
        if(lv_scr_act()) {
            lv_obj_invalidate(lv_scr_act());
        }
    }
#endif

#if (C_LOG_LEVEL < 2)
    if(drv.lv_disp) {
#if (LVGL_VERSION_MAJOR < 9)
        DLOG(TAG, "[%s] New orientation is %d:, rotated flag is :%d, hor_res is: %d, ver_res is: %d\n", __func__,
            (int)r, drv.disp_drv.rotated, lv_disp_get_hor_res(drv.lv_disp), lv_disp_get_ver_res(drv.lv_disp)
        );
#else
        DLOG(TAG, "[%s] New orientation is %d:, rotated flag is :%d, hor_res is: %ld, ver_res is: %ld\n", __func__,
            (int)r, lv_display_get_rotation(drv.lv_disp), lv_display_get_horizontal_resolution(drv.lv_disp), lv_display_get_vertical_resolution(drv.lv_disp)
        );
#endif
    }
#endif
#else
    if(r!=drv.rotated) {
        drv.rotated = r;
    }
#if (C_LOG_LEVEL < 2)
    DLOG(TAG, "[%s] New orientation is %d:, rotated flag is :%d\n", __func__, (int)r, drv.rotated);
#endif
#endif
    return ESP_OK;
}

esp_err_t display_drv_set_rotation(int r) {
    int prev = display_drv_get_rotation();
    int ret = _set_rotation(r);
    if(prev != r && drv.op->set_rotation) ret = drv.op->set_rotation(r);
    return ret;
}

int display_drv_get_rotation() {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s]", __func__);
#endif
#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
    return drv.disp_drv.rotated;
#else
    return lv_display_get_rotation(drv.lv_disp); 
#endif
#else
    return drv.rotated;
#endif
}

#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)

int display_drv_get_width() { return lv_disp_get_hor_res(drv.lv_disp); }
int display_drv_get_height() { return lv_disp_get_ver_res(drv.lv_disp); }

#else

int display_drv_get_width() { return lv_display_get_horizontal_resolution(drv.lv_disp); }
int display_drv_get_height() { return lv_display_get_vertical_resolution(drv.lv_disp); }

#endif

static void increase_lvgl_tick(void *arg) {
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

void display_drv_init() { if(drv.op->d_init) drv.op->d_init(); }

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
            ELOG(TAG, "[%s] Failed to allocate memory for buffer %d", __func__, i);
            ret = ESP_ERR_NO_MEM;
        }
	}
    return ret;
}

void init_lv_screen(void (*cb)(void *)) {
#if (C_LOG_LEVEL < 3)
    ILOG(TAG, "[%s]", __func__);
#endif
    // --- Initialize LVGL
#if (C_LOG_LEVEL < 3)
    ESP_LOGI(TAG, "Initialize LVGL library");
#endif
    lv_init();
    size_t bufsz = LBUFSZ;
    memset(drv.lv_mem_buf, 0, sizeof(drv.lv_mem_buf));
    init_draw_buffers(LBUFSZ, LV_DRAW_BUF_SZ, LCD_PIXELS_MEM_ALIGNED, CONV_BUF_SZ);
    uint8_t *buf[2] = {drv.lv_mem_buf[0], (LV_DRAW_BUF_SZ > 1 ? drv.lv_mem_buf[1] : NULL)};
#if (C_LOG_LEVEL < 3)
    ESP_LOGI(TAG, "Register display driver / create display to LVGL");
#endif
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

#endif