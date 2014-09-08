#include "bsp/timer.h"

TimerCfg_t hwTimers[BSP_TIMER_COUNT];

const uint32_t const divis[4] = {
    F_OSC_DIV_2/1,
    F_OSC_DIV_2/8, 
    F_OSC_DIV_2/64,
    F_OSC_DIV_2/256
};

void timerSetup(uint8_t index, uint16_t ctrlReg, uint16_t periodReg)
{
    printf("[Timer] Initializing timer %d\n", index);
    switch(index)
    {
        case 1:
            T1CON = 0;
            PR1 = periodReg;
            TMR1 = 0;
            T1CON = ctrlReg;
            break;
        case 2:
            T2CON = 0;
            PR2 = periodReg;
            TMR2 = 0;
            T2CON = ctrlReg;
            break;
        case 3:
            T3CON = 0;
            PR3 = periodReg;
            TMR3 = 0;
            T3CON = ctrlReg;
            break;
        case 4:
            T4CON = 0;
            PR4 = periodReg;
            TMR4 = 0;
            T4CON = ctrlReg;
            break;
        case 5:
            T5CON = 0;
            PR5 = periodReg;
            TMR5 = 0;
            T5CON = ctrlReg;
            break;

    }
}

void Timer16InitPeriod(uint8_t index, uint32_t period)
{
    uint8_t i, tmrDivider = 0;
    uint32_t tmrPeriod = 0;

    // Calculate maximum period for each division setting
    for (i = 0; i < 4; i++)
    {
        tmrPeriod = divis[i] / period;
        if (i < 0xFFFF)
            break;
    }

    timerSetup(index, (1<<15) | (tmrDivider << 4), tmrPeriod);
}

void Timer32Init(uint8_t index, uint8_t tmrDivider)
{
    timerSetup(index, (1<<15) | (1<<3) | (tmrDivider << 4), 0xFFFF);
    timerSetup(index+1, (1<<15) | (tmrDivider << 4), 0xFFFF);
}

void TimerInitPeriodic16Isr(uint8_t index, uint32_t period, TimerHandler_t callback)
{
    if (hwTimers[index-1].used == true || index >= BSP_TIMER_COUNT)
    {
        // TODO: Error?
    }
    
    hwTimers[index-1].used = TRUE;
    hwTimers[index-1].type = Periodic16Isr;
    hwTimers[index-1].ISR.callback = callback;
    
    Timer16InitPeriod(index, period);

    switch(index)
    {
        case 1:
            IFS0 &= ~(1<<3);
            if (callback == NULL)
            {
                IEC0 &= ~(1<<3);
            }
            else
            {
                IEC0 |= 1<<3;
            }
            break;
        case 2:
            IFS0 &= ~(1<<7);
            if (callback == NULL)
            {
                IEC0 &= ~(1<<7);
            }
            else
            {
                IEC0 |= 1<<7;
            }
            break;
        case 3:
            IFS0 &= ~(1<<8);
            if (callback == NULL)
            {
                IEC0 &= ~(1<<8);
            }
            else
            {
                IEC0 |= 1<<8;
            }
            break;
        case 4:
            IFS1 &= ~(1<<11);
            if (callback == NULL)
            {
                IEC1 &= ~(1<<11);
            }
            else
            {
                IEC1 |= 1<<11;
            }
            break;
        case 5:
            IFS1 &= ~(1<<12);
            if (callback == NULL)
            {
                IEC1 &= ~(1<<12);
            }
            else
            {
                IEC1 |= 1<<12;
            }
            break;
    }
}

/*void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{
    IFS0 &= ~(1<<3);
    if (hwTimers[0].ISR.callback(0, hwTimers[0].ISR.count))
        hwTimers[0].ISR.count = 0;
    else
        hwTimers[0].ISR.count++;
}*/