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
TIMER_INIT

static const uint16_t WIDTH = 128;
static const uint16_t WIDTH_VISIBLE = 122;
static const uint16_t HEIGHT = 250;
static bool hasColor = false;
static bool hasPartialUpdate = true;
static const bool hasFastPartialUpdate = true;
static const bool useFastFullUpdate = true;        // set false for extended (low) temperature range
static const uint16_t power_on_time = 80;         // ms, e.g. 95868us
static const uint16_t power_off_time = 80;        // ms, e.g. 140350us
static const uint16_t full_refresh_time = 12000;    // ms, e.g. 4011934us
static const uint16_t partial_refresh_time = 3000;  // ms, e.g. 736721us

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

static ram_params_t p = {0};

esp_err_t set_ram_params(ram_params_t * p, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t em) {
    p->x = min(WIDTH, x);
    p->y = min(HEIGHT, y);
    const uint16_t xe = p->x + w, ye = p->y + h;
    p->xe = min(WIDTH, xe) - 1;   // x+w must be less than WIDTH
    p->ye = min(HEIGHT, ye) - 1;  // y+h must be less than HEIGHT
    p->xs_d8 = x / 8;             // startx/8 means (x >> 3)
    p->xe_d8 = p->xe / 8;         // endx/8 means (xe >> 3)
    p->ys_d256 = y / 256;         // starty/256 means (y >> 8)
    p->ys_m256 = y % 256;         // starty%256 means (y & 0xFF)
    p->ye_d256 = p->ye / 256;     // endy/256 means (ye >> 8)
    p->ye_m256 = p->ye % 256;     // endy%256 means (ye & 0xFF)
    p->ram_mode = min(em, 0x03);
    return ESP_OK;
}

void _write_ram_part(const epd_g_t * epd, struct ram_params_s * p, uint8_t em, bool runupdate_part, uint8_t * buf, size_t buf_size) {
    TIMER_S
    set_ram(epd, p);                          // set ram
    //epd->op->waitWhileBusy(epd, __FUNCTION__, 100);                        // needed ?
    write_ram(epd, p, em, buf, buf_size);
    if(runupdate_part)
        Update_Part(epd);
    TIMER_E
}

void Dis_Part(const void* _me, struct ram_params_s * p) {
    TIMER_S
    const epd_g_t* epd = _me;
    /// HEIGHT = 250, WIDTH = 128, LINE_BYTES = 16, BUFFER_SIZE = 4000
    _write_ram_part(epd, p, SSD168X_WRITE_RAM_BW, 1, epd->bw_buf, epd->bw_buf_size);
    delay_ms(PU_DELAY);
    //write_ram(epd, p, SSD168X_WRITE_RAM_BW, epd->bw_buf, epd->bw_buf_size);
    _write_ram_part(epd, p, SSD168X_WRITE_RAM_BW, 0, epd->bw_buf, epd->bw_buf_size);
    delay_ms(PU_DELAY);
    //write_ram(epd, p, SSD168X_WRITE_RAM_RED, 0, 0);
    TIMER_E
}

void updateWindow(void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    TIMER_S
    epd_g_t * epd = _me;
    if(epd->_initial_refresh){
        update(_me);
        goto done;
    }
    if (epd->_current_page != -1)
        goto done;
    if (epd->rotation)
        epd->op->rotate(_me, &x, &y, &w, &h);
    if (x >= WIDTH)
        goto done;
    if (y >= HEIGHT)
        goto done;
    set_ram_params(&p, x, y, w, h, 0x03);
    Init_Part(epd, &p);
    Dis_Part(epd, &p);
    powerDown(epd);
    done:
    TIMER_E
}

void update(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    if (epd->_current_page != -1)
        goto done;
    //epd->_using_partial_mode = false;
    set_ram_params(&p, 0, 0, WIDTH, HEIGHT, 0x03);
    Init_Full(epd, &p);
    if(epd->_initial_refresh){
        // memset(epd->bw_buf, 0, epd->bw_buf_size);
        // memset(epd->red_buf, 0, epd->red_buf_size);
        epd->_initial_refresh = false;
    }
    set_ram(epd, &p); // set ram
    write_ram(epd, &p, SSD168X_WRITE_RAM_BW, epd->bw_buf, epd->bw_buf_size);
    write_ram(epd, &p, SSD168X_WRITE_RAM_RED, 0, 0); // fill red buffer with 0
    //_write_ram_buf(epd, SSD168X_WRITE_RAM_BW, epd->bw_buf, epd->bw_buf_size);
    //write_ram(epd, &p, SSD168X_WRITE_RAM_RED, epd->bw_buf, epd->bw_buf_size);
    Update_Full(epd);
    powerDown(epd);
    done:
    TIMER_E
}

void set_area(const void* _me, const ram_params_t * p) {
    switch (p->ram_mode) {
        case 0x00:                                                     // x decrease, y decrease
            setRamArea(_me, p->xe_d8, 0x00, p->ye_m256, p->ye_d256, 0x00, 0x00);  // X-source area,Y-gate area
            break;
        case 0x01:                                                     // x increase, y decrease : as in demo code
            setRamArea(_me, 0x00, p->xe_d8, p->ye_m256, p->ye_d256, 0x00, 0x00);  // X-source area,Y-gate area
            break;
        case 0x02:                                                     // x decrease, y increase
            setRamArea(_me, p->xe_d8, 0x00, 0x00, 0x00, p->ye_m256, p->ye_d256);  // X-source area,Y-gate area
            break;
        case 0x03:                                                     // x increase, y increase : normal mode
            setRamArea(_me, 0x00, p->xe_d8, 0x00, 0x00, p->ye_m256, p->ye_d256);  // X-source area,Y-gate area
            break;
    }
}

void set_ram(const void* _me, const ram_params_t * p) {
    switch (p->ram_mode) {
        case 0x00:                                                     // x decrease, y decrease
            setRamPointer(_me, p->xe_d8, p->ye_m256, p->ye_d256);                 // set ram
            break;
        case 0x01:                                                     // x increase, y decrease : as in demo code
            setRamPointer(_me, 0x00, p->ye_m256, p->ye_d256);                 // set ram
            break;
        case 0x02:                                                     // x decrease, y increase
            setRamPointer(_me, p->xe_d8, 0x00, 0x00);                     // set ram
            break;
        case 0x03:                                                     // x increase, y increase : normal mode
            setRamPointer(_me, 0x00, 0x00, 0x00);                     // set ram
            break;
    }
}

void setRamArea(const struct epd_g_s * epd, uint8_t Xstart, uint8_t Xend, uint8_t Ystart, uint8_t Ystart1, uint8_t Yend, uint8_t Yend1) {
    LOGR
    epd->op->writeCommand(epd, SSD168X_SET_RAM_X_ADDRESS_START_END_POSITION);
    epd->op->writeByte(epd, Xstart+1);
    epd->op->writeByte(epd, Xend+1);
    epd->op->writeCommand(epd, SSD168X_SET_RAM_Y_ADDRESS_START_END_POSITION);
    epd->op->writeByte(epd, Ystart);
    epd->op->writeByte(epd, Ystart1);
    epd->op->writeByte(epd, Yend);
    epd->op->writeByte(epd, Yend1);
}

void setRamPointer(const struct epd_g_s * epd, uint8_t addrX, uint8_t addrY, uint8_t addrY1) {
    LOGR
    epd->op->writeCommand(epd, SSD168X_SET_RAM_X_ADDRESS_COUNTER);
    epd->op->writeByte(epd, addrX+1);
    epd->op->writeCommand(epd, SSD168X_SET_RAM_Y_ADDRESS_COUNTER);
    epd->op->writeByte(epd, addrY);
    epd->op->writeByte(epd, addrY1);
}

void setRamDataEntryMode(const void* _me, uint8_t em) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(_me, SSD168X_DATA_ENTRY_MODE_SETTING);
    epd->op->writeByte(_me, em);
}

static void setDisplayUpdate22(const void * _me, uint8_t em) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(_me, SSD1680_CMD_SET_DISP_UPDATE_CTRL);  //  Display update control
    epd->op->writeByte(_me, em);
}

static void setDisplayUpdate21(const void * _me) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(_me, SSD168X_DISPLAY_UPDATE_CONTROL_1);  //  Display update control
    epd->op->writeByte(_me, 0x00);
    epd->op->writeByte(_me, 0x80);
}

static void setDisplayOn(const void * _me, uint8_t em, uint16_t timeout) {
    TIMER_S
    const epd_g_t * epd = _me;
    if(em > 0) {
        setDisplayUpdate22(_me, em);
    }
    epd->op->writeCommand(_me, SSD1680_CMD_ACTIVE_DISP_UPDATE_SEQ); // Master Activation
    epd->op->waitWhileBusy(_me, __FUNCTION__, timeout);
    TIMER_E
}

static void PowerOn(void* _me) {
    LOGR
    epd_g_t * epd = _me;
    if (!epd->_power_is_on) {
        epd->_power_is_on = true;
    }
}

static void PowerOff(void* _me) {
    LOGR
    epd_g_t * epd = _me;
    if (epd->_power_is_on) {
         epd->_power_is_on = false;
    }
    //epd->_using_partial_mode = false;
}

static void powerOff(void* _me) {
    PowerOff(_me);
}

void setDeepSleep(const void * _me, uint8_t em) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(epd, SSD168X_DEEP_SLEEP_MODE);  // deep sleep mode
    epd->op->writeByte(epd, 0x01);      // enter deep sleep
}

// hibernate
void powerDown(void* _me) {
    LOGR
    // 6. Power Off
    hibernate(_me, 0x11); // 0x00 = normal, 0x01 = mode1, 0x11 = mode2
    // epd_g_t * epd = _me;
    // epd->_using_partial_mode = false;
    // PowerOff(epd);
    // setDeepSleep(_me);
}

// turns powerOff() and sets controller to deep sleep for minimum power use, ONLY if wakeable by RST (rst >= 0)
void hibernate(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t * epd = _me;
    if (CONFIG_DISPLAY_RST >= 0) {
        setDeepSleep(_me, em);
        epd->_hibernating = true;
    }
    PowerOff(_me);
    TIMER_E
}

static void setGateDrivingVoltage(const void *_me, uint8_t em) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(_me, SSD1680_PARAM_DATA_ENTRY_MODE_3); // Gate Driving voltage, 0x17=20V
    epd->op->writeByte(_me, em); // 0x17);
}

static void setSourceDrivingVoltage(const void * _me) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(_me, SSD1680_CMD_SET_SRC_DRIVING_VOLTAGE); // Source Driving Voltage, 0x41=VSH1/VSH2=15V
    epd->op->writeDataArray(epd, SSD1680_PARAM_SRC_DRIVING_VOLTAGE, 3);
}

static void setVcomRegister(const void * _me) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(_me, SSD1680_CMD_SET_VCOM_REG); // VCOM register x34= -1.3V, x18=-0.6V
    epd->op->writeByte(_me, 0x34);
}

static void setDriverOutput(const void* _me) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(_me, SSD168X_DRIVER_OUTPUT_CONTROL);  // Driver output control
    epd->op->writeByte(_me, (HEIGHT - 1) & 0xff);
    epd->op->writeByte(_me, ((HEIGHT - 1) >> 8) & 0xff);
    epd->op->writeByte(_me, 0x00);
}

static void setBorderWaveform(const void* _me, uint8_t em) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(_me, SSD168X_BORDER_WAVEFORM_CONTROL);  // BorderWavefrom
    epd->op->writeByte(_me, em); // 0x05);
}

static void readTempSensor(const void * _me) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(_me, SSD168X_TEMPERATURE_SENSOR_READ);  // Read built-in temperature sensor
    epd->op->writeByte(_me, 0x80); // 0x64 fast full update?
}

static void setWriteRegister(const void * _me) {
    LOGR
    const epd_g_t * epd = _me;
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
}

static void setLut(const void * _me, const uint8_t * lut, size_t lut_size) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(_me, SSD1680_CMD_SET_LUT_REG);
    epd->op->writeDataArray(epd, lut, lut_size);
    epd->op->writeCommand(_me, SSD1680_CMD_SET_END_OPTION); // Option for LUT end, 0x22=Normal
    epd->op->writeByte(_me, 0x22);
}

static void setSwReset(const void * _me) {
    LOGR
    const epd_g_t * epd = _me;
    epd->op->writeCommand(_me, SSD168X_SW_RESET);  // SWRESET 0x12
    //epd->op->waitWhileBusy(_me, __FUNCTION__, 1000);
    delay_ms(10);
}

// Stages implemented according to doc:
static void InitDisplay(void* _me, struct ram_params_s * p) {
    TIMER_S
    epd_g_t * epd = _me;

    // 2. Set Initial Configuration
    if (epd->_hibernating){
         epd->op->reset(epd, 10); // 10ms after
    }
    setSwReset(_me);

    // 3: Send Initialization code
    setDriverOutput(_me); // stage 2 by spec
    setRamDataEntryMode(_me, p->ram_mode);
    set_area(epd, p);  // X-source area,Y-gate area
    //setRamArea(_me, em);
    //setBorderWaveform(_me, SSD1680_PARAM_BORDER_WAVEFORM); // 0x80 == follow vcom, 0x05 == a2 follow lut, a0-1 lut1
    
    // setDisplayControl(_me);
   TIMER_E
}

static void Init_Full(void* _me, struct ram_params_s * p) {
    TIMER_S
    epd_g_t * epd = _me;

    // 2-3 here
    InitDisplay(_me, p);
    setBorderWaveform(_me, 0x05); // 0x80 == follow vcom, 0x05 == a2 follow lut, a0-1 lut1

    // 4. Load Waveform LUT -- > full init uses defaults.
    readTempSensor(_me);
    setDisplayOn(_me, 0xf7, 10000U);
    PowerOn(_me);

    // 5. Write Image and Drive Display Panel
    //set_ram(_me, p);
    
    epd->_using_partial_mode = false;
    TIMER_E
}

static void Init_Part(void* _me, struct ram_params_s * p) {
    TIMER_S
    epd_g_t * epd = _me;
    
    // 2-3 here
    InitDisplay(_me, p);
    setBorderWaveform(_me, 0xc0); // 0x80 == follow vcom, 0x05 == a2 follow lut, a0-1 lut1

    // 4. Load Waveform LUT
    readTempSensor(_me);
    setLut(_me, &(lut_partial[0]), sizeof(lut_partial));
    setGateDrivingVoltage(_me, 0x17);
    setSourceDrivingVoltage(_me);
    setVcomRegister(_me);
    setWriteRegister(_me);
    setDisplayOn(_me, 0xc0, 10000U);
    PowerOn(_me);

    // 5. Write Image and Drive Display Panel
    //set_ram(_me, p);
    
    epd->_using_partial_mode = true;
    TIMER_E
}

static void Update_Full(const void* _me) {
    TIMER_S
    const epd_g_t * epd = _me;
    // if (useFastFullUpdate) {
    //     epd->op->writeCommand(epd, SSD168X_TEMPERATURE_SENSOR_CONTROL);
    //     epd->op->writeByte(epd, 0x64);
    // }
    epd->op->writeCommand(epd, SSD168X_BOOSTER_SOFT_START_CONTROL);
    epd->op->writeDataArray(epd, (const uint8_t[]){0x8b, 0x9c, 0x96, 0x0f}, 4);
    //setDisplayOn(_me, useFastFullUpdate ? 0xd4 : 0xf4, full_refresh_time);
    setDisplayOn(_me, 0xff, full_refresh_time);
    TIMER_E
}

static void Update_Part(const void* _me) {
    TIMER_S
    const epd_g_t * epd = _me;
    epd->op->writeCommand(epd, SSD168X_BOOSTER_SOFT_START_CONTROL);
    epd->op->writeDataArray(epd, (const uint8_t[]){0x8b, 0x9c, 0x96, 0x0f}, 4);
    // gxepd 0xcc
    // lilygo 0xcf
    // ssd1680 0xff
    // another 0xc7
    // xx 0xc0
    setDisplayOn(_me, 0xcf, partial_refresh_time);
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
    .powerDown = powerDown,
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

