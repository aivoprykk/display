/*******************************************************************************
 * Size: 16 px
 * Bpp: 2
 * Opts: --bpp 2 --size 16 --font /Users/aivo/Dropbox/gt31/squareline_proj_2_13_01/assets/OpenSans-Bold.ttf -o /Users/aivo/Dropbox/gt31/squareline_proj_2_13_01/assets/ui_font_OpenSansBold16p2.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui_common.h"

#ifndef UI_FONT_OPENSANSBOLD16P2
#define UI_FONT_OPENSANSBOLD16P2 1
#endif

#if UI_FONT_OPENSANSBOLD16P2

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x3e, 0x3e, 0x3e, 0x3d, 0x3d, 0x3d, 0x2d, 0x18,
    0x0, 0x18, 0x3e, 0x2d,

    /* U+0022 "\"" */
    0xf2, 0xdf, 0x2d, 0xf1, 0xdb, 0x1d, 0x0, 0x0,

    /* U+0023 "#" */
    0x1, 0xd3, 0x80, 0x1d, 0x34, 0x2, 0xc7, 0x40,
    0x3c, 0x70, 0x3f, 0xff, 0xf2, 0xbe, 0xfa, 0x7,
    0x4e, 0xb, 0xff, 0xfd, 0x6f, 0xbe, 0x90, 0xf2,
    0xc0, 0xe, 0x3c, 0x1, 0xd3, 0x80,

    /* U+0024 "$" */
    0x0, 0xc0, 0x1, 0xbe, 0x42, 0xff, 0xf0, 0xf7,
    0x58, 0x7c, 0xc0, 0xf, 0xf4, 0x0, 0xff, 0xc0,
    0x7, 0xfc, 0x0, 0xdf, 0x58, 0x37, 0xd7, 0xff,
    0xf0, 0x6f, 0xe0, 0x0, 0xc0, 0x0, 0x0, 0x0,

    /* U+0025 "%" */
    0x1f, 0x80, 0x3c, 0x3, 0xfd, 0x7, 0x80, 0x78,
    0xf0, 0xf0, 0x7, 0x4f, 0x1d, 0x0, 0x74, 0xf3,
    0xc0, 0x7, 0x9e, 0x75, 0xf8, 0x3f, 0xdf, 0x3f,
    0xe0, 0xa6, 0xd7, 0x8f, 0x0, 0x3c, 0x74, 0xf0,
    0xb, 0x47, 0x8f, 0x0, 0xf0, 0x3e, 0xe0, 0x2c,
    0x1, 0xf8,

    /* U+0026 "&" */
    0x3, 0xf8, 0x0, 0xf, 0xff, 0x0, 0x1f, 0xf,
    0x0, 0x1f, 0x1f, 0x0, 0xf, 0xbe, 0x0, 0xb,
    0xf8, 0x0, 0x1f, 0xf4, 0x3d, 0x3e, 0x7d, 0xbc,
    0x7c, 0x1f, 0xf4, 0x7e, 0xb, 0xf0, 0x3f, 0xff,
    0xf4, 0xb, 0xfd, 0x7d,

    /* U+0027 "'" */
    0xf3, 0xcf, 0x2c, 0x0,

    /* U+0028 "(" */
    0x7, 0x83, 0xc1, 0xe0, 0xf4, 0x3c, 0x1f, 0x7,
    0x81, 0xe0, 0x7c, 0xf, 0x3, 0xc0, 0xb8, 0xf,
    0x1, 0xe0, 0x0,

    /* U+0029 ")" */
    0x3c, 0xb, 0x40, 0xf0, 0x3d, 0xb, 0x81, 0xe0,
    0x7c, 0x1f, 0x7, 0x82, 0xe0, 0xf4, 0x3c, 0x2e,
    0xf, 0x0, 0x0,

    /* U+002A "*" */
    0x2, 0xd0, 0x0, 0xb0, 0x7, 0xad, 0xb1, 0xff,
    0xfc, 0x3, 0xf0, 0x3, 0xde, 0x1, 0xe3, 0xc0,
    0x0, 0x0,

    /* U+002B "+" */
    0x0, 0xd0, 0x0, 0x74, 0x0, 0x1d, 0x0, 0xaf,
    0xe9, 0x7f, 0xff, 0x40, 0x74, 0x0, 0x1d, 0x0,
    0x7, 0x40,

    /* U+002C "," */
    0x3d, 0x3c, 0x3c, 0x74,

    /* U+002D "-" */
    0xbf, 0xaf, 0xe0,

    /* U+002E "." */
    0x18, 0x3e, 0x2d,

    /* U+002F "/" */
    0x0, 0xf4, 0x3, 0xc0, 0x2e, 0x0, 0xf4, 0x3,
    0xc0, 0x2e, 0x0, 0xf0, 0x7, 0xc0, 0x2e, 0x0,
    0xf0, 0x7, 0xc0, 0x2d, 0x0,

    /* U+0030 "0" */
    0x7, 0xf4, 0x7, 0xff, 0x83, 0xe1, 0xf0, 0xf0,
    0x3d, 0x7c, 0xf, 0x5f, 0x3, 0xe7, 0xc0, 0xf9,
    0xf0, 0x3d, 0x3c, 0xf, 0x4f, 0x87, 0xc1, 0xff,
    0xe0, 0x1f, 0xe0,

    /* U+0031 "1" */
    0x0, 0xf8, 0xf, 0xe1, 0xff, 0x8b, 0x7e, 0x4,
    0xf8, 0x3, 0xe0, 0xf, 0x80, 0x3e, 0x0, 0xf8,
    0x3, 0xe0, 0xf, 0x80, 0x3e,

    /* U+0032 "2" */
    0xb, 0xf8, 0xf, 0xff, 0xc2, 0xd1, 0xf0, 0x0,
    0x3d, 0x0, 0x1f, 0x0, 0xf, 0x80, 0xf, 0xc0,
    0xb, 0xc0, 0xb, 0xc0, 0xb, 0xd0, 0x7, 0xff,
    0xf9, 0xff, 0xfe,

    /* U+0033 "3" */
    0x1f, 0xf8, 0xf, 0xff, 0xc1, 0x42, 0xf0, 0x0,
    0x3c, 0x0, 0x2e, 0x2, 0xfe, 0x0, 0xbf, 0xe0,
    0x0, 0x7d, 0x0, 0xf, 0x84, 0x7, 0xd7, 0xff,
    0xf0, 0xbf, 0xe0,

    /* U+0034 "4" */
    0x0, 0x3e, 0x0, 0x2f, 0x80, 0xf, 0xe0, 0xf,
    0xf8, 0x7, 0xbe, 0x3, 0xcf, 0x82, 0xd3, 0xe1,
    0xe0, 0xf8, 0xbf, 0xff, 0xef, 0xff, 0xf0, 0x3,
    0xe0, 0x0, 0xf8,

    /* U+0035 "5" */
    0x2f, 0xfe, 0xb, 0xff, 0x82, 0xe0, 0x0, 0xf4,
    0x0, 0x3f, 0xf8, 0xf, 0xff, 0xc0, 0x2, 0xf4,
    0x0, 0x3d, 0x0, 0xf, 0x48, 0xb, 0xc3, 0xff,
    0xe0, 0xbf, 0xd0,

    /* U+0036 "6" */
    0x1, 0xff, 0x3, 0xff, 0xc2, 0xf0, 0x0, 0xf0,
    0x0, 0x3d, 0xf8, 0x1f, 0xff, 0xc7, 0xe0, 0xf5,
    0xf0, 0x2e, 0x7c, 0xf, 0x8f, 0x83, 0xd1, 0xff,
    0xf0, 0x1f, 0xe0,

    /* U+0037 "7" */
    0xbf, 0xff, 0xaf, 0xff, 0xe0, 0x0, 0xf0, 0x0,
    0xbc, 0x0, 0x3d, 0x0, 0x1f, 0x0, 0xf, 0x80,
    0x7, 0xc0, 0x2, 0xf0, 0x0, 0xf4, 0x0, 0xbc,
    0x0, 0x3e, 0x0,

    /* U+0038 "8" */
    0xb, 0xf8, 0xb, 0xff, 0xc3, 0xd0, 0xf0, 0xf4,
    0x3c, 0x2f, 0xbe, 0x2, 0xfe, 0x1, 0xff, 0xd0,
    0xf4, 0x7c, 0x7c, 0xb, 0x9f, 0x3, 0xd3, 0xff,
    0xf0, 0x2f, 0xe0,

    /* U+0039 "9" */
    0xb, 0xf4, 0xb, 0xff, 0x83, 0xd1, 0xf1, 0xf0,
    0x3d, 0x7c, 0xf, 0x9f, 0x47, 0xe3, 0xff, 0xf8,
    0x2f, 0x7d, 0x0, 0xf, 0x0, 0xf, 0x82, 0xff,
    0xc0, 0xbf, 0x80,

    /* U+003A ":" */
    0x3d, 0x3e, 0x18, 0x0, 0x0, 0x0, 0x18, 0x3e,
    0x2d,

    /* U+003B ";" */
    0x3d, 0x3e, 0x18, 0x0, 0x0, 0x0, 0x0, 0x3d,
    0x3c, 0x3c, 0x74,

    /* U+003C "<" */
    0x0, 0x0, 0x0, 0x0, 0x90, 0x2, 0xf4, 0xb,
    0xe0, 0x2f, 0x80, 0x1f, 0x80, 0x1, 0xbe, 0x40,
    0x2, 0xfd, 0x0, 0xb, 0x40, 0x0, 0x0,

    /* U+003D "=" */
    0x2a, 0xaa, 0x5f, 0xff, 0xd0, 0x0, 0x0, 0xaa,
    0xa9, 0x7f, 0xff, 0x40,

    /* U+003E ">" */
    0x0, 0x0, 0x18, 0x0, 0x7, 0xe0, 0x0, 0x2f,
    0x80, 0x0, 0xbe, 0x0, 0xb, 0xd0, 0x2f, 0xd0,
    0xfe, 0x40, 0x78, 0x0, 0x0, 0x0, 0x0,

    /* U+003F "?" */
    0x2f, 0xe0, 0xbf, 0xfc, 0x10, 0x3c, 0x0, 0x3c,
    0x0, 0xfc, 0x3, 0xe0, 0xb, 0x80, 0xf, 0x0,
    0x0, 0x0, 0x6, 0x0, 0xf, 0x80, 0xf, 0x40,

    /* U+0040 "@" */
    0x0, 0x6f, 0xe4, 0x0, 0x2f, 0xab, 0xe0, 0xb,
    0x40, 0xb, 0x81, 0xe1, 0xff, 0x3c, 0x3c, 0xbd,
    0xb5, 0xd3, 0x8f, 0xb, 0x4e, 0x38, 0xe0, 0xb0,
    0xe3, 0x8e, 0xb, 0x1d, 0x38, 0xf1, 0xf6, 0xc3,
    0xc7, 0xfb, 0xf4, 0x1f, 0x4, 0x4, 0x0, 0x7e,
    0xab, 0xc0, 0x0, 0xbf, 0xe4, 0x0,

    /* U+0041 "A" */
    0x0, 0xfc, 0x0, 0x1, 0xfe, 0x0, 0x3, 0xef,
    0x0, 0x3, 0xcf, 0x0, 0x7, 0xcb, 0x80, 0xf,
    0x47, 0xc0, 0xf, 0x3, 0xc0, 0x1f, 0xff, 0xe0,
    0x3f, 0xff, 0xf0, 0x3d, 0x1, 0xf0, 0x7c, 0x0,
    0xf8, 0xfc, 0x0, 0xbc,

    /* U+0042 "B" */
    0xbf, 0xf9, 0x2f, 0xff, 0xcb, 0xc1, 0xfa, 0xf0,
    0x3e, 0xbc, 0x1f, 0x6f, 0xff, 0x8b, 0xff, 0xf2,
    0xf0, 0x3e, 0xbc, 0xb, 0xef, 0x3, 0xfb, 0xff,
    0xf6, 0xff, 0xf4,

    /* U+0043 "C" */
    0x1, 0xbf, 0x80, 0x7f, 0xfd, 0xf, 0x81, 0x82,
    0xf0, 0x0, 0x3e, 0x0, 0x3, 0xd0, 0x0, 0x3d,
    0x0, 0x3, 0xe0, 0x0, 0x2f, 0x0, 0x1, 0xf8,
    0x4, 0xb, 0xff, 0xc0, 0x1f, 0xf8,

    /* U+0044 "D" */
    0xbf, 0xf8, 0xb, 0xff, 0xf4, 0xbc, 0x1f, 0xcb,
    0xc0, 0x3e, 0xbc, 0x2, 0xfb, 0xc0, 0x2f, 0xbc,
    0x2, 0xfb, 0xc0, 0x3f, 0xbc, 0x3, 0xeb, 0xc1,
    0xfc, 0xbf, 0xff, 0x4b, 0xff, 0x80,

    /* U+0045 "E" */
    0xbf, 0xfc, 0xbf, 0xfc, 0xbc, 0x0, 0xbc, 0x0,
    0xbc, 0x0, 0xbf, 0xf8, 0xbf, 0xf8, 0xbc, 0x0,
    0xbc, 0x0, 0xbc, 0x0, 0xbf, 0xfc, 0xbf, 0xfc,

    /* U+0046 "F" */
    0xbf, 0xfe, 0xff, 0xfb, 0xc0, 0x2f, 0x0, 0xbc,
    0x2, 0xff, 0xeb, 0xff, 0xaf, 0x0, 0xbc, 0x2,
    0xf0, 0xb, 0xc0, 0x2f, 0x0,

    /* U+0047 "G" */
    0x0, 0xbf, 0xe0, 0x1f, 0xff, 0xc0, 0xfd, 0x5,
    0xb, 0xc0, 0x0, 0x3e, 0x0, 0x0, 0xf4, 0x3f,
    0xd3, 0xd0, 0xff, 0x4f, 0x80, 0x3d, 0x2f, 0x0,
    0xf4, 0x7e, 0x3, 0xd0, 0xbf, 0xff, 0x40, 0x7f,
    0xf8,

    /* U+0048 "H" */
    0xbc, 0x2, 0xfb, 0xc0, 0x2f, 0xbc, 0x2, 0xfb,
    0xc0, 0x2f, 0xbc, 0x2, 0xfb, 0xff, 0xff, 0xbf,
    0xff, 0xfb, 0xc0, 0x2f, 0xbc, 0x2, 0xfb, 0xc0,
    0x2f, 0xbc, 0x2, 0xfb, 0xc0, 0x2f,

    /* U+0049 "I" */
    0xbe, 0xfb, 0xef, 0xbe, 0xfb, 0xef, 0xbe, 0xfb,
    0xef,

    /* U+004A "J" */
    0x2, 0xf0, 0x2f, 0x2, 0xf0, 0x2f, 0x2, 0xf0,
    0x2f, 0x2, 0xf0, 0x2f, 0x2, 0xf0, 0x2f, 0x2,
    0xf0, 0x2f, 0x3, 0xe3, 0xfd, 0x3f, 0x40,

    /* U+004B "K" */
    0xbc, 0x7, 0xcb, 0xc0, 0xf4, 0xbc, 0x3e, 0xb,
    0xcb, 0xc0, 0xbd, 0xf0, 0xb, 0xff, 0x0, 0xbf,
    0xf4, 0xb, 0xdf, 0xc0, 0xbc, 0x3e, 0xb, 0xc2,
    0xf0, 0xbc, 0xf, 0x8b, 0xc0, 0x7d,

    /* U+004C "L" */
    0xbc, 0x0, 0xbc, 0x0, 0xbc, 0x0, 0xbc, 0x0,
    0xbc, 0x0, 0xbc, 0x0, 0xbc, 0x0, 0xbc, 0x0,
    0xbc, 0x0, 0xbc, 0x0, 0xbf, 0xfe, 0xbf, 0xfe,

    /* U+004D "M" */
    0xbf, 0x0, 0x3f, 0xaf, 0xc0, 0xf, 0xeb, 0xf4,
    0x7, 0xfa, 0xef, 0x2, 0xee, 0xbb, 0xc0, 0xfb,
    0xae, 0xb4, 0x7a, 0xeb, 0x9e, 0x2c, 0xba, 0xe3,
    0xcf, 0x2e, 0xb8, 0xbb, 0x8b, 0xae, 0x1f, 0xd2,
    0xeb, 0x83, 0xf0, 0xba, 0xe0, 0xf8, 0x2e,

    /* U+004E "N" */
    0xbf, 0x0, 0xba, 0xfd, 0x2, 0xeb, 0xfc, 0xb,
    0xae, 0xf4, 0x2e, 0xba, 0xf0, 0xba, 0xe3, 0xe2,
    0xeb, 0x8b, 0xcb, 0xae, 0xf, 0xae, 0xb8, 0x1f,
    0xba, 0xe0, 0x3f, 0xeb, 0x80, 0x7f, 0xae, 0x0,
    0xfe,

    /* U+004F "O" */
    0x1, 0xff, 0x80, 0xb, 0xff, 0xf4, 0x1f, 0x80,
    0xfc, 0x2f, 0x0, 0x3d, 0x3e, 0x0, 0x3e, 0x3d,
    0x0, 0x3f, 0x3d, 0x0, 0x3f, 0x3e, 0x0, 0x3e,
    0x2f, 0x0, 0x3d, 0x1f, 0x81, 0xfc, 0xb, 0xff,
    0xf4, 0x1, 0xff, 0x80,

    /* U+0050 "P" */
    0xbf, 0xf8, 0x2f, 0xff, 0x8b, 0xc2, 0xf2, 0xf0,
    0x3d, 0xbc, 0xf, 0x6f, 0xb, 0xcb, 0xff, 0xe2,
    0xff, 0xd0, 0xbc, 0x0, 0x2f, 0x0, 0xb, 0xc0,
    0x2, 0xf0, 0x0,

    /* U+0051 "Q" */
    0x1, 0xff, 0x80, 0xb, 0xff, 0xf4, 0x1f, 0x80,
    0xfc, 0x2f, 0x0, 0x3d, 0x3e, 0x0, 0x3e, 0x3d,
    0x0, 0x3f, 0x3d, 0x0, 0x3f, 0x3e, 0x0, 0x3e,
    0x2f, 0x0, 0x3d, 0x1f, 0x81, 0xfc, 0xb, 0xff,
    0xf4, 0x1, 0xff, 0xd0, 0x0, 0x3, 0xf0, 0x0,
    0x0, 0xfc, 0x0, 0x0, 0x69,

    /* U+0052 "R" */
    0xbf, 0xf4, 0xb, 0xff, 0xe0, 0xbc, 0x2f, 0xb,
    0xc0, 0xf4, 0xbc, 0xf, 0x4b, 0xc2, 0xf0, 0xbf,
    0xfd, 0xb, 0xff, 0x40, 0xbc, 0xbc, 0xb, 0xc3,
    0xe0, 0xbc, 0xf, 0x4b, 0xc0, 0x7c,

    /* U+0053 "S" */
    0x7, 0xfd, 0xb, 0xff, 0xc3, 0xe0, 0x50, 0xf4,
    0x0, 0x3f, 0x40, 0x7, 0xfd, 0x0, 0x3f, 0xd0,
    0x1, 0xfc, 0x0, 0x1f, 0x9, 0xb, 0xc7, 0xff,
    0xe0, 0xbf, 0xd0,

    /* U+0054 "T" */
    0xbf, 0xff, 0xef, 0xff, 0xf0, 0x2f, 0x0, 0xb,
    0xc0, 0x2, 0xf0, 0x0, 0xbc, 0x0, 0x2f, 0x0,
    0xb, 0xc0, 0x2, 0xf0, 0x0, 0xbc, 0x0, 0x2f,
    0x0, 0xb, 0xc0,

    /* U+0055 "U" */
    0xbc, 0x2, 0xeb, 0xc0, 0x2e, 0xbc, 0x2, 0xeb,
    0xc0, 0x2e, 0xbc, 0x2, 0xeb, 0xc0, 0x2e, 0xbc,
    0x2, 0xeb, 0xc0, 0x2e, 0xbc, 0x3, 0xe7, 0xe0,
    0x7d, 0x2f, 0xff, 0x80, 0x7f, 0xd0,

    /* U+0056 "V" */
    0xf8, 0x0, 0xf2, 0xf0, 0xb, 0xc3, 0xc0, 0x3e,
    0xf, 0x80, 0xf4, 0x2f, 0x7, 0xc0, 0x3c, 0x2e,
    0x0, 0xf4, 0xf4, 0x2, 0xe7, 0xc0, 0x7, 0xee,
    0x0, 0xf, 0xf4, 0x0, 0x2f, 0xc0, 0x0, 0x7e,
    0x0,

    /* U+0057 "W" */
    0xf8, 0xb, 0xc0, 0x3d, 0xb8, 0xf, 0xd0, 0x3c,
    0x7c, 0xf, 0xe0, 0x7c, 0x3c, 0x1f, 0xf0, 0xb8,
    0x3d, 0x2d, 0xf0, 0xf4, 0x2e, 0x3d, 0xf4, 0xf0,
    0x1f, 0x3c, 0xb5, 0xf0, 0xf, 0x7c, 0x7a, 0xe0,
    0xf, 0xb8, 0x3e, 0xd0, 0xb, 0xf4, 0x3f, 0xc0,
    0x7, 0xf0, 0x2f, 0xc0, 0x3, 0xf0, 0x1f, 0x80,

    /* U+0058 "X" */
    0x7c, 0x1, 0xf0, 0xfc, 0xf, 0x80, 0xf4, 0xbc,
    0x2, 0xf3, 0xd0, 0x3, 0xfe, 0x0, 0x7, 0xf0,
    0x0, 0x2f, 0xc0, 0x0, 0xff, 0xc0, 0xf, 0x8f,
    0x40, 0x7c, 0x2f, 0x3, 0xd0, 0x3e, 0x2f, 0x0,
    0x7d,

    /* U+0059 "Y" */
    0xbc, 0x3, 0xe3, 0xd0, 0x7c, 0x2f, 0xf, 0x80,
    0xf5, 0xf0, 0xb, 0xfe, 0x0, 0x3f, 0xc0, 0x2,
    0xf8, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0, 0xf,
    0x0, 0x0, 0xf0, 0x0, 0xf, 0x0,

    /* U+005A "Z" */
    0x7f, 0xff, 0x9f, 0xff, 0xe0, 0x1, 0xf0, 0x0,
    0xf4, 0x0, 0xbc, 0x0, 0x7c, 0x0, 0x3e, 0x0,
    0x2f, 0x0, 0x1f, 0x0, 0xf, 0x80, 0xb, 0xff,
    0xfe, 0xff, 0xff,

    /* U+005B "[" */
    0xff, 0xfa, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
    0xf0, 0xf0, 0xf0, 0xf0, 0xfa, 0xff,

    /* U+005C "\\" */
    0xb4, 0x1, 0xf0, 0x3, 0xc0, 0xb, 0x80, 0x1f,
    0x0, 0x3c, 0x0, 0xb8, 0x0, 0xf0, 0x3, 0xd0,
    0xb, 0x80, 0xf, 0x0, 0x3d,

    /* U+005D "]" */
    0xbf, 0x1b, 0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0,
    0xf0, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3c, 0x6f,
    0x2f, 0xc0,

    /* U+005E "^" */
    0x0, 0x40, 0x0, 0xb4, 0x0, 0x3f, 0x0, 0x2d,
    0xd0, 0xe, 0x3c, 0x7, 0x47, 0x43, 0xc0, 0xf1,
    0xd0, 0x1e,

    /* U+005F "_" */
    0x3f, 0xfe, 0x0, 0x0,

    /* U+0060 "`" */
    0x28, 0x1, 0xf0, 0x3, 0xc0,

    /* U+0061 "a" */
    0xb, 0xf8, 0x3, 0xff, 0xc0, 0x40, 0xf4, 0x0,
    0x3d, 0x1f, 0xff, 0x4f, 0x97, 0xd7, 0xc0, 0xf4,
    0xfe, 0xfd, 0x1f, 0xd7, 0x40,

    /* U+0062 "b" */
    0xf8, 0x0, 0x3e, 0x0, 0xf, 0x80, 0x3, 0xeb,
    0xe0, 0xff, 0xfe, 0x3f, 0xb, 0xcf, 0x80, 0xf7,
    0xe0, 0x3d, 0xf8, 0xf, 0x7f, 0xb, 0xcf, 0xff,
    0xe3, 0xef, 0xe0,

    /* U+0063 "c" */
    0x7, 0xfd, 0x1f, 0xfd, 0x3e, 0x0, 0x3d, 0x0,
    0x7c, 0x0, 0x3d, 0x0, 0x3e, 0x1, 0x2f, 0xfd,
    0x7, 0xfc,

    /* U+0064 "d" */
    0x0, 0xb, 0xc0, 0x2, 0xf0, 0x0, 0x7c, 0x2f,
    0xaf, 0x2f, 0xff, 0xcf, 0x83, 0xf3, 0xd0, 0x7d,
    0xf0, 0x1f, 0x3c, 0x7, 0xcf, 0x83, 0xf2, 0xff,
    0xfc, 0x2f, 0x8f,

    /* U+0065 "e" */
    0x7, 0xf8, 0x7, 0xff, 0xc3, 0xd0, 0xb8, 0xfa,
    0xbe, 0x7f, 0xff, 0xcf, 0x0, 0x3, 0xe0, 0x0,
    0x7f, 0xfd, 0x6, 0xfe, 0x0,

    /* U+0066 "f" */
    0x7, 0xf8, 0x3f, 0xe1, 0xf0, 0x1f, 0xfc, 0xbf,
    0xf0, 0x7c, 0x1, 0xf0, 0x7, 0xc0, 0x1f, 0x0,
    0x7c, 0x1, 0xf0, 0x7, 0xc0,

    /* U+0067 "g" */
    0xb, 0xff, 0xcf, 0xaf, 0xd3, 0xc1, 0xf1, 0xf0,
    0x7c, 0x3d, 0x3e, 0x7, 0xfe, 0x2, 0xd4, 0x0,
    0xff, 0xf8, 0x2f, 0xff, 0xad, 0x2, 0xef, 0x0,
    0xba, 0xfa, 0xfc, 0x2f, 0xf8, 0x0,

    /* U+0068 "h" */
    0xf8, 0x0, 0x3e, 0x0, 0xf, 0x80, 0x3, 0xeb,
    0xf0, 0xff, 0xff, 0x3f, 0x7, 0xdf, 0xc0, 0xf7,
    0xe0, 0x3d, 0xf8, 0xf, 0x7e, 0x3, 0xdf, 0x80,
    0xf7, 0xe0, 0x3d,

    /* U+0069 "i" */
    0xbb, 0xe1, 0x3e, 0xfb, 0xef, 0xbe, 0xfb, 0xef,
    0xbe,

    /* U+006A "j" */
    0x2, 0xe0, 0x3e, 0x0, 0x40, 0x3e, 0x3, 0xe0,
    0x3e, 0x3, 0xe0, 0x3e, 0x3, 0xe0, 0x3e, 0x3,
    0xe0, 0x3e, 0x3, 0xe0, 0x3e, 0x3f, 0xd3, 0xf4,

    /* U+006B "k" */
    0xf8, 0x0, 0x3e, 0x0, 0xf, 0x80, 0x3, 0xe0,
    0x7d, 0xf8, 0x7d, 0x3e, 0x3e, 0xf, 0xbe, 0x3,
    0xff, 0x80, 0xfe, 0xf4, 0x3e, 0x2f, 0xf, 0x83,
    0xf3, 0xe0, 0x3e,

    /* U+006C "l" */
    0xfb, 0xef, 0xbe, 0xfb, 0xef, 0xbe, 0xfb, 0xef,
    0xbe,

    /* U+006D "m" */
    0xf2, 0xf8, 0x7f, 0x4f, 0xff, 0xff, 0xfc, 0xfc,
    0x2f, 0x83, 0xdf, 0xc1, 0xf0, 0x3e, 0xf8, 0x1f,
    0x3, 0xef, 0x81, 0xf0, 0x3e, 0xf8, 0x1f, 0x3,
    0xef, 0x81, 0xf0, 0x3e, 0xf8, 0x1f, 0x3, 0xe0,

    /* U+006E "n" */
    0xf2, 0xfc, 0x3f, 0xff, 0xcf, 0xc1, 0xf3, 0xf0,
    0x3d, 0xf8, 0xf, 0x7e, 0x3, 0xdf, 0x80, 0xf7,
    0xe0, 0x3d, 0xf8, 0xf, 0x40,

    /* U+006F "o" */
    0x7, 0xfd, 0x1, 0xff, 0xf4, 0x3e, 0xb, 0xc3,
    0xd0, 0x7c, 0x7c, 0x7, 0xc3, 0xd0, 0x7c, 0x3e,
    0xf, 0xc1, 0xff, 0xf4, 0x7, 0xfd, 0x0,

    /* U+0070 "p" */
    0xf6, 0xf8, 0x3f, 0xff, 0x8f, 0xc2, 0xf3, 0xe0,
    0x3d, 0xf8, 0xf, 0x7e, 0x3, 0xdf, 0xc2, 0xf3,
    0xff, 0xf8, 0xfa, 0xf8, 0x3e, 0x0, 0xf, 0x80,
    0x3, 0xe0, 0x0, 0xf8, 0x0, 0x0,

    /* U+0071 "q" */
    0xb, 0xe7, 0xcb, 0xff, 0xf3, 0xe0, 0xfc, 0xf4,
    0x1f, 0x7c, 0x7, 0xcf, 0x41, 0xf3, 0xe0, 0xfc,
    0xbf, 0xff, 0xb, 0xeb, 0xc0, 0x2, 0xf0, 0x0,
    0xbc, 0x0, 0x2f, 0x0, 0xb, 0xc0,

    /* U+0072 "r" */
    0xf1, 0xff, 0xbf, 0xfe, 0x4f, 0xc0, 0xf8, 0xf,
    0x80, 0xf8, 0xf, 0x80, 0xf8, 0x0,

    /* U+0073 "s" */
    0x1f, 0xf8, 0x3f, 0xfc, 0x7c, 0x0, 0x3f, 0x80,
    0xf, 0xf8, 0x1, 0xfc, 0x0, 0x3d, 0x7f, 0xfc,
    0x2f, 0xe0,

    /* U+0074 "t" */
    0xf, 0x0, 0x3c, 0x7, 0xff, 0x6f, 0xfd, 0x1f,
    0x0, 0x7c, 0x1, 0xf0, 0x7, 0xc0, 0x1f, 0x0,
    0x7f, 0xd0, 0xbf, 0x40,

    /* U+0075 "u" */
    0xf8, 0xf, 0x7e, 0x3, 0xdf, 0x80, 0xf7, 0xe0,
    0x3d, 0xf8, 0xf, 0x7e, 0x3, 0xdb, 0xc2, 0xf5,
    0xff, 0xfd, 0x2f, 0xdb, 0x40,

    /* U+0076 "v" */
    0xf8, 0xb, 0xc7, 0xc0, 0xf8, 0x3d, 0xf, 0x2,
    0xe2, 0xf0, 0x1f, 0x3d, 0x0, 0xf7, 0xc0, 0xb,
    0xf8, 0x0, 0x3f, 0x40, 0x3, 0xf0, 0x0,

    /* U+0077 "w" */
    0xb8, 0x2f, 0x43, 0xd7, 0xc3, 0xf8, 0x3c, 0x3c,
    0x3b, 0xc7, 0xc3, 0xd7, 0x7c, 0xb8, 0x2e, 0xb2,
    0xdf, 0x41, 0xfb, 0x1e, 0xf0, 0xf, 0xf0, 0xfe,
    0x0, 0xfe, 0xf, 0xd0, 0x7, 0xd0, 0xbc, 0x0,

    /* U+0078 "x" */
    0x7c, 0xf, 0x83, 0xf2, 0xf0, 0xf, 0xbd, 0x0,
    0xbf, 0xc0, 0x3, 0xf4, 0x0, 0xbf, 0xc0, 0x1f,
    0x7e, 0x3, 0xe1, 0xf0, 0xbc, 0xf, 0xc0,

    /* U+0079 "y" */
    0xfc, 0xb, 0xc7, 0xc0, 0xf8, 0x3d, 0xf, 0x2,
    0xe2, 0xf0, 0x1f, 0x3d, 0x0, 0xfb, 0xc0, 0x7,
    0xf8, 0x0, 0x3f, 0x40, 0x2, 0xf0, 0x0, 0x2e,
    0x0, 0x7, 0xd0, 0x7, 0xf8, 0x0, 0x7e, 0x0,
    0x0,

    /* U+007A "z" */
    0x7f, 0xfc, 0x7f, 0xfc, 0x0, 0xf8, 0x2, 0xf0,
    0x7, 0xc0, 0xf, 0x40, 0x3e, 0x0, 0x7f, 0xfd,
    0xbf, 0xfd,

    /* U+007B "{" */
    0x2, 0xe0, 0xbe, 0xf, 0x40, 0xf4, 0xf, 0x40,
    0xf4, 0xbe, 0xf, 0xe0, 0x1f, 0x40, 0xf4, 0xf,
    0x40, 0xf4, 0xb, 0xe0, 0x2e,

    /* U+007C "|" */
    0x75, 0xd7, 0x5d, 0x75, 0xd7, 0x5d, 0x75, 0xd7,
    0x5d, 0x75, 0xd7, 0x5d,

    /* U+007D "}" */
    0x7d, 0x1, 0xfc, 0x0, 0xf0, 0x3, 0xc0, 0xf,
    0x0, 0x3d, 0x0, 0x7f, 0x1, 0xfc, 0xf, 0x40,
    0x3c, 0x0, 0xf0, 0x3, 0xc0, 0x7f, 0x1, 0xf4,
    0x0,

    /* U+007E "~" */
    0x1a, 0x40, 0x1f, 0xff, 0xd5, 0xb, 0xf0, 0x0,
    0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 67, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 73, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 121, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 20, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 146, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 82, .adv_w = 231, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 192, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 68, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 164, .adv_w = 87, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 183, .adv_w = 87, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 202, .adv_w = 140, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 220, .adv_w = 146, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 238, .adv_w = 73, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 242, .adv_w = 82, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 245, .adv_w = 73, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 106, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 317, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 479, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 73, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 73, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 553, .adv_w = 146, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 576, .adv_w = 146, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 588, .adv_w = 146, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 611, .adv_w = 122, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 230, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 681, .adv_w = 177, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 172, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 163, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 774, .adv_w = 190, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 143, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 828, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 849, .adv_w = 185, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 882, .adv_w = 196, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 912, .adv_w = 85, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 921, .adv_w = 85, .box_w = 6, .box_h = 15, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 944, .adv_w = 170, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 974, .adv_w = 145, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 998, .adv_w = 241, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1037, .adv_w = 208, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1070, .adv_w = 204, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1106, .adv_w = 161, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1133, .adv_w = 204, .box_w = 12, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1178, .adv_w = 169, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1208, .adv_w = 141, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1235, .adv_w = 148, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1262, .adv_w = 194, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1292, .adv_w = 166, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1325, .adv_w = 248, .box_w = 16, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1373, .adv_w = 171, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1406, .adv_w = 160, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1436, .adv_w = 148, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1463, .adv_w = 85, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1477, .adv_w = 106, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1498, .adv_w = 85, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1516, .adv_w = 146, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1534, .adv_w = 105, .box_w = 8, .box_h = 2, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 1538, .adv_w = 93, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 1543, .adv_w = 155, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1564, .adv_w = 162, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1591, .adv_w = 132, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1609, .adv_w = 162, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1636, .adv_w = 151, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1657, .adv_w = 99, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1678, .adv_w = 145, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1708, .adv_w = 168, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1735, .adv_w = 78, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1744, .adv_w = 78, .box_w = 6, .box_h = 16, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 1768, .adv_w = 159, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1795, .adv_w = 78, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1804, .adv_w = 251, .box_w = 14, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1836, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1857, .adv_w = 159, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1880, .adv_w = 162, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1910, .adv_w = 162, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1940, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1954, .adv_w = 127, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1972, .adv_w = 111, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1992, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2013, .adv_w = 146, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2036, .adv_w = 219, .box_w = 14, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2068, .adv_w = 148, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2091, .adv_w = 146, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 2124, .adv_w = 125, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2142, .adv_w = 101, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2163, .adv_w = 141, .box_w = 3, .box_h = 16, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 2175, .adv_w = 101, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2200, .adv_w = 146, .box_w = 9, .box_h = 4, .ofs_x = 0, .ofs_y = 3}
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
    .kern_dsc = NULL,
    .kern_scale = 0,
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
const lv_font_t ui_font_OpenSansBold16p2 = {
#else
lv_font_t ui_font_OpenSansBold16p2 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_OPENSANSBOLD16P2*/

