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

#ifndef LV_ATTRIBUTE_IMG_ESPIDF_LOGO_V3_48PX
#define LV_ATTRIBUTE_IMG_ESPIDF_LOGO_V3_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_ESPIDF_LOGO_V3_48PX uint8_t espidf_logo_v3_48px_map[] = {
  0x04, 0x05, 0x19, 0x02, 	/*Color of index 0*/
  0x2c, 0x35, 0xe6, 0xc9, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x02, 0xa0, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 
  0x00, 0x01, 0xf0, 0x17, 0x80, 0x00, 
  0x00, 0x03, 0x83, 0xe1, 0xe0, 0x00, 
  0x00, 0x0e, 0x03, 0xfe, 0x70, 0x00, 
  0x00, 0x1c, 0xf0, 0xff, 0x98, 0x00, 
  0x00, 0x3b, 0xfe, 0x3f, 0xcc, 0x00, 
  0x00, 0x33, 0xff, 0x8f, 0xe6, 0x00, 
  0x00, 0x67, 0xff, 0xe7, 0xf7, 0x00, 
  0x00, 0xc7, 0xff, 0xf1, 0xfb, 0x00, 
  0x00, 0xc0, 0xbf, 0xf8, 0xf9, 0x80, 
  0x01, 0x80, 0x07, 0xfe, 0x7d, 0x80, 
  0x01, 0x8f, 0xe1, 0xff, 0x7e, 0xc0, 
  0x03, 0x3f, 0xf8, 0xff, 0x1e, 0xc0, 
  0x03, 0x7f, 0xfe, 0x3f, 0x9e, 0x40, 
  0x03, 0x7f, 0xff, 0x9f, 0xcf, 0x60, 
  0x03, 0x7f, 0xff, 0xcf, 0xef, 0x60, 
  0x03, 0x7c, 0xff, 0xe7, 0xe7, 0x60, 
  0x06, 0xfc, 0x1f, 0xf7, 0xf7, 0x60, 
  0x03, 0x7f, 0xc7, 0xf3, 0xf3, 0x60, 
  0x03, 0x7f, 0xf3, 0xf9, 0xfa, 0x60, 
  0x03, 0x3f, 0xf9, 0xf9, 0xf8, 0x60, 
  0x03, 0x1f, 0xfc, 0xfc, 0xf8, 0x60, 
  0x03, 0x0f, 0xfe, 0xfc, 0xfc, 0xc0, 
  0x01, 0x80, 0xfe, 0x7e, 0xfc, 0xc0, 
  0x01, 0x80, 0x7f, 0x7e, 0x7c, 0xc0, 
  0x01, 0x87, 0x3f, 0x7e, 0xfd, 0x80, 
  0x00, 0xcf, 0x9f, 0x3e, 0x79, 0x80, 
  0x00, 0xef, 0x9f, 0x3e, 0x7b, 0x00, 
  0x00, 0x6f, 0x9f, 0xbe, 0x63, 0x00, 
  0x00, 0x37, 0x1f, 0x3e, 0x0e, 0x00, 
  0x00, 0x18, 0x3f, 0x3e, 0x0c, 0x00, 
  0x00, 0x0c, 0x3f, 0x7e, 0x38, 0x00, 
  0x00, 0x07, 0x0f, 0x1c, 0x70, 0x00, 
  0x00, 0x03, 0xc0, 0x01, 0xc0, 0x00, 
  0x00, 0x00, 0xfa, 0x2f, 0x80, 0x00, 
  0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xac, 0xa4, 0x99, 0x2d, 0x00, 
  0x00, 0xaa, 0xb4, 0x96, 0x4d, 0x80, 
  0x00, 0x9c, 0xdc, 0xab, 0xfb, 0x00, 
  0x00, 0xb0, 0xa0, 0x59, 0x24, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t espidf_logo_v3_48px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = espidf_logo_v3_48px_map,
};
