/**
 * @file bsp.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dfsdm.h"
#include "i2c.h"
#include "octospi.h"
#include "rtc.h"
#include "spi.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

#include "os.hpp"
#include "system_clock.hpp"
#include "bsp.hpp"
#include "i2c.hpp"
// #include "spi.hpp"

/*** STM32 INTERFACES ***/
static void _stm32_interface_init( void );

static I2C m_i2c1 = I2C( &hi2c1, &MX_I2C1_Init );
static I2C m_i2c2 = I2C( &hi2c2, &MX_I2C2_Init );

// static SPI m_spi1 = SPI( &hspi1, MX_SPI1_Init );
// static SPI m_spi3 = SPI( &hspi3, MX_SPI3_Init );

/*** DEVICES ***/
OS::event_id_t BSP::device_interrupt_evt;

extern void system_clock_max_performance( void );
extern void system_clock_low_performance( void );
extern void system_clock_sleep( void );
extern void system_clock_stop( void );
extern void system_clock_standby( void );
static const SYSTEM_CLOCK::system_clock_config_t m_system_clock_config = {
    .profile_config_functions =
        {
            &system_clock_max_performance,
            &system_clock_low_performance,
            &system_clock_sleep,
            &system_clock_stop,
            &system_clock_standby,
        },
};
SYSTEM_CLOCK BSP::system_clock = SYSTEM_CLOCK( &m_system_clock_config );

void BSP::init( void )
{
    HAL_Init();
    system_clock.switch_profile(
        SYSTEM_CLOCK::clock_profile_t::MAX_PERFORMANCE );

    MX_SPI1_Init();
    MX_SPI3_Init();
    MX_UART4_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    MX_USART3_UART_Init();
    MX_USB_OTG_FS_USB_Init();
    MX_RTC_Init();
}

void BSP::init_peripherals( void )
{
    _stm32_interface_init();

    device_interrupt_evt = OS::event_new( nullptr );
}

static void _stm32_interface_init( void )
{
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_DFSDM1_Init();
    MX_OCTOSPI1_Init();

    m_i2c1.init();
    m_i2c2.init();
}
