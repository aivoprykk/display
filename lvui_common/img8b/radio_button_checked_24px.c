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

#ifndef LV_ATTRIBUTE_IMG_RADIO_BUTTON_CHECKED_24PX
#define LV_ATTRIBUTE_IMG_RADIO_BUTTON_CHECKED_24PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_RADIO_BUTTON_CHECKED_24PX uint8_t radio_button_checked_24px_map[] = {
  0x14, 0x14, 0x14, 0x06, 	/*Color of index 0*/
  0x42, 0x42, 0x42, 0xcc, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 
  0x00, 0x7f, 0x00, 
  0x01, 0xff, 0xc0, 
  0x07, 0x00, 0xe0, 
  0x0e, 0x00, 0x70, 
  0x1c, 0x00, 0x30, 
  0x18, 0x38, 0x18, 
  0x30, 0x7e, 0x08, 
  0x30, 0xff, 0x0c, 
  0x31, 0xff, 0x8c, 
  0x31, 0xff, 0x8c, 
  0x31, 0xff, 0x8c, 
  0x30, 0xff, 0x8c, 
  0x30, 0xff, 0x0c, 
  0x10, 0x7e, 0x0c, 
  0x18, 0x3c, 0x18, 
  0x0c, 0x00, 0x38, 
  0x0e, 0x00, 0x70, 
  0x07, 0x00, 0xe0, 
  0x03, 0xff, 0x80, 
  0x00, 0xfe, 0x00, 
  0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 
};

const lv_img_dsc_t radio_button_checked_24px = {
  #if LVGL_VERSION_MAJOR <= 8
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
#else
  .header.cf = LV_COLOR_FORMAT_I1,
#endif
  .header.w = 24,
  .header.h = 24,
  .data_size = 80,
  .data = radio_button_checked_24px_map,
};
