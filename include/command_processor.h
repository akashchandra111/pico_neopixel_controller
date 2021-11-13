#pragma once

#include "datatypes.h"
#include "led_commander.h"

typedef enum command_enum	{
	COMMAND_CHANGE_FPS = 0x00,
	COMMAND_CHANGE_COLOR,
	COMMAND_CHANGE_PATTERN,
	COMMAND_CHANGE_INTENSITY,
	COMMAND_ENUM_LEN
} command_enum;

typedef enum command_error_enum	{
	COMMAND_NO_ERROR = 0x00,
	COMMAND_WRONG_COMMAND,
	COMMAND_CHANGE_FPS_ERROR,
	COMMAND_CHANGE_COLOR_ERROR,
	COMMAND_CHANGE_PATTERN_ERROR,
	COMMAND_CHANGE_INTENSITY_ERROR,
	COMMAND_ERROR_TOTAL
} command_error_enum;

typedef struct command_t	{
	command_enum command_type;
	u32 arg;
} command_t;

command_error_enum process_command(led_opts_t* led_options, const command_t* command);
