#ifndef __BUS_HPP__
#define __BUS_HPP__

#include <stdint.h>
#include "OS.hpp"

/**
 * @brief Base abstract class for buses: I2C, SPI, UART
 *
 */
class BUS
{
    enum class dma_cb_type : int
    {
        DMA_COMPLETE_WRITE_FULL = 1 << 0,
        DMA_COMPLETE_READ_FULL  = 1 << 1,

        DMA_COMPLETE_WRITE_HALF = 1 << 2,
        DMA_COMPLETE_READ_HALF  = 1 << 3,
    };

  public:
    BUS( void );
    ~BUS( void );

    virtual int init( void );
    virtual int deinit( void );

    /**
     * @brief Init OS-dependencies for DMA scheduling
     *
     * @pre OS::init_kernel is called before this API.
     *
     * @param dma_event_config [IN] Config OS event
     * @return int 0: OK, others: error
     */
    int enable_dma( OS::event_attr_t *dma_event_config );

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
              const uint16_t mem_addr_size );

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
               const uint16_t mem_addr_size );

    /**
     * @brief Blocking read data from bus with DMA.
     * This call release CPU while waiting for DMA to finish reading.
     * @pre Bus::enable_dma is called in before this API.
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
                  const uint16_t mem_addr_size );

    /**
     * @brief Blocking write data to bus with DMA.
     * This call releases CPU while writing by DMA.
     *
     * @pre Bus::enable_dma is called in before this API.
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
                   const uint16_t mem_addr_size );

    void dma_interrupt_cb( dma_cb_type type );

  protected:
    void *handler;            /* Device handler from HAL of the platform */
    OS::event_id_t dma_event; /* To synchronize thread with DMA event */
    OS::mutex_id_t mutex;     /* Mutex to be thread-safe */

    /**
     * @brief Actual hardware read without DMA from the HAL of the platform
     *
     * @param data [OUT]
     * @param data_len [IN]
     * @param timeout [IN]
     * @param device_addr [IN]
     * @param mem_addr [IN]
     * @param mem_addr_size [IN]
     * @return int > 0: number of read bytes, <= 0: errors
     */
    virtual int hal_read( void *data,
                          const uint32_t data_len,
                          const uint32_t timeout,
                          const uint16_t device_addr,
                          const uint16_t mem_addr,
                          const uint16_t mem_addr_size )
    {
        return 0;
    }

    /**
     * @brief Actual hardware write without DMA from the HAL of the platform
     *
     * @param data [IN]
     * @param data_len [IN]
     * @param timeout [IN]
     * @param device_addr [IN]
     * @param mem_addr [IN]
     * @param mem_addr_size [IN]
     * @return int > 0: number of read bytes, <= 0: errors
     */
    virtual int hal_write( void *data,
                           const uint32_t data_len,
                           const uint32_t timeout,
                           const uint16_t device_addr,
                           const uint16_t mem_addr,
                           const uint16_t mem_addr_size )
    {
        return 0;
    }

    /**
     * @brief Actual hardware read with DMA from the HAL of the platform
     *
     * @param data [OUT]
     * @param data_len [IN]
     * @param device_addr [IN]
     * @param mem_addr [IN]
     * @param mem_addr_size [IN]
     * @return int > 0: number of read bytes, <= 0: errors
     */
    virtual int hal_read_dma( void *data,
                              const uint32_t data_len,
                              const uint16_t device_addr,
                              const uint16_t mem_addr,
                              const uint16_t mem_addr_size )
    {
        return 0;
    }

    /**
     * @brief Actual hardware write with DMA from the HAL of the platform
     *
     * @param data [IN]
     * @param data_len [IN]
     * @param device_addr [IN]
     * @param mem_addr [IN]
     * @param mem_addr_size [IN]
     * @return int > 0: number of read bytes, <= 0: errors
     */
    virtual int hal_write_dma( void *data,
                               const uint32_t data_len,
                               const uint16_t device_addr,
                               const uint16_t mem_addr,
                               const uint16_t mem_addr_size )
    {
        return 0;
    }

  private:
    enum class io_direction_t
    {
        READ  = 1,
        WRITE = 2,
    };

    int io_access( const io_direction_t direction,
                   const bool dma_enabled,
                   void *data,
                   const uint32_t data_len,
                   const uint32_t timeout,
                   const uint16_t device_addr,
                   const uint16_t mem_addr,
                   const uint16_t mem_addr_size );
};

#endif // __BUS_HPP__