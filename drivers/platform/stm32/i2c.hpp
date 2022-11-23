#ifndef __I2C_HPP__
#define __I2C_HPP__

#include <stdint.h>

#include "bus_i2c.hpp"

class I2C : public BUS::I2C
{
  public:
    I2C( void *handler, BUS::platform_init_fPtr init_fPtr )
        : BUS::I2C::I2C( handler, init_fPtr )
    {
    }
    ~I2C( void ) override
    {
    }

    int deinit( void ) override;

  private:
    int io_access( const BUS::io_direction_t direction,
                   const bool dma_enabled,
                   void *data,
                   const uint32_t data_len,
                   const uint32_t timeout,
                   const uint16_t device_addr,
                   const uint16_t mem_addr,
                   const uint16_t mem_addr_size ) override;
};

#endif // __I2C_HPP__