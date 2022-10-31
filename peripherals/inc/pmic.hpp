#ifndef __PMIC_HPP__
#define __PMIC_HPP__

#include "device.hpp"

class PMIC : public Device
{
  public:
    PMIC( void );
    ~PMIC( void );
    int init( void ) override;
    int deinit( void ) override;
    int on( void ) override;
    int off( void ) override;
    int sleep( void ) override;

    DeviceState get_state( void ) override;

    static PMIC *get_instance( void );
};

#endif // __PMIC_HPP__