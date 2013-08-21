/*********************************************************************
 *
 *                DCC Command Station Firmware Version 1.0
 *
 *********************************************************************
 * FileName:        main.c
 * Dependencies:    See INCLUDES section below
 * Processor:       dsPIC30F3012
 * Compiler:        C30 3.05 +
 * Company:         My personal use
 *
 * Notes:						
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ernesto Pareja       29/12/2009    Original.
 ********************************************************************/

/** I N C L U D E S **********************************************************/
#include <xc.h>
#include <pps.h>
#include <stdio.h>
#include "MRF49XA.h"
#include "IOConfig.h"
#include "utilidades.h"

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

typedef struct {
	unsigned PacketReady		: 1;
	unsigned ResetRadio			: 1;
} TFlags;

TRFData rfData;
char PacketLen;
TFlags Flags;

void initRFPorts(void){
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
}

void UartInit()
{
    U1MODE = 0b1000000000000000;
    U1STA = 0b0000010000000000;
    U1BRG = 51; // 115k2 @ FRCPLL stock
    PORTB &= ~(1<<0);

    PPSUnLock;
    iPPSOutput(OUT_PIN_PPS_RP0, OUT_FN_PPS_U1TX);
    PPSLock;
}
/************* START OF MAIN FUNCTION ***************/
int main ( void ){
#if defined(__PIC24FJ64GB004__)
    AD1PCFG = 0xFFFF;
#else
	ADPCFG = 0xFFFF; // Ports as digital, not analog
#endif
        
        unsigned long i, j;
//	char lenght;
        char PackState;
	char powerState;

        UartInit();
	initRFPorts();

        TRISA &= ~(1<<10);
        LATA |= 1<<10;

        printf("MRF49XA DEMO\r\n");
	MRF49XA_Init();
	InitRFData(&rfData);
	powerState = 0;

            for (i = 0; i < 100; i++)
                for (j = 0; j < 1000; j++)
                    asm volatile("nop");
            
        MRF49XA_Reset_Radio();
        
	while (1) {


#ifdef TRANSMITTER
            for (i = 0; i < 100; i++)
                for (j = 0; j < 1000; j++)
                    asm volatile("nop");
            
            powerState ^= 1; // Toggle powerState
            AddRFData(&rfData,0x12); // First Payload Byte
            AddRFData(&rfData,0x34); // Second Payload Byte
            AddRFData(&rfData,0x56); // Second Payload Byte
            AddRFData(&rfData,0x78); // Second Payload Byte
            AddRFData(&rfData,powerState); // Second Payload Byte
            MRF49XA_Send_Packet(&rfData);
            InitRFData(&rfData);

            printf("TX\r\n");

#else

            RF_FSEL = 1;
	SPI_SDO = 0;
	SPI_CS	=0;							// chip select low
	Nop();
	while(!SPI_SDI);

            PackState = MRF49XA_Receive_Packet(&rfData);
            switch (PackState) {
                    case PACKET_RECEIVED: {

                            for(i = 0; i < rfData.len; i++)
                                printf("0x%02X ", rfData.buffer[i]);
                            printf("\r\n");

                            if (rfData.buffer[rfData.len-1] == CalChkSum(rfData.buffer,rfData.len-1)) {
                                printf("Checksum Y\r\n");
                            } else {
                                printf("Checksum N\r\n");
                            }

                            printf("Packet\r\n");
                            InitRFData(&rfData); // clears indexes
                            break;
                    }

                case NODATA:
                    i++;
                    if (i > 100)
                    {
                        i=0;
                        Flags.ResetRadio = 1;
                    }
                    break;
            }
#endif
		
		if (Flags.ResetRadio == 1) {		
			InitRFData(&rfData);
			MRF49XA_Reset_Radio();
		}
			
	}	
}

