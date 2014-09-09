#include "bsp/softI2c.h"
#include "devices/24aa64.h"

#if BUILD_TARGET != TARGET_SIMULATOR

void eepromRxBytes(uint16_t address, uint8_t* data, uint8_t size)
{
    // Random read
    SoftI2cStart();
    SoftI2cTxByte(0xA0);
    SoftI2cTxByte(address >> 8);
    SoftI2cTxByte(address & 0xFF);

    SoftI2cRepeatedStart();
    SoftI2cTxByte(0xA1);

    while (size != 0)
    {
        size--;

        *data = SoftI2cRxByte(size != 0);

        data++;
    }
    SoftI2cStop();
}
void eepromTxBytes(uint16_t address, uint8_t* data, uint8_t size)
{
    // Random-write
    SoftI2cStart();
    SoftI2cTxByte(0xA0);
    SoftI2cTxByte(address >> 8);
    SoftI2cTxByte(address & 0xFF);

    while (size != 0)
    {
        SoftI2cTxByte(*data);

        data++;
        size--;
    }
    SoftI2cStop();
}

uint8_t eepromRxByte(uint16_t address)
{
    uint8_t dat;
    eepromRxBytes(address, &dat, 1);
    return dat;
}
void eepromTxByte(uint16_t address, uint8_t byte)
{
    eepromTxBytes(address, &byte, 1);
}

#endif