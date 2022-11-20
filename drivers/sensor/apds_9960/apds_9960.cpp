/**
 * @file apds_9960.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "apds_9960.hpp"

APDS_9960::APDS_9960( I2C *bus, GPIO *interrupt_pin, uint8_t addr )
{
    this->bus       = bus;
    this->addr      = addr;
    this->interrupt = interrupt_pin;

    snprintf( this->name, sizeof( name ), "APDS_9960" );
}

APDS_9960::~APDS_9960()
{
}

int APDS_9960::init( void )
{
    this->state = DeviceState::READY;
    return 0;
}

int APDS_9960::deinit( void )
{
    this->state = DeviceState::UNINIT;
    return 0;
}

int APDS_9960::on( void )
{
    this->state = DeviceState::ON;
    return 0;
}

int APDS_9960::off( void )
{
    this->state = DeviceState::OFF;
    return 0;
}

int APDS_9960::sleep( void )
{
    this->state = DeviceState::SLEEP;
    return 0;
}
