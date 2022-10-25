#include "app.hpp"
#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"
#include "usart.h"
#include "jpeg.h"
#include "rtc.h"
#include "system_clock.hpp"

int main( void )
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* Enable I-Cache---------------------------------------------------------*/
    SCB_EnableICache();

    /* Enable D-Cache---------------------------------------------------------*/
    SCB_EnableDCache();

    /* MCU
     * Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the
     * Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock *sysClk = SystemClock::get_instance();
    sysClk->set_speed( SystemClockSpeed::FULL_SPEED );

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART3_UART_Init();
    MX_JPEG_Init();
    MX_RTC_Init();

    /* Init scheduler */
    osKernelInitialize(); /* Call init function for freertos objects (in
                             freertos.c) */

    /* Start scheduler */
    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */
    /* Infinite loop */
    while ( 1 )
    {
    }
}