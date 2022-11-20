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
#include "bsp.hpp"
#include "os.hpp"

static void _test_app( void * );
static void _sensor_handler( void * );

int main( void )
{
    BSP::init();
    OS::init_kernel();
    BSP::init_buses();
    BSP::init_peripherals();

    const OS::thread_attr_t attr1 = {
        .name       = "test",
        .stack_size = 1024,
        .priority   = osPriorityNormal,
    };

    const OS::thread_attr_t attr2 = {
        .name       = "sensor_handler",
        .stack_size = 1024,
        .priority   = osPriorityNormal1,
    };

    OS::thread_new( &_test_app, nullptr, &attr1 );
    OS::thread_new( &_sensor_handler, nullptr, &attr2 );

    /* Start scheduler */
    OS::start_kernel();

    while ( 1 )
    {
    }
}

static void _test_app( void * )
{
    int e = 0;

    BSP::apds_9960.select_feature( static_cast<APDS_9960::feature_t>(
        APDS_9960::feature_t::als | APDS_9960::feature_t::als_interrupt ) );
    BSP::apds_9960.register_global_event_handler( BSP::device_interrupt_evt,
                                                  BSP::EVT_FLAG_APDS_9960_IRQ );
    e = BSP::apds_9960.off();
    if ( e != NO_ERROR )
    {
        Error_Handler();
    }

    e = BSP::apds_9960.on();
    if ( e != NO_ERROR )
    {
        Error_Handler();
    }

    for ( ;; )
    {
        BSP::led.toggle( LED_RGB::color_t::GREEN );
        OS::delay( 1000 );
    }
}

static void _sensor_handler( void * )
{
    OS::event_clear( BSP::device_interrupt_evt, BSP::EVT_FLAG_ALL_DEVICE_IRQ );
    for ( ;; )
    {
        uint32_t flag = OS::event_wait( BSP::device_interrupt_evt,
                                        BSP::EVT_FLAG_ALL_DEVICE_IRQ,
                                        osFlagsWaitAny,
                                        osWaitForever );

        switch ( flag )
        {
        case BSP::EVT_FLAG_APDS_9960_IRQ:
            BSP::apds_9960.handle_measured_data_upon_interrupt();
            break;
        }
    }
}