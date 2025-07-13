cmake_minimum_required(VERSION 3.28)
project(armcortexa_cpp_lib VERSION 1.0.0)

include(arm_none_eabi_gcc.cmake)

enable_language(CXX)

add_library(cortexa5 INTERFACE)
target_include_directories(cortexa5 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(cortexa5 INTERFACE cxx_std_20)
set_target_properties(cortexa5 PROPERTIES EXPORT_NAME cortex-a5)

add_library(cortexa7 INTERFACE)
target_include_directories(cortexa7 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(cortexa7 INTERFACE cxx_std_20)
set_target_properties(cortexa7 PROPERTIES EXPORT_NAME cortex-a7)

add_library(cortexa9 INTERFACE)
target_include_directories(cortexa9 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(cortexa9 INTERFACE cxx_std_20)
set_target_properties(cortexa9 PROPERTIES EXPORT_NAME cortex-a9)

# Set common compile options for all targets
set(COMMON_FLAGS
    -mthumb-interwork
    -mfloat-abi=hard
    -ffunction-sections
    -fdata-sections
    -fno-common
    -ffreestanding
    -fno-builtin
    -fomit-frame-pointer
    -gdwarf-3
    -Wall
    -Wextra
    -Wshadow
    -Wconversion
    -Wsign-conversion
    -Wunused-variable
    -Wunused-parameter
    -Wunused-function
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wformat-signedness
    -Wdouble-promotion
    -Wmissing-include-dirs
    -fno-exceptions
    -fno-rtti
    -fno-unwind-tables
    -fno-threadsafe-statics
    -Wno-psabi
)

# Set specific options for each target
target_compile_options(cortexa5 INTERFACE ${COMMON_FLAGS} -mcpu=cortex-a5 -mfpu=neon-vfpv4)
target_compile_options(cortexa7 INTERFACE ${COMMON_FLAGS} -mcpu=cortex-a7 -mfpu=neon-vfpv4)
target_compile_options(cortexa9 INTERFACE ${COMMON_FLAGS} -mcpu=cortex-a9 -mfpu=neon)

# Export targets
install(
    TARGETS cortexa5 cortexa7 cortexa9
    EXPORT armcortexa_cpp_lib
)

install(
    EXPORT armcortexa_cpp_lib
    FILE armcortexa_cpp_lib.cmake
    NAMESPACE armcortexa::
    DESTINATION lib/cmake/armcortexa_cpp_lib
)

install(
    FILES utils.hpp
    DESTINATION include
)

install(
    DIRECTORY cortexa5 cortexa7 cortexa9
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)
