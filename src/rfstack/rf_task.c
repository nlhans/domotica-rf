#include "stddefs.h"

#include "rtos/task.h"
#include "rtos/timer.h"

#include "rfstack/rf_task.h"
#include "rfstack/hal.h"

#include "bsp/interrupt.h"

RtosTimer_t rfTimer;

RtosTask_t rfTask;
UI08_t rfTaskStk[512];

static void RfTick();
static void RfTask();

static void mrf49xaIsr(UI08_t foo);

void RfInit(void)
{
    RF_RES = 1;
    RF_POWER = 0;

    // Connect up MRF49XA ISR
    PPSUnLock;

    iPPSInput(IN_FN_PPS_INT2, IN_PIN_PPS_RP9);
    ExtIntInit();
    ExtIntSetup(2, mrf49xaIsr, TRUE);

    PPSLock;
    
    RtosTaskCreate(&rfTask, "RF", RfTask, 40, rfTaskStk, sizeof(rfTaskStk));
    RtosTimerCreate(&rfTimer, 10, RfTick);

}

void RfTick(void)
{
    RtosTaskSignalEvent(&rfTask, RF_TICK);

    RtosTimerRearm(&rfTimer, 10);
}

UI16_t mrfIsr;
UI16_t mrfDat;
UI16_t mrfStat;

void mrf49xaIsr(UI08_t foo)
{
    UI16_t mrf49State;

    do
    {
        mrfStat = mrf49State;
        mrf49State = MRF49XAReadStatus();

        if ((mrf49State & (1<<13)) != 0)
        {
            // Overflow FIFO
            MRF49XAReset();
            mrfStat = mrf49State;
            break;
        }

        if ((mrf49State & (1<<15)) != 0 && (mrf49State & (1<<7)) != 0)
        {
            mrfDat++;
            RfHalStatemachine();
        }
        else if((mrf49State & (1<<14)) != 0)
        {
            MRF49XAReset();
        }

        mrfIsr++;

    } while ((mrf49State & 0xC000) != 0);
}

void RfTask()
{
    UI08_t rfInitialized = 0;

    printf("[RF] reset\n");
    RtosTaskDelay(100);
    RF_POWER = 1;
    RF_RES = 1;

    RtosTaskDelay(100);

    printf("[RF] Bootcycle\n");
    printf("1");
    RfHalInit();
    printf("2");
    MRF49XAInit();
    printf("3");
    MRF49XAReset();
    printf("4");
    printf(" done\n");

    rfInitialized = 1;

    while(1)
    {
        UI16_t evt = RtosTaskWaitForEvent(
                            RF_RX_PACKET |
                            RF_TX_PACKET |
                            RF_TICK);

        if (evt & RF_RX_PACKET)
        {
            //
            printf("[RF] Rx\n");
        }

        if (evt & RF_TX_PACKET)
        {
            //
            printf("[RF] Tx\n");
        }

        if (evt & RF_TICK && rfInitialized == 1)
        {
            if (RF_IRQ == 0)
            {
                mrf49xaIsr(3);
            }
            RfHalTick();
        }
    }
}