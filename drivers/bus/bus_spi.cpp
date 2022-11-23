/**
 * @file bus_spi.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "bus_spi.hpp"

int BUS::SPI::read( void *data,
                    const uint32_t data_len,
                    const uint32_t timeout )
{
    return io_access(
        BUS::io_direction_t::READ, false, nullptr, data, data_len, timeout );
}

int BUS::SPI::write( void *data,
                     const uint32_t data_len,
                     const uint32_t timeout )
{
    return io_access(
        BUS::io_direction_t::WRITE, false, data, nullptr, data_len, timeout );
}

int BUS::SPI::read_write( void *tx_data,
                          void *rx_buff,
                          const uint32_t data_len,
                          const uint32_t timeout )
{
    return io_access( BUS::io_direction_t::READ_WRITE,
                      false,
                      tx_data,
                      rx_buff,
                      data_len,
                      timeout );
}

int BUS::SPI::read_dma( void *data,
                        const uint32_t data_len,
                        const uint32_t timeout )
{
    return io_access(
        BUS::io_direction_t::READ, true, nullptr, data, data_len, timeout );
}

int BUS::SPI::write_dma( void *data,
                         const uint32_t data_len,
                         const uint32_t timeout )
{
    return io_access(
        BUS::io_direction_t::WRITE, true, data, nullptr, data_len, timeout );
}

int BUS::SPI::read_write_dma( void *tx_data,
                              void *rx_buff,
                              const uint32_t data_len,
                              const uint32_t timeout )
{
    return io_access( BUS::io_direction_t::READ_WRITE,
                      true,
                      tx_data,
                      rx_buff,
                      data_len,
                      timeout );
}