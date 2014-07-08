#include "devices/mrf49xa.h"

void Mrf49SpiTx(uint8_t byte)
{
    #define SPI_TX_TICK(a) do { if ((byte & (1<<a)) != 0) RF_SPI_SDO = 1; else RF_SPI_SDO = 0; \
    RF_SPI_SCK = 1; \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    RF_SPI_SCK = 0; \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); } while (0);

    SPI_TX_TICK(7);
    SPI_TX_TICK(6);
    SPI_TX_TICK(5);
    SPI_TX_TICK(4);
    SPI_TX_TICK(3);
    SPI_TX_TICK(2);
    SPI_TX_TICK(1);
    SPI_TX_TICK(0);
    RF_SPI_SDO = 0;
}

uint8_t Mrf49SpiRx(void)
{
    uint8_t data = 0;
    RF_SPI_SDO = 0;

    #define SPI_RX_TICK(a) do { if (RF_SPI_SDI) data |= (1<<a); \
    RF_SPI_SCK = 1; \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    RF_SPI_SCK = 0; \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); \
    Nop(); } while (0);

    SPI_RX_TICK(7);
    SPI_RX_TICK(6);
    SPI_RX_TICK(5);
    SPI_RX_TICK(4);
    SPI_RX_TICK(3);
    SPI_RX_TICK(2);
    SPI_RX_TICK(1);
    SPI_RX_TICK(0);

    return data;
}