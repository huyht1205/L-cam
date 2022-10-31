#include "PMIC.hpp"

PMIC::PMIC( void )
{
}

PMIC::~PMIC( void )
{
}

int PMIC::init( void )
{
    return 0;
}

int PMIC::deinit( void )
{
    return 0;
}

int PMIC::on( void )
{
    return 0;
}

int PMIC::off( void )
{
    return 0;
}

int PMIC::sleep( void )
{
    return 0;
}

DeviceState PMIC::get_state( void )
{
    return DeviceState::UNINIT;
}

PMIC *PMIC::get_instance( void )
{
    return nullptr;
}