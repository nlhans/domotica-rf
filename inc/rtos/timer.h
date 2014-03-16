#ifndef RTOS_TIMER
#define RTOS_TIMER

#include "stddefs.h"

typedef  void (*TimerHandler_t) ();

struct RtosTimer_s
{
    TimerHandler_t handler;
    UI16_t interval;
    UI16_t lastRun;
    UI16_t nextRun;
    UI08_t needsRunning;
    struct RtosTimer_s * p;
};

typedef struct RtosTimer_s RtosTimer_t;

void RtosTimerCreate(RtosTimer_t* tObj, UI16_t inTime, TimerHandler_t handler);
void RtosTimerRearm(RtosTimer_t* tObj, UI16_t inTime);

void RtosTimerTick(void);

#endif