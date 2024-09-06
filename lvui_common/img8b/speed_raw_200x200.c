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

#ifndef LV_ATTRIBUTE_IMG_SPEED_RAW_200X200
#define LV_ATTRIBUTE_IMG_SPEED_RAW_200X200
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_SPEED_RAW_200X200 uint8_t speed_raw_200x200_map[] = {
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xe0, 0x00, 0x00, 0x80, 0x3f, 0xee, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xf0, 0x00, 0x00, 0x00, 0x8f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x07, 0xef, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x21, 0xcf, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x08, 0x8f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x01, 0xff, 0x86, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x1f, 0xfc, 0x03, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0xff, 0xe0, 0x01, 0x8b, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x07, 0xff, 0xa0, 0x10, 0xc5, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x3f, 0xf8, 0x10, 0x08, 0x62, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x01, 0xff, 0xe4, 0x08, 0x04, 0x31, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x0f, 0xff, 0x00, 0x04, 0x02, 0x08, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0xff, 0xfc, 0x00, 0x06, 0x00, 0x04, 0x67, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x87, 0xff, 0xd2, 0x00, 0x03, 0x00, 0x02, 0x33, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xbf, 0xf8, 0xfc, 0x00, 0x01, 0x80, 0x21, 0x19, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xff, 0x81, 0x20, 0x00, 0x00, 0x80, 0x10, 0x84, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xfc, 0x00, 0x00, 0x08, 0x00, 0x40, 0x08, 0x46, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xe0, 0x00, 0x00, 0x02, 0x00, 0x20, 0x04, 0x30, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0xc0, 0x04, 0x00, 0x10, 0x02, 0x08, 0xc7, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x84, 0x43, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x02, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x42, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x03, 0x80, 0x0e, 0x00, 0x06, 0x00, 0x21, 0x80, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x04, 0x84, 0x0e, 0x00, 0x03, 0x00, 0x10, 0xc6, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x0c, 0x00, 0x00, 0x00, 0x07, 0x80, 0x08, 0x62, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x1c, 0x20, 0x00, 0x00, 0x00, 0x80, 0x02, 0x10, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x1e, 0x30, 0x60, 0x10, 0x00, 0x40, 0x01, 0x0f, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x1f, 0x00, 0x00, 0x1c, 0x80, 0x20, 0x00, 0x8f, 0x09, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x17, 0x16, 0x00, 0x18, 0x81, 0x30, 0x00, 0xff, 0xe0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x1f, 0xdc, 0x7c, 0x41, 0xc1, 0x08, 0x03, 0xff, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x1f, 0xf8, 0xfc, 0x5c, 0x80, 0x0c, 0x0f, 0xf8, 0xc4, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xc0, 0x1f, 0x7f, 0xbf, 0x00, 0x00, 0x42, 0x7f, 0xc4, 0x60, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xc0, 0xff, 0xfb, 0xf0, 0x00, 0x40, 0x03, 0xfe, 0x02, 0x30, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xe3, 0xdf, 0xff, 0xfb, 0xff, 0xfb, 0x3f, 0xf8, 0x01, 0x18, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xfe, 0x17, 0xff, 0xff, 0xff, 0xfa, 0xff, 0xc0, 0x00, 0x8c, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xb8, 0x0f, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xc0, 0x00, 0x46, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xb0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x40, 0x00, 0x23, 0x30, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x90, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x11, 0xf8, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x98, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xef, 0x30, 0x00, 0x00, 0xd1, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x98, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xbe, 0x30, 0x00, 0x00, 0x64, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x88, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xf8, 0x00, 0x01, 0x38, 0x87, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x8c, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xfc, 0x00, 0x00, 0x98, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x84, 0x0f, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xfc, 0x00, 0x00, 0x4e, 0x99, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x84, 0x07, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xfe, 0x00, 0x00, 0x27, 0x88, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x86, 0x07, 0xff, 0xff, 0xfb, 0xff, 0xfc, 0xfe, 0x00, 0x00, 0x13, 0x94, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x82, 0x07, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0d, 0xc0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x83, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x1f, 0x80, 0x00, 0x02, 0xe8, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x83, 0x27, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x80, 0x00, 0x01, 0x7e, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x81, 0x27, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xe3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x81, 0xaf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0xf1, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x38, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x08, 0x0c, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x04, 0x02, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x73, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x02, 0x01, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x73, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x04, 0x30, 0x01, 0x00, 0xdf, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x31, 0xff, 0xff, 0xff, 0xf7, 0xf9, 0xff, 0xfc, 0x00, 0xc0, 0x00, 0x80, 0x2f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x31, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xfe, 0x03, 0x00, 0x00, 0x40, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x39, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x7e, 0xff, 0x0c, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x19, 0xff, 0xff, 0xff, 0xff, 0x38, 0x3f, 0xfc, 0x10, 0x00, 0x00, 0x20, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x19, 0xff, 0xff, 0xf7, 0xfa, 0x39, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x10, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x09, 0xff, 0xff, 0xdf, 0xe3, 0x18, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x08, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x08, 0xff, 0xff, 0xff, 0x83, 0x8c, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x0c, 0xff, 0xff, 0xff, 0x93, 0xcc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x0c, 0xff, 0xff, 0xff, 0xf0, 0xc7, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x06, 0xff, 0xff, 0xe3, 0xf4, 0x67, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x06, 0xff, 0xff, 0x87, 0xbe, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x03, 0xff, 0xff, 0x86, 0x30, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x3c, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x03, 0xff, 0xf8, 0xe6, 0x70, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x03, 0xff, 0xf0, 0xf3, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x01, 0xff, 0xe7, 0xf3, 0xff, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x01, 0xdc, 0x30, 0x79, 0xfc, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0xf8, 0x70, 0x38, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x0b, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0xf9, 0xff, 0x3f, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x05, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0xf8, 0x3f, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf2, 0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x7c, 0x38, 0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc1, 0x00, 0x01, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x7c, 0xfc, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x3e, 0x47, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x80, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x3e, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x40, 0x00, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x3f, 0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x20, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x10, 0x00, 0x0f, 0xb4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x08, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x04, 0x00, 0x03, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x57, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x6f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0xdf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x8f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x03, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x10, 0x06, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x18, 0x18, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x0e, 0x3c, 0x00, 0x00, 0x08, 0x30, 0x37, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x20, 0xe0, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x0f, 0x0c, 0x00, 0x00, 0xc5, 0xe1, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x33, 0xe0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x01, 0x81, 0xc7, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x0f, 0x1f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x0c, 0x08, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x18, 0x1c, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc0, 0x70, 0x3f, 0xff, 0xf8, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x40, 0x7f, 0xfe, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x04, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x81, 0x80, 0xf1, 0xf0, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x06, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf5, 0x83, 0x01, 0xe0, 0x10, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x02, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xef, 0x0c, 0x03, 0xd0, 0x08, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x03, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x88, 0x0f, 0x80, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x03, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3f, 0xf0, 0x0f, 0x86, 0x04, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x01, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x60, 0x00, 0x86, 0x02, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x01, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x01, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x83, 0xf0, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x08, 0x3c, 0x00, 0x80, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0xcf, 0xc0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x0e, 0xcf, 0xc8, 0x3c, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x03, 0x6c, 0x00, 0x10, 0x7f, 0xff, 0xe8, 0x3c, 0x00, 0x40, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x02, 0x00, 0x03, 0xe0, 0x00, 0x03, 0xf8, 0xff, 0xff, 0xb8, 0x00, 0x20, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x78, 0x00, 0x02, 0x00, 0x1a, 0xc0, 0x00, 0x0f, 0xaf, 0xff, 0xff, 0xb0, 0x00, 0x10, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x30, 0x00, 0x01, 0x00, 0x4e, 0x00, 0x00, 0xfc, 0x37, 0xff, 0xff, 0x80, 0x00, 0x08, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x01, 0x94, 0x00, 0x01, 0xf0, 0x7f, 0xf7, 0x98, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x81, 0xd0, 0x00, 0x01, 0x47, 0xdf, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x01, 0x20, 0x00, 0x01, 0x1f, 0x7f, 0xe6, 0x00, 0x00, 0x00, 0x02, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x41, 0x80, 0x00, 0x00, 0x3f, 0xff, 0xf0, 0x00, 0x00, 0x03, 0x81, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x20, 0x00, 0x00, 0x01, 0x7d, 0xff, 0xfe, 0x00, 0x00, 0x06, 0x40, 0x81, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x20, 0x00, 0x00, 0x01, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x19, 0xc0, 0x43, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xf8, 0x00, 0x00, 0x73, 0xe0, 0x27, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x08, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x00, 0x00, 0x7c, 0xe0, 0x27, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x7f, 0xff, 0xff, 0x00, 0x03, 0x31, 0x90, 0x1f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x04, 0x00, 0x00, 0x3e, 0x7f, 0xff, 0xfe, 0x00, 0x0f, 0xa6, 0x20, 0x0f, 0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x02, 0x00, 0x00, 0x7e, 0x7f, 0xff, 0xfc, 0x00, 0x3b, 0x98, 0x80, 0x1f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x01, 0x00, 0x00, 0xfe, 0x1f, 0xf8, 0x78, 0x00, 0x61, 0xc6, 0x00, 0x7f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x01, 0xdc, 0x00, 0x00, 0x80, 0x03, 0xff, 0x9f, 0xff, 0xe0, 0x00, 0xe1, 0xd8, 0x01, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x40, 0x07, 0xee, 0x07, 0xff, 0xf8, 0x06, 0x73, 0x10, 0x07, 0xf3, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x20, 0x1f, 0xdc, 0x0f, 0xdf, 0xb0, 0x3f, 0x7e, 0x40, 0x0f, 0xfd, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x10, 0x7e, 0xf0, 0x0f, 0xfe, 0x41, 0xff, 0x38, 0x00, 0x3f, 0x8f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x09, 0xf9, 0xe0, 0x07, 0xeb, 0x87, 0xfe, 0x04, 0x00, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x03, 0xe3, 0x82, 0x06, 0x8e, 0x1f, 0xec, 0x10, 0x03, 0xfe, 0xbd, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x0f, 0xc7, 0x00, 0x01, 0x00, 0xff, 0xee, 0x00, 0x07, 0xf9, 0x98, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x3f, 0x8c, 0x0c, 0x00, 0x07, 0xff, 0xfe, 0x00, 0x1f, 0xf8, 0xfd, 0xbf, 0xff, 0xff, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x7c, 0x38, 0x0e, 0x07, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0x87, 0x9f, 0xff, 0xff, 0x80, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x01, 0x70, 0x60, 0x04, 0x07, 0xff, 0xff, 0xff, 0x00, 0xff, 0x1f, 0xec, 0x2f, 0xff, 0xff, 0xc0, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x17, 0x80, 0x03, 0xe1, 0xd8, 0x00, 0x37, 0xff, 0xff, 0xff, 0x83, 0xfd, 0xf9, 0x20, 0x2f, 0xff, 0xff, 0xc0, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x4f, 0xc3, 0x84, 0x01, 0x05, 0xff, 0xff, 0xff, 0xc7, 0xf0, 0x0c, 0x00, 0x07, 0xff, 0xff, 0xe0, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0xc1, 0x3b, 0xce, 0x03, 0x0c, 0x01, 0xff, 0xff, 0xff, 0xf7, 0xff, 0x80, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x3f, 0xac, 0x00, 0xc0, 0x40, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x7f, 0xf0, 0x7f, 0xff, 0xf0, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xff, 0xb0, 0x00, 0x30, 0x00, 0xfe, 0x7f, 0xff, 0xfe, 0x00, 0x0f, 0xff, 0xdc, 0x3f, 0xff, 0xf8, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x80, 0x00, 0x0c, 0x00, 0xff, 0x7f, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x3b, 0xff, 0xfc, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x01, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xf7, 0xef, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x20, 0x00, 0x00, 0x30, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xfc, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x03, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xee, 0xff, 0xff, 0xff, 0xfd, 0xdf, 0xfe, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf7, 0x1f, 0xff, 0xff, 0x80, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2f, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x75, 0x5e, 0x76, 0xff, 0xdf, 0xff, 0x80, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xfe, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xfb, 0xff, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0xff, 0xdf, 0x7f, 0xf8, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x03, 0xfa, 0x2f, 0xff, 0x80, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x03, 0x80, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0xf0, 0xff, 0xbc, 0x00, 0x1f, 0xff, 0xff, 0xe0, 0x00, 0x07, 0xfe, 0x07, 0xff, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe1, 0x9f, 0xbc, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x8d, 0xdf, 0xbf, 0x00, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x26, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x9f, 0xff, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x3f, 0x00, 0x00, 0x00, 0x1c, 0x20, 0x00, 0x78, 0x00, 0x1c, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0xff, 0x01, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0x00, 0x00, 0x17, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x1b, 0x3f, 0xff, 0xf1, 0xdf, 0xff, 0xff, 0xfe, 0x10, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x02, 0x12, 0xff, 0xff, 0xc7, 0x0f, 0xff, 0xff, 0xef, 0xfa, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x0f, 0x04, 0x03, 0xff, 0xfa, 0x13, 0x80, 0x40, 0x07, 0xf8, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x0f, 0xff, 0xe1, 0x80, 0x81, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xe7, 0xff, 0xe3, 0x80, 0x00, 0x04, 0x07, 0x80, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3f, 0xfd, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x1f, 0xff, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0xff, 0x9f, 0x07, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xdf, 0x00, 0x0c, 0x00, 0x00, 0x0e, 0x80, 0x00, 0x20, 0x7f, 0xff, 0xf0, 0x1f, 0xb0, 0x81, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x0b, 0x60, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xe0, 0x00, 0xc1, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x0e, 0xf8, 0xc0, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x10, 0x03, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x9e, 0xf9, 0x00, 0x00, 0x03, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xe0, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
};

const lv_img_dsc_t speed_raw_200x200 = {
  #if LVGL_VERSION_MAJOR <= 8
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
#else
  .header.cf = LV_COLOR_FORMAT_I1,
#endif
  .header.w = 200,
  .header.h = 200,
  .data_size = 5008,
  .data = speed_raw_200x200_map,
};
