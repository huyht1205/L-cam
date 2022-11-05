#ifndef __DEVICE_HPP__
#define __DEVICE_HPP__

enum class DeviceState
{
    UNINIT,
    READY,
    ON,
    OFF,
    SLEEP,
};

class Device
{
  public:
    Device( void );
    ~Device( void );
    virtual int init( void );
    virtual int deinit( void );
    virtual int on( void );
    virtual int off( void );
    virtual int sleep( void );

    virtual DeviceState get_state( void );
    char name [ 16 ];
};

#endif // __DEVICE_HPP__