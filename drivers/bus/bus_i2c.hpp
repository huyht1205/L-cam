#ifndef __BUS_I2C_HPP__
#define __BUS_I2C_HPP__

#include "bus.hpp"

namespace BUS
{

/**
 * @brief Base abstract class for I2C bus
 *
 */
class I2C : public BUS::BUS_BASE
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

  protected:
    I2C( void )
    {
    }
    I2C( void *handler, BUS::platform_init_fPtr init_fPtr )
        : BUS::BUS_BASE::BUS_BASE( handler, init_fPtr )
    {
    }
    virtual ~I2C( void )
    {
    }

    virtual int io_access( const BUS::io_direction_t direction,
                           const bool dma_enabled,
                           void *data,
                           const uint32_t data_len,
                           const uint32_t timeout,
                           const uint16_t device_addr,
                           const uint16_t mem_addr,
                           const uint16_t mem_addr_size ) = 0;
};
}; // namespace BUS

#endif // __BUS_I2C_HPP__