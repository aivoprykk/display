#ifndef FE2867E9_4D0C_43F5_8ACB_37B55964A596
#define FE2867E9_4D0C_43F5_8ACB_37B55964A596

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct epd_g_s;

void update(void* _me);
void updateWindow(void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

void setRamDataEntryMode(const void* _me, uint8_t em);
static void SetRamArea(const void* _me, uint8_t Xstart, uint8_t Xend, uint8_t Ystart, uint8_t Ystart1, uint8_t Yend, uint8_t Yend1);
static void SetRamPointer(const void* _me, uint8_t addrX, uint8_t addrY, uint8_t addrY1);
void setPartialRamArea(const void* _me, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

static void PowerOn(void* _me);
static void PowerOff(void* _me);
static void powerDown(void* _me);
void powerDown(void* _me);

static void InitDisplay(void* _me, uint8_t em);
static void Init_Full(void* _me, uint8_t em);
static void Init_Part(void* _me, uint8_t em);

static void Update_Full(const void* _me);
static void Update_Part(const void* _me);

void _write_ram_part(const struct epd_g_s * epd, uint8_t em, uint16_t y, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t ys_m256, uint8_t ys_d256, uint8_t ye_m256, uint8_t ye_d256, bool runupdate_part, uint8_t * buf, uint16_t size);
void _write_ram_y_dec(const struct epd_g_s * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t x_d8, uint8_t * buf, uint16_t size);
void _write_ram_y_dec_array(const struct epd_g_s * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t x_d8, uint8_t * buf, uint16_t size);
void _write_ram_y_inc(const struct epd_g_s * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t x_d8, uint8_t * buf, uint16_t size);
void _write_ram_y_inc_array(const struct epd_g_s * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t x_d8, uint8_t * buf, uint16_t size);
void _write_ram_buf(const struct epd_g_s * epd, uint8_t em, uint8_t * buf, uint16_t size);
void _write_ram_buf_opt(const struct epd_g_s * epd, uint8_t em, uint8_t * buf, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* FE2867E9_4D0C_43F5_8ACB_37B55964A596 */