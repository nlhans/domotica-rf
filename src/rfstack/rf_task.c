#include "stddefs.h"

#include "rtos/task.h"
#include "rtos/timer.h"

#include "rfstack/rf_task.h"
#include "rfstack/hal.h"
#include "rfstack/packets.h"

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
    ExtIntSetup(2, mrf49xaIsr, TRUE, 6);

    PPSLock;
    
    RtosTaskCreate(&rfTask, "RF", RfTask, 40, rfTaskStk, sizeof(rfTaskStk));
    RtosTimerCreate(&rfTimer, 3, RfTick);

}

void RfTick(void)
{
    RtosTaskSignalEvent(&rfTask, RF_TICK);

    RtosTimerRearm(&rfTimer, 3);
}

UI16_t mrfIsr;
UI16_t mrfDat;
UI16_t mrfStat;
UI08_t mrfInRx;

void mrf49xaIsr(UI08_t foo)
{
    UI16_t mrf49State;

    do
    {
        mrfStat = mrf49State;
        mrf49State = MRF49XAReadStatus();

        /*if ((mrf49State & (1<<13)) != 0)
        {
            // Overflow FIFO
            MRF49XAReset();
            mrfStat = mrf49State;
            printf("err\n");
            break;
        }*/

        if ((mrf49State & (1<<15)) != 0)
        {
            if (mrfInRx==1 && (mrf49State & (1<<7)) == 0) {} else
            {
                mrfDat++;
                RfHalStatemachine();
            }
        }
        else if((mrf49State & (1<<14)) != 0)
        {
            MRF49XAReset();
            printf("por\n");
        }

        mrfIsr++;

    } while ((mrf49State & 0xC000) != 0 && 0);
}

void RfTask()
{
    UI08_t xc = 0;
    UI08_t rfInitialized = 0;

    RtosTaskDelay(1000);
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
            // Tick RX packet process thread
            RfPacketsTickTh(&halPkTh);
        }

        if (evt & RF_TX_PACKET)
        {
            //
            //printf("[RF] Tx\n");
        }

        if (evt & RF_TICK)
        {
            if (RF_IRQ == 0)
            {
                mrf49xaIsr(3);
            }

            // Tick RX procces thread
            RfHalTickRxTh(&halRxBfTh);
            
            // Tick TX procces thread
            RfHalTickTxTh(&halTxBfTh);

            xc++;
            if(xc>200 && 0)
            {
                xc=0;
                printf("[RF] sts: %04X / %d / %d of %d\n", MRF49XAReadStatus(), rfStatus.isr.state, rfStatus.isr.byteCounter, rfStatus.isr.txPacket->size);
            }

            while (mrfDat > 0 && 0)
            {
                mrfDat--;
                printf(".");
            }
#ifdef dsPIC33
            if(xc>250)
            {
                xc = 0;
                UI08_t dummy[20];
                UI08_t k;
                for (k = 0; k < 16; k++) dummy[k] = 0x55 + k;
                
                RfPacketTransmit(1, RF_PING, dummy, 16, 0);
            }
#endif
        }
    }
}