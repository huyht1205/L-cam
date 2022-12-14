set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/STM32L4R5ZITxP_FLASH.ld)

set(BSP_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/main.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/gpio.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/freertos.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/crc.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/dma.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/usart.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/rng.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/rtc.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/stm32l4xx_it.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/stm32l4xx_hal_msp.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/stm32l4xx_hal_timebase_tim.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc_ex.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rng.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rng_ex.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.c
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/system_stm32l4xx.c
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/list.c
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/queue.c
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/timers.c
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/i2c.c
	${CMAKE_CURRENT_LIST_DIR}/startup_stm32l4r5xx.s
	)

include_directories(
	${CMAKE_CURRENT_LIST_DIR}/Core/Inc
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Inc
	${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/include
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
	${CMAKE_CURRENT_LIST_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
	${CMAKE_CURRENT_LIST_DIR}/Drivers/CMSIS/Device/ST/STM32L4xx/Include
	${CMAKE_CURRENT_LIST_DIR}/Drivers/CMSIS/Include
	)

set(MCU_OPTS
	-mcpu=cortex-m4
	-mthumb
	-mfpu=fpv4-sp-d16
	-mfloat-abi=hard
	)

add_link_options(
	${MCU_OPTS}
	-T ${LINKER_SCRIPT}
	)


add_compile_options(
	-DUSE_HAL_DRIVER
	-DSTM32L4R5xx
	${MCU_OPTS}
	)


