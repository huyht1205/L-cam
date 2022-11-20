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

namespace BSP
{
extern LED_RGB_GPIO led;
extern APDS_9960 apds_9960;

void init( void );
}; // namespace BSP

#endif // __BSP_HPP__