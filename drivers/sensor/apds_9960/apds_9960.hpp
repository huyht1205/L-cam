/**
 * @file apds_9960.hpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdint.h>
#include "i2c.hpp"
#include "device.hpp"
#include "gpio.hpp"
#include "error.hpp"

class APDS_9960 : public DEVICE
{
  public:
    APDS_9960( I2C *bus, GPIO *interrupt_pin, uint8_t addr = ( 0x39 << 1 ) );
    ~APDS_9960( void );

    int init( void ) override;
    int deinit( void ) override;
    int on( void ) override;
    int off( void ) override;

    /**
     * @brief Put APDS-9960 to its sleep state
     *
     * Reference: https://docs.broadcom.com/doc/AV02-4191EN, page 9
     *
     * @return int 0: OK
     */
    int sleep( void ) override;

  private:
    uint8_t addr;
    I2C *bus;
    GPIO *interrupt;
};
