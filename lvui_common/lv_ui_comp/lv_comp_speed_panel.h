#ifndef FD03E2AD_E440_462C_A0B2_9CFFF4D910EE
#define FD03E2AD_E440_462C_A0B2_9CFFF4D910EE

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>
#include <stdint.h>

typedef void (*lv_speed_panel_cb_t)(int32_t);

typedef struct {
    lv_obj_t obj;

    lv_obj_t *main_panel;
    lv_obj_t *secondary_panel;
    lv_obj_t *speed_bar;
} lv_speed_panel_t;

lv_obj_t *lv_speed_panel_create(lv_obj_t *parent);

#ifdef __cplusplus
} /*extern "C"*/
#endif


#endif /* FD03E2AD_E440_462C_A0B2_9CFFF4D910EE */
