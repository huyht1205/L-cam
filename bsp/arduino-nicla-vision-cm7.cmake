include(${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/arduino-nicla-vision.cmake)

set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/STM32H747AIIX_FLASH.ld)

set(CM7_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/Core/Startup/startup_stm32h747aiix.s
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/Core/Src/stm32h7xx_hal_msp.c
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/Core/Src/jpeg.c
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/Core/Src/gpio.c
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM4/Core/Src/rtc.c
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM4/Core/Src/i2c.c
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/Core/Src/stm32h7xx_hal_timebase_tim.c
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/Core/Src/syscalls.c
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/Core/Src/freertos.c
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/Core/Src/main.c
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/Core/Src/sysmem.c
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/Core/Src/stm32h7xx_it.c
    )

set(BSP_SOURCES ${BSP_SOURCES}
    ${CM7_SOURCES}
    ${CM4_SOURCES}
    )

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM7/Core/Inc
    ${CMAKE_CURRENT_LIST_DIR}/arduino-nicla-vision/CM4/Core/Inc
    )

set(MCU_OPTS
    -mcpu=cortex-m7
    -mthumb
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    )

add_compile_options(
    ${MCU_OPTS}
    -DCORE_CM7
    -DSTM32H747xx
    )

add_link_options(
    ${MCU_OPTS}
    -T ${LINKER_SCRIPT}
    )
