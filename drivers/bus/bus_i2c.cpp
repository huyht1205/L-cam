/**
 * @file bus_i2c.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "bus_i2c.hpp"

int BUS::I2C::read( void *data,
                    const uint32_t data_len,
                    const uint32_t timeout,
                    const uint16_t device_addr,
                    const uint16_t mem_addr,
                    const uint16_t mem_addr_size )
{
    return io_access( BUS::io_direction_t::READ,
                      false,
                      data,
                      data_len,
                      timeout,
                      device_addr,
                      mem_addr,
                      mem_addr_size );
}

int BUS::I2C::write( void *data,
                     const uint32_t data_len,
                     const uint32_t timeout,
                     const uint16_t device_addr,
                     const uint16_t mem_addr,
                     const uint16_t mem_addr_size )
{
    return io_access( BUS::io_direction_t::WRITE,
                      false,
                      data,
                      data_len,
                      timeout,
                      device_addr,
                      mem_addr,
                      mem_addr_size );
}

int BUS::I2C::read_dma( void *data,
                        const uint32_t data_len,
                        const uint32_t timeout,
                        const uint16_t device_addr,
                        const uint16_t mem_addr,
                        const uint16_t mem_addr_size )
{
    return io_access( BUS::io_direction_t::READ,
                      true,
                      data,
                      data_len,
                      timeout,
                      device_addr,
                      mem_addr,
                      mem_addr_size );
}

int BUS::I2C::write_dma( void *data,
                         const uint32_t data_len,
                         const uint32_t timeout,
                         const uint16_t device_addr,
                         const uint16_t mem_addr,
                         const uint16_t mem_addr_size )
{
    return io_access( BUS::io_direction_t::WRITE,
                      true,
                      data,
                      data_len,
                      timeout,
                      device_addr,
                      mem_addr,
                      mem_addr_size );
}