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

#define RAM_R_W 0x00

/* ------------ Power on/off, enable functions and interrupts. ------------ */
#define ENABLE_R_W 0x80
// Gesture Enable. When asserted, the gesture state machine can be activated.
// Activation is subject to the states of PEN and GMODE bits.
#define ENABLE_GEN_WIDTH 1
#define ENABLE_GEN_POS   6
// Proximity Interrupt Enable. When asserted, it permits proximity interrupts to
// be generated, subject to the persistence filter settings.
#define ENABLE_PIEN_WIDTH 1
#define ENABLE_PIEN_POS   5
// ALS Interrupt Enable. When asserted, it permits ALS interrupts to be
// generated, subject to the persistence filter settings.
#define ENABLE_AIEN_WIDTH 1
#define ENABLE_AIEN_POS   4
// Wait Enable. This bit activates the wait feature. Writing a one activates the
// wait timer. Writing a zero disables the wait timer.
#define ENABLE_WEN_WIDTH 1
#define ENABLE_WEN_POS   3
// Proximity Detect Enable. This field activates the proximity detection.
// Writing a one activates the proximity. Writing a zero disables the proximity.
#define ENABLE_PEN_WIDTH 1
#define ENABLE_PEN_POS   1
// ALS Enable. This field activates ALS function. Writing a one activates the
// ALS. Writing a zero disables the ALS.
#define ENABLE_AEN_WIDTH 1
#define ENABLE_AEN_POS   1
// Power ON. This field activates the internal oscillator to permit the timers
// and ADC channels to operate. Writing a one activates the oscillator. Writing
// a zero disables the oscillator and puts the device into a low power sleep
// mode. During reads and writes over the I2C interface, this bit is temporarily
// overridden and the oscillator is enabled, independent of the state of PON.
#define ENABLE_PON_WIDTH 1
#define ENABLE_PON_POS   0

/* ------------ ADC Integration Time Register ------------ */
#define ATIME_R_W 0x81

/* ------------ Wait Time Register ------------ */
#define WTIME_R_W 0x83

/* ------------ ALS Interrupt Threshold Register ------------ */
#define AILTL_R_W 0x84
#define AILTH_R_W 0x85
#define AIHTL_R_W 0x86
#define AIHTH_R_W 0x87

/* ------------ Proximity Interrupt Threshold Register ------------ */
#define PILT_R_W 0x89
#define PIHT_R_W 0x8B

/* ------------ Persistence Register ------------ */
#define PERS_R_W 0x8C

/* ------------ Configuration Register One ------------ */
#define CONFIG1_R_W 0x8D

/* ------------ Proximity Pulse Count Register ------------ */
#define PPULSE_R_W 0x8E

/* ------------ Control Register One ------------ */
#define CONTROL_R_W 0x8F

/* ------------ Configuration Register Two ------------ */
#define CONFIG2_R_W 0x90

/* ------------ ID Register ------------ */
#define ID_R 0x92

/* ------------ Status Register ------------ */
#define STATUS_R 0x93

/* ------------ RGBC Data Register ------------ */
#define CDATAL_R 0x94
#define CDATAH_R 0x95
#define RDATAL_R 0x96
#define RDATAH_R 0x97
#define GDATAL_R 0x98
#define GDATAH_R 0x99
#define BDATAL_R 0x9A
#define BDATAH_R 0x9B

/* ------------ Proximity Data Register ------------ */
#define PDATA_R 0x9C

/* ------------ Proximity Offset UP / RIGHT Register ------------ */
#define POFFSET_UR_R_W 0x9D

/* ------------ Proximity Offset DOWN / LEFT ------------ */
#define POFFSET_DL_R_W 0x9E

/* ------------ Configuration Three Register ------------ */
#define CONFIG3_R_W 0x9F

/* ------------ Gesture Proximity Enter Threshold Register ------------ */
#define GPENTH_R_W 0xA0

/* ------------ Gesture Exit Threshold Register ------------ */
#define GEXTH_R_W 0xA1

/* ------------ Gesture Configuration One Register ------------ */
#define GCONF1_R_W 0xA2

/* ------------ Gesture Configuration Two Register ------------ */
#define GCONF2_R_W 0xA3

/* ------------ Gesture UP Offset Register ------------ */
#define GOFFSET_U_R_W 0xA4

/* ------------ Gesture DOWN Offset Register ------------ */
#define GOFFSET_D_R_W 0xA5

/* ------------ Gesture LEFT Offset Register ------------ */
#define GOFFSET_L_R_W 0xA7

/* ------------ Gesture RIGHT Offset Register ------------ */
#define GOFFSET_R_R_W 0xA9

/* ------------ Gesture Pulse Count and Length Register ------------ */
#define GPULSE_R_W 0xA6

/* ------------ Gesture Configuration Three Register ------------ */
#define GCONF3_R_W 0xAA

/* ------------ Gesture Configuration Four Register ------------ */
#define GCONF4_R_W 0xAB

/* ------------ Gesture FIFO Level Register ------------ */
#define GFLVL_R 0xAE

/* ------------ Gesture Status Register ------------ */
#define GSTATUS_R 0xAF

/* ------------ Clear Interrupt Registers ------------ */
#define IFORCE_W  0xE4
#define PICLEAR_W 0xE5
#define CICLEAR_W 0xE6
#define AICLEAR_W 0xE7

/* ------------ Gesture FIFO Register ------------ */
#define GFIFO_U_R 0xFC
#define GFIFO_D_R 0xFD
#define GFIFO_L_R 0xFE
#define GFIFO_R_R 0xFF

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

int APDS_9960::init( void )
{
    state = DEVICE::state_t::READY;
    return 0;
}

int APDS_9960::deinit( void )
{
    state = DEVICE::state_t::UNINIT;
    return 0;
}

int APDS_9960::on( void )
{
    int e          = 0;
    uint8_t data   = 0x01 | ( 0x01 << 6 );
    uint8_t rdData = 0;

    e = bus->read( ( void * )&rdData, sizeof( rdData ), 1000, addr, 0x92, 1 );
    if ( e < 0 )
    {
        return -ERRNO_ADPS_9960_ON_BUS_WR;
    }

    e = 0;
    e = bus->write( &data, sizeof( data ), 1000, addr, 0x80, 1 );

    if ( e < 0 )
    {
        return -ERRNO_ADPS_9960_ON_BUS_WR;
    }

    this->state = DEVICE::state_t::ON;
    return 0;
}

int APDS_9960::off( void )
{
    state = DEVICE::state_t::OFF;
    return 0;
}

int APDS_9960::sleep( void )
{
    state = DEVICE::state_t::SLEEP;
    return 0;
}
