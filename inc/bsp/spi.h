#ifndef BSP_UART_H
#define BSP_UART_H

#include "stddefs.h"

void spiDeinit(UI08_t port);
void spiInit(UI08_t port);

void spiTx1(UI08_t b);
void spiTx2(UI08_t b);
UI08_t spiRx1();
UI08_t spiRx2();
UI08_t spiTxRx1(UI08_t b);
UI08_t spiTxRx2(UI08_t b);

bool_t spiBusy1();

#define spiTxByte(p, b) ((p==1) ? spiTx1(b): spiTx2(b))
#define spiTxRxByte(p, b) ((p==1) ? spiTxRx1(b): spiTxRx2(b))
#define spiRxByte(p) ((p==1) ? spiRx1(): spiRx2())

//void spiTxByte(UI08_t port, UI08_t byte);
//UI08_t spiRxByte(UI08_t port);
//UI08_t spiTxRxByte(UI08_t port, UI08_t byte);
void spiTxRxBytes(UI08_t port, UI08_t *dataTx, UI08_t *dataRx, UI16_t size);

#endif