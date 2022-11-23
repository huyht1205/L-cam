/**
 * @file mutex.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

#include "cmsis_os.h"
#include "error.hpp"

namespace OS
{
using mutex_id_t   = osMutexId_t;
using mutex_attr_t = osMutexAttr_t;

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
    return static_cast<int>( osMutexAcquire( mutex_id, timeout ) );
}

/**
 * @brief Wrapped osMutexRelease
 *
 * @param mutex_id
 * @return int
 */
inline int mutex_release( mutex_id_t mutex_id )
{
    return static_cast<int>( osMutexRelease( mutex_id ) );
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

/**
 * @brief Wrapped osMutexDelete
 *
 * @param mutex_id
 * @return int
 */
inline int mutex_delete( mutex_id_t mutex_id )
{
    return static_cast<int>( osMutexDelete( mutex_id ) );
}

}; // namespace OS

#endif // __MUTEX_HPP__