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

class DEVICE
{
  public:
    DEVICE( void );
    ~DEVICE( void );

    virtual int init( void )
    {
        return 0;
    }

    virtual int deinit( void )
    {
        return 0;
    }

    virtual int on( void )
    {
        return 0;
    }

    virtual int off( void )
    {
        return 0;
    }

    virtual int sleep( void )
    {
        return 0;
    }

    DeviceState get_state( void );
    char name [ 16 ];

  protected:
    DeviceState state;
};

#endif // __DEVICE_HPP__