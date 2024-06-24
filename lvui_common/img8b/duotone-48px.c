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

#ifndef LV_ATTRIBUTE_IMG_DUOTONE_48PX
#define LV_ATTRIBUTE_IMG_DUOTONE_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_DUOTONE_48PX uint8_t duotone_48px_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 
  0x00, 0x18, 0x1f, 0xf0, 0x00, 0x00, 
  0x00, 0x1e, 0x0f, 0xfc, 0x00, 0x00, 
  0x00, 0x1f, 0x8f, 0xff, 0x00, 0x00, 
  0x00, 0x1f, 0xc7, 0xff, 0xc0, 0x00, 
  0x00, 0x1f, 0xc1, 0xff, 0xe0, 0x00, 
  0x00, 0x1f, 0xc0, 0x7f, 0xf0, 0x00, 
  0x00, 0x1f, 0xc0, 0x1f, 0xf8, 0x00, 
  0x00, 0x1f, 0xc0, 0x0f, 0xf8, 0x00, 
  0x00, 0x1f, 0xc0, 0x03, 0xf8, 0x00, 
  0x00, 0x1f, 0xc0, 0x03, 0xf8, 0x00, 
  0x00, 0x1f, 0xc0, 0x03, 0xf8, 0x00, 
  0x00, 0x1f, 0xc0, 0x03, 0xf8, 0x00, 
  0x00, 0x1f, 0xc0, 0x0f, 0xf8, 0x00, 
  0x00, 0x1f, 0xc0, 0x1f, 0xf8, 0x00, 
  0x00, 0x1f, 0xc0, 0x7f, 0xf0, 0x00, 
  0x00, 0x1f, 0xc1, 0xff, 0xe0, 0x00, 
  0x00, 0x1f, 0xc7, 0xff, 0xc0, 0x00, 
  0x00, 0x1f, 0x0f, 0xff, 0x00, 0x00, 
  0x00, 0x1c, 0x1f, 0xfc, 0x00, 0x00, 
  0x00, 0x18, 0x1f, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t duotone_48px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = duotone_48px_map,
};
