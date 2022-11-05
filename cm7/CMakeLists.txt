#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.15)

include("cmake/toolchain.cmake")
project(${PROJECT_NAME} C CXX ASM)

# project settings
set(PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(PROJECT_NAME "L-cam-cm7")

include("cmake/config.cmake")
include("cmake/user-config.cmake")
include("cmake/path.cmake")
include("${DRIVERS_DIR}/drivers.cmake")
include("${BSP_DIR}/${BSP}.cmake")
include("${OS_DIR}/os.cmake")

include_directories(
    .
    application/inc
    )

add_compile_options(
    )

link_libraries(
    )

set(APP_SOURCES
    application/src/app.cpp
    )

file(GLOB_RECURSE SOURCES
    ${DRIVERS_SOURCES}
    ${BSP_SOURCES}
    ${APP_SOURCES}
    )

include("cmake/doxygen.cmake")
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
post_build(${PROJECT_NAME})
set(make)