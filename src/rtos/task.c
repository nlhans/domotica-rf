#include "stddefs.h"
#include "rtos/task.h"

// TODO: Create interrupt handlers
// All interrupts are currently pushed on the application's task stack. 
// This means that if any interrupt is received, even the idle stack must
// be capable of supporting the required stack depth. Switching back to the OS
// stack (main()) would be best, but will require the interrupt handlers to run
// via the operating system.

// TODO: Create mailboxes/IPC in addition to events.
// Tasks should be able to create a small mailbox (e.g. 64 bytes of RAM) and
// wait for messages, before contiuning their work. This would not only be
// possible via own IPC implenentation and (abuse of) event handlers

/******* TEMP *******/
RtosTime_t RtosTimestamp = 0;
RtosTime_t RtosGetTime()
{
    return RtosTimestamp;
}


void RtosKernelRestoreTask(RtosTask_t* task);
void RtosKernelStoreTask(RtosTask_t* task);
#ifdef RTOS_DEBUG
const char* const RtosStateText[5] = {
    "SUSPENDED",
    "RUNNING",
    "WAIT FOR TIME (%lu/%lu)",
    "WAIT FOR SIGNAL",
    "READY"
};
#endif

RtosTask_t RtosTaskIdleObj;


static UI08_t RtosTaskIdleStk[80];

static RtosTask_t* RtosActiveTask;
volatile UI08_t* RtosKernelStackPos;
volatile UI16_t RtosCriticalNesting;


/* Idle task */
void RtosTaskIdleFnc()
{
    while(1)
    {
        asm volatile("PWRSAV #1");
    }
}

/* Initialize task kernel */
void RtosTaskInit()
{
    RtosTaskCreate(&RtosTaskIdleObj, "Idle", RtosTaskIdleFnc, 0, RtosTaskIdleStk, sizeof(RtosTaskIdleStk));
}

/* Initialize task object. */
void RtosTaskCreate(RtosTask_t* task, char* name, void* function, UI08_t priority, UI08_t* stack, UI16_t stackSize)
{
    if (task == &RtosTaskIdleObj)
    {
        // Initialize linked-list for first element.
        task->list = NULL;
    }
    else
    {
        // Initialize linked-list for next element
        task->list = RtosTaskIdleObj.list;
        RtosTaskIdleObj.list = (struct RtosTask_t*) task;
    }

#ifdef RTOS_DEBUG
    task->name = name;
    task->stackMaxUsage = 0;
    task->stackUsage = 0;
    task->timeRan = 0;
    task->lastRun = 0;
    task->stackSize = stackSize;

    // Fill stack with test pattern so we chan stack-growth
    memset(stack, 0x55, stackSize);
#endif
    task->method = function;
    task->nextRun = 0;
    task->priority = priority;
    task->stack = stack;
    task->state = TASK_STATE_READY;

    RtosKernelPortInitStack(task);

}

/* Start task kernel */
void RtosTaskRun()
{
    if (RtosTaskIdleObj.list == NULL)
        RtosKernelRestoreTask(&RtosTaskIdleObj);
    else
        RtosKernelRestoreTask((RtosTask_t*)RtosTaskIdleObj.list);
    
    RtosKernelPortTimerStart();
    RtosKernelContextStart();
}

/* Insert a delay inside a testk. Enforces context switch, too. */
void RtosTaskDelay(RtosTime_t time)
{
    RtosActiveTask->nextRun = RtosGetTime() + time;
    RtosActiveTask->state = TASK_STATE_DELAY;
    
    RtosKernelContextSuspend();
}

/* Enforces a task to be run ASAP. Only works when it's set for time delay. */
void RtosTaskWake(RtosTask_t* task)
{
    RtosActiveTask->nextRun = 0;
}

/* Change context. */
void RtosTaskChange()
{
    RtosKernelStoreTask(RtosActiveTask);

    RtosTimestamp ++;

    RtosTask_t* next = &RtosTaskIdleObj;
    RtosTask_t* t = &RtosTaskIdleObj;
    while (t != NULL)
    {
        switch(t->state)
        {
            case TASK_STATE_DELAY:
                if (t->nextRun > RtosGetTime())
                {
                    break;
                }
            case TASK_STATE_READY:
                if (t->priority >= next->priority)
                    next = t;
                break;

#ifdef RTOS_EVENTS
            case TASK_STATE_EVENT:
                // It's waiting forever.
                // TODO: Add timeouts.
                break;
#endif
            default:
                //t->state = TASK_STATE_SUSPENDED;
                break;
        }
        t = (RtosTask_t*)t->list;
    }

    RtosKernelRestoreTask(next);
}

/* Restore task context. */
void RtosKernelRestoreTask(RtosTask_t* task)
{
    RtosActiveTask = task;
    RtosKernelStackPos = task->stackPosition;
    //SPLIM = (UI16_t) (task->stack + task->stackSize) - 1;
    task->state = TASK_STATE_RUNNING;
}

/* Store task context. */
void RtosKernelStoreTask(RtosTask_t* task)
{
    task->stackPosition = (UI08_t*) RtosKernelStackPos;
    if (task->state == TASK_STATE_RUNNING)
    {
        task->state = TASK_STATE_READY;
    }
#ifdef RTOS_DEBUG
    task->lastRun = RtosGetTime();
    task->timeRan++;
    //TODO: Analayze stack
    task->stackUsage = ((UI16_t)task->stackPosition - (UI16_t)task->stack);
    if (task->stackUsage > task->stackMaxUsage)
        task->stackMaxUsage = task->stackUsage;
#endif
}


#ifdef RTOS_EVENTS
UI16_t RtosTaskWaitForEvent(UI16_t mask)
{
    // Suspend the current task untill the event is fired.
    RtosActiveTask->eventMask = mask;
    RtosActiveTask->eventStore &= ~mask;

    RtosActiveTask->state = TASK_STATE_EVENT;

    RtosKernelContextSuspend();

    return RtosActiveTask->eventStore;
}

void RtosTaskSignalEvent(RtosTask_t* task, UI16_t event)
{
    if (task == NULL)
    {
        //error
    }
    else
    {
        task->eventStore |= event;

        if ((event & task->eventMask) != 0)
        {
            task->state = TASK_STATE_READY;
        }
    }
    // Don't enforce a context switch. This is control of application.
    // Moreover, enforcing context switches would make this method not safe
    // for use in interrupts.
}
#endif