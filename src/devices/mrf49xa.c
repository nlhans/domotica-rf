#include "devices/mrf49xa.h"

#define uint8_t unsigned char 

#define packetHwRx rfTrcvStatus.hwRx
#define packetSwRx rfTrcvStatus.swRx
#define packetTx rfTrcvStatus.txPacket

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
    REG(REG_AFCREG,       AFC_EN | AFC_OFFSET_EN | AFC_HAM | AFC_RANGE_P15_M16 | AFC_MODE_INDEPENDANT ),      // AFC ON
    REG(REG_CFSREG |      RF_FREQ_MSB, RF_FREQ_LSB ),
    REG(REG_DRSREG,       DRS_DATARATE ),
    REG(REG_PMCREG,       PMCREG_RESET),
    REG(REG_RXCREG,       RXC_RXBW_270K | RXC_LNA_0DB | RXC_RSSI_M_91DB),
    REG(REG_TXCREG,       TXC_MODBW_150K | TXC_TXPWR_0_DB),                // 60kHz tx BW
    REG(REG_BBFCREG,      BBFC_WRITE | BBFC_AUTO_CLK | BBFC_FILTER_DIGITAL | BBFC_DQTI(4) ),

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
    REG(REG_GENCREG,        GENCREG_RESET),
    REG(REG_PMCREG,         PMCREG_MODE_TX),
    REG(REG_GENCREG,        GENCREG_MODE_TX),
};
volatile const uint8_t mrfRegset_TxCnt = sizeof(mrfRegset_Tx)/sizeof(Mrf49InitReg_t);

// TODO: Calibrate delay to 5ms on PIC16 @ 16MHz.
// 250 = ~109ms
// 5ms -> 12
#define SetupRegisterDelay() for (i = 0; i < 12; i++) { for (j = 0; j < 250; j++) { asm ("nop"); } }

#define SetupRegisters(type) SetupRegistersLoop(mrfRegset_## type, mrfRegset_## type ##Cnt)
#define SetupRegistersWithoutDelay(type) SetupRegistersLoopWithoutDelay(mrfRegset_## type, mrfRegset_## type ##Cnt)

#define SetupRegistersLoopWithoutDelay(array, count) for (k = 0; k < count; k++) { \
        if (array[k].reg != REG_DELAY) \
        Mrf49TxCmd(array[k].reg, array[k].val); }

#define SetupRegistersLoop(array, count) for (k = 0; k < count; k++) { \
    if (array[k].reg == REG_DELAY) { SetupRegisterDelay(); } else { \
    Mrf49TxCmd(array[k].reg, array[k].val); } }

// Do tick or ISR
void Mrf49xaTick(void)
{
    uint8_t data;
#ifdef MRF49XA_POWER_SWITCH
    if (rfTrcvStatus.state == POWERED_OFF)
        return;
#endif

    if (PORTAbits.RA2 == 0)
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

    // TODO: Wake-up timer
    // Use the wake-up timer to signal packet timeouts.
    // For example, we could transmit only 1 packet every 15ms - 20ms.
    // If a packet isn't completely received within that period, the WUT flag
    // occurs & signals the RX statemachine to abort.
    
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
                
                //Truncate data is quality is bad
                if (mrf49Status.flags.lsb.dataQualityOK == 0)
                    break;

                if (rfTrcvStatus.rxPacket[0].state == PKT_FREE) rfTrcvStatus.hwRx = &(rfTrcvStatus.rxPacket[0]);
                else if (rfTrcvStatus.rxPacket[1].state == PKT_FREE) rfTrcvStatus.hwRx = &(rfTrcvStatus.rxPacket[1]);
                else
                {
                    // Error!
                    break;
                }
                packetHwRx->packet.size = data;
                packetHwRx->crc = 0;
                packetHwRx->state = PKT_HW_BUSY_RX;
                
                rfTrcvStatus.state = RECV_DATA;
                rfTrcvStatus.hwRxByte = 1;

                break;

            case RECV_DATA:

                data = Mrf49RxByte();

                //Truncate data is quality is bad
                if (mrf49Status.flags.lsb.dataQualityOK == 0)
                    break;
                
                packetHwRx->raw[rfTrcvStatus.hwRxByte++] = data;

                if (rfTrcvStatus.hwRxByte == packetHwRx->packet.size ||
                        rfTrcvStatus.hwRxByte == 16)
                {
                    rfTrcvStatus.state = RECV_IDLE;
                    packetHwRx->state = PKT_FREE;

                    // flag scope
                    SENSOR_PWR = 1;
                    SENSOR_PWR = 0;

                    // Reset modem
                    Mrf49xaModeRx();

                }

                break;
        }
    }
    
}

void Mrf49xaModeRx(void)
{
    UI08_t k;
    SetupRegistersWithoutDelay(Rx);

    rfTrcvStatus.state = RECV_IDLE;
}

void Mrf49xaModeTx(void)
{
    UI08_t k;
    SetupRegistersWithoutDelay(Tx);

    rfTrcvStatus.state = TX_PACKET;
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
        Mrf49xaTick();
}

#endif