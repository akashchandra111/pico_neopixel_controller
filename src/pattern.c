#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/pattern.h"
#include "../include/default_params.h"

// Blinks the LED at the current position
void pat_time(datetime_t *dt, RGB_t lights[TOTAL_LEDS], i32 length)	{
	rtc_get_datetime(dt);
	for (i32 i=0; i<length; ++i)	{
		is_pat_set = false;
		if (dt->sec == i && (is_pat_set=true))	set_rgb_from_rgb(&lights[i], 255, 0, 0);
		if (dt->min == i && (is_pat_set=true))	set_rgb_from_rgb(&lights[i], 0, 255, 0);
		if (dt->hour == i && (is_pat_set=true))	set_rgb_from_rgb(&lights[i], 0, 0, 255);
		if (dt->dotw == i && (is_pat_set=true))	set_rgb_from_rgb(&lights[i], 128, 128, 0);
		if (dt->day-1 == i && (is_pat_set=true))	set_rgb_from_rgb(&lights[i], 0, 128, 128);
		if (dt->month-1 == i && (is_pat_set=true))	set_rgb_from_rgb(&lights[i], 128, 0, 128);

		if (!is_pat_set)	set_rgb_from_rgb(&lights[i], 0, 0, 0);
	}
}

// Blinks the LEDs till the current position
void pat_time_1(datetime_t *dt, RGB_t lights[TOTAL_LEDS], i32 length)	{
	static u8 vals[NPIN_TOTAL] = { 0 };
	for (i32 i=0; i < NPIN_TOTAL; ++i)	vals[i] = 0;
	vals[dt->sec] = 1;
	vals[dt->min] = 2;
	vals[dt->hour] = 3;

	u8 current_val = 0;
	for (i32 i=NPIN_TOTAL-1; i >= 0; --i)	{
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
void pat_time_2(datetime_t *dt, RGB_t lights[TOTAL_LEDS], i32 length)	{
	static u8 vals[NPIN_TOTAL] = { 0 };
	for (i32 i=0; i < NPIN_TOTAL; ++i)	vals[i] = 0;
	vals[dt->sec] = 1;
	vals[dt->min] = 2;
	vals[dt->hour] = 3;

	u8 current_val = 0;
	for (i32 i=NPIN_TOTAL-1; i >= 0; --i)	{
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
inline void set_pattern_trailing(RGB_t lights[TOTAL_LEDS], i32 length)	{
	for (i32 i=9; i>=0; --i)	{
		set_rgb_from_rgb(&lights[10-1-i], (1<<i)%255, (1<<i)%255, (1<<i)%255);
	}
	for (i32 i=10; i<length; ++i) set_rgb_from_rgb(&lights[i], 10, 0, 0);
}

void pat_fire(RGB_t lights[TOTAL_LEDS], i32 length)	{
	const uint32_t colors[4] = { 0xee6501, 0xf36805, 0xd23e02, 0xfbc92d};
	for (i32 i=0; i<length/4; ++i)	{
		i32 random_val = rand();
		set_rgb_from_u32(&lights[(4*i)+0], colors[random_val%4]);
		set_rgb_from_u32(&lights[(4*i)+1], colors[(random_val+1)%4]);
		set_rgb_from_u32(&lights[(4*i)+2], colors[(random_val+2)%4]);
		set_rgb_from_u32(&lights[(4*i)+3], colors[(random_val+3)%4]);
	}
}

void set_pat_rainbow(RGB_t lights[TOTAL_LEDS], i32 length)	{	// Set 60 colors
	const u32 pixel_red = (length/3)*0;
	const u32 pixel_green = (length/3)*1;
	const u32 pixel_blue = (length/3)*2;
	const u32 color_range = pixel_green - pixel_red;

	for (u32 i=pixel_red, j=0; i < pixel_green; ++i, ++j)	{
		lights[i].g = (u8) ((j/(float) color_range) * 255);
		lights[i].r = (u8) (((color_range - j)/(float) color_range) * 255);
		lights[i].b = 0;
	}

	for (u32 i=pixel_green, j=0; i < pixel_blue; ++i, ++j)	{
		lights[i].b = (u8) ((j/(float) color_range) * 255);
		lights[i].g = (u8) (((color_range - j)/(float) color_range) * 255);
		lights[i].r = 0;
	}

	for (u32 i=pixel_blue, j=0; i < length; ++i, ++j)	{
		lights[i].r = (u8) ((j/(float) color_range) * 255);
		lights[i].b = (u8) (((color_range - j)/(float) color_range) * 255);
		lights[i].g = 0;
	}
}

void set_pat_rainbow_efficient(RGB_t lights[TOTAL_LEDS], i32 length)	{
	const u32 pixel_red = (length/3)*0;
	const u32 pixel_green = (length/3)*1;
	const u32 pixel_blue = (length/3)*2;
	const u32 color_range = pixel_blue - pixel_green;

	for (u32 i=0; i<color_range; ++i)	{
		const u32 pix_red_offset = pixel_red + i;
		const u32 pix_green_offset = pixel_green + i;
		const u32 pix_blue_offset = pixel_blue + i;

		lights[pix_red_offset].g = lights[pix_green_offset].b = lights[pix_blue_offset].r = \
			(u8) ((i/(float) color_range) * 255);
		lights[pix_red_offset].r = lights[pix_green_offset].g = lights[pix_blue_offset].b = \
			(u8) (((color_range - i)/(float) color_range) * 255);
		lights[pix_red_offset].b = lights[pix_green_offset].r = lights[pix_blue_offset].g = \
			0;
	}
}

void pat_rainbow_cycle_all_same(RGB_t lights[TOTAL_LEDS], i32 length)	{
	static u32 i=0;

	if (!is_pat_set)	{
		set_pat_rainbow_efficient(colors, COLOR_RANGE);
		is_pat_set = true;
	}

	for (u32 j=0 ; j<length; ++j)	lights[j].rgb = colors[i].rgb;

	++i;
	if (i == COLOR_RANGE) i=0;	
}

void pat_rainbow_cycle_color_cycle(RGB_t lights[TOTAL_LEDS], i32 length)	{
	static u32 i=0;
	static u32 start = 0, end = 0;

	if (!is_pat_set)	{
		set_pat_rainbow_efficient(colors, COLOR_RANGE);
		is_pat_set = true;
		start = 0;
		end = length - 1;
	}

	for (u32 i=0; i<length; ++i)	{
		if (start < end)	lights[i].rgb = colors[start+i].rgb;
		else	{
			const i32 end_offset = (COLOR_RANGE - start - 1);
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

	++start;
	++end;
	if (start == COLOR_RANGE) start = 0;
	else if (end == COLOR_RANGE)	end = 0;
}

void set_range_to_color(RGB_t lights[TOTAL_LEDS], i32 length, i32 start_index, i32 end_index, RGB_t color)	{
	if (end_index < length)
		for (u32 i=start_index; i<=end_index; ++i)	
			lights[i].rgb = color.rgb;
}

void pat_bouncer(RGB_t lights[TOTAL_LEDS], i32 length, i32 bar_len, RGB_t color)	{
	static bool is_asc = true;
	static u32 start_index = 0, end_index = 0;

	if (!is_pat_set)	{
		set_range_to_color(lights, length, 0, bar_len, color);
		start_index = 0;
		end_index = bar_len-1;
		is_pat_set = true;
	}

	if (is_asc && (end_index+1) < length)	{
		lights[end_index+1].rgb = lights[start_index].rgb;
		lights[start_index].rgb = 0x0;
		++start_index;
		++end_index;

		if (end_index+1 == length)	is_asc = false;
	}
	else if (start_index-1 > 0)	{
		lights[start_index-1].rgb = lights[end_index].rgb;
		lights[end_index].rgb = 0x0;
		--start_index;
		--end_index;

		if (start_index-1 == 0)	is_asc = true;
	}
}

void pat_bright_to_fro(RGB_t lights[TOTAL_LEDS], i32 length, RGB_t color)	{
	static i8 brightness= 0;
	static bool is_asc = true;

	color.r *= (brightness/(f32) 100);
	color.g *= (brightness/(f32) 100);
	color.b *= (brightness/(f32) 100);

	set_range_to_color(lights, length, 0, length-1, color);
	if (is_asc)	{
		++brightness;
		if (brightness == 100)	is_asc = false;
	}
	else	{
		--brightness;
		if (brightness == 0)	is_asc = true;
	}
}

void pat_rainbow_cycle_color_cycle_towards_center(RGB_t lights[TOTAL_LEDS], i32 length)	{
	static u32 i=0;
	static u32 start = 0, end = 0;

	if (!is_pat_set)	{
		set_pat_rainbow_efficient(colors, COLOR_RANGE);
		is_pat_set = true;
		start = 0;
		if (length & 1)	end = length/2;
		else	end = length/2 - 1;
	}

	for (u32 i=0; i<length; ++i)	{
		if (start < end)	lights[i].rgb = colors[start+i].rgb;
		else	{
			const i32 end_offset = (COLOR_RANGE - start - 1);
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

#ifdef IS_REV
	const u32 half_length = length/2;
	const u32 fourth_length = length/4;
	for (u32 i=0; i<fourth_length; ++i)	{
		u32 temp = lights[(half_length)-1-i].rgb;
		lights[(half_length)-1-i].rgb = lights[i].rgb;
		lights[i].rgb = temp;
	}
#endif

	for (u32 i=0; i<length/2; ++i)	lights[length-1-i] = lights[i];

	++start;
	++end;
	if (start == COLOR_RANGE) start = 0;
	else if (end == COLOR_RANGE)	end = 0;
}
