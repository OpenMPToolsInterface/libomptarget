#ifndef _OMPT_TARGET_H_
#define _OMPT_TARGET_H_

#include <ompt.h>

#include "omptarget.h"

// keep in sync with ompt-general.c
typedef ompt_callback_t (*ompt_get_target_callback_t)(ompt_event_t);
typedef void (*ompt_target_task_fn_t)(void);

typedef struct ompt_target_lib_info_s {
    int                        *enabled;
    ompt_get_target_callback_t  get_target_callback;
    ompt_get_task_id_t          get_task_id;
    ompt_get_task_frame_t       get_task_frame;
    ompt_target_task_fn_t       target_task_begin;
    ompt_target_task_fn_t       target_task_end;
} ompt_target_lib_info_t;

extern const ompt_target_lib_info_t *ompt_info;

void __ompt_target_initialize();

// defined in runtime which has C interface
#ifdef __cplusplus
extern "C" {
#endif
extern const ompt_target_lib_info_t *ompt_target_initialize();
#ifdef __cplusplus
};
#endif

// helper functions
static inline int ompt_enabled()
{
    return *(ompt_info->enabled);
}


// callback helpers
static inline ompt_new_target_task_callback_t
ompt_get_new_target_task_callback(ompt_event_t evid)
{
    return (ompt_new_target_task_callback_t) ompt_info->get_target_callback(evid);
}

static inline ompt_new_target_data_callback_t
ompt_get_new_target_data_callback(ompt_event_t evid)
{
    return (ompt_new_target_data_callback_t) ompt_info->get_target_callback(evid);
}

static inline ompt_new_data_map_callback_t
ompt_get_new_data_map_callback(ompt_event_t evid)
{
    return (ompt_new_data_map_callback_t) ompt_info->get_target_callback(evid);
}

static inline ompt_data_map_done_callback_t
ompt_get_target_data_map_done_callback(ompt_event_t evid)
{
    return (ompt_data_map_done_callback_t) ompt_info->get_target_callback(evid);
}

static inline ompt_task_callback_t
ompt_get_task_callback(ompt_event_t evid)
{
    return (ompt_task_callback_t) ompt_info->get_target_callback(evid);
}


// task information
static inline ompt_task_id_t ompt_get_task_id(int depth)
{
    return ompt_info->get_task_id(depth);
}

static inline ompt_frame_t *ompt_get_task_frame(int depth)
{
    return ompt_info->get_task_frame(depth);
}


// target tasks
static inline void ompt_target_task_begin()
{
    ompt_info->target_task_begin();
}

static inline void ompt_target_task_end()
{
    ompt_info->target_task_end();
}


uint32_t ompt_get_mapping_flags(int32_t arg_type);

#endif