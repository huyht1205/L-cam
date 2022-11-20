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

#include "bsp.hpp"
#include "main.h"
#include "cmsis_os.h"
#include "crc.h"
#include "dma.h"
#include "usart.h"
#include "rng.h"
#include "rtc.h"
#include "gpio.h"
#include "gpio.hpp"
#include "i2c.h"

/*** GPIO ***/
static GPIO led_g = GPIO( GPIO::port_t::C, GPIO::pin_t::PIN_7 );
static GPIO led_b = GPIO( GPIO::port_t::B, GPIO::pin_t::PIN_7 );
static GPIO led_r = GPIO( GPIO::port_t::B, GPIO::pin_t::PIN_14 );

LED_RGB_GPIO BSP::led = LED_RGB_GPIO( &led_r, &led_g, &led_b, false );

static void _gpio_init( void );

/*** I2C ***/
static I2C i2c1 = I2C( static_cast<void *>( &hi2c1 ), &MX_I2C1_Init );
static void _i2c_init( void );

/*** DEVICES ***/
APDS_9960 BSP::apds_9960( &i2c1, nullptr );
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

    MX_DMA_Init();
    MX_LPUART1_UART_Init();
    MX_CRC_Init();
    MX_RNG_Init();
    MX_RTC_Init();
}

void BSP::init_buses( void )
{
    _gpio_init();
    _i2c_init();
}

void BSP::init_peripherals( void )
{
    device_interrupt_evt = OS::event_new( nullptr );

    apds_9960.init();
    HAL_NVIC_EnableIRQ( EXTI0_IRQn );
}

static void _gpio_init( void )
{
    MX_GPIO_Init();

    led_b.init( GPIO::mode_t::GPIO_OUTPUT_PP, GPIO::speed_t::LOW );
    led_g.init( GPIO::mode_t::GPIO_OUTPUT_PP, GPIO::speed_t::LOW );
    led_r.init( GPIO::mode_t::GPIO_OUTPUT_PP, GPIO::speed_t::LOW );
}

static void _i2c_init( void )
{
    i2c1.init();
}