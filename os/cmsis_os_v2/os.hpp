#ifndef __OS_HPP__
#define __OS_HPP__

#include <stdint.h>
#include "cmsis_os.h"

namespace os
{
using thread_id_t   = osThreadId_t;
using thread_attr_t = osThreadAttr_t;

using event_id_t   = osEventFlagsId_t;
using event_attr_t = osEventFlagsAttr_t;

using message_queue_id_t   = osMessageQueueId_t;
using message_queue_attr_t = osMessageQueueAttr_t;

using mutex_id_t   = osMutexId_t;
using mutex_attr_t = osMutexAttr_t;

using semaphore_id_t   = osSemaphoreId_t;
using semaphore_attr_t = osSemaphoreAttr_t;

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
 * @brief Wrapped osEventFlagsNew
 *
 * @param attribute [IN] wrapped osEventFlagsAttr_t
 * @return event_id_t wrapped osEventFlagsId_t
 */
inline event_id_t event_new( const event_attr_t *attribute )
{
    return osEventFlagsNew( attribute );
}

/**
 * @brief Wrapped osEventFlagsSet
 *
 * @param event_id
 * @param flags
 * @return int
 */
inline int event_set( event_id_t event_id, int flags )
{
    return osEventFlagsSet( event_id, static_cast<uint32_t>( flags ) );
}

/**
 * @brief Wrapped osEventFLagsClear
 *
 * @param event_id
 * @param flags
 * @return int
 */
inline int event_clear( event_id_t event_id, int flags )
{
    return osEventFlagsClear( event_id, flags );
}

/**
 * @brief Wrapped osEventFlagsGet
 *
 * @param event_id
 * @return int
 */
inline int event_get( event_id_t event_id )
{
    return osEventFlagsGet( event_id );
}

/**
 * @brief Wrapped osEventFlagsWait
 *
 * @param event_id
 * @param flags
 * @param options
 * @param timeout
 * @return int
 */
inline int
event_wait( event_id_t event_id, int flags, int options, uint32_t timeout )
{
    return osEventFlagsWait( event_id, flags, options, timeout );
}

/**
 * @brief Wrapped osMutexNew
 *
 * @param attribute
 * @return mutex_id_t
 */
inline mutex_id_t mutex_new( mutex_attr_t *attribute )
{
    return osMutexNew( attribute );
}

/**
 * @brief Wrapped osMutexAcquire
 *
 * @param mutex_id
 * @param timeout
 * @return int
 */
inline int mutex_acquire( mutex_id_t mutex_id, uint32_t timeout )
{
    return osMutexAcquire( mutex_id, timeout );
}

/**
 * @brief Wrapped osMutexRelease
 *
 * @param mutex_id
 * @return int
 */
inline int mutex_release( mutex_id_t mutex_id )
{
    return osMutexRelease( mutex_id );
}

/**
 * @brief Wrapped osMutexGetOwner
 *
 * @param mutex_id
 * @return mutex_id_t
 */
inline mutex_id_t mutex_get_owner( mutex_id_t mutex_id )
{
    return osMutexGetOwner( mutex_id );
}
} // namespace os

#endif // __OS_HPP__