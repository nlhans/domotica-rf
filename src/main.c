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

#define TRANSMITTER

#endif
#else
#define TRANSMITTER

#endif

typedef struct
{
    unsigned PacketReady		: 1;
    unsigned ResetRadio		: 1;
} TFlags;

char PacketLen;
TFlags Flags;

char PackState;
char powerState;

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

UI08_t buffer[16];

int main ( void ){
    UI08_t i, j;
    #ifdef PIC24_HW
        #if defined(__PIC24FJ64GB004__)
        AD1PCFG = 0xFFFF;
        #else
        ADPCFG = 0xFFFF; // Ports as digital, not analog
        #endif
    #endif

    UartInit();
    initRFPorts();
    
    RF_POWER = 1;

    MRF49XA_Init();
    printf("Hi\r\n");
    Mrf49XaDelay(1);
    
    MRF49XA_Reset_Radio();

    while (1)
    {
        #ifdef TRANSMITTER

        buffer[0] = 0x12;
        buffer[1] = 0x34;
        buffer[2] = 0x56;
        buffer[3] = 0x78;
        buffer[4] = 0x90;
        buffer[5] = 0xAB;
        buffer[6] = 0xCD;
        buffer[7] = 0xEF;

        MRF49XA_TxPacket(buffer, 8);
        
        printf("Tx\r\n");
        
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

