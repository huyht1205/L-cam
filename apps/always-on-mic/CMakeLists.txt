#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.15)

include("cmake/toolchain.cmake")
project(${PROJECT_NAME} C CXX ASM)
enable_language(C)

# project settings
set(PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(PROJECT_NAME "always-on-mic")

include("project-config.cmake")
include("cmake/path.cmake")
include("drivers/drivers.cmake")
include("bsp/${BSP}/${BSP}.cmake")
include("os/${OS}/${OS}.cmake")

include_directories(
    .
    inc
    )

add_compile_options(
    )

link_libraries(
    )

set(APP_SOURCES
    src/app.cpp
    )

set(SOURCES
    ${DRIVERS_SOURCES}
    ${BSP_SOURCES}
    ${OS_SOURCES}
    ${APP_SOURCES}
    )

set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
# include("cmake/doxygen.cmake")
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
post_build(${PROJECT_NAME})
set(make)
