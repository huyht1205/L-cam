#include "device.hpp"
#include <string.h>

DEVICE::DEVICE( void )
{
    memset( this->name, '\0', sizeof( this->name ) );
    this->state = DeviceState::UNINIT;
}

DEVICE::~DEVICE( void )
{
}

DeviceState DEVICE::get_state( void )
{
    return this->state;
}