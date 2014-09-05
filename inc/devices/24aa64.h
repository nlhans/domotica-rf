#ifndef DEVICES_24AA64_H
#define DEVICES_24AA64_H

#include "stddefs.h"

void eepromRxBytes(uint16_t address, uint8_t* data, uint8_t size);
void eepromTxBytes(uint16_t address, uint8_t* data, uint8_t size);
uint8_t eepromRxByte(uint16_t address);
void eepromTxByte(uint16_t address, uint8_t byte);

#endif
