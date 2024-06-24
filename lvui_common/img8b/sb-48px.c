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

#ifndef LV_ATTRIBUTE_IMG_SB_48PX
#define LV_ATTRIBUTE_IMG_SB_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_SB_48PX uint8_t sb_48px_map[] = {
  0x00, 0x00, 0x07, 0x00, 	/*Color of index 0*/
  0x26, 0x1f, 0xea, 0x8b, 	/*Color of index 1*/

  0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x06, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x06, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x0e, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x36, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x76, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x76, 0x9c, 0x00, 0x00, 
  0x00, 0x00, 0x7e, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0xff, 0xfe, 0x00, 0x00, 
  0x00, 0x00, 0x7c, 0xfe, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x1e, 0x00, 0x00, 
  0x00, 0x00, 0xfe, 0x7e, 0x00, 0x00, 
  0x00, 0x00, 0x6b, 0xfe, 0x80, 0x00, 
  0x00, 0x03, 0xe2, 0xff, 0x80, 0x00, 
  0x00, 0x03, 0xe2, 0xfd, 0x80, 0x00, 
  0x00, 0x03, 0x76, 0x0d, 0x80, 0x00, 
  0x00, 0x01, 0xb2, 0xdd, 0x80, 0x00, 
  0x00, 0x01, 0xf6, 0xdf, 0x00, 0x00, 
  0x00, 0x00, 0xdf, 0xfe, 0xa0, 0x00, 
  0x00, 0x3f, 0xbc, 0x3b, 0xf8, 0x00, 
  0x00, 0x3f, 0xee, 0x77, 0xfc, 0x00, 
  0x00, 0x38, 0xee, 0xee, 0x18, 0x00, 
  0x00, 0x38, 0x7f, 0xfc, 0x1c, 0x00, 
  0x00, 0x30, 0x1f, 0xf8, 0x18, 0x00, 
  0x00, 0x38, 0x00, 0x00, 0x5c, 0x00, 
  0x00, 0x3f, 0x00, 0x01, 0xf8, 0x00, 
  0x00, 0x1f, 0xc0, 0x03, 0xf8, 0x00, 
  0x00, 0x01, 0xc0, 0x07, 0x80, 0x00, 
  0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 
  0x00, 0x00, 0xe0, 0x1e, 0x00, 0x00, 
  0x00, 0x00, 0x70, 0x0e, 0x00, 0x00, 
  0x00, 0x01, 0xe0, 0x0f, 0x00, 0x00, 
  0x00, 0x01, 0xc0, 0x07, 0x00, 0x00, 
  0x00, 0x01, 0xc0, 0x0e, 0x00, 0x00, 
  0x00, 0x01, 0xe0, 0x1e, 0x00, 0x00, 
  0x00, 0x00, 0xe0, 0x0e, 0x00, 0x00, 
  0x00, 0x00, 0x79, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x38, 0xff, 0x00, 0x00, 
  0x00, 0x1f, 0xff, 0x9f, 0xf8, 0x00, 
  0x00, 0x3f, 0xff, 0x9f, 0xf8, 0x00, 
  0x00, 0x3f, 0xfa, 0xaa, 0xbc, 0x00, 
  0x00, 0x38, 0x07, 0xf0, 0x18, 0x00, 
  0x00, 0x38, 0x0b, 0xf8, 0x1c, 0x00, 
  0x00, 0x38, 0x0c, 0x38, 0x1c, 0x00, 
  0x00, 0x3f, 0xfc, 0x3f, 0xfc, 0x00, 
  0x00, 0x3f, 0xf8, 0x3f, 0xf8, 0x00, 
  0x00, 0x1f, 0xf8, 0x0f, 0xf0, 0x00, 
};

const lv_img_dsc_t sb_48px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = sb_48px_map,
};
