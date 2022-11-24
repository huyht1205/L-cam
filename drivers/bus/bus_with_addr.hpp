/**
 * @file bus_with_addr.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __BUS_WITH_ADDR_HPP__
#define __BUS_WITH_ADDR_HPP__

#include "bus.hpp"

class BUS_WITH_ADDRESS : public BUS
{
  public:
    /**
     * @brief Blocking read data from bus without DMA.
     * This call consumes CPU until finishes.
     *
     * @param data [OUT] pre-allocated buffer to store bus data
     * @param data_len [IN] Length in bytes of pre-allocated buffer
     * @param timeout [IN] Timeout, unit depends on the platform
     * @param device_addr [IN] address of device
     * @param mem_addr [IN] address of register
     * @param mem_addr_size [IN] size of register
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int read( void *data,
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

    /**
     * @brief Blocking write data to bus without DMA.
     * This call consumes CPU until finishes.
     *
     * @param data [IN] Copy content of data buffer to peripheral by CPU.
     * @param data_len [IN] Length in bytes of data buffer.
     * @param timeout [IN] Timeout, unit depends on the platform
     * @param device_addr [IN] address of device
     * @param mem_addr [IN] address of register
     * @param mem_addr_size [IN] size of register
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int write( void *data,
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

    /**
     * @brief Blocking read data from bus with DMA.
     * This call release CPU while waiting for DMA to finish reading.
     *
     * @param data [OUT] pre-allocated buffer to store bus data
     * @param data_len [IN] Length in bytes of pre-allocated buffer
     * @param timeout [IN] Timeout, unit depends on the platform
     * @param device_addr [IN] address of device
     * @param mem_addr [IN] address of register
     * @param mem_addr_size [IN] size of register
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int read_dma( void *data,
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

    /**
     * @brief Blocking write data to bus with DMA.
     * This call releases CPU while writing by DMA.
     *
     * @param data [IN] Copy content of data buffer to peripheral by CPU.
     * @param data_len [IN] Length in bytes of data buffer.
     * @param timeout [IN] Timeout, unit depends on the platform
     * @param device_addr [IN] address of device
     * @param mem_addr [IN] address of register
     * @param mem_addr_size [IN] size of register
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int write_dma( void *data,
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

  protected:
    BUS_WITH_ADDRESS( void *handler, platform_init_fPtr init_fPtr )
        : BUS::BUS( handler, init_fPtr )
    {
    }
    BUS_WITH_ADDRESS( void )
    {
    }
    virtual ~BUS_WITH_ADDRESS( void )
    {
    }

    virtual int io_access( const io_direction_t direction,
                           const bool dma_enabled,
                           void *data,
                           const uint32_t data_len,
                           const uint32_t timeout,
                           const uint16_t device_addr,
                           const uint16_t mem_addr,
                           const uint16_t mem_addr_size );

    virtual int hal_read( void *data,
                          const uint32_t data_len,
                          const uint32_t timeout,
                          const uint16_t device_addr,
                          const uint16_t mem_addr,
                          const uint16_t mem_addr_size ) = 0;

    virtual int hal_write( void *data,
                           const uint32_t data_len,
                           const uint32_t timeout,
                           const uint16_t device_addr,
                           const uint16_t mem_addr,
                           const uint16_t mem_addr_size ) = 0;

    virtual int hal_read_dma( void *data,
                              const uint32_t data_len,
                              const uint16_t device_addr,
                              const uint16_t mem_addr,
                              const uint16_t mem_addr_size ) = 0;

    virtual int hal_write_dma( void *data,
                               const uint32_t data_len,
                               const uint16_t device_addr,
                               const uint16_t mem_addr,
                               const uint16_t mem_addr_size ) = 0;
};

#endif // __BUS_WITH_ADDR_HPP__