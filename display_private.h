#ifndef C1BEE8A4_839A_4BFD_B010_B2F998E485F8
#define C1BEE8A4_839A_4BFD_B010_B2F998E485F8

#ifdef __cplusplus
extern "C" {
#endif

// Your code here
#if (CONFIG_DISPLAY_LOG_LEVEL <= 2)

#include "esp_timer.h"
#include "esp_log.h"

#endif

#if (CONFIG_DISPLAY_LOG_LEVEL == CONFIG_DISPLAY_LOG_LEVEL_TRACE) // "A lot of logs to give detailed information"

#define DLOG(a, b, ...) ESP_LOGI(a, b, __VA_ARGS__)
#define DMEAS_START() uint64_t _start = (esp_timer_get_time()), _end = 0
#define DMEAS_END(a, b, ...) \
    _end = (esp_timer_get_time());  \
    ESP_LOGI(a, b, __VA_ARGS__, _end - _start)
#define ILOG DLOG
#define IMEAS_START DMEAS_START
#define IMEAS_END DMEAS_END
#define WLOG DLOG
#define WMEAS_START DMEAS_START
#define WMEAS_END DMEAS_END

#elif (CONFIG_DISPLAY_LOG_LEVEL == CONFIG_DISPLAY_LOG_LEVEL_INFO) // "Log important events"

#define DLOG(a, b, ...) ((void)0)
#define DMEAS_START() ((void)0)
#define DMEAS_END(a, b, ...) ((void)0)
#define ILOG(a, b, ...) ESP_LOGI(a, b, __VA_ARGS__)
#define IMEAS_START() uint64_t _start = (esp_timer_get_time()), _end = 0
#define IMEAS_END(a, b, ...) \
    _end = (esp_timer_get_time());  \
    ESP_LOGI(a, b, __VA_ARGS__, _end - _start)
#define WLOG ILOG
#define WMEAS_START IMEAS_START
#define WMEAS_END IMEAS_END

#elif (CONFIG_DISPLAY_LOG_LEVEL == CONFIG_DISPLAY_LOG_LEVEL_WARN) // "Log if something unwanted happened but didn't cause a problem"

#define DLOG(a, b, ...) ((void)0)
#define DMEAS_START() ((void)0)
#define DMEAS_END(a, b, ...) ((void)0)
#define ILOG(a, b, ...) ((void)0)
#define IMEAS_START() ((void)0)
#define IMEAS_END(a, b, ...) ((void)0)
#define WLOG(a, b, ...) ESP_LOGI(a, b, __VA_ARGS__)
#define WMEAS_START() uint64_t _start = (esp_timer_get_time()), _end = 0
#define WMEAS_END(a, b, ...) \
    _end = (esp_timer_get_time());  \
    ESP_LOGI(a, b, __VA_ARGS__, _end - _start)

#else // "Do not log anything"

#define DLOG(a, b, ...) ((void)0)
#define DMEAS_START() ((void)0)
#define DMEAS_END(a, b, ...) ((void)0)
#define ILOG(a, b, ...) ((void)0)
#define IMEAS_START() ((void)0)
#define IMEAS_END(a, b, ...) ((void)0)
#define WLOG(a, b, ...) ((void)0)
#define WMEAS_START() ((void)0)
#define WMEAS_END(a, b, ...) ((void)0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* C1BEE8A4_839A_4BFD_B010_B2F998E485F8 */
