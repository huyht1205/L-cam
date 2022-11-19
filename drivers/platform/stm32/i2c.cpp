/**
 * @file i2c.cpp
 * @author Hoang Trung Huy (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "i2c.hpp"

/*** STM32 HAL ***/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_conf.h"

#ifdef HAL_I2C_MODULE_ENABLED
#define I2C_HANDLER( __h ) static_cast<I2C_HandleTypeDef *>( __h )

I2C::I2C( void *handler, stm32_cubemx_i2c_init init_fPtr )
{
    this->handler     = handler;
    this->cubemx_init = init_fPtr;
}

I2C::~I2C( void )
{
}

int I2C::init( void )
{
    this->cubemx_init();

    return 0;
}

int I2C::deinit( void )
{
    return HAL_I2C_DeInit( I2C_HANDLER( this->handler ) );
}

int I2C::hal_read( void *data,
                   const uint32_t data_len,
                   const uint32_t timeout,
                   const uint16_t device_addr,
                   const uint16_t mem_addr,
                   const uint16_t mem_addr_size )
{
    int e = 0;

    e = HAL_I2C_Mem_Read( I2C_HANDLER( this->handler ),
                          device_addr,
                          mem_addr,
                          mem_addr_size,
                          static_cast<uint8_t *>( data ),
                          data_len,
                          timeout );

    if ( e != HAL_OK )
    {
        return e;
    }
    else
    {
        return data_len;
    }
}

int I2C::hal_write( void *data,
                    const uint32_t data_len,
                    const uint32_t timeout,
                    const uint16_t device_addr,
                    const uint16_t mem_addr,
                    const uint16_t mem_addr_size )
{
    int e = 0;

    e = HAL_I2C_Mem_Write( I2C_HANDLER( this->handler ),
                           device_addr,
                           mem_addr,
                           mem_addr_size,
                           static_cast<uint8_t *>( data ),
                           data_len,
                           timeout );
    if ( e != HAL_OK )
    {
        return e;
    }
    else
    {
        return data_len;
    }
}

int I2C::hal_read_dma( void *data,
                       const uint32_t data_len,
                       const uint16_t device_addr,
                       const uint16_t mem_addr,
                       const uint16_t mem_addr_size )
{
    int e = 0;

    e = HAL_I2C_Mem_Read_DMA( I2C_HANDLER( this->handler ),
                              device_addr,
                              mem_addr,
                              mem_addr_size,
                              static_cast<uint8_t *>( data ),
                              data_len );
    if ( e != HAL_OK )
    {
        return e;
    }
    else
    {
        return data_len;
    }
}

int I2C::hal_write_dma( void *data,
                        const uint32_t data_len,
                        const uint16_t device_addr,
                        const uint16_t mem_addr,
                        const uint16_t mem_addr_size )
{
    int e = 0;

    e = HAL_I2C_Mem_Write_DMA( I2C_HANDLER( this->handler ),
                               device_addr,
                               mem_addr,
                               mem_addr_size,
                               static_cast<uint8_t *>( data ),
                               data_len );
    if ( e != HAL_OK )
    {
        return e;
    }
    else
    {
        return data_len;
    }
}

#endif // HAL_I2C_MODULE_ENABLED