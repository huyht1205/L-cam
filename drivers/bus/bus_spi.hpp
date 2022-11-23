#ifndef __BUS_SPI_HPP__
#define __BUS_SPI_HPP__

#include "bus.hpp"

namespace BUS
{
/**
 * @brief Base abstract class for SPI bus
 *
 */
class SPI : public BUS_BASE
{
    /**
     * @brief Blocking read data from bus without DMA.
     * This call consumes CPU until finishes.
     *
     * @param data [OUT] pre-allocated buffer to store bus data
     * @param data_len [IN] Length in bytes of pre-allocated buffer
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int read( void *data, const uint32_t data_len, const uint32_t timeout );

    /**
     * @brief Blocking write data to bus without DMA.
     * This call consumes CPU until finishes.
     *
     * @param data [IN] Copy content of data buffer to peripheral by CPU.
     * @param data_len [IN] Length in bytes of data buffer.
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int write( void *data, const uint32_t data_len, const uint32_t timeout );

    /**
     * @brief Blocking read & write (in parallel) data <-> bus without DMA.
     * This call consumes CPU until finishes.
     *
     * @param tx_data [IN] Copy content of data buffer to peripheral by CPU.
     * @param rx_buff [OUT] pre-allocated buffer to store bus data.
     * @param data_len [IN] Length in bytes of data buffer.
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int read_write( void *tx_data,
                    void *rx_buff,
                    const uint32_t data_len,
                    const uint32_t timeout );

    /**
     * @brief Blocking read data from bus with DMA.
     * This call release CPU while waiting for DMA to finish reading.
     *
     * @param data [OUT] pre-allocated buffer to store bus data
     * @param data_len [IN] Length in bytes of pre-allocated buffer
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int read_dma( void *data, const uint32_t data_len, const uint32_t timeout );

    /**
     * @brief Blocking write data to bus with DMA.
     * This call releases CPU while writing by DMA.
     *
     * @param data [IN] Copy content of data buffer to peripheral by CPU.
     * @param data_len [IN] Length in bytes of data buffer.
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int
    write_dma( void *data, const uint32_t data_len, const uint32_t timeout );

    /**
     * @brief Blocking read & write (in parallel) data <-> bus DMA.
     * This call releases CPU while writing by DMA.
     *
     * @param tx_data [IN] Copy content of data buffer to peripheral by CPU.
     * @param rx_buff [OUT] pre-allocated buffer to store bus data.
     * @param data_len [IN] Length in bytes of data buffer.
     * @param timeout [IN] Timeout, unit depends on the platform
     * @return int > 0: number of read bytes, <= 0: errors
     */
    int read_write_dma( void *tx_data,
                        void *rx_buff,
                        const uint32_t data_len,
                        const uint32_t timeout );

  protected:
    SPI( void )
    {
    }
    SPI( void *handler, BUS::platform_init_fPtr init_fPtr )
        : BUS::BUS_BASE::BUS_BASE( handler, init_fPtr )
    {
    }
    virtual ~SPI( void )
    {
    }

    virtual int io_access( const BUS::io_direction_t direction,
                           const bool dma_enabled,
                           void *tx_data,
                           void *rx_buff,
                           const uint32_t data_len,
                           const uint32_t timeout ) = 0;
};
}; // namespace BUS

#endif // __BUS_SPI_HPP__