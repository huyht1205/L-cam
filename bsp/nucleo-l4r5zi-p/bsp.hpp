/**
 * @file bsp.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __BSP_HPP__
#define __BSP_HPP__

#include "i2c.hpp"
#include "gpio.hpp"
#include "led.hpp"
#include "apds_9960.hpp"
#include "bsp_system_clock.hpp"
#include "system_clock.hpp"

namespace BSP
{
extern LED_RGB_GPIO led;
extern APDS_9960 apds_9960;
extern OS::event_id_t device_interrupt_evt;
extern SYSTEM_CLOCK system_clock;

const uint32_t EVT_FLAG_ALL_DEVICE_IRQ = 0x0000FFFF;
const uint32_t EVT_FLAG_APDS_9960_IRQ  = ( 1U << 0 );

void init( void );
void init_buses( void );
void init_peripherals( void );
}; // namespace BSP

#endif // __BSP_HPP__