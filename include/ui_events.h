
#ifndef EC03C801_3582_4354_8FBE_98C773E9C9FF
#define EC03C801_3582_4354_8FBE_98C773E9C9FF

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_event.h"
#include "logger_common.h"

// Declare an event base
ESP_EVENT_DECLARE_BASE(UI_EVENT);        // declaration of the ADC_EVENT family

// declaration of the specific events under the ADC_EVENT family
#define UI_EVENT_LIST(l) \
    l(UI_EVENT_FLUSH_START) \
    l(UI_EVENT_FLUSH_DONE)

enum {                                       
    UI_EVENT_LIST(ENUM)
};

const char * ui_event_strings(int id);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* EC03C801_3582_4354_8FBE_98C773E9C9FF */
