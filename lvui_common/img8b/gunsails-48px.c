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

#ifndef LV_ATTRIBUTE_IMG_GUNSAILS_48PX
#define LV_ATTRIBUTE_IMG_GUNSAILS_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_GUNSAILS_48PX uint8_t gunsails_48px_map[] = {
  0x03, 0x03, 0x03, 0x01, 	/*Color of index 0*/
  0x28, 0x2a, 0x2a, 0xf1, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0x98, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xb8, 0x00, 0x00, 
  0x00, 0x00, 0x7f, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x7e, 0x78, 0x00, 0x00, 
  0x00, 0x00, 0xfe, 0x78, 0x00, 0x00, 
  0x00, 0x00, 0xfe, 0x78, 0x00, 0x00, 
  0x00, 0x00, 0xfc, 0x78, 0x00, 0x00, 
  0x00, 0x01, 0xf8, 0x76, 0x00, 0x00, 
  0x00, 0x03, 0xf8, 0x6e, 0x00, 0x00, 
  0x00, 0x03, 0xf8, 0x6e, 0x00, 0x00, 
  0x00, 0x03, 0xf0, 0x1f, 0x00, 0x00, 
  0x00, 0x07, 0xf0, 0x1f, 0x00, 0x00, 
  0x00, 0x0f, 0xe0, 0x1f, 0x80, 0x00, 
  0x00, 0x0f, 0xe0, 0x3f, 0x00, 0x00, 
  0x00, 0x0f, 0xc0, 0x1f, 0x80, 0x00, 
  0x00, 0x1f, 0xf8, 0x1f, 0x80, 0x00, 
  0x00, 0x3f, 0xfe, 0x1f, 0xc0, 0x00, 
  0x00, 0x1f, 0xff, 0xcf, 0xc0, 0x00, 
  0x00, 0x07, 0xff, 0xef, 0xc0, 0x00, 
  0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 
  0x00, 0x00, 0x3f, 0xff, 0xe0, 0x00, 
  0x00, 0x00, 0x07, 0xff, 0xe0, 0x00, 
  0x00, 0x00, 0x03, 0xff, 0xe0, 0x00, 
  0x00, 0x00, 0x00, 0x7f, 0xf0, 0x00, 
  0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x78, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t gunsails_48px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = gunsails_48px_map,
};
