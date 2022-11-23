include("${CMAKE_CURRENT_LIST_DIR}/b-l4s5i-iot01a.cmake")

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    )

set(BSP_SOURCES ${BSP_SOURCES}
    bsp/${BSP}/bsp.cpp
    bsp/${BSP}/bsp_system_clock.cpp
    bsp/${BSP}/bsp_interrupt_handler.cpp
    )

