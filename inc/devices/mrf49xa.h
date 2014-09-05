#ifndef __MRF49XA_H
#define __MRF49XA_H

#include "stddefs.h"

#include "rfstack/rf_defs.h"
#include "devices/mrf49xa_defs.h"
#include "mrf49xa_bsp.h"

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

#endif
