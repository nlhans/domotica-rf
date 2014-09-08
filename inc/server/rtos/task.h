#ifndef TASK_H
#define TASK_H
#define RTOS_DEBUG
#define RTOS_EVENTS

#include "stddefs.h"

#define RtosTime_t uint32_t

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
    uint8_t* stack;
    uint8_t* stackPosition;
    uint8_t priority;

    RtosTaskState_t state;

    //Time_t lastRun;
    RtosTime_t nextRun;

#ifdef RTOS_EVENTS
    uint16_t eventMask;
    uint16_t eventStore;
#endif

#ifdef RTOS_DEBUG
    RtosTime_t lastRun;
    RtosTime_t timeRan;
    uint16_t stackSize;
    uint16_t stackUsage;
    uint16_t stackMaxUsage;
    char* name;
#endif

} RtosTask_t;

#ifdef RTOS_DEBUG
extern const char* const RtosStateText[5];
#endif

extern RtosTask_t RtosTaskIdleObj;
extern RtosTime_t RtosTimestamp;

void RtosTaskInit();
void RtosTaskCreate(RtosTask_t* task, char* name, void* function, uint8_t priority, uint8_t* stack, uint16_t stackSize);
void RtosTaskRun();

void RtosTaskTick();
void RtosTaskChange();

void RtosTaskDelay(RtosTime_t time);
void RtosTaskWake(RtosTask_t* task);

#ifdef RTOS_EVENTS
uint16_t RtosTaskWaitForEvent(uint16_t mask);
void RtosTaskSignalEvent(RtosTask_t* task, uint16_t event);
#endif

extern void RtosKernelPortInitStack(RtosTask_t* task);
extern void RtosKernelPortTimerStart();
extern void RtosKernelPortTimerClear();
extern inline void RtosKernelContextStart();
extern inline void RtosKernelContextSuspend();

#endif