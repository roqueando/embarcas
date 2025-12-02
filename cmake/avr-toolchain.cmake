set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

# Impedir que flags do Clang vazem
set(CMAKE_C_FLAGS_INIT "")
set(CMAKE_CXX_FLAGS_INIT "")
set(CMAKE_EXE_LINKER_FLAGS_INIT "")

# MCU padrão
set(MCU attiny85)
set(F_CPU 16000000UL)

set(CMAKE_C_FLAGS_INIT "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall -Wextra -std=c11")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-mmcu=${MCU}")
