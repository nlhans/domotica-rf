#include "bsp/interrupt.h"
#include "stddefs.h"

static ExtIntInstance_t intHandlers[BSP_EXT_INT_COUNT];

void ExtIntDummy(UI08_t ind) { }

void ExtIntInit(void)
{
    UI08_t i = 0;
    for (i = 0; i < BSP_EXT_INT_COUNT; i++)
    {
        ExtIntSetup(i, NULL, 0, 0);
    }
}

void ExtIntSetup(UI08_t ind, ExtIntHandler_t callback, bool_t fallingEdge, UI08_t prio)
{
    intHandlers[ind].callback = ((callback == NULL) ? ExtIntDummy : callback);

    switch(ind)
    {
        case 0:
            INTCON2bits.INT0EP = (fallingEdge != 0) ? 1 : 0;
            IFS0bits.INT0IF = 0;
            IEC0bits.INT0IE = (callback == NULL) ? 0 : 1;
            IPC0bits.INT0IP = prio;
            break;
        case 1:
            INTCON2bits.INT1EP = (fallingEdge != 0) ? 1 : 0;
            IFS1bits.INT1IF = 0;
            IEC1bits.INT1IE = (callback == NULL) ? 0 : 1;
            IPC5bits.INT1IP = prio;
            break;
        case 2:
            INTCON2bits.INT2EP = (fallingEdge != 0) ? 1 : 0;
            IFS1bits.INT2IF = 0;
            IEC1bits.INT2IE = (callback == NULL) ? 0 : 1;
            IPC7bits.INT2IP = prio;
            break;
    }
}

void __attribute__((__interrupt__,no_auto_psv)) _INT0Interrupt(void)
{
    if (intHandlers[0].callback != NULL)
        if (intHandlers[0].callback(0))
            IFS0bits.INT0IF = 0;
}
void __attribute__((__interrupt__,no_auto_psv)) _INT1Interrupt(void)
{
    if (intHandlers[1].callback != NULL)
        if (intHandlers[1].callback(1))
            IFS1bits.INT1IF = 0;
}
void __attribute__((__interrupt__,no_auto_psv)) _INT2Interrupt(void)
{
    if (intHandlers[2].callback != NULL)
        if (intHandlers[2].callback(2))
            IFS1bits.INT2IF = 0;
}