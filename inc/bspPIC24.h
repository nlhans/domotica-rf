#ifndef IOCONFIG_H
#define IOCONFIG_H
#define INPUT_PIN           1
#define OUTPUT_PIN          0

#include <stdint.h>

#ifdef MAIN_C
    #ifdef PIC24GB

    _CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
    _CONFIG2(POSCMOD_NONE & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_ON)
    _CONFIG3(WPFP_WPFP0 & SOSCSEL_IO & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
    _CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_LPRC & DSBOREN_OFF & DSWDTEN_OFF)


    #endif

    #ifdef PIC24GA

    _CONFIG1(WINDIS_OFF & FWDTEN_OFF & ICS_PGx3 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
    _CONFIG2(POSCMOD_NONE & OSCIOFNC_OFF & FCKSM_CSDCMD & FNOSC_FRCPLL & IESO_OFF & I2C1SEL_PRI & IOL1WAY_OFF)
    
    #endif

    #ifdef dsPIC33

    _FBS(BWRP_WRPROTECT_OFF & BSS_NO_FLASH & RBS_NO_RAM)
    _FSS(SWRP_WRPROTECT_OFF & SSS_NO_FLASH & RSS_NO_RAM)
    _FGS(GWRP_OFF & GCP_OFF)
    _FOSCSEL(FNOSC_FRC & IESO_OFF)
    _FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_OFF & FCKSM_CSECME)
    _FWDT(WDTPOST_PS128 & WDTPRE_PR128 & WINDIS_OFF & FWDTEN_OFF)
    _FPOR(FPWRT_PWR1 & ALTI2C_OFF)
    _FICD(ICS_PGD1 & JTAGEN_OFF)

    #endif
#endif

#ifdef PIC24GA
    #define F_OSC_DIV_2 ((UI32_t)16000000)
#include <PPS.h>
#endif
#ifdef PIC24GB
    #define F_OSC_DIV_2 ((UI32_t)8000000)
#include <PPS.h>
#endif
#ifdef dsPIC33
    #define F_OSC_DIV_2 ((UI32_t)7370000/2)
#include <pps.h>
#endif

// ADC
typedef enum Pic16PortDefs_e
{
    PA,
    PB,
    PC,
    PINT
} Pic16PortDefs_t;

typedef enum AdcChannels_e
{
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
    ADC_DAC  = 0b11110,
    ADC_FVR  = 0b11111,
} AdcChannel_t;

#define BSP_TIMER_COUNT 5
#define BSP_EXT_INT_COUNT 3 // This PIC has 3 ext interrupt lines


#define TRUE 1
#define FALSE 0

typedef unsigned char bool_t;
typedef unsigned char UI08_t;
typedef unsigned int UI16_t;
typedef unsigned long UI32_t;

typedef char I08_t;
typedef int I16_t;
typedef long I32_t;
#define __delay_ms(x)
#define __delay_us(x) do { for(i = 0; i < x; i++) asm volatile("nop"); } while(0);

#define GPIO_OUTPUT 0
#define GPIO_INPUT  1

// BSP I/O mapping for 44QFP PIC24/dsPIC33/PIC32
/*************** PORTA *************/
#define FLASH_CS2               LATAbits.LATA0          // out
#define BSP_HUMIDITY_ANALOG_PIN PA, 1                   // A/D
#define BSP_HUMIDITY_CHANNEL    ADC_AN1                 // A/D
#define RF_INT1                 PORTAbits.RA2           // in
#define SYS_DBG_LED             LATAbits.LATA3          // out
                                         // A4 = secondary osc
#define FLASH_CS1               LATAbits.LATA7          // out
#define SENSOR_PWR              LATAbits.LATA8          // out
#define RF_INT2                 PORTAbits.RA9           // in
#define RF_POWER                LATAbits.LATA10         // out

#define SYS_GPIO_INIT_PORTA() do { \
TRISAbits.TRISA0 = GPIO_OUTPUT; \
TRISAbits.TRISA3 = GPIO_OUTPUT; \
TRISAbits.TRISA7 = GPIO_OUTPUT; \
TRISAbits.TRISA8 = GPIO_OUTPUT; \
TRISAbits.TRISA10 = GPIO_OUTPUT; \
TRISAbits.TRISA1 = GPIO_INPUT; \
TRISAbits.TRISA2 = GPIO_INPUT; \
TRISAbits.TRISA9 = GPIO_INPUT; \
} while(0);

/*************** PORTB *************/
                                         // B0 = PGD / UART (TX)
                                         // B1 = PGC / UART (RX)
#define I2C_SCL                 LATBbits.LATB2          // out
#define I2C_SDA                 LATBbits.LATB3          // tri/out
#define I2C_SDA_READ            PORTBbits.RB3           // tri/in
                                         // B4 = secondary osc
#define RF_SPI_CS               LATBbits.LATB5		// out
                                         // B6 = non existing
#define RF_SPI_SCK              LATBbits.LATB7		// out
#define RF_SPI_SDO              LATBbits.LATB8		// out
#define RF_IRQ                  PORTBbits.RB9		// in
                                         // B10 = USB D+
                                         // B11 = USB D-
                                         // B12 = non existing
#define FLASH_SIO3              LATBbits.LATB13          // out
#define FLASH_SCK               LATBbits.LATB14          // out
#define ETH_INT                 PORTBbits.RB15           // in

#define TRIS_I2C_SCL            TRISBbits.TRISB2
#define TRIS_I2C_SDA            TRISBbits.TRISB3

#define SYS_GPIO_INIT_PORTB() do { \
TRISBbits.TRISB0 = GPIO_OUTPUT; \
TRISBbits.TRISB5 = GPIO_OUTPUT; \
TRISBbits.TRISB7 = GPIO_OUTPUT; \
TRISBbits.TRISB8 = GPIO_OUTPUT; \
TRISBbits.TRISB13 = GPIO_OUTPUT; \
TRISBbits.TRISB14 = GPIO_OUTPUT; \
TRISBbits.TRISB1 = GPIO_INPUT; \
TRISBbits.TRISB9 = GPIO_INPUT; \
TRISBbits.TRISB15 = GPIO_INPUT; \
} while(0);


/*************** PORTC *************/
#define FLASH_SIO0                                      // out
#define FLASH_SIO2              LATCbits.LATC1          // out
#define FLASH_SIO1                                      // in
#define RF_FINT                 PORTCbits.RC3           // in?
#define RF_SPI_SDI              PORTCbits.RC4		// in
#define RF_FSEL                 LATCbits.LATC5		// out / fifo select
#define RF_RES                  LATCbits.LATC6		// out
#define ETH_RES                 LATCbits.LATC7          // out
#define ETH_CS                  LATCbits.LATC8          // out
#define ETH_WOL                 PORTCbits.RC9           // in

#define SYS_GPIO_INIT_PORTC() do { \
TRISCbits.TRISC0 = GPIO_OUTPUT; \
TRISCbits.TRISC1 = GPIO_OUTPUT; \
TRISCbits.TRISC5 = GPIO_OUTPUT; \
TRISCbits.TRISC6 = GPIO_OUTPUT; \
TRISCbits.TRISC7 = GPIO_OUTPUT; \
TRISCbits.TRISC8 = GPIO_OUTPUT; \
TRISCbits.TRISC2 = GPIO_INPUT; \
TRISCbits.TRISC3 = GPIO_INPUT; \
TRISCbits.TRISC4 = GPIO_INPUT; \
TRISCbits.TRISC9 = GPIO_INPUT; \
} while(0);


#define PIC24_HW


#endif