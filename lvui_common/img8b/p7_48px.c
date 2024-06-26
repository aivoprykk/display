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

#ifndef LV_ATTRIBUTE_IMG_P7_48PX
#define LV_ATTRIBUTE_IMG_P7_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_P7_48PX uint8_t p7_48px_map[] = {
  0x00, 0x00, 0x00, 0x05, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xe9, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0b, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xff, 0xe0, 0x00, 
  0x00, 0x01, 0xff, 0xff, 0xf8, 0x00, 
  0x00, 0x07, 0xfd, 0x5f, 0xfe, 0x00, 
  0x00, 0x0f, 0xc0, 0x00, 0xff, 0x00, 
  0x00, 0x3e, 0x00, 0x00, 0x3f, 0xc0, 
  0x00, 0x78, 0x00, 0x00, 0x0f, 0xe0, 
  0x00, 0xe0, 0x00, 0x00, 0x03, 0xe0, 
  0x01, 0xc0, 0x00, 0x00, 0x01, 0xf0, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0xf8, 
  0x06, 0x00, 0x00, 0x00, 0x00, 0x78, 
  0x0e, 0x00, 0x00, 0x00, 0x00, 0x3c, 
  0x0c, 0x00, 0x00, 0x00, 0x00, 0x3c, 
  0x18, 0x00, 0x00, 0x00, 0x00, 0x1e, 
  0x30, 0x00, 0x00, 0x00, 0x00, 0x1e, 
  0x30, 0x00, 0x00, 0x00, 0x00, 0x1e, 
  0x60, 0x00, 0x14, 0x00, 0x00, 0x0f, 
  0x60, 0x17, 0xff, 0x00, 0x00, 0x0f, 
  0x6f, 0xff, 0xff, 0x80, 0x00, 0x0f, 
  0x7f, 0xff, 0xff, 0x80, 0x00, 0x0f, 
  0xff, 0xff, 0xff, 0x80, 0x00, 0x0f, 
  0xff, 0xf4, 0x3f, 0x80, 0x00, 0x0f, 
  0xe8, 0x00, 0x3f, 0x80, 0x00, 0x0f, 
  0x80, 0x00, 0x3f, 0x00, 0x00, 0x0f, 
  0x80, 0x00, 0x3f, 0x00, 0x00, 0x1e, 
  0x80, 0x00, 0x7e, 0x00, 0x00, 0x1e, 
  0x80, 0x00, 0xfe, 0x00, 0x00, 0x1e, 
  0x80, 0x00, 0xfc, 0x00, 0x00, 0x1e, 
  0x40, 0x01, 0xf8, 0x00, 0x00, 0x3c, 
  0x40, 0x03, 0xf0, 0x00, 0x00, 0x3c, 
  0x40, 0x07, 0xf0, 0x00, 0x00, 0x78, 
  0x40, 0x0f, 0xe0, 0x00, 0x00, 0xf8, 
  0x20, 0x1f, 0xc0, 0x00, 0x00, 0xf0, 
  0x20, 0x3f, 0x80, 0x00, 0x01, 0xe0, 
  0x10, 0x7f, 0x00, 0x00, 0x03, 0xc0, 
  0x10, 0xff, 0x00, 0x00, 0x07, 0x80, 
  0x09, 0xfe, 0x00, 0x00, 0x0f, 0x00, 
  0x07, 0xfc, 0x00, 0x00, 0x1e, 0x00, 
  0x03, 0xf8, 0x00, 0x00, 0x7c, 0x00, 
  0x01, 0xf0, 0x00, 0x01, 0xf0, 0x00, 
  0x00, 0xe0, 0x00, 0x07, 0xe0, 0x00, 
  0x00, 0x38, 0x00, 0x1f, 0x80, 0x00, 
  0x00, 0x0f, 0x45, 0xfc, 0x00, 0x00, 
  0x00, 0x01, 0xff, 0xd0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t p7_48px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = p7_48px_map,
};