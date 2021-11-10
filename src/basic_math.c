#include "../include/basic_math.h"

f32 map(const f32 from_val, const f32 to_val, const f32 mapped_start_val, const f32 mapped_end_val, const f32 value)	{
	if (value > to_val)	return 0;
	return (f32) ((value + from_val)/(f32) (to_val - from_val)) * (mapped_end_val - mapped_start_val);
}

i32 step_interval(const i32 step_from, const i32 step_to, const i32 from, const i32 to, const i32 step_cur_interval)	{
	return from + (i32)((to - from)/(f32)(step_to - step_to))*step_cur_interval;
}
