#ifndef BSP_SPI_H
#define BSP_SPI_H

#include "stddefs.h"

void spiDeinit(uint8_t port);
void spiInit(uint8_t port);
void spiSpeed(uint8_t port, bool fast);
/*
void spiTx1(uint8_t b);
void spiTx2(uint8_t b);
uint8_t spiRx1();
uint8_t spiRx2();*/
uint8_t spiTxRx1(uint8_t b);
uint8_t spiTxRx2(uint8_t b);

bool spiBusy1();

#define spiTxByte(p, b) ((p==1) ? spiTxRx1(b): spiTxRx2(b))
#define spiTxRxByte(p, b) ((p==1) ? spiTxRx1(b): spiTxRx2(b))
#define spiRxByte(p) ((p==1) ? spiTxRx1(0): spiTxRx2(0))

//void spiTxByte(uint8_t port, uint8_t byte);
//uint8_t spiRxByte(uint8_t port);
//uint8_t spiTxRxByte(uint8_t port, uint8_t byte);
void spiTxRxBytes(uint8_t port, uint8_t *dataTx, uint8_t *dataRx, uint16_t size);

#endif