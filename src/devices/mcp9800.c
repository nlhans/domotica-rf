#include "devices/mcp9800.h"
#include "bsp/softI2c.h"

void Mcp9800Start(Mcp9800Resolution_t resolution)
{
    SoftI2cStart();
    SoftI2cTxByte(0b10010000);
    SoftI2cTxByte(0x01);
    SoftI2cTxByte(resolution);  // one shot + resolution
    SoftI2cStop();

    SoftI2cStart();
    SoftI2cTxByte(0b10010000);
    SoftI2cTxByte(0x00);
    SoftI2cStop();

}

uint16_t Mcp9800Read(void)
{
    SoftI2cStart();
    SoftI2cTxByte(0b10010001);
    uint8_t tempH = SoftI2cRxByte(1);
    uint8_t tempL = SoftI2cRxByte(0);
    SoftI2cStop();

    return (tempH << 8) | tempL;
}