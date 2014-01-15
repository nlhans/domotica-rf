#include "bsp/interrupt.h"
#include "stddefs.h"

static ExtIntInstance_t intHandlers[BSP_EXT_INT_COUNT];

void ExtIntDummy(UI08_t ind) { }

void ExtIntInit(void)
{
    UI08_t i = 0;
    for (i = 0; i < BSP_EXT_INT_COUNT; i++)
    {
        ExtIntSetup(i, NULL, 0);
    }
}

void ExtIntSetup(UI08_t ind, ExtIntHandler_t callback, bool_t fallingEdge)
{
    intHandlers[ind].ind = ind;
    intHandlers[ind].callback = ((callback == NULL) ? ExtIntDummy : callback);

    if (fallingEdge)
    {
        INTCON2 |= (1<<ind);
    }
    else
    {
        INTCON2 &= ~(1<<ind);
    }
    switch(ind)
    {
        case 0:
            IFS0 &= ~(1<<0);
            if (callback == NULL)
            {
                IEC0 &= ~(1<<0);
            }
            else
            {
                IEC0 |= 1<<0;
            }
            break;
        case 1:
            IFS1 &= ~(1<<4);
            if (callback == NULL)
            {
                IEC1 &= ~(1<<4);
            }
            else
            {
                IEC1 |= 1<<4;
            }
            break;
        case 2:
            IFS1 &= ~(1<<13);
            if (callback == NULL)
            {
                IEC1 &= ~(1<<13);
            }
            else
            {
                IEC1 |= 1<<13;
            }
            break;
    }
}

void __attribute__((__interrupt__,no_auto_psv)) _INT0Interrupt(void)
{
    IFS0 &= ~(1<<0);
    if (intHandlers[0].callback != NULL)
    intHandlers[0].callback(0);

}
void __attribute__((__interrupt__,no_auto_psv)) _INT1Interrupt(void)
{
    IFS1 &= ~(1<<4);
    if (intHandlers[1].callback != NULL)
        intHandlers[1].callback(1);

}
void __attribute__((__interrupt__,no_auto_psv)) _INT2Interrupt(void)
{
    IFS1 &= ~(1<<13);
    if (intHandlers[2].callback != NULL)
        intHandlers[2].callback(2);

}