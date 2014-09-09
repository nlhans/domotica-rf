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

void ExtIntSetup(uint8_t ind, ExtIntHandler_t callback, bool fallingEdge, uint8_t prio)
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

extern Mrf49xaMac_t mrf49xaInst;

void interrupt extInt()
{
    if (INTCONbits.INTF != 0)
    {
        uint8_t ofw = 0;
        while (!Mrf49xaServe(&mrf49xaInst))
        {
            ofw++;
            if (ofw == 255)
            {
                ExtIntDeinit();
                Mrf49xaNeedsReset(&mrf49xaInst);
                break;
            }
        }
        INTCONbits.INTF = 0;
    }
}