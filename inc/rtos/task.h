#ifndef TASK_H
#define TASK_H
#define RTOS_DEBUG
#define RTOS_EVENTS

#include "stddefs.h"

#define RtosTime_t UI32_t

typedef enum RtosTaskState_e
{
    TASK_STATE_SUSPENDED,
    TASK_STATE_RUNNING,
    TASK_STATE_DELAY,
    TASK_STATE_EVENT,
    TASK_STATE_READY
} RtosTaskState_t;

typedef struct RtosTask_s
{
    struct RtosTask_t* list;
    void* method;
    UI08_t* stack;
    UI08_t* stackPosition;
    UI08_t priority;

    RtosTaskState_t state;

    //Time_t lastRun;
    RtosTime_t nextRun;

#ifdef RTOS_EVENTS
    UI16_t eventMask;
    UI16_t eventStore;
#endif

#ifdef RTOS_DEBUG
    RtosTime_t lastRun;
    RtosTime_t timeRan;
    UI16_t stackSize;
    UI16_t stackUsage;
    UI16_t stackMaxUsage;
    char* name;
#endif

} RtosTask_t;

extern const char* const RtosStateText[5];
extern RtosTask_t RtosTaskIdleObj;

RtosTime_t RtosGetTime();

void RtosTaskInit();
void RtosTaskCreate(RtosTask_t* task, char* name, void* function, UI08_t priority, UI08_t* stack, UI16_t stackSize);
void RtosTaskRun();

void RtosTaskTick();
void RtosTaskChange();

void RtosTaskDelay(RtosTime_t time);
void RtosTaskWake(RtosTask_t* task);

#ifdef RTOS_EVENTS
UI16_t RtosTaskWaitForEvent(UI16_t mask);
void RtosTaskSignalEvent(RtosTask_t* task, UI16_t event);
#endif

extern void RtosKernelPortInitStack(RtosTask_t* task);
extern void RtosKernelPortTimerStart();
extern void RtosKernelPortTimerClear();
extern inline void RtosKernelContextStart();
extern inline void RtosKernelContextSuspend();

#endif