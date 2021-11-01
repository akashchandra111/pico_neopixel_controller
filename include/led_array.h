#ifndef ARRAY_H
#define ARRAY_H

#include "default_params.h"
#include "neopixel.h"
#include "datatypes.h"


typedef struct led_array_t	{
	RGB_t buffer[LED_BUFFER_SIZE];
	u16 length;
} led_array_t;

#endif
