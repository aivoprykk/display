#include "driver_vendor.h"

#if defined(CONFIG_DISPLAY_DRIVER_SSD168X)

// #include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

// #include "esp_system.h"
// #include "esp_timer.h"

#include "display_private.h"

#include "driver/gpio.h"
// #include "driver/spi_master.h"

#include <esp_lcd_panel_ops.h>
#include "ui_events.h"
#include "logger_common.h"
#include "esp_lcd_panel_ssd168x.h"

#include "ssd168x_waveshare_lut.h"
#ifdef CONFIG_SSD168X_PANEL_SSD1681
static const char *TAG = "display_drv.ssd1681";
#else
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

// Timing constants
#define DISPLAY_RESET_DELAY_MS 10
#define DISPLAY_INIT_DELAY_MS  20
#define REFRESH_SCREEN_CFG     0xcf
#define SPI_TRANS_QUEUE_DEPTH  10

static esp_lcd_panel_handle_t panel_handle = NULL;
static esp_lcd_panel_io_handle_t io_handle = NULL;

#if defined(CONFIG_EPD_USE_CUSTOM_LUT)
#ifdef CONFIG_SSD168X_PANEL_SSD1681
static const uint8_t fast_refresh_lut[] = _1681_LUT_FAST_REFRESH_KEEP;
static const uint8_t full_refresh_lut[] = _1681_LUT_FULL_REFRESH;
#else
static const uint8_t fast_refresh_lut[] = _1680_LUT_FAST_REFRESH_0;
static const uint8_t full_refresh_lut[] = _1680_LUT_FULL_REFRESH_0;
#endif
size_t fast_refresh_lut_size = lengthof(fast_refresh_lut);
size_t full_refresh_lut_size = lengthof(full_refresh_lut);
#endif

typedef enum { 
    LOCAL_INIT_MODE_NONE = 0,
    LOCAL_INIT_MODE_FULL,   // corresponds to INIT_MODE_FULL_1 - full refresh
    LOCAL_INIT_MODE_FAST,   // corresponds to INIT_MODE_FULL_2 - fast refresh
    LOCAL_INIT_MODE_PARTIAL // corresponds to INIT_MODE_PARTIAL - partial refresh
} local_init_mode_t;

typedef struct {
local_init_mode_t init_mode_requested;
local_init_mode_t init_mode_performed;
uint32_t flush_count;
uint32_t last_flush_ms;
uint32_t full_refresh_count;
uint32_t fast_refresh_count;
uint32_t partial_refresh_count;
bool flush_requested;
uint32_t flush_request_count;
} flush_ctx_t;

static flush_ctx_t flush_ctx = {LOCAL_INIT_MODE_FAST, LOCAL_INIT_MODE_NONE, 0, 0, 0, 0, 0, false, 0};

// const unsigned char clear_img[LCD_PIXELS_MEM_ALIGNED] = { [0 ... LCD_PIXELS_MEM_ALIGNED-1] = 0xFF };

IRAM_ATTR bool _flush_ready_callback(const esp_lcd_panel_handle_t handle,
    const void *edata, void *user_data) {
    if(user_data) {
#ifdef CONFIG_DISPLAY_USE_LVGL
        FLUSH_READY_CB(user_data);
#endif
    }
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if(drv.flush_sem)
        xSemaphoreGiveFromISR(drv.flush_sem, &xHigherPriorityTaskWoken);
    if(drv.flush_complete_sem)
        xSemaphoreGiveFromISR(drv.flush_complete_sem, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE) {
        return true;
    }
    return false;
}

static esp_err_t _request_full_update() {
    DISPLAY_ILOG_SIMPLE(TAG, "[_request_full_update]");
    flush_ctx.init_mode_requested = LOCAL_INIT_MODE_FULL;
    return ESP_OK;
}

static esp_err_t _request_fast_update() {
    DISPLAY_ILOG_SIMPLE(TAG, "[_request_fast_update]");
    flush_ctx.init_mode_requested = LOCAL_INIT_MODE_FAST;
    return ESP_OK;
}

static esp_err_t _request_partial_update() {
    DISPLAY_ILOG_SIMPLE(TAG, "[_request_partial_update]");
    flush_ctx.init_mode_requested = LOCAL_INIT_MODE_PARTIAL;
    return ESP_OK;
}

static uint32_t _flush_count() {
    FUNC_ENTRYT(TAG);
    return flush_ctx.flush_count;
}

static uint32_t _last_flush_ms() {
    FUNC_ENTRYT(TAG);
    return flush_ctx.last_flush_ms;
}

void display_drv_epd_reset_flush_requested() {
    flush_ctx.flush_requested = false;
    flush_ctx.flush_request_count = 0;
}

bool display_drv_epd_get_flush_requested() {
    return flush_ctx.flush_requested;
}

bool display_drv_epd_is_full_refresh_in_progress(void) {
    // Full refresh is in progress when requested is FULL_1 but not yet performed
    return (flush_ctx.init_mode_requested == LOCAL_INIT_MODE_FULL && 
            flush_ctx.init_mode_performed != LOCAL_INIT_MODE_FULL);
}

uint32_t display_drv_epd_get_flush_request_count() {
    return flush_ctx.flush_request_count;
}

static void update_counters() {
    switch(flush_ctx.init_mode_performed) {
        case LOCAL_INIT_MODE_FAST:
            flush_ctx.fast_refresh_count++;
            break;
        case LOCAL_INIT_MODE_FULL:
            flush_ctx.full_refresh_count++;
            break;
        case LOCAL_INIT_MODE_PARTIAL:
            flush_ctx.partial_refresh_count++;
            break;
        default:
            break;
    }
}

static void update_flush_count() {
    flush_ctx.flush_count++;
    flush_ctx.last_flush_ms = get_millis();
}

void display_drv_epd_signal_no_flush() {
    update_flush_count();
}

static esp_err_t _turn_off(esp_lcd_panel_handle_t panel_handle) {
    FUNC_ENTRY(TAG);
    if(epaper_panel_shut_down(panel_handle)) {
        return ESP_FAIL;
    }
    return ESP_OK;
}

static bool _needs_init(local_init_mode_t requested_mode, local_init_mode_t performed_mode) {
    FUNC_ENTRY_ARGSD(TAG, "requested: 0x%02x, performed: 0x%02x",
        requested_mode, performed_mode);
    // Determine if we need to reinitialize the display
    // Rules:
    // 1. Full refresh (FULL_1) → always reset + init (baseline mode)
    // 2. Fast refresh (FULL_2) → reset + init only if previous was NOT fast (need to load custom LUT)
    // 3. Partial refresh (PARTIAL) → reset + init only if previous was fast (need to clear custom LUT)
    if(requested_mode == LOCAL_INIT_MODE_FULL) {
        // Full refresh always needs init
        return true;
    }
    else if(requested_mode == LOCAL_INIT_MODE_FAST) {
        // Fast refresh needs init if not already in fast mode
        // (to load the custom fast_refresh_lut for first time or after coming from full/partial)
        if(performed_mode != LOCAL_INIT_MODE_FAST) {
            return true;
        }
    }
    else if(requested_mode == LOCAL_INIT_MODE_PARTIAL) {
        // Partial refresh needs init only if previous was full mode
        // (to reset and remove full LUT, go back to default parameters)
        if(performed_mode == LOCAL_INIT_MODE_FULL) {
            return true;
        }
    }
    return false;
}

static esp_err_t _turn_on(esp_lcd_panel_handle_t panel_handle, bool needs_init) {
    FUNC_ENTRY(TAG);
    esp_err_t err = ESP_OK;
    if(needs_init) {
        FUNC_ENTRY_ARGS(TAG, "Reset/Init e-Paper display");
        if(flush_ctx.flush_count > 0) {
            if(_turn_off(panel_handle) != ESP_OK) {
                goto cleanup;
            }
        }
        err = esp_lcd_panel_reset(panel_handle);
        if(err != ESP_OK) {
            FUNC_ENTRY_ARGE(TAG, "Failed to reset panel: %s",
                esp_err_to_name(err));
            goto cleanup;
        }
        vTaskDelay(pdMS_TO_TICKS(DISPLAY_RESET_DELAY_MS));
        epaper_panel_init_mode_t init_mode = flush_ctx.init_mode_requested == LOCAL_INIT_MODE_FULL ? 
            INIT_MODE_FULL_1 : INIT_MODE_FULL_2;
        err = epaper_panel_init_screen_ssd168x(panel_handle, init_mode, 0);
        if(err != ESP_OK) {
            FUNC_ENTRY_ARGE(TAG, "Failed to init screen: %s",
                esp_err_to_name(err));
            goto cleanup;
        }
        vTaskDelay(pdMS_TO_TICKS(DISPLAY_INIT_DELAY_MS));
    }

    err = esp_lcd_panel_disp_on_off(panel_handle, true);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to turn on display: %s",
            esp_err_to_name(err));
        goto cleanup;
    }

#if defined(CONFIG_EPD_USE_CUSTOM_LUT)    
    // Set custom LUT only for fast refresh mode (FULL_2)
    // The LUT persists until next reset, so it only needs to be set once
    if(flush_ctx.init_mode_requested != LOCAL_INIT_MODE_FULL && needs_init) {
        FUNC_ENTRY_ARGS(TAG, " Set fast refresh LUT");
        err = epaper_panel_set_custom_lut_ssd168x(panel_handle,
            fast_refresh_lut, fast_refresh_lut_size);
        if(err != ESP_OK) {
            FUNC_ENTRY_ARGE(TAG, "Failed to set custom LUT: %s",
                esp_err_to_name(err));
            goto cleanup;
        }
    }
    else if(flush_ctx.init_mode_requested == LOCAL_INIT_MODE_FULL && needs_init) {
        // If coming from fast refresh to other mode, need to reset LUT to full refresh
        FUNC_ENTRY_ARGS(TAG, " Set full refresh (default) LUT");
        err = epaper_panel_set_custom_lut_ssd168x(panel_handle, full_refresh_lut, full_refresh_lut_size);
        if(err != ESP_OK) {
            FUNC_ENTRY_ARGE(TAG, "Failed to set custom LUT: %s",
                esp_err_to_name(err));
            goto cleanup;
        }
    }
#endif    
    // Note: init_mode_performed is updated in _flush_cb() after successful refresh completes
    return ESP_OK;

cleanup:
    return err != ESP_OK ? err : ESP_FAIL;
}

static esp_err_t _draw_bitmap_only(esp_lcd_panel_handle_t panel_handle,
    int rotated, m_area_t *area, uint8_t *color_map) {
    esp_err_t err = ESP_OK;
    if(rotated == DISP_ROT_NONE || rotated == DISP_ROT_180) {
        err = esp_lcd_panel_swap_xy(panel_handle, false);
        if(err != ESP_OK) {
            WLOG(TAG, "Failed to set swap_xy to false %d", err);
            return err;
        }
    }
    else {
        err = esp_lcd_panel_swap_xy(panel_handle, true);
        if(err != ESP_OK) {
            WLOG(TAG, "Failed to set swap_xy to true %d", err);
            return err;
        }
    }

    if(rotated == DISP_ROT_NONE) {
        err = esp_lcd_panel_mirror(panel_handle, false, false);
        if(err != ESP_OK) {
            WLOG(TAG, "Failed to set mirror to false, false %d", err);
            return err;
        } // x inc y inc
    }
    else if(rotated == DISP_ROT_90) {
        err = esp_lcd_panel_mirror(panel_handle, true, false);
        if(err != ESP_OK) {
            WLOG(TAG, "Failed to set mirror to true, false %d", err);
            return err;
        } // x dec y inc
    }
    else if(rotated == DISP_ROT_180) {
        err = esp_lcd_panel_mirror(panel_handle, true, true);
        if(err != ESP_OK) {
            WLOG(TAG, "Failed to set mirror to true, true %d", err);
            return err;
        } // x dec y dec
    }
    else { // DISP_ROT_270 (270 degrees)
        err = esp_lcd_panel_mirror(panel_handle, false, true);
        if(err != ESP_OK) {
            WLOG(TAG, "Failed to set mirror to false, true %d", err);
            return err;
        } // x inc y dec
    }

    err = epaper_panel_set_bitmap_color_ssd168x(panel_handle, SSD168X_EPAPER_BITMAP_BLACK);
    if(err != ESP_OK) {
        WLOG(TAG, "Failed to set bitmap color to BLACK %d", err);
        return err;
    }
    err = esp_lcd_panel_draw_bitmap(panel_handle, area->x1, area->y1,
        area->x2 + 1, area->y2 + 1, color_map);
    if(err != ESP_OK) {
        WLOG(TAG, "Failed to draw bitmap %d", err);
        return err;
    }
    return ESP_OK;
}

static esp_err_t _refresh_screen_only(esp_lcd_panel_handle_t panel_handle) {
    esp_err_t err = epaper_panel_refresh_screen_ssd168x(panel_handle, REFRESH_SCREEN_CFG);
    if(err != ESP_OK) {
        WLOG(TAG, "Failed to refresh screen %d", err);
        return err;
    }
    err = epaper_panel_update_full_screen_ssd168x(panel_handle);
    if(err != ESP_OK) {
        WLOG(TAG, "Failed to update full screen %d", err);
        return err;
    }
    return ESP_OK;
}

static esp_err_t _refresh_and_turn_off(esp_lcd_panel_handle_t panel_handle,
    int rotated, m_area_t *area, uint8_t *color_map) {
    FUNC_ENTRY(TAG);
    esp_err_t err = _draw_bitmap_only(panel_handle, rotated, area, color_map);
    if (err != ESP_OK) return err;

    err = _refresh_screen_only(panel_handle);
    return err;
}

#ifdef CONFIG_DISPLAY_USE_LVGL
// Apply 6-bit shift to the entire buffer after rotation
// Apply 6-bit shift to the entire buffer after rotation
#if 0
static void apply_bit_shift(uint8_t *buffer, int width, int height, int shift_bits) {
    if (shift_bits == 0) return;
    int abs_shift = abs(shift_bits);
    if (abs_shift <= 0 || abs_shift >= 8) return;
    int bytes_per_row = (width + 7) / 8;

    for (int row = 0; row < height; row++) {
        uint8_t carry = 0;
        for (int col = 0; col < bytes_per_row; col++) {
            int idx = row * bytes_per_row + col;
            uint8_t current = buffer[idx];
            uint8_t new_byte;

            if (shift_bits > 0) {
                // RIGHT shift
                new_byte = (current >> abs_shift) | (carry << (8 - abs_shift));
                carry = current & ((1 << abs_shift) - 1); // Save bottom bits
            } else {
                // LEFT shift  
                new_byte = (current << abs_shift) | carry;
                carry = current >> (8 - abs_shift); // Save top bits
            }

            buffer[idx] = new_byte;
        }
    }
}
#endif
// LVGL pixel conversion callback for rotate_bitmap function
static uint8_t lvgl_pixel_convert_cb(const unsigned char *src_data,
    esp_lcd_ssd168x_area_t src_area, int rotation, int data_format,
    void *user_data) {
    int src_x = src_area.x1;
    int src_y = src_area.y1;
    int src_w = src_area.x2;
    int src_h = src_area.y2;

    if (src_w <= 0 || src_h <= 0) {
        return 0;
    }
    if (src_x < 0 || src_x >= src_w || src_y < 0 || src_y >= src_h) {
        return 0;
    }

    // rotate_bitmap already maps the logical coordinates, so we only need the linear index
    int pixel_idx = src_y * src_w + src_x;

    uint8_t pixel_value = 0;

    // Convert pixel based on LVGL format
    if (data_format == 1) {
        // LVGL v8: color array
#if (LVGL_VERSION_MAJOR < 9)
        lv_color_t *colors = (lv_color_t *)src_data;
        pixel_value = (lv_color_brightness(colors[pixel_idx]) < 128) ? 1 : 0;
#else
        pixel_value = 0; // Fallback for LVGL v9 with wrong format
#endif
    } else if (data_format == 2) {
        // LVGL v9: 1-bit packed data
        pixel_value = (src_data[pixel_idx / 8] >> (7 - (pixel_idx % 8))) & 1;
    }

    return pixel_value;
}

// Streamlined flush callback using callback-based rotate_bitmap
#define MYINT lv_coord_t
#define MYINT_D "d"
static bool frame_active = false; // Track if we are in the middle of a frame update

static void _flush_cb(display_lvgl_flush_ctx_t *dspl, const lv_area_t *area,
    display_lvgl_color_t *color_map) {
    FUNC_ENTRY_ARGS(TAG, " x1:%"MYINT_D" y1:%"MYINT_D", x2:%"MYINT_D" y2:%"MYINT_D"",
        area->x1, area->y1, area->x2, area->y2);

    bool is_last = display_lvgl_flush_is_last(dspl);

    flush_ctx.flush_requested = true;
    flush_ctx.flush_request_count++;

    // Wait for previous flush to complete
    xSemaphoreTake(drv.flush_complete_sem, portMAX_DELAY);

    esp_lcd_panel_handle_t panel_handle = GET_USER_DATA(dspl);

    MYINT offsetx1 = area->x1;
    MYINT offsetx2 = area->x2;
    MYINT offsety1 = area->y1;
    MYINT offsety2 = area->y2;

    // Calculate area dimensions
    MYINT len_x = abs(offsetx1 - offsetx2) + 1;
    MYINT len_y = abs(offsety1 - offsety2) + 1;
    int rotated = display_drv_get_rotation();

    // Adjust dimensions for SSD1680 padding requirements
// #if defined(CONFIG_SSD168X_PANEL_SSD1680)
//     if(rotated == DISP_ROT_270 || rotated == DISP_ROT_90) {
//         len_y = ROUND_UP_TO_8(len_y);
//     } else {
//         len_x = ROUND_UP_TO_8(len_x);
//     }
// #endif

    // Get buffer for e-paper display
    uint8_t *converted_buffer_black = drv.lv_mem_buf[LV_DRAW_BUF_SZ];

    // Determine whether LVGL already provides bit-packed data (v9 + I1 color format)
    bool src_bitpacked = false;
#if (LVGL_VERSION_MAJOR >= 9)
    src_bitpacked = (drv.color_format == LV_COLOR_FORMAT_I1);
#endif

    // Prepare conversion context
    pixel_convert_cb_t convert_cb = src_bitpacked ? NULL : lvgl_pixel_convert_cb;
    int data_format = 0;
    unsigned char *src_data = (unsigned char *)color_map;

#if (LVGL_VERSION_MAJOR < 9)
    data_format = 1; // LVGL v8 uses lv_color_t arrays
#else
    if (!src_bitpacked) {
        data_format = 2; // Expect packed bits for LVGL v9 fallback path
    }
#endif

    // Convert LVGL rotation to driver rotation constants
    // Note: Driver rotation values are counter-clockwise: 1=270°, 3=90°
    unsigned char driver_rotation = 0;
    switch(rotated) {
        case DISP_ROT_90:   driver_rotation = 3; break;  // 90° CW = driver 3
        case DISP_ROT_180:  driver_rotation = 2; break;  // 180° = driver 2
        case DISP_ROT_270:  driver_rotation = 1; break;  // 270° CW = driver 1  
        default:            driver_rotation = 0; break;  // 0° = driver 0
    }

    // Fast path: if rotation is 0 and source is already bit-packed, we can just copy
    if (driver_rotation == 0 && src_bitpacked) {
        // memcpy(converted_buffer_black, src_data, (len_x * len_y + 7) / 8); 
        // Actually, since src_bitpacked is true, src_data is already a packed bitmap.
        // However, we need to be careful about stride/alignment if the width isn't a multiple of 8.
        // But for EPDs usually full updates are byte aligned.
        // For simplicity and safety against striding issues in sub-window updates (though we usually do full),
        // we might still want to use rotate_bitmap or a smarter copy. 
        //
        // If we trust that len_x is a multiple of 8 (which it is for full screen), we can memcpy.
        // Use the existing buffer pointer if we want to avoid copy? 
        // The rest of the pipeline expects 'converted_buffer_black' to be populated.

        int bytes_to_copy = ((len_x + 7) / 8) * len_y;
        memcpy(converted_buffer_black, src_data, bytes_to_copy);
    } else {
        // Use rotate_bitmap with LVGL conversion callback
        rotate_bitmap(src_data, converted_buffer_black, 
                     len_x, len_y, driver_rotation, 
                     convert_cb, data_format, 0);
    }


// #if defined(CONFIG_SSD168X_PANEL_SSD1680)
    // Apply bit shift for SSD1680 based on rotation
    // apply_bit_shift(converted_buffer_black, len_x, len_y, 2);
// #endif

    // Adjust area coordinates for rotated buffer dimensions
    MYINT final_offsetx1 = offsetx1;
    MYINT final_offsetx2 = offsetx2; 
    MYINT final_offsety1 = offsety1;
    MYINT final_offsety2 = offsety2;

    if(driver_rotation == 1 || driver_rotation == 3) { // 270° or 90° 
        // Dimensions are swapped, so adjust area to match rotated buffer
        final_offsetx1 = offsety1;
        final_offsetx2 = offsety2;
        final_offsety1 = offsetx1; 
        final_offsety2 = offsetx2;
    }

    FUNC_ENTRY_ARGS(TAG, " processed %"MYINT_D"x%"MYINT_D" buffer, rotation=%d",
        len_x, len_y, rotated);

    // Handle display refresh - always use DISP_ROT_NONE to prevent double rotation
    // (software rotation already applied by rotate_bitmap above)
    m_area_t flush_area = {final_offsetx1, final_offsety1, final_offsetx2, final_offsety2};
    esp_err_t err = ESP_OK;

    // Turn on display and perform refresh
    // _turn_on() will handle init if mode changed, otherwise it's a no-op
    // Only init if we are starting a frame, or if we are not in a frame sequence yet
    bool needs_init = _needs_init(flush_ctx.init_mode_requested, flush_ctx.init_mode_performed);

    // If we're not inside an active frame sequence, this is the first chunk
    if (!frame_active) {
        frame_active = true;
        err = _turn_on(panel_handle, needs_init);
    } else {
        // We are inside a frame sequence. 
        // Even if needs_init is true (e.g. FULL refresh always says true), 
        // we should NOT re-init/reset here because it would wipe previous chunks.
        // We implicitly assume the first chunk handled the necessary init.
        err = _turn_on(panel_handle, false); // Just ensure power is on, no reset
    }

    if(err == ESP_OK) {
        DLOG(TAG, "Display drawing RAM");
        // Always draw the pixels to RAM
        err = _draw_bitmap_only(panel_handle, DISP_ROT_NONE,
            &flush_area, converted_buffer_black);

        // Only trigger screen refresh update on the LAST chunk
        if(err == ESP_OK && is_last) {
            DLOG(TAG, "Display refresh trigger (mode 0x%02x)", flush_ctx.init_mode_requested);
            err = _refresh_screen_only(panel_handle);

            // Update performed mode only after successful refresh
            if(err == ESP_OK && flush_ctx.init_mode_requested != flush_ctx.init_mode_performed) {
                DLOG(TAG, "Mode updated: 0x%02x -> 0x%02x", flush_ctx.init_mode_performed, flush_ctx.init_mode_requested);
                flush_ctx.init_mode_performed = flush_ctx.init_mode_requested;
                // Increment the appropriate refresh count
                update_counters();
            }
            frame_active = false; // Frame done
        }
    }

    if(err != ESP_OK) {
        ELOG(TAG, "Display refresh failed: %s", esp_err_to_name(err));
        frame_active = false; // Reset on error
    }

    // Update statistics and notify completion
    if (err == ESP_OK) {
        if (is_last) {
            update_flush_count();
            // Refresh started successfully, callback will signal completion
            FUNC_ENTRY_ARGSD(TAG, "flush done count: %" PRIu32 "", flush_ctx.flush_count);
            esp_event_post(UI_EVENT, UI_EVENT_FLUSH_DONE, 0, 0, pdMS_TO_TICKS(100));
        } else {
            // If not last, we are done with this chunk immediately
            // But we must signal flush ready to LVGL
            xSemaphoreGive(drv.flush_complete_sem); // Ready for next chunk immediately
        }
    } else if (err == ESP_ERR_NOT_FINISHED) {
        WLOG(TAG, "Panel busy, waiting for previous refresh to complete");
        // Don't give semaphore, wait for callback from previous refresh
    } else  {
        ELOG(TAG, "Flush sequence failed: %s", esp_err_to_name(err));
        if(drv.flush_sem) {
            xSemaphoreGive(drv.flush_sem);
        }
        xSemaphoreGive(drv.flush_complete_sem);
        display_handle_driver_error();
        frame_active = false;
        return;
    }
    FLUSH_READY_CB(dspl);
}

#if (LVGL_VERSION_MAJOR < 9)
static void _wait_cb(struct _lv_disp_drv_t *disp_drv)
#else
static void _wait_cb(display_lvgl_flush_ctx_t *disp)
#endif
{
    if(drv.flush_sem)
        xSemaphoreTake(drv.flush_sem, portMAX_DELAY);
}

#if defined(BELOW_IS_NEEDED)
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

#if (LVGL_VERSION_MAJOR < 9)
#if 0
static void set_px_cb(display_lvgl_flush_ctx_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
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
#endif
#endif

static void _init_cb(void *dsp) {
    FUNC_ENTRY(TAG);
    display_lvgl_flush_ctx_t *disp_drv = (display_lvgl_flush_ctx_t *)dsp;
#if (LVGL_VERSION_MAJOR < 9)
    // Set the callback functions
    disp_drv->hor_res = LCD_H_VISIBLE;
    disp_drv->ver_res = LCD_V_VISIBLE;
    disp_drv->rotated = DISP_ROT_270;
    // NOTE: The ssd168x e-paper is monochrome and 1 byte represents 8 pixels
    // so full_refresh is MANDATORY because we cannot set position to bitmap at pixel level
    disp_drv->full_refresh = 1;
    disp_drv->direct_mode = 1;
    disp_drv->sw_rotate = 0;
    disp_drv->user_data = panel_handle;
    // alloc bitmap buffer to draw
    disp_drv->flush_cb = _flush_cb;
    disp_drv->wait_cb = _wait_cb;
    // disp_drv->set_px_cb = set_px_cb;
    // disp_drv->drv_update_cb = epaper_lvgl_port_update_callback;
#else
    lv_display_set_rotation(disp, DISP_ROT_270);
    // NOTE: The ssd168x e-paper is monochrome and 1 byte represents 8 pixels
    // so full_refresh is MANDATORY because we cannot set position to bitmap at pixel level
    // lv_disp_set_full_refresh(disp, true);
    // lv_disp_set_direct_mode(disp, 1);
    // lv_disp_set_sw_rotate(disp, false);
    lv_display_set_user_data(disp, panel_handle);
    lv_display_set_flush_cb(disp, _flush_cb);
    lv_display_set_flush_wait_cb(disp, _wait_cb);
    // lv_display_set_color_format(disp, LV_COLOR_FORMAT_I8);
#endif
}
#endif

static void _d_init() {
    FUNC_ENTRY(TAG);
#ifdef CONFIG_DISPLAY_USE_LVGL
#if (LVGL_VERSION_MAJOR < 9)
    if(drv.disp_drv.user_data == NULL)
#else
    if(lv_display_get_user_data(drv.lv_disp) == NULL)
#endif
    {
        init_lv_screen(_init_cb);
        // --- Register the e-Paper refresh done callback
        epaper_panel_callbacks_t cbs = {
            .on_epaper_refresh_done = _flush_ready_callback
        };
#if (LVGL_VERSION_MAJOR < 9)
        epaper_panel_register_event_callbacks_ssd168x(panel_handle, &cbs, &drv.disp_drv);
#else
        epaper_panel_register_event_callbacks_ssd168x(panel_handle, &cbs, drv.lv_disp);
#endif
    }
#else
    epaper_panel_callbacks_t cbs = {0};
    epaper_panel_register_event_callbacks_ssd168x(panel_handle, &cbs, NULL);
    // Note: rotation is handled by display_drv_set_rotation()
#endif
}

static esp_lcd_panel_handle_t _new() {
    FUNC_ENTRY(TAG);
    esp_err_t err = ESP_OK;
    // Initialize GPIOs direction & initial states
#if (PIN_NUM_EPD_CS >= 0)
    err = gpio_set_direction(PIN_NUM_EPD_CS, GPIO_MODE_OUTPUT);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to set CS direction: %s",
            esp_err_to_name(err));
        return NULL;
    }
    err = gpio_set_level(PIN_NUM_EPD_CS, 1);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to set CS level: %s",
            esp_err_to_name(err));
        return NULL;
    }
#endif
#if (PIN_NUM_EPD_DC >= 0)
    err = gpio_set_direction(PIN_NUM_EPD_DC, GPIO_MODE_OUTPUT);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to set DC direction: %s",
            esp_err_to_name(err));
        return NULL;
    }
    err = gpio_set_level(PIN_NUM_EPD_DC, 1);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to set DC level: %s",
            esp_err_to_name(err));
        return NULL;
    }
#endif
#if (PIN_NUM_EPD_RST >= 0)
    err = gpio_set_direction(PIN_NUM_EPD_RST, GPIO_MODE_OUTPUT);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to set RST direction: %s",
            esp_err_to_name(err));
        return NULL;
    }
    err = gpio_set_level(PIN_NUM_EPD_RST, 1);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to set RST level: %s",
            esp_err_to_name(err));
        return NULL;
    }
#endif
#if (PIN_NUM_EPD_BUSY >= 0)
    err = gpio_set_direction(PIN_NUM_EPD_BUSY, GPIO_MODE_INPUT);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to set BUSY direction: %s",
            esp_err_to_name(err));
        return NULL;
    }
    err = gpio_set_pull_mode(PIN_NUM_EPD_BUSY, GPIO_PULLUP_ONLY);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to set BUSY pull mode: %s",
            esp_err_to_name(err));
        return NULL;
    }
#endif

    ILOG(TAG, "Initialize SPI bus");
    spi_bus_config_t buscfg = {
        .sclk_io_num = PIN_NUM_SCLK,
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_RESOLUTION,
    };
    err = spi_bus_initialize(SPIx_HOST, &buscfg, SPI_DMA_CH_AUTO);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to initialize SPI bus: %s",
            esp_err_to_name(err));
        return NULL;
    }

    ILOG(TAG, "Install panel IO");
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = PIN_NUM_EPD_DC,
        .cs_gpio_num = PIN_NUM_EPD_CS,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ,
        .lcd_cmd_bits = LCD_CMD_BITS,
        .lcd_param_bits = LCD_PARAM_BITS,
        .spi_mode = 0,
        .trans_queue_depth = SPI_TRANS_QUEUE_DEPTH,
        .on_color_trans_done = NULL,
    };
    // --- Attach the LCD to the SPI bus
    err = esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPIx_HOST,
        &io_config, &io_handle);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to create panel io: %s",
            esp_err_to_name(err));
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
    err = gpio_install_isr_service(0);
    if(err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        FUNC_ENTRY_ARGE(TAG, "Failed to install GPIO ISR service: %s",
            esp_err_to_name(err));
        // Continue anyway, ISR service might already be installed
    }
    err = esp_lcd_new_panel_ssd168x(io_handle, &panel_config, &panel_handle);
    if(err != ESP_OK) {
        FUNC_ENTRY_ARGE(TAG, "Failed to create panel: %s",
            esp_err_to_name(err));
        return NULL;
    }

    // // --- Reset the display
    // ILOG(TAG, "Resetting e-Paper display...");
    // if(esp_lcd_panel_reset(panel_handle)) {
    //     ELOG(TAG, "Failed to reset panel");
    //     return NULL;
    // }
    // delay_ms(100);
    // // --- Initialize panel
    // ILOG(TAG, "Initializing e-Paper display...");
    // if(esp_lcd_panel_init(panel_handle)) {
    //     ELOG(TAG, "Failed to init panel");
    //     return NULL;
    // }
#if (LCD_H_GAP > 0) || (LCD_V_GAP > 0)
    esp_lcd_panel_set_gap(panel_handle, LCD_H_GAP, LCD_V_GAP);
#endif
    // delay_ms(100);
    // display_lv_init();

    return panel_handle;
}

static void _del() {
    FUNC_ENTRY(TAG);
#ifdef CONFIG_DISPLAY_USE_LVGL
#if LV_MEM_CUSTOM == 0
    lv_deinit();
#else
    lv_mem_deinit();
#endif
#endif
    esp_lcd_panel_del(panel_handle);
    panel_handle = NULL;
    esp_lcd_panel_io_del(io_handle);
    io_handle = NULL;
    for(uint8_t i = LV_DRAW_BUF_SZ; i < LV_DRAW_BUF_SZ + CONV_BUF_SZ; i++) {
        if(drv.lv_mem_buf[i]) {
            heap_caps_free(drv.lv_mem_buf[i]);
            drv.lv_mem_buf[i] = NULL;
        }
    }
    // Cleanup SPI bus if needed (only if no other devices use it)
    // Note: spi_bus_free() should be called carefully as it affects all devices
}

display_driver_op_t display_driver_ssd168x_op = {
    .new = _new,
    .del = _del,
    .set_rotation = 0,
    .d_init = _d_init,
    .epd_request_fast_update = _request_fast_update,
    .epd_request_full_update = _request_full_update,
    .epd_request_partial_update = _request_partial_update,
    .epd_refresh_and_turn_off = _refresh_and_turn_off,
    // .epd_turn_on = _turn_on,
    .epd_turn_off = _turn_off,
    .flush_count = _flush_count,
    .epd_last_flush_ms = _last_flush_ms,
};

#endif

