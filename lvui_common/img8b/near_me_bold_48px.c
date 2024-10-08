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

#ifndef LV_ATTRIBUTE_IMG_NEAR_ME_BOLD_48PX
#define LV_ATTRIBUTE_IMG_NEAR_ME_BOLD_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_NEAR_ME_BOLD_48PX uint8_t near_me_bold_48px_map[] = {
  0x04, 0x04, 0x04, 0x02, 	/*Color of index 0*/
  0x42, 0x42, 0x42, 0xee, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x7f, 0xc0, 
  0x00, 0x00, 0x00, 0x01, 0xff, 0xc0, 
  0x00, 0x00, 0x00, 0x0f, 0xff, 0xc0, 
  0x00, 0x00, 0x00, 0x3f, 0xff, 0x80, 
  0x00, 0x00, 0x01, 0xff, 0xff, 0x80, 
  0x00, 0x00, 0x07, 0xff, 0xdf, 0x00, 
  0x00, 0x00, 0x3f, 0xfe, 0x1f, 0x00, 
  0x00, 0x01, 0xff, 0xf8, 0x3f, 0x00, 
  0x00, 0x07, 0xff, 0xc0, 0x3e, 0x00, 
  0x00, 0x3f, 0xff, 0x00, 0x3e, 0x00, 
  0x01, 0xff, 0xf8, 0x00, 0x7c, 0x00, 
  0x07, 0xff, 0xe0, 0x00, 0x7c, 0x00, 
  0x0f, 0xff, 0x00, 0x00, 0x7c, 0x00, 
  0x0f, 0xf8, 0x00, 0x00, 0xf8, 0x00, 
  0x0f, 0xfc, 0x00, 0x00, 0xf8, 0x00, 
  0x07, 0xff, 0x80, 0x01, 0xf8, 0x00, 
  0x01, 0xff, 0xf0, 0x01, 0xf0, 0x00, 
  0x00, 0x7f, 0xfc, 0x01, 0xf0, 0x00, 
  0x00, 0x0f, 0xfe, 0x03, 0xe0, 0x00, 
  0x00, 0x01, 0xfe, 0x03, 0xe0, 0x00, 
  0x00, 0x00, 0x7f, 0x07, 0xe0, 0x00, 
  0x00, 0x00, 0x1f, 0x07, 0xc0, 0x00, 
  0x00, 0x00, 0x0f, 0x87, 0xc0, 0x00, 
  0x00, 0x00, 0x0f, 0x8f, 0x80, 0x00, 
  0x00, 0x00, 0x0f, 0x8f, 0x80, 0x00, 
  0x00, 0x00, 0x07, 0xdf, 0x80, 0x00, 
  0x00, 0x00, 0x07, 0xdf, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t near_me_bold_48px = {
  #if LVGL_VERSION_MAJOR <= 8
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
#else
  .header.cf = LV_COLOR_FORMAT_I1,
#endif
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = near_me_bold_48px_map,
};
