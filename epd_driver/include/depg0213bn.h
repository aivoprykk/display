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
// Library: https://github.com/ZinggJM/GxEPD

#ifndef _DEPG0213_BN_H_
#define _DEPG0213_BN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

// the physical number of pixels (for controller parameter)
#define DEPG0213BN_X_PIXELS 128
#define DEPG0213BN_Y_PIXELS 250

#define DEPG0213BN_WIDTH DEPG0213BN_X_PIXELS
#define DEPG0213BN_HEIGHT DEPG0213BN_Y_PIXELS
#define DEPG0213BN_BUFFER_SIZE (((uint16_t)DEPG0213BN_WIDTH) * ((uint16_t)DEPG0213BN_HEIGHT) / 8)

// divisor for AVR, should be factor of DEPG0213BN_HEIGHT
#define DEPG0213BN_PAGES 5

#define DEPG0213BN_PAGE_HEIGHT (DEPG0213BN_HEIGHT / DEPG0213BN_PAGES)
#define DEPG0213BN_PAGE_SIZE (DEPG0213BN_BUFFER_SIZE / DEPG0213BN_PAGES)

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

typedef struct depg0213bn_s {
    struct epd_g_s* epd;
    //struct epd_spi_s* IO;
    bool spi_optimized;// = true;
    //SemaphoreHandle_t screen_lock;
    uint8_t bw_buf[DEPG0213BN_BUFFER_SIZE];
    uint8_t red_buf[DEPG0213BN_BUFFER_SIZE];
    bool _initial;  // = true;
    //const unsigned char* lut_partial;
} depg0213bn_t;

void depg0213bn_free(void* me);
void depg0213bn_deinit(void* me);
depg0213bn_t* depg0213bn_init(depg0213bn_t* me, struct epd_g_s* epd, bool debug);
depg0213bn_t* depg0213bn_new(struct epd_g_s* epd, bool debug);

#ifdef __cplusplus
}
#endif
#endif
