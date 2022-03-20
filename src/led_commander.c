#include "hardware/gpio.h"
#include "hardware/pio.h"

#include "pico/stdlib.h"

#include "../include/led_commander.h"
#include "../include/datatypes.h"
#include "../include/neopixel.h"

void led_options_init(led_opts_t *led_options, const u8 fps, const f32 intensity, const u16 led_buffer_len, const u8 pin)	{
	// set data structure
	led_options->fps = fps;
	led_options->leds_buffer.length = led_buffer_len;
	led_options->intensity = intensity;

	// set gpio
	gpio_init(pin);
	gpio_set_dir(pin, GPIO_OUT);
	neopixel_init(pio0, 0, pin);
}

// It uses sleep_ms function to create illusion of fps
// independent of the led_opts_t struct
inline void led_options_set_fps(const u8 fps)	{
	sleep_ms(fps);
}

inline void led_send_pixels(led_opts_t* led_options)	{
	neopixel_send(
		led_options->leds_buffer.buffer,
		led_options->leds_buffer.length,
		led_options->intensity
	);
}

// Set intensity for single frame (use it when changes are less often)
inline void led_set_pixel_intensity(led_opts_t* led_options, const f32 intensity)	{
	led_options->intensity = intensity;
}

inline void led_display(led_opts_t* led_options)	{
	sleep_ms(led_options->fps);
	led_send_pixels(led_options);
}

inline void led_buffer_shl(led_opts_t* led_options, const bool is_cyclic)	{
	if (is_cyclic)
		led_options->leds_buffer.buffer[0].rgb = led_options->leds_buffer.buffer[led_options->leds_buffer.length-1].rgb;
	else
		led_options->leds_buffer.buffer[0].rgb = 0;

	for (int i=(led_options->leds_buffer.length)-1; i>0; --i)	
		led_options->leds_buffer.buffer[i].rgb = led_options->leds_buffer.buffer[i-1].rgb;
}

inline void led_buffer_shr(led_opts_t* led_options, const bool is_cyclic)	{
	if (is_cyclic)
		led_options->leds_buffer.buffer[led_options->leds_buffer.length-1].rgb = led_options->leds_buffer.buffer[0].rgb;
	else
		led_options->leds_buffer.buffer[led_options->leds_buffer.length-1].rgb = 0;

	for (int i=0; i<led_options->leds_buffer.length-1; ++i)	
		led_options->leds_buffer.buffer[i].rgb = led_options->leds_buffer.buffer[i+1].rgb;
}

inline void led_set_to_rgb_color(led_opts_t* led_options, const RGB_t color_pattern, const u32 start, const u32 end)	{
	for (int i=start, j=0; i <= end && j<led_options->leds_buffer.length; ++i, ++j)
		set_rgb_from_u32(&led_options->leds_buffer.buffer[i], color_pattern.rgb);
}

void led_pattern_switch(const pattern_enum pattern_type)	{
	is_pat_set = false;

	if (pattern_type > PATTERN_TOTAL_PATTERNS)	current_pattern = PATTERN_NO_PATTERN;
	else	current_pattern = pattern_type;
}

void led_run_current_pattern(led_opts_t* led_options, extra_opts_t *extra_options)	{
	switch(current_pattern)	{
		case PATTERN_NO_PATTERN:	{
			set_range_to_color(
				led_options->leds_buffer.buffer,
				led_options->leds_buffer.length,
				0,
				led_options->leds_buffer.length-1,
				extra_options->temp_color
			);
			break;
		}
		case PATTERN_TIME:	{
			pat_time(
				extra_options->date_time,
				led_options->leds_buffer.buffer,
				led_options->leds_buffer.length
			);
			break;
		}
		case PATTERN_TIME_1:		{
			pat_time_1(
				extra_options->date_time,
				led_options->leds_buffer.buffer,
				led_options->leds_buffer.length
			);
			break;
		}
		case PATTERN_TIME_2:		{
			pat_time_2(
				extra_options->date_time,
				led_options->leds_buffer.buffer,
				led_options->leds_buffer.length
			);
			break;
		}
		case PATTERN_FIRE:		{
			pat_fire(
				led_options->leds_buffer.buffer, 
				led_options->leds_buffer.length
			);
			break;
		}
		case PATTERN_RAINBOW_CYCLE_ALL_SAME:		{
			pat_rainbow_cycle_all_same(
				led_options->leds_buffer.buffer, 
				led_options->leds_buffer.length
			);
			break;
		}
		case PATTERN_RAINBOW_CYCLE_COLOR_CYCLE:		{
			pat_rainbow_cycle_color_cycle(
				led_options->leds_buffer.buffer, 
				led_options->leds_buffer.length
			);
			break;
		}
		case PATTERN_BRIGHT_TO_FRO:		{
			pat_bright_to_fro(
				led_options->leds_buffer.buffer, 
				led_options->leds_buffer.length,
				extra_options->temp_color
			);
			break;
		}
		case PATTERN_RAINBOW_CYCLE_TOWARDS_CENTER:		{
			pat_rainbow_cycle_color_cycle_towards_center(
				led_options->leds_buffer.buffer, 
				led_options->leds_buffer.length,
				true
			);
			break;
		}
		case PATTERN_RAINBOW_CYCLE_AWAY_CENTER:		{
			pat_rainbow_cycle_color_cycle_towards_center(
				led_options->leds_buffer.buffer, 
				led_options->leds_buffer.length,
				false	
			);
			break;
		}
		case PATTERN_MAP_TEMP:		{
			pat_map_pico_temp(
				led_options->leds_buffer.buffer, 
				led_options->leds_buffer.length
			);
			break;
		}
		default:		{
		}
	}
}
