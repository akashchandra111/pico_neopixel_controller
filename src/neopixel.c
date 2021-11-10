#include <stdbool.h>
#include <stdint.h>

#include "ws2812b.pio.h"

#include "../include/neopixel.h"
#include "../include/default_params.h"

static PIO current_pio;
static u8 current_pin;
static u8 current_sm;
static bool rgbw;
static float freq;

void neopixel_init(PIO pio, u8 sm, u8 pin)	{
	u32 offset = pio_add_program(pio, &ws2812_program);
	rgbw = false;
	freq = 800000;
	current_pio = pio;
	current_pin = pin;
	current_sm = sm;
	ws2812_program_init(current_pio, current_sm, offset, current_pin, freq, rgbw);
}

void neopixel_send(RGB_t rgb[], const u32 total_leds, const f32 intensity)	{
	const u32 min_iter = (total_leds < TOTAL_LEDS)? total_leds : TOTAL_LEDS;

	for (u32 i=0; i<min_iter; ++i)	{
		u32 val = 0;
		val = (((u8) (rgb[i].g * intensity)) << 24u) | (((u8) (rgb[i].r * intensity)) << 16u) | 
				(((u8) (rgb[i].b * intensity)) << 8u) | 0x00;
		pio_sm_put_blocking(current_pio, current_sm, val);
	}
}

RGB_t get_rgb(u8 r, u8 g, u8 b)	{
	return (RGB_t) {
		.r = r,
		.g = g,
		.b = b
	};
}

/*
 *	Function assumes last 8 LSB is of no use
 */
RGB_t get_rgb_from_u32(u32 val)	{
	return  (RGB_t)	{
		.r = (val >> 16u) & 0xFF,
		.g = (val >> 8u) & 0xFF,
		.b = (val) & 0xFF,
	};
}

// Little endian
inline void set_rgb_from_u32(RGB_t *rgb, u32 val)	{
	rgb->r = (val >> 16u) & 0xFF;
	rgb->g = (val >> 8u) & 0xFF;
	rgb->b = (val) & 0xFF;
}

inline void set_rgb_from_rgb(RGB_t *rgb, u8 r, u8 g, u8 b)	{
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
}
