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

inline void led_set_to_rgb_color(led_opts_t* led_options, const RGB_t color_pattern)	{
	for (int i=0; i<led_options->leds_buffer.length; ++i)
		set_rgb_from_u32(&led_options->leds_buffer.buffer[i], color_pattern.rgb);
}
