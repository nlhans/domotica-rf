#include "stddefs.h"
#include "rtos/task.h"

typedef struct RtosPic24Stack_s
{
    UI16_t lowPc;
    UI16_t highPc;
    UI16_t sr;
    UI16_t w[15];
    UI16_t rcount;
    UI16_t tblpag;
    UI16_t corcon;
    UI16_t psvpag;
    UI16_t nest;
} RtosPic24Stack_t;

void RtosKernelPortInitStack(RtosTask_t* task)
{
    RtosPic24Stack_t *stack = (RtosPic24Stack_t*) task->stack;

    memset(stack, 0, sizeof(RtosPic24Stack_t));
    stack->lowPc = (UI16_t)task->method;
    stack->corcon = CORCON;
    stack->psvpag = PSVPAG;

    task->stackPosition = (UI08_t*)(stack+1);

}

void RtosKernelPortTimerStart()
{
    T5CON = 0;
    TMR5 = 0;

    PR5 = F_OSC_DIV_2/1000; // 1kHz

    RtosKernelPortTimerClear();
    IPC7bits.T5IP = 0x01; // Priority level
    IEC1bits.T5IE = 1; // Enable Timer 5 interrupts

    T5CONbits.TON = 1;
}

void RtosKernelPortTimerClear()
{
    IFS1bits.T5IF = 0;
}

void __attribute__((__interrupt__, __shadow__, auto_psv)) _T5Interrupt(void)
{
    RtosKernelPortTimerClear();
    RtosKernelContextSuspend();
}

inline void RtosKernelContextStart()
{
    asm volatile("CALL _RtosKernelStart");
}

inline void RtosKernelContextSuspend()
{
    asm volatile("CALL _RtosKernelContext");
}