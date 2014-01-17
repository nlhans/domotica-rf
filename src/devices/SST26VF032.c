#include "devices/SST26VF032.h"

void FlashInit(void)
{
    spiInit(FLASH_SPI_PORT);
    FLASH_CS(1, FALSE);
}

void FlashCsSet(UI32_t addr, bool_t state)
{
    if (addr <= 524288)
    {
        FLASH_CS(1, state);
    }
    else
    {
        FLASH_CS(2, state);
    }
}

UI16_t FlashReadId(void)
{
    UI16_t id = 0;

    FLASH_CS(1, TRUE);

    spiTxByte(FLASH_SPI_PORT, FLASH_CMD_READ_ID);

#if FLASH_CMD_READ_ID_BYTES == 4
    id |= spiRxByte(FLASH_SPI_PORT) << 16;
#endif
#if FLASH_CMD_READ_ID_BYTES >= 3
    id |= spiRxByte(FLASH_SPI_PORT) << 16;
#endif
#if FLASH_CMD_READ_ID_BYTES >= 2
    id |= spiRxByte(FLASH_SPI_PORT) << 8;
#endif
#if FLASH_CMD_READ_ID_BYTES >= 1
    id |= spiRxByte(FLASH_SPI_PORT);
#endif

    FLASH_CS(1, FALSE);

    return id;
}

void FlashRxBytes(UI32_t addr, UI08_t *bf, UI16_t size)
{
    FlashCsSet(addr, TRUE);

    spiTxByte(FLASH_SPI_PORT, FLASH_CMD_RX_DATA);

    spiTxByte(FLASH_SPI_PORT, (addr >> 16) & 0xFF);
    spiTxByte(FLASH_SPI_PORT, (addr >> 8) & 0xFF);
    spiTxByte(FLASH_SPI_PORT,  addr & 0xFF);

    spiTxRxBytes(FLASH_SPI_PORT, NULL, bf, size);

    FlashCsSet(addr, FALSE);

}