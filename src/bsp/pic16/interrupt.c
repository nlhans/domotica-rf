#include "bsp/interrupt.h"
#include "stddefs.h"

#include "devices/mrf49xa.h"

ExtIntHandler_t cb;

void ExtIntInit(void)
{
    OPTION_REGbits.INTEDG = 0;

    INTCONbits.INTF = 0;
    INTCONbits.INTE = 1;
    INTCONbits.GIE = 1;
}

void ExtIntDeinit(void)
{
    INTCONbits.INTE = 0;
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
        uint8_t ofw = 0;
        while (!Mrf49xaServe())
        {
            ofw++;
            if (ofw == 255)
            {
                ExtIntDeinit();
                Mrf49xaNeedsReset();
                break;
            }
        }
        INTCONbits.INTF = 0;
    }
}