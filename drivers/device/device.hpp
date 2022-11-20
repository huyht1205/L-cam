#ifndef __DEVICE_HPP__
#define __DEVICE_HPP__

#include "os.hpp"

class DEVICE
{
  public:
    enum class state_t
    {
        UNINIT,
        READY,
        ON,
        OFF,
        SLEEP,
    };

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

    virtual int reset( void )
    {
        return 0;
    }

    /**
     * @brief Call this API in interrupt routine context GPIO interrupt handler
     *
     */
    virtual void interrupt_callback( void )
    {
    }

    /**
     * @brief Actual data handler upon an interrupt. This is recommended to be
     * called in a non-interrupt routine.
     *
     */
    virtual void handle_measured_data_upon_interrupt( void )
    {
    }

    /**
     * @brief Plug devices into a global event ruled by a master thread.
     *
     * @param event_id [IN] Pre-allocated event object
     * @param device_id [IN] Device ID (defined by user) to be recognized in the
     * master thread
     */
    virtual void register_global_event_handler( OS::event_id_t event_id,
                                                int device_id )
    {
    }

    state_t get_state( void );
    char name [ 16 ];

  protected:
    state_t state;

    /**
     * @brief Plug devices into a global interrupt event to be handled by a
     * master thread.
     *
     */
    OS::event_id_t global_interrupt_event;

    /**
     * @brief Device ID to be recognized in event handler thread
     *
     */
    int device_event_id;
};

#endif // __DEVICE_HPP__