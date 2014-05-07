#include "devices/mrf49xa.h"

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

void Mrf49RxSts(void)
{
    MRF_DISABLE_INT;
    RF_CS_ACQ();

    mrf49Status.byte[0] = Mrf49SpiRx();
    mrf49Status.byte[1] = Mrf49SpiRx();

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