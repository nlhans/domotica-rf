#ifndef __MRF49XA_H
#define __MRF49XA_H

#include "stddefs.h"

#include "rfstack/rf_defs.h"
#include "devices/mrf49xa_defs.h"

// -------
// mrf49xa.c
void Mrf49xaInit(void);

void Mrf49xaModeRx(void);
void Mrf49xaModeTx(void);

bool_t Mrf49xaSignalPresent(void);

#ifdef MRF49XA_POWER_SWITCH
void Mrf49xaBootup(void);
void Mrf49xaShutdown(void);
#endif

// -------
// mrf49xa_cmd.c
void Mrf49TxCmd(uint8_t cmd, uint8_t val);
uint8_t Mrf49RxCmd(uint8_t cmd);
void Mrf49RxSts(void);

uint8_t Mrf49RxByte(void);
void Mrf49TxByte(uint8_t byte);

// -------
// mrf49xa_data.c
#ifdef PIC24_HW
bool_t Mrf49xaServe(uint8_t foo);
#else
bool_t Mrf49xaServe(void);
#endif

// -------
// mrf49xa_packet.c
void Mrf49xaTick();

bool_t Mrf49xaPacketPending(void);

rfTrcvPacket_t* Mrf49xaRxPacket(void);
rfTrcvPacket_t* Mrf49xaAllocPacket(void);
void Mrf49xaFreePacket(rfTrcvPacket_t* packet);

bool_t Mrf49xaTxPacket(rfTrcvPacket_t* packet, bool_t response, bool_t needAck);
void Mrf49xaTxAck(rfTrcvPacket_t* packet);


// Platform dependant.
#ifdef PIC16_HW

#define MRF_DISABLE_INT     INTCONbits.INTE = 0;
#define MRF_ENABLE_INT      INTCONbits.INTE = 1;

// These delays may be longer than the function name suggests(!)
#define Delay5Ms() _delay(40000)
#define Delay50Ms() _delay(400000)

// -------
// mrf49xa_spi_pic16.c
void Mrf49SpiTx(uint8_t byte);
uint8_t Mrf49SpiRx(void);

#define RF_CS_ACQ() RF_SPI_CS = 0;
#define RF_CS_REL() RF_SPI_CS = 1;

#else
// -------
// bsp/spi.c

#include "utilities/spiArbiter.h"
#include "bsp/spi.h"

#define MRF_DISABLE_INT     IEC1bits.INT2IE = 0;
#define MRF_ENABLE_INT      IEC1bits.INT2IE = 1;

#define RF_CS_ACQ() spiArbRfAcquire();
#define RF_CS_REL() spiArbRfComplete();

#define Mrf49SpiTx(x) spiTx1(x)
#define Mrf49SpiRx() spiRx1()

#define Delay5Ms() RtosTaskDelay(10)
#define Delay50Ms() RtosTaskDelay(50)


#endif




#endif
