#include "devices/mrf49xa.h"

#if BUILD_TARGET != TARGET_SIMULATOR

#define Mrf49DataTx(d)  Mrf49TxCmd(MRF_REG_TXBREG, d);
//#define Mrf49DataRx(d)  Mrf49RxCmd(MRF_REG_TXBREG, d);

void Mrf49TxCmd(uint8_t cmd, uint8_t val)
{
    RF_CS_ACQ();

    Mrf49SpiTx(cmd);
    Mrf49SpiTx(val);

    // CS gaat al omhoog voordat de laatste clock afgelopen is.
    // Check de errata van de dsPIC33 chip
    RF_CS_REL();
}

uint8_t Mrf49RxCmd(uint8_t cmd)
{
    RF_CS_ACQ();

    Mrf49SpiTx(cmd);
    uint8_t val = Mrf49SpiRx();

    RF_CS_REL();

    return val;

}

void Mrf49RxSts(Mrf49xaMac_t* inst)
{
    MRF_DISABLE_INT;
    RF_CS_ACQ();

    mrf49Inst->status.byte[0] = Mrf49SpiRx();
    mrf49Inst->status.byte[1] = Mrf49SpiRx();

    RF_CS_REL();
    MRF_ENABLE_INT;
}

uint8_t Mrf49RxByte(void)
{
    return Mrf49RxCmd(REG_RXFIFO);
}

void Mrf49TxByte(uint8_t byte)
{
    Mrf49TxCmd(REG_TXBREG, byte);
}

#endif