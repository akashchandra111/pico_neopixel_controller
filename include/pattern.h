#pragma once
#include "hardware/rtc.h"
#include "pico/util/datetime.h"

#include "neopixel.h"

void pat_time(datetime_t *dt, int temperature, RGB_t lights[TOTAL_LEDS], int length);
void pat_time_1(datetime_t *dt, int temperature, RGB_t lights[TOTAL_LEDS], int length);
void pat_time_2(datetime_t *dt, int temperature, RGB_t lights[TOTAL_LEDS], int length);
void pat_fire(RGB_t lights[TOTAL_LEDS], int length);

void set_pat_rainbow(RGB_t lights[TOTAL_LEDS], int length);
void set_pat_rainbow_efficient(RGB_t lights[TOTAL_LEDS], int length);
void pat_rainbow_cycle_all_same(RGB_t lights[TOTAL_LEDS], int length);
void pat_rainbow_cycle_color_cycle(RGB_t lights[TOTAL_LEDS], int length);
