#pragma once

#include <stdint.h>

#include "hardware/pio.h"

#include "default_params.h"
/*
 * size:		 8 8 8 8 (word size)
 *				|0|b|g|r|
 *
 */
typedef struct RGB	{
	union	{
		uint32_t rgb;	// 32-bit word
		uint32_t rgbf;	// 32-bit word (f is 8-bit flags, if you want to use it)
		struct	{
			uint8_t f;	// Flag value
			uint8_t b;	// Blue value
			uint8_t g;	// Green value
			uint8_t r;	// Red value
		};
	};
} RGB_t;

void neopixel_init(PIO pio, uint8_t sm, uint8_t pin);
void neopixel_send(RGB_t rgb[], uint8_t total_leds);
RGB_t get_rgb(uint8_t r, uint8_t g,  uint8_t b);
RGB_t get_rgb_from_u32(uint32_t val);
void set_rgb_from_u32(RGB_t *rgb, uint32_t val);
void set_rgb_from_rgb(RGB_t *rgb, uint8_t r, uint8_t g,  uint8_t b);
void set_pat_rainbow(RGB_t lights[], int length);
