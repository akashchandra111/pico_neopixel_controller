#include <stdbool.h>
#include <stdint.h>

#include "ws2812b.pio.h"

#include "../include/neopixel.h"
#include "../include/default_params.h"

static PIO current_pio;
static uint8_t current_pin;
static uint8_t current_sm;
static bool rgbw;
static float freq;

void neopixel_init(PIO pio, uint8_t sm, uint8_t pin)	{
	uint offset = pio_add_program(pio, &ws2812_program);
	rgbw = false;
	freq = 800000;
	current_pio = pio;
	current_pin = pin;
	current_sm = sm;
	ws2812_program_init(current_pio, current_sm, offset, current_pin, freq, rgbw);
}

void neopixel_send(RGB_t rgb[], uint8_t total_leds)	{
	const int min_iter = (total_leds < TOTAL_LEDS)? total_leds : TOTAL_LEDS;

	for (int i=0; i<min_iter; ++i)	{
		uint32_t val = 0;
		val = (((uint8_t) (rgb[i].g * DEF_INTENSITY_FACTOR)) << 24u) | 
				(((uint8_t) (rgb[i].r * DEF_INTENSITY_FACTOR)) << 16u) | 
				(((uint8_t) (rgb[i].b * DEF_INTENSITY_FACTOR)) << 8u) | 
				0x00;
		pio_sm_put_blocking(current_pio, current_sm, val);
	}
}

RGB_t get_rgb(uint8_t r, uint8_t g,  uint8_t b)	{
	return (RGB_t) {
		.r = r,
		.g = g,
		.b = b
	};
}

/*
 *	Function assumes last 8 LSB is of no use
 */
RGB_t get_rgb_from_u32(uint32_t val)	{
	return  (RGB_t)	{
		.r = (val >> 16u) & 0xFF,
		.g = (val >> 8u) & 0xFF,
		.b = (val) & 0xFF,
	};
}

// Little endian
inline void set_rgb_from_u32(RGB_t *rgb, uint32_t val)	{
	rgb->r = (val >> 16u) & 0xFF;
	rgb->g = (val >> 8u) & 0xFF;
	rgb->b = (val) & 0xFF;
}

inline void set_rgb_from_rgb(RGB_t *rgb, uint8_t r, uint8_t g,  uint8_t b)	{
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
}
