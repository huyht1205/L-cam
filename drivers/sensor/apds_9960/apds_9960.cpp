/**
 * @file apds_9960.cpp
 * @author Luck Hoang (huyht1205@pm.me)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "apds_9960.hpp"
#include "error.hpp"
#include "bits.hpp"

#define REG_RAM_R_W 0x00

/* ------------ Power on/off, enable functions and interrupts. ------------ */
#define REG_ENABLE_R_W 0x80
// Power ON. This field activates the internal oscillator to permit the timers
// and ADC channels to operate. Writing a one activates the oscillator. Writing
// a zero disables the oscillator and puts the device into a low power sleep
// mode. During reads and writes over the I2C interface, this bit is temporarily
// overridden and the oscillator is enabled, independent of the state of PON.
#define ENABLE_PON 0x01

/* ------------ ADC Integration Time Register ------------ */
#define REG_ATIME_R_W 0x81

/* ------------ Wait Time Register ------------ */
#define REG_WTIME_R_W 0x83

/* ------------ ALS Interrupt Threshold Register ------------ */
#define REG_AILTL_R_W 0x84
#define REG_AILTH_R_W 0x85
#define REG_AIHTL_R_W 0x86
#define REG_AIHTH_R_W 0x87

/* ------------ Proximity Interrupt Threshold Register ------------ */
#define REG_PILT_R_W 0x89
#define REG_PIHT_R_W 0x8B

/* ------------ Persistence Register ------------ */
#define REG_PERS_R_W 0x8C

/* ------------ Configuration Register One ------------ */
#define REG_CONFIG1_R_W 0x8D

/* ------------ Proximity Pulse Count Register ------------ */
#define REG_PPULSE_R_W 0x8E

/* ------------ Control Register One ------------ */
#define REG_CONTROL_R_W 0x8F

/* ------------ Configuration Register Two ------------ */
#define REG_CONFIG2_R_W 0x90

/* ------------ ID Register ------------ */
#define REG_ID_R 0x92

/* ------------ Status Register ------------ */
#define REG_STATUS_R 0x93

/* ------------ RGBC Data Register ------------ */
#define REG_CDATAL_R 0x94
#define REG_CDATAH_R 0x95
#define REG_RDATAL_R 0x96
#define REG_RDATAH_R 0x97
#define REG_GDATAL_R 0x98
#define REG_GDATAH_R 0x99
#define REG_BDATAL_R 0x9A
#define REG_BDATAH_R 0x9B

/* ------------ Proximity Data Register ------------ */
#define REG_PDATA_R 0x9C

/* ------------ Proximity Offset UP / RIGHT Register ------------ */
#define REG_POFFSET_UR_R_W 0x9D

/* ------------ Proximity Offset DOWN / LEFT ------------ */
#define REG_POFFSET_DL_R_W 0x9E

/* ------------ Configuration Three Register ------------ */
#define REG_CONFIG3_R_W 0x9F

/* ------------ Gesture Proximity Enter Threshold Register ------------ */
#define REG_GPENTH_R_W 0xA0

/* ------------ Gesture Exit Threshold Register ------------ */
#define REG_GEXTH_R_W 0xA1

/* ------------ Gesture Configuration One Register ------------ */
#define REG_GCONF1_R_W 0xA2

/* ------------ Gesture Configuration Two Register ------------ */
#define REG_GCONF2_R_W 0xA3

/* ------------ Gesture UP Offset Register ------------ */
#define REG_GOFFSET_U_R_W 0xA4

/* ------------ Gesture DOWN Offset Register ------------ */
#define REG_GOFFSET_D_R_W 0xA5

/* ------------ Gesture LEFT Offset Register ------------ */
#define REG_GOFFSET_L_R_W 0xA7

/* ------------ Gesture RIGHT Offset Register ------------ */
#define REG_GOFFSET_R_R_W 0xA9

/* ------------ Gesture Pulse Count and Length Register ------------ */
#define REG_GPULSE_R_W 0xA6

/* ------------ Gesture Configuration Three Register ------------ */
#define REG_GCONF3_R_W 0xAA

/* ------------ Gesture Configuration Four Register ------------ */
#define REG_GCONF4_R_W 0xAB

/* ------------ Gesture FIFO Level Register ------------ */
#define REG_GFLVL_R 0xAE

/* ------------ Gesture Status Register ------------ */
#define REG_GSTATUS_R 0xAF

/* ------------ Clear Interrupt Registers ------------ */
#define REG_IFORCE_W  0xE4
#define REG_PICLEAR_W 0xE5
#define REG_CICLEAR_W 0xE6
#define REG_AICLEAR_W 0xE7

/* ------------ Gesture FIFO Register ------------ */
#define REG_GFIFO_U_R 0xFC
#define REG_GFIFO_D_R 0xFD
#define REG_GFIFO_L_R 0xFE
#define REG_GFIFO_R_R 0xFF

APDS_9960::APDS_9960( I2C *bus, GPIO *interrupt_pin, uint8_t addr )
{
    this->bus       = bus;
    this->addr      = addr;
    this->interrupt = interrupt_pin;

    snprintf( name, sizeof( name ), "APDS_9960" );
}

APDS_9960::~APDS_9960()
{
}

void APDS_9960::select_feature( feature_t feature )
{
    this->feature = static_cast<uint8_t>( feature );
}

int APDS_9960::init( void )
{
    uint8_t id              = 0;
    const uint8_t DEVICE_ID = 0xAB;
    int e                   = 0;

    e = bus->read( &id, sizeof( id ), 1000, addr, REG_ID_R, 1 );
    if ( e != sizeof( id ) )
    {
        return -ERRNO_ADPS_9960_READ_ID_BUS_RD;
    }

    if ( id != DEVICE_ID )
    {
        return -ERRNO_ADPS_9960_READ_ID_WRONG;
    }

    state   = DEVICE::state_t::READY;
    error   = NO_ERROR;
    status  = 0;
    feature = 0;

    return 0;
}

int APDS_9960::deinit( void )
{
    state = DEVICE::state_t::UNINIT;
    return 0;
}

int APDS_9960::on( void )
{
    uint8_t data = this->feature | ENABLE_PON;
    int e        = 0;

    e = bus->write( &data, sizeof( data ), 1000, addr, REG_ENABLE_R_W, 1 );
    if ( e < 0 )
    {
        return -ERRNO_ADPS_9960_ON_BUS_WR;
    }

    this->state = DEVICE::state_t::ON;
    return 0;
}

int APDS_9960::off( void )
{
    uint8_t data = 0;
    int e        = 0;

    e = bus->write( &data, sizeof( data ), 1000, addr, REG_ENABLE_R_W, 1 );
    if ( e < 0 )
    {
        return -ERRNO_ADPS_9960_ON_BUS_WR;
    }

    state = DEVICE::state_t::OFF;
    return 0;
}

int APDS_9960::sleep( void )
{
    state = DEVICE::state_t::SLEEP;
    return 0;
}

void APDS_9960::interrupt_callback( void )
{
    if ( state >= DEVICE::state_t::READY )
    {
        OS::event_set( this->global_interrupt_event, this->device_event_id );
    }
}

void APDS_9960::handle_measured_data_upon_interrupt( void )
{
    int e = 0;

    do
    {
        e = bus->read( &status, sizeof( status ), 1000, addr, REG_STATUS_R, 1 );
        if ( e != sizeof( status ) )
        {
            this->error = -ERRNO_ADPS_9960_IRQ_STATUS_BUS_RD;
        }

        if ( ( feature & feature_t::als_interrupt ) ==
             feature_t::als_interrupt )
        {
            e = handle_als_interrupt();
        }
        if ( e != NO_ERROR )
        {
            this->error = e;
        }

        if ( ( feature & feature_t::proximity_interrupt ) ==
             feature_t::proximity_interrupt )
        {
            e = handle_proximity_interrupt();
        }
        if ( e != NO_ERROR )
        {
            this->error = e;
        }

        if ( ( feature & feature_t::gesture ) == feature_t::gesture )
        {
            e = handle_gesture_interrupt();
        }
        if ( e != NO_ERROR )
        {
            this->error = e;
        }
    } while ( 0 );

    // Clear all interrupts
    uint8_t dummy = 0;

    e = bus->write( &dummy, 1, 1000, addr, REG_PICLEAR_W, 1 );
    if ( e != 1 )
    {
        this->error = -ERRNO_ADPS_9960_IRQ_PICLEAR_BUS_WR;
    }

    e = bus->write( &dummy, 1, 1000, addr, REG_CICLEAR_W, 1 );
    if ( e != 1 )
    {
        this->error = -ERRNO_ADPS_9960_IRQ_PICLEAR_BUS_WR;
    }

    e = bus->write( &dummy, 1, 1000, addr, REG_AICLEAR_W, 1 );
    if ( e != 1 )
    {
        this->error = -ERRNO_ADPS_9960_IRQ_PICLEAR_BUS_WR;
    }
}

void APDS_9960::register_global_event_handler( OS::event_id_t event_id,
                                               int device_id )
{
    this->global_interrupt_event = event_id;
    this->device_event_id        = device_id;
}

int APDS_9960::handle_als_interrupt( void )
{
    int e = 0;

    // Read 8-bytes starting from CDATAL - BDATAH for all RGBC
    e = bus->read( &rgb_data, 8, 1000, addr, REG_CDATAL_R, 1 );
    if ( e != 8 )
    {
        return -ERRNO_ADPS_9960_IRQ_RGBC_BUS_RD;
    }

    return NO_ERROR;
}

int APDS_9960::handle_proximity_interrupt( void )
{
    return NO_ERROR;
}

int APDS_9960::handle_gesture_interrupt( void )
{
    return NO_ERROR;
}
