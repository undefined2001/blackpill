cmake_minimum_required(VERSION 3.12)

# ##############################################################################
# Edit your MCU information up to the next border

include(arm-none-eabi.cmake)

project(baremetal C CXX ASM)

# Set CPU-specific compile and linker options
set(CPU_PARAMETERS
    "-mcpu=cortex-m4"
    "-mthumb"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
)

# Linker script for the specific MCU
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/stm32f4.ld)

# ##############################################################################

# Executable name based on the project name
set(EXECUTABLE ${CMAKE_PROJECT_NAME})

# Set C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Directories for header files
set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/inc 
)

# CMSIS core headers
set(CMSIS ${CMAKE_CURRENT_SOURCE_DIR}/core)

# Define the target (the executable) and its properties
add_executable(${EXECUTABLE} ${SRC_FILES})  # Ensure you have a source file here, replace `main.c` with your actual main file.

# Compile definitions for STM32F411xE MCU
target_compile_definitions(${EXECUTABLE} PUBLIC STM32F411xE)

# Include directories
target_include_directories(${EXECUTABLE} SYSTEM PUBLIC ${CMSIS})
target_include_directories(${EXECUTABLE} PUBLIC ${INCLUDE_DIRS})

# Compiler options
target_compile_options(${EXECUTABLE} PUBLIC
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-Og -g0>
)

# Linker options
target_link_options(${EXECUTABLE} PUBLIC
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${EXECUTABLE}.map
    -u_printf_float
    --specs=nosys.specs
    -Wl,--start-group
    -lm
    -lstdc++_nano
    -lc_nano
    -Wl,--end-group
    -Wl,--print-memory-usage
)

add_custom_command(
  TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE}.elf ${EXECUTABLE}.bin
  COMMENT "Converting ELF to BIN"
)
