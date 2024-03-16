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

#include "epdg.h"
#include "epd_driver_spi.h"
#include <logger_common.h>

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
static const uint16_t power_on_time = 100;         // ms, e.g. 95868us
static const uint16_t power_off_time = 250;        // ms, e.g. 140350us
static const uint16_t full_refresh_time = 4100;    // ms, e.g. 4011934us
static const uint16_t partial_refresh_time = 750;  // ms, e.g. 736721us

#define SSD168X_DRIVER_OUTPUT_CONTROL 0x01
#define SSD168X_BOOSTER_SOFT_START_CONTROL 0x0C
#define SSD168X_GATE_SCAN_START_POSITION 0x0F
#define SSD168X_DEEP_SLEEP_MODE 0x10
#define SSD168X_DATA_ENTRY_MODE_SETTING 0x11
#define SSD168X_SW_RESET 0x12
#define SSD168X_TEMPERATURE_SENSOR_READ 0x18
#define SSD168X_TEMPERATURE_SENSOR_CONTROL 0x1A
#define SSD168X_MASTER_ACTIVATION 0x20
#define SSD168X_DISPLAY_UPDATE_CONTROL_1 0x21
#define SSD168X_DISPLAY_UPDATE_CONTROL_2 0x22
#define SSD168X_WRITE_RAM_BW 0x24
#define SSD168X_WRITE_RAM_RED 0x26
#define SSD168X_WRITE_VCOM_REGISTER 0x2C
#define SSD168X_WRITE_LUT_REGISTER 0x32
#define SSD168X_SET_DUMMY_LINE_PERIOD 0x3A
#define SSD168X_SET_GATE_TIME 0x3B
#define SSD168X_BORDER_WAVEFORM_CONTROL 0x3C
#define SSD168X_SET_RAM_X_ADDRESS_START_END_POSITION 0x44
#define SSD168X_SET_RAM_Y_ADDRESS_START_END_POSITION 0x45
#define SSD168X_SET_RAM_X_ADDRESS_COUNTER 0x4E
#define SSD168X_SET_RAM_Y_ADDRESS_COUNTER 0x4F
#define SSD168X_TERMINATE_FRAME_READ_WRITE 0xFF

// #define DISABLE_DIAGNOSTIC_OUTPUT

// Partial Update Delay, may have an influence on degradation
#define GD_UPDATE_DELAY 100

#ifndef pgm_read_byte
#define pgm_read_byte(addr) (*(const unsigned char*)(addr))
#endif

static uint8_t lut_partial[] =
    {
        /// A                 B                C               D
        /* LUT 0 VS Group 0~11 */
        0x00, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        /* LUT 1 VS Group 0~11 */
        0x80, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        /* LUT 2 VS Group 0~11, keep the same as LUT0 for Black-White e-Paper */
        0x40, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        /* LUT 3 VS Group 0~11, keep the same as LUT1 for Black-White e-Paper */
        0x00, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        /* LUT 4 VS Group 0~11, seems useless, just keep all zero */
        0x00, 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        /// tpa   tpb  srab  tpc  tpd  srcd  rp
        /// Phase 0-11
        /* Only Group0~2 are used */
        /* Group 0  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x0A, 0x0, 0x00, 0x0, 0x0, 0x00, 0x2,
        /* Group 1  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x10, 0x0, 0x00, 0x0, 0x0, 0x00, 0x0,
        /* Group 2  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x10, 0x0, 0x00, 0x0, 0x0, 0x00, 0x0,
        /* Group 3  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x00, 0x0, 0x00, 0x0, 0x0, 0x00, 0x0,
        /* Group 4  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x00, 0x0, 0x00, 0x0, 0x0, 0x00, 0x0,
        /* Group 5  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x00, 0x0, 0x00, 0x0, 0x0, 0x00, 0x0,
        /* Group 6  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x00, 0x0, 0x00, 0x0, 0x0, 0x00, 0x0,
        /* Group 7  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x00, 0x0, 0x00, 0x0, 0x0, 0x00, 0x0,
        /* Group 8  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x00, 0x0, 0x00, 0x0, 0x0, 0x00, 0x0,
        /* Group 9  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x00, 0x0, 0x00, 0x0, 0x0, 0x00, 0x0,
        /* Group 10 TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x00, 0x0, 0x00, 0x0, 0x0, 0x00, 0x0,
        /* Group 11 TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */
        0x00, 0x0, 0x00, 0x0, 0x0, 0x00, 0x0,
        /// fr 0-5
        /* --- */
        0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
        /// xon bits 3 x 8
        0x0, 0x0, 0x0,
        /* --- Other register params, do not transfer together with data above */
        0x22, 0x17, 0x41, 0x0, 0x32, 0x20};

// static void fillScreen(void* _me, uint16_t color);
static void update(void* _me);
// static void drawBitmap(void* _me, const uint8_t* bitmap, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, int16_t mode);
// static void drawBitmap_b(void* _me, const uint8_t* bitmap, uint32_t size, int16_t mode);
// static void eraseDisplay(void* _me, bool using_partial_update);
static void updateWindow(void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
// static void _writeToWindow(void* _me, uint8_t command, uint16_t xs, uint16_t ys, uint16_t xd, uint16_t yd, uint16_t w, uint16_t h);
//  static void updateToWindow(void* _me, uint16_t xs, uint16_t ys, uint16_t xd, uint16_t yd, uint16_t w, uint16_t h, bool using_rotation);

static void _setRamDataEntryMode(const void* _me, uint8_t em);
static void _SetRamArea(const void* _me, uint8_t Xstart, uint8_t Xend, uint8_t Ystart, uint8_t Ystart1, uint8_t Yend, uint8_t Yend1);
static void _SetRamPointer(const void* _me, uint8_t addrX, uint8_t addrY, uint8_t addrY1);

static void _PowerOn(void* _me);
static void _PowerOff(void* _me);
static void powerOff(void* _me);

static void _InitDisplay(void* _me, uint8_t em);
static void _Init_Full(void* _me, uint8_t em);
static void _Init_Part(void* _me, uint8_t em);

static void _Update_Full(const void* _me);
static void _Update_Part(const void* _me);

/* static void _write_ram_y_dec(const epd_g_t * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8) {
    const uint8_t xLineBytes = WIDTH / 8;
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ye; y1 > ys; --y1) { // decrease
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            epd->op->writeByte(epd, (idx < epd->buffer_size) ? ~epd->buffer[idx] : 0xff);
        }
    }
} */

static void _write_ram_y_dec_opt(const epd_g_t * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8) {
    const uint8_t xLineBytes = WIDTH / 8;
    uint8_t x1buf[xLineBytes];
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ye; y1 > ys; --y1) { // decrease
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            x1buf[x1] = (idx < epd->buffer_size) ? ~epd->buffer[idx] : 0xFF;
        }
        epd->op->writeDataArray(epd, x1buf, sizeof(x1buf));
    }
}

static void _write_ram_y_inc(const epd_g_t * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8) {
    const uint8_t xLineBytes = WIDTH / 8;
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ys; y1 < ye; ++y1) { // decrease
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            epd->op->writeByte(epd, (idx < epd->buffer_size) ? ~epd->buffer[idx] : 0xff);
        }
    }
}

/* static void _write_ram_y_inc_opt(const epd_g_t * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8) {
    const uint8_t xLineBytes = WIDTH / 8;
    uint8_t x1buf[xLineBytes];
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ys; y1 < ye; ++y1) { // decrease
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            x1buf[x1] = (idx < epd->buffer_size) ? ~epd->buffer[idx] : 0xFF;
        }
        epd->op->writeDataArray(epd, x1buf, sizeof(x1buf));
    }
} */

static void update(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    if (epd->_current_page != -1)
        return;
    /// HEIGHT = 250, WIDTH = 128, LINE_BYTES = 16, BUFFER_SIZE = 4000
    const uint8_t xLineBytes = WIDTH / 8;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->_using_partial_mode = false;
    _Init_Full(epd, 0x01);
    _write_ram_y_dec_opt(epd, SSD168X_WRITE_RAM_BW, 0, HEIGHT, 0, xLineBytes);
    _write_ram_y_dec_opt(epd, SSD168X_WRITE_RAM_RED, 0, HEIGHT, 0, xLineBytes); // both buffers same for full b/w
    _Update_Full(epd);
    _PowerOff(epd);
    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

/* static void drawBitmap_b(void* _me, const uint8_t* bitmap, uint32_t size, int16_t mode) {
    epd_g_t* epd = _me;
    depg0213bn_t* me = me;
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
        _Init_Part(_me, ram_entry_mode);
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
        _Update_Part(_me);
        epd->op->delay(GD_UPDATE_DELAY);
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
        epd->op->delay(GD_UPDATE_DELAY);
    } else {
        epd->_using_partial_mode = false;  // remember
        _Init_Full(_me, ram_entry_mode);
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
        _Update_Full(_me);
    }
} */

/* static void eraseDisplay(void* _me, bool using_partial_update) {
    epd_g_t* epd = _me;
    if (epd->_current_page != -1)
        return;
    if (using_partial_update) {
        epd->_using_partial_mode = true;  // remember
        _Init_Part(_me, 0x01);
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_BW);
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            epd->op->writeByte(_me, 0xFF);
        }
        _Update_Part(_me);
        epd->op->delay(GD_UPDATE_DELAY);
        // update previous buffer
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_RED);
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            epd->op->writeByte(_me, 0xFF);
        }
        epd->op->delay(GD_UPDATE_DELAY);
    } else {
        epd->_using_partial_mode = false;  // remember
        _Init_Full(_me, 0x01);
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_BW);
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            epd->op->writeByte(_me, 0xFF);
        }
        epd->op->writeCommand(_me, SSD168X_WRITE_RAM_RED);  // both buffers same for full b/w
        for (uint32_t i = 0; i < GD_BUFFER_SIZE; i++) {
            epd->op->writeByte(_me, 0xFF);
        }
        _Update_Full(_me);
        _PowerOff(_me);
    }
} */

static void _write_ram_part(const epd_g_t * epd, uint8_t em, uint16_t y, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t ys_m256, uint8_t ys_d256, uint8_t ye_m256, uint8_t ye_d256) {
    epd->op->writeCommand(epd, SSD168X_DATA_ENTRY_MODE_SETTING);
    epd->op->writeByte(epd, 0x03);
    _SetRamArea(epd, xs_d8, xe_d8, ys_m256, ys_d256, ye_m256, ye_d256);  // X-source area,Y-gate area
    _SetRamPointer(epd, xs_d8, ys_m256, ys_d256);                          // set ram
    epd->op->waitWhileBusy(epd, __FUNCTION__, 100);                        // needed ?
    _write_ram_y_inc(epd, em, y, ye, xs_d8, xe_d8);
    _Update_Part(epd);
    epd->op->delay(GD_UPDATE_DELAY);
}

static void _Dis_Part(const void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
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
    _write_ram_part(epd, SSD168X_WRITE_RAM_BW, y, ye, xs_d8, xe_d8, ys_m256, ys_d256, ye_m256, ye_d256);
    _write_ram_part(epd, SSD168X_WRITE_RAM_RED, y, ye, xs_d8, xe_d8, ys_m256, ys_d256, ye_m256, ye_d256);
    TIMER_E
}

static void updateWindow(void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    TIMER_S
    epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    if (epd->_current_page != -1)
        return;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    if (epd->rotation)
        epd->op->rotate(_me, &x, &y, &w, &h);
    if (x >= WIDTH)
        return;
    if (y >= HEIGHT)
        return;
    _Init_Part(epd, 0x03);
    _Dis_Part(epd, x, y, w, h);
    //_PowerOff(epd);
    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void powerOff(void* _me) {
    _PowerOff(_me);
}

// turns powerOff() and sets controller to deep sleep for minimum power use, ONLY if wakeable by RST (rst >= 0)
static void hibernate(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    _PowerOff(_me);
    if (CONFIG_DISPLAY_RST >= 0) {
        epd->op->writeCommand(epd, SSD168X_DEEP_SLEEP_MODE);  // deep sleep mode
        epd->op->writeByte(epd, 0x1);      // enter deep sleep
        epd->_hibernating = true;
    }
    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void _setRamDataEntryMode(const void* _me, uint8_t em) {
    const uint16_t xPixelsPar = WIDTH - 1;
    const uint16_t yPixelsPar = HEIGHT - 1;
    const uint8_t x_d8 = xPixelsPar / 8;
    const uint8_t y_d256 = yPixelsPar / 256;
    const uint8_t y_m256 = yPixelsPar % 256;
    em = gx_uint16_min(em, 0x03);
    const epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->op->writeCommand(_me, SSD168X_DATA_ENTRY_MODE_SETTING);
    epd->op->writeByte(_me, em);
    switch (em) {
        case 0x00:                                                                                   // x decrease, y decrease
            _SetRamArea(_me, x_d8, 0x00, y_m256, y_d256, 0x00, 0x00);  // X-source area,Y-gate area
            _SetRamPointer(_me, x_d8, y_m256, y_d256);                 // set ram
            break;
        case 0x01:                                                                                   // x increase, y decrease : as in demo code
            _SetRamArea(_me, 0x00, x_d8, y_m256, y_d256, 0x00, 0x00);  // X-source area,Y-gate area
            _SetRamPointer(_me, 0x00, y_m256, y_d256);                           // set ram
            break;
        case 0x02:                                                                                   // x decrease, y increase
            _SetRamArea(_me, x_d8, 0x00, 0x00, 0x00, y_m256, y_d256);  // X-source area,Y-gate area
            _SetRamPointer(_me, x_d8, 0x00, 0x00);                                         // set ram
            break;
        case 0x03:                                                                                   // x increase, y increase : normal mode
            _SetRamArea(_me, 0x00, x_d8, 0x00, 0x00, y_m256, y_d256);  // X-source area,Y-gate area
            _SetRamPointer(_me, 0x00, 0x00, 0x00);                                                   // set ram
            break;
    }
    xSemaphoreGiveRecursive(me->screen_lock);
}

static void _SetRamArea(const void* _me, uint8_t Xstart, uint8_t Xend, uint8_t Ystart, uint8_t Ystart1, uint8_t Yend, uint8_t Yend1) {
    const epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->op->writeCommand(_me, SSD168X_SET_RAM_X_ADDRESS_START_END_POSITION);
    epd->op->writeByte(_me, Xstart);
    epd->op->writeByte(_me, Xend);
    epd->op->writeCommand(_me, SSD168X_SET_RAM_Y_ADDRESS_START_END_POSITION);
    epd->op->writeByte(_me, Ystart);
    epd->op->writeByte(_me, Ystart1);
    epd->op->writeByte(_me, Yend);
    epd->op->writeByte(_me, Yend1);
    xSemaphoreGiveRecursive(me->screen_lock);
}

static void _SetRamPointer(const void* _me, uint8_t addrX, uint8_t addrY, uint8_t addrY1) {
    const epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->op->writeCommand(_me, SSD168X_SET_RAM_X_ADDRESS_COUNTER);
    epd->op->writeByte(_me, addrX);
    epd->op->writeCommand(_me, SSD168X_SET_RAM_Y_ADDRESS_COUNTER);
    epd->op->writeByte(_me, addrY);
    epd->op->writeByte(_me, addrY1);
    xSemaphoreGiveRecursive(me->screen_lock);
}

static void _PowerOn(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    if (!epd->_power_is_on) {
        xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
        epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
        epd->op->writeByte(epd, 0xf8);  // 0xc0);
        epd->op->writeCommand(epd, SSD168X_MASTER_ACTIVATION);
        epd->op->waitWhileBusy(epd, "_PowerOn", power_on_time);
        epd->_power_is_on = true;
        xSemaphoreGiveRecursive(me->screen_lock);
    }
    TIMER_E
}

static void _PowerOff(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    if (epd->_power_is_on) {
        xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
        epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
        epd->op->writeByte(epd, 0x83);
        epd->op->writeCommand(epd, SSD168X_MASTER_ACTIVATION);
        epd->op->waitWhileBusy(epd, "_PowerOff", power_off_time);
        epd->_power_is_on = false;
        epd->_using_partial_mode = false;
        xSemaphoreGiveRecursive(me->screen_lock);
    }
    TIMER_E
}

static void _InitDisplay(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    if (epd->_hibernating){
        epd->op->reset(epd, 10); // 10ms before and after
    }
    epd->op->writeCommand(_me, SSD168X_SW_RESET);  // SWRESET
    epd->op->waitWhileBusy(_me, __FUNCTION__, 10);

    epd->op->writeCommand(_me, SSD168X_DRIVER_OUTPUT_CONTROL);  // Driver output control
    epd->op->writeByte(_me, (HEIGHT - 1) & 0xff);
    epd->op->writeByte(_me, ((HEIGHT - 1) >> 8) & 0xff);
    epd->op->writeByte(_me, 0x00);

    epd->op->writeCommand(_me, SSD168X_BORDER_WAVEFORM_CONTROL);  // BorderWavefrom
    epd->op->writeByte(_me, 0x05);

    epd->op->writeCommand(_me, SSD168X_DISPLAY_UPDATE_CONTROL_1);  //  Display update control
    epd->op->writeByte(_me, 0x00);
    epd->op->writeByte(_me, 0x80);

    epd->op->writeCommand(_me, SSD168X_TEMPERATURE_SENSOR_READ);  // Read built-in temperature sensor
    epd->op->writeByte(_me, 0x80);

    _setRamDataEntryMode(_me, em);
    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void _Init_Full(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    _InitDisplay(_me, em);
    _PowerOn(_me);
    epd->_using_partial_mode = false;
    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void _Init_Part(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    _InitDisplay(_me, em);
    epd->op->writeCommand(_me, SSD168X_WRITE_LUT_REGISTER);
    epd->op->writeDataArray(epd, &(lut_partial[0]), sizeof(lut_partial));
    _PowerOn(_me);
    epd->_using_partial_mode = true;
    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void _Update_Full(const void* _me) {
    TIMER_S
    const epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    if (useFastFullUpdate) {
        epd->op->writeCommand(epd, 0x1A);
        epd->op->writeByte(epd, 0x64);
        epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
        epd->op->writeByte(epd, 0xd4);
    } else {
        epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
        epd->op->writeByte(epd, 0xf4);
    }
    epd->op->writeCommand(epd, SSD168X_MASTER_ACTIVATION);
    epd->op->waitWhileBusy(epd, __FUNCTION__, full_refresh_time);
    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void _Update_Part(const void* _me) {
    TIMER_S
    const epd_g_t* epd = _me;
    depg0213bn_t * me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
    epd->op->writeByte(epd, 0xFF);
    epd->op->writeCommand(epd, SSD168X_MASTER_ACTIVATION);
    epd->op->waitWhileBusy(epd, __FUNCTION__, partial_refresh_time);
    xSemaphoreGiveRecursive(me->screen_lock);
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

const epdg_screen_driver_t screen_driver = SCREEN_DEPG0213BN;

void depg0213bn_deinit(void* _me) {
    LOGR
    if (!_me) return;
    depg0213bn_t* me = _me;
    vSemaphoreDelete(me->screen_lock);
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
        me->epd = epdg_new(screen_driver, debug);
        me->epd->init_mode = 2;
        epd = me->epd;
        epd->_diag_enabled = debug;
    } else {
        me->epd = epd;
    }

    me->spi_optimized = true;
    me->screen_lock = xSemaphoreCreateRecursiveMutex();

    // class overrides
    epd->HEIGHT = epd->_height = HEIGHT;
    epd->WIDTH = epd->_width = WIDTH;
    epd->buffer = me->_buffer;
    epd->buffer_size = sizeof(me->_buffer);
    epd->_page_height = HEIGHT/50;
    epd->_pages = (epd->HEIGHT / epd->_page_height) + ((epd->HEIGHT % epd->_page_height) > 0);
    epd->TAG = TAG;
    epd->op->setRotation(epd, 1);
    epd->screenop = &depg0213bn_ops;
    epd->screen = me;
    // method overrides
    TIMER_E
    return me;
}

depg0213bn_t* depg0213bn_new(epd_g_t* epd, bool debug) {
    LOGR
        depg0213bn_t* me = (depg0213bn_t*)malloc(sizeof(struct depg0213bn_s));
    return depg0213bn_init(me, epd, debug);
}

