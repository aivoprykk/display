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

#ifndef LV_ATTRIBUTE_IMG_SETTINGS_24PX
#define LV_ATTRIBUTE_IMG_SETTINGS_24PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_SETTINGS_24PX uint8_t settings_24px_map[] = {
  0x0c, 0x0c, 0x0c, 0x08, 	/*Color of index 0*/
  0x43, 0x43, 0x43, 0xd3, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 
  0x00, 0x7c, 0x00, 
  0x00, 0x3e, 0x00, 
  0x00, 0x66, 0x00, 
  0x0c, 0xe7, 0x30, 
  0x1f, 0xc3, 0xf8, 
  0x1b, 0x00, 0xd8, 
  0x30, 0x00, 0x0c, 
  0x18, 0x3c, 0x18, 
  0x0c, 0x7e, 0x30, 
  0x04, 0x7e, 0x30, 
  0x0c, 0x7e, 0x20, 
  0x0c, 0x7e, 0x30, 
  0x38, 0x3c, 0x38, 
  0x30, 0x00, 0x0c, 
  0x1b, 0x00, 0xd8, 
  0x1f, 0xc3, 0xf8, 
  0x0c, 0xe7, 0x30, 
  0x00, 0x66, 0x00, 
  0x00, 0x6e, 0x00, 
  0x00, 0x3c, 0x00, 
  0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 
};

const lv_img_dsc_t settings_24px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 24,
  .header.h = 24,
  .data_size = 80,
  .data = settings_24px_map,
};
