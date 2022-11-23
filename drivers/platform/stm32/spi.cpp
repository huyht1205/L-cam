/**
 * @file spi.cpp
 * @author Hoang Trung Huy (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "spi.hpp"
#include "error.hpp"

/*** STM32 HAL ***/
#if defined( STM32L4 )
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_conf.h"
#elif defined( STM32H7 )
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_conf.h"
#endif

#ifdef HAL_SPI_MODULE_ENABLED
#define SPI_HANDLER( __h ) static_cast<SPI_HandleTypeDef *>( __h )

int SPI::deinit( void )
{
    return -HAL_SPI_DeInit( SPI_HANDLER( this->handler ) );
}

int SPI::io_access( const BUS::io_direction_t direction,
                    const bool dma_enabled,
                    void *tx_data,
                    void *rx_buff,
                    const uint32_t data_len,
                    const uint32_t timeout )

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
            hal_e = HAL_SPI_Receive_DMA( SPI_HANDLER( handler ),
                                         static_cast<uint8_t *>( rx_buff ),
                                         data_len );
        }
        else
        {
            hal_e = HAL_SPI_Receive( SPI_HANDLER( handler ),
                                     static_cast<uint8_t *>( rx_buff ),
                                     data_len,
                                     remainingTimeout );
        }
    }
    else if ( BUS::io_direction_t::WRITE == direction )
    {
        if ( true == dma_enabled )
        {
            hal_e = HAL_SPI_Transmit_DMA( SPI_HANDLER( handler ),
                                          static_cast<uint8_t *>( tx_data ),
                                          data_len );
        }
        else
        {
            hal_e = HAL_SPI_Transmit( SPI_HANDLER( handler ),
                                      static_cast<uint8_t *>( tx_data ),
                                      data_len,
                                      remainingTimeout );
        }
    }
    else
    {
        if ( true == dma_enabled )
        {
            hal_e =
                HAL_SPI_TransmitReceive_DMA( SPI_HANDLER( handler ),
                                             static_cast<uint8_t *>( tx_data ),
                                             static_cast<uint8_t *>( rx_buff ),
                                             data_len );
        }
        else
        {
            hal_e = HAL_SPI_TransmitReceive( SPI_HANDLER( handler ),
                                             static_cast<uint8_t *>( tx_data ),
                                             static_cast<uint8_t *>( rx_buff ),
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
#endif // HAL_SPI_MODULE_ENABLED
