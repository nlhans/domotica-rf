#include "stddefs.h"

#include "rtos/task.h"
#include "rtos/timer.h"

#include "tasks/rf_task.h"
#include "rfstack/packets.h"

#include "bsp/interrupt.h"

RtosTimer_t rfTimer;
RtosTimer_t rfPingTimer;

RtosTask_t rfTask;
UI08_t rfTaskStk[512];

static void RfTick();
static void RfTask();
void RfPing(void);

void RfInit(void)
{
    RF_RES = 1;
    RF_POWER = 0;

    // Connect up MRF49XA ISR

    PPSUnLock;

    iPPSInput(IN_FN_PPS_INT2, IN_PIN_PPS_RP9);
    iPPSInput(IN_FN_PPS_T4CK, IN_PIN_PPS_RP9);
    ExtIntSetup(2, Mrf49xaServe, TRUE, 6);

    PPSLock;

    TMR4 = 0;
    T4CON = (1<<15) | (1<<1);
    
    RtosTaskCreate(&rfTask, "RF", RfTask, 40, rfTaskStk, sizeof(rfTaskStk));
    RtosTimerCreate(&rfPingTimer, 25, RfPing);
    RtosTimerCreate(&rfTimer, 25, RfTick);

}

void RfPing(void)
{
    RtosTaskSignalEvent(&rfTask, RF_PINGA);

    RtosTimerRearm(&rfPingTimer, 25);
}

void RfTick(void)
{
    RtosTaskSignalEvent(&rfTask, RF_TICK);

    RtosTimerRearm(&rfTimer, 2);
}

extern void UartTxByte(char c);

void RfTask()
{
    rfTrcvPacket_t ping;
    UI08_t i;
    RtosTaskDelay(100);

    Mrf49xaInit();
    RtosTaskDelay(100);

    rfTrcvStatus.src = 1;

    while(1)
    {
        UI16_t evt = RtosTaskWaitForEvent(
                            RF_TICK | RF_PINGA);

        if (evt & RF_PINGA)
        {
            ping.packet.src = 1;
            ping.packet.dst = 0xFF;
            ping.packet.id = RF_PING;
            ping.packet.size = 0x10;
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