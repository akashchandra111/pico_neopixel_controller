#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

// #include "hardware/rtc.h"
// #include "pico/util/datetime.h"

#include "pico/stdlib.h"

#include "../include/led_commander.h"
#include "../include/neopixel.h"
#include "../include/pattern.h"
	
#define DEBUG 0							// conditional variable to enable debugging
#define NPIN 0u							// PIN which control the neopixels
#define LED_INTENSITY 10				// LED intensity in %

int main()	{
	stdio_init_all();

	led_opts_t led_options;
	led_options_init(
		&led_options, 
		FPS, 
		LED_INTENSITY, 
		TOTAL_LEDS, 
		NPIN
	);

	/*
	// Setup Datetime
	datetime_t dt = {
		.year = 2021,
		.month = 10,
		.day = 15,	// Date
		.dotw = 6,	// Sunday
		.hour = 14,
		.min = 30,
		.sec = 0
	};

	rtc_init();
	rtc_set_datetime(&dt);
	*/

	while (1)	{
		pat_rainbow_cycle_all_same(
			led_options.leds_buffer.buffer,
			led_options.leds_buffer.length
		);

#if DEBUG
		for (int i=0; i<led_options.leds_buffer.length; ++i)	
			printf("%x|", led_options.leds_buffer.buffer[i]);
		printf("\n");
#endif
		// Send the rgb data to neopixel in one go
		led_display(&led_options);
	}

	return 0;
}
