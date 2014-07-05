#ifndef IOCONFIG_H
#define IOCONFIG_H

// GPIO's
#define INPUT_PIN           1
#define OUTPUT_PIN          0

// ADC

typedef enum Pic16PortDefs_e {
    PA,
    PB,
    PC,
    PINT
} Pic16PortDefs_t;

typedef enum AdcChannels_e {
    ADC_AN0 = 0,
    ADC_AN1,
    ADC_AN2,
    ADC_AN3,
    ADC_AN4,
    ADC_AN5,
    ADC_AN6,
    ADC_AN7,
    ADC_AN8,
    ADC_AN9,
    ADC_AN10,
    ADC_AN11,
    ADC_TEMP = 0b11101,
    ADC_DAC = 0b11110,
    ADC_FVR = 0b11111,
} AdcChannel_t;

// Compile the BSP c files
#define ADC16_C

// Process clocking & fuse bits
#define _XTAL_FREQ 16000000

#define TRUE 1
#define FALSE 0

// Standard types
typedef unsigned char bool_t;
typedef unsigned char UI08_t;
typedef unsigned int UI16_t;
typedef unsigned long UI32_t;

typedef char I08_t;
typedef int I16_t;
typedef long I32_t;

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef char int8_t;
typedef int int16_t;
typedef long int32_t;

#define GPIO_OUTPUT 0
#define GPIO_INPUT  1

// BSP I/O mapping for 20SSOP PIC16F150(8/9)
/*************** PORTA *************/
#define RF_IRQ                  PORTAbits.RA2		// in
#define RF_RES                  LATAbits.LATA4		// out
#define RF_INT                  LATAbits.LATA5		// out

/*************** PORTB *************/
#define I2C_SCL                 LATBbits.LATB6          // out
#define I2C_SDA                 LATBbits.LATB4          // tri/out
#define I2C_SDA_READ            PORTBbits.RB4        // tri/in

#define UART_RX                 PORTBbits.RB5        // in

#define RF_SPI_SDO              PORTBbits.RB7          // out

#define TRIS_I2C_SCL            TRISBbits.TRISB6
#define TRIS_I2C_SDA            TRISBbits.TRISB4

/*************** PORTC *************/
#define BSP_HUMIDITY_ANALOG_PIN      PC, 0              // A/D
#define BSP_HUMIDITY_CHANNEL         ADC_AN4            // A/D

#define MRF49XA_POWER_SWITCH
#ifdef RF_PWR_NFET
#define RF_PWR_ON 1
#define RF_PWR_OFF 0
#else
#define RF_PWR_ON 0
#define RF_PWR_OFF 0 // TODO: Temporarely!
#endif

#define RF_POWER                LATCbits.LATC1          // out
#define SENSOR_PWR              LATCbits.LATC2          // out
#define RF_FINT                 PORTCbits.RC3           // in
#define RF_FSEL                 LATCbits.LATC4          // out
#define RF_SPI_SDI              PORTCbits.RC5           // in
#define RF_SPI_CS               PORTCbits.RC6           // out
#define RF_SPI_SCK              LATCbits.LATC7          // out
//#define RF_SPI_SCK              PORTCbits.RC7          // out

#define Nop() asm("nop");

#endif
