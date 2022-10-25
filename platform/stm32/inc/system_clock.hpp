#ifndef __SYSTEM_CLOCK_HPP__
#define __SYSTEM_CLOCK_HPP__

enum class SystemClockSpeed
{
    STOP,
    FULL_SPEED,
};

class SystemClock
{
  public:
    SystemClock( void );
    ~SystemClock( void );

    void set_speed( SystemClockSpeed speed );
    static SystemClock *get_instance( void );
};

#endif //  __SYSTEM_CLOCK_HPP__