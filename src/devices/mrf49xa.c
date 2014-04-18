#include "devices/mrf49xa.h"

#define uint8_t unsigned char 

// Hardware chip status
mrf49xaStatus_t mrf49Status;

// Software driver status
rfTrcvStatus_t rfTrcvStatus;
// TODO: make object

typedef struct Mrf49InitReg_s
{
    uint8_t reg;
    uint8_t val;
}Mrf49InitReg_t;
#define REG(a, b) { a, b}

volatile const Mrf49InitReg_t const mrfRegset_Init[] = {
    REG(REG_FIFORSTREG,   FIFORST_RESET),
    REG(REG_FIFORSTREG,   FIFORST_MODE_RX),

    REG(REG_GENCREG,      GENCREG_RESET),
    REG(REG_AFCREG,       AFC_EN | AFC_OFFSET_EN | AFC_HAM | AFC_RANGE_P7_M8 | AFC_MODE_INDEPENDANT ),      // AFC ON
    REG(REG_CFSREG |      RF_FREQ_MSB, RF_FREQ_LSB ),
    REG(REG_DRSREG,       DRS_DATARATE ),
    REG(REG_PMCREG,       PMCREG_RESET),
    REG(REG_RXCREG,       RXC_RXBW_270K | RXC_LNA_0DB | RXC_RSSI_M_91DB),
    REG(REG_TXCREG,       TXC_MODBW_150K | TXC_TXPWR_0_DB),                // 60kHz tx BW
    REG(REG_BBFCREG,      0xAC), //BBFC_WRITE | BBFC_AUTO_CLK | BBFC_FILTER_DIGITAL | BBFC_DQTI(4) ),
    REG(REG_PMCREG,       PMCREG_MODE_TX),


    REG(REG_DELAY,        0x00), // tune in antenna

    REG(REG_PMCREG,       PMCREG_MODE_RX),
    REG(REG_GENCREG,      GENCREG_MODE_RX),
    REG(REG_FIFORSTREG,   FIFORST_RESET),
    REG(REG_FIFORSTREG,   FIFORST_MODE_RX),
    
};
volatile const uint8_t mrfRegset_InitCnt = sizeof(mrfRegset_Init)/sizeof(Mrf49InitReg_t);

volatile const Mrf49InitReg_t const mrfRegset_Rx[] = {
    REG(REG_PMCREG,         PMCREG_RESET),
    REG(REG_FIFORSTREG,     FIFORST_RESET),
    REG(REG_GENCREG,        GENCREG_RESET),
    REG(REG_PMCREG,         PMCREG_MODE_RX),
    REG(REG_GENCREG,        GENCREG_MODE_RX),
    REG(REG_FIFORSTREG,     FIFORST_MODE_RX)
};
volatile const uint8_t mrfRegset_RxCnt = sizeof(mrfRegset_Rx)/sizeof(Mrf49InitReg_t);

volatile const Mrf49InitReg_t const mrfRegset_Tx[] = {
    REG(REG_PMCREG,         PMCREG_RESET),
    REG(REG_FIFORSTREG,     FIFORST_RESET),
    REG(REG_GENCREG,        GENCREG_MODE_TX),
    REG(REG_PMCREG,         PMCREG_MODE_TX),
};
volatile const uint8_t mrfRegset_TxCnt = sizeof(mrfRegset_Tx)/sizeof(Mrf49InitReg_t);

#define SetupRegisters(type) SetupRegistersLoop(mrfRegset_## type, mrfRegset_## type ##Cnt)
#define SetupRegistersWithoutDelay(type) SetupRegistersLoopWithoutDelay(mrfRegset_## type, mrfRegset_## type ##Cnt)

#define SetupRegistersLoopWithoutDelay(array, count) for (k = 0; k < count; k++) { \
        if (array[k].reg != REG_DELAY) \
        Mrf49TxCmd(array[k].reg, array[k].val); }

#define SetupRegistersLoop(array, count) for (k = 0; k < count; k++) { \
    if (array[k].reg == REG_DELAY) { Delay5Ms(); } else { \
    Mrf49TxCmd(array[k].reg, array[k].val); } }

// Serve MRf49XA chipset when requires attention.
bool_t Mrf49xaServe(void)
{
    uint8_t data;
#ifdef MRF49XA_POWER_SWITCH
    if (rfTrcvStatus.state == POWERED_OFF)
        return;
#endif

    Mrf49RxSts();
    // Power-on-Reset
    if (mrf49Status.flags.msb.por == 1)
    {
        // TODO: Software reset?
    }

    // TXOWRXOF (RX overrun / TX underrun)
    if (mrf49Status.flags.msb.overflow == 1)
    {
        switch(rfTrcvStatus.state)
        {
            case RECV_IDLE:
            case RECV_DATA:
            case RECV_TIMEOUT:

                // Clear fifo data
                data = Mrf49RxByte();
                data = Mrf49RxByte();

                // Reset HW & SW rx
                Mrf49xaModeRx();

                // TODO: Wait until end of this packet burst is done.
                
                break;

            case TX_PACKET:
                // According to the datasheet, fifoTxRx is also always set.
                // So we don't have to do anything, as after this the
                // data-statemachine will run.
                break;
        }
    }

    // TODO: Logic external interrupt
    // This is probably never going to be used.

    // TODO: Low battery threshold detect
    // The system has it's own battery monitor.
    
    // TXRXFIFO flag raised
    if (mrf49Status.flags.msb.fifoTxRx == 1)
    {
        // Depending on the driver status.
        switch (rfTrcvStatus.state)
        {
            case RECV_IDLE:
                data = Mrf49RxByte();
                
                // Truncate data if quality is bad
                // Reset radio & wait for sync byte. Current pattern is rubbish data.
                if (mrf49Status.flags.lsb.dataQualityOK == 0)
                {
                    Mrf49xaModeRx();
                    break;
                }

                if (rfTrcvStatus.rxPacket[0].state == PKT_FREE) rfTrcvStatus.hwRx = &(rfTrcvStatus.rxPacket[0]);
                else if (rfTrcvStatus.rxPacket[1].state == PKT_FREE) rfTrcvStatus.hwRx = &(rfTrcvStatus.rxPacket[1]);
                else
                {
                    // Error, no space in RX buffers.
                    // Reset radio. Drop this packet.
                    Mrf49xaModeRx();
                    break;
                }
                packetRx->packet.size = data;
                packetRx->crc = 0;
                packetRx->state = PKT_HW_BUSY_RX;
                
                rfTrcvStatus.state = RECV_DATA;
                rfTrcvStatus.hwByte = 1;

                break;

            case RECV_DATA:

                data = Mrf49RxByte();

                // Truncate data if quality is bad
                // Reset radio & wait for sync byte. Current pattern is rubbish data.
                if (mrf49Status.flags.lsb.dataQualityOK == 0)
                {
                    Mrf49xaModeRx();
                    break;
                }

                if (rfTrcvStatus.hwByte == packetRx->packet.size)
                {
                    packetRx->crc = data;
                    
                    // TODO: Check CRC
                    // TODO: Check node ID (broadcast/myself)
                    packetRx->state = PKT_HW_READY_RX;

                    // Reset modem
                    Mrf49xaModeRx();

                    // flag scope
                    SENSOR_PWR = 1;
                    SENSOR_PWR = 0;

                }
                else
                {
                    packetRx->raw[rfTrcvStatus.hwByte++] = data;
                }
                
                break;

            case TX_PACKET:
                switch (rfTrcvStatus.hwByte)
                {
                    case 0:
                    case 1:
                        Mrf49TxByte(0xAA);
                        break;

                    case 2:
                        Mrf49TxByte(RF_NETWORKID1);
                        break;

                    case 3:
                        Mrf49TxByte(RF_NETWORKID2);
                        break;
                        
                        // 4..packet size
                    default:
                        Mrf49TxByte(packetTx.raw[rfTrcvStatus.hwByte-4]);
                        packetTx.crc = packetTx.crc ^ packetTx.raw[rfTrcvStatus.hwByte-4];
                        if (rfTrcvStatus.hwByte-4 == packetTx.packet.size)
                        {
                            rfTrcvStatus.hwByte = 48;
                        }
                        break;

                    case 49: // crc
                        Mrf49TxByte(packetTx.crc);
                        break;

                    case 50:
                        Mrf49TxByte(0x00);
                        break;

                    case 51:
                        Mrf49TxByte(0x00);
                        Mrf49xaModeRx();
                        packetTx.state = PKT_FREE;
                        break;
                }

                rfTrcvStatus.hwByte++;

                break;
        }
    }

    // TODO: Wake-up timer
    // On second thought, the underneath is not very attractive.
    // The wake-up needs shadow PMC register as the bit needs to be set
    // to 0 and back to 1 for it to retrigger.
    // An internal timer is more economic, as this bit reset/set costs
    // ~120us on PIC16.

    // Use the wake-up timer to signal packet timeouts & base tick
    // For example, we could transmit only 1 packet every 15ms - 20ms.
    // If a packet isn't completely received within that period, the WUT flag
    // occurs & signals the RX statemachine to abort.

    return RF_IRQ == 1 ? TRUE : FALSE;
}

void Mrf49xaModeRx(void)
{
    UI08_t k;
    SetupRegistersWithoutDelay(Rx);

    rfTrcvStatus.state = RECV_IDLE;
    rfTrcvStatus.hwByte = 0;
}

void Mrf49xaModeTx(void)
{
    UI08_t k;
    SetupRegistersWithoutDelay(Tx);

    rfTrcvStatus.state = TX_PACKET;
    rfTrcvStatus.hwByte = 0;
}

#ifdef MRF49XA_POWER_SWITCH
void Mrf49xaBootup(void)
{
    UI08_t i, j, k;
    
    RF_POWER = 1;
    RF_RES = 0;
    for (i = 0; i < 250; i++)
    {
        if (i == 125)
            RF_RES = 1;
        for (j = 0; j < 250; j++) asm ("nop");
    }
    RF_RES = 1;

    SetupRegisters(Init);

    Mrf49xaModeRx();
}

void Mrf49xaShutdown(void)
{
    RF_POWER = 0;

    rfTrcvStatus.state = POWERED_OFF;
}

#else

void Mrf49xaInit(void)
{
    UI08_t i, j, k;
    SetupRegisters(Init);

    Mrf49xaModeRx();

    while(RF_IRQ == 0)
        Mrf49xaServe();
}

#endif