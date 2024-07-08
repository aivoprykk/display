#ifndef C1BEE8A4_839A_4BFD_B010_B2F998E485F8
#define C1BEE8A4_839A_4BFD_B010_B2F998E485F8

#ifdef __cplusplus
extern "C" {
#endif

// Your code here
#if (CONFIG_DISPLAY_LOG_LEVEL<=CONFIG_DISPLAY_LOG_LEVEL_INFO)
#include "esp_timer.h"
#include "esp_log.h"
#define DEBUG_LOG(a, b, ...) ESP_LOGI(a, b, __VA_ARGS__)
#define DEBUG_MEAS_START() uint64_t _start = (esp_timer_get_time()), _end = 0
#define DEBUG_MEAS_END(a, b, ...) \
    _end = (esp_timer_get_time());  \
    ESP_LOGI(a, b, __VA_ARGS__, _end - _start)
#else
#define DEBUG_LOG(a, b, ...) ((void)0)
#define DEBUG_MEAS_START() ((void)0)
#define DEBUG_MEAS_END(a, b, ...) ((void)0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* C1BEE8A4_839A_4BFD_B010_B2F998E485F8 */
