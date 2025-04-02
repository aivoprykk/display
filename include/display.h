#ifndef A999696B_59F7_4B87_BBA4_0E0940D9CA18
#define A999696B_59F7_4B87_BBA4_0E0940D9CA18

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"

typedef struct display_op_s {
    uint32_t (*screen_cb)(void*);
} display_op_t;

typedef struct display_s {
    display_op_t *op;
    uint32_t buf_update_count;
    uint32_t flush_count;
    uint32_t count_last_full_refresh; 
    uint8_t task_resumed_for_times;
    int8_t task_fast_refresh_on_time;
    int8_t task_full_refresh_on_time;
    bool task_full_refresh_on_time_force;
} display_t;

struct display_s *display_init(struct display_s *me, struct display_op_s *op);
void display_uninit(struct display_s *me);
void display_task_start();
bool display_task_is_paused();
void display_task_pause();
void display_task_resume();
void display_task_resume_for_times(uint8_t times, int8_t fast_refresh_time, int8_t full_refresh_time, bool full_refresh_force);
void display_wait_for_task();
void display_cancel_delay();
bool display_refresh_lock(int timeout);
void display_refresh_unlock();
void display_request_full_refresh(bool force);
void display_request_fast_refresh();
void display_task_cancel_req_full_refresh();
void display_task_cancel_req_fast_refresh();
void display_set_rotation(uint8_t rotation);
void display_incr_flush_count();
void display_incr_buf_update_count();
uint32_t display_get_buf_update_count();
uint16_t display_get_offscreen_counter();
uint32_t display_get_flush_count();

#ifdef __cplusplus
}
#endif

#endif /* A999696B_59F7_4B87_BBA4_0E0940D9CA18 */
