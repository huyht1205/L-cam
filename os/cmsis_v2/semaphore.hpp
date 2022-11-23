#ifndef __SEMAPHORE_HPP__
#define __SEMAPHORE_HPP__

#include "cmsis_os.h"
#include "error.hpp"

namespace OS
{
using semaphore_id_t   = osSemaphoreId_t;
using semaphore_attr_t = osSemaphoreAttr_t;

/**
 * @brief Wrapped osSemaphoreNew
 *
 * @param max_count
 * @param initial_count
 * @param attr
 * @return semaphore_id_t
 */
inline semaphore_id_t semaphore_new( uint32_t max_count,
                                     uint32_t initial_count,
                                     const semaphore_attr_t *attr )
{
    return osSemaphoreNew( max_count, initial_count, attr );
}

/**
 * @brief Wrapped osSemaphoreAcquire
 *
 * @param semaphore_id
 * @param timeout
 * @return int
 */
inline int semaphore_acquire( semaphore_id_t semaphore_id, uint32_t timeout )
{
    return static_cast<int>( osSemaphoreAcquire( semaphore_id, timeout ) );
}

/**
 * @brief Wrapped osSemaphoreRelease
 *
 * @param semaphore_id
 * @return int
 */
inline int semaphore_release( semaphore_id_t semaphore_id )
{
    return static_cast<int>( osSemaphoreRelease( semaphore_id ) );
}

/**
 * @brief Wrapped osSemaphoreDelete
 *
 * @param semaphore_id
 * @return int
 */
inline int semaphore_delete( semaphore_id_t semaphore_id )
{
    return static_cast<int>( osSemaphoreDelete( semaphore_id ) );
}

/**
 * @brief Wrapped osSemaphoreGetCount
 *
 * @param semaphore_id
 * @return int
 */
inline int semaphore_get_count( semaphore_id_t semaphore_id )
{
    return static_cast<int>( osSemaphoreGetCount( semaphore_id ) );
}

/**
 * @brief Wrapped osSemaphoreGetName
 *
 * @param semaphore_id
 * @return const char*
 */
inline const char *semaphore_get_name( semaphore_id_t semaphore_id )
{
    return osSemaphoreGetName( semaphore_id );
}

}; // namespace OS

#endif // __SEMAPHORE_HPP__