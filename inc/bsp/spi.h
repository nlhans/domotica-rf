#ifndef BSP_UART_H
#define BSP_UART_H

#include "stddefs.h"

void spiDeinit(UI08_t port);
void spiInit(UI08_t port);
void spiTxByte(UI08_t port, UI08_t byte);
UI08_t spiTxRxByte(UI08_t port, UI08_t byte);
UI08_t spiRxByte(UI08_t port);
void spiTxRxBytes(UI08_t port, UI08_t *dataTx, UI08_t *dataRx, UI16_t size);

void sqiEnable(UI08_t port);
void sqiDisable(UI08_t port);
void sqiTxByte(UI08_t port, UI08_t byte);
UI08_t sqiRxByte(UI08_t port);
UI08_t sqiTxRxByte(UI08_t port, UI08_t byte);
void sqiTxRxBytes(UI08_t port, UI08_t *txBf, UI08_t *rxBf, UI16_t size);

#endif