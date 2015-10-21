#include <mutex>

#include "ompt_target.h"

const ompt_target_lib_info_t *ompt_info;

void __ompt_target_initialize()
{
  static int ompt_target_initialized = 0;
  static std::mutex lock;

  std::lock_guard<std::mutex> locker(lock);
  if (ompt_target_initialized == 0) {
    ompt_target_initialized = 1;

    ompt_info = ompt_target_initialize();
  }
}

uint32_t ompt_get_mapping_flags(int32_t arg_type)
{
  uint32_t mapping_flags = 0;

  if (arg_type & tgt_map_to) {
    mapping_flags |= ompt_target_map_flag_to;
  }
  if (arg_type & tgt_map_from) {
    mapping_flags |= ompt_target_map_flag_from;
  }

  if (mapping_flags == 0) {
    if (arg_type == tgt_map_alloc) {
      mapping_flags = ompt_target_map_flag_alloc;
    } else if (arg_type == tgt_map_release) {
      mapping_flags = ompt_target_map_flag_release;
    } else if (arg_type == tgt_map_delete) {
      mapping_flags = ompt_target_map_flag_delete;
    }
  }

  // currently all operations are synchronous
  mapping_flags |= ompt_target_map_flag_sync;

  return mapping_flags;
}
