#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#define NO_ERROR 0

// Bit 31:24 for bus error
#define ERRNO_BUS_TYPE_POS  28 // Bit 30:28
#define ERRNO_BUS_ERROR_POS 24 // Bit 27:24
#define ERRNO_BUS_MASK      ( 0x7F000000 )
#define ERRNO_BASE_BUS_I2C  ( ( 1U & 0x07 ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_SPI  ( ( 2U & 0x07 ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_UART ( ( 3U & 0x07 ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_SAI  ( ( 4U & 0x07 ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_I2S  ( ( 5U & 0x07 ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_CAN  ( ( 6U & 0x07 ) << ERRNO_BUS_TYPE_POS )
#define ERRNO_BASE_BUS_USB  ( ( 7U & 0x07 ) << ERRNO_BUS_TYPE_POS )

#define BUS_ERR( __v ) ( ( __v & ( 0x0F ) ) << ERRNO_BUS_ERROR_POS )

#define ERR_I2C_WR     ( BUS_ERR( 1U ) | ERRNO_BASE_BUS_I2C )
#define ERR_I2C_WR_DMA ( BUS_ERR( 2U ) | ERRNO_BASE_BUS_I2C )
#define ERR_I2C_RD     ( BUS_ERR( 3U ) | ERRNO_BASE_BUS_I2C )
#define ERR_I2C_RD_DMA ( BUS_ERR( 4U ) | ERRNO_BASE_BUS_I2C )

// Bit 23:15 for domain of the error
#define ERRNO_DOMAIN_TYPE_POS 16 // Bit 23:16
#define ERRNO_DOMAIN_MASK     0x00FF0000

/* ADPS-9960 */
#define ERRNO_DOMAIN_ADPS_9960 ( ( 1U & 0xFF ) << ERRNO_DOMAIN_TYPE_POS )
#define ERR_APDS_9960( __v )                                                   \
    ( ( ( __v & 0xFFFF ) << ERRNO_ERROR_POS ) | ERRNO_DOMAIN_ADPS_9960 )
#define ERRNO_ADPS_9960_ON_BUS_WR          ( ERR_I2C_WR | ERR_APDS_9960( 1 ) )
#define ERRNO_ADPS_9960_READ_ID_BUS_RD     ( ERR_I2C_RD | ERR_APDS_9960( 2 ) )
#define ERRNO_ADPS_9960_READ_ID_WRONG      ( ERR_APDS_9960( 3 ) )
#define ERRNO_ADPS_9960_OFF_BUS_WR         ( ERR_I2C_WR | ERR_APDS_9960( 4 ) )
#define ERRNO_ADPS_9960_IRQ_STATUS_BUS_RD  ( ERR_I2C_RD | ERR_APDS_9960( 5 ) )
#define ERRNO_ADPS_9960_IRQ_RGBC_BUS_RD    ( ERR_I2C_RD | ERR_APDS_9960( 6 ) )
#define ERRNO_ADPS_9960_IRQ_PICLEAR_BUS_WR ( ERR_I2C_WR | ERR_APDS_9960( 7 ) )
#define ERRNO_ADPS_9960_IRQ_CICLEAR_BUS_WR ( ERR_I2C_WR | ERR_APDS_9960( 8 ) )
#define ERRNO_ADPS_9960_IRQ_AICLEAR_BUS_WR ( ERR_I2C_WR | ERR_APDS_9960( 9 ) )

// Bit 15:0 for the specific reason/state of the error
#define ERRNO_ERROR_POS  0 // Bit 0:15
#define ERRNO_ERROR_MASK 0x0000FFFF

#endif // __ERROR_HPP__