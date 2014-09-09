#include "stddefs.h"
#include "rtos/task.h"

typedef struct RtosPic24Stack_s
{
    uint16_t lowPc;
    uint16_t highPc;
    uint16_t sr;
    uint16_t w[15];
    uint16_t rcount;
    uint16_t tblpag;
    uint16_t corcon;
    uint16_t psvpag;
    uint16_t nest;
} RtosPic24Stack_t;

void RtosKernelPortInitStack(RtosTask_t* task)
{
    RtosPic24Stack_t *stack = (RtosPic24Stack_t*) task->stack;

    memset(stack, 0, sizeof(RtosPic24Stack_t));
    stack->lowPc = (uint16_t)task->method;
    stack->corcon = CORCON;
    stack->psvpag = PSVPAG;

    task->stackPosition = (uint8_t*)(stack+1);

}

void RtosKernelPortTimerStart()
{
    T1CON = 0;
    TMR1 = 0;

    PR1 = F_OSC_DIV_2/1000; // 1kHz

    RtosKernelPortTimerClear();
    IPC0bits.T1IP = 1;
    IEC0bits.T1IE = 1;

    T1CONbits.TON = 1;
/*
    IPC7bits.T5IP = 0x01; // Priority level
    IEC1bits.T5IE = 1; // Enable Timer 5 interrupts
    T5CONbits.TON = 1;*/
}

void RtosKernelPortTimerClear()
{
    IFS0bits.T1IF = 0;
}

void __attribute__((__interrupt__, __shadow__, auto_psv)) _T1Interrupt(void)
{
    RtosKernelPortTimerClear();
    RtosTimerTick();
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