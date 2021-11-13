#include "../include/pattern.h"
#include "../include/command_processor.h"

command_error_enum process_command(led_opts_t* led_options, const command_t* command)	{
	if (command->command_type > COMMAND_ENUM_LEN)	{
		return COMMAND_WRONG_COMMAND;
	}

	switch(command->command_type)	{
		case COMMAND_CHANGE_FPS:	{
			led_options_set_fps(command->arg);
			break;
		}
		case COMMAND_CHANGE_COLOR:	{
			led_set_to_rgb_color(
				led_options, 
				get_rgb_from_u32(command->arg),
				0, 
				led_options->leds_buffer.length
			);
			break;
		}
		case COMMAND_CHANGE_PATTERN:	{
			if ((u32) command->arg > PATTERN_TOTAL_PATTERNS)	return COMMAND_CHANGE_PATTERN_ERROR;
			led_pattern_switch((pattern_enum) command->arg);
			break;
		}
		case COMMAND_CHANGE_INTENSITY:	{
			const f32 intensity = (f32) command->arg;

			if (intensity < .0f || intensity > 1.f) return COMMAND_CHANGE_INTENSITY_ERROR;
			led_set_pixel_intensity(led_options, intensity);
			break;
		}
		default:	{
			return COMMAND_WRONG_COMMAND;
		}
	}

	return COMMAND_NO_ERROR;
}
