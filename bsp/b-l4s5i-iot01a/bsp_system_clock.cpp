/**
 * @file bsp_SYS_CLOCK.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "bsp_system_clock.hpp"
#include "main.h"

static void _peripheral_clock_max_performance( void );

void system_clock_max_performance()
{
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    /** Configure the main internal regulator output voltage
     */
    if ( HAL_PWREx_ControlVoltageScaling(
             PWR_REGULATOR_VOLTAGE_SCALE1_BOOST ) != HAL_OK )
    {
        Error_Handler();
    }

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType =
        RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState      = RCC_HSE_BYPASS;
    RCC_OscInitStruct.LSIState      = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState  = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM      = 2;
    RCC_OscInitStruct.PLL.PLLN      = 60;
    RCC_OscInitStruct.PLL.PLLP      = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ      = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR      = RCC_PLLR_DIV2;
    if ( HAL_RCC_OscConfig( &RCC_OscInitStruct ) != HAL_OK )
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if ( HAL_RCC_ClockConfig( &RCC_ClkInitStruct, FLASH_LATENCY_5 ) != HAL_OK )
    {
        Error_Handler();
    }

    _peripheral_clock_max_performance();
}

static void _peripheral_clock_max_performance( void )
{
    RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

    /** Initializes the peripherals clock
     */
    PeriphClkInit.PeriphClockSelection  = RCC_PERIPHCLK_USB | RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection     = RCC_ADCCLKSOURCE_PLLSAI1;
    PeriphClkInit.UsbClockSelection     = RCC_USBCLKSOURCE_PLLSAI1;
    PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSE;
    PeriphClkInit.PLLSAI1.PLLSAI1M      = 1;
    PeriphClkInit.PLLSAI1.PLLSAI1N      = 24;
    PeriphClkInit.PLLSAI1.PLLSAI1P      = RCC_PLLP_DIV2;
    PeriphClkInit.PLLSAI1.PLLSAI1Q      = RCC_PLLQ_DIV4;
    PeriphClkInit.PLLSAI1.PLLSAI1R      = RCC_PLLR_DIV2;
    PeriphClkInit.PLLSAI1.PLLSAI1ClockOut =
        RCC_PLLSAI1_48M2CLK | RCC_PLLSAI1_ADC1CLK;
    if ( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInit ) != HAL_OK )
    {
        Error_Handler();
    }
}

void system_clock_low_performance( void )
{
}

void system_clock_sleep( void )
{
}

void system_clock_stop( void )
{
}

void system_clock_standby( void )
{
}
