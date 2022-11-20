#include "bus.hpp"

BUS::BUS( void )
{
}

BUS::~BUS( void )
{
}

int BUS::enable_dma( OS::event_attr_t *dma_event_config )
{
    this->dma_event = OS::event_new( NULL );

    return 0;
}

int BUS::init( void )
{
    return 0;
}

int BUS::deinit( void )
{
    return 0;
}
int BUS::read( void *data,
               const uint32_t data_len,
               const uint32_t timeout,
               const uint16_t device_addr,
               const uint16_t mem_addr,
               const uint16_t mem_addr_size )
{
    return io_access( io_direction_t::READ,
                      false,
                      data,
                      data_len,
                      timeout,
                      device_addr,
                      mem_addr,
                      mem_addr_size );
}

int BUS::write( void *data,
                const uint32_t data_len,
                const uint32_t timeout,
                const uint16_t device_addr,
                const uint16_t mem_addr,
                const uint16_t mem_addr_size )
{
    return io_access( io_direction_t::WRITE,
                      false,
                      data,
                      data_len,
                      timeout,
                      device_addr,
                      mem_addr,
                      mem_addr_size );
}

int BUS::read_dma( void *data,
                   const uint32_t data_len,
                   const uint32_t timeout,
                   const uint16_t device_addr,
                   const uint16_t mem_addr,
                   const uint16_t mem_addr_size )
{
    return io_access( io_direction_t::READ,
                      true,
                      data,
                      data_len,
                      timeout,
                      device_addr,
                      mem_addr,
                      mem_addr_size );
}

int BUS::write_dma( void *data,
                    const uint32_t data_len,
                    const uint32_t timeout,
                    const uint16_t device_addr,
                    const uint16_t mem_addr,
                    const uint16_t mem_addr_size )
{
    return io_access( io_direction_t::WRITE,
                      true,
                      data,
                      data_len,
                      timeout,
                      device_addr,
                      mem_addr,
                      mem_addr_size );
}

void BUS::dma_interrupt_cb( dma_cb_type type )
{
    switch ( type )
    {
    case dma_cb_type::DMA_COMPLETE_WRITE_HALF:
        break;
    case dma_cb_type::DMA_COMPLETE_READ_HALF:
        break;
    case dma_cb_type::DMA_COMPLETE_WRITE_FULL:
        break;
    case dma_cb_type::DMA_COMPLETE_READ_FULL:
        break;
    }
}

int BUS::io_access( const io_direction_t direction,
                    const bool dma_enabled,
                    void *data,
                    const uint32_t data_len,
                    const uint32_t timeout,
                    const uint16_t device_addr,
                    const uint16_t mem_addr,
                    const uint16_t mem_addr_size )
{
    int e                     = 0;
    int eventMask             = 0;
    uint32_t begin            = 0;
    uint32_t remainingTimeout = timeout;

    begin = OS::get_tick();

    e = OS::mutex_acquire( this->mutex, timeout );
    if ( e != 0 )
    {
        return e;
    }

    remainingTimeout -= OS::get_tick() - begin;

    if ( true == dma_enabled )
    {
        if ( io_direction_t::READ == direction )
        {
            eventMask =
                static_cast<int>( dma_cb_type::DMA_COMPLETE_READ_FULL ) |
                static_cast<int>( dma_cb_type::DMA_COMPLETE_READ_HALF );
        }
        else
        {
            eventMask =
                static_cast<int>( dma_cb_type::DMA_COMPLETE_WRITE_FULL ) |
                static_cast<int>( dma_cb_type::DMA_COMPLETE_WRITE_HALF );
        }

        e = OS::event_clear( this->dma_event, eventMask );
        if ( e != 0 )
        {
            return e;
        }
    }

    if ( io_direction_t::READ == direction )
    {
        if ( true == dma_enabled )
        {
            e = this->hal_read_dma(
                data, data_len, device_addr, mem_addr, mem_addr_size );
        }
        else
        {
            e = this->hal_read( data,
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
            e = this->hal_write_dma(
                data, data_len, device_addr, mem_addr, mem_addr_size );
        }
        else
        {
            e = this->hal_write( data,
                                 data_len,
                                 remainingTimeout,
                                 device_addr,
                                 mem_addr,
                                 mem_addr_size );
        }
    }

    if ( true == dma_enabled )
    {
        e = OS::event_wait( this->dma_event, eventMask, 0, timeout );
        if ( e != 0 )
        {
            return e;
        }
    }

    OS::mutex_release( this->mutex );

    return e;
}