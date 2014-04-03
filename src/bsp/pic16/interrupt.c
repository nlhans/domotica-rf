#include "bsp/interrupt.h"
#include "stddefs.h"

extern bool_t mrf49XaIsr();

ExtIntHandler_t cb = mrf49XaIsr;

void ExtIntInit(void)
{
    OPTION_REGbits.INTEDG = 0;

    INTCONbits.INTF = 0;
    INTCONbits.INTE = 1;
    INTCONbits.GIE = 1;
}

void ExtIntSetup(UI08_t ind, ExtIntHandler_t callback, bool_t fallingEdge, UI08_t prio)
{
    cb = callback;
    INTCONbits.INTF = 0;
    INTCONbits.INTE = 1;
    INTCONbits.GIE = 1;

    if(fallingEdge)
        OPTION_REGbits.INTEDG = 0;
    else
        OPTION_REGbits.INTEDG = 1;
    
}

void interrupt extInt()
{
    if (INTCONbits.INTF != 0)
    {
        mrf49XaIsr();
        //cb(0);
        INTCONbits.INTF = 0;
    }
}