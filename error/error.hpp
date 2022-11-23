/**
 * @file error.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include <stdint.h>
#include "errno.h"

#define NO_ERROR 0

enum
{
    ERR_APDS_BEGIN = 100,
    ERR_APDS_9960_INIT_READ_ID,
    ERR_APDS_9960_INIT_WRONG_ID,
    ERR_APDS_9960_IRQ_READ_STATUS,
    ERR_APDS_9960_IRQ_PICLEAR,
    ERR_APDS_9960_IRQ_CICLEAR,
    ERR_APDS_9960_IRQ_AICLEAR,
    ERR_APDS_9960_IRQ_RGBC,
    ERR_APDS_9960_ON,
    ERR_APDS_9960_OFF,
};

#endif // __ERROR_HPP__