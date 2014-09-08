#ifndef ADC_H
#define ADC_H
#include "stddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

void AdcInit(void);
void AdcDeinit(void);

void AdcGo(void);
uint8_t AdcIsBusy(void);
void AdcPinEnable(uint8_t port, uint8_t portNumber);
void AdcPinDisable(uint8_t port, uint8_t portNumber);
inline uint16_t AdcGetResult(void);
uint16_t AdcSample(uint8_t ch);
void AdcChSelect(AdcChannel_t channel);


#ifdef __cplusplus
}
#endif

#endif
