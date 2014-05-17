#ifndef RFSTACK_PACKETS_H
#define RFSTACK_PACKETS_H

#include "stddefs.h"
#include "rfstack/rf_defs.h"

#include "devices/mrf49xa.h"

#define FW_RUNTIME_MAJOR 0
#define FW_RUNTIME_MINOR 1

#define FW_APPLICATION_MAJOR_LOC 0x0
#define FW_APPLICATION_MINOR_LOC 0x1
#define FW_APPLICATION_VERSION 0x0

#define FW_APPLICATION_STATE 0x2

void RfSendPowerState(void);
void HandlePacket(rfTrcvPacket_t* packet);

extern uint32_t syncedTime;

#endif