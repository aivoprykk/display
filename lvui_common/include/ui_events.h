
#ifndef EC03C801_3582_4354_8FBE_98C773E9C9FF
#define EC03C801_3582_4354_8FBE_98C773E9C9FF

#include "esp_event.h"

#ifdef __cplusplus
extern "C" {
#endif

// Declare an event base
ESP_EVENT_DECLARE_BASE(UI_EVENT);        // declaration of the ADC_EVENT family

// declaration of the specific events under the ADC_EVENT family
enum {                                       
    UI_EVENT_FLUSH_START,                  // battery level is low
    UI_EVENT_FLUSH_DONE,             // battery level is critical
};

extern const char * ui_event_strings[];

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* EC03C801_3582_4354_8FBE_98C773E9C9FF */
