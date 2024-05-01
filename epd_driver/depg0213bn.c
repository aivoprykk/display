// class DEPG0213BN : Display class for DEPG0213BN e-Paper from DKE
//
// based on Demo Example from Good Display, available here: http://www.e-paper-display.com/download_detail/downloadsId=806.html
// Panel: DEPG0213BN : https://www.dke.top/products/213-eiink-display
// Controller : SSD1680 : https://www.good-display.com/companyfile/101.html
// Display: LILYGO® T5 V2.3.1 2.13 inch : https://www.aliexpress.com/item/32869729970.html
//
// Author : J-M Zingg
//
// Version : see library.properties
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//
// Library: https://github.com/ZinggJM/DEPG0213BN

#include "depg0213bn.h"
#include "epd_driver_private.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

#include "esp_log.h"
#include "esp_system.h"
#include "esp_timer.h"

#include "logger_common.h"
#include "epdg.h"
#include "epd_driver_spi.h"

// Partial Update Delay, may have an influence on degradation
#define DEPG0213BN_PU_DELAY 300

#define N DEPG0213BN

static const char* TAG = QUOTE_CMD(N);

static const uint16_t WIDTH = 128;
static const uint16_t WIDTH_VISIBLE = 122;
static const uint16_t HEIGHT = 250;
static bool hasColor = false;
static bool hasPartialUpdate = true;
static const bool hasFastPartialUpdate = true;
static const bool useFastFullUpdate = true;        // set false for extended (low) temperature range
static const uint16_t power_on_time = 80;         // ms, e.g. 95868us
static const uint16_t power_off_time = 80;        // ms, e.g. 140350us
static const uint16_t full_refresh_time = 1200;    // ms, e.g. 4011934us
static const uint16_t partial_refresh_time = 300;  // ms, e.g. 736721us

#define SSD168X_DRIVER_OUTPUT_CONTROL 0x01
#define SSD1680_PARAM_DATA_ENTRY_MODE_1       0x01
#define SSD1680_PARAM_DATA_ENTRY_MODE_2       0x02
#define SSD1680_PARAM_DATA_ENTRY_MODE_3       0x03
#define SSD1680_PARAM_DATA_ENTRY_MODE_4       0x04
#define SSD168X_BOOSTER_SOFT_START_CONTROL 0x0C
#define SSD168X_GATE_SCAN_START_POSITION 0x0F
#define SSD168X_DEEP_SLEEP_MODE 0x10
#define SSD168X_DATA_ENTRY_MODE_SETTING 0x11
#define SSD168X_SW_RESET 0x12
#define SSD168X_TEMPERATURE_SENSOR_READ 0x18
#define SSD168X_TEMPERATURE_SENSOR_CONTROL 0x1A
#define SSD168X_MASTER_ACTIVATION 0x20
#define SSD1680_CMD_ACTIVE_DISP_UPDATE_SEQ  0x20
#define SSD168X_DISPLAY_UPDATE_CONTROL_1 0x21
#define SSD1680_PARAM_TEMP_SENSOR           0x80
#define SSD168X_DISPLAY_UPDATE_CONTROL_2 0x22
#define SSD1680_CMD_SET_DISP_UPDATE_CTRL    0x22
#define SSD168X_WRITE_RAM_BW 0x24
#define SSD168X_WRITE_RAM_RED 0x26
#define SSD168X_WRITE_VCOM_REGISTER 0x2C
#define SSD1680_CMD_SET_VCOM_REG            0x2c
#define SSD1680_CMD_SET_SRC_DRIVING_VOLTAGE 0x04
#define SSD1680_PARAM_SRC_DRIVING_VOLTAGE   ((uint8_t[]) {0x41, 0x00, 0x32})
#define SSD168X_WRITE_LUT_REGISTER 0x32
#define SSD1680_CMD_SET_LUT_REG             0x32
#define SSD1680_CMD_SET_WRITE_REGISTER       0x37
#define SSD168X_SET_DUMMY_LINE_PERIOD 0x3A
#define SSD168X_SET_GATE_TIME 0x3B
#define SSD168X_BORDER_WAVEFORM_CONTROL 0x3C
#define SSD1680_CMD_SET_BORDER_WAVEFORM     0x3c
#define SSD1680_PARAM_BORDER_WAVEFORM       0x80
#define SSD1680_CMD_SET_END_OPTION          0x3f
#define SSD168X_SET_RAM_X_ADDRESS_START_END_POSITION 0x44
#define SSD168X_SET_RAM_Y_ADDRESS_START_END_POSITION 0x45
#define SSD168X_SET_RAM_X_ADDRESS_COUNTER 0x4E
#define SSD168X_SET_RAM_Y_ADDRESS_COUNTER 0x4F
#define SSD168X_TERMINATE_FRAME_READ_WRITE 0xFF

// #define DISABLE_DIAGNOSTIC_OUTPUT

// Partial Update Delay, may have an influence on degradation
#define PU_DELAY 300

const uint8_t lut_partial_b[] = { // gxepd gps logger mod
    /* LUT 0 VS Group 0~11 */
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* LUT 1 VS Group 0~11 */
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* LUT 2 VS Group 0~11 */
    0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* LUT 3 VS Group 0~11 */
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* LUT 4 VS Group 0~11 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 5*12=60 bytes
    /* --- */ 
    /* Only Group0~2 are used */ 
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // Partial update bad contrast with 0x10, change to 0x40, Jan Heynen !!!!!
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 12*7=84 bytes  
    /* --- */ 
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22,         // 6 bytes
    
    0x00, 0x00, 0x00,                           // 3 bytes, totaal dus 153 bytes
    
    // 0x22, 0x17, 0x41, 0x00, 0x32, 0x32
};

const uint8_t lut_partial[] = { // gxepd1
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    /* --- */ 
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    /* --- */ 
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00,
};

void update(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    if (epd->_current_page != -1)
        return;
    epd->_using_partial_mode = false;
    Init_Full(epd, 0x03);
    if(epd->_initial_refresh){
        // memset(epd->bw_buf, 0, epd->bw_buf_size);
        // memset(epd->red_buf, 0, epd->red_buf_size);
        epd->_initial_refresh = false;
    }
    _write_ram_buf(epd, SSD168X_WRITE_RAM_BW, epd->bw_buf, epd->bw_buf_size);
    //_write_ram_buf(epd, SSD168X_WRITE_RAM_RED, epd->bw_buf, epd->bw_buf_size);
    Update_Full(epd);
    powerDown(epd);
    TIMER_E
}

/* static void drawBitmap_b(void* _me, const uint8_t* bitmap, uint32_t size, int16_t mode) {
    epd_g_t* epd = _me;
    depg0213bn_t* me = epd->depg0213bn;
    assert(me);
    if (epd->_current_page != -1)
        return;
    // example bitmaps are made for y-decrement, x-increment, for origin on opposite corner
    // bm_flip_x for normal display (bm_flip_y would be rotated)
    if (mode & bm_default)
        mode |= bm_flip_x;
    uint8_t ram_entry_mode = 0x03;  // y-increment, x-increment for normal mode
    if ((mode & bm_flip_y) && (mode & bm_flip_x))
        ram_entry_mode = 0x00;  // y-decrement, x-decrement
    else if (mode & bm_flip_y)
        ram_entry_mode = 0x01;  // y-decrement, x-increment
    else if (mode & bm_flip_x)
        ram_entry_mode = 0x02;  // y-increment, x-decrement
    if (mode & bm_partial_update) {
        epd->_using_partial_mode = true;  // remember
        Init_Part(_me, ram_entry_mode);
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_BW);
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            uint8_t data = 0xFF;  // white is 0xFF on device
            if (i < size) {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
                data = pgm_read_byte(&bitmap[i]);
#else
                data = bitmap[i];
#endif
                if (mode & bm_invert)
                    data = ~data;
            }
            epd->op->writeByte(_me, data);
        }
        Update_Part(_me);
        epd->op->delay(PU_DELAY);
        // update previous buffer
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_RED);
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            uint8_t data = 0xFF;  // white is 0xFF on device
            if (i < size) {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
                data = pgm_read_byte(&bitmap[i]);
#else
                data = bitmap[i];
#endif
                if (mode & bm_invert)
                    data = ~data;
            }
            epd->op->writeByte(_me, data);
        }
        epd->op->delay(PU_DELAY);
    } else {
        epd->_using_partial_mode = false;  // remember
        Init_Full(_me, ram_entry_mode);
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_BW);
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            uint8_t data = 0xFF;  // white is 0xFF on device
            if (i < size) {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
                data = pgm_read_byte(&bitmap[i]);
#else
                data = bitmap[i];
#endif
                if (mode & bm_invert)
                    data = ~data;
            }
            epd->op->writeByte(_me, data);
        }
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_RED);  // both buffers same for full b/w
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            uint8_t data = 0xFF;  // white is 0xFF on device
            if (i < size) {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
                data = pgm_read_byte(&bitmap[i]);
#else
                data = bitmap[i];
#endif
                if (mode & bm_invert)
                    data = ~data;
            }
            epd->op->writeByte(_me, data);
        }
        Update_Full(_me);
    }
} */

/* static void eraseDisplay(void* _me, bool using_partial_update) {
    epd_g_t* epd = _me;
    if (epd->_current_page != -1)
        return;
    if (using_partial_update) {
        epd->_using_partial_mode = true;  // remember
        Init_Part(_me, 0x01);
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_BW);
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            epd->op->writeByte(_me, 0xFF);
        }
        Update_Part(_me);
        epd->op->delay(PU_DELAY);
        // update previous buffer
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_RED);
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            epd->op->writeByte(_me, 0xFF);
        }
        epd->op->delay(PU_DELAY);
    } else {
        epd->_using_partial_mode = false;  // remember
        Init_Full(_me, 0x01);
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_BW);
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            epd->op->writeByte(_me, 0xFF);
        }
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_RED);  // both buffers same for full b/w
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            epd->op->writeByte(_me, 0xFF);
        }
        Update_Full(_me);
        PowerOff(_me);
    }
} */

void _write_ram_part(const epd_g_t * epd, uint8_t em, uint16_t y, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t ys_m256, uint8_t ys_d256, uint8_t ye_m256, uint8_t ye_d256, bool runupdate_part, uint8_t * buf, uint16_t size) {
    TIMER_S
    // epd->op->writeCommand(epd, SSD168X_DATA_ENTRY_MODE_SETTING);
    // epd->op->writeByte(epd, 0x03);
    SetRamArea(epd, xs_d8, xe_d8, ys_m256, ys_d256, ye_m256, ye_d256);  // X-source area,Y-gate area
    SetRamPointer(epd, xs_d8, ys_m256, ys_d256);                          // set ram
    epd->op->waitWhileBusy(epd, __FUNCTION__, 100);                        // needed ?
    _write_ram_y_inc(epd, em, y, ye, xs_d8, xe_d8, WIDTH / 8, buf, size);
    if(runupdate_part)
        Update_Part(epd);
    TIMER_E
}

void Dis_Part(const void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    TIMER_S
    const epd_g_t* epd = _me;
    /// HEIGHT = 250, WIDTH = 128, LINE_BYTES = 16, BUFFER_SIZE = 4000
    const uint16_t xe = gx_uint16_min(WIDTH, x + w) - 1;   // x+w must be less than WIDTH
    const uint16_t ye = gx_uint16_min(HEIGHT, y + h) - 1;  // y+h must be less than HEIGHT
    const uint8_t xs_d8 = x / 8;                                // start x/8
    const uint8_t xe_d8 = xe / 8;                               // end x/8
    const uint8_t ys_d256 = y / 256;
    const uint8_t ys_m256 = y % 256;
    const uint8_t ye_d256 = ye / 256;
    const uint8_t ye_m256 = ye % 256;
    _write_ram_part(epd, SSD168X_WRITE_RAM_BW, y, ye, xs_d8, xe_d8, ys_m256, ys_d256, ye_m256, ye_d256, 1, epd->bw_buf, epd->bw_buf_size);
    //delay_ms(PU_DELAY);
    _write_ram_part(epd, SSD168X_WRITE_RAM_BW, y, ye, xs_d8, xe_d8, ys_m256, ys_d256, ye_m256, ye_d256, 0, epd->bw_buf, epd->bw_buf_size);
    //delay_ms(PU_DELAY);
    TIMER_E
}

void updateWindow(void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    TIMER_S
    epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    if (epd->_current_page != -1)
        return;
    // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    if (epd->rotation)
        epd->op->rotate(_me, &x, &y, &w, &h);
    if (x >= WIDTH)
        return;
    if (y >= HEIGHT)
        return;
    Init_Part(epd, 0x03);
    Dis_Part(epd, x, y, w, h);
    //PowerOff(epd);
    // xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void powerOff(void* _me) {
    PowerOff(_me);
}

// turns powerOff() and sets controller to deep sleep for minimum power use, ONLY if wakeable by RST (rst >= 0)
static void hibernate(void* _me) {
    TIMER_S
    epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    PowerOff(_me);
    if (CONFIG_DISPLAY_RST >= 0) {
        epd->op->writeCommand(epd, SSD168X_DEEP_SLEEP_MODE);  // deep sleep mode
        epd->op->writeByte(epd, 0x1);      // enter deep sleep
        epd->_hibernating = true;
    }
    // xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

void setRamDataEntryMode(const void* _me, uint8_t em) {
    LOGR
    const uint16_t xPixelsPar = WIDTH - 1;
    const uint16_t yPixelsPar = HEIGHT - 1;
    const uint8_t x_d8 = xPixelsPar / 8;
    const uint8_t y_d256 = yPixelsPar / 256;
    const uint8_t y_m256 = yPixelsPar % 256;
    em = gx_uint16_min(em, 0x03);
    const epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->op->writeCommand(_me, SSD168X_DATA_ENTRY_MODE_SETTING);
    epd->op->writeByte(_me, em);
    switch (em) {
        case 0x00:                                                     // x decrease, y decrease
            SetRamArea(_me, x_d8, 0x00, y_m256, y_d256, 0x00, 0x00);  // X-source area,Y-gate area
            SetRamPointer(_me, x_d8, y_m256, y_d256);                 // set ram
            break;
        case 0x01:                                                     // x increase, y decrease : as in demo code
            SetRamArea(_me, 0x00, x_d8, y_m256, y_d256, 0x00, 0x00);  // X-source area,Y-gate area
            SetRamPointer(_me, 0x00, y_m256, y_d256);                 // set ram
            break;
        case 0x02:                                                     // x decrease, y increase
            SetRamArea(_me, x_d8, 0x00, 0x00, 0x00, y_m256, y_d256);  // X-source area,Y-gate area
            SetRamPointer(_me, x_d8, 0x00, 0x00);                     // set ram
            break;
        case 0x03:                                                     // x increase, y increase : normal mode
            SetRamArea(_me, 0x00, x_d8, 0x00, 0x00, y_m256, y_d256);  // X-source area,Y-gate area
            SetRamPointer(_me, 0x00, 0x00, 0x00);                     // set ram
            break;
    }
    // xSemaphoreGiveRecursive(me->screen_lock);
}

static void SetRamArea(const void* _me, uint8_t Xstart, uint8_t Xend, uint8_t Ystart, uint8_t Ystart1, uint8_t Yend, uint8_t Yend1) {
    LOGR
    const epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->op->writeCommand(_me, SSD168X_SET_RAM_X_ADDRESS_START_END_POSITION);
    epd->op->writeByte(_me, Xstart+1);
    epd->op->writeByte(_me, Xend+1);
    epd->op->writeCommand(_me, SSD168X_SET_RAM_Y_ADDRESS_START_END_POSITION);
    epd->op->writeByte(_me, Ystart);
    epd->op->writeByte(_me, Ystart1);
    epd->op->writeByte(_me, Yend);
    epd->op->writeByte(_me, Yend1);
    // xSemaphoreGiveRecursive(me->screen_lock);
}

static void SetRamPointer(const void* _me, uint8_t addrX, uint8_t addrY, uint8_t addrY1) {
    LOGR
    const epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->op->writeCommand(_me, SSD168X_SET_RAM_X_ADDRESS_COUNTER);
    epd->op->writeByte(_me, addrX+1);
    epd->op->writeCommand(_me, SSD168X_SET_RAM_Y_ADDRESS_COUNTER);
    epd->op->writeByte(_me, addrY);
    epd->op->writeByte(_me, addrY1);
    // xSemaphoreGiveRecursive(me->screen_lock);
}

static void PowerOn(void* _me) {
    LOGR
    // TIMER_S
    epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    if (!epd->_power_is_on) {
    //     // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    //     epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
    //     epd->op->writeByte(epd, 0xf8);  // 0xc0);
    //     epd->op->writeCommand(epd, SSD168X_MASTER_ACTIVATION);
    //     epd->op->waitWhileBusy(epd, "PowerOn", power_on_time);
        epd->_power_is_on = true;
    //     // xSemaphoreGiveRecursive(me->screen_lock);
    }
    // TIMER_E
}

static void PowerOff(void* _me) {
    LOGR
    // TIMER_S
    epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    if (epd->_power_is_on) {
    //     // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    //     epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
    //     epd->op->writeByte(epd, 0x83);
    //     epd->op->writeCommand(epd, SSD168X_MASTER_ACTIVATION);
    //     epd->op->waitWhileBusy(epd, "PowerOff", power_off_time);
         epd->_power_is_on = false;
    //     epd->_using_partial_mode = false;
    //     // xSemaphoreGiveRecursive(me->screen_lock);
    }
    // TIMER_E
}

// hibernate
void powerDown(void* _me) {
    LOGR
    epd_g_t * epd = _me;
    epd->_using_partial_mode = false;
    epd->op->writeCommand(epd, SSD168X_DEEP_SLEEP_MODE);
    epd->op->writeByte(epd, 0x01);
    PowerOff(epd);
}

static void InitDisplay(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    // if (epd->_hibernating){
    //     epd->op->reset(epd, 10); // 10ms before and after
    // }
    epd->op->writeCommand(_me, SSD168X_SW_RESET);  // SWRESET
    //epd->op->waitWhileBusy(_me, __FUNCTION__, 1000);
    delay_ms(10);

    // epd->op->writeCommand(_me, SSD168X_DRIVER_OUTPUT_CONTROL);  // Driver output control
    // epd->op->writeByte(_me, (HEIGHT - 1) & 0xff);
    // epd->op->writeByte(_me, ((HEIGHT - 1) >> 8) & 0xff);
    // epd->op->writeByte(_me, 0x00);

    // epd->op->writeCommand(_me, SSD168X_BORDER_WAVEFORM_CONTROL);  // BorderWavefrom
    // epd->op->writeByte(_me, 0x05);

    // epd->op->writeCommand(_me, SSD168X_DISPLAY_UPDATE_CONTROL_1);  //  Display update control
    // epd->op->writeByte(_me, 0x00);
    // epd->op->writeByte(_me, 0x80);

    // epd->op->writeCommand(_me, SSD168X_TEMPERATURE_SENSOR_READ);  // Read built-in temperature sensor
    // epd->op->writeByte(_me, 0x80);

    setRamDataEntryMode(_me, em);
    // xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void Init_Full(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    InitDisplay(_me, em);
    PowerOn(_me);
    epd->_using_partial_mode = false;
    // xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void Init_Part(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    InitDisplay(_me, em);
    epd->op->writeCommand(_me, SSD1680_CMD_SET_LUT_REG);
    epd->op->writeDataArray(epd, &(lut_partial[0]), sizeof(lut_partial));
    epd->op->writeCommand(_me, SSD1680_CMD_SET_END_OPTION); // Option for LUT end, 0x22=Normal
    epd->op->writeByte(_me, 0x22);

    epd->op->writeCommand(_me, SSD1680_PARAM_DATA_ENTRY_MODE_3); // Gate Driving voltage, 0x17=20V
    epd->op->writeByte(_me, 0x17);
    epd->op->writeCommand(_me, SSD1680_CMD_SET_SRC_DRIVING_VOLTAGE); // Source Driving Voltage, 0x41=VSH1/VSH2=15V
    epd->op->writeDataArray(epd, SSD1680_PARAM_SRC_DRIVING_VOLTAGE, 3);
    // epd->op->writeByte(_me, SSD1680_PARAM_SRC_DRIVING_VOLTAGE[0]);
    // epd->op->writeByte(_me, SSD1680_PARAM_SRC_DRIVING_VOLTAGE[1]);
    // epd->op->writeByte(_me, SSD1680_PARAM_SRC_DRIVING_VOLTAGE[2]);
    epd->op->writeCommand(_me, SSD1680_CMD_SET_VCOM_REG); // VCOM register x34= -1.3V, x18=-0.6V
    epd->op->writeByte(_me, 0x34);

    epd->op->writeCommand(_me, SSD1680_CMD_SET_WRITE_REGISTER); // Write Register for Display option
    epd->op->writeByte(_me, 0x00);
    epd->op->writeByte(_me, 0x00);
    epd->op->writeByte(_me, 0x00);
    epd->op->writeByte(_me, 0x00);
    epd->op->writeByte(_me, 0x00);
    epd->op->writeByte(_me, 0x40); // F Display Mode for [WS35:32] ?
    epd->op->writeByte(_me, 0x00);
    epd->op->writeByte(_me, 0x00);
    epd->op->writeByte(_me, 0x00);
    epd->op->writeByte(_me, 0x00);

    epd->op->writeCommand(_me, SSD1680_CMD_SET_BORDER_WAVEFORM); // Border Wafeform control
    epd->op->writeByte(_me, SSD1680_PARAM_BORDER_WAVEFORM);
    epd->op->writeCommand(_me, SSD1680_CMD_SET_DISP_UPDATE_CTRL); // Display update control 2
    epd->op->writeByte(_me, 0xC0); // Enable Analog
    epd->op->writeCommand(_me, SSD1680_CMD_ACTIVE_DISP_UPDATE_SEQ); // Master Activation
    epd->op->waitWhileBusy(_me, __FUNCTION__, 10000);
    PowerOn(_me);
    epd->_using_partial_mode = true;
    // xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void Update_Full(const void* _me) {
    TIMER_S
    const epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    // if (useFastFullUpdate) {
    //     epd->op->writeCommand(epd, 0x1A);
    //     epd->op->writeByte(epd, 0x64);
    //     epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
    //     epd->op->writeByte(epd, 0xd4);
    // } else {
    //     epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
    //     epd->op->writeByte(epd, 0xf4);
    // }
    epd->op->writeCommand(epd, SSD1680_CMD_ACTIVE_DISP_UPDATE_SEQ);
    epd->op->waitWhileBusy(epd, __FUNCTION__, full_refresh_time);
    // xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void Update_Part(const void* _me) {
    TIMER_S
    const epd_g_t * epd = _me;
    // depg0213bn_t* me = epd->screen;
    // xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
    // gxepd 0xcc
    // lilygo 0xcf
    // ssd1680 0xff
    // another 0xc7
    // xx 0xc0
    epd->op->writeByte(epd, 0xcf); // 0xcf - enable clk signal enable analog, display width mode 2, disable analog, disable osc
    epd->op->writeCommand(epd, SSD168X_MASTER_ACTIVATION);
    epd->op->waitWhileBusy(epd, __FUNCTION__, partial_refresh_time);
    // xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static uint16_t _get_height() {
    return HEIGHT;
}

static uint16_t _get_width() {
    return WIDTH_VISIBLE;
}

static bool _has_fast_partial_update() {
    return hasFastPartialUpdate;
}

const epdg_screen_driver_t my_driver = SCREEN_DEPG0213BN;

void depg0213bn_deinit(void* _me) {
    LOGR
    if (!_me) return;
    depg0213bn_t* me = _me;
    //vSemaphoreDelete(me->screen_lock);
    epdg_screen_deinit(me->epd);
}

void depg0213bn_free(void* _me) {
    LOGR
    if (_me) {
        depg0213bn_t* me = _me;
        depg0213bn_deinit(me);
        free(me);
    }
}

const screen_op_t depg0213bn_ops = {
    .powerOff = powerOff,
    .powerDown = powerDown,
    .hibernate = hibernate,
    .update = update,
    .updateWindow = updateWindow,
    .get_height = _get_height,
    .get_width = _get_width,
    .hasFastPartialUpdate = _has_fast_partial_update,

    .deinit = depg0213bn_deinit,
    .free = depg0213bn_free,
};

depg0213bn_t* depg0213bn_init(depg0213bn_t* me, epd_g_t* epd, bool debug) {
    TIMER_S
    if (!epd) {
        me->epd = epdg_new(my_driver, debug);
        me->epd->init_mode = 2;
        epd = me->epd;
        epd->_diag_enabled = debug;
    } else {
        me->epd = epd;
    }

    me->spi_optimized = true;
    //me->screen_lock = xSemaphoreCreateRecursiveMutex();

    // class overrides
    epd->HEIGHT = epd->_height = HEIGHT;
    epd->WIDTH = epd->_width = WIDTH_VISIBLE;
    epd->RAW_WIDTH = WIDTH;
    epd->bw_buf = me->bw_buf;
    epd->bw_buf_size = sizeof(me->bw_buf);
    //epd->red_buf = me->red_buf;
    //epd->red_buf_size = sizeof(me->red_buf);
    epd->_page_height = HEIGHT/50;
    epd->_pages = (epd->HEIGHT / epd->_page_height) + ((epd->HEIGHT % epd->_page_height) > 0);
    epd->TAG = TAG;
    epd->op->setRotation(epd, 1);
    epd->screenop = &depg0213bn_ops;
    // method overrides
    TIMER_E
    return me;
}

depg0213bn_t* depg0213bn_new(epd_g_t* epd, bool debug) {
    LOGR
    depg0213bn_t* me = (depg0213bn_t*)malloc(sizeof(struct depg0213bn_s));
    return depg0213bn_init(me, epd, debug);
}

