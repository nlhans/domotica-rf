#ifndef DEVICES_24AA64_H
#define DEVICES_24AA64_H

#include "stddefs.h"

void eepromRxBytes(UI16_t address, UI08_t* data, UI08_t size);
void eepromTxBytes(UI16_t address, UI08_t* data, UI08_t size);
UI08_t eepromRxByte(UI16_t address);
void eepromTxByte(UI16_t address, UI08_t byte);

#endif