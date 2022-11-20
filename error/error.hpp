#ifndef __ERROR_HPP__
#define __ERROR_HPP__

// Bit 31:24 for bus error
#define ERRNO_BUS_TYPE_POS   28 // Bit 31:28
#define ERRNO_BUS_ERROR_POS  24 // Bit 27:24
#define ERRNO_BUS_TYPE_MASK  0xF0000000
#define ERRNO_BUS_ERROR_MASK 0x0F000000
#define ERRNO_BUS_MASK       ( ERRNO_BUS_TYPE_MASK | ERRNO_BUS_ERROR_MASK )
#define ERRNO_BASE_BUS_I2C   ( ( 1U & 0x0F ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_SPI   ( ( 2U & 0x0F ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_UART  ( ( 3U & 0x0F ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_SAI   ( ( 4U & 0x0F ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_I2S   ( ( 5U & 0x0F ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_CAN   ( ( 6U & 0x0F ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_USB   ( ( 7U & 0x0F ) << ERRNO_BUS_TYPE_POS )

// Bit 23:15 for domain of the error
#define ERRNO_DOMAIN_TYPE_POS  16 // Bit 23:16
#define ERRNO_DOMAIN_MASK      0x00FF0000

/* ADPS-9960 */
#define ERRNO_DOMAIN_ADPS_9960 ( ( 1U & 0xFF ) << ERRNO_DOMAIN_TYPE_POS )

// Bit 15:0 for the specific reason/state of the error
#define ERRNO_ERROR_POS  0 // Bit 0:15
#define ERRNO_ERROR_MASK 0x0000FFFF

#endif // __ERROR_HPP__