#include "epd_driver_private.h"
#include "epdg.h"

void _write_ram_buf(const epd_g_t * epd, uint8_t em, uint8_t * buf, uint16_t size) {
    epd->op->writeCommand(epd, em);
    int16_t i;
    for (i = 0; i < size; ++i) {
        epd->op->writeByte(epd, ~*(buf+i));
    }
}

void _write_ram_buf_opt(const epd_g_t * epd, uint8_t em, uint8_t * buf, uint16_t size) {
    epd->op->writeCommand(epd, em);
    epd->op->writeDataArray(epd, buf, size);
}

void _write_ram_y_dec(const epd_g_t * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t x_d8, uint8_t * buf, uint16_t size) {
    const uint8_t xLineBytes = x_d8;
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ye; y1 > ys; --y1) { // y decrease (height - 1 to 0)
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            epd->op->writeByte(epd, (idx < size) ? ~*(buf+idx) : 0x00);
        }
    }
}

void _write_ram_y_dec_array(const epd_g_t * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t x_d8, uint8_t * buf, uint16_t size) {
    const uint8_t xLineBytes = x_d8;
    uint8_t x1buf[xLineBytes];
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ye; y1 > ys; --y1) { // y decrease (height - 1 to 0)
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            x1buf[x1] = (idx < size) ? ~*(buf+idx) : 0x00;
        }
        epd->op->writeDataArray(epd, x1buf, sizeof(x1buf));
    }
}

void _write_ram_y_inc(const epd_g_t * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t x_d8, uint8_t * buf, uint16_t size) {
    const uint8_t xLineBytes = x_d8;
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ys; y1 < ye; ++y1) { // y increase (height - 0 to 1)
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            epd->op->writeByte(epd, (idx < size) ? ~*(buf+idx) : 0x00);
        }
    }
}

void _write_ram_y_inc_array(const epd_g_t * epd, uint8_t em, uint16_t ys, uint16_t ye, uint8_t xs_d8, uint8_t xe_d8, uint8_t x_d8, uint8_t * buf, uint16_t size) {
    const uint8_t xLineBytes = x_d8;
    uint8_t x1buf[xLineBytes];
    uint16_t idx;
    int16_t x1, y1;
    epd->op->writeCommand(epd, em);
    for (y1 = ys; y1 < ye; ++y1) { // y increase (height - 0 to 1)
        for (x1 = xs_d8; x1 <= xe_d8; ++x1) {
            idx = y1 * xLineBytes + x1;
            x1buf[x1] = (idx < size) ? ~*(buf+idx) : 0x00;
        }
        epd->op->writeDataArray(epd, x1buf, sizeof(x1buf));
    }
}
