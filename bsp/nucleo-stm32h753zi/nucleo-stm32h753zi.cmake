# C sources
set(BSP_SOURCES
    ${BSP_DIR}/Core/Src/main.c
    ${BSP_DIR}/Core/Src/gpio.c
    ${BSP_DIR}/Core/Src/freertos.c
    ${BSP_DIR}/Core/Src/jpeg.c
    ${BSP_DIR}/Core/Src/rtc.c
    ${BSP_DIR}/Core/Src/usart.c
    ${BSP_DIR}/Core/Src/stm32h7xx_it.c
    ${BSP_DIR}/Core/Src/stm32h7xx_hal_msp.c
    ${BSP_DIR}/Core/Src/stm32h7xx_hal_timebase_tim.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_jpeg.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rtc.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rtc_ex.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c
    ${BSP_DIR}/Core/Src/system_stm32h7xx.c
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/list.c
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/queue.c
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/timers.c
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
    ${BSP_DIR}/Utilities/JPEG/jpeg_utils.c
)

# ASM sources
set(BSP_ASM_SOURCES
    ${BSP_DIR}/startup_stm32h753xx.s
)

# ASM includes
include_directories(
    ${BSP_DIR}/Core/Inc
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc
    ${BSP_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
    ${BSP_DIR}/Utilities/JPEG
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/include
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    ${BSP_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ${BSP_DIR}/Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ${BSP_DIR}/Drivers/CMSIS/Include
)

set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/STM32H753ZITx_FLASH.ld)

set(MCU_OPTS
    -mcpu=cortex-m7
    -mthumb
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    )

add_compile_options(
    ${MCU_OPTS}
    )

add_link_options(
    ${MCU_OPTS}
    -T ${LINKER_SCRIPT}
    )

add_compile_definitions(
    USE_HAL_DRIVER
    STM32H753xx
    )

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
