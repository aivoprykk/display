// GOODISPLAY product https://www.good-display.com/product/388.html
//            can be used alond DESPI-C03 adapter with Front light

#ifndef D355F571_B2D5_432B_9A8D_E600648EE4DF
#define D355F571_B2D5_432B_9A8D_E600648EE4DF

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

// Controller: SSD1681 (Acts similar than IL3829)
#define GDEY0154D67_WIDTH 200
#define GDEY0154D67_HEIGHT 200
#define GDEY0154D67_BUFFER_SIZE (((uint32_t) GDEY0154D67_WIDTH * (uint32_t)GDEY0154D67_HEIGHT) / 8)
// 1 byte of this color in the buffer
#define GDEY0154D67_8PIX_BLACK 0xFF
#define GDEY0154D67_8PIX_WHITE 0x00

// divisor for AVR, should be factor of GDEY0154D67_HEIGHT
#define GDEY0154D67_PAGES 4

#define GDEY0154D67_PAGE_HEIGHT (GDEY0154D67_HEIGHT / GDEY0154D67_PAGES)
#define GDEY0154D67_PAGE_SIZE (GDEY0154D67_BUFFER_SIZE / GDEY0154D67_PAGES)

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

// class Gdey0154d67 : public Epd
typedef struct gdey0154d67_s {
    struct epd_g_s* epd;
    //struct epd_spi_s* IO;
    bool spi_optimized;               // = true;
    SemaphoreHandle_t screen_lock;
    uint8_t _buffer[GDEY0154D67_BUFFER_SIZE];
    uint8_t _buffer1[GDEY0154D67_BUFFER_SIZE];
    uint8_t _buffer2[GDEY0154D67_BUFFER_SIZE];
    bool _initial;  // = true;
    bool _mono_mode;
    // Command & data structs
    // static const epd_lut_159 lut_4_grays;
    // static const epd_init_3 GDOControl;
} gdey0154d67_t;

void gdey0154d67_free(void* me);
void gdey0154d67_deinit(void* me);
gdey0154d67_t* gdey0154d67_init(gdey0154d67_t* me, struct epd_g_s* epd, bool debug);
gdey0154d67_t* gdey0154d67_new(struct epd_g_s* epd, bool debug);

#ifdef __cplusplus
}
#endif
#endif /* D355F571_B2D5_432B_9A8D_E600648EE4DF */
