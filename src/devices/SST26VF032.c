#include "devices/SST26VF032.h"

void FlashInit(void)
{
    TRISC &= ~(1<<1);   // SIO2
    TRISB &= ~(1<<13);  // SIO3

    LATB |= 1<<13;
    LATC |= 1<<1;

    //
    FlashCsSet(0, 1);
    spiInit(FLASH_PORT);
    FlashCsSet(0, 1);
    asm("nop");
    FlashCsSet(0, 0);
    spiTxByte(FLASH_PORT, 0x1D); // 0x38 enable Quad IO
    spiRxByte(FLASH_PORT);
    spiRxByte(FLASH_PORT);
    FlashCsSet(0, 1);

    FlashReadId();
    sqiEnable(FLASH_PORT);
    
}

void FlashCsSet(UI32_t addr, bool_t state)
{
    //
    // For multiple flash chips; determine which one to use.
    //
    if(state == 1)
    {
        LATA |= (1<<0) | (1<<7);
    }
    else
    {
        if(addr < 0x400000)
            LATA &= ~(1<<0); // CS1
        else
            LATA &= ~(1<<7); // CS2
        // -> 0x000000 - 0x3FFFFF = cs2
        // -> 0x400000 - 0x7FFFFF = cs1
    }
    
}

UI08_t flashChipId[3];
UI08_t* FlashReadId(void)
{
    FlashCsSet(0, 0);

    sqiTxByte(FLASH_PORT, 0xAF); // read command
    flashChipId[0] = sqiRxByte(FLASH_PORT);
    flashChipId[1] = sqiRxByte(FLASH_PORT);
    flashChipId[2] = sqiRxByte(FLASH_PORT);
    FlashCsSet(0, 1);

    return flashChipId;
}
UI08_t FlashRxByte(UI32_t addr)
{
    sqiDisable(FLASH_PORT);
    // Tx read
    FlashCsSet(addr, 0);
    
    spiTxByte(FLASH_PORT, 0x03); // read command
    spiTxByte(FLASH_PORT, (addr >> 16) & 0xFF);
    spiTxByte(FLASH_PORT, (addr >> 8) & 0xFF);
    spiTxByte(FLASH_PORT, (addr & 0xFF));
    UI08_t data = spiRxByte(FLASH_PORT);
    FlashCsSet(addr, 1);

    sqiEnable(FLASH_PORT);
    return data;
}
void FlashRxBytes(UI32_t addr, UI08_t *bf, UI16_t size)
{
    sqiDisable(FLASH_PORT);
    FlashCsSet(addr, 0);
    
    spiTxByte(FLASH_PORT, 0x0B); // read command
    spiTxByte(FLASH_PORT, addr >> 16);
    spiTxByte(FLASH_PORT, addr >> 8);
    spiTxByte(FLASH_PORT, addr & 0xFF);
    spiTxByte(FLASH_PORT, 0x00); // dummy

    spiTxRxBytes(FLASH_PORT, NULL, bf, size);
    
    FlashCsSet(addr, 1);
    sqiEnable(FLASH_PORT);
}
void FlashTxBytes(UI32_t addr, UI08_t *bf, UI16_t size)
{
    FlashCsSet(addr, 0);
    sqiTxByte(FLASH_PORT, 0x06); // write enable
    FlashCsSet(addr, 1);

    asm volatile("nop");
    
    FlashCsSet(addr, 0);

    sqiTxByte(FLASH_PORT, 0x02); // read command
    
    sqiTxByte(FLASH_PORT, addr >> 16);
    sqiTxByte(FLASH_PORT, addr >> 8);
    sqiTxByte(FLASH_PORT, addr & 0xFF);

    sqiTxRxBytes(FLASH_PORT, bf, NULL, size);

    FlashCsSet(addr, 1);
}

void FlashEraseSector(UI32_t addr)
{
    //
    FlashCsSet(addr, 0);
    sqiTxByte(FLASH_PORT, 0x20); // erase sector
    sqiTxByte(FLASH_PORT, addr >> 16);
    sqiTxByte(FLASH_PORT, addr >> 8);
    sqiTxByte(FLASH_PORT, addr & 0xFF);
    FlashCsSet(addr, 1);
}