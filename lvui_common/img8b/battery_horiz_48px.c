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

#ifndef LV_ATTRIBUTE_IMG_BATTERY_HORIZ_48PX
#define LV_ATTRIBUTE_IMG_BATTERY_HORIZ_48PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BATTERY_HORIZ_48PX uint8_t battery_horiz_48px_map[] = {
  0x09, 0x09, 0x09, 0x00, 	/*Color of index 0*/
  0x68, 0x62, 0x5e, 0xf9, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x01, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x01, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x01, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x0f, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x0f, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x0f, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x0f, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x0f, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x0f, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x0f, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x0f, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x01, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x01, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x01, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t battery_horiz_48px = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 296,
  .data = battery_horiz_48px_map,
};