#ifndef BSP_DMA_H
#define BSP_DMA_H

#include "stddefs.h"

typedef void (*DmaTransferCompleteHandler_t) (uint8_t ch);

// Direction, 0 = to peripheral(out) , 1 = from peripheral(in)
// bfA, bfB, hwReg are pointers to the buffer & peripheral
void DmaSetup(uint8_t ch, uint16_t bfA, uint16_t bfB, uint16_t* hwReg, uint8_t direction, uint8_t options, uint8_t req);
void DmaTransfer(uint8_t ch, uint16_t size);
bool_t DmaDone(void);
bool_t DmaIsBusy(uint8_t ch);
void DmaIrqCallback(uint8_t ch, DmaTransferCompleteHandler_t handler);

// dummy callback
void DmaDummy(uint8_t ch);

#endif