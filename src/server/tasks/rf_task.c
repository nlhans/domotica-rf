#include "stddefs.h"
#include "config.h"

#include "rtos/task.h"
#include "rtos/timer.h"

#include "tasks/rf_task.h"
#include "rfstack/packets.h"

#include "bsp/interrupt.h"

RtosTimer_t rfTimer;
RtosTimer_t rfPingTimer;

RtosTask_t rfTask;
UI08_t rfTaskStk[512];

#ifdef RF_DEBUG
RfDiagnosticPacket_t rfHistoryPackets[RF_HISTORY_DEPTH];
uint8_t rfHistoryHead = 0;
#endif

static void RfTick();
static void RfTask();
void RfPing(void);

void RfInit(void)
{
    RF_RES = 1;
    RF_POWER = 0;
    
    RtosTaskCreate(&rfTask, "RF", RfTask, 40, rfTaskStk, sizeof(rfTaskStk));

#ifdef PIC24GB
    RtosTimerCreate(&rfPingTimer, 1000, RfPing);
#endif
    
    RtosTimerCreate(&rfTimer, 2, RfTick);

#ifdef RF_DEBUG
    uint8_t i = 0;
    for (i = 0; i < RF_HISTORY_DEPTH; i++)
        rfHistoryPackets[i].needAck = 0xFF;
#endif
}

void RfPing(void)
{
    RtosTaskSignalEvent(&rfTask, RF_PINGA);

    RtosTimerRearm(&rfPingTimer, 5000);
}

void RfTick(void)
{
    // Reduce CPU load of RF task.
    if (Mrf49xaPacketPending() || packetTx.state != PKT_FREE)
        RtosTaskSignalEvent(&rfTask, RF_TICK);
    RtosTimerRearm(&rfTimer, 2);
}

#ifdef RF_DEBUG
void rfHistoryPut(rfTrcvPacket_t* packet)
{
    if (packet->packet.id == RF_ACK)
    {
        uint8_t i ;
        uint8_t pt = rfHistoryHead;
        RfDiagnosticPacket_t* targetQueue = NULL;
        
        // Put ACK timestamp onto corresponding message.
        for (i = 0; i < RF_HISTORY_DEPTH; i++)
        {
            if (i > rfHistoryHead) pt = rfHistoryHead + RF_HISTORY_DEPTH - i;
            else  pt = rfHistoryHead - i;
            targetQueue = &(rfHistoryPackets[pt]);

            if (targetQueue->crcHw == packet->packet.data[1]
             && targetQueue->packet.id == packet->packet.data[0])
            {
                break;
            }
            else
            {
                targetQueue = NULL;
            }
        }
        if (targetQueue != NULL)
            targetQueue->ackTime = RtosTimestamp;
    }
    else
    {
        RfDiagnosticPacket_t* targetQueue = &(rfHistoryPackets[rfHistoryHead]);
        rfHistoryHead++;
        if (rfHistoryHead >= RF_HISTORY_DEPTH) rfHistoryHead = 0;

        targetQueue->rxTime = RtosTimestamp;

        memcpy(&(targetQueue->raw), &(packet->raw), RF_PACKET_LENGTH);
        targetQueue->crcHw = packet->crc;
        targetQueue->needAck = packet->needAck;
        if (packet == &(rfTrcvStatus.txPacket))
            targetQueue->direction = 1;
        else
            targetQueue->direction = 0;
        
        if (targetQueue->packet.size <= RF_PACKET_LENGTH)
            targetQueue->crcSw = targetQueue->raw[targetQueue->packet.size];

        
    }
}
#endif

void RfTask()
{
    rfTrcvPacket_t ping;
    UI08_t i;
    
    RtosTaskDelay(100);

    MRF_DISABLE_INT;
    Mrf49xaInit();

    // Connect up MRF49XA ISR
    PPSUnLock;

    iPPSInput(IN_FN_PPS_INT2, IN_PIN_PPS_RP9);
    ExtIntSetup(2, Mrf49xaServe, TRUE, 6);
    
    PPSLock;

    MRF_ENABLE_INT;

    RtosTaskDelay(100);

    cfgRam.nodeId = 1;

    while(1)
    {
        UI16_t evt = RtosTaskWaitForEvent(
                            RF_TICK | RF_PINGA);

        if (evt & RF_PINGA)
        {
            ping.packet.src = 1;
            ping.packet.dst = 0xFF;
            ping.packet.id = RF_PING;
            ping.packet.size = 16;
            ping.packet.opt = 0;

            ping.packet.data[0] = 1;
            for( i = 1; i < 16 ;i++)
                ping.packet.data[i] = i;
            
            Mrf49xaTxPacket(&ping, FALSE, FALSE);
        }

        if (evt & RF_TICK)
        {
            Mrf49xaTick();
        }
    }
}