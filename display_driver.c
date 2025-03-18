#include "display_private.h"
#if defined(CONFIG_DISPLAY_ENABLED)
#include "driver_vendor.h"
#include "esp_err.h"
#include "esp_lcd_panel_ops.h"
#ifdef CONFIG_DISPLAY_USE_LVGL
#include "lvgl.h"
#endif

#if defined(CONFIG_DISPLAY_DRIVER_ST7789)
display_driver_op_t *display_drv_op = &display_driver_st7789_op;
#elif defined(CONFIG_DISPLAY_DRIVER_RM67162)
display_driver_op_t *display_drv_op = &display_driver_rm67162_op;
#elif defined(CONFIG_DISPLAY_DRIVER_QEMU)
display_driver_op_t *display_drv_op = &display_driver_qemu_op;
#elif defined(CONFIG_DISPLAY_DRIVER_SSD168X)
display_driver_op_t *display_drv_op = &display_driver_ssd168x_op;
#endif

esp_lcd_panel_handle_t display_drv_new() {
    if(!display_drv_op->new) return NULL;
    return display_drv_op->new();
}

void display_drv_del() {
    if(display_drv_op->del)
        display_drv_op->del();
}

esp_err_t display_drv_epd_request_full_update() {
    if(!display_drv_op->epd_request_full_update) return ESP_ERR_NOT_SUPPORTED;
    return display_drv_op->epd_request_full_update();
}

esp_err_t display_drv_epd_request_fast_update() {
    if(!display_drv_op->epd_request_fast_update) return ESP_ERR_NOT_SUPPORTED;
    return display_drv_op->epd_request_fast_update();
}

void display_drv_bl_set(uint8_t brightness_percent) {
    if(display_drv_op->bl_set)
        display_drv_op->bl_set(brightness_percent);
}

esp_err_t display_drv_set_rotation(int r) {
    if(!display_drv_op->set_rotation) return ESP_ERR_NOT_SUPPORTED;
    return display_drv_op->set_rotation(r);
}

int display_drv_get_rotation(void) {
    if(!display_drv_op->get_rotation) return 0;
    return display_drv_op->get_rotation();
}

bool display_drv_lock(int timeout_ms) {
    if(!display_drv_op->lock) return false;
    return display_drv_op->lock(timeout_ms);
}

void display_drv_unlock() {
    if(display_drv_op->unlock)
        display_drv_op->unlock();
}

esp_err_t display_drv_epd_refresh_and_turn_off(esp_lcd_panel_handle_t panel_handle, int rotated, m_area_t *area, uint8_t *color_map) {
    if(! display_drv_op->epd_refresh_and_turn_off) return ESP_ERR_NOT_SUPPORTED;
    return display_drv_op->epd_refresh_and_turn_off(panel_handle, rotated, area, color_map);
}

esp_err_t display_drv_epd_turn_on(esp_lcd_panel_handle_t panel_handle) {
    if(! display_drv_op->epd_turn_on) return ESP_ERR_NOT_SUPPORTED;
    return display_drv_op->epd_turn_on(panel_handle);
}

#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
lv_disp_drv_t * display_drv_get_driver() {
    if(!display_drv_op->get_driver) return NULL;
    return display_drv_op->get_driver();
}
#endif
lv_disp_t * display_drv_get() {
    if(!display_drv_op->get) return NULL;
    return display_drv_op->get();
}
void display_drv_lv_init() {
    if(display_drv_op->lv_init)
        display_drv_op->lv_init();
}
#endif

display_driver_op_t display_drv_ops = {
    .new = display_drv_new,
    .del = display_drv_del,
    .epd_request_full_update = display_drv_epd_request_full_update,
    .epd_request_fast_update = display_drv_epd_request_fast_update,
    .bl_set = display_drv_bl_set,
    .set_rotation = display_drv_set_rotation,
    .get_rotation = display_drv_get_rotation,
    .lock = display_drv_lock,
    .unlock = display_drv_unlock,
    .epd_refresh_and_turn_off = display_drv_epd_refresh_and_turn_off,
    .epd_turn_on = display_drv_epd_turn_on,
    #ifdef CONFIG_DISPLAY_USE_LVGL
    #if (LVGL_VERSION_MAJOR < 9)
    .get_driver = display_drv_get_driver,
    #endif
    .get = display_drv_get,
    .lv_init = display_drv_lv_init
    #endif
};

#endif