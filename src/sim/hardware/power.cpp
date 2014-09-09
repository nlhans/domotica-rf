#include "hardware/power.h"

#include <math.h>
#include <stdlib.h>

void PwrI2cWake() {}
void PwrI2cSleep() {}

void PwrSensorWake() {}
void PwrSensorSleep() {}

void PwrRfWake() {}
void PwrRfSleep() {}

void PwrAdcWake()
{

}
void PwrAdcSleep()
{
}

void Mcp9800Start(uint8_t mode)
{

}

uint16_t Mcp9800Read()
{
    return 0xAA55;
}

uint16_t AdcSample(uint8_t ch)
{
    return rand();
}
