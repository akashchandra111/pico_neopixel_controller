#pragma once

#include "hardware/rtc.h"
#include "pico/util/datetime.h"

#include "datatypes.h"
#include "neopixel.h"

#define DEBUG 0
#define COLOR_RANGE (180*3)
#define IS_REV 1

static RGB_t colors[COLOR_RANGE];	// Global color indexing memory
static u8 vals[NPIN_TOTAL] = { 0 };	// Used only for time patterns
static bool is_pat_set = false;

typedef enum pattern_enum	{
	PATTERN_NO_PATTERN = 0x00,
	PATTERN_TIME,
	PATTERN_TIME_1,
	PATTERN_TIME_2,
	PATTERN_FIRE,
	PATTERN_RAINBOW_CYCLE_ALL_SAME,
	PATTERN_RAINBOW_CYCLE_COLOR_CYCLE,
	PATTERN_BRIGHT_TO_FRO,
	PATTERN_RAINBOW_CYCLE_TOWARDS_CENTER,
	PATTERN_RAINBOW_CYCLE_AWAY_CENTER,
	PATTERN_TOTAL_PATTERNS
} pattern_enum;

void pat_time(datetime_t *dt, RGB_t lights[TOTAL_LEDS], i32 length);
void pat_time_1(datetime_t *dt, RGB_t lights[TOTAL_LEDS], i32 length);
void pat_time_2(datetime_t *dt, RGB_t lights[TOTAL_LEDS], i32 length);
void pat_fire(RGB_t lights[TOTAL_LEDS], i32 length);
void pat_rainbow_cycle_all_same(RGB_t lights[TOTAL_LEDS], i32 length);
void pat_rainbow_cycle_color_cycle(RGB_t lights[TOTAL_LEDS], i32 length);
void pat_bouncer(RGB_t lights[TOTAL_LEDS], i32 length, i32 bar_len, RGB_t color);
void pat_bright_to_fro(RGB_t lights[TOTAL_LEDS], i32 length, RGB_t color);
void pat_rainbow_cycle_color_cycle_towards_center(RGB_t lights[TOTAL_LEDS], i32 length, const bool is_rev);

void set_pat_rainbow(RGB_t lights[TOTAL_LEDS], i32 length);
void set_pat_rainbow_efficient(RGB_t lights[TOTAL_LEDS], i32 length);
void set_range_to_color(RGB_t lights[TOTAL_LEDS], i32 length, i32 start_index, i32 end_index, RGB_t color);
