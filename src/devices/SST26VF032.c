#include "devices/SST26VF032.h"

#ifdef PIC24GB

void FlashInit(void)
{
    FLASH_SIO2 = 1;
    FLASH_SIO3 = 1;
    
    FLASH_CS(1, false);
    FLASH_CS(2, false);
    spiInit(FLASH_SPI_PORT);
}

void FlashCsSet(uint32_t addr, bool state)
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

uint16_t FlashReadId(void)
{
    uint16_t id = 0;

    FLASH_CS(1, true);

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

    FLASH_CS(1, false);

    return id;
}

void FlashRxBytes(uint32_t addr, uint8_t *bf, uint16_t size)
{
    FlashCsSet(addr, true);

    spiTxByte(FLASH_SPI_PORT, FLASH_CMD_RX_DATA);

    spiTxByte(FLASH_SPI_PORT, (addr >> 16));
    spiTxByte(FLASH_SPI_PORT, (addr >> 8));
    spiTxByte(FLASH_SPI_PORT,  addr);

    spiTxRxBytes(FLASH_SPI_PORT, NULL, bf, size);

    FlashCsSet(addr, false);
}

#endif