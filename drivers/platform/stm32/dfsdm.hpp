/**
 * @file spi.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __SPI_HPP__
#define __SPI_HPP__

#include <stdint.h>

#include "bus_without_addr.hpp"

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

class SPI : public BUS_WITHOUT_ADDRESS
{
  public:
    SPI( void *handler, BUS::platform_init_fPtr init_fPtr )
        : BUS_WITHOUT_ADDRESS( handler, init_fPtr )
    {
    }

    ~SPI( void ) override
    {
    }

    int deinit( void ) override
    {
        return -HAL_SPI_DeInit( SPI_HANDLER( handler ) );
    }

  private:
    int hal_read( void *data,
                  const uint32_t data_len,
                  const uint32_t timeout ) override
    {
        return -HAL_SPI_Receive( SPI_HANDLER( handler ),
                                 static_cast<uint8_t *>( data ),
                                 data_len,
                                 timeout );
    }

    int hal_write( void *data,
                   const uint32_t data_len,
                   const uint32_t timeout ) override
    {
        return -HAL_SPI_Transmit( SPI_HANDLER( handler ),
                                  static_cast<uint8_t *>( data ),
                                  data_len,
                                  timeout );
    }

    int hal_read_write( void *tx_data,
                        void *rx_buff,
                        const uint32_t data_len,
                        const uint32_t timeout ) override
    {
        return -HAL_SPI_TransmitReceive( SPI_HANDLER( handler ),
                                         static_cast<uint8_t *>( tx_data ),
                                         static_cast<uint8_t *>( rx_buff ),
                                         data_len,
                                         timeout );
    }

    int hal_read_dma( void *data, const uint32_t data_len ) override
    {
        return -HAL_SPI_Receive_DMA(
            SPI_HANDLER( handler ), static_cast<uint8_t *>( data ), data_len );
    }

    int hal_write_dma( void *data, const uint32_t data_len ) override
    {
        return -HAL_SPI_Transmit_DMA(
            SPI_HANDLER( handler ), static_cast<uint8_t *>( data ), data_len );
    }

    int hal_read_write_dma( void *tx_data,
                            void *rx_buff,
                            const uint32_t data_len ) override
    {
        return -HAL_SPI_TransmitReceive_DMA( SPI_HANDLER( handler ),
                                             static_cast<uint8_t *>( tx_data ),
                                             static_cast<uint8_t *>( rx_buff ),
                                             data_len );
    }
};

#endif // HAL_SPI_MODULE_ENABLED
#endif // __SPI_HPP__