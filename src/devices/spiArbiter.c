#include "stddefs.h"
#include "devices/spiArbiter.h"
#include "devices/enc28j60.h"

volatile spiArbStat_t spiArbStat;
UI08_t ethFault = 0;

UI32_t spiTime = 0;
UI32_t spiStart=0;
#define execGetTimestamp() ((UI32_t)(TMR2 | ((UI32_t)TMR3 << 16))/8 )

static UI08_t spiArbIsrOff = 0;

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
    TMR2 = 0;
    TMR3 = 0;
    spiStart = execGetTimestamp();
    
    spiArbEthDisableIsr();
    ENC28J60_CS_LOW;
    return TRUE;
}
UI16_t spiArbEthComplete(void)
{
    spiArbStat.ethBusy = 0;
    ENC28J60_CS_HIGH;
    UI32_t dt = execGetTimestamp() - spiStart;
    spiArbEthEnableIsr();

    if(dt > spiTime-5 || spiTime <= 5)
    {
        //printf("i%lu\n", dt);
        if(dt > spiTime) spiTime = dt;
    }
    
    return 1;
}

void spiArbRfAcquire(void)
{
    if (PORTCbits.RC8 == 0)
    {
        printf("CS conflict\n");
        //while(1);
    }
    RF_SPI_CS = 0;
}

void spiArbRfComplete(void)
{
    RF_SPI_CS = 1;
}