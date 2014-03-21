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
    RtosTimerCreate(&rfTimer, 3, RfTick);

}

void RfTick(void)
{
    RtosTaskSignalEvent(&rfTask, RF_TICK);

    RtosTimerRearm(&rfTimer, 3);
}

UI08_t swtick = 0;

UI16_t mrfIsr;
UI16_t mrfDat;
UI16_t mrfStat;
UI08_t mrfInRx;
UI16_t mrfOf;
UI16_t mrfUf;
UI08_t mrfBadData;

bool_t mrf49xaIsr(UI08_t foo)
{
    UI16_t mrf49State;

    if (PORTCbits.RC8 == 0)
    {
        printf("Conflict with ethernet found.");
    }

    if (foo != 5)
    {
        swtick++;
    }

    do
    {
        mrfStat = mrf49State;
        mrf49State = MRF49XAReadStatus();

        /*if ((mrf49State & (1<<13)) != 0)
        {
            if (RfHalInRxMode())
                mrfOf++;
            else
                mrfUf++;
        }*/

        if ((mrf49State & (1<<15)) != 0)
        {
            if (mrfInRx==1 && (mrf49State & (1<<7)) == 0)
            {
                //mrfBadData++;
            }
            else
            {
                mrfDat++;
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
    printf(" done\n");

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
            if (RF_IRQ == 0)
            {
                while (!mrf49xaIsr(5));
            }
            
            // Tick RX procces thread
            RfHalTickRxTh(&halRxBfTh);

            // Tick TX procces thread
            RfHalTickTxTh(&halTxBfTh);

            UI16_t tick = TMR4;
            UI16_t myck = swtick;
            if (tick != myck)
            {
                I08_t d = (tick - myck);
                if (d < 0)
                {
                    UartTxByte('-');
                    d = 0 - d;
                }
                if (d < 10)
                {
                    char m = '0' + d;
                    UartTxByte(m);
                }
                else
                {
                    printf("%d", d);
                }
                UartTxByte('\r');
                UartTxByte('\n');
            }
            if (tick != 0)
            {
                swtick=0; TMR4=0;
            }
            
            while (mrfOf > 0)
            {
                mrfOf--;
                printf("@");
            }

            while (mrfUf > 0)
            {
                mrfUf--;
                printf("#");
            }


            while (mrfBadData > 0)
            {
                mrfBadData--;
                printf("^");
            }

        }
    }
}