#include "stddefs.h"
#include "devices/spiArbiter.h"
#include "devices/enc28j60.h"

volatile spiArbStat_t spiArbStat;
UI08_t ethFault = 0;

void spiArbEthAbort(void)
{
    //if (spiBusy1())
    //   while(spiBusy1());
    spiArbStat.ethBusy = 0;
    spiArbStat.ethAbort = 1;

    ethFault++;
    
    ENC28J60_CS_HIGH;
}
UI16_t spiArbEthWasAborted(void)
{
    if (spiArbStat.ethAbort)
        return 1;
    else
        return 0;
}

UI16_t spiArbEthAcquire(void)
{
    if (spiArbStat.rfBusy == 1)
    {
        return FALSE;
    }
    else
    {
        spiArbStat.ethAbort = 0;
        spiArbStat.ethBusy  = 1;

        ENC28J60_CS_LOW;

        return TRUE;
    }
}
UI16_t spiArbEthComplete(void)
{
    spiArbStat.ethBusy = 0;

    ENC28J60_CS_HIGH;
    
    return 1;
}

void spiArbRfAcquire(void)
{
    if (spiArbStat.ethBusy == TRUE)
    {
        spiArbEthAbort();
    }
    
    spiArbStat.rfBusy = 1;
    RF_SPI_CS = 0;
}

void spiArbRfComplete(void)
{
    RF_SPI_CS = 1;
    spiArbStat.rfBusy = 0;
}