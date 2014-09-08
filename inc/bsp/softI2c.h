#ifndef SOFT_I2C_H
#define SOFT_I2C_H

#include "stddefs.h"
#define I2C_HIGH 1
#define I2C_LOW 0

void SoftI2cInit(void);
void SoftI2cRepeatedStart(void);
void SoftI2cNop(void);


void SoftI2cStart(void);
uint8_t SoftI2cRxByte(uint8_t ack);
uint8_t SoftI2cTxByte(uint8_t data);
void SoftI2cStop(void);

#endif