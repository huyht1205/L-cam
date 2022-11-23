/**
 * @file queue.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __MESSAGE_QUEUE_HPP__
#define __MESSAGE_QUEUE_HPP__

#include "cmsis_os.h"
#include "error.hpp"

namespace OS
{
using message_queue_id_t   = osMessageQueueId_t;
using message_queue_attr_t = osMessageQueueAttr_t;

/**
 * @brief Wrapped osMessageQueueNew
 *
 * @param msg_count
 * @param msg_size
 * @param attr
 * @return message_queue_id_t
 */
inline message_queue_id_t message_queue_new( uint32_t msg_count,
                                             uint32_t msg_size,
                                             const message_queue_attr_t *attr )
{
    return osMessageQueueNew( msg_count, msg_size, attr );
}

/**
 * @brief Wrapped osMessageQueueDelete
 *
 * @param mq_id
 * @return int
 */
inline int message_queue_delete( message_queue_id_t mq_id )
{
    return static_cast<int>( osMessageQueueDelete( mq_id ) );
}

/**
 * @brief Wrapped osMessageQueueGetCapacity
 *
 * @param mq_id
 * @return uint32_t
 */
inline uint32_t message_queue_get_capacity( message_queue_id_t mq_id )
{
    return osMessageQueueGetCapacity( mq_id );
}

/**
 * @brief Wrapped osMessageQueueGetName
 *
 * @param mq_id
 * @return const char*
 */
inline const char *message_queue_get_name( message_queue_id_t mq_id )
{
    return osMessageQueueGetName( mq_id );
}

/**
 * @brief Wrapped osMessageQueuePut
 *
 * @param mq_id
 * @param msg_ptr
 * @param msg_prio
 * @param timeout
 * @return int
 */
inline int message_queue_put( message_queue_id_t mq_id,
                              const void *msg_ptr,
                              uint8_t msg_prio,
                              uint32_t timeout )
{
    return static_cast<int>(
        osMessageQueuePut( mq_id, msg_ptr, msg_prio, timeout ) );
}

/**
 * @brief Wrapped osMessageQueuGet
 *
 * @param mq_id
 * @param msg_ptr
 * @param msg_prio
 * @param timeout
 * @return int
 */
inline int message_queue_get( message_queue_id_t mq_id,
                              void *msg_ptr,
                              uint8_t *msg_prio,
                              uint32_t timeout )
{
    return static_cast<int>(
        osMessageQueueGet( mq_id, msg_ptr, msg_prio, timeout ) );
}

/**
 * @brief Wrapped osMessageQueueGetMsgSize
 *
 * @return int
 */
inline uint32_t message_queue_get_msg_size( message_queue_id_t mq_id )
{
    return osMessageQueueGetMsgSize( mq_id );
}

/**
 * @brief Wrapped osMessageQueueGetCount
 *
 * @param mq_id
 * @return uint32_t
 */
inline uint32_t message_queue_get_count( message_queue_id_t mq_id )
{
    return osMessageQueueGetCount( mq_id );
}

/**
 * @brief Wrapped osMessageQueueGetSpace
 *
 * @param mq_id
 * @return uint32_t
 */
inline uint32_t message_queue_get_space( message_queue_id_t mq_id )
{
    return osMessageQueueGetSpace( mq_id );
}

/**
 * @brief Wrapped osMessageQueueReset
 *
 * @param mq_id
 * @return int
 */
inline int message_queue_reset( message_queue_id_t mq_id )
{
    return static_cast<int>( osMessageQueueReset( mq_id ) );
}

}; // namespace OS

#endif // __MESSAGE_QUEUE_HPP__