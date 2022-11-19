set(STM32_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/gpio.cpp
    )

include_directories(
    ${DRIVERS_DIR}/platform/stm32
    )
