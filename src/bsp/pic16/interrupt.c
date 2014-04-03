#include "bsp/interrupt.h"
#include "stddefs.h"

ExtIntHandler_t callback;

void ExtIntInit(void)
{
}

void ExtIntSetup(UI08_t ind, ExtIntHandler_t callback, bool_t fallingEdge, UI08_t prio)
{

}

void interrupt extInt()
{
    //
}