#include "devices/mrf49xa.h"
#if BUILD_TARGET != TARGET_SIMULATOR

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

volatile const Mrf49InitReg_t const mrfRegset_Sleep[] = {
    REG(REG_PMCREG,         PMCREG_MODE_SLEEP),
    REG(REG_FIFORSTREG,     FIFORST_RESET),
    REG(REG_GENCREG,        GENCREG_MODE_SLEEP),
};
volatile const uint8_t mrfRegset_SleepCnt = sizeof(mrfRegset_Sleep)/sizeof(Mrf49InitReg_t);
    
void mrf49xaCfg(Mrf49InitReg_t* regs, uint8_t count)
{
    uint8_t k = 0;
    SetupRegistersLoop(regs, count);
}

bool Mrf49xaSignalPresent(Mrf49xaMac_t* inst)
{
    Mrf49RxSts(mrf49Inst);
    if (mrf49Inst->status.flags.msb.signalPresent == 0)
        return true;
    else
        return false;
}

void Mrf49xaModeRx(Mrf49xaMac_t* inst)
{
    uint8_t k;
    SetupRegistersWithoutDelay(Rx);
    //mrf49xaCfg(mrfRegset_Rx, mrfRegset_RxCnt);

    mrf49Inst->state = RECV_IDLE;
    mrf49Inst->hwByte = 0;

    mrf49Inst->status.flags.msb.fifoTxRx = 0;
}

void Mrf49xaModeTx(Mrf49xaMac_t* inst)
{
    uint8_t k;
    SetupRegistersWithoutDelay(Tx);
    //mrf49xaCfg(mrfRegset_Tx, mrfRegset_TxCnt);

    mrf49Inst->state = TX_PACKET;
    mrf49Inst->hwByte = 99;
}

#ifdef MRF49XA_POWER_SWITCH
void Mrf49xaModeSleep(Mrf49xaMac_t* inst)
{
    uint8_t k;
    SetupRegistersWithoutDelay(Sleep);

    mrf49Inst->state = POWERED_OFF;
    mrf49Inst->hwByte = 0;
}

void Mrf49xaShutdown(Mrf49xaMac_t* inst)
{
    Mrf49xaModeSleep(mrf49Inst);
    //RF_POWER = RF_PWR_OFF;

    //mrf49Inst->state = POWERED_OFF;
}

void Mrf49xaReboot(Mrf49xaMac_t* inst)
{
    Mrf49xaModeRx(mrf49Inst);
}
#endif

void Mrf49xaNeedsReset(Mrf49xaMac_t* inst)
{
    mrf49Inst->needsReset = true;
}

void Mrf49xaInit(Mrf49xaMac_t* inst)
{
    uint8_t k;
#ifdef PIC16_HW
    uint8_t i, j;
#endif
    reset:

    for (k = 0; k < sizeof(Mrf49xaMac_t); k++)
    {
        ((uint8_t*)mrf49Inst)[k] = 0;
    }

    // Power chip, reset it.
    RF_SPI_CS = 1;
    RF_SPI_SCK = 0;
    RF_SPI_SDO = 0;

    RF_POWER = RF_PWR_ON;
    RF_FSEL = 1;
#ifdef PIC16_HW
    RF_INT = 1;
#endif
    Delay50Ms();
    RF_RES = 0;
    Delay50Ms();
    RF_RES = 1;
    Delay50Ms();

    mrf49Inst->state = RECV_IDLE;
    
    SetupRegisters(Init);
    //mrf49xaCfg(mrfRegset_Init, mrfRegset_InitCnt);

    Mrf49xaModeRx(mrf49Inst);

    k = 0;
    while(RF_IRQ == 0)
    {
        k++;
        if (k == 255)
        {
            k = 0;
            // Overflow, reset..
            goto reset;
        }

#ifdef PIC24_HW
        Mrf49xaServe(0);
#else
        Mrf49xaServe(mrf49Inst);
#endif
    }
}

#endif
