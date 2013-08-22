
#if !defined(__MRF49XA_H)
#define __MRF49XA_H

#include "GenericTypeDefs.h"
#include "ioconfig.h"
#include "ConfigMRF49XA.h"


#define GENCREG 		0x8000 | XTAL_LD_CAP_125 | FREQ_BAND_868		// Cload=12.5pF TX registers & FIFO are disabled
#define PMCREG 			0x8200		// Everything off, uC clk enabled
#define	RXCREG      (0x9460 | LNA_GAIN | RSSI_THRESHOLD)
//	#define RXCREG 			0x94A1		// BW=135kHz, DRSSI=-97dBm, pin8=VDI, fast VDI
#define TXBREG 			0xB800
#define FIFORSTREG	0xCA81		// clear the sync latch enabled, limit=8bits, disable sensitive reset
#define BBFCREG 		0xC2AC		// Digital LPF (default), Automatic Recovery Clock
#define AFCCREG			0xC4D7		// Auto AFC (default) , +15/-16 Fres, Output enable
#define CFSREG 			0xA860		// Fo=915.000MHz (default)
#define TXCREG			0x9890		// df=150kHz, Pmax, normal modulation polarity
#define DRSREG 			0xC6A3		// 9579Baud (default)
#define	SYNBREG			0xCED4		// Syncronization Pattern (default 0xCED4)


#define NODATA 					0
#define DATA_RECEIVED 	1
#define PACKET_RECEIVED	2
#define	PAYLOAD_MAX			20
#define RX_PACKET_SIZE	10

typedef struct
{
    UI08_t buffer[PAYLOAD_MAX];
    UI08_t index;               // Contains the array index
    UI08_t len;                 // Real array length
    UI08_t ChkSum;                // For storing 14, 28 and 128 bit speeds
} TRFData;

typedef struct
{
    union
    {
        BYTE    Val;
        struct
        {
            BYTE    Valid       :1;
            BYTE    RSSI        :1;
            BYTE    DQD         :1;
        } bits;
    } flags;
    BYTE        Payload[RX_PACKET_SIZE];
    BYTE        PayloadLen;
} RX_PACKET;

#define	FREQ_BAND_433				0x0010       //    433 MHz
#define FREQ_BAND_868				0x0020       //    868 MHz
#define FREQ_BAND_915				0x0030       //    915 MHz

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


typedef union
{
    unsigned int  Val;
    unsigned char v[2];
    struct
    {
        unsigned	RSSI_ATS    :1;
        unsigned	FFEM        :1;
        unsigned	LBD         :1;
        unsigned	EXT         :1;
        unsigned	WKUP        :1;
        unsigned	RGUR_FFOV   :1;
        unsigned	POR         :1;
        unsigned	RG_FF_IT    :1;

        unsigned	filler      :5;
        unsigned	ATGL        :1;
        unsigned	CRL         :1;
        unsigned	DQD         :1;
    } bits;
 } TTranseiverStatus;


UI08_t SPI_Read(void);
void SPI_Write(UI08_t spidata);
void SPI_Write16(UI16_t spicmd);
void SPI_Command(UI16_t spicmd);

void MRF49XA_Init();
void MRF49XA_Send_Packet(TRFData *RFData);
UI08_t  MRF49XA_Receive_Packet(TRFData *RFData);

void MRF49XA_Power_Down(void);

void MRF49XA_Read_Status(unsigned char *ffit_rgit);

void MRF49XA_Reset_Radio(void);

void AddRFData(TRFData *RFData, unsigned char data);

void InitRFData(TRFData *RFData);

unsigned char CalChkSum(unsigned char *buffer, unsigned char len);

void StatusRead(void);

#endif
