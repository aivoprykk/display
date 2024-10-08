/*******************************************************************************
 * Size: 9 px
 * Bpp: 4
 * Opts: --bpp 4 --size 9 --font /Users/aivo/Downloads/squareline/squareline_proj_2_13_01_s/assets/SF_Distant_Galaxy.ttf -o /Users/aivo/Downloads/squareline/squareline_proj_2_13_01_s/assets/ui_font_SFDistantGalaxyRegular9p4.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui_common.h"

#ifndef UI_FONT_SFDISTANTGALAXYREGULAR9P4
#define UI_FONT_SFDISTANTGALAXYREGULAR9P4 1
#endif

#if UI_FONT_SFDISTANTGALAXYREGULAR9P4

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0xca, 0xca, 0xb9, 0xa8, 0x54, 0xa8,

    /* U+0022 "\"" */
    0xa8, 0xb6, 0x57, 0x75, 0x0, 0x0,

    /* U+0023 "#" */
    0x3, 0xe2, 0xf0, 0x5f, 0xff, 0xfb, 0x1a, 0x99,
    0xa1, 0xaf, 0xff, 0xf5, 0x2f, 0x4e, 0x50, 0x1,
    0x1, 0x0,

    /* U+0024 "$" */
    0x0, 0x6b, 0x0, 0x0, 0x6f, 0xff, 0xf3, 0xf,
    0xff, 0xee, 0x20, 0xef, 0xe4, 0x0, 0x2, 0xdf,
    0xf3, 0xb, 0xef, 0xff, 0x50, 0xdf, 0xff, 0xb0,
    0x0, 0x6, 0xb0, 0x0,

    /* U+0025 "%" */
    0x0, 0x0, 0x0, 0x0, 0x5e, 0xa1, 0xe4, 0x0,
    0xc4, 0xd9, 0xf2, 0x0, 0x5e, 0xad, 0xc0, 0x0,
    0x0, 0x2f, 0x9d, 0xc1, 0x0, 0x8f, 0x97, 0xa5,
    0x0, 0xaa, 0x3e, 0xd1, 0x0, 0x0, 0x0, 0x0,

    /* U+0026 "&" */
    0x3d, 0xff, 0xff, 0x3b, 0xfc, 0xbb, 0xb2, 0xaf,
    0xf9, 0x0, 0xa, 0xfa, 0x59, 0xd2, 0xbf, 0xcb,
    0xef, 0x33, 0xdf, 0xff, 0xf3,

    /* U+0027 "'" */
    0xa8, 0x57, 0x0,

    /* U+0028 "(" */
    0x6, 0x23, 0xf2, 0x9d, 0xc, 0xc0, 0xcb, 0xb,
    0xc0, 0x6f, 0x0, 0xe4,

    /* U+0029 ")" */
    0x53, 0x8, 0xd0, 0x3f, 0x32, 0xf6, 0x1f, 0x62,
    0xf4, 0x5f, 0x1a, 0x90,

    /* U+002A "*" */
    0x5d, 0x80, 0x9f, 0xe1, 0x5d, 0x80,

    /* U+002B "+" */
    0xe, 0x40, 0xcf, 0xf2, 0x2e, 0x50,

    /* U+002C "," */
    0x32, 0xa9, 0x12,

    /* U+002D "-" */
    0xcf, 0xf2, 0x22, 0x20,

    /* U+002E "." */
    0x43, 0xa8,

    /* U+002F "/" */
    0x0, 0x66, 0x0, 0xeb, 0x4, 0xf5, 0xa, 0xe0,
    0xf, 0x90, 0x5f, 0x30, 0xbd, 0x0, 0x66, 0x0,

    /* U+0030 "0" */
    0x5, 0xdf, 0xc3, 0x5, 0xff, 0xef, 0xf1, 0xbf,
    0x60, 0xaf, 0x7b, 0xf6, 0xa, 0xf7, 0x5f, 0xfe,
    0xff, 0x20, 0x5d, 0xfc, 0x30,

    /* U+0031 "1" */
    0x4f, 0xf0, 0x7f, 0xf0, 0x1f, 0xf0, 0x1f, 0xf0,
    0x1f, 0xf0, 0x1f, 0xf0,

    /* U+0032 "2" */
    0x7f, 0xff, 0xfc, 0x15, 0xbb, 0xbe, 0xf7, 0x2d,
    0xff, 0xff, 0x5b, 0xfa, 0x98, 0x50, 0xdf, 0xcb,
    0xbb, 0x6d, 0xff, 0xff, 0xf9,

    /* U+0033 "3" */
    0xdf, 0xff, 0xf8, 0x9, 0xbb, 0xbf, 0xf1, 0x5,
    0xff, 0xff, 0x0, 0x29, 0x9f, 0xf1, 0x9b, 0xbb,
    0xff, 0x1d, 0xff, 0xff, 0x70,

    /* U+0034 "4" */
    0x4, 0x40, 0xef, 0x33, 0xff, 0xe, 0xf3, 0x6f,
    0xc0, 0xef, 0x39, 0xff, 0xff, 0xf9, 0xae, 0xee,
    0xff, 0x80, 0x0, 0xe, 0xf3,

    /* U+0035 "5" */
    0xdf, 0xff, 0xff, 0x3d, 0xfc, 0xbb, 0xb2, 0xdf,
    0xff, 0xfb, 0x7, 0x99, 0x9c, 0xf7, 0x9b, 0xbb,
    0xdf, 0x7d, 0xff, 0xff, 0xb0,

    /* U+0036 "6" */
    0x3d, 0xff, 0xff, 0x3b, 0xfc, 0xbb, 0xb2, 0xdf,
    0xff, 0xfb, 0xd, 0xfa, 0x9c, 0xf7, 0xbf, 0xcb,
    0xdf, 0x73, 0xdf, 0xff, 0xb0,

    /* U+0037 "7" */
    0xdf, 0xff, 0xff, 0x39, 0xbb, 0xff, 0x90, 0x0,
    0x8f, 0xd0, 0x0, 0x2f, 0xf4, 0x0, 0xc, 0xf9,
    0x0, 0x7, 0xfe, 0x0, 0x0,

    /* U+0038 "8" */
    0x2d, 0xff, 0xfb, 0x9, 0xfd, 0xbe, 0xf5, 0x5f,
    0xff, 0xff, 0x1a, 0xfa, 0x9c, 0xf6, 0xbf, 0xcb,
    0xdf, 0x73, 0xdf, 0xff, 0xb1,

    /* U+0039 "9" */
    0x3d, 0xff, 0xfb, 0xb, 0xfc, 0xbe, 0xf7, 0x9f,
    0xff, 0xff, 0x90, 0x68, 0x9c, 0xf9, 0x5b, 0xbb,
    0xdf, 0x77, 0xff, 0xff, 0xb1,

    /* U+003A ":" */
    0x43, 0xa8, 0x0, 0x43, 0xa8,

    /* U+003B ";" */
    0x43, 0xa8, 0x0, 0x32, 0xa9, 0x12,

    /* U+003C "<" */
    0x2c, 0x39, 0xe0, 0xad, 0x4, 0xf3,

    /* U+003D "=" */
    0xcf, 0xfe, 0x22, 0x22, 0xcf, 0xfe, 0x22, 0x22,

    /* U+003E ">" */
    0x7a, 0x5, 0xf2, 0x3f, 0x49, 0xe0,

    /* U+003F "?" */
    0xdf, 0xff, 0xa0, 0x9b, 0xbe, 0xf5, 0x3d, 0xff,
    0xf3, 0xbe, 0x98, 0x40, 0x43, 0x0, 0x0, 0xa8,
    0x0, 0x0,

    /* U+0040 "@" */
    0x8, 0xbb, 0x20, 0x88, 0xfa, 0xc0, 0xb5, 0xed,
    0x83, 0x88, 0x15, 0xc0, 0x8, 0xbb, 0x30,

    /* U+0041 "A" */
    0x5, 0xff, 0xf7, 0x0, 0xaf, 0xff, 0xc0, 0xe,
    0xfd, 0xff, 0x2, 0xff, 0x5f, 0xf4, 0x6f, 0xff,
    0xff, 0x8a, 0xfc, 0x8b, 0xfc,

    /* U+0042 "B" */
    0xdf, 0xff, 0xf8, 0xd, 0xfa, 0x8f, 0xf2, 0xdf,
    0xff, 0xff, 0xd, 0xf6, 0x3d, 0xf7, 0xdf, 0xa8,
    0xef, 0x7d, 0xff, 0xff, 0xa0,

    /* U+0043 "C" */
    0x5, 0xdf, 0xfd, 0x5f, 0xfe, 0xeb, 0xbf, 0x60,
    0x0, 0xbf, 0x60, 0x0, 0x5f, 0xfe, 0xeb, 0x5,
    0xdf, 0xfd,

    /* U+0044 "D" */
    0xdf, 0xff, 0xc3, 0xd, 0xfe, 0xef, 0xf1, 0xdf,
    0x40, 0xaf, 0x7d, 0xf4, 0xa, 0xf7, 0xdf, 0xee,
    0xff, 0x2d, 0xff, 0xfc, 0x30,

    /* U+0045 "E" */
    0xdf, 0xff, 0xff, 0x3d, 0xfe, 0xee, 0xe2, 0xdf,
    0xff, 0xb0, 0xd, 0xfc, 0x96, 0x0, 0xdf, 0xee,
    0xee, 0x2d, 0xff, 0xff, 0xf3,

    /* U+0046 "F" */
    0xdf, 0xff, 0xff, 0x3d, 0xfe, 0xee, 0xe2, 0xdf,
    0xff, 0xb0, 0xd, 0xfc, 0x96, 0x0, 0xdf, 0x70,
    0x0, 0xd, 0xf7, 0x0, 0x0,

    /* U+0047 "G" */
    0x5, 0xdf, 0xc2, 0x5, 0xff, 0xec, 0x10, 0xbf,
    0x60, 0x0, 0xb, 0xf6, 0xb, 0xf9, 0x5f, 0xfe,
    0xff, 0x90, 0x5d, 0xff, 0xf9,

    /* U+0048 "H" */
    0xdf, 0x70, 0xbf, 0x9d, 0xf7, 0xb, 0xf9, 0xdf,
    0xff, 0xff, 0x9d, 0xfc, 0x9d, 0xf9, 0xdf, 0x70,
    0xbf, 0x9d, 0xf7, 0xb, 0xf9,

    /* U+0049 "I" */
    0xdf, 0x7d, 0xf7, 0xdf, 0x7d, 0xf7, 0xdf, 0x7d,
    0xf7,

    /* U+004A "J" */
    0x4, 0xfc, 0x4, 0xfc, 0x4, 0xfc, 0x4, 0xfc,
    0x4, 0xfc, 0x7, 0xfb, 0xbf, 0xfa, 0x7d, 0xa1,

    /* U+004B "K" */
    0xdf, 0x78, 0xff, 0x3d, 0xfa, 0xff, 0x80, 0xdf,
    0xff, 0xc0, 0xd, 0xff, 0xfb, 0x0, 0xdf, 0xbf,
    0xfe, 0x7d, 0xf7, 0x4d, 0xf9,

    /* U+004C "L" */
    0xdf, 0x70, 0x0, 0xdf, 0x70, 0x0, 0xdf, 0x70,
    0x0, 0xdf, 0x70, 0x0, 0xdf, 0xee, 0xeb, 0xdf,
    0xff, 0xfd,

    /* U+004D "M" */
    0xdf, 0xc0, 0x4f, 0xf5, 0xdf, 0xf8, 0xef, 0xf5,
    0xdf, 0xff, 0xff, 0xf5, 0xdf, 0xff, 0xff, 0xf5,
    0xdf, 0xbf, 0xcf, 0xf5, 0xdf, 0x78, 0x2f, 0xf5,

    /* U+004E "N" */
    0xcd, 0x81, 0xbf, 0x9d, 0xff, 0xdc, 0xf9, 0xdf,
    0xff, 0xff, 0x9d, 0xfb, 0xdf, 0xf9, 0xdf, 0x71,
    0xff, 0x9d, 0xf7, 0xc, 0xf9,

    /* U+004F "O" */
    0x5, 0xdf, 0xc3, 0x5, 0xff, 0xef, 0xf1, 0xbf,
    0x60, 0xaf, 0x7b, 0xf6, 0xa, 0xf7, 0x5f, 0xfe,
    0xff, 0x20, 0x5d, 0xfc, 0x30,

    /* U+0050 "P" */
    0xdf, 0xff, 0xfa, 0xb, 0xee, 0xef, 0xf6, 0x11,
    0x11, 0xdf, 0x7d, 0xff, 0xff, 0xe1, 0xdf, 0x94,
    0x40, 0xd, 0xf7, 0x0, 0x0,

    /* U+0051 "Q" */
    0x5, 0xdf, 0xc3, 0x5, 0xff, 0xef, 0xf1, 0xbf,
    0x60, 0xaf, 0x7b, 0xf6, 0xa, 0xf7, 0x5f, 0xfe,
    0xff, 0xd0, 0x5d, 0xff, 0xff,

    /* U+0052 "R" */
    0xdf, 0xff, 0xfa, 0xb, 0xee, 0xef, 0xf6, 0x23,
    0x33, 0xdf, 0x7d, 0xff, 0xff, 0xc0, 0xdf, 0xbf,
    0xff, 0xdd, 0xf7, 0x4d, 0xff,

    /* U+0053 "S" */
    0x6, 0xef, 0xff, 0x30, 0xff, 0xfe, 0xe2, 0xe,
    0xfe, 0x40, 0x0, 0x2d, 0xff, 0x30, 0xbe, 0xff,
    0xf5, 0xd, 0xff, 0xfb, 0x0,

    /* U+0054 "T" */
    0xdf, 0xff, 0xff, 0x9b, 0xef, 0xff, 0xe7, 0x0,
    0xcf, 0x80, 0x0, 0xc, 0xf8, 0x0, 0x0, 0xcf,
    0x80, 0x0, 0xc, 0xf8, 0x0,

    /* U+0055 "U" */
    0xdf, 0x30, 0x7f, 0x9d, 0xf3, 0x7, 0xf9, 0xdf,
    0x30, 0x7f, 0x9b, 0xf6, 0xa, 0xf7, 0x5f, 0xfe,
    0xff, 0x20, 0x5d, 0xfc, 0x30,

    /* U+0056 "V" */
    0xaf, 0xa0, 0x8f, 0xc6, 0xfe, 0xc, 0xf8, 0x2f,
    0xf3, 0xff, 0x40, 0xef, 0xbf, 0xf0, 0xa, 0xff,
    0xfc, 0x0, 0x5f, 0xff, 0x70,

    /* U+0057 "W" */
    0xaf, 0xa9, 0xff, 0x4f, 0xf5, 0x6f, 0xed, 0xff,
    0xbf, 0xf1, 0x2f, 0xff, 0xff, 0xff, 0xd0, 0xe,
    0xff, 0xff, 0xff, 0x90, 0xa, 0xff, 0xcf, 0xff,
    0x40, 0x5, 0xff, 0x7c, 0xff, 0x0,

    /* U+0058 "X" */
    0x6f, 0xf5, 0x7f, 0xf4, 0xa, 0xff, 0xff, 0x80,
    0x0, 0xcf, 0xfb, 0x0, 0x0, 0xcf, 0xfb, 0x0,
    0xa, 0xff, 0xff, 0x80, 0x6f, 0xf5, 0x7f, 0xf4,

    /* U+0059 "Y" */
    0x8f, 0xe1, 0x9f, 0xe0, 0xe, 0xfb, 0xff, 0x50,
    0x5, 0xff, 0xfc, 0x0, 0x0, 0xcf, 0xf3, 0x0,
    0x0, 0x6f, 0xd0, 0x0, 0x0, 0x6f, 0xd0, 0x0,

    /* U+005A "Z" */
    0xdf, 0xff, 0xff, 0x3b, 0xee, 0xff, 0x90, 0x0,
    0x7f, 0xd0, 0x0, 0x2f, 0xf3, 0x0, 0xc, 0xff,
    0xee, 0x77, 0xff, 0xff, 0xf9,

    /* U+005B "[" */
    0x68, 0x3d, 0xf7, 0xdb, 0xd, 0xb0, 0xdb, 0xd,
    0xb0, 0xdd, 0x3d, 0xf7,

    /* U+005C "\\" */
    0x66, 0x0, 0xbd, 0x0, 0x5f, 0x30, 0xf, 0x90,
    0xa, 0xe0, 0x4, 0xf5, 0x0, 0xeb, 0x0, 0x66,

    /* U+005D "]" */
    0x68, 0x3d, 0xf7, 0x1f, 0x71, 0xf7, 0x1f, 0x71,
    0xf7, 0x7f, 0x7d, 0xf7,

    /* U+005E "^" */
    0x3, 0x50, 0x0, 0xcb, 0x30, 0x86, 0x2c, 0x0,

    /* U+005F "_" */
    0xff, 0xf2, 0x22,

    /* U+0060 "`" */
    0x24, 0x0, 0x36, 0x62,

    /* U+0061 "a" */
    0x5, 0xff, 0xf7, 0x0, 0xaf, 0xff, 0xc0, 0xe,
    0xfd, 0xff, 0x2, 0xff, 0x5f, 0xf4, 0x6f, 0xff,
    0xff, 0x8a, 0xfc, 0x8b, 0xfc,

    /* U+0062 "b" */
    0xdf, 0xff, 0xf8, 0xd, 0xfa, 0x8f, 0xf2, 0xdf,
    0xff, 0xff, 0xd, 0xf6, 0x3d, 0xf7, 0xdf, 0xa8,
    0xef, 0x7d, 0xff, 0xff, 0xa0,

    /* U+0063 "c" */
    0x5, 0xdf, 0xfd, 0x5f, 0xfe, 0xeb, 0xbf, 0x60,
    0x0, 0xbf, 0x60, 0x0, 0x5f, 0xfe, 0xeb, 0x5,
    0xdf, 0xfd,

    /* U+0064 "d" */
    0xdf, 0xff, 0xc3, 0xd, 0xfe, 0xef, 0xf1, 0xdf,
    0x40, 0xaf, 0x7d, 0xf4, 0xa, 0xf7, 0xdf, 0xee,
    0xff, 0x2d, 0xff, 0xfc, 0x30,

    /* U+0065 "e" */
    0xdf, 0xff, 0xff, 0x3d, 0xfe, 0xee, 0xe2, 0xdf,
    0xff, 0xb0, 0xd, 0xfc, 0x96, 0x0, 0xdf, 0xee,
    0xee, 0x2d, 0xff, 0xff, 0xf3,

    /* U+0066 "f" */
    0xdf, 0xff, 0xff, 0x3d, 0xfe, 0xee, 0xe2, 0xdf,
    0xff, 0xb0, 0xd, 0xfc, 0x96, 0x0, 0xdf, 0x70,
    0x0, 0xd, 0xf7, 0x0, 0x0,

    /* U+0067 "g" */
    0x5, 0xdf, 0xff, 0x95, 0xff, 0xee, 0xe7, 0xbf,
    0x60, 0x0, 0xb, 0xf6, 0xb, 0xf9, 0x5f, 0xfe,
    0xff, 0x90, 0x5d, 0xff, 0xf9,

    /* U+0068 "h" */
    0xdf, 0x70, 0xbf, 0x9d, 0xf7, 0xb, 0xf9, 0xdf,
    0xff, 0xff, 0x9d, 0xfc, 0x9d, 0xf9, 0xdf, 0x70,
    0xbf, 0x9d, 0xf7, 0xb, 0xf9,

    /* U+0069 "i" */
    0xdf, 0x7d, 0xf7, 0xdf, 0x7d, 0xf7, 0xdf, 0x7d,
    0xf7,

    /* U+006A "j" */
    0x4, 0xfc, 0x4, 0xfc, 0x4, 0xfc, 0x4, 0xfc,
    0x4, 0xfc, 0x7, 0xfb, 0xbf, 0xfa, 0x7d, 0xa1,

    /* U+006B "k" */
    0xdf, 0x78, 0xff, 0x3d, 0xfa, 0xff, 0x80, 0xdf,
    0xff, 0xc0, 0xd, 0xff, 0xfb, 0x0, 0xdf, 0xbf,
    0xfe, 0x7d, 0xf7, 0x4d, 0xf9,

    /* U+006C "l" */
    0xdf, 0x70, 0x0, 0xdf, 0x70, 0x0, 0xdf, 0x70,
    0x0, 0xdf, 0x70, 0x0, 0xdf, 0xee, 0xeb, 0xdf,
    0xff, 0xfd,

    /* U+006D "m" */
    0xdf, 0xc0, 0x4f, 0xf5, 0xdf, 0xf8, 0xef, 0xf5,
    0xdf, 0xff, 0xff, 0xf5, 0xdf, 0xff, 0xff, 0xf5,
    0xdf, 0xbf, 0xcf, 0xf5, 0xdf, 0x78, 0x2f, 0xf5,

    /* U+006E "n" */
    0xdf, 0xc0, 0xbf, 0x9d, 0xff, 0x9b, 0xf9, 0xdf,
    0xff, 0xef, 0x9d, 0xfe, 0xff, 0xf9, 0xdf, 0x7d,
    0xff, 0x9d, 0xf7, 0x2f, 0xf9,

    /* U+006F "o" */
    0x5, 0xdf, 0xc3, 0x5, 0xff, 0xef, 0xf1, 0xbf,
    0x60, 0xaf, 0x7b, 0xf6, 0xa, 0xf7, 0x5f, 0xfe,
    0xff, 0x20, 0x5d, 0xfc, 0x30,

    /* U+0070 "p" */
    0xdf, 0xff, 0xfa, 0xd, 0xfc, 0xaf, 0xf6, 0xdf,
    0xca, 0xef, 0x6d, 0xff, 0xff, 0xa0, 0xdf, 0x70,
    0x0, 0xd, 0xf7, 0x0, 0x0,

    /* U+0071 "q" */
    0x5, 0xdf, 0xc3, 0x5, 0xff, 0xef, 0xf1, 0xbf,
    0x60, 0xaf, 0x7b, 0xf6, 0xa, 0xf7, 0x5f, 0xfe,
    0xff, 0xd0, 0x5d, 0xff, 0xff,

    /* U+0072 "r" */
    0xdf, 0xff, 0xfa, 0xd, 0xfc, 0xaf, 0xf6, 0xdf,
    0xb7, 0xef, 0x7d, 0xff, 0xff, 0xc0, 0xdf, 0xbf,
    0xff, 0xdd, 0xf7, 0x4d, 0xff,

    /* U+0073 "s" */
    0x6, 0xef, 0xff, 0x30, 0xff, 0xfe, 0xe2, 0xe,
    0xfe, 0x40, 0x0, 0x2d, 0xff, 0x30, 0xbe, 0xff,
    0xf5, 0xd, 0xff, 0xfb, 0x0,

    /* U+0074 "t" */
    0xdf, 0xff, 0xff, 0x9b, 0xef, 0xff, 0xe7, 0x0,
    0xcf, 0x80, 0x0, 0xc, 0xf8, 0x0, 0x0, 0xcf,
    0x80, 0x0, 0xc, 0xf8, 0x0,

    /* U+0075 "u" */
    0xdf, 0x30, 0x7f, 0x9d, 0xf3, 0x7, 0xf9, 0xdf,
    0x30, 0x7f, 0x9b, 0xf6, 0xa, 0xf7, 0x5f, 0xfe,
    0xff, 0x20, 0x5d, 0xfc, 0x30,

    /* U+0076 "v" */
    0xaf, 0xa0, 0x8f, 0xc6, 0xfe, 0xc, 0xf8, 0x2f,
    0xf3, 0xff, 0x40, 0xef, 0xbf, 0xf0, 0xa, 0xff,
    0xfc, 0x0, 0x5f, 0xff, 0x70,

    /* U+0077 "w" */
    0xaf, 0xa9, 0xff, 0x4f, 0xf5, 0x6f, 0xed, 0xff,
    0xbf, 0xf1, 0x2f, 0xff, 0xff, 0xff, 0xd0, 0xe,
    0xff, 0xff, 0xff, 0x90, 0xa, 0xff, 0xcf, 0xff,
    0x40, 0x5, 0xff, 0x7c, 0xff, 0x0,

    /* U+0078 "x" */
    0x6f, 0xf5, 0x7f, 0xf4, 0xa, 0xff, 0xff, 0x80,
    0x0, 0xcf, 0xfb, 0x0, 0x0, 0xcf, 0xfb, 0x0,
    0xa, 0xff, 0xff, 0x80, 0x6f, 0xf5, 0x7f, 0xf4,

    /* U+0079 "y" */
    0x8f, 0xe1, 0x9f, 0xe0, 0xe, 0xfb, 0xff, 0x50,
    0x5, 0xff, 0xfc, 0x0, 0x0, 0xcf, 0xf3, 0x0,
    0x0, 0x6f, 0xd0, 0x0, 0x0, 0x6f, 0xd0, 0x0,

    /* U+007A "z" */
    0xdf, 0xff, 0xff, 0x3b, 0xee, 0xff, 0x90, 0x0,
    0x7f, 0xd0, 0x0, 0x2f, 0xf3, 0x0, 0xc, 0xff,
    0xee, 0x77, 0xff, 0xff, 0xf9,

    /* U+007B "{" */
    0x2, 0x71, 0xe, 0xf3, 0xf, 0x70, 0x2f, 0x60,
    0xcf, 0x20, 0x2f, 0x60, 0xf, 0xb1, 0x9, 0xf3,

    /* U+007C "|" */
    0x65, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,

    /* U+007D "}" */
    0x64, 0x0, 0xdf, 0x40, 0x1f, 0x60, 0xf, 0x80,
    0xc, 0xf2, 0xf, 0x80, 0x7f, 0x60, 0xcd, 0x10,

    /* U+007E "~" */
    0x9b, 0xb2
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 54, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 30, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 60, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 12, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 30, .adv_w = 102, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 58, .adv_w = 121, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 90, .adv_w = 102, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 30, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 114, .adv_w = 42, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 126, .adv_w = 42, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 138, .adv_w = 55, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 144, .adv_w = 54, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 150, .adv_w = 30, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 153, .adv_w = 54, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 157, .adv_w = 30, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 64, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 175, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 52, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 102, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 30, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 30, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 387, .adv_w = 42, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 393, .adv_w = 66, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 401, .adv_w = 42, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 407, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 88, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 102, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 102, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 563, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 42, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 614, .adv_w = 63, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 630, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 120, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 693, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 714, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 735, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 756, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 777, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 798, .adv_w = 102, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 819, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 861, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 882, .adv_w = 155, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 912, .adv_w = 126, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 936, .adv_w = 119, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 960, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 981, .adv_w = 42, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 993, .adv_w = 64, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1009, .adv_w = 42, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1021, .adv_w = 68, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 1029, .adv_w = 48, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1032, .adv_w = 60, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1036, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1057, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1078, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1096, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1117, .adv_w = 102, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1138, .adv_w = 102, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1159, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1180, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1201, .adv_w = 42, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1210, .adv_w = 63, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1226, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1247, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1265, .adv_w = 120, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1289, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1310, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1331, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1352, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1373, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1394, .adv_w = 102, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1415, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1436, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1457, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1478, .adv_w = 155, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1508, .adv_w = 126, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1532, .adv_w = 119, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1556, .adv_w = 108, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1577, .adv_w = 54, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1593, .adv_w = 33, .box_w = 2, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1601, .adv_w = 54, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1617, .adv_w = 54, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 6}
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


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 0, 3, 4, 5, 6, 7,
    8, 9, 10, 0, 0, 0, 0, 0,
    0, 0, 11, 12, 13, 2, 0, 14,
    15, 0, 0, 0, 16, 17, 0, 0,
    2, 18, 19, 20, 21, 22, 23, 24,
    24, 25, 26, 27, 0, 0, 0, 0,
    0, 0, 11, 12, 13, 2, 0, 14,
    0, 0, 0, 0, 16, 17, 0, 0,
    2, 18, 19, 20, 21, 22, 23, 24,
    24, 25, 26, 27, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 3, 4, 5, 6, 7, 0, 8,
    9, 10, 11, 0, 0, 0, 0, 0,
    0, 0, 12, 0, 3, 0, 0, 0,
    3, 0, 0, 13, 0, 0, 0, 0,
    3, 14, 3, 14, 15, 16, 17, 18,
    18, 19, 20, 21, 0, 0, 0, 0,
    0, 0, 12, 0, 3, 0, 0, 0,
    3, 0, 0, 13, 0, 0, 0, 0,
    3, 0, 3, 0, 15, 16, 17, 18,
    18, 19, 20, 21, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    -11, 0, 0, 0, -4, 0, -9, 0,
    0, 0, 0, -13, -20, 0, -9, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 0, -3, 0, 0,
    -7, -21, 0, 0, -4, 0, -7, -19,
    -17, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, -10, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -9, 0, 0, 0, 0,
    0, -10, -9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    -5, 0, 0, -5, 0, 0, -4, -5,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, -4, 0, -3, -4, -10, 0, 0,
    -6, 0, -4, -5, -6, -4, 0, 0,
    0, -3, 0, 0, 0, 0, -4, 0,
    -3, -4, -10, 0, 0, -6, 0, -4,
    -5, -6, -4, -23, -12, -20, -12, -7,
    -3, -20, -12, -4, -13, -13, -23, -25,
    0, -23, -5, 0, -3, -4, -6, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -9, 0, 0, 0,
    0, -5, -10, -11, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -9, 0, 0, 0, 0, 0, -10,
    -10, 0, 0, 0, -7, -9, 0, 0,
    -5, 0, 0, 0, -4, 0, 0, 0,
    0, -15, -6, -19, 0, -22, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, 0, -3, -10, 0, 0, -5, 0,
    -8, -11, -15, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -13, 0, -5, 0, -7, -3, -12,
    0, -4, -4, 0, -17, -25, 0, -13,
    -5, 0, -3, -4, -6, -3, 0, 0,
    0, -10, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, -15, 0, -10,
    0, -21, 0, 0, 0, 0, -8, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, -6, -13, -3, -5, -6, 0,
    -5, 0, -8, -4, -6, -3, -4, -33,
    -5, -18, -5, -37, -5, -12, 0, 0,
    0, -6, 0, -10, 0, 0, 0, 0,
    -14, -23, 0, -12, -4, 0, -7, -16,
    -15, 0, 0, 0, 0, -7, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, -8, 0, -12, 0, -22, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -9, -6, 0,
    -9, 0, -16, 0, -9, 0, 0, 0,
    -4, 0, -9, 0, 0, 0, 0, -13,
    -20, 0, -9, -24, 0, 0, 0, 0,
    0, -11, 0, -4, 0, -5, 0, -10,
    0, 0, 0, 0, -15, -23, 0, -11,
    -3, 0, 0, 0, -4, 0, 0, 0,
    0, 0, 0, 0, -4, 0, 0, 0,
    0, -6, -20, 0, 0, 0, 0, 0,
    0, 0, 0, -13, 0, -7, -4, -3,
    0, -13, 0, 0, -5, -4, -19, -20,
    0, -13, 0, 0, 0, 0, 0, 0,
    0, -10, -19, -9, 0, 0, -14, -10,
    0, -10, -5, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, -21, -9, -17,
    -10, -6, 0, -18, -10, 0, -11, -11,
    -22, -24, 0, -21, -4, 0, 0, 0,
    -4, 0, 0, 0, 0, -8, 0, 0,
    0, 0, 0, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 27,
    .right_class_cnt     = 21,
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
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 1,
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
const lv_font_t ui_font_SFDistantGalaxyRegular9p4 = {
#else
lv_font_t ui_font_SFDistantGalaxyRegular9p4 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_SFDISTANTGALAXYREGULAR9P4*/

