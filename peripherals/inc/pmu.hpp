#ifndef __PMU_HPP__
#define __PMU_HPP__

#include "device.hpp"

class PMU : public Device
{
  public:
    PMU( void );
    ~PMU( void );
    int init( void ) override;
    int deinit( void ) override;
    int on( void ) override;
    int off( void ) override;
    int sleep( void ) override;

    DeviceState get_state( void ) override;

    static PMU *get_instance( void );
};

#endif // __PMU_HPP__