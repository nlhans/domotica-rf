#include <xc.h>
#include <stdio.h>
#include "MRF49XA.h"
#include "IOConfig.h"

#ifdef PIC24_HW
#if defined(__PIC24FJ64GB004__)

_CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
_CONFIG2(POSCMOD_NONE & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_ON)
_CONFIG3(WPFP_WPFP0 & SOSCSEL_IO & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
_CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_LPRC & DSBOREN_OFF & DSWDTEN_OFF)


#else

_FBS(BWRP_WRPROTECT_OFF & BSS_NO_FLASH & RBS_NO_RAM)
_FSS(SWRP_WRPROTECT_OFF & SSS_NO_FLASH & RSS_NO_RAM)
_FGS(GWRP_OFF & GCP_OFF)
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF)
_FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_OFF & FCKSM_CSECME)
_FWDT(WDTPOST_PS128 & WDTPRE_PR128 & WINDIS_OFF & FWDTEN_OFF)
_FPOR(FPWRT_PWR1 & ALTI2C_OFF)
_FICD(ICS_PGD2 & JTAGEN_OFF)

#endif
#else
#define TRANSMITTER

 #define _XTAL_FREQ 16000000

 __CONFIG( FOSC_INTOSC & WDTE_OFF & PWRTE_ON & MCLRE_ON & CP_OFF & BOREN_OFF & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF  );
 __CONFIG( WRT_ALL & STVREN_ON & BORV_HI & LPBOR_OFF & LVP_OFF );

#include <xc.h>

#endif


 const UI16_t humids30c[15] = {65535, 39000, 20000, 9800, 4700, 1310, 770, 440, 250, 170, 105, 72, 50, 36, 25 };
 
void initRFPorts(void)
{
    TRIS_SPI_SDI 	= INPUT_PIN;
    TRIS_SPI_SDO 	= OUTPUT_PIN;
    TRIS_SPI_SCK 	= OUTPUT_PIN;
    TRIS_SPI_CS  	= OUTPUT_PIN;
    TRIS_RF_IRQ		= INPUT_PIN;
    TRIS_RF_FSEL	= OUTPUT_PIN;
    TRIS_RF_DIO		= INPUT_PIN;
    TRIS_RF_RES		= OUTPUT_PIN;
    TRIS_RF_FINT	= INPUT_PIN;
    TRIS_RF_IRQ		= INPUT_PIN;
    TRIS_RF_POWER       = OUTPUT_PIN;
}

void UartInit()
{
#ifdef PIC24_HW
    U1MODE = 0b1000000000000000;
    U1STA = 0b0000010000000000;
    U1BRG = 51; // 115k2 @ FRCPLL stock
    PORTB &= ~(1<<0);
    PORTB |= 1<<1;
    PPSUnLock;
    iPPSOutput(OUT_PIN_PPS_RP0, OUT_FN_PPS_U1TX);
    iPPSInput(IN_FN_PPS_U1RX, IN_PIN_PPS_RP1);
    PPSLock;
#endif
}

void TimInit(void)
{
    // 16MHz/4 Fclk
    // -> 2kHz
    OPTION_REG = 0b00000011;
    // div by 16 -> 125 tmr value
    TMR0 = 255-125;

    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    //INTCONbits.GIE = 1;
}

#define SENSOR_PWR LATCbits.LATC2

int enableHumidPower = 0;

void interrupt isr()
{
    // Timer 0
    INTCONbits.TMR0IF = 0;
    if(enableHumidPower == 0)
    {
        SENSOR_PWR = 0;
    }
    else
    {
        if (SENSOR_PWR != 0)
        {
            SENSOR_PWR = 0;
        }
        else
        {
            SENSOR_PWR = 1;
        }
    }
    TMR0 = 255-125;
}

void AdcInit(void)
{
    // PIC16
    // 16M -> Fosc/64 = 4us
    // 1M -> Fosc/4 = 4us

    FVRCON = 0b11100001;
    ADCON2 = 0b00000000;
    ADCON1 = 0b11110000;
    ADCON0 = 0b00000000;

    ADCON0 = 0b00010011;
}

UI08_t buffer[16];

#include "math.h"
void AdcConvert(void)
{
    UI16_t temp;
    UI16_t sensor;
    
    //LATC |= 1<<2;

    //enableHumidPower = 1;

    SENSOR_PWR = 1;
    ADCON0 = 0b00010011;
    __delay_ms(100);
    temp = (ADRESH << 8) | ADRESL;
    ADCON0 = 0b00010011;
    while ((ADCON0 & 0x2));
    temp += (ADRESH << 8) | ADRESL;
    SENSOR_PWR = 0;

    sensor=temp / 2;

    buffer[0] = ADRESH;
    buffer[1] = ADRESL;

    ADCON0 = 0b01111111;
    __delay_us(200);
    while (ADCON0 & 0x2);
    ADCON0 = 0b01111111;
    while (ADCON0 & 0x2);

    buffer[2] = ADRESH;
    buffer[3] = ADRESL;
    temp = (ADRESH << 8) | ADRESL;

    ADCON0 = 0b01110111;
    while (ADCON0 & 0x2);
    __delay_us(200);
    ADCON0 = 0b01110111;
    while (ADCON0 & 0x2);

    temp = (ADRESH << 8) | ADRESL;
    temp = (temp - 480) * 100 / 120 - 43;
    temp = 29;
    buffer[4] = ADRESH;
    buffer[5] = ADRESL;
    buffer[6] = temp;

    float voltage = (sensor/1023.0);
    float ntcResistance = 47*pow(1/1.044, buffer[6]-25);
    float humidityResistance = (1/(1/voltage - 1)) * ntcResistance * 10;

    UI16_t iHumidityResistance = (UI16_t) humidityResistance;
    buffer[7] = iHumidityResistance >> 8;
    buffer[8] = iHumidityResistance & 0xFF;

    UI08_t ii = 0;

    while(ii < 14)
    {
        if (humids30c[ii+1] <= iHumidityResistance && humids30c[ii] >= ii)
        {
            // GOOD
            float part = (humids30c[ii] - iHumidityResistance) / ((float)humids30c[ii+1] - humids30c[ii]);
            float humidity = part*5 + 20 + ii * 5;
            buffer[9] = (UI08_t) humidity;
            break;
        }
        ii++;
    }
}

int main ( void ){
    UI08_t i, j,k;
    #ifdef PIC24_HW
        #if defined(__PIC24FJ64GB004__)
        AD1PCFG = 0xFFFF;
        #else
        ADPCFG = 0xFFFF; // Ports as digital, not analog
        #endif
    #else
        OSCCON = 0b01111000;
        
        TRISC |= 1<<0; // Humidity
        TRISC &= ~(1<<2);
        TRISA &= ~(1<<0);
        TRISA &= ~(1<<1);
        
        ANSELA = 0;
        ANSELB = 0;
        ANSELC = (1<<0); // RC0, AN4
    #endif

    TimInit();
    AdcInit();

    UartInit();
    initRFPorts();
    
    RF_POWER = 1;

    MRF49XA_Init();
    //printf("Hi\r\n");
    Mrf49XaDelay(2);
    Mrf49XaDelay(2);
    
    MRF49XA_Reset_Radio();

    while (1)
    {
        #ifdef TRANSMITTER

        PORTA |= 1<<0;
        AdcConvert();
        PORTA &= ~(1<<0);

        PORTA |= 1<<1;
        
        MRF49XA_TxPacket(buffer, 10);
        PORTA &= ~(1<<1);
        for(k=0;k<30;k++)
            Mrf49XaDelay(2);

        //printf("Tx\r\n");
        
        #else

        i = MRF49XA_RxPacket(buffer);

        if (i != 0)
        {
            if ((i & 0x80) == 0)
            {
                printf("CRC Y\t");
            }
            else
            {
                printf("CRC N\t");
            }
            
            for(j = 0; j < (i&0x7F); j++)
            {
                printf("0x%02X ", buffer[j]);
            }

            printf("\r\n");
        }
        #endif

    }
}

