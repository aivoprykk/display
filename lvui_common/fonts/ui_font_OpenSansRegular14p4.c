/*******************************************************************************
 * Size: 14 px
 * Bpp: 4
 * Opts: --bpp 4 --size 14 --font /Users/aivo/Downloads/squareline/squareline_proj_2_13_01_s/assets/OpenSans-Regular.ttf -o /Users/aivo/Downloads/squareline/squareline_proj_2_13_01_s/assets/ui_font_OpenSansRegular14p4.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_OPENSANSREGULAR14P4
#define UI_FONT_OPENSANSREGULAR14P4 1
#endif

#if UI_FONT_OPENSANSREGULAR14P4

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0xd8, 0xc7, 0xb6, 0xb6, 0xa5, 0x94, 0x94, 0x42,
    0xb7, 0xd8,

    /* U+0022 "\"" */
    0xf, 0x18, 0x90, 0xf0, 0x78, 0xe, 0x6, 0x70,
    0x90, 0x45,

    /* U+0023 "#" */
    0x0, 0x9, 0x50, 0x85, 0x0, 0x0, 0xc2, 0xb,
    0x20, 0x0, 0xe, 0x0, 0xe0, 0x1, 0xee, 0xfe,
    0xef, 0xe9, 0x0, 0x59, 0x5, 0x90, 0x0, 0x9,
    0x50, 0x85, 0x0, 0x9e, 0xfe, 0xef, 0xee, 0x20,
    0xe, 0x0, 0xe0, 0x0, 0x2, 0xc0, 0x2c, 0x0,
    0x0, 0x49, 0x5, 0x90, 0x0,

    /* U+0024 "$" */
    0x0, 0x7, 0x60, 0x0, 0x3, 0xcf, 0xfd, 0x70,
    0xe, 0x78, 0x74, 0x40, 0x1f, 0x7, 0x60, 0x0,
    0xd, 0xa9, 0x60, 0x0, 0x1, 0x9f, 0xd7, 0x0,
    0x0, 0x7, 0x9b, 0xc0, 0x0, 0x7, 0x60, 0xf2,
    0x4, 0x7, 0x66, 0xe0, 0x1d, 0xff, 0xfc, 0x30,
    0x0, 0x8, 0x60, 0x0, 0x0, 0x7, 0x60, 0x0,

    /* U+0025 "%" */
    0x8, 0xec, 0x20, 0x3, 0xc0, 0x1, 0xd0, 0x69,
    0x0, 0xc3, 0x0, 0x4a, 0x2, 0xc0, 0x5a, 0x0,
    0x4, 0xa0, 0x2c, 0xd, 0x7d, 0xb1, 0x1d, 0x7,
    0x96, 0x9e, 0x17, 0x80, 0x6d, 0xb2, 0xd3, 0xc0,
    0x2c, 0x0, 0x0, 0x87, 0x3b, 0x1, 0xd0, 0x0,
    0x2d, 0x2, 0xc0, 0x2c, 0x0, 0xa, 0x50, 0xd,
    0x5, 0x90, 0x3, 0xc0, 0x0, 0x5c, 0xc1,

    /* U+0026 "&" */
    0x0, 0x8e, 0xfb, 0x10, 0x0, 0x0, 0x3f, 0x20,
    0xb9, 0x0, 0x0, 0x3, 0xe0, 0x9, 0x80, 0x0,
    0x0, 0xb, 0x98, 0xd1, 0x0, 0x0, 0x0, 0x7f,
    0xe0, 0x0, 0x21, 0x0, 0x9c, 0x2c, 0xa0, 0xc,
    0x50, 0x2f, 0x10, 0xc, 0xa3, 0xe0, 0x3, 0xf0,
    0x0, 0xc, 0xf7, 0x0, 0xe, 0x70, 0x4, 0xde,
    0xa0, 0x0, 0x3c, 0xee, 0xc5, 0x1d, 0xa0,

    /* U+0027 "'" */
    0xf, 0x10, 0xf0, 0xe, 0x0, 0x90,

    /* U+0028 "(" */
    0x0, 0xb6, 0x5, 0xd0, 0xc, 0x60, 0x1f, 0x10,
    0x4e, 0x0, 0x6c, 0x0, 0x6b, 0x0, 0x6c, 0x0,
    0x4e, 0x0, 0x1f, 0x10, 0xc, 0x60, 0x5, 0xd0,
    0x0, 0xb6,

    /* U+0029 ")" */
    0x4d, 0x0, 0xb, 0x70, 0x4, 0xd0, 0x0, 0xf3,
    0x0, 0xc6, 0x0, 0xa8, 0x0, 0x98, 0x0, 0xa8,
    0x0, 0xc6, 0x0, 0xf3, 0x4, 0xe0, 0xb, 0x70,
    0x4d, 0x0,

    /* U+002A "*" */
    0x0, 0xc, 0x60, 0x0, 0x0, 0xa, 0x50, 0x0,
    0x4c, 0x7a, 0x78, 0xd0, 0x15, 0x7f, 0xd7, 0x50,
    0x0, 0x79, 0xe3, 0x0, 0x3, 0xf2, 0x7d, 0x0,
    0x0, 0x40, 0x4, 0x0,

    /* U+002B "+" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x70, 0x0,
    0x0, 0x7, 0x70, 0x0, 0x0, 0x7, 0x70, 0x0,
    0x4f, 0xff, 0xff, 0xf4, 0x0, 0x7, 0x70, 0x0,
    0x0, 0x7, 0x70, 0x0, 0x0, 0x7, 0x70, 0x0,

    /* U+002C "," */
    0x7, 0x50, 0xe5, 0x1f, 0x5, 0x90,

    /* U+002D "-" */
    0x6f, 0xfe, 0x2, 0x21,

    /* U+002E "." */
    0xb6, 0xd8,

    /* U+002F "/" */
    0x0, 0x5, 0xc0, 0x0, 0xb6, 0x0, 0x1f, 0x10,
    0x6, 0xa0, 0x0, 0xd5, 0x0, 0x2e, 0x0, 0x8,
    0x90, 0x0, 0xe3, 0x0, 0x4d, 0x0, 0xa, 0x70,
    0x0,

    /* U+0030 "0" */
    0x0, 0xaf, 0xf9, 0x0, 0x9, 0xb1, 0x1b, 0x80,
    0xf, 0x20, 0x2, 0xf0, 0x3f, 0x0, 0x0, 0xf3,
    0x4d, 0x0, 0x0, 0xe4, 0x4d, 0x0, 0x0, 0xe4,
    0x3f, 0x0, 0x0, 0xf3, 0xf, 0x20, 0x2, 0xf0,
    0x9, 0xb1, 0x1b, 0x90, 0x0, 0x9f, 0xfa, 0x0,

    /* U+0031 "1" */
    0x0, 0xae, 0x2d, 0xae, 0x65, 0x3e, 0x0, 0x3e,
    0x0, 0x3e, 0x0, 0x3e, 0x0, 0x3e, 0x0, 0x3e,
    0x0, 0x3e, 0x0, 0x3e,

    /* U+0032 "2" */
    0x4, 0xcf, 0xf9, 0x0, 0xb, 0x51, 0x2c, 0x90,
    0x0, 0x0, 0x6, 0xc0, 0x0, 0x0, 0x7, 0xb0,
    0x0, 0x0, 0x1e, 0x40, 0x0, 0x0, 0xc8, 0x0,
    0x0, 0xb, 0x90, 0x0, 0x0, 0xb8, 0x0, 0x0,
    0xc, 0xa1, 0x11, 0x10, 0x5f, 0xff, 0xff, 0xf3,

    /* U+0033 "3" */
    0x6, 0xdf, 0xfb, 0x10, 0x19, 0x30, 0x1b, 0xb0,
    0x0, 0x0, 0x5, 0xd0, 0x0, 0x0, 0x2c, 0x70,
    0x0, 0xce, 0xf8, 0x0, 0x0, 0x11, 0x4b, 0xa0,
    0x0, 0x0, 0x1, 0xf1, 0x0, 0x0, 0x1, 0xf1,
    0x35, 0x10, 0x2b, 0xc0, 0x3b, 0xff, 0xe9, 0x10,

    /* U+0034 "4" */
    0x0, 0x0, 0x5f, 0x30, 0x0, 0x2, 0xdd, 0x30,
    0x0, 0xd, 0x3d, 0x30, 0x0, 0xa6, 0xd, 0x30,
    0x6, 0xa0, 0xd, 0x30, 0x3c, 0x0, 0xd, 0x30,
    0xbf, 0xff, 0xff, 0xfb, 0x12, 0x22, 0x2e, 0x51,
    0x0, 0x0, 0xd, 0x30, 0x0, 0x0, 0xd, 0x30,

    /* U+0035 "5" */
    0x8, 0xff, 0xff, 0x80, 0x9, 0x81, 0x11, 0x0,
    0xb, 0x50, 0x0, 0x0, 0xc, 0xef, 0xfa, 0x10,
    0x1, 0x10, 0x2b, 0xc0, 0x0, 0x0, 0x1, 0xf2,
    0x0, 0x0, 0x0, 0xf3, 0x0, 0x0, 0x2, 0xf0,
    0x17, 0x20, 0x3c, 0x90, 0xa, 0xef, 0xe8, 0x0,

    /* U+0036 "6" */
    0x0, 0x2a, 0xef, 0x80, 0x2, 0xe6, 0x0, 0x0,
    0xa, 0x60, 0x0, 0x0, 0xf, 0x5d, 0xfc, 0x20,
    0x2f, 0xa1, 0x7, 0xe0, 0x3f, 0x10, 0x0, 0xe4,
    0x2f, 0x0, 0x0, 0xd5, 0xf, 0x30, 0x0, 0xf3,
    0x8, 0xd2, 0x9, 0xd0, 0x0, 0x8e, 0xfb, 0x10,

    /* U+0037 "7" */
    0x5f, 0xff, 0xff, 0xf4, 0x1, 0x11, 0x13, 0xf1,
    0x0, 0x0, 0x9, 0x90, 0x0, 0x0, 0x1f, 0x20,
    0x0, 0x0, 0x7b, 0x0, 0x0, 0x0, 0xe3, 0x0,
    0x0, 0x6, 0xc0, 0x0, 0x0, 0xd, 0x50, 0x0,
    0x0, 0x5e, 0x0, 0x0, 0x0, 0xc7, 0x0, 0x0,

    /* U+0038 "8" */
    0x2, 0xbf, 0xfb, 0x20, 0xc, 0x90, 0x9, 0xc0,
    0xf, 0x20, 0x3, 0xe0, 0x9, 0xa0, 0xa, 0x80,
    0x0, 0xae, 0xe8, 0x0, 0x5, 0xd6, 0x8e, 0x50,
    0x1f, 0x10, 0x2, 0xf1, 0x4d, 0x0, 0x0, 0xd4,
    0x1f, 0x60, 0x6, 0xe1, 0x3, 0xcf, 0xfc, 0x30,

    /* U+0039 "9" */
    0x2, 0xbf, 0xe9, 0x0, 0xd, 0x80, 0x2b, 0x80,
    0x3e, 0x0, 0x1, 0xf0, 0x4e, 0x0, 0x0, 0xf3,
    0xf, 0x60, 0x18, 0xf3, 0x3, 0xcf, 0xd5, 0xf2,
    0x0, 0x0, 0x2, 0xf0, 0x0, 0x0, 0x8, 0xb0,
    0x1, 0x1, 0x7f, 0x20, 0x8, 0xff, 0xb3, 0x0,

    /* U+003A ":" */
    0xd8, 0xb6, 0x0, 0x0, 0x0, 0x0, 0xb6, 0xd8,

    /* U+003B ";" */
    0xd, 0x70, 0xb6, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x8, 0x40, 0xf3, 0x3e, 0x7, 0x80,

    /* U+003C "<" */
    0x0, 0x0, 0x0, 0x73, 0x0, 0x0, 0x7e, 0x91,
    0x0, 0x6d, 0x81, 0x0, 0x2d, 0x91, 0x0, 0x0,
    0x19, 0xd7, 0x10, 0x0, 0x0, 0x18, 0xe9, 0x20,
    0x0, 0x0, 0x6, 0xd3, 0x0, 0x0, 0x0, 0x0,

    /* U+003D "=" */
    0x3f, 0xff, 0xff, 0xf3, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xff, 0xf3,

    /* U+003E ">" */
    0x37, 0x0, 0x0, 0x0, 0x19, 0xe7, 0x0, 0x0,
    0x0, 0x19, 0xd6, 0x0, 0x0, 0x0, 0x19, 0xd2,
    0x0, 0x1, 0x7d, 0x91, 0x2, 0x9e, 0x71, 0x0,
    0x4d, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,

    /* U+003F "?" */
    0x5c, 0xff, 0xa0, 0x44, 0x12, 0xc7, 0x0, 0x0,
    0x7a, 0x0, 0x0, 0xc5, 0x0, 0x1c, 0x70, 0x0,
    0xc5, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x0,
    0x2, 0xd2, 0x0, 0x3, 0xf2, 0x0,

    /* U+0040 "@" */
    0x0, 0x3, 0xae, 0xee, 0xb5, 0x0, 0x0, 0x6d,
    0x50, 0x0, 0x3c, 0x80, 0x4, 0xc0, 0x3c, 0xde,
    0x80, 0xc4, 0xc, 0x30, 0xe3, 0x5, 0xa0, 0x59,
    0xe, 0x5, 0xb0, 0x6, 0x90, 0x3b, 0x2c, 0x6,
    0xa0, 0x8, 0x80, 0x4a, 0x2c, 0x2, 0xe1, 0x1c,
    0xa0, 0xa5, 0xe, 0x0, 0x7d, 0xc3, 0x9d, 0x80,
    0x9, 0x70, 0x0, 0x0, 0x0, 0x0, 0x1, 0xd9,
    0x20, 0x2, 0x60, 0x0, 0x0, 0x7, 0xce, 0xec,
    0x80, 0x0,

    /* U+0041 "A" */
    0x0, 0x4, 0xf2, 0x0, 0x0, 0x0, 0xad, 0x80,
    0x0, 0x0, 0x1f, 0x4e, 0x0, 0x0, 0x7, 0xb0,
    0xd5, 0x0, 0x0, 0xd5, 0x8, 0xb0, 0x0, 0x3f,
    0x0, 0x2f, 0x10, 0xa, 0xff, 0xff, 0xf7, 0x1,
    0xf5, 0x22, 0x27, 0xd0, 0x6d, 0x0, 0x0, 0xf,
    0x4c, 0x60, 0x0, 0x0, 0x9a,

    /* U+0042 "B" */
    0xaf, 0xff, 0xea, 0x20, 0xa8, 0x0, 0x2b, 0xc0,
    0xa8, 0x0, 0x4, 0xe0, 0xa8, 0x0, 0xa, 0x90,
    0xaf, 0xee, 0xfa, 0x0, 0xa9, 0x11, 0x3a, 0xc0,
    0xa8, 0x0, 0x0, 0xf3, 0xa8, 0x0, 0x0, 0xf3,
    0xa8, 0x0, 0x2a, 0xe0, 0xaf, 0xff, 0xfb, 0x20,

    /* U+0043 "C" */
    0x0, 0x19, 0xef, 0xeb, 0x20, 0x1e, 0xb4, 0x12,
    0x60, 0x9, 0xc0, 0x0, 0x0, 0x0, 0xf4, 0x0,
    0x0, 0x0, 0x1f, 0x10, 0x0, 0x0, 0x1, 0xf1,
    0x0, 0x0, 0x0, 0xf, 0x40, 0x0, 0x0, 0x0,
    0xab, 0x0, 0x0, 0x0, 0x2, 0xea, 0x31, 0x24,
    0x0, 0x2, 0xae, 0xff, 0xb0,

    /* U+0044 "D" */
    0xaf, 0xff, 0xea, 0x20, 0xa, 0x80, 0x2, 0x9f,
    0x30, 0xa8, 0x0, 0x0, 0x8d, 0xa, 0x80, 0x0,
    0x1, 0xf2, 0xa8, 0x0, 0x0, 0xf, 0x4a, 0x80,
    0x0, 0x0, 0xf4, 0xa8, 0x0, 0x0, 0x2f, 0x1a,
    0x80, 0x0, 0x9, 0xc0, 0xa8, 0x1, 0x3a, 0xe2,
    0xa, 0xff, 0xfd, 0x91, 0x0,

    /* U+0045 "E" */
    0xaf, 0xff, 0xff, 0xa9, 0x11, 0x11, 0xa8, 0x0,
    0x0, 0xa8, 0x0, 0x0, 0xaf, 0xff, 0xfa, 0xa9,
    0x22, 0x21, 0xa8, 0x0, 0x0, 0xa8, 0x0, 0x0,
    0xa9, 0x11, 0x11, 0xaf, 0xff, 0xff,

    /* U+0046 "F" */
    0xaf, 0xff, 0xff, 0xa9, 0x11, 0x11, 0xa8, 0x0,
    0x0, 0xa8, 0x0, 0x0, 0xaf, 0xff, 0xfa, 0xa9,
    0x22, 0x21, 0xa8, 0x0, 0x0, 0xa8, 0x0, 0x0,
    0xa8, 0x0, 0x0, 0xa8, 0x0, 0x0,

    /* U+0047 "G" */
    0x0, 0x7, 0xdf, 0xfd, 0x80, 0x0, 0xcc, 0x41,
    0x14, 0x40, 0x9, 0xc0, 0x0, 0x0, 0x0, 0xf,
    0x40, 0x0, 0x0, 0x0, 0x1f, 0x10, 0x5, 0xff,
    0xf2, 0x1f, 0x10, 0x0, 0x22, 0xf2, 0xf, 0x40,
    0x0, 0x0, 0xf2, 0xa, 0xb0, 0x0, 0x0, 0xf2,
    0x1, 0xeb, 0x31, 0x14, 0xf2, 0x0, 0x19, 0xef,
    0xfd, 0xa1,

    /* U+0048 "H" */
    0xa8, 0x0, 0x0, 0x3f, 0xa8, 0x0, 0x0, 0x3f,
    0xa8, 0x0, 0x0, 0x3f, 0xa8, 0x0, 0x0, 0x3f,
    0xaf, 0xff, 0xff, 0xff, 0xa9, 0x22, 0x22, 0x5f,
    0xa8, 0x0, 0x0, 0x3f, 0xa8, 0x0, 0x0, 0x3f,
    0xa8, 0x0, 0x0, 0x3f, 0xa8, 0x0, 0x0, 0x3f,

    /* U+0049 "I" */
    0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8,
    0xa8, 0xa8,

    /* U+004A "J" */
    0x0, 0xb, 0x70, 0x0, 0xb7, 0x0, 0xb, 0x70,
    0x0, 0xb7, 0x0, 0xb, 0x70, 0x0, 0xb7, 0x0,
    0xb, 0x70, 0x0, 0xb7, 0x0, 0xb, 0x70, 0x0,
    0xb7, 0x0, 0xb, 0x70, 0x1, 0xe4, 0x1f, 0xf9,
    0x0, 0x11, 0x0,

    /* U+004B "K" */
    0xa8, 0x0, 0x6, 0xd1, 0xa8, 0x0, 0x5e, 0x20,
    0xa8, 0x4, 0xe3, 0x0, 0xa8, 0x3e, 0x30, 0x0,
    0xaa, 0xea, 0x0, 0x0, 0xaf, 0x6f, 0x40, 0x0,
    0xa8, 0x6, 0xe1, 0x0, 0xa8, 0x0, 0xab, 0x0,
    0xa8, 0x0, 0xd, 0x70, 0xa8, 0x0, 0x3, 0xf3,

    /* U+004C "L" */
    0xa8, 0x0, 0x0, 0xa8, 0x0, 0x0, 0xa8, 0x0,
    0x0, 0xa8, 0x0, 0x0, 0xa8, 0x0, 0x0, 0xa8,
    0x0, 0x0, 0xa8, 0x0, 0x0, 0xa8, 0x0, 0x0,
    0xa9, 0x11, 0x11, 0xaf, 0xff, 0xff,

    /* U+004D "M" */
    0xaf, 0x40, 0x0, 0x0, 0xaf, 0x3a, 0xba, 0x0,
    0x0, 0x1e, 0xe3, 0xa7, 0xe1, 0x0, 0x7, 0x9e,
    0x3a, 0x79, 0x60, 0x0, 0xd3, 0xe3, 0xa7, 0x3c,
    0x0, 0x3d, 0xe, 0x3a, 0x70, 0xd2, 0x9, 0x70,
    0xe3, 0xa7, 0x8, 0x90, 0xe1, 0xe, 0x3a, 0x70,
    0x2e, 0x6a, 0x0, 0xe3, 0xa7, 0x0, 0xcf, 0x40,
    0xe, 0x3a, 0x70, 0x6, 0xe0, 0x0, 0xe3,

    /* U+004E "N" */
    0xae, 0x10, 0x0, 0xe, 0x3a, 0xea, 0x0, 0x0,
    0xe3, 0xa7, 0xe4, 0x0, 0xe, 0x3a, 0x65, 0xd0,
    0x0, 0xe3, 0xa7, 0xb, 0x70, 0xe, 0x3a, 0x70,
    0x1e, 0x20, 0xe3, 0xa7, 0x0, 0x6b, 0xe, 0x3a,
    0x70, 0x0, 0xc5, 0xe3, 0xa7, 0x0, 0x2, 0xde,
    0x3a, 0x70, 0x0, 0x7, 0xf3,

    /* U+004F "O" */
    0x0, 0x2a, 0xef, 0xe9, 0x10, 0x0, 0x2e, 0xa3,
    0x13, 0xad, 0x10, 0xa, 0xa0, 0x0, 0x0, 0xc8,
    0x0, 0xf4, 0x0, 0x0, 0x6, 0xd0, 0x1f, 0x10,
    0x0, 0x0, 0x3f, 0x1, 0xf1, 0x0, 0x0, 0x3,
    0xf0, 0xf, 0x40, 0x0, 0x0, 0x5e, 0x0, 0xaa,
    0x0, 0x0, 0xc, 0x80, 0x2, 0xe9, 0x20, 0x2a,
    0xe1, 0x0, 0x2, 0xae, 0xfe, 0x91, 0x0,

    /* U+0050 "P" */
    0xaf, 0xff, 0xd6, 0xa, 0x80, 0x15, 0xf5, 0xa8,
    0x0, 0x9, 0xaa, 0x80, 0x0, 0x8a, 0xa8, 0x0,
    0x4e, 0x4a, 0xfe, 0xfe, 0x60, 0xa9, 0x11, 0x0,
    0xa, 0x80, 0x0, 0x0, 0xa8, 0x0, 0x0, 0xa,
    0x80, 0x0, 0x0,

    /* U+0051 "Q" */
    0x0, 0x2a, 0xef, 0xe9, 0x10, 0x0, 0x2e, 0xa3,
    0x13, 0xad, 0x10, 0xa, 0xa0, 0x0, 0x0, 0xc8,
    0x0, 0xf4, 0x0, 0x0, 0x6, 0xd0, 0x1f, 0x10,
    0x0, 0x0, 0x3f, 0x1, 0xf1, 0x0, 0x0, 0x3,
    0xf0, 0xf, 0x40, 0x0, 0x0, 0x5d, 0x0, 0xaa,
    0x0, 0x0, 0xc, 0x80, 0x2, 0xe9, 0x20, 0x2a,
    0xd1, 0x0, 0x2, 0xae, 0xff, 0xa1, 0x0, 0x0,
    0x0, 0x0, 0xca, 0x0, 0x0, 0x0, 0x0, 0x1,
    0xe8, 0x0, 0x0, 0x0, 0x0, 0x3, 0x81, 0x0,

    /* U+0052 "R" */
    0xaf, 0xff, 0xd7, 0x0, 0xa8, 0x1, 0x5e, 0x60,
    0xa8, 0x0, 0x9, 0xa0, 0xa8, 0x0, 0x9, 0xa0,
    0xa8, 0x0, 0x3e, 0x40, 0xaf, 0xef, 0xe5, 0x0,
    0xa9, 0x13, 0xf2, 0x0, 0xa8, 0x0, 0x8c, 0x0,
    0xa8, 0x0, 0xd, 0x60, 0xa8, 0x0, 0x4, 0xf2,

    /* U+0053 "S" */
    0x2, 0xbf, 0xfd, 0x60, 0xe9, 0x21, 0x44, 0x2f,
    0x10, 0x0, 0x0, 0xe6, 0x0, 0x0, 0x3, 0xdc,
    0x50, 0x0, 0x0, 0x4b, 0xe3, 0x0, 0x0, 0x7,
    0xd0, 0x0, 0x0, 0x3f, 0x25, 0x20, 0x2b, 0xb2,
    0xcf, 0xfe, 0x91,

    /* U+0054 "T" */
    0xef, 0xff, 0xff, 0xf9, 0x11, 0x1c, 0x71, 0x10,
    0x0, 0xb, 0x70, 0x0, 0x0, 0xb, 0x70, 0x0,
    0x0, 0xb, 0x70, 0x0, 0x0, 0xb, 0x70, 0x0,
    0x0, 0xb, 0x70, 0x0, 0x0, 0xb, 0x70, 0x0,
    0x0, 0xb, 0x70, 0x0, 0x0, 0xb, 0x70, 0x0,

    /* U+0055 "U" */
    0xb7, 0x0, 0x0, 0x3e, 0xb7, 0x0, 0x0, 0x3e,
    0xb7, 0x0, 0x0, 0x3e, 0xb7, 0x0, 0x0, 0x3e,
    0xb7, 0x0, 0x0, 0x3e, 0xb7, 0x0, 0x0, 0x3e,
    0xb7, 0x0, 0x0, 0x4e, 0x9a, 0x0, 0x0, 0x7c,
    0x2f, 0x71, 0x15, 0xf5, 0x3, 0xbf, 0xfc, 0x50,

    /* U+0056 "V" */
    0xd6, 0x0, 0x0, 0x1f, 0x27, 0xc0, 0x0, 0x6,
    0xc0, 0x1f, 0x10, 0x0, 0xc7, 0x0, 0xb7, 0x0,
    0x2f, 0x10, 0x6, 0xd0, 0x7, 0xb0, 0x0, 0xf,
    0x20, 0xd6, 0x0, 0x0, 0xa8, 0x2f, 0x0, 0x0,
    0x4, 0xd8, 0xa0, 0x0, 0x0, 0xe, 0xe4, 0x0,
    0x0, 0x0, 0x9e, 0x0, 0x0,

    /* U+0057 "W" */
    0xa8, 0x0, 0x5, 0xf2, 0x0, 0xa, 0x96, 0xc0,
    0x0, 0xac, 0x70, 0x0, 0xe5, 0x2f, 0x10, 0xe,
    0x4c, 0x0, 0x2f, 0x10, 0xd5, 0x3, 0xc0, 0xe1,
    0x6, 0xc0, 0x9, 0x90, 0x78, 0xa, 0x50, 0xa8,
    0x0, 0x5d, 0xc, 0x40, 0x6a, 0xe, 0x40, 0x1,
    0xf2, 0xf0, 0x1, 0xf2, 0xf0, 0x0, 0xc, 0x9b,
    0x0, 0xd, 0x9b, 0x0, 0x0, 0x8f, 0x70, 0x0,
    0x8f, 0x70, 0x0, 0x4, 0xf2, 0x0, 0x4, 0xf2,
    0x0,

    /* U+0058 "X" */
    0x6d, 0x0, 0x0, 0xb7, 0x0, 0xb8, 0x0, 0x6c,
    0x0, 0x2, 0xe2, 0x1e, 0x30, 0x0, 0x7, 0xca,
    0x80, 0x0, 0x0, 0xd, 0xe0, 0x0, 0x0, 0x2,
    0xee, 0x30, 0x0, 0x0, 0xb7, 0x6c, 0x0, 0x0,
    0x5d, 0x0, 0xc7, 0x0, 0x1e, 0x30, 0x3, 0xf2,
    0xa, 0x90, 0x0, 0x9, 0xb0,

    /* U+0059 "Y" */
    0xb8, 0x0, 0x0, 0xa8, 0x3f, 0x10, 0x3, 0xe1,
    0xa, 0x80, 0xb, 0x70, 0x2, 0xe1, 0x3e, 0x0,
    0x0, 0x98, 0xb6, 0x0, 0x0, 0x1e, 0xd0, 0x0,
    0x0, 0xa, 0x80, 0x0, 0x0, 0xa, 0x80, 0x0,
    0x0, 0xa, 0x80, 0x0, 0x0, 0xa, 0x80, 0x0,

    /* U+005A "Z" */
    0x4f, 0xff, 0xff, 0xf5, 0x1, 0x11, 0x17, 0xe0,
    0x0, 0x0, 0x1e, 0x40, 0x0, 0x0, 0xb9, 0x0,
    0x0, 0x6, 0xd0, 0x0, 0x0, 0x1f, 0x30, 0x0,
    0x0, 0xb9, 0x0, 0x0, 0x6, 0xd0, 0x0, 0x0,
    0x2f, 0x51, 0x11, 0x10, 0x7f, 0xff, 0xff, 0xf7,

    /* U+005B "[" */
    0xdf, 0xf3, 0xd4, 0x0, 0xd4, 0x0, 0xd4, 0x0,
    0xd4, 0x0, 0xd4, 0x0, 0xd4, 0x0, 0xd4, 0x0,
    0xd4, 0x0, 0xd4, 0x0, 0xd4, 0x0, 0xd4, 0x0,
    0xdf, 0xf3,

    /* U+005C "\\" */
    0xa7, 0x0, 0x4, 0xd0, 0x0, 0xe, 0x30, 0x0,
    0x89, 0x0, 0x2, 0xe0, 0x0, 0xd, 0x50, 0x0,
    0x6b, 0x0, 0x1, 0xf1, 0x0, 0xb, 0x70, 0x0,
    0x5d,

    /* U+005D "]" */
    0xaf, 0xf7, 0x0, 0xa7, 0x0, 0xa7, 0x0, 0xa7,
    0x0, 0xa7, 0x0, 0xa7, 0x0, 0xa7, 0x0, 0xa7,
    0x0, 0xa7, 0x0, 0xa7, 0x0, 0xa7, 0x0, 0xa7,
    0xaf, 0xf7,

    /* U+005E "^" */
    0x0, 0x4, 0x20, 0x0, 0x0, 0xd, 0xb0, 0x0,
    0x0, 0x68, 0xb3, 0x0, 0x0, 0xd2, 0x4b, 0x0,
    0x4, 0xa0, 0xc, 0x30, 0xc, 0x30, 0x4, 0xb0,
    0x3c, 0x0, 0x0, 0xc3,

    /* U+005F "_" */
    0xe, 0xee, 0xee, 0xe2,

    /* U+0060 "`" */
    0x27, 0x0, 0xc, 0x70, 0x1, 0xc2,

    /* U+0061 "a" */
    0x3, 0xcf, 0xfa, 0x0, 0x23, 0x0, 0xc7, 0x0,
    0x0, 0x7, 0xa0, 0x3b, 0xdd, 0xea, 0x1f, 0x60,
    0x7, 0xa5, 0xd0, 0x0, 0x9a, 0x3f, 0x10, 0x3e,
    0xa0, 0x8e, 0xda, 0x5a,

    /* U+0062 "b" */
    0xc5, 0x0, 0x0, 0xc, 0x50, 0x0, 0x0, 0xc5,
    0x0, 0x0, 0xc, 0x6c, 0xfe, 0x60, 0xcd, 0x30,
    0x4f, 0x3c, 0x80, 0x0, 0x99, 0xc5, 0x0, 0x6,
    0xcc, 0x50, 0x0, 0x6c, 0xc8, 0x0, 0x9, 0x9c,
    0xe3, 0x4, 0xf3, 0xc4, 0xcf, 0xe6, 0x0,

    /* U+0063 "c" */
    0x0, 0x8e, 0xfd, 0x10, 0x9c, 0x20, 0x30, 0xf,
    0x20, 0x0, 0x3, 0xf0, 0x0, 0x0, 0x3f, 0x0,
    0x0, 0x0, 0xf2, 0x0, 0x0, 0xa, 0xc2, 0x4,
    0x0, 0x9, 0xef, 0xc1,

    /* U+0064 "d" */
    0x0, 0x0, 0x0, 0xc5, 0x0, 0x0, 0x0, 0xc5,
    0x0, 0x0, 0x0, 0xc5, 0x1, 0xaf, 0xe8, 0xc5,
    0xa, 0xb1, 0x8, 0xf5, 0xf, 0x20, 0x0, 0xf5,
    0x3f, 0x0, 0x0, 0xc5, 0x3f, 0x0, 0x0, 0xc5,
    0x1f, 0x20, 0x0, 0xe5, 0xb, 0xb1, 0x8, 0xf5,
    0x1, 0xaf, 0xe8, 0x95,

    /* U+0065 "e" */
    0x0, 0x9e, 0xfa, 0x10, 0x9, 0xa1, 0x9, 0xb0,
    0xf, 0x10, 0x2, 0xf0, 0x3f, 0xff, 0xff, 0xf1,
    0x3f, 0x0, 0x0, 0x0, 0xf, 0x30, 0x0, 0x0,
    0x9, 0xd3, 0x2, 0x50, 0x0, 0x8e, 0xfe, 0x80,

    /* U+0066 "f" */
    0x0, 0xaf, 0xf2, 0x5, 0xe1, 0x0, 0x7, 0xa0,
    0x0, 0x8f, 0xff, 0x80, 0x7, 0xa0, 0x0, 0x7,
    0xa0, 0x0, 0x7, 0xa0, 0x0, 0x7, 0xa0, 0x0,
    0x7, 0xa0, 0x0, 0x7, 0xa0, 0x0, 0x7, 0xa0,
    0x0,

    /* U+0067 "g" */
    0x3, 0xce, 0xff, 0xf4, 0xe, 0x60, 0x3f, 0x20,
    0x2f, 0x0, 0xc, 0x60, 0x2f, 0x0, 0xc, 0x50,
    0xe, 0x70, 0x3f, 0x10, 0x4, 0xfe, 0xc4, 0x0,
    0xb, 0x71, 0x10, 0x0, 0x9, 0xff, 0xff, 0x80,
    0x7b, 0x10, 0x3, 0xf2, 0xc6, 0x0, 0x0, 0xf2,
    0x9b, 0x10, 0x19, 0xd0, 0x1a, 0xef, 0xea, 0x10,

    /* U+0068 "h" */
    0xc5, 0x0, 0x0, 0xc, 0x50, 0x0, 0x0, 0xc5,
    0x0, 0x0, 0xc, 0x7b, 0xfe, 0x80, 0xce, 0x30,
    0x3f, 0x3c, 0x80, 0x0, 0xb6, 0xc5, 0x0, 0xa,
    0x7c, 0x50, 0x0, 0xa7, 0xc5, 0x0, 0xa, 0x7c,
    0x50, 0x0, 0xa7, 0xc5, 0x0, 0xa, 0x70,

    /* U+0069 "i" */
    0xc5, 0x62, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5,
    0xc5, 0xc5,

    /* U+006A "j" */
    0x0, 0xc5, 0x0, 0x62, 0x0, 0xc5, 0x0, 0xc5,
    0x0, 0xc5, 0x0, 0xc5, 0x0, 0xc5, 0x0, 0xc5,
    0x0, 0xc5, 0x0, 0xc5, 0x0, 0xc5, 0x0, 0xc5,
    0x1, 0xe3, 0xbf, 0x90,

    /* U+006B "k" */
    0xc5, 0x0, 0x0, 0xc, 0x50, 0x0, 0x0, 0xc5,
    0x0, 0x0, 0xc, 0x50, 0xb, 0x90, 0xc5, 0x9,
    0xb0, 0xc, 0x58, 0xc0, 0x0, 0xc9, 0xf3, 0x0,
    0xc, 0xda, 0xc0, 0x0, 0xc5, 0xd, 0x70, 0xc,
    0x50, 0x3f, 0x30, 0xc5, 0x0, 0x7d, 0x0,

    /* U+006C "l" */
    0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5,
    0xc5, 0xc5, 0xc5,

    /* U+006D "m" */
    0xc4, 0xcf, 0xd4, 0x5e, 0xfc, 0x1c, 0xd2, 0x8,
    0xeb, 0x10, 0xba, 0xc7, 0x0, 0x1f, 0x30, 0x5,
    0xcc, 0x50, 0x0, 0xf1, 0x0, 0x4d, 0xc5, 0x0,
    0xf, 0x10, 0x4, 0xdc, 0x50, 0x0, 0xf1, 0x0,
    0x4d, 0xc5, 0x0, 0xf, 0x10, 0x4, 0xdc, 0x50,
    0x0, 0xf1, 0x0, 0x4d,

    /* U+006E "n" */
    0xc4, 0xbf, 0xe7, 0xc, 0xe3, 0x3, 0xf3, 0xc8,
    0x0, 0xb, 0x6c, 0x50, 0x0, 0xa7, 0xc5, 0x0,
    0xa, 0x7c, 0x50, 0x0, 0xa7, 0xc5, 0x0, 0xa,
    0x7c, 0x50, 0x0, 0xa7,

    /* U+006F "o" */
    0x0, 0x9e, 0xfc, 0x30, 0x9, 0xc1, 0x6, 0xe1,
    0xf, 0x20, 0x0, 0xb7, 0x3f, 0x0, 0x0, 0x8a,
    0x2f, 0x0, 0x0, 0x89, 0xf, 0x30, 0x0, 0xc7,
    0x9, 0xc1, 0x6, 0xe1, 0x0, 0x8e, 0xfc, 0x30,

    /* U+0070 "p" */
    0xc4, 0xbf, 0xe6, 0xc, 0xd3, 0x4, 0xf4, 0xc8,
    0x0, 0x9, 0x9c, 0x50, 0x0, 0x6c, 0xc5, 0x0,
    0x6, 0xcc, 0x80, 0x0, 0x99, 0xce, 0x30, 0x4f,
    0x3c, 0x7c, 0xfe, 0x60, 0xc5, 0x0, 0x0, 0xc,
    0x50, 0x0, 0x0, 0xc5, 0x0, 0x0, 0xc, 0x50,
    0x0, 0x0,

    /* U+0071 "q" */
    0x1, 0xaf, 0xe7, 0x95, 0xa, 0xb1, 0x8, 0xf5,
    0x1f, 0x20, 0x0, 0xf5, 0x3f, 0x0, 0x0, 0xc5,
    0x3f, 0x0, 0x0, 0xc5, 0x1f, 0x20, 0x0, 0xe5,
    0xb, 0xb1, 0x8, 0xf5, 0x1, 0xaf, 0xe7, 0xc5,
    0x0, 0x0, 0x0, 0xc5, 0x0, 0x0, 0x0, 0xc5,
    0x0, 0x0, 0x0, 0xc5, 0x0, 0x0, 0x0, 0xc5,

    /* U+0072 "r" */
    0xc3, 0xaf, 0x6c, 0xd6, 0x11, 0xc9, 0x0, 0xc,
    0x50, 0x0, 0xc5, 0x0, 0xc, 0x50, 0x0, 0xc5,
    0x0, 0xc, 0x50, 0x0,

    /* U+0073 "s" */
    0x7, 0xef, 0xe8, 0x2, 0xe2, 0x2, 0x30, 0x3e,
    0x10, 0x0, 0x0, 0x8f, 0xa3, 0x0, 0x0, 0x17,
    0xe8, 0x0, 0x0, 0x2, 0xf0, 0x24, 0x0, 0x6e,
    0x2, 0xcf, 0xfc, 0x30,

    /* U+0074 "t" */
    0x6, 0x60, 0x0, 0xa6, 0x0, 0x9f, 0xff, 0x90,
    0xb6, 0x0, 0xb, 0x60, 0x0, 0xb6, 0x0, 0xb,
    0x60, 0x0, 0xb6, 0x0, 0x9, 0xb0, 0x0, 0x2d,
    0xf9,

    /* U+0075 "u" */
    0xe4, 0x0, 0xc, 0x6e, 0x40, 0x0, 0xc6, 0xe4,
    0x0, 0xc, 0x6e, 0x40, 0x0, 0xc6, 0xe4, 0x0,
    0xc, 0x6d, 0x40, 0x0, 0xe6, 0xaa, 0x0, 0x6f,
    0x62, 0xce, 0xd8, 0xa6,

    /* U+0076 "v" */
    0xd6, 0x0, 0x6, 0xd7, 0xb0, 0x0, 0xb7, 0x1f,
    0x10, 0x1f, 0x10, 0xc6, 0x6, 0xb0, 0x6, 0xc0,
    0xc6, 0x0, 0x1f, 0x3f, 0x10, 0x0, 0xbc, 0xa0,
    0x0, 0x5, 0xf5, 0x0,

    /* U+0077 "w" */
    0xb7, 0x0, 0x4f, 0x30, 0x9, 0x87, 0xb0, 0x9,
    0xe7, 0x0, 0xd4, 0x3f, 0x0, 0xe6, 0xc0, 0x1f,
    0x0, 0xe3, 0x3d, 0xf, 0x15, 0xc0, 0xa, 0x78,
    0x90, 0xb5, 0x98, 0x0, 0x6a, 0xc4, 0x6, 0xad,
    0x40, 0x2, 0xee, 0x0, 0x2e, 0xf0, 0x0, 0xe,
    0xa0, 0x0, 0xdb, 0x0,

    /* U+0078 "x" */
    0x4e, 0x10, 0xa, 0x90, 0x9, 0xa0, 0x5e, 0x0,
    0x0, 0xe5, 0xe4, 0x0, 0x0, 0x4f, 0x90, 0x0,
    0x0, 0x6f, 0xb0, 0x0, 0x2, 0xe3, 0xd6, 0x0,
    0xb, 0x80, 0x3e, 0x10, 0x6d, 0x0, 0x8, 0xb0,

    /* U+0079 "y" */
    0xc6, 0x0, 0x5, 0xd0, 0x7c, 0x0, 0xb, 0x80,
    0x1f, 0x10, 0xf, 0x20, 0xb, 0x60, 0x5d, 0x0,
    0x5, 0xc0, 0xa7, 0x0, 0x0, 0xf2, 0xf2, 0x0,
    0x0, 0xaa, 0xc0, 0x0, 0x0, 0x4f, 0x70, 0x0,
    0x0, 0x1f, 0x10, 0x0, 0x0, 0x6b, 0x0, 0x0,
    0x2, 0xe5, 0x0, 0x0, 0xdf, 0x80, 0x0, 0x0,

    /* U+007A "z" */
    0x2f, 0xff, 0xfe, 0x0, 0x0, 0xb, 0x80, 0x0,
    0x5, 0xd0, 0x0, 0x1, 0xe3, 0x0, 0x0, 0xa8,
    0x0, 0x0, 0x5d, 0x0, 0x0, 0x1e, 0x30, 0x0,
    0x7, 0xfe, 0xee, 0xe0,

    /* U+007B "{" */
    0x0, 0x2c, 0xc0, 0xc, 0x80, 0x0, 0xe3, 0x0,
    0xe, 0x30, 0x0, 0xe3, 0x0, 0x4f, 0x0, 0x9f,
    0x50, 0x0, 0x4f, 0x10, 0x0, 0xe3, 0x0, 0xe,
    0x30, 0x0, 0xe3, 0x0, 0xc, 0x80, 0x0, 0x2c,
    0xc0,

    /* U+007C "|" */
    0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5,
    0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5,

    /* U+007D "}" */
    0x8d, 0x50, 0x0, 0x4f, 0x10, 0x0, 0xf2, 0x0,
    0xf, 0x20, 0x0, 0xf2, 0x0, 0xc, 0x80, 0x0,
    0x2e, 0xe0, 0xc, 0x80, 0x0, 0xf2, 0x0, 0xf,
    0x20, 0x0, 0xf2, 0x0, 0x5f, 0x0, 0x8d, 0x50,
    0x0,

    /* U+007E "~" */
    0x1b, 0xfc, 0x50, 0x43, 0x34, 0x5, 0xcf, 0xb1
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 59, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 10, .adv_w = 89, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 20, .adv_w = 145, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 113, .adv_w = 185, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 163, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 49, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 229, .adv_w = 66, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 255, .adv_w = 66, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 281, .adv_w = 123, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 309, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 341, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 347, .adv_w = 72, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 351, .adv_w = 59, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 82, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 598, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 678, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 718, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 59, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 766, .adv_w = 59, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 781, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 813, .adv_w = 128, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 829, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 861, .adv_w = 97, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 891, .adv_w = 201, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 957, .adv_w = 142, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1002, .adv_w = 145, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1042, .adv_w = 141, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1087, .adv_w = 163, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1132, .adv_w = 124, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1162, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1192, .adv_w = 163, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1242, .adv_w = 165, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1282, .adv_w = 63, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1292, .adv_w = 60, .box_w = 5, .box_h = 14, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 1327, .adv_w = 137, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1367, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1397, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1452, .adv_w = 169, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1497, .adv_w = 174, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1552, .adv_w = 135, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1587, .adv_w = 174, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1659, .adv_w = 138, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1699, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1734, .adv_w = 123, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1774, .adv_w = 163, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1814, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1859, .adv_w = 207, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1924, .adv_w = 129, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1969, .adv_w = 125, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2009, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2049, .adv_w = 73, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2075, .adv_w = 82, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2100, .adv_w = 73, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2126, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 2154, .adv_w = 98, .box_w = 8, .box_h = 1, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 2158, .adv_w = 62, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 2164, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2192, .adv_w = 137, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2231, .adv_w = 107, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2259, .adv_w = 137, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2303, .adv_w = 126, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2335, .adv_w = 75, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2368, .adv_w = 122, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 2416, .adv_w = 137, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2455, .adv_w = 57, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2465, .adv_w = 57, .box_w = 4, .box_h = 14, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 2493, .adv_w = 118, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2532, .adv_w = 57, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2543, .adv_w = 207, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2587, .adv_w = 137, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2615, .adv_w = 135, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2647, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2689, .adv_w = 137, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 2737, .adv_w = 92, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2757, .adv_w = 107, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2785, .adv_w = 80, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2810, .adv_w = 137, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2838, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2866, .adv_w = 174, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2910, .adv_w = 117, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2942, .adv_w = 112, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 2990, .adv_w = 105, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3018, .adv_w = 84, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3051, .adv_w = 123, .box_w = 2, .box_h = 15, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 3066, .adv_w = 84, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3099, .adv_w = 128, .box_w = 8, .box_h = 2, .ofs_x = 0, .ofs_y = 4}
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



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_OpenSansRegular14p4 = {
#else
lv_font_t ui_font_OpenSansRegular14p4 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_OPENSANSREGULAR14P4*/

