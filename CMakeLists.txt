# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(keypad_14_jan C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(keypad_14_jan keypad_14_jan.c)

pico_set_program_name(keypad_14_jan "keypad_14_jan")
pico_set_program_version(keypad_14_jan "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(keypad_14_jan 0)
pico_enable_stdio_usb(keypad_14_jan 0)

# Add the standard library to the build
target_link_libraries(keypad_14_jan
        pico_stdlib
)

# Add the standard include files to the build
target_include_directories(keypad_14_jan PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Include hardware PWM header
target_include_directories(keypad_14_jan PRIVATE 
  ${PICO_SDK_PATH}/src/rp2_common/hardware_pwm/include
)

# Link PWM hardware library
target_link_libraries(keypad_14_jan
  hardware_pwm
)

# Add any user requested libraries
target_link_libraries(keypad_14_jan 
        # Add more libraries here if needed
)

pico_add_extra_outputs(keypad_14_jan)
