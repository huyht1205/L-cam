/**
 * @file bits.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __BITS_HPP__
#define __BITS_HPP__

#include <stdint.h>

namespace BITS
{
enum class mask_t : uint32_t {
    WIDTH_1 = 0x00000001,
    WIDTH_2 = 0x00000003,
    WIDTH_3 = 0x00000007,
    WIDTH_4 = 0x0000000F,

    WIDTH_5 = 0x0000001F,
    WIDTH_6 = 0x0000003F,
    WIDTH_7 = 0x0000007F,
    WIDTH_8 = 0x000000FF,

    WIDTH_9  = 0x000001FF,
    WIDTH_10 = 0x000003FF,
    WIDTH_11 = 0x000007FF,
    WIDTH_12 = 0x00000FFF,

    WIDTH_13 = 0x00001FFF,
    WIDTH_14 = 0x00003FFF,
    WIDTH_15 = 0x00007FFF,
    WIDTH_16 = 0x0000FFFF,

    WIDTH_17 = 0x0001FFFF,
    WIDTH_18 = 0x0003FFFF,
    WIDTH_19 = 0x0007FFFF,
    WIDTH_20 = 0x000FFFFF,

    WIDTH_21 = 0x001FFFFF,
    WIDTH_22 = 0x003FFFFF,
    WIDTH_23 = 0x007FFFFF,
    WIDTH_24 = 0x00FFFFFF,

    WIDTH_25 = 0x01FFFFFF,
    WIDTH_26 = 0x03FFFFFF,
    WIDTH_27 = 0x07FFFFFF,
    WIDTH_28 = 0x0FFFFFFF,

    WIDTH_29 = 0x1FFFFFFF,
    WIDTH_30 = 0x3FFFFFFF,
    WIDTH_31 = 0x7FFFFFFF,
    WIDTH_32 = 0xFFFFFFFF,
};

struct reg_8bit_feature
{
    uint8_t pos;
    mask_t mask;
};

inline void set( uint8_t pos, mask_t mask, uint32_t value, uint32_t reg )
{
    reg |= ( value & static_cast<uint32_t>( mask ) ) << pos;
}
inline void clear( uint8_t pos, mask_t mask, uint32_t reg )
{
    reg &= ~( ( static_cast<uint32_t>( mask ) ) << pos );
}
}; // namespace BITS

#endif // __BITS_HPP__