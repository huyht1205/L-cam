#ifndef __OS_HPP__
#define __OS_HPP__

#include <stdint.h>
#include "cmsis_os.h"

namespace os
{
using eventID_t      = osEventFlagsId_t;
using event_config_t = osEventFlagsAttr_t;

/**
 * @brief Delay for ms milliseconds. Release CPU to other threads
 *
 * @param ms [IN] milliseconds
 */
inline int delay_ms( const uint32_t ms )
{
    return static_cast<int>( osDelay( ms ) );
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
 * @param config [IN] wrapped osEventFlagsAttr_t
 * @return eventID_t wrapped osEventFlagsId_t
 */
inline eventID_t event_new( const event_config_t *config )
{
    return osEventFlagsNew( config );
}

/**
 * @brief Wrapped osEventFlagsSet
 *
 * @param event_id
 * @param flags
 * @return int
 */
inline int event_set( eventID_t event_id, int flags )
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
inline int event_clear( eventID_t event_id, int flags )
{
    return osEventFlagsClear( event_id, flags );
}

/**
 * @brief Wrapped osEventFlagsGet
 *
 * @param event_id
 * @return int
 */
inline int event_get( eventID_t event_id )
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
event_wait( eventID_t event_id, int flags, int options, uint32_t timeout )
{
    return osEventFlagsWait( event_id, flags, options, timeout );
}
} // namespace os

#endif // __OS_HPP__