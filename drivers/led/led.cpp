/**
 * @file led.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "led.hpp"

const LED_RGB_GPIO::rgb_code_t RGB_GPIO_TABLE [] = {
    { 1, 0, 0 },
    { 0, 1, 0 },
    { 0, 0, 1 },
};

LED_GPIO::LED_GPIO( GPIO *gpio, bool active_low )
{
    this->gpio       = gpio;
    this->active_low = active_low;
}

LED_GPIO::~LED_GPIO( void )
{
}

void LED_GPIO::on( void )
{
    GPIO::state_t state =
        this->active_low ? GPIO::state_t::RESET : GPIO::state_t::SET;

    this->gpio->write( state );
}

void LED_GPIO::off( void )
{
    GPIO::state_t state =
        this->active_low ? GPIO::state_t::SET : GPIO::state_t::RESET;

    this->gpio->write( state );
}

void LED_GPIO::toggle( void )
{
    this->gpio->toggle();
}

LED_RGB_GPIO::LED_RGB_GPIO( GPIO *red,
                            GPIO *green,
                            GPIO *blue,
                            bool active_low )
{
    this->red        = red;
    this->green      = green;
    this->blue       = blue;
    this->active_low = active_low;
    this->state      = LED_RGB::state_t::OFF;
}

LED_RGB_GPIO::~LED_RGB_GPIO( void )
{
}

void LED_RGB_GPIO::on( void )
{
    on( this->color );
    this->state = LED_RGB::state_t::ON;
}

void LED_RGB_GPIO::off( void )
{
    GPIO::state_t state =
        this->active_low ? GPIO::state_t::SET : GPIO::state_t::RESET;

    this->red->write( state );
    this->green->write( state );
    this->blue->write( state );

    this->state = LED_RGB::state_t::OFF;
}

void LED_RGB_GPIO::toggle( void )
{
    toggle( this->color );
}

void LED_RGB_GPIO::on( color_t color )
{
    rgb_code_t code = RGB_GPIO_TABLE [ static_cast<int>( color ) ];
    GPIO::state_t stateR;
    GPIO::state_t stateG;
    GPIO::state_t stateB;

    if ( active_low )
    {
        stateR = code.red ? GPIO::state_t::RESET : GPIO::state_t::SET;
        stateG = code.gree ? GPIO::state_t::RESET : GPIO::state_t::SET;
        stateB = code.blue ? GPIO::state_t::RESET : GPIO::state_t::SET;
    }
    else
    {
        stateR = code.red ? GPIO::state_t::SET : GPIO::state_t::RESET;
        stateG = code.gree ? GPIO::state_t::SET : GPIO::state_t::RESET;
        stateB = code.blue ? GPIO::state_t::SET : GPIO::state_t::RESET;
    }

    this->red->write( stateR );
    this->green->write( stateG );
    this->blue->write( stateB );
    this->color = color;
    this->state = LED_RGB::state_t::ON;
}

void LED_RGB_GPIO::toggle( LED_RGB::color_t color )
{
    this->color = color;
    if ( this->state == LED_RGB::state_t::ON )
    {
        off();
    }
    else
    {
        on( this->color );
    }
}
