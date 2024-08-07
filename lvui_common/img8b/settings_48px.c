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

#ifndef LV_ATTRIBUTE_IMG_SETTINGS_48PX
#define LV_ATTRIBUTE_IMG_SETTINGS_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_SETTINGS_48PX uint8_t settings_48px_map[] = {
  0x08, 0x08, 0x08, 0x04, 	/*Color of index 0*/
  0x43, 0x43, 0x43, 0xe6, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x1c, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x3c, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 
  0x00, 0xc0, 0x38, 0x3c, 0x03, 0x00, 
  0x00, 0xf0, 0xf8, 0x1f, 0x1f, 0x00, 
  0x01, 0xff, 0xf8, 0x1f, 0xff, 0x80, 
  0x03, 0xff, 0xe0, 0x07, 0xff, 0xc0, 
  0x03, 0xcf, 0x80, 0x01, 0xf3, 0xc0, 
  0x07, 0x83, 0x00, 0x00, 0xc1, 0xe0, 
  0x07, 0x00, 0x00, 0x00, 0x01, 0xe0, 
  0x0f, 0x80, 0x01, 0x40, 0x00, 0xf0, 
  0x07, 0xc0, 0x0f, 0xf0, 0x03, 0xe0, 
  0x03, 0xe0, 0x1f, 0xf8, 0x07, 0xc0, 
  0x01, 0xf0, 0x3f, 0xfc, 0x1f, 0x80, 
  0x00, 0x78, 0x3f, 0xfc, 0x0e, 0x00, 
  0x00, 0x70, 0x3f, 0xfc, 0x1e, 0x00, 
  0x00, 0x78, 0x7f, 0xfe, 0x0e, 0x00, 
  0x00, 0x70, 0x3f, 0xfc, 0x0e, 0x00, 
  0x00, 0x78, 0x7f, 0xfe, 0x1e, 0x00, 
  0x00, 0x70, 0x3f, 0xfc, 0x0e, 0x00, 
  0x01, 0xf8, 0x3f, 0xfc, 0x1f, 0x80, 
  0x03, 0xe0, 0x1f, 0xf8, 0x07, 0xc0, 
  0x07, 0xc0, 0x0f, 0xf0, 0x03, 0xe0, 
  0x0f, 0x80, 0x02, 0x80, 0x01, 0xf0, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 
  0x07, 0x81, 0x00, 0x00, 0xc1, 0xe0, 
  0x03, 0xcf, 0x80, 0x01, 0xf3, 0xc0, 
  0x03, 0xff, 0xe0, 0x07, 0xff, 0xc0, 
  0x01, 0xff, 0xf8, 0x1f, 0xff, 0x80, 
  0x00, 0xf8, 0xf8, 0x1f, 0x1f, 0x00, 
  0x00, 0xc0, 0x3c, 0x3c, 0x03, 0x00, 
  0x00, 0x00, 0x38, 0x1c, 0x00, 0x00, 
  0x00, 0x00, 0x1c, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x1c, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t settings_48px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = settings_48px_map,
};