#ifndef __OS_HPP__
#define __OS_HPP__

#include <stdint.h>
#include "cmsis_os.h"
#include "event.hpp"
#include "thread.hpp"
#include "mutex.hpp"
#include "semaphore.hpp"
#include "message_queue.hpp"

namespace OS
{
const uint32_t WAIT_FOREVER = static_cast<uint32_t>( osWaitForever );

const int ERROR_TIMEOUT = static_cast<int>( osErrorTimeout );

/**
 * @brief Get the tick of OS.
 *
 * @return uint32_t tick count
 */
inline uint32_t get_tick( void )
{
    return osKernelGetTickCount();
}

/**
 * @brief Delay for a number of os tick. Release CPU to other threads
 *
 * @param tick [IN] Tick count
 */
inline int delay( const uint32_t tick )
{
    return static_cast<int>( osDelay( tick ) );
}

/**
 * @brief Wrapped osKernelInitialize
 *
 */
inline void init_kernel( void )
{
    osKernelInitialize();
}

/**
 * @brief Wrapped osKernelStart
 *
 */
inline void start_kernel( void )
{
    osKernelStart();
}

inline thread_id_t
thread_new( thread_func_t func, void *arg, const thread_attr_t *attr )
{
    return osThreadNew( func, arg, attr );
}

} // namespace OS

#endif // __OS_HPP__