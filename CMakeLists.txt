cmake_minimum_required(VERSION 3.21)

project(
  embarcas
  VERSION 0.0.1
  DESCRIPTION "A project for studying C and Embedded Systems"
  LANGUAGES C
  )

set(TARGET_NAME "${PROJECT_NAME}-bin")
set(MCU atmega328p)
set(BAUD_RATE 9600)
set(F_CPU 16000000UL)
set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall -Wextra -std=c11")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json)


add_executable(${TARGET_NAME} src/main.c)
target_link_libraries(${TARGET_NAME} PUBLIC embarcas)
target_include_directories("${TARGET_NAME}" PRIVATE include)

add_subdirectory(src)

add_custom_command(TARGET "${TARGET_NAME}" POST_BUILD
  COMMAND avr-objcopy -O ihex ${TARGET_NAME} "${PROJECT_NAME}.hex"
  COMMENT "Generating HEX file..."
)

