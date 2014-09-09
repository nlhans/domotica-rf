#ifndef RTOS_TIMER
#define RTOS_TIMER

#include "stddefs.h"
#include "rtos/task.h"

typedef  void (*TimerHandler_t) ();

struct RtosTimer_s
{
    TimerHandler_t handler;
    RtosTime_t lastRun;
    RtosTime_t nextRun;
    uint16_t interval;
    uint8_t needsRunning;
    struct RtosTimer_s * p;
};

typedef struct RtosTimer_s RtosTimer_t;

void RtosTimerCreate(RtosTimer_t* tObj, uint16_t inTime, TimerHandler_t handler);
void RtosTimerRearm(RtosTimer_t* tObj, uint16_t inTime);

void RtosTimerTick(void);

#endif