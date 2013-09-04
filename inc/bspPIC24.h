#ifndef IOCONFIG_H
#define IOCONFIG_H
#define INPUT_PIN           1
#define OUTPUT_PIN          0

#ifdef MAIN_C
    #ifdef PIC24

    _CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
    _CONFIG2(POSCMOD_NONE & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_ON)
    _CONFIG3(WPFP_WPFP0 & SOSCSEL_IO & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
    _CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_LPRC & DSBOREN_OFF & DSWDTEN_OFF)


    #endif

    #ifdef dsPIC33

    _FBS(BWRP_WRPROTECT_OFF & BSS_NO_FLASH & RBS_NO_RAM)
    _FSS(SWRP_WRPROTECT_OFF & SSS_NO_FLASH & RSS_NO_RAM)
    _FGS(GWRP_OFF & GCP_OFF)
    _FOSCSEL(FNOSC_FRCPLL & IESO_OFF)
    _FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_OFF & FCKSM_CSECME)
    _FWDT(WDTPOST_PS128 & WDTPRE_PR128 & WINDIS_OFF & FWDTEN_OFF)
    _FPOR(FPWRT_PWR1 & ALTI2C_OFF)
    _FICD(ICS_PGD2 & JTAGEN_OFF)

    #endif
#endif


#include <pps.h>

typedef unsigned char UI08_t;
typedef unsigned int UI16_t;
typedef unsigned long UI32_t;

typedef char I08_t;
typedef int I16_t;
typedef long I32_t;

// PIC24FJ64GB004 / dsPIC33FJ128GP804 main controller

#define SPI_SDO                 LATBbits.LATB8		// PIN_F3  SDO
#define SPI_SDI                 PORTCbits.RC4		// PIN_F2  SDI
#define SPI_SCK                 LATBbits.LATB7		// PIN_E8  SPI clock
#define SPI_CS                  LATBbits.LATB5		// PIN_E2  chip select
#define RF_IRQ                  PORTBbits.RB9		// PIN_E3  MRF49XA interrupt
#define RF_FSEL                 LATCbits.LATC5		// PIN_E5  fifo select, active low output
#define RF_DIO                  PORTAbits.RA9		// PIN_E0
#define RF_RES                  LATCbits.LATC6		// PIN_B4  MRF49XA reset
#define RF_FINT                 PORTCbits.RC3
#define RF_POWER                LATAbits.LATA10

#define TRIS_SPI_SDO		TRISBbits.TRISB8	// PIN_F2  SDO (Out to SPI)
#define TRIS_SPI_SDI		TRISCbits.TRISC4	// PIN_F3  SDI (IN from SPI)
#define TRIS_SPI_SCK		TRISBbits.TRISB7	// PIN_E8  SPI clock
#define TRIS_SPI_CS		TRISBbits.TRISB5	// PIN_E2  chip select
#define TRIS_RF_IRQ		TRISBbits.TRISB9	// PIN_D0  MRF49XA interrupt
#define TRIS_RF_FSEL		TRISCbits.TRISC5	// PIN_E5  fifo select, active low output
#define TRIS_RF_DIO		TRISAbits.TRISA9	// PIN_E0
#define TRIS_RF_RES		TRISCbits.TRISC6	// PIN_B4  MRF49XA reset
#define TRIS_RF_FINT		TRISCbits.TRISC3
#define TRIS_RF_POWER           TRISAbits.TRISA10



#endif