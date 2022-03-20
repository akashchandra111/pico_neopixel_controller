#pragma once

#include "datatypes.h"

f32 map_float(const f32 from_val, const f32 to_val, const f32 mapped_start_val, const f32 mapped_end_val, const f32 value);
i32 map_int(const i32 from_val, const i32 to_val, const i32 mapped_start_val, const i32 mapped_end_val, const i32 value);
i32 step_interval(const i32 step_from, const i32 step_to, const i32 from, const i32 to, const i32 step_cur_interval);
