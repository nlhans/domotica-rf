/*********************************************************************
 * FileName:        IOConfig.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 3.05 +
 * Company:         Microchip Technology, Inc.
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ernesto Pareja       23/12/07    Original.
 ********************************************************************/


/** T R I S *********************************************************/
#define INPUT_PIN           1
#define OUTPUT_PIN          0


/** D C C   S I G N A L **********************************************/
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




