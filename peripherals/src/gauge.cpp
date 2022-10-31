#include "gauge.hpp"

GAUGE::GAUGE( void )
{
}

GAUGE::~GAUGE( void )
{
}

int GAUGE::init( void )
{
    return 0;
}

int GAUGE::deinit( void )
{
    return 0;
}

int GAUGE::on( void )
{
    return 0;
}

int GAUGE::off( void )
{
    return 0;
}

int GAUGE::sleep( void )
{
    return 0;
}

DeviceState GAUGE::get_state( void )
{
    return DeviceState::UNINIT;
}

GAUGE *GAUGE::get_instance( void )
{
    return nullptr;
}