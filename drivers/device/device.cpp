#include "device.hpp"
#include <string.h>

DEVICE::DEVICE( void )
{
    memset( this->name, '\0', sizeof( this->name ) );
    state = DEVICE::state_t::UNINIT;
}

DEVICE::~DEVICE( void )
{
}

DEVICE::state_t DEVICE::get_state( void )
{
    return state;
}