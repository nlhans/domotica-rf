#include "rtos/timer.h"
#include "rtos/task.h"

UI08_t rtosTimerChainStarted = 0;
RtosTimer_t* rtosTimerChain;

void RtosTimerCreate(RtosTimer_t* tObj, UI16_t inTime, TimerHandler_t handler)
{
    if (rtosTimerChainStarted == 0)
    {
        rtosTimerChain = tObj;
        rtosTimerChainStarted = 1;
    }
    else
    {
        RtosTimer_t* t;
        for(t = rtosTimerChain; t->p != NULL; t = t->p);
        t->p = tObj;

    }

    tObj->handler = handler;
    RtosTimerRearm(tObj, inTime);
}

void RtosTimerRearm(RtosTimer_t* tObj, UI16_t inTime)
{
    tObj->lastRun = RtosTimestamp;
    tObj->nextRun = RtosTimestamp + inTime;
    tObj->needsRunning = 1;
}

void RtosTimerTick(void)
{
    RtosTimer_t* t;
    if (rtosTimerChainStarted == 0) return;
    for(t = rtosTimerChain; ; t = t->p)
    {
        if (t->needsRunning == 1 && RtosTimestamp >= t->nextRun)
        {
            t->needsRunning = 0;
            t->handler();
        }
        if (t->p == NULL) break;
    }
}