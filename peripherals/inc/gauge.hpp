#ifndef __GAUGE_HPP__
#define __GAUGE_HPP__

#include "device.hpp"

class GAUGE : public Device
{
  public:
    GAUGE( void );
    ~GAUGE( void );
    int init( void ) override;
    int deinit( void ) override;
    int on( void ) override;
    int off( void ) override;
    int sleep( void ) override;

    DeviceState get_state( void ) override;

    static GAUGE *get_instance( void );
};

#endif // __GAUGE_HPP__