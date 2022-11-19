/**
 * @file app.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "app.hpp"
#include "main.h"
#include "cmsis_os.h"
#include "crc.h"
#include "dma.h"
#include "usart.h"
#include "rng.h"
#include "rtc.h"
#include "gpio.h"

void SystemClock_Config( void );

int main( void )
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU
     * Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the
     * Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_LPUART1_UART_Init();
    MX_CRC_Init();
    MX_RNG_Init();
    MX_RTC_Init();
    /* USER CODE BEGIN 2 */

    /* USER CODE END 2 */

    /* Init scheduler */
    osKernelInitialize(); /* Call init function for freertos objects (in
                             freertos.c) */

    /* Start scheduler */
    // osKernelStart();

    /* We should never get here as control is now taken by the scheduler */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while ( 1 )
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        HAL_GPIO_TogglePin( LD3_GPIO_Port, LD3_Pin );
        HAL_GPIO_TogglePin( LD2_GPIO_Port, LD2_Pin );
        HAL_GPIO_TogglePin( LD1_GPIO_Port, LD1_Pin );
        HAL_Delay( 1000 );
    }
    /* USER CODE END 3 */
}

void SystemClock_Config( void )
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

    /** Configure LSE Drive Capability
     */
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG( RCC_LSEDRIVE_LOW );

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType =
        RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.LSEState            = RCC_LSE_ON;
    RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM            = 4;
    RCC_OscInitStruct.PLL.PLLN            = 60;
    RCC_OscInitStruct.PLL.PLLP            = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ            = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR            = RCC_PLLR_DIV2;
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

    /** Enables the Clock Security System
     */
    HAL_RCCEx_EnableLSECSS();
}