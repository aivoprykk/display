
#ifndef EC03C801_3582_4354_8FBE_98C773E9C9FF
#define EC03C801_3582_4354_8FBE_98C773E9C9FF

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_event.h"
#include "logger_common.h"

#define UI_EVENT_BASE 0x30  // Component ID 3

// Declare an event base
ESP_EVENT_DECLARE_BASE(UI_EVENT);        // declaration of the ADC_EVENT family

// declaration of the specific events under the ADC_EVENT family
#define UI_EVENT_LIST(l) \
    l(FLUSH_START) \
    l(FLUSH_DONE)

#define UI_EVENT_ENUM(l) UI_EVENT_##l,
enum {                                       
    UI_EVENT_LIST(UI_EVENT_ENUM)
};

const char * ui_event_strings(int id);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* EC03C801_3582_4354_8FBE_98C773E9C9FF */
