#ifndef __MRF49XA_H
#define __MRF49XA_H

#include "stddefs.h"

#define RF_NETWORKID1 0x2D
#define RF_NETWORKID2 0xD4
#define RF_NETWORKID3 0x6B

#define MRF49XA_WaitOnTx() do { while (!RF_SPI_SDI); } while (0);

#define PACKET_SIZE_MAX         20              // 8x2 bytes + 4 bytes header/footer

#define GENCREG 		0x8000 | XTAL_LD_CAP_125 | FREQ_BAND_868		// Cload=12.5pF TX registers & FIFO are disabled
#define PMCREG 			0x8200		// Everything off, uC clk enabled
#define	RXCREG                 (0x9460 | LNA_GAIN_0_DB | RSSI_THRESHOLD_103)
#define TXBREG 			0xB800
#define FIFORSTREG              0xCA81		// clear the sync latch enabled, limit=8bits, disable sensitive reset
#define BBFCREG 		0xC2AC		// Digital LPF (default), Automatic Recovery Clock
#define AFCCREG			0xC4D7		// Auto AFC (default) , +15/-16 Fres, Output enable
#define CFSREG 			0xA860		// Fo=915.000MHz (default)
#define TXCREG			0x9890		// df=150kHz, Pmax, normal modulation polarity
#define DRSREG 			0xC611		// 9579Baud (default)
#define	SYNBREG			0xCED4		// Syncronization Pattern (default 0xCED4)

typedef enum Mrf49XARxState_e
{
    RX_STATE_NONE,
    RX_STATE_DATA,
    RX_STATE_PACKET
} Mrf49XARxState_t;

typedef struct
{
    UI08_t buffer[PACKET_SIZE_MAX];
    UI08_t index;               // Contains the array index
    UI08_t len;                 // Real array length
    UI08_t ChkSum;                // For storing 14, 28 and 128 bit speeds
} TRFData;

#define	FREQ_BAND_433			0x0010       //    433 MHz
#define FREQ_BAND_868			0x0020       //    868 MHz
#define FREQ_BAND_915			0x0030       //    915 MHz

#define XTAL_LD_CAP_85			0x0000
#define XTAL_LD_CAP_9			0x0001
#define XTAL_LD_CAP_95			0x0002
#define XTAL_LD_CAP_10			0x0003
#define XTAL_LD_CAP_105			0x0004
#define XTAL_LD_CAP_11			0x0005
#define XTAL_LD_CAP_115			0x0006
#define XTAL_LD_CAP_12			0x0007
#define XTAL_LD_CAP_125			0x0008
#define XTAL_LD_CAP_13			0x0009
#define XTAL_LD_CAP_135			0x000A
#define XTAL_LD_CAP_14			0x000B
#define XTAL_LD_CAP_145			0x000C
#define XTAL_LD_CAP_15			0x000D
#define XTAL_LD_CAP_155			0x000E
#define XTAL_LD_CAP_16			0x000F    

#define LNA_GAIN_0_DB			0x0000
#define LNA_GAIN_N_6_DB			0x0008
#define LNA_GAIN_N_14_DB		0x0010
#define LNA_GAIN_N_20_DB 		0x0018


#define TX_POWER_0_DB			0x0000
#define TX_POWER_N_2_5_DB               0x0001
#define TX_POWER_N_5_DB			0x0002
#define TX_POWER_N_7_5_DB		0x0003
#define TX_POWER_N_10_DB		0x0004
#define TX_POWER_N_12_5_DB              0x0005
#define TX_POWER_N_15_DB		0x0006
#define TX_POWER_N_17_5_DB              0x0007

#define RSSI_THRESHOLD_103              0x0000
#define RSSI_THRESHOLD_97               0x0001
#define RSSI_THRESHOLD_91               0x0002
#define RSSI_THRESHOLD_85               0x0003
#define RSSI_THRESHOLD_79               0x0004
#define RSSI_THRESHOLD_73               0x0005

//#ifdef PIC16
    UI08_t SPI_Read(void);
    void SPI_Write(UI08_t data);
//#else
#ifdef JHAHAHA
    #include "bsp/spi.h"
    

    // On PIC24 we use SPI HAL in combination with ENC28J60
    #define MRF49XA_PORT 1

    #define SPI_Read() spiRxByte(MRF49XA_PORT)
    #define SPI_Write(a) spiTxByte(MRF49XA_PORT, a);
#endif

void MRF49XAInit();
void MRF49XAReset(void);
void MRF49XACommand(UI16_t spicmd);
UI16_t MRF49XAReadStatus();


void RfTrcvPut(UI08_t byte);
UI08_t RfTrcvGet(void);
UI08_t RfTrcvCrcTick(UI08_t initial, UI08_t data);
void RfTrcvRearm(void);

/*
void MRF49XA_TxPacket(UI08_t *data, UI08_t size);
UI08_t MRF49XA_RxPacket(UI08_t *data);
*/
#endif
