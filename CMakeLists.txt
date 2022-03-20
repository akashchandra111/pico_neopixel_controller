cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(neopixel C CXX ASM)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable( ${PROJECT_NAME}
    src/main.c
	src/neopixel.c
	src/pattern.c
	src/led_commander.c
	src/command_processor.c
	src/basic_math.c
)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/src/ws2812b.pio)

target_include_directories(${PROJECT_NAME} PUBLIC include/)

#enable usb output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	pico_stdlib 
	hardware_pio
	hardware_rtc 
	hardware_gpio
	hardware_adc
	# harpico_multicore 
	# harhardware_i2c
)
