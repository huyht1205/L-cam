# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(TARGET_TRIPLET "arm-none-eabi-")

include(${CMAKE_CURRENT_LIST_DIR}/user-config.cmake)

add_compile_definitions(__arm__)

# default to Debug build
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: Debug Release." FORCE)
endif()

# do some windows specific logic
if(WIN32)
    set(TOOLCHAIN_EXT ".exe")
else()
    set(TOOLCHAIN_EXT "")
endif(WIN32)

find_program(COMPILER_ON_PATH "${TARGET_TRIPLET}gcc${TOOLCHAIN_EXT}")

if(NOT "${TOOLCHAIN_PATH}" STREQUAL "")
    # Check if user has defined toolchain path in user-config.cmake
    message(STATUS "User toolchain path: ${TOOLCHAIN_PATH}")
    set(ARM_TOOLCHAIN_PATH ${TOOLCHAIN_PATH})
elseif(DEFINED ENV{ARM_GCC_PATH})
    # use the environment variable first
    file(TO_CMAKE_PATH $ENV{ARM_GCC_PATH} ARM_TOOLCHAIN_PATH)
    message(STATUS "Using ENV variable ARM_GCC_PATH = ${ARM_TOOLCHAIN_PATH}")
elseif(COMPILER_ON_PATH)
    # then check on the current path
    get_filename_component(ARM_TOOLCHAIN_PATH ${COMPILER_ON_PATH} DIRECTORY)
    message(STATUS "Using ARM GCC from path = ${ARM_TOOLCHAIN_PATH}")
else()
    message(FATAL_ERROR "Unable to find ARM GCC. Either add to your PATH, or define ARM_GCC_PATH to the compiler location")
endif()

# Perform compiler test with the static library
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER    ${ARM_TOOLCHAIN_PATH}/${TARGET_TRIPLET}gcc${TOOLCHAIN_EXT})
set(CMAKE_CXX_COMPILER  ${ARM_TOOLCHAIN_PATH}/${TARGET_TRIPLET}g++${TOOLCHAIN_EXT})
set(CMAKE_ASM_COMPILER  ${ARM_TOOLCHAIN_PATH}/${TARGET_TRIPLET}gcc${TOOLCHAIN_EXT})
set(CMAKE_LINKER        ${ARM_TOOLCHAIN_PATH}/${TARGET_TRIPLET}gcc${TOOLCHAIN_EXT})
set(CMAKE_SIZE_UTIL     ${ARM_TOOLCHAIN_PATH}/${TARGET_TRIPLET}size${TOOLCHAIN_EXT})
set(CMAKE_OBJCOPY       ${ARM_TOOLCHAIN_PATH}/${TARGET_TRIPLET}objcopy${TOOLCHAIN_EXT})
set(CMAKE_OBJDUMP       ${ARM_TOOLCHAIN_PATH}/${TARGET_TRIPLET}objdump${TOOLCHAIN_EXT})
set(CMAKE_NM_UTIL       ${ARM_TOOLCHAIN_PATH}/${TARGET_TRIPLET}gcc-nm${TOOLCHAIN_EXT})
set(CMAKE_AR            ${ARM_TOOLCHAIN_PATH}/${TARGET_TRIPLET}gcc-ar${TOOLCHAIN_EXT})
set(CMAKE_RANLIB        ${ARM_TOOLCHAIN_PATH}/${TARGET_TRIPLET}gcc-ranlib${TOOLCHAIN_EXT})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
