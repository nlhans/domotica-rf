#ifndef __MRF49XA_H
#define __MRF49XA_H

#include "stddefs.h"

#include "rfstack/rf_defs.h"
#include "devices/mrf49xa_defs.h"

// -------
// mrf49xa.c
Mrf49xaMac_t* Mrf49xaInit(void);

void Mrf49xaModeRx(void);
void Mrf49xaModeTx(void);
void Mrf49xaModeSleep(void);

void Mrf49xaNeedsReset(void);

bool Mrf49xaSignalPresent(void);

#ifdef MRF49XA_POWER_SWITCH
void Mrf49xaReboot(void);
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
bool Mrf49xaServe(uint8_t foo);
#else
bool Mrf49xaServe(void);
#endif

// -------
// mrf49xa_packet.c
void Mrf49xaTick(Mrf49xaMac_t* inst);

bool Mrf49xaPacketPending(Mrf49xaMac_t* inst);

rfTrcvPacket_t* Mrf49xaRxPacket(Mrf49xaMac_t* inst);
rfTrcvPacket_t* Mrf49xaAllocPacket(Mrf49xaMac_t* inst);
void Mrf49xaFreePacket(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet);

bool Mrf49xaTxPacket(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet, bool response, bool needAck);
bool Mrf49xaTxAck(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet);


// Platform dependant.
#ifdef PIC16_HW
#include "power.h"

#define MRF_DISABLE_INT     INTCONbits.INTE = 0;
#define MRF_ENABLE_INT      INTCONbits.INTE = 1;

// These delays may be longer than the function name suggests(!)
extern void LoseTime(uint16_t t);

#define Delay5Ms() Sleepy(5)
#define Delay50Ms() Sleepy(64)

//#define Delay5Ms() _delay(40000)
//#define Delay50Ms() _delay(400000)

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

//#define Mrf49SpiTx(x) spiTxRx1(x)
//#define Mrf49SpiRx() spiTxRx1(0)

void Mrf49SpiTx(uint8_t byte);
uint8_t Mrf49SpiRx(void);

#define Delay5Ms() RtosTaskDelay(10)
#define Delay50Ms() RtosTaskDelay(50)


#endif




#endif
