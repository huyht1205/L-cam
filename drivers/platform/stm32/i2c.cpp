#include "i2c.hpp"
#include "i2c.h"
#include "stm32h7xx_hal_conf.h"

#ifdef HAL_I2C_MODULE_ENABLED
#define STM32_I2C_DEINIT( __handler )                                          \
    HAL_I2C_DeInit( static_cast<I2C_HandleTypeDef *>( __handler ) )

#define STM32_I2C_MEM_READ( __handler,                                         \
                            __dev_addr,                                        \
                            __mem_addr,                                        \
                            __mem_addr_size,                                   \
                            __data,                                            \
                            __data_len,                                        \
                            __timeout )                                        \
    HAL_I2C_Mem_Read( static_cast<I2C_HandleTypeDef *>( __handler ),           \
                      __dev_addr,                                              \
                      __mem_addr,                                              \
                      __mem_addr_size,                                         \
                      static_cast<uint8_t *>( __data ),                        \
                      __data_len,                                              \
                      __timeout )

#define STM32_I2C_MEM_WRITE( __handler,                                        \
                             __dev_addr,                                       \
                             __mem_addr,                                       \
                             __mem_addr_size,                                  \
                             __data,                                           \
                             __data_len,                                       \
                             __timeout )                                       \
    HAL_I2C_Mem_Write( static_cast<I2C_HandleTypeDef *>( __handler ),          \
                       __dev_addr,                                             \
                       __mem_addr,                                             \
                       __mem_addr_size,                                        \
                       static_cast<uint8_t *>( __data ),                       \
                       __data_len,                                             \
                       __timeout )

#define STM32_I2C_MEM_READ_DMA(                                                \
    __handler, __dev_addr, __mem_addr, __mem_addr_size, __data, __data_len )   \
    HAL_I2C_Mem_Read_DMA( static_cast<I2C_HandleTypeDef *>( __handler ),       \
                          __dev_addr,                                          \
                          __mem_addr,                                          \
                          __mem_addr_size,                                     \
                          static_cast<uint8_t *>( __data ),                    \
                          __data_len )

#define STM32_I2C_MEM_WRITE_DMA(                                               \
    __handler, __dev_addr, __mem_addr, __mem_addr_size, __data, __data_len )   \
    HAL_I2C_Mem_Write_DMA( static_cast<I2C_HandleTypeDef *>( __handler ),      \
                           __dev_addr,                                         \
                           __mem_addr,                                         \
                           __mem_addr_size,                                    \
                           static_cast<uint8_t *>( __data ),                   \
                           __data_len )

#else // HAL_I2C_MODULE_ENABLED
#define STM32_I2C_DEINIT( __handler ) 0

#define STM32_I2C_MEM_READ( __handler,                                         \
                            __dev_addr,                                        \
                            __mem_addr,                                        \
                            __mem_addr_size,                                   \
                            __data,                                            \
                            __data_len,                                        \
                            __timeout )                                        \
    0

#define STM32_I2C_MEM_WRITE( __handler,                                        \
                             __dev_addr,                                       \
                             __mem_addr,                                       \
                             __mem_addr_size,                                  \
                             __data,                                           \
                             __data_len,                                       \
                             __timeout )                                       \
    0

#define STM32_I2C_MEM_READ_DMA(                                                \
    __handler, __dev_addr, __mem_addr, __mem_addr_size, __data, __data_len )   \
    0

#define STM32_I2C_MEM_WRITE_DMA(                                               \
    __handler, __dev_addr, __mem_addr, __mem_addr_size, __data, __data_len )   \
    0
#endif // HAL_I2C_MODULE_ENABLED

I2C_STM32::I2C_STM32( void *handler, stm32_cubemx_i2c_init init_fPtr )
{
    this->handler     = handler;
    this->cubemx_init = init_fPtr;
}

I2C_STM32::~I2C_STM32( void )
{
}

int I2C_STM32::init( void )
{
    this->cubemx_init();

    return 0;
}

int I2C_STM32::deinit( void )
{
    return STM32_I2C_DEINIT( this->handler );
}

int I2C_STM32::hal_read( void *data,
                         const uint32_t data_len,
                         const uint32_t timeout,
                         const uint16_t device_addr,
                         const uint16_t mem_addr,
                         const uint16_t mem_addr_size )
{
    int e = 0;

    e = STM32_I2C_MEM_READ( this->handler,
                            device_addr,
                            mem_addr,
                            mem_addr_size,
                            data,
                            data_len,
                            timeout );

    if ( e != HAL_OK )
    {
        return e;
    }
    else
    {
        return data_len;
    }
}

int I2C_STM32::hal_write( void *data,
                          const uint32_t data_len,
                          const uint32_t timeout,
                          const uint16_t device_addr,
                          const uint16_t mem_addr,
                          const uint16_t mem_addr_size )
{
    int e = 0;

    e = STM32_I2C_MEM_WRITE( this->handler,
                             device_addr,
                             mem_addr,
                             mem_addr_size,
                             data,
                             data_len,
                             timeout );
    if ( e != HAL_OK )
    {
        return e;
    }
    else
    {
        return data_len;
    }
}

int I2C_STM32::hal_read_dma( void *data,
                             const uint32_t data_len,
                             const uint16_t device_addr,
                             const uint16_t mem_addr,
                             const uint16_t mem_addr_size )
{
    int e = 0;

    e = STM32_I2C_MEM_READ_DMA(
        this->handler, device_addr, mem_addr, mem_addr_size, data, data_len );
    if ( e != HAL_OK )
    {
        return e;
    }
    else
    {
        return data_len;
    }
}

int I2C_STM32::hal_write_dma( void *data,
                              const uint32_t data_len,
                              const uint16_t device_addr,
                              const uint16_t mem_addr,
                              const uint16_t mem_addr_size )
{
    int e = 0;

    e = STM32_I2C_MEM_WRITE_DMA(
        this->handler, device_addr, mem_addr, mem_addr_size, data, data_len );
    if ( e != HAL_OK )
    {
        return e;
    }
    else
    {
        return data_len;
    }
}
