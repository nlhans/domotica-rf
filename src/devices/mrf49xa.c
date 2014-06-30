#include "devices/mrf49xa.h"

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
/*
    REG(REG_PMCREG,         PMCREG_MODE_RX),
    REG(REG_GENCREG,        GENCREG_MODE_RX),

    REG(REG_CMSA,         0x00),

    REG(REG_GENCREG,      GENCREG_RESET),*/
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

#define SetupRegistersLoopWithoutDelay(array, count) for (k = 0; k < count; k++) { Mrf49TxCmd(array[k].reg, array[k].val); }

#define SetupRegistersLoop(array, count) for (k = 0; k < count; k++) { \
    if (array[k].reg == REG_DELAY) { Delay5Ms(); } else \
{ Mrf49TxCmd(array[k].reg, array[k].val); } }
//if (array[k].reg == REG_CMSA) { while(Mrf49xaSignalPresent()); } else { \
    
void mrf49xaCfg(Mrf49InitReg_t* regs, uint8_t count)
{
    uint8_t k = 0;
    SetupRegistersLoop(regs, count);
}

bool_t Mrf49xaSignalPresent(void)
{
    Mrf49RxSts();
    if (mrf49Status.flags.msb.signalPresent == 0)
        return TRUE;
    else
        return FALSE;
}

void Mrf49xaModeRx(void)
{
    UI08_t k;
    SetupRegistersWithoutDelay(Rx);
    //mrf49xaCfg(mrfRegset_Rx, mrfRegset_RxCnt);

    rfTrcvStatus.state = RECV_IDLE;
    rfTrcvStatus.hwByte = 0;
}

void Mrf49xaModeTx(void)
{
    UI08_t k;
    SetupRegistersWithoutDelay(Tx);
    //mrf49xaCfg(mrfRegset_Tx, mrfRegset_TxCnt);

    rfTrcvStatus.state = TX_PACKET;
    rfTrcvStatus.hwByte = 99;
}

#ifdef MRF49XA_POWER_SWITCH
void Mrf49xaBootup(void)
{
    UI08_t i, j, k;
    
    RF_POWER = 1;
    RF_RES = 0;
    Delay50Ms();
    RF_RES = 1;
    Delay50Ms();

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
    UI08_t k;
#ifdef PIC16_HW
    UI08_t i, j;
#endif
    
    // Power chip, reset it.
    RF_POWER = 1;
    RF_FSEL = 1;
#ifdef PIC16_HW
    RF_INT = 1;
#endif
    Delay50Ms();
    RF_RES = 0;
    Delay50Ms();
    RF_RES = 1;
    Delay50Ms();

    rfTrcvStatus.state = RECV_IDLE;
    
    SetupRegisters(Init);
    //mrf49xaCfg(mrfRegset_Init, mrfRegset_InitCnt);

    Mrf49xaModeRx();

#ifdef PIC24_HW
    while(RF_IRQ == 0)
        Mrf49xaServe(0);
#else
   
    while(RF_IRQ == 0)
        Mrf49xaServe();
#endif
    
}

#endif