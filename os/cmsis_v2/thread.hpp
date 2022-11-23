/**
 * @file thread.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include "cmsis_os.h"

namespace OS
{
using thread_id_t   = osThreadId_t;
using thread_attr_t = osThreadAttr_t;
using thread_func_t = osThreadFunc_t;


};     // namespace OS
#endif //  __THREAD_HPP__