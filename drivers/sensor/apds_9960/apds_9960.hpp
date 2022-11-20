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

    enum feature_t : int
    {
        // Gesture Enable. When asserted, the gesture state machine can be
        // activated.
        // Activation is subject to the states of PEN and GMODE bits.
        gesture = ( 1U << 6 ),

        // Proximity Interrupt Enable. When asserted, it permits proximity
        // interrupts to
        // be generated, subject to the persistence filter settings.
        proximity_interrupt = ( 1U << 5 ),

        // ALS Interrupt Enable. When asserted, it permits ALS interrupts to be
        // generated, subject to the persistence filter settings.
        als_interrupt = ( 1U << 4 ),

        // Wait Enable. This bit activates the wait feature. Writing a one
        // activates the
        // wait timer. Writing a zero disables the wait timer.
        wait = ( 1U << 3 ),

        // Proximity Detect Enable. This field activates the proximity
        // detection.
        // Writing a one activates the proximity. Writing a zero disables the
        // proximity.
        proximity_detect = ( 1U << 2 ),

        // ALS Enable. This field activates ALS function. Writing a one
        // activates the
        // ALS. Writing a zero disables the ALS.
        als = ( 1U << 1 ),
    };

    /**
     * @brief Select 1 or more features (merged by bitwise OR)
     *
     */
    void select_feature( APDS_9960::feature_t feature );

    int init( void ) override;
    int deinit( void ) override;
    int on( void ) override;
    int off( void ) override;

    void interrupt_callback( void ) override;
    void handle_measured_data_upon_interrupt( void ) override;
    void register_global_event_handler( OS::event_id_t event_id,
                                        int device_id ) override;

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
    uint8_t feature;
    uint8_t status;
    int error;

    struct rgb_data_t
    {
        uint16_t clear;
        uint16_t red;
        uint16_t green;
        uint16_t blue;
    } rgb_data;

    int handle_als_interrupt( void );
    int handle_proximity_interrupt( void );
    int handle_gesture_interrupt( void );
};
