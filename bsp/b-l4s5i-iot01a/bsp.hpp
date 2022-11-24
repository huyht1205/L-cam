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

#include "gpio.hpp"
#include "led.hpp"
#include "os.hpp"
#include "bsp_system_clock.hpp"
#include "system_clock.hpp"

namespace BSP
{
extern OS::event_id_t device_interrupt_evt;
extern SYSTEM_CLOCK system_clock;

const uint32_t EVT_FLAG_ALL_DEVICE_IRQ = 0x0000FFFF;

void init( void );
void init_peripherals( void );
}; // namespace BSP

#endif // __BSP_HPP__