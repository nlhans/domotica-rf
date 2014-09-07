#ifndef POWER_H
#define POWER_H

#include <stdint.h>
#include "bsp/adc.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define Mcp9800_9bit 9
#define BSP_HUMIDITY_CHANNEL 0
#define ADC_FVR 1

void PwrI2cWake();
void PwrI2cSleep();

void PwrSensorWake();
void PwrSensorSleep();

void PwrRfWake();
void PwrRfSleep();

void PwrAdcWake();
void PwrAdcSleep();

void Mcp9800Start(uint8_t mode);
uint16_t Mcp9800Read();

#ifdef __cplusplus
}
#endif

#endif // VIRTUAL_POWER_H
