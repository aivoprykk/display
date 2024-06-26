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

#ifndef LV_ATTRIBUTE_IMG_Z_48PX
#define LV_ATTRIBUTE_IMG_Z_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_Z_48PX uint8_t z_48px_map[] = {
  0x04, 0x04, 0x04, 0x04, 	/*Color of index 0*/
  0x23, 0x7c, 0x97, 0xf5, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0a, 0xaa, 0xaa, 0xa0, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 
  0x7f, 0xff, 0xff, 0xff, 0xf0, 0x00, 
  0x3f, 0xff, 0xff, 0xff, 0xfc, 0x00, 
  0x1f, 0xff, 0xff, 0xff, 0xfc, 0x00, 
  0x0f, 0xff, 0xff, 0xff, 0xff, 0x00, 
  0x07, 0xff, 0xff, 0xff, 0xff, 0x00, 
  0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x00, 0x7f, 0xff, 0xff, 0xff, 0xf0, 
  0x00, 0x3f, 0xff, 0xff, 0xff, 0xfc, 
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xfa, 
  0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x14, 0x10, 0x50, 0x10, 0x00, 
  0x00, 0x0a, 0x20, 0xd0, 0x60, 0x00, 
  0x00, 0x1c, 0x10, 0x78, 0x30, 0x00, 
  0x00, 0x0a, 0x30, 0xf0, 0x30, 0x00, 
  0x00, 0x18, 0x10, 0x58, 0x50, 0x00, 
  0x00, 0x08, 0x30, 0xd0, 0x30, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t z_48px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = z_48px_map,
};