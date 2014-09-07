#ifndef MRF49XA_BSP
#define MRF49XA_BSP
// -------
// bsp/spi.c

#include "power.h"

#define mrf49Inst ((Mrf49xaMac_t*)(&mrf49xaInst))

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

#endif
