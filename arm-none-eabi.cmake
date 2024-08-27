set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)


set(SRC_FILES
./src/startup.s
./src/system_stm32f4xx.c
./src/syscalls.c
./src/sysmem.c
./src/spi.cpp
./src/main.cpp
)

# Some default GCC settings
set(FLAGS
-fdata-sections -ffunction-sections #-nostartfiles
--specs=nano.specs -Wl,--gc-sections)
set(CPP_FLAGS
-fno-rtti -fno-exceptions
-fno-threadsafe-statics)

set(TOOLCHAIN_PREFIX arm-none-eabi)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc ${FLAGS})
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++ ${FLAGS} ${CPP_FLAGS})
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}-size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)