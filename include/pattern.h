#pragma once
#include "hardware/rtc.h"
#include "pico/util/datetime.h"

#include "datatypes.h"
#include "neopixel.h"

void pat_time(datetime_t *dt, i32 temperature, RGB_t lights[TOTAL_LEDS], i32 length);
void pat_time_1(datetime_t *dt, i32 temperature, RGB_t lights[TOTAL_LEDS], i32 length);
void pat_time_2(datetime_t *dt, i32 temperature, RGB_t lights[TOTAL_LEDS], i32 length);
void pat_fire(RGB_t lights[TOTAL_LEDS], i32 length);
void pat_rainbow_cycle_all_same(RGB_t lights[TOTAL_LEDS], i32 length);
void pat_rainbow_cycle_color_cycle(RGB_t lights[TOTAL_LEDS], i32 length);
void pat_bouncer(RGB_t lights[TOTAL_LEDS], i32 length, i32 bar_len, RGB_t color);
void pat_bright_to_fro(RGB_t lights[TOTAL_LEDS], i32 length, RGB_t color);
void pat_rainbow_cycle_color_cycle_towards_center(RGB_t lights[TOTAL_LEDS], i32 length);

void set_pat_rainbow(RGB_t lights[TOTAL_LEDS], i32 length);
void set_pat_rainbow_efficient(RGB_t lights[TOTAL_LEDS], i32 length);
void set_range_to_color(RGB_t lights[TOTAL_LEDS], i32 length, i32 start_index, i32 end_index, RGB_t color);
