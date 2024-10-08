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

#ifndef LV_ATTRIBUTE_IMG_LOFTSAILS_48PX
#define LV_ATTRIBUTE_IMG_LOFTSAILS_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_LOFTSAILS_48PX uint8_t loftsails_48px_map[] = {
  0xba, 0xba, 0xba, 0x76, 	/*Color of index 0*/
  0x01, 0x01, 0x01, 0x41, 	/*Color of index 1*/

  0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 
  0xff, 0xfe, 0x0f, 0xe0, 0x7f, 0xff, 
  0xff, 0xf8, 0xff, 0xfe, 0x1f, 0xff, 
  0xff, 0xe3, 0xff, 0xff, 0xc7, 0xff, 
  0xff, 0xcf, 0xff, 0xff, 0xf3, 0xff, 
  0xff, 0x1f, 0xff, 0xa0, 0x11, 0xff, 
  0xff, 0x7f, 0xf8, 0x0f, 0x80, 0xff, 
  0xfe, 0x7f, 0xe1, 0xff, 0xff, 0xff, 
  0xfc, 0xff, 0xcf, 0xff, 0xff, 0xff, 
  0xfc, 0xff, 0x9f, 0xff, 0xff, 0xff, 
  0xfc, 0xff, 0xbf, 0xff, 0xff, 0xff, 
  0xfc, 0xff, 0xbf, 0xff, 0xff, 0xff, 
  0xfe, 0x7f, 0x9f, 0xff, 0xff, 0xff, 
  0xff, 0x3f, 0xcf, 0xff, 0xff, 0xff, 
  0xff, 0x9f, 0xcf, 0xff, 0xff, 0xff, 
  0xff, 0xcf, 0xe7, 0xff, 0xff, 0xff, 
  0xff, 0xe3, 0xf3, 0xff, 0xff, 0x87, 
  0xff, 0xf1, 0xf9, 0xff, 0xfc, 0x01, 
  0xff, 0xfc, 0xfc, 0xff, 0xf0, 0xfc, 
  0xff, 0xfe, 0x3e, 0x7f, 0xc7, 0xfc, 
  0x7f, 0xff, 0x8f, 0x3f, 0x1f, 0xfe, 
  0x3f, 0xff, 0xe7, 0xbc, 0x7f, 0xfe, 
  0x3f, 0xff, 0xf1, 0xb1, 0xff, 0xfe, 
  0x1f, 0xff, 0xf8, 0x07, 0xff, 0xff, 
  0xdf, 0xff, 0xf0, 0x8f, 0xff, 0xff, 
  0xcf, 0xff, 0xe4, 0x3f, 0xc0, 0xff, 
  0x8f, 0xff, 0xea, 0x7c, 0x0e, 0x7e, 
  0x27, 0xff, 0xe0, 0x00, 0xff, 0x7f, 
  0x07, 0xff, 0xc2, 0x8f, 0xff, 0x7e, 
  0x03, 0xff, 0xd2, 0xff, 0xff, 0x7e, 
  0x09, 0xff, 0xc0, 0xff, 0xff, 0x7e, 
  0x41, 0xff, 0x82, 0xff, 0xff, 0x7e, 
  0x04, 0xff, 0xa8, 0xff, 0xff, 0x7c, 
  0x28, 0x7f, 0x8a, 0xff, 0xfe, 0x7c, 
  0x89, 0x3f, 0x08, 0xff, 0xfe, 0xf9, 
  0x84, 0x1f, 0x1a, 0xff, 0xfe, 0xf9, 
  0xd2, 0x46, 0x18, 0xff, 0xfc, 0xf3, 
  0xc3, 0x10, 0xb0, 0xff, 0xfd, 0xf3, 
  0xe9, 0xc2, 0x31, 0xff, 0xf9, 0xe7, 
  0xf0, 0xf0, 0xf1, 0xff, 0xfb, 0xcf, 
  0xf2, 0x7f, 0xf5, 0xff, 0xf3, 0xdf, 
  0xf9, 0x3f, 0xf1, 0xff, 0xe7, 0x1f, 
  0xfc, 0x9f, 0xf1, 0xff, 0xe6, 0x3f, 
  0xfe, 0x27, 0xe1, 0xff, 0xcc, 0xff, 
  0xff, 0x91, 0xeb, 0xff, 0x99, 0xff, 
  0xff, 0xc4, 0x03, 0xff, 0x23, 0xff, 
  0xff, 0xf2, 0xa7, 0xff, 0x0f, 0xff, 
  0xff, 0xfc, 0x0f, 0xff, 0x3f, 0xff, 
};

const lv_img_dsc_t loftsails_48px = {
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
  .data = loftsails_48px_map,
};
