#ifndef BSP_TIMER_H
#define BSP_TIMER_H

#include "stddefs.h"

typedef bool_t (*TimerHandler_t) (UI08_t ind, UI16_t count);

typedef enum TimerCfgType_e
{
    Periodic16Isr,
    Pwm,
    Capture
} TimerCfgType_t;
typedef struct TimerCfg_s
{
    UI08_t used:1;
    TimerCfgType_t type:7;

    union
    {
        struct
        {
            UI16_t period;
            UI16_t count;
            TimerHandler_t callback;
        } ISR;

        UI08_t data[6];
    };
} TimerCfg_t;

void Timer32Init(UI08_t index, UI08_t tmrDivider);

void Timer16InitPeriod(UI08_t index, UI32_t period);
void TimerInitPeriodic16Isr(UI08_t index, UI32_t period, TimerHandler_t callback);

#endif