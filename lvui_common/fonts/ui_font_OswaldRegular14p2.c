/*******************************************************************************
 * Size: 14 px
 * Bpp: 2
 * Opts: --bpp 2 --size 14 --font /Users/aivo/Dropbox/gt31/squareline_proj_2_13_01/assets/Oswald-Regular.ttf -o /Users/aivo/Dropbox/gt31/squareline_proj_2_13_01/assets/ui_font_OswaldRegular14p2.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui_common.h"

#ifndef UI_FONT_OSWALDREGULAR14P2
#define UI_FONT_OSWALDREGULAR14P2 1
#endif

#if UI_FONT_OSWALDREGULAR14P2

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x70, 0xc3, 0xc, 0x30, 0xc3, 0x8, 0x10, 0x87,
    0x0,

    /* U+0022 "\"" */
    0xae, 0x9d, 0x8c, 0x44,

    /* U+0023 "#" */
    0xe, 0x34, 0x35, 0xc1, 0xcb, 0x2f, 0xfd, 0x2c,
    0xe0, 0xb3, 0x8b, 0xff, 0x4e, 0x74, 0x35, 0xc1,
    0xcb, 0x7, 0x2c, 0x0,

    /* U+0024 "$" */
    0x1, 0x0, 0xbf, 0x7, 0x4b, 0x1c, 0x1c, 0x74,
    0x0, 0xb8, 0x0, 0xb8, 0x0, 0x78, 0x10, 0x71,
    0xc0, 0xc3, 0x8b, 0x7, 0xf4, 0x1, 0x0,

    /* U+0025 "%" */
    0x2f, 0x43, 0x40, 0x72, 0xc7, 0x0, 0x71, 0xcb,
    0x0, 0x71, 0xcd, 0x0, 0x72, 0xcc, 0x0, 0x3f,
    0x5c, 0xbd, 0x0, 0x29, 0xdb, 0x0, 0x35, 0xc7,
    0x0, 0x31, 0xc7, 0x0, 0xb1, 0xcb, 0x0, 0xd0,
    0xbd,

    /* U+0026 "&" */
    0xb, 0xd0, 0x2d, 0xb0, 0x2c, 0x70, 0x2c, 0xe0,
    0xe, 0xc0, 0xb, 0x0, 0x1f, 0x8e, 0x39, 0xdd,
    0x34, 0xbc, 0x39, 0xbd, 0x1f, 0xca,

    /* U+0027 "'" */
    0xa9, 0x84,

    /* U+0028 "(" */
    0x29, 0xca, 0x38, 0xe3, 0x4d, 0x34, 0xd3, 0x8e,
    0x28, 0x70, 0xa0,

    /* U+0029 ")" */
    0xa0, 0x38, 0x2c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,
    0x1c, 0x1c, 0x1c, 0x2c, 0x38, 0xa0,

    /* U+002A "*" */
    0x9, 0x2, 0xa8, 0x1f, 0x41, 0xa4, 0x10, 0x40,

    /* U+002B "+" */
    0x4, 0x0, 0x90, 0x9, 0xb, 0xfd, 0xa, 0x0,
    0x90,

    /* U+002C "," */
    0x21, 0xc3, 0x4,

    /* U+002D "-" */
    0x7e, 0x0,

    /* U+002E "." */
    0x21, 0xc0,

    /* U+002F "/" */
    0x2, 0x80, 0xd0, 0x30, 0x2c, 0xe, 0x3, 0x1,
    0xc0, 0xa0, 0x34, 0xc, 0x7, 0x0,

    /* U+0030 "0" */
    0xf, 0xd0, 0xf2, 0xc3, 0x43, 0x4d, 0xd, 0x34,
    0x34, 0xd0, 0xd3, 0x43, 0x4d, 0xd, 0x34, 0x34,
    0xf2, 0xc0, 0xfd, 0x0,

    /* U+0031 "1" */
    0xb, 0xbf, 0xb, 0xb, 0xb, 0xb, 0xb, 0xb,
    0xb, 0xb, 0xb,

    /* U+0032 "2" */
    0x1f, 0xd0, 0xe2, 0xc3, 0x47, 0x8, 0x1c, 0x0,
    0xf0, 0x7, 0x0, 0x38, 0x3, 0xc0, 0x1c, 0x0,
    0xe0, 0x7, 0xff, 0x0,

    /* U+0033 "3" */
    0x1f, 0xd1, 0xe2, 0xc7, 0x7, 0x0, 0x2c, 0x3,
    0xc0, 0xb, 0x80, 0xb, 0x4, 0x1c, 0x70, 0x70,
    0xe7, 0xc1, 0xfc, 0x0,

    /* U+0034 "4" */
    0x2, 0xd0, 0xf, 0x40, 0xbd, 0x3, 0x74, 0x1c,
    0xd0, 0xe3, 0x47, 0xd, 0x1f, 0xfe, 0x1, 0xd0,
    0x3, 0x40, 0xd, 0x0,

    /* U+0035 "5" */
    0x3f, 0xf0, 0xe5, 0x43, 0x0, 0xc, 0x0, 0x3b,
    0xd0, 0xe2, 0xc0, 0x7, 0x0, 0x1c, 0x70, 0x70,
    0xe2, 0xc1, 0xfc, 0x0,

    /* U+0036 "6" */
    0xf, 0xd0, 0xf2, 0xc3, 0x42, 0xd, 0x0, 0x3b,
    0xd0, 0xe2, 0xc3, 0x43, 0x4d, 0xd, 0x34, 0x34,
    0xf6, 0xc0, 0xfd, 0x0,

    /* U+0037 "7" */
    0xbf, 0xc0, 0xe0, 0x34, 0xd, 0x7, 0x2, 0xc0,
    0xe0, 0x34, 0xd, 0x7, 0x2, 0xc0,

    /* U+0038 "8" */
    0x1f, 0xd0, 0xe2, 0xc3, 0x47, 0xe, 0x2c, 0xf,
    0xc0, 0xf7, 0xc3, 0x47, 0x1c, 0xd, 0x30, 0x30,
    0xe2, 0xc1, 0xfd, 0x0,

    /* U+0039 "9" */
    0x1f, 0xc0, 0xe3, 0xc7, 0x7, 0x1c, 0x1c, 0x34,
    0x70, 0xbf, 0xc0, 0x7, 0x0, 0x1c, 0x70, 0x70,
    0xe7, 0xc1, 0xfc, 0x0,

    /* U+003A ":" */
    0x34, 0x80, 0x0, 0x20, 0xd0,

    /* U+003B ";" */
    0x34, 0x80, 0x0, 0x0, 0x83, 0x45, 0x20,

    /* U+003C "<" */
    0x0, 0x2, 0xd7, 0xd2, 0xc0, 0x2f, 0x0, 0x90,
    0x0,

    /* U+003D "=" */
    0x3f, 0xc0, 0x0, 0x3f, 0xc0, 0x0,

    /* U+003E ">" */
    0x0, 0xe, 0x1, 0xf8, 0xf, 0x2e, 0xd, 0x0,
    0x0,

    /* U+003F "?" */
    0x1f, 0xc0, 0xe7, 0xc7, 0x7, 0x0, 0x1c, 0x0,
    0xf0, 0xb, 0x0, 0xb0, 0x3, 0x80, 0x0, 0x0,
    0x14, 0x0, 0xe0, 0x0,

    /* U+0040 "@" */
    0x0, 0x7f, 0xd0, 0x0, 0xf4, 0x1e, 0x0, 0xf0,
    0x0, 0xd0, 0x70, 0x7f, 0x5c, 0x38, 0x35, 0xc3,
    0xd, 0x28, 0x70, 0xc3, 0xd, 0x2c, 0x30, 0xc3,
    0x4a, 0x18, 0x34, 0xe7, 0x8c, 0xe, 0x1e, 0x7d,
    0x1, 0xc0, 0x0, 0x0, 0x2d, 0x0, 0x0, 0x1,
    0xff, 0xd0, 0x0, 0x0, 0x0, 0x0,

    /* U+0041 "A" */
    0x7, 0x40, 0x2e, 0x0, 0xfc, 0x3, 0x70, 0x1c,
    0xc0, 0xb3, 0x43, 0x8a, 0xf, 0xfc, 0x34, 0x71,
    0xc0, 0xdb, 0x3, 0x80,

    /* U+0042 "B" */
    0x3f, 0xd0, 0xe1, 0xc3, 0x43, 0x4d, 0xd, 0x34,
    0x70, 0xff, 0x83, 0x87, 0x4d, 0xf, 0x34, 0x2c,
    0xe1, 0xe3, 0xfe, 0x0,

    /* U+0043 "C" */
    0x1f, 0xe0, 0xf1, 0xd3, 0x43, 0x9d, 0xe, 0x74,
    0x1, 0xd0, 0x7, 0x40, 0x1d, 0xe, 0x34, 0x38,
    0xf5, 0xd0, 0xfe, 0x0,

    /* U+0044 "D" */
    0x3f, 0xe0, 0xe1, 0xd3, 0x43, 0x8d, 0xe, 0x34,
    0x38, 0xd0, 0xe3, 0x43, 0x8d, 0xe, 0x34, 0x38,
    0xe1, 0xd3, 0xfd, 0x0,

    /* U+0045 "E" */
    0x3f, 0xd3, 0x80, 0x34, 0x3, 0x40, 0x34, 0x3,
    0xf8, 0x38, 0x3, 0x40, 0x34, 0x3, 0x80, 0x3f,
    0xd0,

    /* U+0046 "F" */
    0x3f, 0xd3, 0x80, 0x34, 0x3, 0x40, 0x34, 0x3,
    0xf8, 0x38, 0x3, 0x40, 0x34, 0x3, 0x40, 0x34,
    0x0,

    /* U+0047 "G" */
    0x1f, 0xe0, 0xf1, 0xd3, 0x43, 0x9d, 0x0, 0x74,
    0x1, 0xd3, 0xe7, 0x42, 0xdd, 0xb, 0x34, 0x3c,
    0xf5, 0xf0, 0xfd, 0xc0,

    /* U+0048 "H" */
    0x34, 0x2c, 0xd0, 0xb3, 0x42, 0xcd, 0xb, 0x34,
    0x2c, 0xff, 0xf3, 0x82, 0xcd, 0xb, 0x34, 0x2c,
    0xd0, 0xb3, 0x42, 0xc0,

    /* U+0049 "I" */
    0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe3,
    0x80,

    /* U+004A "J" */
    0x1d, 0x1d, 0x1d, 0x1d, 0x1d, 0x1d, 0x1d, 0x1d,
    0x1d, 0x2c, 0xf8,

    /* U+004B "K" */
    0x34, 0x34, 0xd2, 0xc3, 0x4d, 0xd, 0xb0, 0x3b,
    0x40, 0xfe, 0x3, 0xec, 0xd, 0x34, 0x34, 0xb0,
    0xd1, 0xd3, 0x43, 0x80,

    /* U+004C "L" */
    0x34, 0x3, 0x40, 0x34, 0x3, 0x40, 0x34, 0x3,
    0x40, 0x34, 0x3, 0x40, 0x34, 0x3, 0x80, 0x3f,
    0xd0,

    /* U+004D "M" */
    0x38, 0x7, 0xf, 0x2, 0xc3, 0xc0, 0xf0, 0xf4,
    0x3c, 0x3a, 0x1b, 0x4d, 0xc9, 0xd3, 0x33, 0x34,
    0xc9, 0xcd, 0x31, 0xe3, 0x4c, 0x34, 0xd3, 0xc,
    0x34,

    /* U+004E "N" */
    0x30, 0x38, 0xe0, 0xe3, 0xc3, 0x8f, 0x8e, 0x3b,
    0x38, 0xcd, 0xe3, 0x1f, 0x8c, 0x3e, 0x30, 0xb8,
    0xc0, 0xe3, 0x2, 0x80,

    /* U+004F "O" */
    0xf, 0xe0, 0xf1, 0xe7, 0x43, 0xdd, 0xb, 0x74,
    0x2d, 0xd0, 0xb7, 0x42, 0xdd, 0xb, 0x34, 0x3c,
    0xf5, 0xd0, 0xfe, 0x0,

    /* U+0050 "P" */
    0x3f, 0xd0, 0xe1, 0xc3, 0x43, 0x4d, 0xd, 0x34,
    0x74, 0xff, 0x83, 0x80, 0xd, 0x0, 0x34, 0x0,
    0xd0, 0x3, 0x40, 0x0,

    /* U+0051 "Q" */
    0xf, 0xe0, 0xf1, 0xe7, 0x43, 0xdd, 0xb, 0x74,
    0x2d, 0xd0, 0xb7, 0x42, 0xdd, 0xb, 0x34, 0x3c,
    0xf5, 0xd0, 0xfe, 0x0, 0x2c, 0x0, 0x20, 0x0,
    0x0,

    /* U+0052 "R" */
    0x3f, 0xd0, 0xe2, 0xc3, 0x43, 0x4d, 0xd, 0x34,
    0x74, 0xff, 0x83, 0x9d, 0xd, 0x38, 0x34, 0xb0,
    0xd1, 0xc3, 0x43, 0x80,

    /* U+0053 "S" */
    0x1f, 0xc0, 0xd3, 0xc7, 0x7, 0x1d, 0x0, 0x2e,
    0x0, 0x2e, 0x0, 0x1e, 0x4, 0x1c, 0x70, 0x34,
    0xe2, 0xc1, 0xfd, 0x0,

    /* U+0054 "T" */
    0xff, 0xe0, 0xf0, 0xe, 0x0, 0xe0, 0xe, 0x0,
    0xe0, 0xe, 0x0, 0xe0, 0xe, 0x0, 0xe0, 0xe,
    0x0,

    /* U+0055 "U" */
    0x34, 0x2c, 0xd0, 0xb3, 0x42, 0xcd, 0xb, 0x34,
    0x2c, 0xd0, 0xb3, 0x42, 0xcd, 0xb, 0x34, 0x38,
    0xf5, 0xd0, 0xfe, 0x0,

    /* U+0056 "V" */
    0xb0, 0x39, 0xc0, 0xd3, 0x43, 0xe, 0x1c, 0x2c,
    0xa0, 0x73, 0x40, 0xdd, 0x3, 0xb0, 0xb, 0xc0,
    0x1e, 0x0, 0x74, 0x0,

    /* U+0057 "W" */
    0x70, 0xb0, 0xa3, 0xb, 0xd, 0x30, 0xf0, 0xd3,
    0x4f, 0x4c, 0x29, 0xe9, 0xc2, 0xa9, 0x9c, 0x1e,
    0x4e, 0x80, 0xf0, 0xf4, 0xf, 0xf, 0x40, 0xf0,
    0xb0, 0xa, 0x7, 0x0,

    /* U+0058 "X" */
    0xb0, 0x30, 0xd2, 0xc2, 0xcd, 0x3, 0xb0, 0xf,
    0x40, 0x2c, 0x0, 0xf8, 0x7, 0xb0, 0x38, 0xd0,
    0xc2, 0xcb, 0x3, 0x40,

    /* U+0059 "Y" */
    0xb0, 0x35, 0xc1, 0xc3, 0x4a, 0xb, 0x34, 0x1d,
    0xc0, 0x3e, 0x0, 0xb4, 0x1, 0xc0, 0x7, 0x0,
    0x1c, 0x0, 0x70, 0x0,

    /* U+005A "Z" */
    0x7f, 0xe0, 0x1c, 0x2, 0xc0, 0x34, 0x7, 0x0,
    0xe0, 0xd, 0x2, 0xc0, 0x38, 0x7, 0x40, 0x7f,
    0xe0,

    /* U+005B "[" */
    0x3e, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
    0x34, 0x34, 0x34, 0x34, 0x3e,

    /* U+005C "\\" */
    0x70, 0xc, 0x3, 0x40, 0xa0, 0x1c, 0x3, 0x0,
    0xe0, 0x2c, 0x3, 0x0, 0xd0, 0x28,

    /* U+005D "]" */
    0x7d, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd,
    0xd, 0xd, 0xd, 0xd, 0x7d,

    /* U+005E "^" */
    0x5, 0x0, 0xf4, 0x1e, 0x83, 0x4c, 0x70, 0xe0,

    /* U+005F "_" */
    0xff, 0xc0, 0x0,

    /* U+0060 "`" */
    0x10, 0x28, 0xc,

    /* U+0061 "a" */
    0x2f, 0x47, 0x2c, 0x51, 0xc0, 0xbc, 0x39, 0xcb,
    0x1c, 0xb7, 0xc3, 0xdc,

    /* U+0062 "b" */
    0x34, 0x3, 0x40, 0x34, 0x3, 0xbc, 0x38, 0xd3,
    0x4e, 0x34, 0xe3, 0x4e, 0x34, 0xe3, 0x4d, 0x3b,
    0xc0,

    /* U+0063 "c" */
    0x2f, 0x83, 0x5c, 0x70, 0xc7, 0x0, 0x70, 0x7,
    0xc, 0x35, 0xc2, 0xf8,

    /* U+0064 "d" */
    0x0, 0xd0, 0xd, 0x0, 0xd2, 0xed, 0x35, 0xd7,
    0xd, 0x70, 0xd7, 0xd, 0x70, 0xd3, 0x5d, 0x2e,
    0xd0,

    /* U+0065 "e" */
    0x2f, 0x83, 0x5c, 0x70, 0xd7, 0xfd, 0x70, 0x7,
    0xc, 0x35, 0xc2, 0xf8,

    /* U+0066 "f" */
    0x1f, 0x2c, 0x38, 0xbf, 0x3c, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38,

    /* U+0067 "g" */
    0x0, 0x0, 0xbd, 0xc3, 0x1c, 0x1c, 0x30, 0x71,
    0xc0, 0xfe, 0x3, 0x0, 0xf, 0xf0, 0x71, 0xa2,
    0xc2, 0x83, 0xfc, 0x0,

    /* U+0068 "h" */
    0x34, 0x3, 0x40, 0x34, 0x3, 0xbc, 0x38, 0xe3,
    0x4e, 0x34, 0xe3, 0x4e, 0x34, 0xe3, 0x4e, 0x34,
    0xe0,

    /* U+0069 "i" */
    0x34, 0x80, 0xd, 0x34, 0xd3, 0x4d, 0x34, 0xd3,
    0x40,

    /* U+006A "j" */
    0xd, 0x9, 0x0, 0xd, 0xd, 0xd, 0xd, 0xd,
    0xd, 0xd, 0xd, 0x1d, 0x7c,

    /* U+006B "k" */
    0x34, 0x0, 0xd0, 0x3, 0x40, 0xd, 0x38, 0x35,
    0xc0, 0xde, 0x3, 0xf4, 0xe, 0xe0, 0x35, 0xc0,
    0xd3, 0x43, 0x4b, 0x0,

    /* U+006C "l" */
    0x34, 0xd3, 0x4d, 0x34, 0xd3, 0x4d, 0x34, 0xd3,
    0x40,

    /* U+006D "m" */
    0x7b, 0xdb, 0x5d, 0x38, 0xb7, 0xd, 0x2d, 0xc3,
    0x4b, 0x70, 0xd2, 0xdc, 0x34, 0xb7, 0xd, 0x2d,
    0xc3, 0x4b,

    /* U+006E "n" */
    0x7b, 0xc7, 0x4d, 0x74, 0xd7, 0x4d, 0x74, 0xd7,
    0x4d, 0x74, 0xd7, 0x4d,

    /* U+006F "o" */
    0x2f, 0x83, 0x5c, 0x70, 0xd7, 0xd, 0x70, 0xd7,
    0xd, 0x35, 0xc2, 0xf8,

    /* U+0070 "p" */
    0x7b, 0xc7, 0x4d, 0x74, 0xe7, 0x4e, 0x74, 0xe7,
    0x4e, 0x74, 0xd7, 0xbc, 0x74, 0x7, 0x40,

    /* U+0071 "q" */
    0x2e, 0xd3, 0x5d, 0x70, 0xd7, 0xd, 0x70, 0xd7,
    0xd, 0x35, 0xd2, 0xed, 0x0, 0xd0, 0xd,

    /* U+0072 "r" */
    0x3b, 0x4f, 0x43, 0x40, 0xd0, 0x34, 0xd, 0x3,
    0x40, 0xd0,

    /* U+0073 "s" */
    0x2f, 0x1c, 0xa7, 0x0, 0xb4, 0xb, 0x44, 0xb7,
    0x2c, 0xbd,

    /* U+0074 "t" */
    0x14, 0x38, 0x38, 0xbf, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x3c, 0x1f,

    /* U+0075 "u" */
    0x70, 0xd7, 0xd, 0x70, 0xd7, 0xd, 0x70, 0xd7,
    0xd, 0x75, 0xd3, 0xed,

    /* U+0076 "v" */
    0xb1, 0xc7, 0x2c, 0x72, 0x83, 0x78, 0x37, 0x42,
    0xb0, 0x1f, 0x1, 0xe0,

    /* U+0077 "w" */
    0xa2, 0xc7, 0x72, 0xca, 0x33, 0xcd, 0x33, 0x9d,
    0x3a, 0x6c, 0x2e, 0x7c, 0x2d, 0x3c, 0x1c, 0x38,

    /* U+0078 "x" */
    0xb1, 0xc3, 0x78, 0x2f, 0x0, 0xe0, 0x1e, 0x3,
    0xf0, 0x33, 0x8a, 0x1c,

    /* U+0079 "y" */
    0xb1, 0xc7, 0x1c, 0x32, 0xc3, 0x78, 0x3b, 0x42,
    0xf0, 0x1f, 0x0, 0xe0, 0xd, 0x7, 0x80,

    /* U+007A "z" */
    0x7f, 0x81, 0xc0, 0xb0, 0x34, 0x2c, 0xe, 0x7,
    0x42, 0xfd,

    /* U+007B "{" */
    0x1f, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x74, 0x3c,
    0x2c, 0x2c, 0x2c, 0x2c, 0x1f,

    /* U+007C "|" */
    0x34, 0xd3, 0x4d, 0x34, 0xd3, 0x4d, 0x34, 0xd3,
    0x4d, 0x34,

    /* U+007D "}" */
    0x78, 0x2c, 0x1c, 0x1c, 0x1c, 0x1c, 0xf, 0x1d,
    0x1c, 0x1c, 0x1c, 0x2c, 0x78,

    /* U+007E "~" */
    0x2d, 0x11, 0x7d, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 51, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 47, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 60, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 13, .adv_w = 109, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 110, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 56, .adv_w = 200, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 136, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 28, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 113, .adv_w = 67, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 124, .adv_w = 58, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 138, .adv_w = 89, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 146, .adv_w = 93, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 155, .adv_w = 42, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 158, .adv_w = 68, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 160, .adv_w = 42, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 83, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 116, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 85, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 107, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 107, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 108, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 107, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 113, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 86, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 112, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 112, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 44, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 366, .adv_w = 48, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 373, .adv_w = 84, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 382, .adv_w = 93, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 388, .adv_w = 84, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 397, .adv_w = 108, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 202, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 463, .adv_w = 110, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 117, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 115, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 118, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 91, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 88, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 120, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 617, .adv_w = 56, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 67, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 637, .adv_w = 111, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 89, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 148, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 118, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 739, .adv_w = 108, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 759, .adv_w = 121, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 784, .adv_w = 116, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 106, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 93, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 841, .adv_w = 122, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 861, .adv_w = 113, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 881, .adv_w = 163, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 909, .adv_w = 108, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 929, .adv_w = 108, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 949, .adv_w = 93, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 966, .adv_w = 76, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 979, .adv_w = 83, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 993, .adv_w = 69, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1006, .adv_w = 99, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1014, .adv_w = 77, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1017, .adv_w = 62, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1020, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1032, .adv_w = 100, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1049, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1061, .adv_w = 99, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1078, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1090, .adv_w = 64, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1101, .adv_w = 99, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1121, .adv_w = 100, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1138, .adv_w = 51, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1147, .adv_w = 52, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1160, .adv_w = 96, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1180, .adv_w = 51, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1189, .adv_w = 152, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1207, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1219, .adv_w = 95, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1231, .adv_w = 100, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1246, .adv_w = 99, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1261, .adv_w = 72, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1271, .adv_w = 84, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1281, .adv_w = 69, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1292, .adv_w = 99, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1304, .adv_w = 86, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1316, .adv_w = 132, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1332, .adv_w = 87, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1344, .adv_w = 88, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1359, .adv_w = 78, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1369, .adv_w = 67, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1382, .adv_w = 54, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1392, .adv_w = 72, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1405, .adv_w = 100, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    3, 34,
    3, 36,
    3, 40,
    3, 43,
    3, 48,
    3, 50,
    3, 66,
    3, 68,
    3, 69,
    3, 70,
    3, 72,
    3, 80,
    3, 82,
    3, 84,
    7, 53,
    8, 34,
    8, 36,
    8, 40,
    8, 43,
    8, 48,
    8, 50,
    8, 66,
    8, 68,
    8, 69,
    8, 70,
    8, 72,
    8, 80,
    8, 82,
    8, 84,
    11, 43,
    11, 57,
    13, 35,
    13, 36,
    13, 37,
    13, 38,
    13, 39,
    13, 40,
    13, 41,
    13, 42,
    13, 44,
    13, 45,
    13, 47,
    13, 48,
    13, 49,
    13, 50,
    13, 51,
    13, 53,
    13, 54,
    13, 55,
    13, 56,
    13, 58,
    13, 68,
    13, 69,
    13, 70,
    13, 80,
    13, 82,
    13, 85,
    13, 87,
    13, 88,
    13, 90,
    14, 53,
    14, 55,
    14, 56,
    14, 57,
    14, 58,
    15, 35,
    15, 36,
    15, 37,
    15, 38,
    15, 39,
    15, 40,
    15, 41,
    15, 42,
    15, 44,
    15, 45,
    15, 47,
    15, 48,
    15, 49,
    15, 50,
    15, 51,
    15, 53,
    15, 54,
    15, 55,
    15, 56,
    15, 58,
    15, 68,
    15, 69,
    15, 70,
    15, 80,
    15, 82,
    15, 85,
    15, 87,
    15, 88,
    15, 90,
    16, 36,
    16, 40,
    16, 48,
    16, 50,
    16, 52,
    16, 68,
    16, 69,
    16, 70,
    16, 80,
    16, 82,
    17, 24,
    17, 57,
    17, 58,
    18, 24,
    19, 21,
    21, 18,
    21, 24,
    22, 24,
    23, 18,
    23, 19,
    23, 24,
    23, 26,
    23, 58,
    24, 21,
    25, 24,
    25, 58,
    26, 24,
    27, 53,
    27, 55,
    27, 56,
    27, 58,
    28, 53,
    28, 55,
    28, 56,
    28, 58,
    34, 3,
    34, 8,
    34, 36,
    34, 40,
    34, 48,
    34, 52,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 58,
    34, 71,
    34, 85,
    34, 87,
    34, 88,
    34, 90,
    35, 3,
    35, 8,
    35, 13,
    35, 15,
    35, 34,
    35, 53,
    35, 55,
    35, 56,
    35, 57,
    35, 58,
    36, 3,
    36, 8,
    36, 13,
    36, 15,
    36, 57,
    36, 58,
    37, 3,
    37, 8,
    37, 13,
    37, 15,
    37, 24,
    37, 34,
    37, 43,
    37, 53,
    37, 55,
    37, 57,
    37, 58,
    37, 59,
    37, 61,
    38, 68,
    38, 69,
    38, 70,
    38, 72,
    38, 80,
    38, 82,
    38, 84,
    39, 3,
    39, 8,
    39, 13,
    39, 15,
    39, 27,
    39, 28,
    39, 34,
    39, 43,
    39, 52,
    39, 66,
    39, 68,
    39, 69,
    39, 70,
    39, 72,
    39, 80,
    39, 82,
    39, 84,
    39, 89,
    39, 90,
    39, 91,
    40, 3,
    40, 8,
    40, 53,
    40, 55,
    40, 56,
    40, 58,
    43, 13,
    43, 15,
    44, 14,
    44, 36,
    44, 40,
    44, 48,
    44, 50,
    44, 52,
    44, 54,
    44, 66,
    44, 68,
    44, 69,
    44, 70,
    44, 72,
    44, 80,
    44, 82,
    44, 84,
    44, 85,
    44, 86,
    44, 87,
    44, 88,
    44, 90,
    45, 3,
    45, 8,
    45, 11,
    45, 14,
    45, 18,
    45, 24,
    45, 36,
    45, 40,
    45, 48,
    45, 50,
    45, 52,
    45, 53,
    45, 54,
    45, 55,
    45, 56,
    45, 58,
    45, 61,
    45, 68,
    45, 69,
    45, 70,
    45, 71,
    45, 72,
    45, 80,
    45, 82,
    45, 84,
    45, 85,
    45, 88,
    45, 90,
    46, 52,
    46, 53,
    46, 55,
    46, 58,
    48, 3,
    48, 8,
    48, 13,
    48, 15,
    48, 24,
    48, 34,
    48, 43,
    48, 53,
    48, 55,
    48, 57,
    48, 58,
    48, 59,
    48, 61,
    49, 13,
    49, 14,
    49, 15,
    49, 16,
    49, 21,
    49, 24,
    49, 34,
    49, 43,
    49, 52,
    49, 57,
    49, 59,
    49, 61,
    49, 66,
    49, 68,
    49, 69,
    49, 70,
    49, 72,
    49, 78,
    49, 79,
    49, 80,
    49, 82,
    49, 83,
    49, 84,
    49, 91,
    50, 3,
    50, 8,
    50, 13,
    50, 15,
    50, 24,
    50, 34,
    50, 43,
    50, 53,
    50, 55,
    50, 57,
    50, 58,
    50, 59,
    50, 61,
    51, 36,
    51, 40,
    51, 48,
    51, 50,
    51, 52,
    51, 53,
    51, 54,
    51, 55,
    51, 56,
    51, 58,
    51, 61,
    51, 66,
    51, 68,
    51, 69,
    51, 70,
    51, 80,
    51, 82,
    51, 88,
    51, 90,
    51, 91,
    52, 16,
    52, 34,
    52, 46,
    52, 52,
    52, 55,
    52, 57,
    52, 58,
    52, 61,
    53, 7,
    53, 13,
    53, 14,
    53, 15,
    53, 16,
    53, 27,
    53, 28,
    53, 34,
    53, 36,
    53, 40,
    53, 43,
    53, 46,
    53, 48,
    53, 50,
    53, 66,
    53, 68,
    53, 69,
    53, 70,
    53, 71,
    53, 72,
    53, 75,
    53, 78,
    53, 79,
    53, 80,
    53, 81,
    53, 82,
    53, 83,
    53, 84,
    53, 85,
    53, 86,
    53, 88,
    53, 89,
    53, 90,
    53, 91,
    54, 13,
    54, 15,
    54, 16,
    54, 34,
    55, 13,
    55, 14,
    55, 15,
    55, 16,
    55, 27,
    55, 28,
    55, 34,
    55, 36,
    55, 40,
    55, 43,
    55, 46,
    55, 48,
    55, 50,
    55, 52,
    55, 66,
    55, 68,
    55, 69,
    55, 70,
    55, 72,
    55, 78,
    55, 79,
    55, 80,
    55, 81,
    55, 82,
    55, 83,
    55, 84,
    55, 85,
    55, 86,
    55, 87,
    55, 88,
    55, 89,
    55, 90,
    55, 91,
    56, 13,
    56, 14,
    56, 15,
    56, 16,
    56, 27,
    56, 28,
    56, 34,
    56, 36,
    56, 40,
    56, 48,
    56, 50,
    56, 52,
    56, 61,
    56, 66,
    56, 68,
    56, 69,
    56, 70,
    56, 71,
    56, 72,
    56, 78,
    56, 79,
    56, 80,
    56, 81,
    56, 82,
    56, 83,
    56, 84,
    56, 87,
    56, 88,
    56, 89,
    56, 91,
    57, 11,
    57, 14,
    57, 17,
    57, 36,
    57, 40,
    57, 48,
    57, 50,
    57, 52,
    57, 61,
    57, 66,
    57, 68,
    57, 69,
    57, 70,
    57, 71,
    57, 72,
    57, 80,
    57, 82,
    57, 84,
    57, 85,
    57, 87,
    57, 88,
    57, 90,
    58, 13,
    58, 14,
    58, 15,
    58, 16,
    58, 17,
    58, 21,
    58, 23,
    58, 25,
    58, 27,
    58, 28,
    58, 34,
    58, 36,
    58, 40,
    58, 43,
    58, 46,
    58, 48,
    58, 50,
    58, 52,
    58, 66,
    58, 68,
    58, 69,
    58, 70,
    58, 71,
    58, 72,
    58, 78,
    58, 79,
    58, 80,
    58, 81,
    58, 82,
    58, 83,
    58, 84,
    58, 86,
    58, 88,
    58, 89,
    58, 90,
    58, 91,
    59, 36,
    59, 40,
    59, 48,
    59, 50,
    59, 52,
    59, 66,
    59, 68,
    59, 69,
    59, 70,
    59, 80,
    59, 82,
    61, 36,
    61, 40,
    61, 48,
    61, 50,
    61, 52,
    61, 53,
    61, 54,
    61, 55,
    61, 56,
    61, 58,
    66, 3,
    66, 8,
    66, 53,
    66, 55,
    66, 56,
    66, 58,
    66, 85,
    66, 87,
    66, 88,
    66, 90,
    67, 3,
    67, 8,
    67, 13,
    67, 15,
    67, 53,
    67, 55,
    67, 56,
    67, 58,
    67, 72,
    67, 75,
    67, 88,
    67, 89,
    68, 3,
    68, 8,
    68, 13,
    68, 15,
    68, 53,
    68, 56,
    68, 58,
    68, 68,
    68, 69,
    68, 70,
    68, 75,
    68, 80,
    68, 82,
    69, 53,
    69, 55,
    69, 56,
    69, 58,
    70, 3,
    70, 8,
    70, 53,
    70, 55,
    70, 56,
    70, 58,
    70, 75,
    70, 88,
    70, 89,
    71, 15,
    71, 27,
    71, 28,
    71, 34,
    71, 66,
    71, 68,
    71, 69,
    71, 70,
    71, 71,
    71, 74,
    71, 75,
    71, 80,
    71, 82,
    71, 86,
    72, 53,
    72, 55,
    72, 57,
    72, 58,
    72, 59,
    72, 68,
    72, 69,
    72, 70,
    72, 72,
    72, 75,
    72, 80,
    72, 82,
    72, 85,
    72, 86,
    72, 88,
    72, 90,
    73, 3,
    73, 8,
    73, 53,
    73, 55,
    73, 56,
    73, 58,
    76, 3,
    76, 8,
    76, 53,
    76, 56,
    76, 58,
    76, 68,
    76, 69,
    76, 70,
    76, 72,
    76, 80,
    76, 82,
    76, 84,
    78, 3,
    78, 8,
    78, 53,
    78, 55,
    78, 56,
    78, 58,
    79, 3,
    79, 8,
    79, 53,
    79, 55,
    79, 56,
    79, 58,
    80, 3,
    80, 8,
    80, 13,
    80, 15,
    80, 53,
    80, 55,
    80, 56,
    80, 58,
    80, 72,
    80, 75,
    80, 88,
    80, 89,
    81, 3,
    81, 8,
    81, 13,
    81, 15,
    81, 53,
    81, 55,
    81, 56,
    81, 58,
    81, 72,
    81, 75,
    81, 88,
    81, 89,
    82, 3,
    82, 8,
    82, 53,
    82, 55,
    82, 58,
    83, 13,
    83, 15,
    83, 34,
    83, 43,
    83, 53,
    83, 57,
    83, 58,
    83, 59,
    83, 66,
    83, 68,
    83, 69,
    83, 70,
    83, 72,
    83, 80,
    83, 82,
    84, 3,
    84, 8,
    84, 53,
    84, 55,
    84, 56,
    84, 57,
    84, 58,
    85, 3,
    85, 8,
    85, 52,
    85, 53,
    85, 55,
    85, 58,
    85, 72,
    86, 3,
    86, 8,
    86, 53,
    86, 55,
    86, 56,
    86, 58,
    87, 13,
    87, 15,
    87, 34,
    87, 43,
    87, 53,
    87, 55,
    87, 56,
    87, 57,
    87, 58,
    87, 59,
    87, 66,
    87, 72,
    88, 13,
    88, 15,
    88, 34,
    88, 43,
    88, 53,
    88, 55,
    88, 56,
    88, 57,
    88, 58,
    88, 59,
    88, 66,
    88, 72,
    89, 53,
    89, 55,
    89, 56,
    89, 58,
    89, 68,
    89, 69,
    89, 70,
    89, 80,
    89, 82,
    90, 13,
    90, 15,
    90, 34,
    90, 43,
    90, 53,
    90, 55,
    90, 56,
    90, 57,
    90, 58,
    90, 59,
    90, 66,
    90, 72,
    91, 53,
    91, 55,
    91, 56,
    91, 58,
    91, 68,
    91, 69,
    91, 70,
    91, 72,
    91, 80,
    91, 82
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -14, -2, -2, -7, -2, -2, -3, -5,
    -5, -5, -7, -5, -5, -3, -3, -14,
    -2, -2, -7, -2, -2, -3, -5, -5,
    -5, -7, -5, -5, -3, -2, -2, -1,
    -2, -1, -1, -1, -2, -1, -1, -1,
    -1, -1, -2, -1, -2, -1, -12, -2,
    -10, -8, -15, -2, -2, -2, -2, -2,
    -2, -4, -2, -2, -4, -6, -1, -2,
    -4, -1, -2, -1, -1, -1, -2, -1,
    -1, -1, -1, -1, -2, -1, -2, -1,
    -12, -2, -10, -8, -15, -2, -2, -2,
    -2, -2, -2, -4, -2, -2, -2, -2,
    -2, -2, -2, -4, -4, -4, -4, -4,
    -2, -1, -2, -3, -2, -2, -4, -2,
    -1, -1, -2, -1, -1, -7, -3, -1,
    -3, -14, -2, -2, -10, -14, -2, -2,
    -10, -14, -14, -1, -1, -1, -1, -9,
    -1, -9, -6, -9, -4, -2, -2, -4,
    -3, -3, -3, -2, -2, 0, -5, -6,
    0, -5, -2, -2, -2, -1, -1, -1,
    0, -2, -2, -2, -2, -1, -1, -1,
    -1, -1, -2, -2, -1, -3, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -14,
    -14, -3, -3, -8, -7, 0, -4, -3,
    -3, -3, -2, -3, -3, -4, -2, -2,
    -3, -2, -2, -3, -2, 0, -3, -6,
    -6, -2, -4, -4, -4, -2, -2, 0,
    -1, -3, -3, -3, -1, -3, -3, -1,
    -2, 0, -1, -3, -6, -6, -6, -10,
    -4, -3, -1, -1, -1, -1, -2, -1,
    -17, -2, -16, -11, -20, -7, -1, -1,
    -1, -3, -1, -1, -1, -1, -2, -7,
    -11, -1, -2, -1, -1, -2, -2, -2,
    -2, -1, -1, -1, -1, -1, -2, -2,
    -1, -3, -23, -19, -25, -12, -6, -1,
    -10, -5, -1, -2, -6, -2, -6, -4,
    -4, -4, -4, -2, -2, -4, 0, -2,
    -2, -2, -2, -2, -2, -2, -1, -1,
    -1, -1, -1, -2, -2, -1, -3, -1,
    -1, -1, -1, 0, -3, 0, -1, -1,
    -3, -2, -2, -2, -2, -2, -2, -2,
    -2, -1, -2, -2, -1, -1, -2, -1,
    -1, -1, -3, -1, -12, -4, -12, -4,
    -14, -14, -9, -1, -1, -5, -2, -1,
    -1, -15, -14, -14, -14, -7, -15, -3,
    -13, -13, -14, -13, 0, -13, -15, -4,
    -11, -14, -11, -13, -12, -2, -2, -2,
    -1, -11, -6, -11, -2, -2, -2, -9,
    -1, -1, -4, -1, -1, -1, 0, -13,
    -9, -9, -9, -11, -4, -4, -9, -7,
    -7, -4, -9, -2, -6, -4, -4, -4,
    -7, -9, -8, -1, -8, -3, -2, -2,
    -6, 0, 0, 0, 0, 0, -2, -9,
    -6, -6, -6, -1, -5, -3, -3, -6,
    -2, 0, -3, -3, -2, -2, -2, -2,
    -2, -2, -1, -2, -2, -2, -2, -1,
    -2, -2, -2, -2, -2, -4, -2, -2,
    -2, -4, -4, -4, -7, -7, -15, -4,
    -15, -4, -2, -2, -1, -1, -11, -11,
    -9, -2, -2, -4, -1, -2, -2, -1,
    -16, -13, -13, -13, -6, -13, -11, -11,
    -13, -9, -3, -11, -11, -10, -8, -9,
    -7, -6, -1, -1, -1, -1, 0, -1,
    -1, -1, -1, -1, -1, -2, -2, -2,
    -2, -2, -4, -2, -4, -4, -4, -6,
    -6, -13, -11, -7, -15, 0, -1, -1,
    0, -5, -5, -2, -2, -14, -9, -6,
    -13, 0, -1, 0, -3, -4, -4, 0,
    0, -11, 0, -9, -1, -1, -1, -1,
    -1, -1, 7, 2, 2, 4, -2, -2,
    -14, -7, -2, -12, -1, 0, -2, -3,
    -1, -1, -1, -2, -4, -4, -4, -7,
    -2, -2, -4, -4, -2, -8, -2, -4,
    -2, -2, -1, -1, -1, -2, 2, -1,
    -1, 1, 0, 1, 1, -7, -7, -13,
    -6, -3, -11, -2, -2, -7, -1, -6,
    -1, -1, -1, -1, -1, -1, -1, -7,
    -7, -13, -6, -3, -11, -7, -7, -13,
    -6, -3, -11, -5, -5, -2, -2, -14,
    -9, -6, -13, 0, -1, 0, -3, -5,
    -5, -2, -2, -14, -9, -6, -13, 0,
    -1, 0, -3, -2, -2, -11, -5, -8,
    -16, -16, -6, -2, -12, -4, -4, -4,
    -2, -1, -1, -1, -1, -1, -2, -3,
    -3, -14, -9, -2, -2, -13, -3, -3,
    0, -6, -2, -2, -1, -2, -2, -12,
    -4, -1, -10, -4, -4, -4, -2, -16,
    -4, -2, -4, -7, -4, -1, -1, -3,
    -4, -3, -7, -14, -4, -2, -7, -7,
    -2, -1, -1, -11, -4, -2, -9, -3,
    -3, -3, -3, -3, -6, -6, -4, -2,
    -16, -4, -2, -4, -7, -4, -1, -1,
    -11, -3, -2, -6, -2, -2, -2, -1,
    -2, -2
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 746,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR <= 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR <= 8
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_OswaldRegular14p2 = {
#else
lv_font_t ui_font_OswaldRegular14p2 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_OSWALDREGULAR14P2*/

