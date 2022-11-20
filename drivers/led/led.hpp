/**
 * @file led.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __LED_HPP__
#define __LED_HPP__

#include "gpio.hpp"

class LED
{
  public:
    LED( void )
    {
    }
    ~LED( void )
    {
    }

    virtual void on( void )
    {
    }
    virtual void off( void )
    {
    }
    virtual void toggle( void )
    {
    }
};

class LED_GPIO : public LED
{
  public:
    LED_GPIO( GPIO *gpio, bool active_low = true );
    ~LED_GPIO( void );

    void on( void ) override;
    void off( void ) override;
    void toggle( void ) override;

  private:
    GPIO *gpio;
    bool active_low;
};

class LED_RGB
{
  public:
    LED_RGB( void )
    {
    }
    ~LED_RGB( void )
    {
    }

    struct rgb_code_t
    {
        uint8_t red;
        uint8_t gree;
        uint8_t blue;
    };

    enum class color_t
    {
        RED = 0,
        GREEN,
        BLUE,
        ALL_COLOR,
    };

    enum class state_t
    {
        OFF = 0,
        ON,
    };

    virtual void on( void )
    {
    }
    virtual void off( void )
    {
    }
    virtual void toggle( void )
    {
    }
    virtual void on( color_t color )
    {
    }
    virtual void toggle( LED_RGB::color_t color )
    {
    }

  protected:
    color_t color;
    bool active_low;
    state_t state;
};

class LED_RGB_GPIO : public LED_RGB
{
  public:
    LED_RGB_GPIO( GPIO *red, GPIO *green, GPIO *blue, bool active_low = true );
    ~LED_RGB_GPIO( void );

    /**
     * @brief Turn on with the previous color. If previous is OFF, it will
     * remain OFF.
     *
     */
    void on( void ) override;

    /**
     * @brief Turn off, obviously.
     *
     */
    void off( void ) override;

    /**
     * @brief Toggle with the previous color. If previous is OFF, it will remain
     * OFF.
     *
     */
    void toggle( void ) override;

    /**
     * @brief Turn on with a specific color
     *
     * @param color [IN] color to turn on
     */
    void on( color_t color ) override;

    /**
     * @brief Toggle with a specific color
     *
     * @param color [IN] color to toggle
     */
    void toggle( LED_RGB::color_t color ) override;

  private:
    GPIO *red;
    GPIO *green;
    GPIO *blue;
};

#endif //  __LED_HPP__