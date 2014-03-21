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

static bool_t mrf49xaIsr(UI08_t foo);

void RfInit(void)
{
    RF_RES = 1;
    RF_POWER = 0;

    // Connect up MRF49XA ISR
    PPSUnLock;

    iPPSInput(IN_FN_PPS_INT2, IN_PIN_PPS_RP9);
    iPPSInput(IN_FN_PPS_T4CK, IN_PIN_PPS_RP9);
    ExtIntSetup(2, mrf49xaIsr, TRUE, 6);

    PPSLock;

    TMR4 = 0;
    T4CON = (1<<15) | (1<<1);

    RtosTaskCreate(&rfTask, "RF", RfTask, 40, rfTaskStk, sizeof(rfTaskStk));
    RtosTimerCreate(&rfTimer, 25, RfTick);

}

void RfTick(void)
{
    RtosTaskSignalEvent(&rfTask, RF_TICK);

    RtosTimerRearm(&rfTimer, 2);
}

UI08_t swtick = 0;

UI16_t mrfIsr;
UI16_t mrfDat;
UI16_t mrfStat;
UI08_t mrfInRx;
UI16_t mrfOf;
UI16_t mrfUf;
UI08_t mrfBadData;

UI16_t mrf49State;

bool_t mrf49xaIsr(UI08_t foo)
{

    // Check conflict with ethernet
    if (PORTCbits.RC8 == 0)
    {
        printf("SPI CS conflict\n");
    }

    // Foo==5 means it was called from the main thread.
    // Foo==2 when in ISR
    // We don't want to count ticks from main thread
    if (foo != 5)
    {
        swtick++;
    }

    do
    {
        mrfStat = mrf49State;
        mrf49State = MRF49XAReadStatus();

        if ((mrf49State & (1<<15)) != 0)
        {
            if (mrfInRx==1 && (mrf49State & (1<<7)) == 0)
            {
            }
            else
            {
                RfHalStatemachine();
            }
        }
        else if((mrf49State & (1<<14)) != 0)
        {
            MRF49XAReset();
            printf("$\n");
        }

        mrfIsr++;

    } while ((mrf49State & 0xC000) != 0);

    return (RF_IRQ == 1)?1:0;
}

extern void UartTxByte(char c);

void RfTask()
{
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
    RtosTaskDelay(100);
    printf(" done\n");

    UI16_t i, j;

    if (RF_IRQ == 0)
    {
        while (!mrf49xaIsr(5));
    }

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
        }

        if (evt & RF_TICK)
        {
            // Tick RX procces thread
            RfHalTickRxTh(&halRxBfTh);

            // Tick TX procces thread
            RfHalTickTxTh(&halTxBfTh);

            if (mrfIsr > 0)
            {
                UI16_t tick = TMR4;
                UI16_t myck = swtick;
                //printf("%04X | %04X | %04d | %04d | %02d\n", mrf49State, mrfStat, tick, myck, (tick-myck));
                mrfIsr=0;
                swtick=0; TMR4=0;
            }

            //for (i = 0; i < 100; i++)
            //    for(j = 0; j < 100; j++)
            //        asm volatile("nop");

        }
    }
}