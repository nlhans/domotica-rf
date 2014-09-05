#ifndef POWER_H
#define POWER_H

#include "stddefs.h"

#include "devices/mrf49xa.h"

extern Mrf49xaMac_t mrf49xaInst;
extern Mrf49xaMac_t* macPtr;

void Sleepy(uint16_t ms);

void PwrI2cInit(void);
void PwrI2cSleep(void);
void PwrI2cWake(void);

void PwrRfInit(void);
void PwrRfSleep(void);
void PwrRfWake(void);

void PwrSensorInit(void);
void PwrSensorSleep(void);
void PwrSensorWake(void);

void PwrAdcInit(void);
void PwrAdcSleep(void);
void PwrAdcWake(void);

#endif