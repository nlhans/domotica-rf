#ifndef IOCONFIG_H
#define IOCONFIG_H
#define INPUT_PIN           1
#define OUTPUT_PIN          0

#if defined(__PIC24FJ64GB004__)
#define PIC24_HW
#endif

#if defined(__dsPIC33FJ128GP804__)
#define PIC24_HW
#endif

#ifdef PIC24_HW
#include <pps.h>

typedef unsigned char UI08_t;
typedef unsigned int UI16_t;
typedef unsigned long UI32_t;

typedef char I08_t;
typedef int I16_t;
typedef long I32_t;

// PIC24FJ64GB004 / dsPIC33FJ128GP804 main controller

#define SPI_SDO		LATBbits.LATB8		// PIN_F3  SDO
#define SPI_SDI		PORTCbits.RC4		// PIN_F2  SDI
#define SPI_SCK		LATBbits.LATB7		// PIN_E8  SPI clock
#define SPI_CS		LATBbits.LATB5		// PIN_E2  chip select
#define RF_IRQ		PORTBbits.RB9		// PIN_E3  MRF49XA interrupt
#define RF_FSEL		LATCbits.LATC5		// PIN_E5  fifo select, active low output
#define RF_DIO		PORTAbits.RA9		// PIN_E0
#define RF_RES		LATCbits.LATC6		// PIN_B4  MRF49XA reset
//#define RF_RSSIO	PORTEbits.RE1
#define RF_FINT		PORTCbits.RC3		//
#define TRIS_SPI_SDO		TRISBbits.TRISB8		// PIN_F2  SDO (Out to SPI)
#define TRIS_SPI_SDI		TRISCbits.TRISC4		// PIN_F3  SDI (IN from SPI)
#define TRIS_SPI_SCK		TRISBbits.TRISB7		// PIN_E8  SPI clock
#define TRIS_SPI_CS			TRISBbits.TRISB5		// PIN_E2  chip select
#define TRIS_RF_IRQ			TRISBbits.TRISB9		// PIN_D0  MRF49XA interrupt
#define TRIS_RF_FSEL		TRISCbits.TRISC5		// PIN_E5  fifo select, active low output
#define TRIS_RF_DIO			TRISAbits.TRISA9		// PIN_E0
#define TRIS_RF_RES			TRISCbits.TRISC6		// PIN_B4  MRF49XA reset
//#define TRIS_RF_RSSIO		TRISEbits.TRISE1
#define TRIS_RF_FINT		TRISCbits.TRISC3

#else

// PIC16LF1508 / PIC16LF1509 node

#define SPI_SDO		LATBbits.LATB7		// PIN_F3  SDO
#define SPI_SDI		PORTCbits.RC5		// PIN_F2  SDI
#define SPI_SCK		LATCbits.LATC7		// PIN_E8  SPI clock
#define SPI_CS		LATCbits.LATC6		// PIN_E2  chip select
#define RF_IRQ		PORTAbits.RA2		// PIN_E3  MRF49XA interrupt
#define RF_FSEL		LATCbits.LATC4		// PIN_E5  fifo select, active low output
#define RF_DIO		PORTAbits.RA5		// PIN_E0
#define RF_RES		LATAbits.LATA4		// PIN_B4  MRF49XA reset
//#define RF_RSSIO	PORTEbits.RE1
#define RF_FINT		PORTCbits.RC3		//

#define TRIS_SPI_SDO		TRISBbits.TRISB7		// PIN_F2  SDO (Out to SPI)
#define TRIS_SPI_SDI		TRISCbits.TRISC5		// PIN_F3  SDI (IN from SPI)
#define TRIS_SPI_SCK		TRISCbits.TRISC7		// PIN_E8  SPI clock
#define TRIS_SPI_CS		TRISCbits.TRISC6		// PIN_E2  chip select
#define TRIS_RF_IRQ		TRISAbits.TRISA2		// PIN_D0  MRF49XA interrupt
#define TRIS_RF_FSEL		TRISCbits.TRISC4		// PIN_E5  fifo select, active low output
#define TRIS_RF_DIO		TRISAbits.TRISA5		// PIN_E0
#define TRIS_RF_RES		TRISAbits.TRISA4		// PIN_B4  MRF49XA reset
//#define TRIS_RF_RSSIO		TRISEbits.TRISE1
#define TRIS_RF_FINT		TRISCbits.TRISC3

#define Nop() asm("nop");

#endif


#endif