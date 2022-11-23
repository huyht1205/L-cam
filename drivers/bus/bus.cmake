set(BUS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/bus.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bus_i2c.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bus_spi.cpp
    )

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    )