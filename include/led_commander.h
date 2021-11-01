#pragma once

#include <stdbool.h>

#include "datatypes.h"
#include "led_array.h"
#include "neopixel.h"

typedef enum command	{
	COMMAND_FPS,			// Set frames
	COMMAND_INTENSITY,		// Set light intensity
	COMMAND_SHR,			// Shift colors right (cyclic)
	COMMAND_SHL,			// Shift colors left (cyclic)
	COMMAND_MODE,			// Select saved modes
	COMMAND_REPEAT_LAST,	// Repeat last command
} command_enum;

typedef struct led_opts_t {
	u8 fps;
	f32 intensity;
	led_array_t leds_buffer;
} led_opts_t;

void led_options_init(led_opts_t *led_options, u8 fps, u8 intensity, u16 led_buffer_len, u8 pin);
void led_options_set_fps(u8 fps);
void led_send_pixels(led_opts_t* led_options);
void led_set_pixel_intensity(led_opts_t* led_options, f32 intensity);
void led_display(led_opts_t* led_options);	// Sets important options and should be present at the end of the loop
void led_buffer_shl(led_opts_t* led_options, bool is_cyclic);
void led_buffer_shr(led_opts_t* led_options, bool is_cyclic);
void led_set_to_rgb_color(led_opts_t* led_options, RGB_t color_pattern);
