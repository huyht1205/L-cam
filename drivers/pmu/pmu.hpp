#ifndef __PMU_HPP__
#define __PMU_HPP__

#include <stdint.h>
#include "device.hpp"
#include "bus.hpp"

class PMU : public DEVICE
{
  public:
    struct charge_profile_t
    {
        uint32_t fast_current; // Fast charge current
        uint32_t fast_voltage; // Fast charge voltage
        uint32_t term_current; // Terminate charge current
        uint32_t term_voltage; // Terminate charge voltage

        charge_profile_t( uint32_t fast_mA,
                          uint32_t fast_mV,
                          uint32_t term_mA,
                          uint32_t term_mV )
            : fast_current( fast_mA ), fast_voltage( fast_mA ),
              term_current( term_mA ), term_voltage( term_mV )
        {
        }
    };

    struct battery_profile_t
    {
        uint32_t capacity_mAh;     // Battery capacity in mAh
        uint32_t norminal_voltage; // Nominal voltage (Ex: 3.7 for LiPo battery)

        battery_profile_t( uint32_t cap_mAh, uint32_t norm_mV )
            : capacity_mAh( cap_mAh ), norminal_voltage( norm_mV )
        {
        }
    };

    /**
     * @brief Attribute of 1 power rail
     *
     */
    struct power_rail_t
    {
        bool enable;         // Enable or disable power rail
        uint32_t voltage_mV; // Voltage value of the power rail in mV

        power_rail_t( bool en, uint32_t volt_mV )
            : enable( en ), voltage_mV( volt_mV )
        {
        }
    };

  public:
    PMU( void );
    ~PMU( void );
    int init( void ) override;
    int deinit( void ) override;
    int on( void ) override;
    int off( void ) override;
    int sleep( void ) override;

    virtual int charge_enable( void );
    virtual int charge_disable( void );
    virtual int get_soc( void );
    virtual int get_battery_temperature( void );
    virtual int config_charge_profile( const charge_profile_t *profile );
    virtual int config_battery_profile( const battery_profile_t *profile );
};

#endif // __PMU_HPP__