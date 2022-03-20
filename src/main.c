#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/util/datetime.h"
#include "hardware/rtc.h"

#include "../include/led_commander.h"
#include "../include/neopixel.h"
#include "../include/pattern.h"
#include "../include/basic_math.h"
	
#define DEBUG 0							// conditional variable to enable debugging
#define NPIN 0u							// PIN which control the neopixels

int main()	{
	stdio_init_all();
	
	// Setup Datetime
	datetime_t dt = (datetime_t)	{
		.year = 2021,
		.month = 11,
		.day = 13,	// Date
		.dotw = 5,	// Sunday
		.hour = 18,
		.min = 0,
		.sec = 0
	};

	rtc_init();
	rtc_set_datetime(&dt);

	led_opts_t led_options;
	extra_opts_t extra_options = {
		.temp_color = get_rgb(0xFF, 0xFF, 0xFF),
		.date_time = &dt
	};

	led_options_init(
		&led_options, 
		FPS, 
		LED_INTENSITY, 
		TOTAL_LEDS, 
		NPIN
	);

	led_pattern_switch(PATTERN_MAP_TEMP);

	while (true)	{
		led_run_current_pattern(
			&led_options, 
			&extra_options
		);

#if DEBUG
#endif
		// Send the rgb data to neopixel in one go
		led_display(&led_options);
	}

	return 0;
}
