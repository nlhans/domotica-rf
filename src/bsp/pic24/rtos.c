#include "stddefs.h"
#include "rtos/task.h"

void RtosKernelPortInitStack(RtosTask_t* task)
{
    UI08_t i = 0;
    UI16_t* TOS = task->stack;

    *TOS = (int)task->method; TOS++;        // low byte PC
    *TOS = 0; TOS++;                        // high byte PC
    *TOS = 0; TOS++;                        // initial SR
    *TOS = 0; TOS++;                        // W0.

    // Add W1-W14, RCOUNT and TBLPAG
    for (i = 0; i < 16; i++)
    {
        *TOS = 0; TOS++;
    }

    // Add CORCON and PSVPAG
    *TOS = CORCON; TOS++;                        // CORCON - why save this?
    *TOS = PSVPAG; TOS++;                        // PSVPAG
    *TOS = 0; TOS++;                             // Nesting depth

    task->stackPosition = TOS;
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