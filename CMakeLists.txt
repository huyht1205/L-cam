#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.15)

# project settings
set(PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(PROJECT_NAME "L-cam")
set(BSP "nucleo-stm32h753zi")
set(PLATFORM "stm32")
include("cmake/user-config.cmake")
include("cmake/path.cmake")
include("cmake/arm-none-eabi-gcc.cmake")
include("cmake/toolchain.cmake")
include("${PLATFORM_DIR}/${PLATFORM}.cmake")
include("${BSP_DIR}/${BSP}.cmake")
include("${PERIPHERALS_DIR}/peripherals.cmake")
include("${BUS_DIR}/bus.cmake")

project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

include_directories(
    .
    application/inc
    peripherals/inc
    )

add_compile_definitions(
    )

link_libraries(
    )

set(APP_SOURCES
    application/src/app.cpp
    )

file(GLOB_RECURSE SOURCES
    ${APP_SOURCES}
    ${BSP_ASM_SOURCES}
    ${BSP_SOURCES}
    ${PLATFORM_SOURCES}
    ${PERIPHERALS_SOURCES}
    )

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
post_build(${PROJECT_NAME})
include("cmake/doxygen.cmake")
set(BUILD_WITH_DOCS ON)
