#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/pattern.h"
#include "../include/default_params.h"

#define DEBUG 0
#define COLOR_RANGE (255*3)

static RGB_t colors[COLOR_RANGE];	// Global color indexing memory

// Blinks the LED at the current position
void pat_time(datetime_t *dt, int temperature, RGB_t lights[TOTAL_LEDS], int length)	{
	rtc_get_datetime(dt);
	for (int i=0; i<length; ++i)	{
		bool is_set = false;
		if (dt->sec == i && (is_set=true))	set_rgb_from_rgb(&lights[i], 255, 0, 0);
		if (dt->min == i && (is_set=true))	set_rgb_from_rgb(&lights[i], 0, 255, 0);
		if (dt->hour == i && (is_set=true))	set_rgb_from_rgb(&lights[i], 0, 0, 255);
		if (dt->dotw == i && (is_set=true))	set_rgb_from_rgb(&lights[i], 128, 128, 0);
		if (dt->day-1 == i && (is_set=true))	set_rgb_from_rgb(&lights[i], 0, 128, 128);
		if (dt->month-1 == i && (is_set=true))	set_rgb_from_rgb(&lights[i], 128, 0, 128);
		if (temperature == i && (is_set=true))	set_rgb_from_rgb(&lights[i], 128, 128, 128);

		if (!is_set)	set_rgb_from_rgb(&lights[i], 0, 0, 0);
	}
}

// Blinks the LEDs till the current position
void pat_time_1(datetime_t *dt, int temperature, RGB_t lights[TOTAL_LEDS], int length)	{
	static uint8_t vals[NPIN_TOTAL] = { 0 };
	for (int i=0; i < NPIN_TOTAL; ++i)	vals[i] = 0;
	vals[dt->sec] = 1;
	vals[dt->min] = 2;
	vals[dt->hour] = 3;

	uint8_t current_val = 0;
	for (int i=NPIN_TOTAL-1; i >= 0; --i)	{
		if (vals[i] != 0)	current_val = vals[i];
		if (vals[i] == current_val || (vals[i] == 0 && current_val != 0))	{
			if (current_val == 0)	set_rgb_from_rgb(&lights[i], 0, 0, 0);
			else if (current_val == 1)	set_rgb_from_rgb(&lights[i], 255, 0, 0);
			else if (current_val == 2)	set_rgb_from_rgb(&lights[i], 0, 255, 0);
			else	set_rgb_from_rgb(&lights[i], 0, 0, 255);
		}
	}
}

// Blinks the LEDs till the current position but in different color
void pat_time_2(datetime_t *dt, int temperature, RGB_t lights[TOTAL_LEDS], int length)	{
	static uint8_t vals[NPIN_TOTAL] = { 0 };
	for (int i=0; i < NPIN_TOTAL; ++i)	vals[i] = 0;
	vals[dt->sec] = 1;
	vals[dt->min] = 2;
	vals[dt->hour] = 3;

	uint8_t current_val = 0;
	for (int i=NPIN_TOTAL-1; i >= 0; --i)	{
		if (vals[i] != 0)	current_val = vals[i];
		if (vals[i] == current_val || (vals[i] == 0 && current_val != 0))	{
			if (current_val == 0)	set_rgb_from_rgb(&lights[i], 0, 0, 0);
			else if (current_val == 1)	set_rgb_from_rgb(&lights[i], 127, 127, 0);
			else if (current_val == 2)	set_rgb_from_rgb(&lights[i], 0, 127, 127);
			else	set_rgb_from_rgb(&lights[i], 127, 0, 127);
		}
	}
}

// trail pattern
inline void set_pattern_trailing(RGB_t lights[TOTAL_LEDS], int length)	{
	for (int i=9; i>=0; --i)	{
		set_rgb_from_rgb(&lights[10-1-i], (1<<i)%255, (1<<i)%255, (1<<i)%255);
	}
	for (int i=10; i<length; ++i) set_rgb_from_rgb(&lights[i], 10, 0, 0);
}

void pat_fire(RGB_t lights[TOTAL_LEDS], int length)	{
	const uint32_t colors[4] = { 0xee6501, 0xf36805, 0xd23e02, 0xfbc92d};
	for (int i=0; i<length/4; ++i)	{
		int random_val = rand();
		lights[(4*i)+0].rgb = colors[random_val%4];
		lights[(4*i)+1].rgb = colors[(random_val+1)%4];
		lights[(4*i)+2].rgb = colors[(random_val+2)%4];
		lights[(4*i)+3].rgb = colors[(random_val+3)%4];
	}
}

void set_pat_rainbow(RGB_t lights[TOTAL_LEDS], int length)	{	// Set 60 colors
	const size_t pixel_red = (length/3)*0;
	const size_t pixel_green = (length/3)*1;
	const size_t pixel_blue = (length/3)*2;
	const size_t color_range = pixel_green - pixel_red;

	for (size_t i=pixel_red, j=0; i < pixel_green; ++i, ++j)	{
		lights[i].g = (uint8_t) ((j/(float) color_range) * 255);
		lights[i].r = (uint8_t) (((color_range - j)/(float) color_range) * 255);
		lights[i].b = 0;
	}

	for (size_t i=pixel_green, j=0; i < pixel_blue; ++i, ++j)	{
		lights[i].b = (uint8_t) ((j/(float) color_range) * 255);
		lights[i].g = (uint8_t) (((color_range - j)/(float) color_range) * 255);
		lights[i].r = 0;
	}

	for (size_t i=pixel_blue, j=0; i < length; ++i, ++j)	{
		lights[i].r = (uint8_t) ((j/(float) color_range) * 255);
		lights[i].b = (uint8_t) (((color_range - j)/(float) color_range) * 255);
		lights[i].g = 0;
	}
}

void set_pat_rainbow_efficient(RGB_t lights[TOTAL_LEDS], int length)	{
	const size_t pixel_red = (length/3)*0;
	const size_t pixel_green = (length/3)*1;
	const size_t pixel_blue = (length/3)*2;
	const size_t color_range = pixel_blue - pixel_green;

	for (size_t i=0; i<color_range; ++i)	{
		const size_t pix_red_offset = pixel_red + i;
		const size_t pix_green_offset = pixel_green + i;
		const size_t pix_blue_offset = pixel_blue + i;
		lights[pix_red_offset].g = lights[pix_green_offset].b = lights[pix_blue_offset].r = (uint8_t) ((i/(float) color_range) * 255);
		lights[pix_red_offset].r = lights[pix_green_offset].g = lights[pix_blue_offset].b = (uint8_t) (((color_range - i)/(float) color_range) * 255);
		lights[pix_red_offset].b = lights[pix_green_offset].r = lights[pix_blue_offset].g = 0;
	}
}

void pat_rainbow_cycle_all_same(RGB_t lights[TOTAL_LEDS], int length)	{
	static bool is_pat_set = false;
	static size_t i=0;

	if (!is_pat_set)	{
		set_pat_rainbow_efficient(colors, COLOR_RANGE);
		is_pat_set = true;
	}

	for (size_t j=0 ; j<length; ++j)	lights[j].rgb = colors[i].rgb;

#if DEBUG
		printf("i: %zu>0x%x \n", i, colors[i].rgb);
#endif

	++i;
	if (i == COLOR_RANGE) i=0;	
}

void pat_rainbow_cycle_color_cycle(RGB_t lights[TOTAL_LEDS], int length)	{
	static bool is_pat_set = false;
	static size_t i=0;
	static size_t start = 0, end = 0;

	if (!is_pat_set)	{
		set_pat_rainbow_efficient(colors, COLOR_RANGE);
		is_pat_set = true;
		start = 0;
		end = length - 1;
	}

	for (size_t i=0; i<length; ++i)	{
		if (start < end)	lights[i].rgb = colors[start+i].rgb;
		else	{
			const int end_offset = (COLOR_RANGE - start - 1);
			bool cond_1 = false, cond_2 = false;
			if (start+i < COLOR_RANGE)	{
				lights[i].rgb = colors[start+i].rgb;
				cond_1 = true;
			}
			if (i <= end + 1)	{
				lights[end_offset+i].rgb = colors[i].rgb;
				cond_2 = true;
			}

			if (!(cond_1 || cond_2))	break;
		}
	}

#if DEBUG
#endif

	++start;
	++end;
	if (start == COLOR_RANGE) start = 0;
	else if (end == COLOR_RANGE)	end = 0;
}
