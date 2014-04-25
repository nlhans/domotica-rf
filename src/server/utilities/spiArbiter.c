#include "stddefs.h"
#include "utilities/spiArbiter.h"
#include "devices/enc28j60.h"

volatile spiArbStat_t spiArbStat;
UI08_t ethFault = 0;

void spiArbEthDisableIsr(void)
{
    __builtin_disi(0xFFF);
}
void spiArbEthEnableIsr(void)
{
    __builtin_disi(0);
}

UI16_t spiArbEthAcquire()
{
    spiArbEthDisableIsr();
    //spiSpeed(1, TRUE);
    ENC28J60_CS_LOW;
    return TRUE;
}
UI16_t spiArbEthComplete(void)
{
    spiArbStat.ethBusy = 0;
    ENC28J60_CS_HIGH;
    //spiSpeed(1, FALSE);
    spiArbEthEnableIsr();

    return 1;
}

void spiArbRfAcquire(void)
{
    //spiSpeed(1, FALSE);
    RF_SPI_CS = 0;
}

void spiArbRfComplete(void)
{
    RF_SPI_CS = 1;
    //spiSpeed(1, TRUE);
}