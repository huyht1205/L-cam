/**
 * @file bus_with_addr.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "bus_with_addr.hpp"
#include "error.hpp"

int BUS_WITH_ADDRESS::io_access( const io_direction_t direction,
                                 const bool dma_enabled,
                                 void *data,
                                 const uint32_t data_len,
                                 const uint32_t timeout,
                                 const uint16_t device_addr,
                                 const uint16_t mem_addr,
                                 const uint16_t mem_addr_size )
{
    int e                     = 0;
    int nbyte                 = 0;
    uint32_t eventMask        = 0;
    uint32_t remainingTimeout = timeout;
    uint32_t timestamp        = OS::get_tick();

    e = OS::mutex_acquire( this->mutex, timeout );
    if ( e != NO_ERROR )
    {
        return e;
    }

    remainingTimeout -= OS::get_tick() - timestamp;
    timestamp = OS::get_tick();

    if ( true == dma_enabled )
    {
        e = clear_dma_event( direction, &eventMask );
        if ( e != NO_ERROR )
        {
            return e;
        }
    }

    if ( io_direction_t::READ == direction )
    {
        if ( true == dma_enabled )
        {
            e = hal_read_dma( static_cast<uint8_t *>( data ),
                              data_len,
                              device_addr,
                              mem_addr,
                              mem_addr_size );
        }
        else
        {
            e = hal_read( static_cast<uint8_t *>( data ),
                          data_len,
                          remainingTimeout,
                          device_addr,
                          mem_addr,
                          mem_addr_size );
        }
    }
    else
    {
        if ( true == dma_enabled )
        {
            e = hal_write_dma( static_cast<uint8_t *>( data ),
                               data_len,
                               device_addr,
                               mem_addr,
                               mem_addr_size );
        }
        else
        {
            e = hal_write( static_cast<uint8_t *>( data ),
                           data_len,
                           remainingTimeout,
                           device_addr,
                           mem_addr,
                           mem_addr_size );
        }
    }

    if ( e == NO_ERROR )
    {
        nbyte = data_len;
    }
    else
    {
        nbyte = e;
    }

    remainingTimeout -= OS::get_tick() - timestamp;
    timestamp = OS::get_tick();

    if ( true == dma_enabled )
    {
        e = OS::event_wait( this->dma_event,
                            eventMask,
                            OS::event_flag_option_t::wait_any,
                            remainingTimeout );
        if ( e != NO_ERROR )
        {
            return e;
        }
    }

    OS::mutex_release( this->mutex );

    return nbyte;
}