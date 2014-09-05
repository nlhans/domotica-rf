#ifndef __MRF49XA_H
#define __MRF49XA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stddefs.h"

#include "rfstack/rf_defs.h"
#include "devices/mrf49xa_defs.h"
#include "mrf49xa_bsp.h"

// Code used for initialzing registers into INIT, RX, TX and SLEEP states.
typedef struct Mrf49InitReg_s
{
    uint8_t reg;
    uint8_t val;
}Mrf49InitReg_t;
#define REG(a, b) { a, b}

#define SetupRegisters(type) SetupRegistersLoop(mrfRegset_## type, mrfRegset_## type ##Cnt)
#define SetupRegistersWithoutDelay(type) SetupRegistersLoopWithoutDelay(mrfRegset_## type, mrfRegset_## type ##Cnt)

#define SetupRegistersLoopWithoutDelay(array, count) for (k = 0; k < count; k++) { Mrf49TxCmd(array[k].reg, array[k].val); }

#define SetupRegistersLoop(array, count) for (k = 0; k < count; k++) { \
    if (array[k].reg == REG_DELAY) { Delay5Ms(); } else \
{ Mrf49TxCmd(array[k].reg, array[k].val); } }



// -------
// mrf49xa.c
void Mrf49xaInit(Mrf49xaMac_t* inst);

void Mrf49xaModeRx(Mrf49xaMac_t* inst);
void Mrf49xaModeTx(Mrf49xaMac_t* inst);
void Mrf49xaModeSleep(Mrf49xaMac_t* inst);

void Mrf49xaNeedsReset(Mrf49xaMac_t* inst);

bool Mrf49xaSignalPresent(Mrf49xaMac_t* inst);

#ifdef MRF49XA_POWER_SWITCH
void Mrf49xaReboot(Mrf49xaMac_t* inst);
void Mrf49xaShutdown(Mrf49xaMac_t* inst);
#endif

// -------
// mrf49xa_cmd.c
void Mrf49TxCmd(uint8_t cmd, uint8_t val);
uint8_t Mrf49RxCmd(uint8_t cmd);
void Mrf49RxSts(Mrf49xaMac_t* inst);

uint8_t Mrf49RxByte(void);
void Mrf49TxByte(uint8_t byte);

// -------
// mrf49xa_phy.c
bool Mrf49xaServe(Mrf49xaMac_t* inst);

// -------
// mrf49xa_mac.c
void Mrf49xaTick(Mrf49xaMac_t* inst);

bool Mrf49xaPacketPending(Mrf49xaMac_t* inst);

rfTrcvPacket_t* Mrf49xaRxPacket(Mrf49xaMac_t* inst);
rfTrcvPacket_t* Mrf49xaAllocPacket(Mrf49xaMac_t* inst);
void Mrf49xaFreePacket(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet);

bool Mrf49xaTxPacket(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet, bool response, bool needAck);
bool Mrf49xaTxAck(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet);

#ifdef __cplusplus
}
#endif
#endif
