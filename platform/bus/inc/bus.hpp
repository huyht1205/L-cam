#ifndef __BUS_HPP__
#define __BUS_HPP__

#include <stdint.h>

/**
 * @brief Base abstract class for buses: I2C, SPI, UART
 *
 */
class Bus
{
  public:
    Bus( void );
    ~Bus( void );

    virtual int init( void );
    virtual int deinit( void );

    /**
     * @brief Power on bus
     * In general, it will enable peripheral clock of the bus.
     *
     * @return int 0: OK, others: errors
     */
    virtual int on( void );

    /**
     * @brief Power off bus
     * In general, it will gate peripheral clock of the bus.
     *
     * @return int 0: OK, others: errors
     */
    virtual int off( void );

    /**
     * @brief Blocking read data from bus.
     * This call consumes CPU until finishes.
     *
     * @param data [IN] pre-allocated buffer to store bus data
     * @param data_len [IN] Length in bytes of pre-allocated buffer
     * @param timeout_ms [IN] Timeout in milliseconds
     * @return int > 0: number of read bytes, <= 0: errors
     */
    virtual int
    read( void *data, const uint32_t data_len, const uint32_t timeout_ms );

    /**
     * @brief Blocking write data to bus.
     * This call consumes CPU until finishes.
     *
     * @param data [IN] Copy content of data buffer to peripheral by CPU.
     * @param data_len [IN] Length in bytes of data buffer.
     * @param timeout_ms [IN] Timeout in milliseconds.
     * @return int > 0: number of read bytes, <= 0: errors
     */
    virtual int
    write( void *data, const uint32_t data_len, const uint32_t timeout_ms );

    /**
     * @brief Blocking read data from bus by DMA
     * This call does NOT consume CPU until finishes.
     * Data is transferred by DMA.
     *
     * @pre DMA must be enable for the bus. DMA buffer type is linear.
     *
     * @param data [IN] pre-allocated buffer to store bus data
     * @param data_len [IN] Length in bytes of pre-allocated buffer
     * @param timeout_ms [IN] Timeout in milliseconds
     * @return int > 0: number of read bytes, <= 0: errors
     */
    virtual int
    read_dma( void *data, const uint32_t data_len, const uint32_t timeout_ms );

    /**
     * @brief Blocking write data to bus by DMA.
     * This call does NOT consume CPU until finishes.
     * Data is transferred by DMA.
     *
     * @pre DMA must be enable for the bus. DMA buffer type is linear.
     *
     * @param data [IN] Copy content of data buffer to peripheral by DMA.
     * @param data_len [IN] Length in bytes of data buffer.
     * @param timeout_ms [IN] Timeout in milliseconds.
     * @return int > 0: number of read bytes, <= 0: errors
     */
    virtual int
    write_dma( void *data, const uint32_t data_len, const uint32_t timeout_ms );
};

#endif // __BUS_HPP__