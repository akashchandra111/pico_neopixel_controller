#pragma once

#include "default_params.h"
#include "datatypes.h"
#include "neopixel.h"


typedef struct led_array_t	{
	RGB_t buffer[LED_BUFFER_SIZE];
	u16 length;
} led_array_t;
