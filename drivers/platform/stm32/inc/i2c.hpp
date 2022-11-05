#ifndef __I2C_HPP__
#define __I2C_HPP__

#include <stdint.h>

#include "bus.hpp"
#include "i2c.h"

class I2C : public Bus
{
  public:
    I2C( void );
    ~I2C( void );

    int init( void ) override;
    int deinit( void ) override;

    int on( void ) override;
    int off( void ) override;

    static I2C *get_instance( char *name );

    int read( void *data,
              const uint32_t data_len,
              const uint32_t timeout_ms ) override;
    int write( void *data,
               const uint32_t data_len,
               const uint32_t timeout_ms ) override;
    int read_dma( void *data,
                  const uint32_t data_len,
                  const uint32_t timeout_ms ) override;
    int write_dma( void *data,
                   const uint32_t data_len,
                   const uint32_t timeout_ms ) override;

  private:
    I2C_HandleTypeDef *handler;
};

#endif // __I2C_HPP__