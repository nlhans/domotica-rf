#include "stddefs.h"
#include "utilities/spiArbiter.h"
#include "devices/enc28j60.h"
#include "devices/mrf49xa.h"

uint16_t spiArbEthAcquire()
{
    ENC28J60_CS_LOW;
    return true;
}
uint16_t spiArbEthComplete(void)
{
    ENC28J60_CS_HIGH;

    return 1;
}

void spiArbRfAcquire(void)
{
    MRF_DISABLE_INT;
    RF_SPI_CS = 0;
}

void spiArbRfComplete(void)
{
    RF_SPI_CS = 1;
    MRF_ENABLE_INT;
}