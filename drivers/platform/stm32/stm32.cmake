set(STM32_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/gpio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/i2c.cpp
    ${CMAKE_CURRENT_LIST_DIR}/spi.cpp
    ${CMAKE_CURRENT_LIST_DIR}/system_clock.cpp
    )

include_directories(
    ${DRIVERS_DIR}/platform/stm32
    )
