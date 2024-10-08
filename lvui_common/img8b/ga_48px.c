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

#ifndef LV_ATTRIBUTE_IMG_GA_48PX
#define LV_ATTRIBUTE_IMG_GA_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_GA_48PX uint8_t ga_48px_map[] = {
  0x61, 0x5b, 0x57, 0xef, 	/*Color of index 0*/
  0x0b, 0x0a, 0x0a, 0x05, 	/*Color of index 1*/

  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 
  0xff, 0xff, 0xfd, 0x7f, 0xff, 0xff, 
  0xff, 0xff, 0xfd, 0xbf, 0xff, 0xff, 
  0xff, 0xff, 0xfb, 0xbf, 0xff, 0xff, 
  0xff, 0xff, 0xfa, 0xdf, 0xff, 0xff, 
  0xff, 0xff, 0xf4, 0x5f, 0xff, 0xff, 
  0xff, 0xff, 0xec, 0x2f, 0xff, 0xff, 
  0xff, 0xff, 0xe8, 0x37, 0xff, 0xff, 
  0xff, 0xff, 0xd8, 0x17, 0xff, 0xff, 
  0xff, 0xff, 0xd0, 0x1b, 0xff, 0xff, 
  0xff, 0xff, 0xb0, 0x0b, 0xff, 0xff, 
  0xff, 0xff, 0xa0, 0x0d, 0xff, 0xff, 
  0xff, 0xff, 0x60, 0x05, 0xff, 0xff, 
  0xff, 0xfe, 0xc0, 0x02, 0xff, 0xff, 
  0xff, 0xfe, 0xc0, 0x03, 0x7f, 0xff, 
  0xff, 0xfd, 0x80, 0x01, 0x7f, 0xff, 
  0xff, 0xfd, 0x00, 0x01, 0xbf, 0xff, 
  0xff, 0xfb, 0x00, 0x00, 0xbf, 0xff, 
  0xff, 0xfa, 0x00, 0x00, 0xdf, 0xff, 
  0xff, 0xf6, 0x00, 0x00, 0x5f, 0xff, 
  0xff, 0xec, 0x00, 0x00, 0x2f, 0xff, 
  0xff, 0xec, 0x00, 0x00, 0x37, 0xff, 
  0xff, 0xd8, 0x00, 0x00, 0x17, 0xff, 
  0xff, 0xd0, 0x00, 0x00, 0x1b, 0xff, 
  0xff, 0xb0, 0x00, 0x00, 0x0b, 0xff, 
  0xff, 0xa0, 0x00, 0x00, 0x0d, 0xff, 
  0xff, 0x60, 0x00, 0x00, 0x06, 0xff, 
  0xff, 0x40, 0x00, 0x00, 0x02, 0xff, 
  0xfe, 0xc0, 0x00, 0x00, 0x03, 0x7f, 
  0xfd, 0x80, 0x00, 0x00, 0x01, 0x7f, 
  0xfd, 0x80, 0x00, 0x00, 0x01, 0xbf, 
  0xfb, 0x00, 0x00, 0x00, 0x00, 0xbf, 
  0xfa, 0x00, 0x00, 0x00, 0x00, 0x5f, 
  0xf6, 0x00, 0x00, 0x00, 0x00, 0x6f, 
  0xf4, 0x00, 0x00, 0x00, 0x00, 0x2f, 
  0xec, 0x00, 0x00, 0x00, 0x00, 0x37, 
  0xe8, 0x00, 0x00, 0x00, 0x00, 0x17, 
  0xd8, 0x00, 0x00, 0x00, 0x00, 0x1b, 
  0xb0, 0x00, 0x00, 0x00, 0x00, 0x0b, 
  0xbf, 0xff, 0xff, 0xff, 0xff, 0xfd, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
};

const lv_img_dsc_t ga_48px = {
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
  .data = ga_48px_map,
};
