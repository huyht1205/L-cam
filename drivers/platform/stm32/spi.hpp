#ifndef __SPI_HPP__
#define __SPI_HPP__

#include <stdint.h>

#include "bus_spi.hpp"

class SPI : public BUS::SPI
{
  public:
    SPI( void *handler, BUS::platform_init_fPtr init_fPtr )
        : BUS::SPI::SPI( handler, init_fPtr )
    {
    }

    ~SPI( void ) override
    {
    }

    int deinit( void ) override;

  private:
    int io_access( const BUS::io_direction_t direction,
                   const bool dma_enabled,
                   void *tx_data,
                   void *rx_buff,
                   const uint32_t data_len,
                   const uint32_t timeout ) override;
};

#endif // __SPI_HPP__