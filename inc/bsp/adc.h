#ifndef ADC_H
#define ADC_H
#include "stddefs.h"

void AdcInit(void);
void AdcDeinit(void);

void AdcGo(void);
UI08_t AdcIsBusy(void);
void AdcPinEnable(UI08_t port, UI08_t portNumber);
void AdcPinDisable(UI08_t port, UI08_t portNumber);
inline UI16_t AdcGetResult(void);
UI16_t AdcSample(UI08_t ch);
void AdcChSelect(AdcChannel_t channel);

#endif