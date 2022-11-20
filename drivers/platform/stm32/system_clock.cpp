/**
 * @file system_clock.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdlib.h>
#include <string.h>
#include "system_clock.hpp"

SYSTEM_CLOCK::SYSTEM_CLOCK( system_clock_config_t *config )
{
    memcpy( this->profile_config_functions,
            config->profile_config_functions,
            sizeof( config->profile_config_functions ) );
}

SYSTEM_CLOCK::~SYSTEM_CLOCK( void )
{
}

void SYSTEM_CLOCK::switch_profile( clock_profile_t profile )
{
    this->profile_config_functions [ static_cast<int>( profile ) ]();
}