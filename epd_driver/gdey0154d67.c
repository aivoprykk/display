// GOODISPLAY product https://www.good-display.com/product/388.html
#include "gdey0154d67.h"

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
#include <logger_common.h>

#define N gdey0154d67

static const char* TAG = QUOTE_CMD(N);

static const uint16_t WIDTH = 200;
static const uint16_t WIDTH_VISIBLE = WIDTH;
static const uint16_t HEIGHT = 200;
static bool hasColor = false;
static bool hasPartialUpdate = true;
static const bool hasFastPartialUpdate = true;
static const bool useFastFullUpdate = true;        // set false for extended (low) temperature range
static const uint16_t power_on_time = 100;         // ms, e.g. 96000us
static const uint16_t power_off_time = 150;        // ms, e.g. 141000us
static const uint16_t full_refresh_time = 2000;    // ms, e.g. 1907000us
static const uint16_t partial_refresh_time = 500;  // ms, e.g. 459000us

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
#define SSD168X_WRITE_RAM_1 0x24
#define SSD168X_WRITE_RAM_2 0x26
#define SSD168X_WRITE_VCOM_REGISTER 0x2C
#define SSD168X_WRITE_LUT_REGISTER 0x32
#define SSD168X_SET_DUMMY_LINE_PERIOD 0x3A
#define SSD168X_SET_GATE_TIME 0x3B
#define SSD168X_BORDER_WAVEFORM_CONTROL 0x3C
#define SSD168X_SET_RAM_X_ADDRESS_START_END_POSITION 0x44
#define SSD168X_SET_RAM_Y_ADDRESS_START_END_POSITION 0x45
#define SSD168X_SET_RAM_X_ADDRESS_COUNTER 0x4E
#define SSD168X_SET_RAM_Y_ADDRESS_COUNTER 0x4F
#define SSD168X_SET_ANALOG_BLOCK_CONTROL 0x74
#define SSD168X_SET_DIGITAL_BLOCK_CONTROL 0x7E
#define SSD168X_TERMINATE_FRAME_READ_WRITE 0xFF

/*
 The EPD needs a bunch of command/data values to be initialized. They are send using the IO class
*/
#define GDEY0154D67_PU_DELAY 300

// Place data into DRAM. Constant data gets placed into DROM by default, which is not accessible by DMA.

static epd_lut_159 lut_4_grays = {
    SSD168X_WRITE_LUT_REGISTER,
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

/* static uint8_t lut_partial[] =
    {
        0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x80, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x2, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0, 0x0, 0x0}; */

DRAM_ATTR const epd_init_3 GDOControl = {
    SSD168X_DRIVER_OUTPUT_CONTROL,
    {(HEIGHT - 1) % 256, (HEIGHT - 1) / 256, 0x00},
    3};

// static void init(void* _me, bool debug) ;
// static void fillScreen(void* _me, uint16_t color);
static void update(void* _me);
static void updateWindow(void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
static void _Deep_Sleep(void* _me);
// static void _rotate(void* _me, uint16_t* x, uint16_t* y, uint16_t* w, uint16_t* h);
// static void drawPixel(void* _me, int16_t x, int16_t y, uint16_t color);
static void _wakeUp(void* _me, uint8_t em);
static void _Init_Full(void* _me, uint8_t em);
static void _Init_Part(void* _me, uint8_t em);
static void _InitDisplay(void* _me, uint8_t em);
static void _Update_Full(void* _me);
static void _Update_Part(const void* _me);
static void _setRamDataEntryMode(void* _me, uint8_t em);
static void _SetRamArea(const void* _me, uint8_t Xstart, uint8_t Xend, uint8_t Ystart, uint8_t Ystart1, uint8_t Yend, uint8_t Yend1);
static void _SetRamPointer(const void* _me, uint8_t addrX, uint8_t addrY, uint8_t addrY1);
static void _PowerOn(void* _me);
static void _PowerOff(void* _me);
static void hibernate(void* _me);

/* static void fillScreen(void* _me, uint16_t color) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0154d67_t* me = me;
    if (me->_mono_mode) {
        // 0xFF = 8 pixels black, 0x00 = 8 pix. white
        uint8_t data = (color == EPD_BLACK) ? GDEY0154D67_8PIX_BLACK : GDEY0154D67_8PIX_WHITE;
        for (uint16_t x = 0; x < sizeof(me->_buffer); x++) {
            me->_buffer[x] = data;
        }
    } else {
        // 4 Grays mode
        // This is to make faster black & white
        if (color == 255 || color == 0) {
            for (uint32_t i = 0; i < GDEY0154D67_BUFFER_SIZE; i++) {
                me->_buffer1[i] = (color == 0xFF) ? 0xFF : 0x00;
                me->_buffer2[i] = (color == 0xFF) ? 0xFF : 0x00;
            }
            return;
        }

        for (uint32_t y = 0; y < HEIGHT; y++) {
            for (uint32_t x = 0; x < WIDTH; x++) {
                drawPixel(_me, x, y, color);
                if (x % 8 == 0) {
                    vTaskDelay(pdMS_TO_TICKS(2));
                }
            }
        }
    }
    TIMER_E
} */

/* static void _write_ram_y_dec(const epd_g_t* epd, uint8_t em, uint8_t* buf, uint16_t bufsiz, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8) {
    const uint8_t xLineBytes = WIDTH / 8;
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ye; y1 > ys; --y1) {  // decrease
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            epd->op->writeByte(epd, (idx < bufsiz) ? ~buf[idx] : 0xff);
        }
    }
} */

static void _write_ram_y_dec_opt(const epd_g_t* epd, uint8_t em, uint8_t* buf, uint16_t bufsiz, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8) {
    const uint8_t xLineBytes = WIDTH / 8;
    uint8_t x1buf[xLineBytes];
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ye; y1 > ys; --y1) {  // decrease
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            x1buf[x1] = (idx < bufsiz) ? ~buf[idx] : 0xFF;
        }
        epd->op->writeDataArray(epd, x1buf, sizeof(x1buf));
    }
}

static void _write_ram_y_inc(const epd_g_t* epd, uint8_t em, uint8_t* buf, uint16_t bufsiz, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8) {
    const uint8_t xLineBytes = WIDTH / 8;
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ys; y1 < ye; ++y1) {  // decrease
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            epd->op->writeByte(epd, (idx < bufsiz) ? ~buf[idx] : 0xff);
        }
    }
}

static void _write_ram_y_inc_opt(const epd_g_t* epd, uint8_t em, uint8_t* buf, uint16_t bufsiz, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8) {
    const uint8_t xLineBytes = WIDTH / 8;
    uint8_t x1buf[xLineBytes];
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ys; y1 < ye; ++y1) {  // decrease
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            x1buf[x1] = (idx < bufsiz) ? ~buf[idx] : 0xFF;
        }
        epd->op->writeDataArray(epd, x1buf, sizeof(x1buf));
    }
}

static void _set_ram_y_dec_opt(const epd_g_t* epd, uint8_t em, uint8_t* x1buf, uint16_t x1buf_size) {
    TIMER_S
    uint16_t y;
    epd->op->writeCommand(epd, em);  // write RAM for black(0)/white (1)
    for (y = HEIGHT; y > 0; --y) {
        epd->op->writeDataArray(epd, x1buf, x1buf_size);
    }
    TIMER_E
}

/* static void _set_ram_y_inc_opt(const epd_g_t* epd, uint8_t em, uint8_t* x1buf, uint16_t x1buf_size) {
    TIMER_S
    uint16_t y;                      //, idx;
    epd->op->writeCommand(epd, em);  // write RAM for black(0)/white (1)
    for (y = 0; y < HEIGHT; ++y) {
        epd->op->writeDataArray(epd, x1buf, x1buf_size);
    }
    TIMER_E
}

static void _set_ram_y_inc_full_opt(const epd_g_t* epd, uint8_t color, uint8_t choice) {
    uint8_t xLineBytes = WIDTH / 8, x;
    uint8_t x1buf[xLineBytes];
    for (x = 0; x < xLineBytes; ++x)
        x1buf[x] = color;
    if (choice == SSD168X_WRITE_RAM_1 || choice == 0)
        _set_ram_y_inc_opt(epd, SSD168X_WRITE_RAM_1, x1buf, sizeof(x1buf));
    if (choice == SSD168X_WRITE_RAM_2 || choice == 0)
        _set_ram_y_inc_opt(epd, SSD168X_WRITE_RAM_2, x1buf, sizeof(x1buf));
} */

static void _set_ram_y_dec_full_opt(const epd_g_t* epd, uint8_t color, uint8_t choice) {
    uint8_t xLineBytes = WIDTH / 8, x;
    uint8_t x1buf[xLineBytes];
    for (x = 0; x < xLineBytes; ++x)
        x1buf[x] = color;
    if (choice == SSD168X_WRITE_RAM_1 || choice == 0)
        _set_ram_y_dec_opt(epd, SSD168X_WRITE_RAM_1, x1buf, sizeof(x1buf));
    if (choice == SSD168X_WRITE_RAM_2 || choice == 0)
        _set_ram_y_dec_opt(epd, SSD168X_WRITE_RAM_2, x1buf, sizeof(x1buf));
}

static void update(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
    // uint64_t startTime = esp_timer_get_time();
    uint8_t xLineBytes = WIDTH / 8, x;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    if (me->_mono_mode) {
        _Init_Full(_me, 0x01);
        _set_ram_y_dec_full_opt(epd, 0xff, 0);
        _write_ram_y_dec_opt(epd, SSD168X_WRITE_RAM_1, me->_buffer, epd->buffer_size, 0, HEIGHT, 0, xLineBytes);
        //_write_ram_y_dec_opt(epd, SSD168X_WRITE_RAM_2, me->_buffer, epd->buffer_size, 0, HEIGHT, 0, xLineBytes);
    } else {
        // 4 gray mode!
        _wakeUp(_me, 0);
        _write_ram_y_dec_opt(epd, SSD168X_WRITE_RAM_1, me->_buffer1, epd->buffer_size, 0, HEIGHT, 0, xLineBytes);
        _write_ram_y_dec_opt(epd, SSD168X_WRITE_RAM_2, me->_buffer2, epd->buffer_size, 0, HEIGHT, 0, xLineBytes);  // both buffers same for full b/w
    }

    _Update_Full(epd);
    hibernate(_me);
    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void _write_ram_part(const epd_g_t* epd, uint8_t em, uint16_t y, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t ys_m256, uint8_t ys_d256, uint8_t ye_m256, uint8_t ye_d256, uint8_t init) {
    if (init) {
        _SetRamArea(epd, xs_d8, xe_d8, ys_m256, ys_d256, ye_m256, ye_d256);  // X-source area,Y-gate area
        _SetRamPointer(epd, xs_d8, ys_m256, ys_d256);                        // set ram
        epd->op->waitWhileBusy(epd, __FUNCTION__, 100);
    }
    //_set_ram_y_dec_full_opt(epd, 0x00, em);                     // needed ?
    _write_ram_y_inc(epd, em, epd->buffer, epd->buffer_size, y, ye, xs_d8, xe_d8);
    if (init != 3)
        _Update_Part(epd);
    epd->op->delay(GDEY0154D67_PU_DELAY);
}

static void _Dis_Part(const void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    TIMER_S
    const epd_g_t* epd = _me;
    /// HEIGHT = 250, WIDTH = 128, LINE_BYTES = 16, BUFFER_SIZE = 4000
    const uint16_t xe = gx_uint16_min(WIDTH, x + w) - 1;   // x+w must be less than WIDTH
    const uint16_t ye = gx_uint16_min(HEIGHT, y + h) - 1;  // y+h must be less than HEIGHT
    const uint8_t xs_d8 = x / 8;                           // start x/8
    const uint8_t xe_d8 = xe / 8;                          // end x/8
    const uint8_t ys_d256 = y / 256;
    const uint8_t ys_m256 = y % 256;
    const uint8_t ye_d256 = ye / 256;
    const uint8_t ye_m256 = ye % 256;
    _write_ram_part(epd, SSD168X_WRITE_RAM_1, y, ye, xs_d8, xe_d8, ys_m256, ys_d256, ye_m256, ye_d256, 1);
    TIMER_E
}

static void updateWindow(void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    if (epd->rotation)
        epd->op->rotate(epd, &x, &y, &w, &h);
    if (x >= WIDTH)
        return;
    if (y >= HEIGHT)
        return;

    _Init_Part(epd, 0x03);
    //_set_ram_y_dec_full_opt(epd, 0xff, SSD168X_WRITE_RAM_1);
    _set_ram_y_dec_full_opt(epd, 0x00, SSD168X_WRITE_RAM_2);
    _Dis_Part(epd, x, y, w, h);

    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void _Deep_Sleep(void* _me) {
    epd_g_t* epd = _me;
    epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);  // power off display
    epd->op->writeByte(epd, 0xc3);
    epd->op->writeCommand(epd, SSD168X_MASTER_ACTIVATION);
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
        epd->op->writeCommand(epd, SSD168X_DEEP_SLEEP_MODE);  // deep sleep mode
        epd->op->writeByte(epd, 0x1);                         // enter deep sleep
        epd->_hibernating = true;
    }
    TIMER_E
}

/* static void drawPixel(void* _me, int16_t x, int16_t y, uint16_t color) {
    epd_g_t* epd = _me;
    if ((x < 0) || (x >= epd->_width) || (y < 0) || (y >= epd->_height))
        return;

    // check rotation, move pixel around if necessary
    switch (epd->rotation) {
        case 1:
            _swap_uint16_t(x, y);
            x = WIDTH - x - 1;
            break;
        case 2:
            x = WIDTH - x - 1;
            y = HEIGHT - y - 1;
            break;
        case 3:
            _swap_uint16_t(x, y);
            y = HEIGHT - y - 1;
            break;
    }
    uint16_t i = x / 8 + y * WIDTH / 8;
    gdey0154d67_t* me = me;
    if (me->_mono_mode) {
        // This is the trick to draw colors right. Genious Jean-Marc
        if (color) {
            me->_buffer[i] = (me->_buffer[i] & (0xFF ^ (1 << (7 - x % 8))));
        } else {
            me->_buffer[i] = (me->_buffer[i] | (1 << (7 - x % 8)));
        }
    } else {
        // 4 gray mode
        uint8_t mask = 0x80 >> (x & 7);

        color >>= 6;  // Color is from 0 (black) to 255 (white)

        switch (color) {
            case 1:
                // Dark gray: Correct
                me->_buffer1[i] = me->_buffer1[i] | mask;
                me->_buffer2[i] = me->_buffer2[i] & (0xFF ^ mask);
                break;
            case 2:
                // Light gray: Correct
                me->_buffer1[i] = me->_buffer1[i] & (0xFF ^ mask);
                me->_buffer2[i] = me->_buffer2[i] | mask;
                break;
            case 3:
                // WHITE
                me->_buffer1[i] = me->_buffer1[i] | mask;
                me->_buffer2[i] = me->_buffer2[i] | mask;
                break;
            default:
                // Black
                me->_buffer1[i] = me->_buffer1[i] & (0xFF ^ mask);
                me->_buffer2[i] = me->_buffer2[i] & (0xFF ^ mask);
                break;
        }
    }
} */

static void _setRamDataEntryMode(void* _me, uint8_t em) {
    const uint16_t xPixelsPar = WIDTH - 1;
    const uint16_t yPixelsPar = HEIGHT - 1;
    const uint8_t x_d8 = xPixelsPar / 8;
    const uint8_t y_d256 = yPixelsPar / 256;
    const uint8_t y_m256 = yPixelsPar % 256;
    em = gx_uint16_min(em, 0x03);
    epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->op->writeCommand(epd, SSD168X_DATA_ENTRY_MODE_SETTING);
    epd->op->writeByte(epd, em);
    switch (em) {
        case 0x00:                                                     // x decrease, y decrease
            _SetRamArea(epd, x_d8, 0x00, y_m256, y_d256, 0x00, 0x00);  // X-source area,Y-gate area
            _SetRamPointer(epd, x_d8, y_m256, y_d256);                 // set ram
            break;
        case 0x01:                                                     // x increase, y decrease : as in demo code
            _SetRamArea(epd, 0x00, x_d8, y_m256, y_d256, 0x00, 0x00);  // X-source area,Y-gate area
            _SetRamPointer(epd, 0x00, y_m256, y_d256);                 // set ram
            break;
        case 0x02:                                                     // x decrease, y increase
            _SetRamArea(epd, x_d8, 0x00, 0x00, 0x00, y_m256, y_d256);  // X-source area,Y-gate area
            _SetRamPointer(epd, x_d8, 0x00, 0x00);                     // set ram
            break;
        case 0x03:                                                     // x increase, y increase : normal mode
            _SetRamArea(epd, 0x00, x_d8, 0x00, 0x00, y_m256, y_d256);  // X-source area,Y-gate area
            _SetRamPointer(epd, 0x00, 0x00, 0x00);                     // set ram
            break;
    }
    xSemaphoreGiveRecursive(me->screen_lock);
}

static void _SetRamArea(const void* _me, uint8_t Xstart, uint8_t Xend, uint8_t Ystart, uint8_t Ystart1, uint8_t Yend, uint8_t Yend1) {
    const epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->op->writeCommand(epd, SSD168X_SET_RAM_X_ADDRESS_START_END_POSITION);
    epd->op->writeByte(epd, Xstart);
    epd->op->writeByte(epd, Xend);
    epd->op->writeCommand(epd, SSD168X_SET_RAM_Y_ADDRESS_START_END_POSITION);
    epd->op->writeByte(epd, Ystart);
    epd->op->writeByte(epd, Ystart1);
    epd->op->writeByte(epd, Yend);
    epd->op->writeByte(epd, Yend1);
    xSemaphoreGiveRecursive(me->screen_lock);
}

static void _SetRamPointer(const void* _me, uint8_t addrX, uint8_t addrY, uint8_t addrY1) {
    const epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    epd->op->writeCommand(epd, SSD168X_SET_RAM_X_ADDRESS_COUNTER);
    epd->op->writeByte(epd, addrX);
    epd->op->writeCommand(epd, SSD168X_SET_RAM_Y_ADDRESS_COUNTER);
    epd->op->writeByte(epd, addrY);
    epd->op->writeByte(epd, addrY1);
    xSemaphoreGiveRecursive(me->screen_lock);
}

static void _PowerOn(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
    if (!epd->_power_is_on) {
        xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
        epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
        epd->op->writeByte(epd, 0xc0);
        epd->op->writeCommand(epd, SSD168X_MASTER_ACTIVATION);
        epd->op->waitWhileBusy(_me, __FUNCTION__, power_on_time);
        epd->_power_is_on = true;
        xSemaphoreGiveRecursive(me->screen_lock);
    }
    TIMER_E
}

static void _PowerOff(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
    if (epd->_power_is_on) {
        xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
        epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);
        epd->op->writeByte(epd, 0x83);
        epd->op->writeCommand(epd, SSD168X_MASTER_ACTIVATION);
        epd->op->waitWhileBusy(epd, __FUNCTION__, power_off_time);
        epd->_power_is_on = false;
        xSemaphoreGiveRecursive(me->screen_lock);
    }
    TIMER_E
}

// Now redefined as 4 gray mode
static void _wakeUp(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    if (epd->_hibernating) {
        epd->op->reset(epd, 10);
    }
    epd->op->writeCommand(epd, SSD168X_SW_RESET);  // SWRESET
    epd->op->waitWhileBusy(_me, __FUNCTION__, 10);

    epd->op->writeCommand(epd, SSD168X_SET_ANALOG_BLOCK_CONTROL);  // set analog block control
    epd->op->writeByte(epd, 0x54);

    epd->op->writeCommand(epd, SSD168X_SET_DIGITAL_BLOCK_CONTROL);  // set digital block control
    epd->op->writeByte(epd, 0x3B);

    epd->op->writeCommand(epd, SSD168X_DRIVER_OUTPUT_CONTROL);  // Driver output control
    epd->op->writeByte(epd, 0x07);
    epd->op->writeByte(epd, 0x01);
    epd->op->writeByte(epd, 0x00);

    _setRamDataEntryMode(_me, em);

    epd->op->writeCommand(epd, SSD168X_BORDER_WAVEFORM_CONTROL);  // BorderWavefrom
    epd->op->writeByte(epd, 0x00);

    epd->op->writeCommand(epd, SSD168X_WRITE_VCOM_REGISTER);  // VCOM Voltage
    epd->op->writeByte(epd, lut_4_grays.data[158]);           // 0x1C

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
    epd->op->writeDataArray(epd, &(lut_4_grays.data[0]), lut_4_grays.databytes);
    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void _InitDisplay(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    if (epd->_hibernating) {
        epd->op->reset(epd, 10);
    }
    epd->op->writeCommand(epd, SSD168X_SW_RESET);  // SWRESET
    epd->op->waitWhileBusy(_me, __FUNCTION__, 10);

    /* epd->op->writeCommand(epd, GDOControl.cmd);
    for (int i=0;i<GDOControl.databytes;++i) {
        epd->op->writeByte(epd, GDOControl.data[i]);
    } */
    epd->op->writeCommand(epd, SSD168X_DRIVER_OUTPUT_CONTROL);  // Driver output control
    epd->op->writeByte(_me, (HEIGHT - 1) & 0xff);
    epd->op->writeByte(_me, ((HEIGHT - 1) >> 8) & 0xff);
    epd->op->writeByte(epd, 0x00);

    _setRamDataEntryMode(_me, em);

    epd->op->writeCommand(epd, SSD168X_BORDER_WAVEFORM_CONTROL);  // BorderWavefrom
    epd->op->writeByte(epd, 0x05);

    epd->op->writeCommand(epd, SSD168X_TEMPERATURE_SENSOR_READ);  // Read built-in temperature sensor
    epd->op->writeByte(epd, 0x80);

    epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);  // Load Temperature and waveform setting.
    epd->op->writeByte(epd, 0XB1);

    epd->op->writeCommand(epd, SSD168X_MASTER_ACTIVATION);

    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void _InitDisplayFast(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    if (epd->_hibernating) {
        epd->op->reset(epd, 10);
    }
    epd->op->writeCommand(epd, SSD168X_SW_RESET);  // SWRESET
    epd->op->waitWhileBusy(_me, __FUNCTION__, 10);

    epd->op->writeCommand(epd, SSD168X_TEMPERATURE_SENSOR_READ);  // Read built-in temperature sensor
    epd->op->writeByte(epd, 0x80);

    epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);  // Read built-in temperature sensor
    epd->op->writeByte(epd, 0xB1);
    epd->op->writeByte(epd, 0x20);
    epd->op->waitWhileBusy(_me, __FUNCTION__, 10);

    epd->op->writeCommand(epd, SSD168X_TEMPERATURE_SENSOR_CONTROL);  // Read built-in temperature sensor
    epd->op->writeByte(epd, 0x64);
    epd->op->writeByte(epd, 0x00);

    epd->op->writeCommand(epd, SSD168X_DISPLAY_UPDATE_CONTROL_2);  // Read built-in temperature sensor
    epd->op->writeByte(epd, 0x91);
    epd->op->writeByte(epd, 0x20);
    epd->op->waitWhileBusy(_me, __FUNCTION__, 10);

    epd->op->writeCommand(epd, SSD168X_BORDER_WAVEFORM_CONTROL);  // BorderWavefrom
    epd->op->writeByte(epd, 0x05);

    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void _Init_Full(void* _me, uint8_t em) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
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
    gdey0154d67_t* me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    _InitDisplay(_me, em);
    // epd->op->writeCommand(_me, SSD168X_WRITE_LUT_REGISTER);
    // epd->op->writeDataArray(epd, &(lut_partial[0]), sizeof(lut_partial));
    epd->op->writeCommand(_me, SSD168X_WRITE_LUT_REGISTER);
    epd->op->writeDataArray(epd, &(lut_4_grays.data[0]), lut_4_grays.databytes);
    _PowerOn(_me);
    epd->_using_partial_mode = true;
    xSemaphoreGiveRecursive(me->screen_lock);
    TIMER_E
}

static void _Update_Full(void* _me) {
    TIMER_S
    epd_g_t* epd = _me;
    gdey0154d67_t* me = epd->screen;
    xSemaphoreTakeRecursive(me->screen_lock, portMAX_DELAY);
    if (useFastFullUpdate) {
        epd->op->writeCommand(epd, SSD168X_TEMPERATURE_SENSOR_CONTROL);
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
    gdey0154d67_t* me = epd->screen;
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

static epdg_screen_driver_t my_driver = SCREEN_GDEY0154D67;

void gdey0154d67_deinit(void* _me) {
    LOGR if (!_me) return;
    gdey0154d67_t* me = _me;
    vSemaphoreDelete(me->screen_lock);
    epdg_screen_deinit(me->epd);
}

gdey0154d67_t* gdey0154d67_new(epd_g_t* epd, bool debug) {
    LOGR
        gdey0154d67_t* me = (gdey0154d67_t*)malloc(sizeof(struct gdey0154d67_s));
    return gdey0154d67_init(me, epd, debug);
}

void gdey0154d67_free(void* _me) {
    LOGR if (_me) {
        gdey0154d67_deinit(_me);
        free(_me);
    }
}

const screen_op_t gdey0154d67_ops = {
    .powerOff = powerOff,
    .hibernate = hibernate,
    .update = update,
    .updateWindow = updateWindow,
    .get_height = _get_height,
    .get_width = _get_width,
    .hasFastPartialUpdate = _has_fast_partial_update,

    .deinit = gdey0154d67_deinit,
    .free = gdey0154d67_free,
};

gdey0154d67_t* gdey0154d67_init(gdey0154d67_t* me, epd_g_t* epd, bool debug) {
    TIMER_S

    if (!epd) {
        me->epd = epdg_new(my_driver, debug);
        me->epd->init_mode = 2;
        epd = me->epd;
        epd->_diag_enabled = debug;
    } else {
        me->epd = epd;
    }

    me->_mono_mode = true;
    me->spi_optimized = true;
    me->screen_lock = xSemaphoreCreateRecursiveMutex();

    // class overrides
    epd->HEIGHT = epd->_height = HEIGHT;
    epd->WIDTH = epd->_width = WIDTH;
    epd->buffer = me->_buffer;
    epd->buffer_size = sizeof(me->_buffer);
    epd->_page_height = HEIGHT;
    epd->_pages = (epd->HEIGHT / epd->_page_height) + ((epd->HEIGHT % epd->_page_height) > 0);
    epd->TAG = TAG;
    epd->op->setRotation(epd, 1);
    epd->screenop = &gdey0154d67_ops;
    epd->screen = me;
    TIMER_E
    return me;
}
