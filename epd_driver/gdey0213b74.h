// GOODISPLAY product https://www.good-display.com/product/391.html
// Controller:        SSD1680Z

#ifndef D7C5EC4E_95A3_47B4_A463_5DCC207C8C14
#define D7C5EC4E_95A3_47B4_A463_5DCC207C8C14

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

// All comments below are from J-M Zingg (Ref. EPD)
// The physical number of pixels (for controller parameter)
#define GDEY0213B74_X_PIXELS 128
#define GDEY0213B74_Y_PIXELS 250

// The logical width and height of the display
#define GDEY0213B74_WIDTH GDEY0213B74_X_PIXELS
#define GDEY0213B74_HEIGHT GDEY0213B74_Y_PIXELS

// Note: the visible number of display pixels is 122*250, see GDEH0213B72 V1.1 Specification.pdf
#define GDEY0213B74_VISIBLE_WIDTH 122

#define GDEY0213B74_BUFFER_SIZE (((uint32_t)GDEY0213B74_WIDTH * (uint32_t)GDEY0213B74_HEIGHT) / 8)

// divisor for AVR, should be factor of GDEY0213B74_HEIGHT
#define GDEY0213B74_PAGES 4

#define GDEY0213B74_PAGE_HEIGHT (GDEY0213B74_HEIGHT / GDEY0213B74_PAGES)
#define GDEY0213B74_PAGE_SIZE (GDEY0213B74_BUFFER_SIZE / GDEY0213B74_PAGES)

// class Gdey0213b74 : public Epd
typedef struct gdey0213b74_s {
    struct epd_g_s* epd;
    //struct epd_spi_s* IO;
    uint8_t spi_optimized;                     // = true;
    uint8_t _buffer[GDEY0213B74_BUFFER_SIZE];  // for mono mode
    uint8_t _buffer1[GDEY0213B74_BUFFER_SIZE];
    uint8_t _buffer2[GDEY0213B74_BUFFER_SIZE];
    bool _initial;  // = true;
    bool _mono_mode;
} gdey0213b74_t;

void gdey0213b74_free(void* me);
void gdey0213b74_deinit(void*);
gdey0213b74_t* gdey0213b74_init(gdey0213b74_t*, struct epd_g_s* epd, bool debug);
gdey0213b74_t* gdey0213b74_new(struct epd_g_s* epd, bool debug);

#ifdef __cplusplus
}
#endif
#endif /* D7C5EC4E_95A3_47B4_A463_5DCC207C8C14 */
