#include "devices/mrf49xa.h"

void Mrf49xaInit(Mrf49xaMac_t* inst)
{
    inst->needsReset = false;
}

void Mrf49xaNeedsReset(Mrf49xaMac_t* inst)
{
    inst->needsReset = true;
}

void ExtIntInit(void)
{
    // ?
}

void Mrf49RxSts(Mrf49xaMac_t* inst)
{

}

void Mrf49xaModeTx(Mrf49xaMac_t* inst)
{
    //
}

void Delay5Ms(void)
{
    //
}
