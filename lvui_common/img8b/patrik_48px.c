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

#ifndef LV_ATTRIBUTE_IMG_PATRIK_48PX
#define LV_ATTRIBUTE_IMG_PATRIK_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_PATRIK_48PX uint8_t patrik_48px_map[] = {
  0x00, 0x00, 0x00, 0x06, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xf8, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0xff, 0xff, 0xff, 0xf8, 0xff, 
  0x01, 0xff, 0xff, 0xff, 0xf0, 0xff, 
  0x03, 0xff, 0xff, 0xff, 0xf0, 0xfe, 
  0x03, 0xff, 0xff, 0xff, 0xf0, 0xfe, 
  0x03, 0xff, 0xff, 0xff, 0xf1, 0xfe, 
  0x03, 0xff, 0xff, 0xff, 0xf1, 0xfe, 
  0x07, 0xff, 0xff, 0xff, 0xe1, 0xfe, 
  0x07, 0xf8, 0x00, 0x1f, 0xe1, 0xfc, 
  0x07, 0xf8, 0x00, 0x0f, 0xe1, 0xfc, 
  0x07, 0xf0, 0x00, 0x1f, 0xe3, 0xfc, 
  0x07, 0xf0, 0x00, 0x1f, 0xc3, 0xfc, 
  0x0f, 0xf0, 0xfe, 0x1f, 0xc3, 0xf8, 
  0x0f, 0xf1, 0xfe, 0x1f, 0xc3, 0xf8, 
  0x0f, 0xe1, 0xfe, 0x3f, 0xc3, 0xf8, 
  0x0f, 0xe1, 0xfc, 0x3f, 0xc7, 0xf8, 
  0x0f, 0xe1, 0xfc, 0x3f, 0x87, 0xf8, 
  0x1f, 0xe3, 0xfc, 0x3f, 0x87, 0xf0, 
  0x1f, 0xe1, 0xfc, 0x3f, 0x87, 0xf0, 
  0x1f, 0xc3, 0xf8, 0x7f, 0x8f, 0xf0, 
  0x1f, 0xc3, 0xfc, 0x7f, 0x8f, 0xf0, 
  0x3f, 0xc3, 0xf8, 0x7f, 0x0f, 0xf0, 
  0x3f, 0xc7, 0xf8, 0x00, 0x0f, 0xe0, 
  0x3f, 0x87, 0xf8, 0x00, 0x0f, 0xe0, 
  0x3f, 0x87, 0xf0, 0x00, 0x1f, 0xe0, 
  0x3f, 0x87, 0xf8, 0x00, 0x1f, 0xe0, 
  0x7f, 0x87, 0xff, 0xff, 0xff, 0xc0, 
  0x7f, 0x8f, 0xff, 0xff, 0xff, 0xc0, 
  0x7f, 0x0f, 0xff, 0xff, 0xff, 0xc0, 
  0x7f, 0x0f, 0xff, 0xff, 0xff, 0xc0, 
  0xff, 0x0f, 0xff, 0xff, 0xff, 0xc0, 
  0xff, 0x1f, 0xff, 0xff, 0xff, 0x80, 
  0xff, 0x0f, 0xff, 0xff, 0xff, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t patrik_48px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = patrik_48px_map,
};