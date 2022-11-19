/**
 * @file gpio.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "gpio.hpp"

GPIO_TypeDef *PORT_HANDLER [] = {
    GPIOA,
#if defined( GPIOB )
    GPIOB,
#endif
#if defined( GPIOC )
    GPIOC,
#endif
#if defined( GPIOD )
    GPIOD,
#endif
#if defined( GPIOE )
    GPIOE,
#endif
#if defined( GPIOF )
    GPIOF,
#endif
#if defined( GPIOG )
    GPIOG,
#endif
#if defined( GPIOH )
    GPIOH,
#endif
#if defined( GPIOI )
    GPIOI,
#endif
};

#define HANDLER( __port ) PORT_HANDLER [ static_cast<int>( ( __port ) ) ]

GPIO::GPIO( GPIO::port_t port, GPIO::pin_t pin )
{
    this->port = port;
    this->pin  = pin;
}

GPIO::~GPIO( void )
{
}

void GPIO::init( GPIO::mode_t mode, GPIO::speed_t speed, GPIO::pull_t pull )
{
    this->mode  = mode;
    this->speed = speed;
    this->pull  = pull;

    switch ( this->port )
    {
    case port_t::A:
        __HAL_RCC_GPIOA_CLK_ENABLE();
        break;
#if defined( GPIOB )
    case port_t::B:
        __HAL_RCC_GPIOB_CLK_ENABLE();
        break;
#endif
#if defined( GPIOC )
    case port_t::C:
        __HAL_RCC_GPIOC_CLK_ENABLE();
        break;
#endif
#if defined( GPIOD )
    case port_t::D:
        __HAL_RCC_GPIOD_CLK_ENABLE();
        break;
#endif
#if defined( GPIOE )
    case port_t::E:
        __HAL_RCC_GPIOE_CLK_ENABLE();
        break;
#endif
#if defined( GPIOF )
    case port_t::F:
        __HAL_RCC_GPIOF_CLK_ENABLE();
        break;
#endif
#if defined( GPIOG )
    case port_t::G:
        __HAL_RCC_GPIOG_CLK_ENABLE();
        break;
#endif
#if defined( GPIOH )
    case port_t::H:
        __HAL_RCC_GPIOH_CLK_ENABLE();
        break;
#endif
#if defined( GPIOI )
    case port_t::I:
        __HAL_RCC_GPIOI_CLK_ENABLE();
        break;
#endif
    }

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    GPIO_InitStruct.Mode  = static_cast<uint32_t>( this->mode );
    GPIO_InitStruct.Pin   = static_cast<uint32_t>( this->pin );
    GPIO_InitStruct.Pull  = static_cast<uint32_t>( this->pull );
    GPIO_InitStruct.Speed = static_cast<uint32_t>( this->speed );

    HAL_GPIO_Init( HANDLER( this->port ), &GPIO_InitStruct );
}

void GPIO::deinit( void )
{
    HAL_GPIO_DeInit( HANDLER( this->port ),
                     static_cast<uint16_t>( this->pin ) );
}

void GPIO::set( void )
{
    HAL_GPIO_WritePin( HANDLER( this->port ),
                       static_cast<uint16_t>( this->pin ),
                       GPIO_PIN_SET );
}

void GPIO::clear( void )
{
    HAL_GPIO_WritePin( HANDLER( this->port ),
                       static_cast<uint16_t>( this->pin ),
                       GPIO_PIN_RESET );
}

void GPIO::toggle( void )
{
    HAL_GPIO_TogglePin( HANDLER( this->port ),
                        static_cast<uint16_t>( this->pin ) );
}

bool GPIO::get( void )
{
    return static_cast<bool>( HAL_GPIO_ReadPin(
        HANDLER( this->port ), static_cast<uint16_t>( this->pin ) ) );
}