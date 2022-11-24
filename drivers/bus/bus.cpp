/**
 * @file bus.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "bus.hpp"
#include "error.hpp"

BUS::BUS( void *handler, platform_init_fPtr init_fPtr )
{
    this->handler       = handler;
    this->platform_init = init_fPtr;

    this->mutex     = OS::mutex_new( nullptr );
    this->dma_event = OS::event_new( NULL );
}

int BUS::BUS::init( void )
{
    this->platform_init();

    return NO_ERROR;
}

int BUS::BUS::deinit( void )
{
    return NO_ERROR;
}

void BUS::BUS::dma_interrupt_callback( dma_cb_type type )
{
    OS::event_set( dma_event, static_cast<uint32_t>( type ) );
}

int BUS::BUS::clear_dma_event( io_direction_t direction, uint32_t *mask )
{
    if ( ( static_cast<uint32_t>( io_direction_t::READ ) &
           static_cast<uint32_t>( direction ) ) != 0 )
    {
        *mask |= static_cast<int>( dma_cb_type::DMA_COMPLETE_READ_FULL ) |
                 static_cast<int>( dma_cb_type::DMA_COMPLETE_READ_HALF );
    }

    if ( ( static_cast<uint32_t>( io_direction_t::WRITE ) &
           static_cast<uint32_t>( direction ) ) != 0 )
    {
        *mask |= static_cast<int>( dma_cb_type::DMA_COMPLETE_WRITE_FULL ) |
                 static_cast<int>( dma_cb_type::DMA_COMPLETE_WRITE_HALF );
    }

    return OS::event_clear( this->dma_event, *mask );
}
