#ifndef RFSTACK_PACKETS_H
#define RFSTACK_PACKETS_H

#include "stddefs.h"
#include "rfstack/rf_defs.h"

#include "devices/mrf49xa.h"

void HandlePacket(rfTrcvPacket_t* packet);

extern uint32_t syncedTime;

#endif