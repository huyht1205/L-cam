include("${CMAKE_CURRENT_LIST_DIR}/device/device.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/pmu/pmu.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/sensor/sensor.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/bus/bus.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/led/led.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/platform/stm32/stm32.cmake")

set(DRIVERS_SOURCES
    ${DEVICE_SOURCES}
    # ${PMU_SOURCES}
    ${LED_SOURCES}
    ${BUS_SOURCES}
    ${STM32_SOURCES}
    ${STM32_SOURCES}
    ${SENSOR_SOURCES}
    )
