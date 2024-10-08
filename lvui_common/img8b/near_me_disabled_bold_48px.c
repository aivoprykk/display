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

#ifndef LV_ATTRIBUTE_IMG_NEAR_ME_DISABLED_BOLD_48PX
#define LV_ATTRIBUTE_IMG_NEAR_ME_DISABLED_BOLD_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_NEAR_ME_DISABLED_BOLD_48PX uint8_t near_me_disabled_bold_48px_map[] = {
  0x07, 0x07, 0x07, 0x05, 	/*Color of index 0*/
  0x42, 0x42, 0x42, 0xf2, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0xc0, 0x00, 0x00, 0x00, 0x10, 
  0x03, 0xe0, 0x00, 0x00, 0x00, 0x70, 
  0x03, 0xf0, 0x00, 0x00, 0x03, 0xe0, 
  0x00, 0xf8, 0x00, 0x00, 0x1f, 0xe0, 
  0x00, 0xfc, 0x00, 0x00, 0x7f, 0xe0, 
  0x00, 0x3e, 0x00, 0x03, 0xff, 0xc0, 
  0x00, 0x3f, 0x00, 0x1f, 0xff, 0xc0, 
  0x00, 0x0f, 0x80, 0x7f, 0xff, 0x80, 
  0x00, 0x0f, 0xc1, 0xff, 0xff, 0x80, 
  0x00, 0x03, 0xe0, 0xff, 0xdf, 0x80, 
  0x00, 0x03, 0xf0, 0xfe, 0x1f, 0x00, 
  0x00, 0x01, 0xf8, 0x38, 0x3f, 0x00, 
  0x00, 0x0f, 0xfc, 0x00, 0x3e, 0x00, 
  0x00, 0x7f, 0xfe, 0x00, 0x3e, 0x00, 
  0x01, 0xff, 0xff, 0x00, 0x7e, 0x00, 
  0x0f, 0xff, 0xdf, 0x80, 0x7c, 0x00, 
  0x0f, 0xff, 0x07, 0xc0, 0xfc, 0x00, 
  0x0f, 0xfc, 0x07, 0xe0, 0xfc, 0x00, 
  0x0f, 0xfe, 0x01, 0xf0, 0x78, 0x00, 
  0x0f, 0xff, 0xc1, 0xf8, 0x38, 0x00, 
  0x03, 0xff, 0xf0, 0x7c, 0x30, 0x00, 
  0x00, 0x7f, 0xfe, 0x3e, 0x00, 0x00, 
  0x00, 0x1f, 0xfe, 0x3f, 0x00, 0x00, 
  0x00, 0x03, 0xff, 0x0f, 0x80, 0x00, 
  0x00, 0x00, 0xff, 0x0f, 0xc0, 0x00, 
  0x00, 0x00, 0x1f, 0x07, 0xe0, 0x00, 
  0x00, 0x00, 0x1f, 0x87, 0xf0, 0x00, 
  0x00, 0x00, 0x0f, 0x8f, 0xf8, 0x00, 
  0x00, 0x00, 0x0f, 0x8f, 0xfc, 0x00, 
  0x00, 0x00, 0x0f, 0xdf, 0xfe, 0x00, 
  0x00, 0x00, 0x07, 0xdf, 0xbf, 0x00, 
  0x00, 0x00, 0x07, 0xff, 0x0f, 0x80, 
  0x00, 0x00, 0x03, 0xff, 0x0f, 0xc0, 
  0x00, 0x00, 0x03, 0xfe, 0x03, 0xe0, 
  0x00, 0x00, 0x03, 0xfe, 0x03, 0xf0, 
  0x00, 0x00, 0x01, 0xfe, 0x00, 0xf8, 
  0x00, 0x00, 0x01, 0xfc, 0x00, 0xfc, 
  0x00, 0x00, 0x00, 0xfc, 0x00, 0x3e, 
  0x00, 0x00, 0x00, 0xfc, 0x00, 0x3e, 
  0x00, 0x00, 0x00, 0xf8, 0x00, 0x0e, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t near_me_disabled_bold_48px = {
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
  .data = near_me_disabled_bold_48px_map,
};
