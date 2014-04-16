#ifndef __MRF49XA_H
#define __MRF49XA_H

#include "stddefs.h"

#include "rfstack/rf_defs.h"
#include "devices/mrf49xa_defs.h"

#ifdef PIC16_HW

// -------
// mrf49xa.c
void Mrf49xaInit(void);
bool_t Mrf49xaTick(void);


void Mrf49xaModeRx(void);
void Mrf49xaModeTx(void);

#ifdef MRF49XA_POWER_SWITCH
void Mrf49xaBootup(void);
void Mrf49xaShutdown(void);
#endif

// -------
// mrf49xa_spi_pic16.c
void Mrf49SpiTx(uint8_t byte);
uint8_t Mrf49SpiRx(void);

// -------
// mrf49xa_cmd.c
void Mrf49TxCmd(uint8_t cmd, uint8_t val);
uint8_t Mrf49RxCmd(uint8_t cmd);
void Mrf49RxSts(void);

uint8_t Mrf49RxByte(void);
void Mrf49TxByte(uint8_t byte);

#define RF_CS_ACQ() RF_SPI_CS = 0;
#define RF_CS_REL() RF_SPI_CS = 1;

#else
// -------
// bsp/spi.c

#include "utilities/spiArbiter.h"

#define RF_CS_ACQ() spiArbRfAcquire();
#define RF_CS_REL() spiArbRfComplete();


#endif




























#endif
