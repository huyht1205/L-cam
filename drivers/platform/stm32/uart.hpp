/**
 * @file uart.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __UART_HPP__
#define __UART_HPP__

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

#ifdef HAL_UART_MODULE_ENABLED
#define UART_HANDLER( __h ) static_cast<UART_HandleTypeDef *>( __h )

class UART : public BUS_WITHOUT_ADDRESS
{
  public:
    UART( void *handler, BUS::platform_init_fPtr init_fPtr )
        : BUS_WITHOUT_ADDRESS( handler, init_fPtr )
    {
    }

    ~UART( void ) override
    {
    }

    int deinit( void ) override
    {
        return -HAL_UART_DeInit( UART_HANDLER( handler ) );
    }

  private:
    int hal_read( void *data,
                  const uint32_t data_len,
                  const uint32_t timeout ) override
    {
        return -HAL_UART_Receive( UART_HANDLER( handler ),
                                  static_cast<uint8_t *>( data ),
                                  data_len,
                                  timeout );
    }

    int hal_write( void *data,
                   const uint32_t data_len,
                   const uint32_t timeout ) override
    {
        return -HAL_UART_Transmit( UART_HANDLER( handler ),
                                   static_cast<uint8_t *>( data ),
                                   data_len,
                                   timeout );
    }

    int hal_read_dma( void *data, const uint32_t data_len ) override
    {
        return -HAL_UART_Receive_DMA(
            UART_HANDLER( handler ), static_cast<uint8_t *>( data ), data_len );
    }

    int hal_write_dma( void *data, const uint32_t data_len ) override
    {
        return -HAL_UART_Transmit_DMA(
            UART_HANDLER( handler ), static_cast<uint8_t *>( data ), data_len );
    }
};

#endif // HAL_UART_MODULE_ENABLED
#endif // __UART_HPP__