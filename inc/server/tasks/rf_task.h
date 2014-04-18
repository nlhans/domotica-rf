#ifndef RFSTACK_RF_TASK
#define RFSTACK_RF_TASK

#include "rtos/task.h"

extern RtosTask_t rfTask;
extern UI08_t mrfInRx;

#define RF_RX_PACKET   0x01
#define RF_TX_PACKET   0x02
#define RF_PINGA         0x10
#define RF_TICK        0x80

void RfInit(void);

#endif