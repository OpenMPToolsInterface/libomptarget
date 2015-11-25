#include <atomic>
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

ompt_target_activity_id_t ompt_target_activity_id_new()
{
  static std::atomic<ompt_target_activity_id_t> map_id { 1 };
  return map_id++;
}
