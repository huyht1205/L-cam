/**
 * @file gpio.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __GPIO_HPP__
#define __GPIO_HPP__

#include <stdint.h>

#if defined( STM32L4 )
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_conf.h"
#elif defined( STM32H7 )
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_conf.h"
#endif

class GPIO
{
  public:
    enum class pin_t : uint16_t
    {
        PIN_0  = GPIO_PIN_0,
        PIN_1  = GPIO_PIN_1,
        PIN_2  = GPIO_PIN_2,
        PIN_3  = GPIO_PIN_3,
        PIN_4  = GPIO_PIN_4,
        PIN_5  = GPIO_PIN_5,
        PIN_6  = GPIO_PIN_6,
        PIN_7  = GPIO_PIN_7,
        PIN_8  = GPIO_PIN_8,
        PIN_9  = GPIO_PIN_9,
        PIN_10 = GPIO_PIN_10,
        PIN_11 = GPIO_PIN_11,
        PIN_12 = GPIO_PIN_12,
        PIN_13 = GPIO_PIN_13,
        PIN_14 = GPIO_PIN_14,
        PIN_15 = GPIO_PIN_15,
    };

    enum class port_t : uint32_t
    {
        A = 0,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
    };

    enum class mode_t : uint32_t
    {
        GPIO_INPUT              = GPIO_MODE_INPUT,
        GPIO_OUTPUT_PP          = GPIO_MODE_OUTPUT_PP,
        GPIO_OUTPUT_OD          = GPIO_MODE_OUTPUT_OD,
        GPIO_AF_PP              = GPIO_MODE_AF_PP,
        GPIO_AF_OD              = GPIO_MODE_AF_OD,
        GPIO_ANALOG             = GPIO_MODE_ANALOG,
        GPIO_ANALOG_ADC_CONTROL = GPIO_MODE_ANALOG_ADC_CONTROL,
        GPIO_IT_RISING          = GPIO_MODE_IT_RISING,
        GPIO_IT_FALLING         = GPIO_MODE_IT_FALLING,
        GPIO_IT_RISING_FALLING  = GPIO_MODE_IT_RISING_FALLING,
        GPIO_EVT_RISING         = GPIO_MODE_EVT_RISING,
        GPIO_EVT_FALLING        = GPIO_MODE_EVT_FALLING,
        GPIO_EVT_RISING_FALLING = GPIO_MODE_EVT_RISING_FALLING,
    };

    enum class pull_t : char
    {
        NO_PULL   = GPIO_NOPULL,
        PULL_UP   = GPIO_PULLUP,
        PULL_DOWN = GPIO_PULLDOWN,
    };

    enum class speed_t : char
    {
        LOW       = GPIO_SPEED_FREQ_LOW,
        MEDIUM    = GPIO_SPEED_FREQ_MEDIUM,
        HIGH      = GPIO_SPEED_FREQ_HIGH,
        VERY_HIGH = GPIO_SPEED_FREQ_VERY_HIGH,
    };

    GPIO( GPIO::port_t port, GPIO::pin_t pin );
    ~GPIO( void );

    void init( GPIO::mode_t mode,
               GPIO::speed_t speed,
               GPIO::pull_t pull = GPIO::pull_t::NO_PULL );
    void deinit( void );

    void set( void );
    void clear( void );
    void toggle( void );
    bool get( void );

  private:
    GPIO::port_t port;
    GPIO::mode_t mode;
    GPIO::pull_t pull;
    GPIO::speed_t speed;
    GPIO::pin_t pin;
};

#endif // __GPIO_HPP__