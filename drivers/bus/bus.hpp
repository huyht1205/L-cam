#ifndef __BUS_HPP__
#define __BUS_HPP__

#include <stdint.h>
#include "OS.hpp"

namespace BUS
{
typedef void ( *platform_init_fPtr )( void );
enum class dma_cb_type : int
{
    DMA_COMPLETE_WRITE_FULL = 1 << 0,
    DMA_COMPLETE_READ_FULL  = 1 << 1,

    DMA_COMPLETE_WRITE_HALF = 1 << 2,
    DMA_COMPLETE_READ_HALF  = 1 << 3,
};

enum class io_direction_t : uint8_t
{
    READ       = 1,
    WRITE      = 2,
    READ_WRITE = READ | WRITE,
};

class BUS_BASE
{
  public:
    virtual int init( void );
    virtual int deinit( void ) = 0;

    /**
     * @brief Call this API in the interrupt routine
     *
     * @param type [IN] type of DMA interrupt (full/half, read/write)
     */
    virtual void dma_interrupt_callback( BUS::dma_cb_type type );

  protected:
    BUS_BASE( void *handler, BUS::platform_init_fPtr init_fPtr );
    BUS_BASE( void )
    {
    }
    virtual ~BUS_BASE( void )
    {
    }

    int clear_dma_event( io_direction_t direction, uint32_t *mask );

    void *handler;            /* Device handler from HAL of the platform */
    OS::event_id_t dma_event; /* To synchronize thread with DMA event */
    OS::mutex_id_t mutex;     /* Mutex to be thread-safe */
    BUS::platform_init_fPtr platform_init;
};
}; // namespace BUS

#endif // __BUS_HPP__