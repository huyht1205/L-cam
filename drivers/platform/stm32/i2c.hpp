#ifndef __I2C_HPP__
#define __I2C_HPP__

#include <stdint.h>

#include "bus_with_addr.hpp"

/*** STM32 HAL ***/
#if defined( STM32L4 )
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_conf.h"
#elif defined( STM32H7 )
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_conf.h"
#endif

#ifdef HAL_I2C_MODULE_ENABLED
#define I2C_HANDLER( __h ) static_cast<I2C_HandleTypeDef *>( __h )

class I2C : public BUS_WITH_ADDRESS
{
  public:
    I2C( void *handler, BUS::platform_init_fPtr init_fPtr )
        : BUS_WITH_ADDRESS( handler, init_fPtr )
    {
    }
    ~I2C( void ) override
    {
    }

    int deinit( void ) override
    {
        return -HAL_I2C_DeInit( I2C_HANDLER( handler ) );
    }

  private:
    int hal_read( void *data,
                  const uint32_t data_len,
                  const uint32_t timeout,
                  const uint16_t device_addr,
                  const uint16_t mem_addr,
                  const uint16_t mem_addr_size ) override
    {
        return -HAL_I2C_Mem_Read( I2C_HANDLER( handler ),
                                  device_addr,
                                  mem_addr,
                                  mem_addr_size,
                                  static_cast<uint8_t *>( data ),
                                  data_len,
                                  timeout );
    }

    int hal_write( void *data,
                   const uint32_t data_len,
                   const uint32_t timeout,
                   const uint16_t device_addr,
                   const uint16_t mem_addr,
                   const uint16_t mem_addr_size ) override
    {
        return -HAL_I2C_Mem_Write( I2C_HANDLER( handler ),
                                   device_addr,
                                   mem_addr,
                                   mem_addr_size,
                                   static_cast<uint8_t *>( data ),
                                   data_len,
                                   timeout );
    }

    int hal_read_dma( void *data,
                      const uint32_t data_len,
                      const uint16_t device_addr,
                      const uint16_t mem_addr,
                      const uint16_t mem_addr_size ) override
    {
        return -HAL_I2C_Mem_Read_DMA( I2C_HANDLER( handler ),
                                      device_addr,
                                      mem_addr,
                                      mem_addr_size,
                                      static_cast<uint8_t *>( data ),
                                      data_len );
    }

    int hal_write_dma( void *data,
                       const uint32_t data_len,
                       const uint16_t device_addr,
                       const uint16_t mem_addr,
                       const uint16_t mem_addr_size ) override
    {
        return -HAL_I2C_Mem_Write_DMA( I2C_HANDLER( handler ),
                                       device_addr,
                                       mem_addr,
                                       mem_addr_size,
                                       static_cast<uint8_t *>( data ),
                                       data_len );
    }
};

#endif // HAL_I2C_MODULE_ENABLED
#endif // __I2C_HPP__