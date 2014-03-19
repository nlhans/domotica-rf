#ifndef DEVICES_SPI_ARBITER
#define DEVICES_SPI_ARBITER

#include "stddefs.h"

typedef struct spiArbstat_s
{
    bool_t ethBusy:1;
    bool_t ethAbort:1;
    bool_t rfBusy:1;
} spiArbStat_t;

extern UI08_t ethFault;

extern volatile spiArbStat_t spiArbStat;

void spiArbEthAbort(void);
UI16_t spiArbEthWasAborted(void);
UI16_t spiArbEthAcquire(void);
UI16_t spiArbEthComplete(void);

void spiArbRfAcquire(void);
void spiArbRfComplete(void);

#endif