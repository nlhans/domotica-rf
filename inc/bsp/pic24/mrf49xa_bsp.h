#ifndef MRF49XA_BSP
#define MRF49XA_BSP
// -------
// bsp/spi.c

#include "utilities/spiArbiter.h"
#include "bsp/spi.h"

#include "tasks/rf_task.h"

#define mrf49Inst ((Mrf49xaMac_t*)(&mrf49xaInst))

#define MRF_DISABLE_INT     IEC1bits.INT2IE = 0;
#define MRF_ENABLE_INT      IEC1bits.INT2IE = 1;

#define RF_CS_ACQ() spiArbRfAcquire();
#define RF_CS_REL() spiArbRfComplete();

#define HandlePacket HandlePacketServer

//#define Mrf49SpiTx(x) spiTxRx1(x)
//#define Mrf49SpiRx() spiTxRx1(0)

void Mrf49SpiTx(uint8_t byte);
uint8_t Mrf49SpiRx(void);

#define Delay5Ms() RtosTaskDelay(10)
#define Delay50Ms() RtosTaskDelay(50)

#endif

