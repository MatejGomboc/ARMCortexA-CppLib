set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

if(MINGW OR CYGWIN OR WIN32)
    set(UTIL_SEARCH_CMD where)
elseif(UNIX OR APPLE)
    set(UTIL_SEARCH_CMD which)
endif()

set(TOOLCHAIN_PREFIX arm-none-eabi-)

execute_process(
    COMMAND ${UTIL_SEARCH_CMD} ${TOOLCHAIN_PREFIX}gcc
    OUTPUT_VARIABLE BINUTILS_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(BINUTILS_PATH)
    get_filename_component(ARM_TOOLCHAIN_DIR ${BINUTILS_PATH} DIRECTORY)
else()
    message(FATAL_ERROR "Toolchain ${TOOLCHAIN_PREFIX}gcc not found!")
endif()

# Without this flag CMake is unable to pass the compiler sanity check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)

set(CMAKE_OBJCOPY ${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}objcopy CACHE INTERNAL "objcopy tool")
set(CMAKE_SIZE_UTIL ${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}size CACHE INTERNAL "size tool")

set(CMAKE_FIND_ROOT_PATH ${BINUTILS_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Set Cortex-A specific compile flags
set(ARM_FLAGS "-marm -march=armv7-a")

set(CMAKE_C_FLAGS "${ARM_FLAGS}" CACHE INTERNAL "C compiler flags")
set(CMAKE_CXX_FLAGS "${ARM_FLAGS}" CACHE INTERNAL "C++ compiler flags")
set(CMAKE_ASM_FLAGS "${ARM_FLAGS} -x assembler-with-cpp" CACHE INTERNAL "ASM compiler flags")

set(CMAKE_C_FLAGS_DEBUG "-O0 -g3" CACHE INTERNAL "C compiler flags debug")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3" CACHE INTERNAL "C++ compiler flags debug")
set(CMAKE_ASM_FLAGS_DEBUG "-g3" CACHE INTERNAL "ASM compiler flags debug")

set(CMAKE_C_FLAGS_RELEASE "-O3" CACHE INTERNAL "C compiler flags release")
set(CMAKE_CXX_FLAGS_RELEASE "-O3" CACHE INTERNAL "C++ compiler flags release")
set(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "ASM compiler flags release")

set(CMAKE_EXE_LINKER_FLAGS "-specs=nosys.specs -Wl,--gc-sections -Wl,--print-memory-usage" CACHE INTERNAL "Linker flags")
