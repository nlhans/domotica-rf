#ifndef DBG_DBG_TASK_H
#define DBG_DBG_TASK_H

#include "stddefs.h"

#include "devices/mrf49xa.h"

#define HISTORY_SIZE 32
extern rfTrcvPacket_t historyA[HISTORY_SIZE];
extern rfTrcvPacket_t historyB[HISTORY_SIZE];
extern rfTrcvPacket_t* bfHw;
extern rfTrcvPacket_t* bfSw;
extern uint16_t bfSwPacket;

void DbgInit(void);
// Buffer overflow; transfer now
void DbgTransferPackets(void);

#endif