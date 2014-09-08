#ifndef BSP_TIMER_H
#define BSP_TIMER_H

#include "stddefs.h"

typedef bool (*TimerHandler_t) (uint8_t ind, uint16_t count);

typedef enum TimerCfgType_e
{
    Periodic16Isr,
    Pwm,
    Capture
} TimerCfgType_t;
typedef struct TimerCfg_s
{
    uint8_t used:1;
    TimerCfgType_t type:7;

    union
    {
        struct
        {
            uint16_t period;
            uint16_t count;
            TimerHandler_t callback;
        } ISR;

        uint8_t data[6];
    };
} TimerCfg_t;

void Timer32Init(uint8_t index, uint8_t tmrDivider);

void Timer16InitPeriod(uint8_t index, uint32_t period);
void TimerInitPeriodic16Isr(uint8_t index, uint32_t period, TimerHandler_t callback);

#endif