#pragma once

#include <stdbool.h>
#include "pico/util/datetime.h"

#include "datatypes.h"
#include "led_array.h"
#include "neopixel.h"
#include "pattern.h"

typedef struct led_opts_t {
	u8 fps;
	f32 intensity;
	led_array_t leds_buffer;
} led_opts_t;

typedef struct extra_opts_t	{
	datetime_t* date_time;
	RGB_t temp_color;
} extra_opts_t;

static pattern_enum current_pattern;

// This variable comes from pattern.c
// extern int is_pat_set;

void led_options_init(led_opts_t *led_options, const u8 fps, const f32 intensity, const u16 led_buffer_len, const u8 pin);
void led_options_set_fps(const u8 fps);
void led_send_pixels(led_opts_t* led_options);
void led_set_pixel_intensity(led_opts_t* led_options, const f32 intensity);
void led_display(led_opts_t* led_options);	// Sets important options and should be present at the end of the loop
void led_buffer_shl(led_opts_t* led_options, const bool is_cyclic);
void led_buffer_shr(led_opts_t* led_options, const bool is_cyclic);
void led_set_to_rgb_color(led_opts_t* led_options, const RGB_t color_pattern, const u32 start, const u32 end);
void led_pattern_switch(const pattern_enum pattern_type);
void led_run_current_pattern(led_opts_t* led_options, extra_opts_t *extra_options);
