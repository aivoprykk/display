#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_FANATIC_48PX
#define LV_ATTRIBUTE_IMG_FANATIC_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_FANATIC_48PX uint8_t fanatic_48px_map[] = {
  0xf3, 0xf3, 0xf3, 0x15, 	/*Color of index 0*/
  0x03, 0x03, 0x03, 0x3f, 	/*Color of index 1*/

  0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 
  0xff, 0xff, 0xff, 0xff, 0xf0, 0xdf, 
  0xff, 0xff, 0xff, 0xff, 0xf2, 0xdf, 
  0xff, 0xff, 0xff, 0xff, 0xe6, 0xdf, 
  0xff, 0xff, 0xff, 0xff, 0x8e, 0xdf, 
  0xff, 0xff, 0xff, 0xff, 0x9e, 0xdf, 
  0xff, 0xff, 0xff, 0xff, 0x3e, 0xdf, 
  0xff, 0xff, 0xff, 0xfc, 0x7e, 0xdf, 
  0xff, 0xff, 0xff, 0xfc, 0xfe, 0xdf, 
  0xff, 0xff, 0xff, 0xf9, 0xfe, 0xdf, 
  0xff, 0xff, 0xff, 0xe3, 0xfe, 0xdf, 
  0xff, 0xff, 0xff, 0xe7, 0xfe, 0xdf, 
  0xff, 0xff, 0xff, 0xcf, 0xfc, 0xdf, 
  0xff, 0xff, 0xff, 0x1f, 0xfc, 0xdf, 
  0xff, 0xff, 0xff, 0x3f, 0xf9, 0xdf, 
  0xff, 0xff, 0xfe, 0x7f, 0xf1, 0xdf, 
  0xff, 0xff, 0xf8, 0xff, 0xe7, 0xdf, 
  0xff, 0xff, 0xf9, 0xff, 0xcf, 0xdf, 
  0xff, 0xff, 0xf3, 0xff, 0x80, 0xdf, 
  0xff, 0xff, 0xe7, 0xff, 0x20, 0xdf, 
  0xff, 0xff, 0xcf, 0xfe, 0x67, 0xdf, 
  0xff, 0xff, 0x9f, 0xfc, 0x0e, 0xdf, 
  0xff, 0xfe, 0x3f, 0xf9, 0x1e, 0xdf, 
  0xff, 0xfe, 0x7f, 0xf3, 0x3e, 0xdf, 
  0xff, 0xfc, 0xff, 0xe0, 0x7e, 0xdf, 
  0xff, 0xfd, 0xff, 0xcc, 0xfe, 0xdf, 
  0xff, 0xf3, 0xff, 0x99, 0xfe, 0xdf, 
  0xff, 0xe7, 0xff, 0x03, 0xfe, 0xdf, 
  0xff, 0xef, 0xfe, 0x67, 0xfe, 0xdf, 
  0xff, 0x9f, 0xfc, 0x4f, 0xfe, 0xdf, 
  0xff, 0xbf, 0xf8, 0x0f, 0xfc, 0xdf, 
  0xff, 0x9f, 0xf3, 0x3f, 0xf9, 0xdf, 
  0xff, 0x8f, 0xe2, 0x3f, 0xf1, 0xdf, 
  0xff, 0xe7, 0xc0, 0x7f, 0xf7, 0xdf, 
  0xff, 0xf3, 0x99, 0xff, 0xcf, 0xdf, 
  0xff, 0xf1, 0x11, 0xff, 0xcf, 0xdf, 
  0xff, 0xfc, 0x27, 0xff, 0x3f, 0xdf, 
  0xff, 0xff, 0xc7, 0xfe, 0x7f, 0xdf, 
  0xff, 0xff, 0xdf, 0xfe, 0x7f, 0xdf, 
  0xff, 0xff, 0xdf, 0xfc, 0x7f, 0xdf, 
  0xff, 0xff, 0xcf, 0xfe, 0x7f, 0xdf, 
  0xff, 0xff, 0xc7, 0xff, 0x3f, 0xdf, 
  0xff, 0xff, 0xf3, 0xff, 0x8f, 0xdf, 
  0xff, 0xff, 0xf9, 0xff, 0xcf, 0xdf, 
  0xff, 0xff, 0xf8, 0xff, 0xe7, 0xdf, 
  0xff, 0xff, 0xfe, 0x7f, 0xf7, 0xdf, 
  0xff, 0xff, 0xff, 0x3f, 0xe7, 0xdf, 
  0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 
};

const lv_img_dsc_t fanatic_48px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = fanatic_48px_map,
};
