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

#include <stdint.h>

#include "error.hpp"
#include "i2c.hpp"
#include "os.hpp"

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

int I2C::deinit( void )
{
    return -HAL_I2C_DeInit( I2C_HANDLER( this->handler ) );
}

int I2C::io_access( const BUS::io_direction_t direction,
                    const bool dma_enabled,
                    void *data,
                    const uint32_t data_len,
                    const uint32_t timeout,
                    const uint16_t device_addr,
                    const uint16_t mem_addr,
                    const uint16_t mem_addr_size )
{
    int e                     = 0;
    HAL_StatusTypeDef hal_e   = HAL_ERROR;
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

    if ( BUS::io_direction_t::READ == direction )
    {
        if ( true == dma_enabled )
        {
            hal_e = HAL_I2C_Mem_Read_DMA( I2C_HANDLER( handler ),
                                          device_addr,
                                          mem_addr,
                                          mem_addr_size,
                                          static_cast<uint8_t *>( data ),
                                          data_len );
        }
        else
        {
            hal_e = HAL_I2C_Mem_Read( I2C_HANDLER( handler ),
                                      device_addr,
                                      mem_addr,
                                      mem_addr_size,
                                      static_cast<uint8_t *>( data ),
                                      data_len,
                                      remainingTimeout );
        }
    }
    else
    {
        if ( true == dma_enabled )
        {
            hal_e = HAL_I2C_Mem_Write_DMA( I2C_HANDLER( handler ),
                                           device_addr,
                                           mem_addr,
                                           mem_addr_size,
                                           static_cast<uint8_t *>( data ),
                                           data_len );
        }
        else
        {
            hal_e = HAL_I2C_Mem_Write( I2C_HANDLER( handler ),
                                       device_addr,
                                       mem_addr,
                                       mem_addr_size,
                                       static_cast<uint8_t *>( data ),
                                       data_len,
                                       remainingTimeout );
        }
    }

    if ( hal_e == HAL_OK )
    {
        nbyte = e;
    }
    else
    {
        nbyte = -hal_e;
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

#endif // HAL_I2C_MODULE_ENABLED