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

#ifndef LV_ATTRIBUTE_IMG_SD_TROUBLE_BOLD_48PX
#define LV_ATTRIBUTE_IMG_SD_TROUBLE_BOLD_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_SD_TROUBLE_BOLD_48PX uint8_t sd_trouble_bold_48px_map[] = {
  0x05, 0x05, 0x05, 0x03, 	/*Color of index 0*/
  0x42, 0x42, 0x42, 0xe0, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0a, 0xaa, 0xa8, 0x00, 
  0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 
  0x00, 0x00, 0x7f, 0xff, 0xff, 0x80, 
  0x00, 0x00, 0xff, 0xff, 0xff, 0x80, 
  0x00, 0x01, 0xff, 0xff, 0xff, 0x80, 
  0x00, 0x03, 0xfe, 0xaa, 0xaf, 0xc0, 
  0x00, 0x07, 0xf8, 0x00, 0x0f, 0x80, 
  0x00, 0x0f, 0xf0, 0x00, 0x07, 0xc0, 
  0x00, 0x1f, 0xe0, 0x00, 0x0f, 0x80, 
  0x00, 0x3f, 0xc0, 0x00, 0x07, 0xc0, 
  0x00, 0x7f, 0x80, 0x00, 0x0f, 0x80, 
  0x00, 0xff, 0x00, 0x00, 0x07, 0xc0, 
  0x01, 0xfe, 0x00, 0x00, 0x0f, 0x80, 
  0x01, 0xfc, 0x00, 0x00, 0x07, 0xc0, 
  0x03, 0xf8, 0x03, 0xc0, 0x0f, 0x80, 
  0x01, 0xf0, 0x03, 0xc0, 0x07, 0xc0, 
  0x03, 0xf0, 0x03, 0xc0, 0x0f, 0x80, 
  0x01, 0xf0, 0x03, 0xc0, 0x07, 0xc0, 
  0x03, 0xe0, 0x03, 0xc0, 0x0f, 0x80, 
  0x01, 0xf0, 0x03, 0xc0, 0x07, 0xc0, 
  0x03, 0xe0, 0x03, 0xc0, 0x0f, 0x80, 
  0x01, 0xf0, 0x03, 0xc0, 0x07, 0xc0, 
  0x03, 0xe0, 0x03, 0xc0, 0x0f, 0x80, 
  0x01, 0xf0, 0x03, 0xc0, 0x07, 0xc0, 
  0x03, 0xe0, 0x03, 0xc0, 0x0f, 0x80, 
  0x01, 0xf0, 0x00, 0x00, 0x07, 0xc0, 
  0x03, 0xe0, 0x00, 0x00, 0x0f, 0x80, 
  0x01, 0xf0, 0x01, 0x00, 0x07, 0xc0, 
  0x03, 0xe0, 0x03, 0xc0, 0x0f, 0x80, 
  0x01, 0xf0, 0x03, 0xe0, 0x07, 0xc0, 
  0x03, 0xe0, 0x07, 0xc0, 0x0f, 0x80, 
  0x01, 0xf0, 0x03, 0xc0, 0x07, 0xc0, 
  0x03, 0xe0, 0x00, 0x80, 0x0f, 0x80, 
  0x01, 0xf0, 0x00, 0x00, 0x07, 0xc0, 
  0x03, 0xe0, 0x00, 0x00, 0x0f, 0x80, 
  0x01, 0xf0, 0x00, 0x00, 0x07, 0xc0, 
  0x03, 0xe0, 0x00, 0x00, 0x0f, 0x80, 
  0x01, 0xf0, 0x00, 0x00, 0x07, 0xc0, 
  0x03, 0xf5, 0x55, 0x55, 0x5f, 0x80, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 
  0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 
  0x00, 0x15, 0x55, 0x55, 0x54, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t sd_trouble_bold_48px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = sd_trouble_bold_48px_map,
};