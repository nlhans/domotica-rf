#ifndef SST26VF032_H
#define SST26VF032_H

#include "stddefs.h"
#include "bsp/spi.h"

#define FLASH_SPI_PORT 2

// There are multiple command ID definitions because of simulation & confusing
// of different chips.
#define FLASH_CMD_RX_DATA 0b00000011

#define FLASH_CMD_READ_ID 0b00011101

#define FLASH_CMD_READ_ID_BYTES 2

#define FLASH_CS2_SELECT        FLASH_CS2 = 0;
#define FLASH_CS2_DESELECT      FLASH_CS2 = 1;

#define FLASH_CS1_SELECT        FLASH_CS1 = 0;
#define FLASH_CS1_DESELECT      FLASH_CS1 = 1;

#define FLASH_CS(i, s) do { \
if (i == 1) {if (s) FLASH_CS1_SELECT else FLASH_CS1_DESELECT } \
else{ if (s) FLASH_CS2_SELECT else FLASH_CS2_DESELECT } } while (0); \

void FlashInit(void);
UI16_t FlashReadId(void);

void FlashCsSet(UI32_t addr, bool_t state);
void FlashRxBytes(UI32_t addr, UI08_t *bf, UI16_t size);
void FlashTxBytes(UI32_t addr, UI08_t *bf, UI16_t size);
void FlashEraseSector(UI32_t addr);

#endif