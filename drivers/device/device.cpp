#include "device.hpp"
#include <string.h>

Device::Device( void )
{
    memset( this->name, '\0', sizeof( this->name ) );
}

Device::~Device( void )
{
}

int Device::init( void )
{
    return 0;
}

int Device::deinit( void )
{
    return 0;
}
int Device::on( void )
{
    return 0;
}
int Device::off( void )
{
    return 0;
}
int Device::sleep( void )
{
    return 0;
}

DeviceState Device::get_state( void )
{
    return DeviceState::UNINIT;
}