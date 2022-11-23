/**
 * @file event.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include "cmsis_os.h"
#include "error.hpp"

namespace OS
{
using event_id_t   = osEventFlagsId_t;
using event_attr_t = osEventFlagsAttr_t;

enum class event_flag_option_t : uint32_t
{
    wait_any = static_cast<uint32_t>( osFlagsWaitAny ),
    wait_all = static_cast<uint32_t>( osFlagsWaitAll ),
    no_clear = static_cast<uint32_t>( osFlagsNoClear ),
};

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
inline int event_set( event_id_t event_id, uint32_t flags )
{
    return static_cast<int>( osEventFlagsSet( event_id, flags ) );
}

/**
 * @brief Wrapped osEventFLagsClear
 *
 * @param event_id
 * @param flags
 * @return int
 */
inline int event_clear( event_id_t event_id, uint32_t flags )
{
    return static_cast<int>( osEventFlagsClear( event_id, flags ) );
}

/**
 * @brief Wrapped osEventFlagsGet
 *
 * @param event_id
 * @return int
 */
inline int event_get( event_id_t event_id )
{
    return static_cast<int>( osEventFlagsGet( event_id ) );
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
inline int event_wait( event_id_t event_id,
                       uint32_t flags,
                       OS::event_flag_option_t options,
                       uint32_t timeout )
{
    return static_cast<int>( osEventFlagsWait(
        event_id, flags, static_cast<uint32_t>( options ), timeout ) );
}
};     // namespace OS
#endif // __EVENT_HPP__