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
#ifdef MAIN_C
__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_ON & MCLRE_ON & CP_OFF & BOREN_OFF & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF);
__CONFIG(WRT_ALL & STVREN_ON & BORV_HI & LPBOR_OFF & LVP_OFF);
#endif

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

#define GPIO_OUTPUT 0
#define GPIO_INPUT  1

// BSP I/O mapping for 20SSOP PIC16F150(8/9)
/*************** PORTA *************/
#define RF_IRQ                  PORTAbits.RA2		// in
#define RF_RES                  LATAbits.LATA4		// out
#define RF_INT                  LATAbits.LATA5		// out

#define SYS_GPIO_INIT_PORTA() do { \
TRISAbits.TRISA2 = GPIO_INPUT; \
TRISAbits.TRISA4 = GPIO_OUTPUT; \
TRISAbits.TRISA5 = GPIO_OUTPUT; \
RF_RES = 0; \
RF_INT = 0; \
} while(0);

/*************** PORTB *************/
#define I2C_SCL                 LATBbits.LATB4          // out
#define I2C_SDA                 LATBbits.LATB6          // tri/out
#define I2C_SDA_READ            PORTBbits.RB6        // tri/in

#define UART_RX                 PORTBbits.RB5        // in

#define RF_SPI_SDO              LATBbits.LATB7          // out

#define TRIS_I2C_SCL            TRISBbits.TRISB4
#define TRIS_I2C_SDA            TRISBbits.TRISB6

#define SYS_GPIO_INIT_PORTB() do { \
TRISBbits.TRISB4 = GPIO_OUTPUT; \
TRISBbits.TRISB6 = GPIO_OUTPUT; \
TRISBbits.TRISB7 = GPIO_OUTPUT; \
TRISBbits.TRISB5 = GPIO_INPUT; \
} while(0);


/*************** PORTC *************/
#define BSP_HUMIDITY_ANALOG_PIN      PC, 0              // A/D
#define BSP_HUMIDITY_CHANNEL         ADC_AN4            // A/D

#define RF_POWER                LATCbits.LATC1          // out
#define SENSOR_PWR              LATCbits.LATC2          // out
#define RF_FINT                 PORTCbits.RC3           // in
#define RF_FSEL                 LATCbits.LATC4          // out
#define RF_SPI_SDI              PORTCbits.RC5           // in
#define RF_SPI_CS               LATCbits.LATC6          // out
#define RF_SPI_SCK              LATCbits.LATC7          // out

#define SYS_GPIO_INIT_PORTC() do { \
TRISCbits.TRISC1 = GPIO_OUTPUT; \
TRISCbits.TRISC2 = GPIO_OUTPUT; \
TRISCbits.TRISC4 = GPIO_OUTPUT; \
TRISCbits.TRISC6 = GPIO_OUTPUT; \
TRISCbits.TRISC7 = GPIO_OUTPUT; \
TRISCbits.TRISC0 = GPIO_INPUT; \
TRISCbits.TRISC3 = GPIO_INPUT; \
TRISCbits.TRISC5 = GPIO_INPUT; \
RF_POWER = 0; \
SENSOR_PWR = 0; \
RF_FSEL = 0; \
RF_SPI_CS = 1; \
RF_SPI_SCK = 0; \
} while(0);

/*
#define SENSOR_PWR      LATCbits.LATC2
#define SPI_SDO		LATBbits.LATB7		// PIN_F3  SDO
#define SPI_SDI		PORTCbits.RC5		// PIN_F2  SDI
#define SPI_SCK		LATCbits.LATC7		// PIN_E8  SPI clock
#define SPI_CS		LATCbits.LATC6		// PIN_E2  chip select
#define RF_IRQ		PORTAbits.RA2		// PIN_E3  MRF49XA interrupt
#define RF_FSEL		LATCbits.LATC4		// PIN_E5  fifo select, active low output
#define RF_DIO		PORTAbits.RA5		// PIN_E0
#define RF_RES		LATAbits.LATA4		// PIN_B4  MRF49XA reset
#define RF_FINT		PORTCbits.RC3		//
#define RF_POWER        LATCbits.LATC1

#define TRIS_SENSOR_PWR         TRISCbits.TRISC2                // Pin C2 Sensor power (Temp + Humid)
#define TRIS_SPI_SDO		TRISBbits.TRISB7		// PIN_F2  SDO (Out to SPI)
#define TRIS_SPI_SDI		TRISCbits.TRISC5		// PIN_F3  SDI (IN from SPI)
#define TRIS_SPI_SCK		TRISCbits.TRISC7		// PIN_E8  SPI clock
#define TRIS_SPI_CS		TRISCbits.TRISC6		// PIN_E2  chip select
#define TRIS_RF_IRQ		TRISAbits.TRISA2		// PIN_D0  MRF49XA interrupt
#define TRIS_RF_FSEL		TRISCbits.TRISC4		// PIN_E5  fifo select, active low output
#define TRIS_RF_DIO		TRISAbits.TRISA5		// PIN_E0
#define TRIS_RF_RES		TRISAbits.TRISA4		// PIN_B4  MRF49XA reset
#define TRIS_RF_FINT		TRISCbits.TRISC3
#define TRIS_RF_POWER           TRISCbits.TRISC1*/

#define Nop() asm("nop");

#endif
