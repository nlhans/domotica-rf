#ifndef DEVICES_SPI_ARBITER
#define DEVICES_SPI_ARBITER

#include "stddefs.h"

typedef struct spiArbstat_s
{
    bool ethBusy:1;
    bool ethAbort:1;
    bool rfBusy:1;
} spiArbStat_t;

extern uint8_t ethFault;

extern volatile spiArbStat_t spiArbStat;

void spiArbEthAbort(void);
uint16_t spiArbEthWasAborted(void);
uint16_t spiArbEthAcquire(void);
uint16_t spiArbEthComplete(void);

void spiArbRfAcquire(void);
void spiArbRfComplete(void);

void spiArbEthDisableIsr(void);
void spiArbEthEnableIsr(void);

#endif