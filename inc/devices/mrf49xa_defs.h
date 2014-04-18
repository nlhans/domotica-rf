#ifndef DEVICES_MRF49XA_DEFS
#define DEVICES_MRF49XA_DEFS

#define RF_DATARATE 2400
#define RF_DATARATE_SLOW

// RF Center frequency
// The formula for calculating the exact value can be found on page 26.
// F_center = 10 x FA1 x (FA0 + freq/4000) [MHz]
// For 434MHz band: FA1 = 1 and FA0 = 43
// For 868MHz band: FA1 = 2 and FA0 = 43
// For 915MHz band: FA1 = 3 and FA0 = 30
//#define RF_FREQ 1400 // =867MHz
#define RF_FREQ 0x860 // 2144 / =870.72MHz

// All available registers
#define REG_GENCREG     0x80
#define REG_PMCREG      0x82
#define REG_AFCREG      0xC4
#define REG_TXCREG      0x98
#define REG_CFSREG      0xA0
#define REG_RXCREG      0x90
#define REG_BBFCREG     0xC2
#define REG_FIFORSTREG  0xCA
#define REG_SYNBREG     0xCE
#define REG_DRSREG      0xC6
#define REG_WTSREG      0xE0

// Tx buffer
#define REG_TXBREG      0xB8

// Rx buffer
#define REG_RXFIFO      0xB0

// Magic register for loop to request a delay
#define REG_DELAY       0x55

// ***** General Configuration Register (GENCREG) ******//
#define	FREQ_BAND_433			0x10       //    433 MHz
#define FREQ_BAND_868			0x20       //    868 MHz
#define FREQ_BAND_915			0x30       //    915 MHz

#define XTAL_LD_CAP_85			0x00
#define XTAL_LD_CAP_9			0x01
#define XTAL_LD_CAP_95			0x02
#define XTAL_LD_CAP_10			0x03
#define XTAL_LD_CAP_105			0x04
#define XTAL_LD_CAP_11			0x05
#define XTAL_LD_CAP_115			0x06
#define XTAL_LD_CAP_12			0x07
#define XTAL_LD_CAP_125			0x08
#define XTAL_LD_CAP_13			0x09
#define XTAL_LD_CAP_135			0x0A
#define XTAL_LD_CAP_14			0x0B
#define XTAL_LD_CAP_145			0x0C
#define XTAL_LD_CAP_15			0x0D
#define XTAL_LD_CAP_155			0x0E
#define XTAL_LD_CAP_16			0x0F

#define GENC_RX_FIFO                    0x40
#define GENC_TX_DATA                    0x80

#define GENCREG_RESET                   XTAL_LD_CAP_125 | FREQ_BAND_868
#define GENCREG_MODE_RX                 GENCREG_RESET | GENC_RX_FIFO
#define GENCREG_MODE_TX                 GENCREG_RESET | GENC_TX_DATA


// ***** Automatic Frequency Control Register (AFCREG) ******//
#define AFC_EN          0x01
#define AFC_OFFSET_EN   0x02
#define AFC_HAM         0x04

#define AFC_RANGE_NONE      0x00
#define AFC_RANGE_P15_M16   0x10
#define AFC_RANGE_P7_M8     0x20
#define AFC_RANGE_P3_M4      0x30

#define AFC_MODE_ONLY_RX  0x80
#define AFC_MODE_INDEPENDANT 0xC0

// ***** Transmit Configuration Register (TXCREG) ******//
#define TXC_MODBW_15K    0x00
#define TXC_MODBW_30K    0x10
#define TXC_MODBW_45K    0x20
#define TXC_MODBW_60K    0x30
#define TXC_MODBW_75K    0x40
#define TXC_MODBW_90K    0x50
#define TXC_MODBW_105K   0x60
#define TXC_MODBW_120K   0x70
#define TXC_MODBW_135K   0x80
#define TXC_MODBW_150K   0x90
#define TXC_MODBW_165K   0xA0
#define TXC_MODBW_180K   0xB0
#define TXC_MODBW_195K   0xC0
#define TXC_MODBW_210K   0xD0
#define TXC_MODBW_225K   0xE0
#define TXC_MODBW_240K   0xF0

#define TXC_TXPWR_0_DB		0x00
#define TXC_TXPWR_N_2_5_DB      0x01
#define TXC_TXPWR_N_5_DB	0x02
#define TXC_TXPWR_N_7_5_DB	0x03
#define TXC_TXPWR_N_10_DB	0x04
#define TXC_TXPWR_N_12_5_DB     0x05
#define TXC_TXPWR_N_15_DB	0x06
#define TXC_TXPWR_N_17_5_DB     0x07

// ***** Center Frequency Value Set Register ******//

#if RF_FREQ > 3903
#error "RF center frequency must be 96 < freq < 3903"
#endif
#if RF_FREQ < 96
#error "RF center frequency must be 96 < freq < 3903"
#endif

#define RF_FREQ_MSB ((RF_FREQ >> 8) & 0x0F)
#define RF_FREQ_LSB (RF_FREQ & 0xFF)

// ***** Receive Control Register ******//

// Data indicator output is overloaded onto ext input interrupt (INT pin).
#define RXC_DIO_FUNCTION        0x04

#define RXC_DIO_RESPONSE_CONT   0x03
#define RXC_DIO_RESPONSE_SLOW   0x02
#define RXC_DIO_RESPONSE_MED    0x01
#define RXC_DIO_RESPONSE_FAST   0x00

// Receiver bandwidth. Must be greater than transmit bandwidth
#define RXC_RXBW_67K            0xC0
#define RXC_RXBW_134K           0xA0
#define RXC_RXBW_200K           0x80
#define RXC_RXBW_270K           0x60
#define RXC_RXBW_340K           0x40
#define RXC_RXBW_400K           0x20

// Receiver LNA amplifier
#define RXC_LNA_M_20DB          0x18
#define RXC_LNA_M_14DB          0x10
#define RXC_LNA_M_6DB           0x08
#define RXC_LNA_0DB             0x00

// RSSI Thresshold
#define RXC_RSSI_M_73DB         0x05
#define RXC_RSSI_M_79DB         0x04
#define RXC_RSSI_M_85DB         0x03
#define RXC_RSSI_M_91DB         0x02
#define RXC_RSSI_M_97DB         0x01
#define RXC_RSSI_M_103DB        0x00

// ***** Baseband Filter Configuration Register ******//
#define BBFC_WRITE              0x28

#define BBFC_AUTO_CLK           0x80

// Manual clock recovery needs to control these bits
#define BBFC_CLK_FAST           0x40
#define BBFC_CLK_SLOW           0x00

// Baseband filter type
#define BBFC_FILTER_ANALOG      0x10
#define BBFC_FILTER_DIGITAL     0x00

// Data Quality threshold
#define BBFC_DQTI(t)     (t & 0x07)

// ***** Fifo and Reset mode configuration register ******//
#define FIFORST_DIS_SEN_RST     0x01

#define FIFORST_SYNC_CHAR       0x02

#define FIFORST_FIFO_ALWAYS_FILL    0x04
#define FIFORST_FIFO_SYNC_CHAR_FILL 0x00

#define FIFORST_SYNC_BYTE       0x08
#define FIFORST_SYNC_WORD       0x00

#define FIFORST_FIFO_FILL_CNT(x)    ((x << 4) & 0xF0)

#define FIFORST_RESET           FIFORST_DIS_SEN_RST | FIFORST_FIFO_FILL_CNT(7)
#define FIFORST_MODE_RX         FIFORST_RESET | FIFORST_SYNC_CHAR
#define FIFORST_MODE_TX         FIFORST_RESET

// ***** Data Rate Value Set Register ******//
//#define DRS_SLOW(x)             (0x7F & (10000000/(uint32_t)(29 * 8 * x) - 1))
//#define DRS_FAST(x)             (0x7F & (10000000/(uint32_t)(29     * x) - 1))
#define DRS_SLOW(x) 0x05 // TODO: Fix this formula, 0x11 is 2400bps
#ifdef RF_DATARATE_SLOW
#define DRS_DATARATE DRS_SLOW(RF_DATARATE)
#else
#define DRS_DATARATE DRS_FAST(RF_DATERATE)
#endif

// ***** Power Management Register ******//
#define PMCREG_CLKOUT           0x01
#define PMCREG_WAKEUP           0x02
#define PMCREG_LOWBAT           0x04
#define PMCREG_OSC              0x08
#define PMCREG_SYN              0x10
#define PMCREG_TXC              0x20
#define PMCREG_BBC              0x40
#define PMCREG_RXC              0x80

#define PMCREG_MODE_RX          PMCREG_RXC
#define PMCREG_MODE_TX          PMCREG_TXC
#define PMCREG_RESET            0

// ***** Wake-up timer register ******//
#define WTS_EVERY_9MS_MSB       0x03
#define WTS_EVERY_9MS_LSB       0x01

// ***** Status Register ******//
// (obtained by 2 reads)
typedef union mrf49xaStatus_u
{
    UI08_t byte[2];
    struct
    {
        struct
        {
            UI08_t signalPresent:1;
            UI08_t fifoEmpty:1;
            UI08_t lowBat:1;
            UI08_t extIntPin:1;
            UI08_t wakeup:1;
            UI08_t overflow:1;
            UI08_t por:1;
            UI08_t fifoTxRx:1;
        } msb;
        struct
        {
            UI08_t offset:4;
            UI08_t offsetSign:1;
            UI08_t afc:1;
            UI08_t clockLock:1;
            UI08_t dataQualityOK:1;
        } lsb;
    } flags;
}mrf49xaStatus_t;
extern mrf49xaStatus_t mrf49Status;

// Software status for receiving & transmitting packets
typedef enum rfTrcvState_e
{
#ifdef MRF49XA_POWER_SWITCH
    POWERED_OFF,
#endif
            
    RECV_IDLE,
    RECV_DATA,

    TX_PACKET
} rfTrcvState_t;

typedef enum rfTrcvPacketState_e
{
    PKT_FREE,               // Packet is unused
    PKT_READY_FOR_TX,       // Marked for transmit
    PKT_WAITING_FOR_ACK,    // Packet was transmitted but is waiting for acknowledgement
    PKT_HW_BUSY_RX,         // Hardware is busy with receiving in this buffer
    PKT_HW_READY_RX,        // Hardware is done with receiving, software can pick it up
    PKT_SW_BUSY             // Software is still busy with processing. After this; returns to "FREE"
}rfTrcvPacketState_t;

typedef enum rfTrcvAckState_e
{
    NO_ACK,
    NEED_ACK,
    ACK_RECEIVED
} rfTrcvAckState_t;

typedef struct rfTrcvPacket_s
{
    rfTrcvPacketState_t state;

    union
    {
        struct
        {
            uint8_t size;
            uint8_t src;
            uint8_t dst;
            uint8_t id;
            uint8_t opt;
            
            uint8_t data[16];
        } packet;
        uint8_t raw[21];
    };
    uint8_t crc;
    rfTrcvAckState_t needAck;
    uint8_t retry:4;
    uint8_t retransmit:2;
} rfTrcvPacket_t;

typedef struct rfTrcvStatus_s
{
    rfTrcvState_t state;

    rfTrcvPacket_t txPacket;
    rfTrcvPacket_t rxPacket[2];

    rfTrcvPacket_t* hwRx;
    uint8_t hwByte;

    uint8_t src; // my node ID

} rfTrcvStatus_t;
extern rfTrcvStatus_t rfTrcvStatus;

#define packetRx rfTrcvStatus.hwRx
#define packetTx rfTrcvStatus.txPacket


// Node ID for broadcasts
#define RF_BROADCAST 0xFF

#endif