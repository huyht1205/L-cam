/**
 * @file bus_without_addr.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __BUS_WITHOUT_ADDR_HPP__
#define __BUS_WITHOUT_ADDR_HPP__

#include "bus.hpp"

class BUS_WITHOUT_ADDRESS : public BUS
{
  public:
    /**
     * @brief Blocking read data from bus without DMA.
     * This call consumes CPU until finishes.
     *
     * @param data [OUT] pre-allocated buffer to store bus data
     * @param data_len [IN] Length in bytes of pre-allocated buffer
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int read( void *data, const uint32_t data_len, const uint32_t timeout )
    {
        return io_access( BUS::io_direction_t::READ,
                          false,
                          nullptr,
                          data,
                          data_len,
                          timeout );
    }

    /**
     * @brief Blocking write data to bus without DMA.
     * This call consumes CPU until finishes.
     *
     * @param data [IN] Copy content of data buffer to peripheral by CPU.
     * @param data_len [IN] Length in bytes of data buffer.
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int write( void *data, const uint32_t data_len, const uint32_t timeout )
    {
        return io_access( BUS::io_direction_t::WRITE,
                          false,
                          data,
                          nullptr,
                          data_len,
                          timeout );
    }

    /**
     * @brief Blocking read & write data (in parallel) from bus without DMA.
     * This call consumes CPU until finishes.
     *
     * @param tx_data [IN] Copy content of data buffer to peripheral by CPU.
     * @param rx_buff [OUT] pre-allocated buffer to store bus data
     * @param data_len [IN] Length in bytes of pre-allocated buffer
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int read_write( void *tx_data,
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

    /**
     * @brief Blocking read data from bus with DMA.
     * This call release CPU while waiting for DMA to finish reading.
     *
     * @param data [OUT] pre-allocated buffer to store bus data
     * @param data_len [IN] Length in bytes of pre-allocated buffer
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int read_dma( void *data, const uint32_t data_len, const uint32_t timeout )
    {
        return io_access(
            BUS::io_direction_t::READ, true, nullptr, data, data_len, timeout );
    }

    /**
     * @brief Blocking write data to bus with DMA.
     * This call releases CPU while writing by DMA.
     *
     * @param data [IN] Copy content of data buffer to peripheral by CPU.
     * @param data_len [IN] Length in bytes of data buffer.
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int write_dma( void *data, const uint32_t data_len, const uint32_t timeout )
    {
        return io_access( BUS::io_direction_t::WRITE,
                          true,
                          data,
                          nullptr,
                          data_len,
                          timeout );
    }

    /**
     * @brief Blocking read & write data (in parallel) from bus DMA.
     * This call releases CPU while writing by DMA.
     *
     * @param tx_data [IN] Copy content of data buffer to peripheral by CPU.
     * @param rx_buff [OUT] pre-allocated buffer to store bus data
     * @param data_len [IN] Length in bytes of pre-allocated buffer
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int read_write_dma( void *tx_data,
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

  protected:
    BUS_WITHOUT_ADDRESS( void *handler, platform_init_fPtr init_fPtr )
        : BUS::BUS( handler, init_fPtr )
    {
    }

    BUS_WITHOUT_ADDRESS( void )
    {
    }

    virtual ~BUS_WITHOUT_ADDRESS( void )
    {
    }

    virtual int io_access( const io_direction_t direction,
                           const bool dma_enabled,
                           void *tx_data,
                           void *rx_buff,
                           const uint32_t data_len,
                           const uint32_t timeout );

    virtual int
    hal_read( void *data, const uint32_t data_len, const uint32_t timeout ) = 0;

    virtual int hal_write( void *data,
                           const uint32_t data_len,
                           const uint32_t timeout ) = 0;

    virtual int hal_read_write( void *tx_data,
                                void *rx_buff,
                                const uint32_t data_len,
                                const uint32_t timeout )
    {
        return NO_ERROR;
    }

    virtual int hal_read_dma( void *data, const uint32_t data_len ) = 0;

    virtual int hal_write_dma( void *data, const uint32_t data_len ) = 0;

    virtual int
    hal_read_write_dma( void *tx_data, void *rx_buff, const uint32_t data_len )
    {
        return NO_ERROR;
    }
};

#endif // __BUS_WITHOUT_ADDR_HPP__