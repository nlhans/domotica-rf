#ifndef RFSTACK_RF_TASK
#define RFSTACK_RF_TASK

#include "rtos/task.h"

#include "devices/mrf49xa.h"
#include "rfstack/rf_defs.h"

extern RtosTask_t rfTask;
extern UI08_t mrfInRx;
extern Mrf49xaMac_t mrf49xaInst;

#define RF_RX_PACKET   0x01
#define RF_TX_PACKET   0x02
#define RF_PINGA         0x10
#define RF_TICK        0x80

#ifdef RF_DEBUG
typedef struct RfDiagnosticPacket_s
{
    RtosTime_t rxTime;
    RtosTime_t ackTime;
    uint8_t needAck;
    uint8_t direction;
    
    union
    {
        struct
        {
            uint8_t size;
            uint8_t src;
            uint8_t dst;
            uint8_t id;
            uint8_t opt;

            uint8_t data[16];
        } packet;
        uint8_t raw[21];
    };
    
    uint8_t crcHw;
    uint8_t crcSw;
}RfDiagnosticPacket_t;

extern uint8_t rfHistoryHead;
extern RfDiagnosticPacket_t rfHistoryPackets[RF_HISTORY_DEPTH];

#endif

void RfInit(void);

#endif