#ifndef _OMPT_TARGET_H_
#define _OMPT_TARGET_H_

#include <ompt.h>

#include "omptarget.h"

// filled in __ompt_target_initialize
typedef int (*ompt_enabled_t)();
extern ompt_enabled_t ompt_enabled;

typedef ompt_callback_t (*ompt_get_target_callback_t)(ompt_event_t);
extern ompt_get_target_callback_t __ompt_get_target_callback;

extern ompt_get_task_id_t ompt_get_task_id;
extern ompt_get_task_frame_t ompt_get_task_frame;

void __ompt_target_initialize();

// defined in runtime which has C interface
#ifdef __cplusplus
extern "C" {
#endif
extern void ompt_target_initialize(ompt_enabled_t *,
                                   ompt_get_target_callback_t *,
                                   ompt_get_task_id_t *,
                                   ompt_get_task_frame_t *);
#ifdef __cplusplus
};
#endif

// helper functions for callbacks
static inline ompt_new_target_task_callback_t
ompt_get_new_target_task_callback(ompt_event_t evid)
{
    return (ompt_new_target_task_callback_t) __ompt_get_target_callback(evid);
}

static inline ompt_new_target_data_callback_t
ompt_get_new_target_data_callback(ompt_event_t evid)
{
    return (ompt_new_target_data_callback_t) __ompt_get_target_callback(evid);
}

static inline ompt_new_data_map_callback_t
ompt_get_new_data_map_callback(ompt_event_t evid)
{
    return (ompt_new_data_map_callback_t) __ompt_get_target_callback(evid);
}

static inline ompt_data_map_done_callback_t
ompt_get_target_data_map_done_callback(ompt_event_t evid)
{
    return (ompt_data_map_done_callback_t) __ompt_get_target_callback(evid);
}

static inline ompt_task_callback_t
ompt_get_task_callback(ompt_event_t evid)
{
    return (ompt_task_callback_t) __ompt_get_target_callback(evid);
}


uint32_t ompt_get_mapping_flags(int32_t arg_type);

#endif
