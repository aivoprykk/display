#include "gdey0213b74.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_timer.h"

#include "epdg.h"
#include "epd_driver_spi.h"

// #define DISABLE_DIAGNOSTIC_OUTPUT

/*
 The EPD needs a bunch of command/data values to be initialized. They are send using the IO class
*/
#define N GDEY0213B74

static const char* TAG = QUOTE_CMD(N);

static const uint16_t WIDTH = 128;
static const uint16_t WIDTH_VISIBLE = 122;
static const uint16_t HEIGHT = 250;
static bool hasColor = false;
static bool hasPartialUpdate = true;
static const bool hasFastPartialUpdate = true;
static const uint16_t power_on_time = 100;         // ms, e.g. 95868us
static const uint16_t power_off_time = 250;        // ms, e.g. 140350us
static uint16_t full_refresh_time = 4100;    // ms, e.g. 4011934us
static uint16_t partial_refresh_time = 750;  // ms, e.g. 736721us

#define GDEY0213B74_PU_DELAY 300

// Grays Waveform
static const epd_lut_159 lut_4_grays = {
    0x32,
    {0x40, 0x48, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x8, 0x48, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x2, 0x48, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x20, 0x48, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0xA, 0x19, 0x0, 0x3, 0x8, 0x0, 0x0,
     0x14, 0x1, 0x0, 0x14, 0x1, 0x0, 0x3,
     0xA, 0x3, 0x0, 0x8, 0x19, 0x0, 0x0,
     0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0, 0x0, 0x0,
     0x22, 0x17, 0x41, 0x0, 0x32, 0x1C},
    159};

static void fillScreen(void* _me, uint16_t color);
static void update(void* _me);
static void updateWindow(void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
static void _sleep(void* _me);
static void _rotate(void* _me, uint16_t* x, uint16_t* y, uint16_t* w, uint16_t* h);
static void drawPixel(void* _me, int16_t x, int16_t y, uint16_t color);
static void _InitDisplay(void* _me, uint8_t em);
static void _wakeUp(void* _me, uint8_t em);
static void _Init_Full(void* _me, uint8_t em);
static void _Init_Part(void* _me, uint8_t em);
static void _setRamDataEntryMode(void* _me, uint8_t em);
static void _SetRamArea(void* _me, uint8_t Xstart, uint8_t Xend, uint8_t Ystart, uint8_t Ystart1, uint8_t Yend, uint8_t Yend1);
static void _SetRamPointer(void* _me, uint8_t addrX, uint8_t addrY, uint8_t addrY1);
static void _PowerOn(void* _me);
static void _PowerOff(void* _me);

static void update(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    if (epd->_current_page != -1)
        return;
    
    gdey0213b74_t* me = epd->screen;

    epd->_using_partial_mode = false;
    
    // For v1.0 only monochrome supported
    uint8_t xLineBytes = GDEY0213B74_WIDTH / 8;
    uint8_t x1buf[xLineBytes];
    uint32_t i = 0;

    if (me->_mono_mode) {
        _InitDisplay(_me, 0x03);
        epd->op->writeCommand(epd, 0x24);  // write RAM1 for black(0)/white (1)
        for (uint16_t y = GDEY0213B74_HEIGHT; y > 0; y--) {
            for (uint16_t x = 0; x < xLineBytes; x++) {
                uint16_t idx = y * xLineBytes + x;
                uint8_t data = i < sizeof(me->_buffer) ? me->_buffer[idx] : 0x00;
                x1buf[x] = data;  // ~ is invert

                if (x == xLineBytes - 1) {  // Flush the X line buffer to SPI
                    epd->IO->op->data_v(epd->IO, x1buf, sizeof(x1buf));
                }
                ++i;
            }
        }
    } else {
        _wakeUp(_me, 0x03);

        // 4 grays mode GDEY0213B74
        printf("\n4 gray MODE. sends LUT 159 bytes\n");
        epd->op->writeCommand(epd, 0x24);  // write RAM1 for black(0)/white (1)
        for (uint16_t y = GDEY0213B74_HEIGHT; y > 0; y--) {
            for (uint16_t x = 0; x < xLineBytes; x++) {
                uint16_t idx = y * xLineBytes + x;
                uint8_t data = i < sizeof(me->_buffer1) ? me->_buffer1[idx] : 0x00;
                x1buf[x] = data;  // ~ is invert

                if (x == xLineBytes - 1) {  // Flush the X line buffer to SPI
                    epd->IO->op->data_v(epd->IO, x1buf, sizeof(x1buf));
                }
                ++i;
            }
        }

        i = 0;
        epd->op->writeCommand(epd, 0x26);  // RAM2 buffer: SPI2
        for (uint16_t y = GDEY0213B74_HEIGHT; y > 0; y--) {
            for (uint16_t x = 0; x < xLineBytes; x++) {
                uint16_t idx = y * xLineBytes + x;
                uint8_t data = i < sizeof(me->_buffer2) ? me->_buffer2[idx] : 0x00;
                x1buf[x] = data;  // ~ is invert

                if (x == xLineBytes - 1) {  // Flush the X line buffer to SPI
                    epd->IO->op->data_v(epd->IO, x1buf, sizeof(x1buf));
                }
                ++i;
            }
        }
    }
    
    epd->op->writeCommand(epd, 0x22);  // Display Update Control
    uint8_t twenty_two = (me->_mono_mode) ? 0xF7 : 0xC4;
    epd->op->writeByte(epd, twenty_two);  // When 4 gray 0xC7 : Same as gdeh042Z96
    epd->op->writeCommand(epd, 0x20);     // Update sequence
    epd->op->waitWhileBusy(_me, "update full", 100);
    TIMER_E
}

static void fillScreen(void* _me, uint16_t color) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0213b74_t* me = epd->screen;
    assert(me);
    if (me->_mono_mode) {
        uint8_t data = (color == EPD_WHITE) ? 0xFF : 0x00;
        for (uint16_t x = 0; x < sizeof(me->_buffer); x++) {
            me->_buffer[x] = data;
        }
        if (epd->_diag_enabled)
            printf("fillScreen(%d) _buffer len:%d\n", data, sizeof(me->_buffer));
    } else {
        // This is to make faster black & white
        if (color == 255 || color == 0) {
            for (uint32_t i = 0; i < GDEY0213B74_BUFFER_SIZE; i++) {
                me->_buffer1[i] = (color == 0xFF) ? 0x00 : 0xFF;
                me->_buffer2[i] = (color == 0xFF) ? 0x00 : 0xFF;
            }
            return;
        }

        for (uint32_t y = 0; y < GDEY0213B74_HEIGHT; y++) {
            for (uint32_t x = 0; x < GDEY0213B74_WIDTH; x++) {
                drawPixel(_me, x, y, color);
                if (x % 8 == 0) {
                    delay_ms(2);
                }
            }
        }
    }
    TIMER_E
}

static void updateWindow(void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0213b74_t* me = epd->screen;
    // ESP_LOGE("PARTIAL", "update is not implemented x:%d y:%d\n", (int)x, (int)y);
    if (!me->epd->_using_partial_mode) {
        me->epd->_using_partial_mode = true;
        _InitDisplay(_me, 0x03);
    }
    if (epd->rotation)
        _rotate(epd, &x, &y, &w, &h);
    if (x >= GDEY0213B74_WIDTH)
        return;
    if (y >= GDEY0213B74_HEIGHT)
        return;
    uint16_t xe = gx_uint16_min(GDEY0213B74_WIDTH, x + w) - 1;
    uint16_t ye = gx_uint16_min(GDEY0213B74_HEIGHT, y + h) - 1;
    uint16_t xs_d8 = x / 8;
    uint16_t xe_d8 = xe / 8;

    //_Init_Part(epd, 0x03);
    epd->op->writeCommand(epd, 0x12);  // SWRESET
    epd->op->waitWhileBusy(epd, "SWRESET", 100);

    _setRamDataEntryMode(epd, 0x03);

    _SetRamArea(epd, xs_d8, xe_d8, y % 256, y / 256, ye % 256, ye / 256);  // X-source area,Y-gate area
    _SetRamPointer(epd, xs_d8, y % 256, y / 256);                          // set ram
    epd->op->waitWhileBusy(epd, "updateWindow I", 100);

    epd->op->writeCommand(epd, 0x22);
    epd->op->writeByte(epd, 0xFF);

    epd->op->writeCommand(epd, 0x24);  // BW RAM
    for (int16_t y1 = y; y1 <= ye; y1++) {
        for (int16_t x1 = xs_d8; x1 <= xe_d8; x1++) {
            uint16_t idx = y1 * (GDEY0213B74_WIDTH / 8) + x1;
            uint8_t data = (idx < sizeof(me->_buffer)) ? me->_buffer[idx] : 0x00;
            epd->op->writeByte(epd, data);
        }
    }

    //_Update_Part(epd);
    // update previous buffer
    //epd->op->delay(GDEY0213B74_PU_DELAY);
    _SetRamArea(epd, xs_d8, xe_d8, y % 256, y / 256, ye % 256, ye / 256);  // X-source area,Y-gate area
    _SetRamPointer(epd, xs_d8, y % 256, y / 256);                          // set ram
    epd->op->waitWhileBusy(epd, 0, 100);                                           // needed ?

   
    // If I don't do this then the 2nd partial comes out gray:

    epd->op->writeCommand(epd, 0x26);  // RAM2
    for (int16_t y1 = y; y1 <= ye; y1++) {
        for (int16_t x1 = xs_d8; x1 <= xe_d8; x1++) {
            uint16_t idx = y1 * (GDEY0213B74_WIDTH / 8) + x1;
            uint8_t data = (idx < sizeof(me->_buffer)) ? me->_buffer[idx] : 0x00;
            epd->op->writeByte(epd, ~data);
        }
    }

    // epd->op->writeCommand(epd, 0x20);
    //epd->op->waitBusy(epd, "update partial");
    epd->op->delay(GDEY0213B74_PU_DELAY);
    TIMER_E
}

static void _sleep(void* _me) {
    LOGR
    epd_g_t* epd = _me;
    epd->op->writeCommand(epd, 0x10);  // deep sleep
    epd->op->writeByte(epd, 0x01);
     //epd->op->waitBusy(_me, "power_off");
}

// turns off generation of panel driving voltages, avoids screen fading over time
static void powerOff(void* _me) {
    TIMER_S
    _PowerOff(_me);
    TIMER_E
}

// turns powerOff() and sets controller to deep sleep for minimum power use, ONLY if wakeable by RST (rst >= 0)
static void hibernate(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    _PowerOff(_me);
    if (CONFIG_DISPLAY_RST >= 0) {
        epd->op->writeCommand(epd, 0x10);  // deep sleep mode
        epd->op->writeByte(epd, 0x1);      // enter deep sleep
        epd->_hibernating = true;
    }
    TIMER_E
}

static void drawPixel(void* _me, int16_t x, int16_t y, uint16_t color) {
    epd_g_t* epd = _me;
    if ((x < 0) || (x >= epd->_width) || (y < 0) || (y >= epd->_height))
        return;

    gdey0213b74_t* me = epd->screen;
    // check rotation, move pixel around if necessary
    switch (epd->rotation) {
        case 1:
            _swap_uint16_t(x, y);
            x = GDEY0213B74_VISIBLE_WIDTH - x - 1;
            break;
        case 2:
            x = GDEY0213B74_VISIBLE_WIDTH - x - 1;
            y = GDEY0213B74_HEIGHT - y - 1;
            break;
        case 3:
            _swap_uint16_t(x, y);
            y = GDEY0213B74_HEIGHT - y - 1;
            break;
    }
    uint16_t i = x / 8 + y * GDEY0213B74_WIDTH / 8;
    uint8_t mask = 1 << (7 - x % 8);

    if (me->_mono_mode) {
        if (color) {
            me->_buffer[i] = me->_buffer[i] | mask;
        } else {
            me->_buffer[i] = me->_buffer[i] & (0xFF ^ mask);
        }
    } else {
        // 4 gray mode
        mask = 0x80 >> (x & 7);
        color >>= 6;  // Color is from 0 (black) to 255 (white)

        switch (color) {
            case 1:
                // Dark gray
                me->_buffer1[i] = me->_buffer1[i] & (0xFF ^ mask);
                me->_buffer2[i] = me->_buffer2[i] | mask;
                break;
            case 2:
                // Light gray
                me->_buffer1[i] = me->_buffer1[i] | mask;
                me->_buffer2[i] = me->_buffer2[i] & (0xFF ^ mask);
                break;
            case 3:
                // White
                me->_buffer1[i] = me->_buffer1[i] & (0xFF ^ mask);
                me->_buffer2[i] = me->_buffer2[i] & (0xFF ^ mask);
                break;
            default:
                // Black
                me->_buffer1[i] = me->_buffer1[i] | mask;
                me->_buffer2[i] = me->_buffer2[i] | mask;
                break;
        }
    }
}

// We use only 0x03: At the moment this method is not used
// ram_entry_mode = 0x03; // y-increment, x-increment : normal mode
// ram_entry_mode = 0x00; // y-decrement, x-decrement
// ram_entry_mode = 0x01; // y-decrement, x-increment
// ram_entry_mode = 0x02; // y-increment, x-decrement
static void _setRamDataEntryMode(void* _me, uint8_t em) {
    epd_g_t* epd = _me;
    const uint16_t xPixelsPar = GDEY0213B74_X_PIXELS - 1;
    const uint16_t yPixelsPar = GDEY0213B74_Y_PIXELS - 1;
    em = gx_uint16_min(em, 0x03);
    epd->op->writeCommand(epd, 0x11);
    epd->op->writeByte(epd, em);
    switch (em) {
        case 0x00:                                                                                   // x decrease, y decrease
            _SetRamArea(epd, xPixelsPar / 8, 0x00, yPixelsPar % 256, yPixelsPar / 256, 0x00, 0x00);  // X-source area,Y-gate area
            _SetRamPointer(epd, xPixelsPar / 8, yPixelsPar % 256, yPixelsPar / 256);                 // set ram
            break;
        case 0x01:                                                                                   // x increase, y decrease : as in demo code
            _SetRamArea(epd, 0x00, xPixelsPar / 8, yPixelsPar % 256, yPixelsPar / 256, 0x00, 0x00);  // X-source area,Y-gate area
            _SetRamPointer(epd, 0x00, yPixelsPar % 256, yPixelsPar / 256);                           // set ram
            break;
        case 0x02:                                                                                   // x decrease, y increase
            _SetRamArea(epd, xPixelsPar / 8, 0x00, 0x00, 0x00, yPixelsPar % 256, yPixelsPar / 256);  // X-source area,Y-gate area
            _SetRamPointer(epd, xPixelsPar / 8, 0x00, 0x00);                                         // set ram
            break;
        case 0x03:                                                                                   // x increase, y increase : normal mode
            _SetRamArea(epd, 0x00, xPixelsPar / 8, 0x00, 0x00, yPixelsPar % 256, yPixelsPar / 256);  // X-source area,Y-gate area
            _SetRamPointer(epd, 0x00, 0x00, 0x00);                                                   // set ram
            break;
    }
}

static void _SetRamArea(void* _me, uint8_t Xstart, uint8_t Xend, uint8_t Ystart, uint8_t Ystart1, uint8_t Yend, uint8_t Yend1) {
    epd_g_t* epd = _me;
    epd->op->writeCommand(epd, 0x44);
    epd->op->writeByte(epd, Xstart);
    epd->op->writeByte(epd, Xend);
    epd->op->writeCommand(epd, 0x45);
    epd->op->writeByte(epd, Ystart);
    epd->op->writeByte(epd, Ystart1);
    epd->op->writeByte(epd, Yend);
    epd->op->writeByte(epd, Yend1);
}

static void _SetRamPointer(void* _me, uint8_t addrX, uint8_t addrY, uint8_t addrY1) {
    epd_g_t* epd = _me;
    epd->op->writeCommand(epd, 0x4e);
    epd->op->writeByte(epd, addrX);
    epd->op->writeCommand(epd, 0x4f);
    epd->op->writeByte(epd, addrY);
    epd->op->writeByte(epd, addrY1);
}

// _InitDisplay generalizing names here
static void _InitDisplay(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t* epd = _me;
    if (epd->_hibernating) {
        epd->op->reset(epd, 10);
    }
    epd->op->delay(10);                // 10ms according to specs
    epd->op->writeCommand(epd, 0x12);  // SWRESET
    epd->op->delay(10);                // 10ms according to specs
    //epd->op->waitWhileBusy(epd, "SWRESET", 10);

    epd->op->writeCommand(epd, 0x01);  // Driver output control
    epd->op->writeByte(epd, 0xF9);
    epd->op->writeByte(epd, 0x00);
    epd->op->writeByte(epd, 0x00);

    epd->op->writeCommand(epd, 0x11);  // data entry mode
    epd->op->writeByte(epd, 0x01);

    epd->op->writeCommand(epd, 0x44);  // set Ram-X address start/end position
    epd->op->writeByte(epd, 0x00);
    epd->op->writeByte(epd, 0x0F);  // 0x0F-->(15+1)*8=128
    epd->op->writeCommand(epd, 0x45);  // set Ram-Y address start/end position
    epd->op->writeByte(epd, 0xF9);     // 0xF9-->(249+1)=250
    epd->op->writeByte(epd, 0x00);
    epd->op->writeByte(epd, 0x00);
    epd->op->writeByte(epd, 0x00);

    epd->op->writeCommand(epd, 0x3C);  // BorderWavefrom
    epd->op->writeByte(epd, 0x05);

    epd->op->writeCommand(epd, 0x21);  //  Display update control
    epd->op->writeByte(epd, 0x00);
    epd->op->writeByte(epd, 0x80);

    epd->op->writeCommand(epd, 0x18);  // Read built-in temperature sensor
    epd->op->writeByte(epd, 0x80);

    epd->op->writeCommand(epd, 0x4E);  // set RAM x address count to 0;
    epd->op->writeByte(epd, 0x00);

    epd->op->writeCommand(epd, 0x4F);  // set RAM y address count to 0X199;
    epd->op->writeByte(epd, 0xF9);
    epd->op->writeByte(epd, 0x00);

    //_setRamDataEntryMode(_me, em);

    //epd->op->waitWhileBusy(epd, "wakeup CMDs", 10);
    TIMER_E
}

static void _wakeUp(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t* epd = _me;
    if (epd->_hibernating) {
        epd->op->reset(epd, 10);
    }
    epd->op->delay(10);                // 10ms according to specs
    epd->op->writeCommand(epd, 0x12);  // SWRESET
    epd->op->delay(10);                // 10ms according to specs

    epd->op->writeCommand(epd, 0x74);  // set analog block control
    epd->op->writeByte(epd, 0x54);

    epd->op->writeCommand(epd, 0x7E);  // set digital block control
    epd->op->writeByte(epd, 0x3B);

    epd->op->writeCommand(epd, 0x01);  // Driver output control
    epd->op->writeByte(epd, 0x07);
    epd->op->writeByte(epd, 0x01);
    epd->op->writeByte(epd, 0x00);

    epd->op->writeCommand(epd, 0x11);  // data entry mode
    epd->op->writeByte(epd, 0x01);

    epd->op->writeCommand(epd, 0x44);  // set Ram-X address start/end position
    epd->op->writeByte(epd, 0x00);
    epd->op->writeByte(epd, 0x0F);  // 0x0F-->(15+1)*8=128

    epd->op->writeCommand(epd, 0x45);  // set Ram-Y address start/end position
    epd->op->writeByte(epd, 0xF9);     // 0xF9-->(249+1)=250
    epd->op->writeByte(epd, 0x00);
    epd->op->writeByte(epd, 0x00);
    epd->op->writeByte(epd, 0x00);

    epd->op->writeCommand(epd, 0x3C);  // BorderWavefrom
    epd->op->writeByte(epd, 0x00);

    epd->op->writeCommand(epd, 0x2C);                // VCOM Voltage
    epd->op->writeByte(epd, lut_4_grays.data[158]);  // 0x1C

    epd->op->writeCommand(epd, 0x3F);  // EOPQ
    epd->op->writeByte(epd, lut_4_grays.data[153]);

    epd->op->writeCommand(epd, 0x03);  // VGH
    epd->op->writeByte(epd, lut_4_grays.data[154]);

    epd->op->writeCommand(epd, 0x04);                //
    epd->op->writeByte(epd, lut_4_grays.data[155]);  // VSH1
    epd->op->writeByte(epd, lut_4_grays.data[156]);  // VSH2
    epd->op->writeByte(epd, lut_4_grays.data[157]);  // VSL

    // LUT init table for 4 gray. Check if it's needed!
    epd->op->writeCommand(epd, lut_4_grays.cmd);  // boost
    epd->op->writeDataArray(epd,&(lut_4_grays.data[0]),lut_4_grays.databytes);
    TIMER_E
}

static void _PowerOn(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    if (!epd->_power_is_on) {
        epd->op->writeCommand(epd, 0x22);
        epd->op->writeByte(epd, 0xc0);
        epd->op->writeCommand(epd, 0x20);
        epd->op->waitWhileBusy(epd, "_PowerOn", power_on_time);
        epd->_power_is_on = true;
    }
    TIMER_E
}

static void _PowerOff(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    if (epd->_power_is_on) {
        epd->op->writeCommand(epd, 0x22);
        epd->op->writeByte(epd, 0x83);
        epd->op->writeCommand(epd, 0x20);
        epd->op->waitWhileBusy(epd, "_PowerOff", power_off_time);
        epd->_power_is_on = false;
    }
    TIMER_E
}

static void _Init_Full(void* _me, uint8_t em) {
    TIMER_S
    _InitDisplay(_me, em);
    _PowerOn(_me);
    TIMER_E
}

static void _Init_Part(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t* epd = _me;
    _InitDisplay(_me, em);
    epd->op->writeCommand(_me, lut_4_grays.cmd);
    epd->op->writeDataArray(epd,&(lut_4_grays.data[0]),lut_4_grays.databytes);
    _PowerOn(_me);
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

static epdg_screen_driver_t my_driver = SCREEN_GDEY0213B74;

void gdey0213b74_deinit(void* _me) {
    LOGR
    if (!_me)
        return;
    epdg_screen_deinit(((gdey0213b74_t*)_me)->epd);
}

gdey0213b74_t* gdey0213b74_new(epd_g_t* epd, bool debug) {
    LOGR
    gdey0213b74_t* me = (gdey0213b74_t*)malloc(sizeof(struct gdey0213b74_s));
    return gdey0213b74_init(me, epd, debug);
}

void gdey0213b74_free(void* _me) {
    LOGR
    if (_me) {
        gdey0213b74_deinit(_me);
        free(_me);
    }
}

screen_op_t gdey0213b74_ops = {
    .powerOff = powerOff,
    .hibernate = hibernate,
    .update = update,
    .updateWindow = updateWindow,
    .get_height = _get_height,
    .get_width = _get_width,
    .hasFastPartialUpdate = _has_fast_partial_update,

    .deinit = gdey0213b74_deinit,
    .free = gdey0213b74_free,
};

// Initialize the display
gdey0213b74_t* gdey0213b74_init(gdey0213b74_t* me, epd_g_t* epd, bool debug) {
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
    
    // class overrides
    epd->HEIGHT = epd->_height = HEIGHT;
    epd->WIDTH = epd->_width = WIDTH;
    epd->buffer = me->_buffer;
    epd->buffer_size = sizeof(me->_buffer);
    epd->_page_height = HEIGHT;
    epd->_pages = (epd->HEIGHT / epd->_page_height) + ((epd->HEIGHT % epd->_page_height) > 0);
    epd->TAG = QUOTE_CMD(N);
    epd->op->setRotation(epd, 1);
    epd->screenop = &gdey0213b74_ops;
    epd->screen = me;
    // method overrides
    TIMER_E
    return me;
}
