#ifndef SST26VF032_H
#define SST26VF032_H

#include "stddefs.h"
#include "bsp/spi.h"

#define FLASH_PORT 2

void FlashInit(void);
void FlashCsSet(UI32_t addr, bool_t state);
UI08_t FlashRxByte(UI32_t addr);
void FlashRxBytes(UI32_t addr, UI08_t *bf, UI16_t size);
void FlashTxByte(UI32_t addr);
void FlashTxBytes(UI32_t addr, UI08_t *bf, UI16_t size);
void FlashEraseSector(UI32_t addr);
UI08_t* FlashReadId(void);

#endif