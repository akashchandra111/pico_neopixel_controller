#pragma once

#include <stdint.h>

#include "hardware/pio.h"

#include "default_params.h"
#include "datatypes.h"
/*
 * size:		 8 8 8 8 (word size)
 *				|0|b|g|r|
 *
 */
typedef struct RGB	{
	union	{
		u32 rgb;	// 32-bit word
		u32 rgbf;	// 32-bit word (f is 8-bit flags, if you want to use it)
		struct	{
			u8 f;	// Flag value
			u8 b;	// Blue value
			u8 g;	// Green value
			u8 r;	// Red value
		};
	};
} RGB_t;

void neopixel_init(PIO pio, u8 sm, u8 pin);
void neopixel_send(RGB_t rgb[], const u32 total_leds, const f32 intensity);
RGB_t get_rgb(u8 r, u8 g, u8 b);
RGB_t get_rgb_from_u32(u32 val);
void set_rgb_from_u32(RGB_t *rgb, u32 val);
void set_rgb_from_rgb(RGB_t *rgb, u8 r, u8 g, u8 b);
