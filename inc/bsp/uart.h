#ifndef BSP_UART_H
#define BSP_UART_H

#include "stddefs.h"

void UartInit(uint8_t port, const uint32_t baud);

void UartTxStr(uint8_t port, const char * str);
void UartTxArr(uint8_t port, unsigned char * bf, uint16_t size);
void UartTxByte(uint8_t port, uint8_t byte);

#ifdef dsPIC33
bool_t UartTxDmaStatus(uint8_t port);
void UartTxDma(uint8_t port, uint8_t dmaCh, uint16_t bfDmaPtr, uint16_t size);
#endif

#endif