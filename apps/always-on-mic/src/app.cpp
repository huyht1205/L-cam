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

int main( void )
{
    BSP::init();
    OS::init_kernel();

    /* Start scheduler */
    // OS::start_kernel();

    while ( 1 )
    {
        BSP::led.toggle( LED_RGB::color_t::RED );

        HAL_Delay( 1000 );
    }
}
