#ifndef __I2C_HPP__
#define __I2C_HPP__

#include <stdint.h>

#include "bus.hpp"

typedef void ( *stm32_cubemx_i2c_init )( void );

class I2C : public BUS
{
  public:
    I2C( void *handler, stm32_cubemx_i2c_init init_fPtr );
    ~I2C( void );

    int init( void ) override;
    int deinit( void ) override;

  private:
    void ( *cubemx_init )( void );

  protected:
    int hal_read( void *data,
                  const uint32_t data_len,
                  const uint32_t timeout,
                  const uint16_t device_addr,
                  const uint16_t mem_addr,
                  const uint16_t mem_addr_size ) override;

    int hal_write( void *data,
                   const uint32_t data_len,
                   const uint32_t timeout,
                   const uint16_t device_addr,
                   const uint16_t mem_addr,
                   const uint16_t mem_addr_size ) override;

    int hal_read_dma( void *data,
                      const uint32_t data_len,
                      const uint16_t device_addr,
                      const uint16_t mem_addr,
                      const uint16_t mem_addr_size ) override;

    int hal_write_dma( void *data,
                       const uint32_t data_len,
                       const uint16_t device_addr,
                       const uint16_t mem_addr,
                       const uint16_t mem_addr_size ) override;
};

#endif // __I2C_HPP__