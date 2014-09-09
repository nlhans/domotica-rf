#include "hardware/rf.h"

#include "devices/mrf49xa.h"
#include "devices/device.h"

void Mrf49xaInit(Mrf49xaMac_t* inst)
{
    if (inst == NULL) return;
    inst->needsReset = false;

    //
    // Initialize MAC
    //
    inst->hwByte = 0;
    inst->hwRx   = NULL;
    inst->needsReset = 0;
    inst->nodeId = 0;

    inst->rxPacket[0].state = PKT_FREE;
    inst->rxPacket[1].state = PKT_FREE;

    inst->txPacket.state = PKT_FREE;
    if (inst->client == NULL) return;

    HwRfClient* client = (HwRfClient*) inst->client;
    client->SwitchBuffer(0);
}

void Mrf49xaNeedsReset(Mrf49xaMac_t* inst)
{
    inst->needsReset = true;
}

void Mrf49RxSts(Mrf49xaMac_t* inst)
{
    HwRfClient* client = (HwRfClient*) inst->client;

    inst->status.byte[0] = client->status.byte[0];
    inst->status.byte[1] = client->status.byte[1];
}

void Mrf49xaModeTx(Mrf49xaMac_t* inst)
{
    //
    inst->state = TX_PACKET;
    inst->hwByte = 0;

    HwRfClient* client = (HwRfClient*) inst->client;
}

void Mrf49xaModeRx(Mrf49xaMac_t* inst)
{
    //
    inst->state = RECV_IDLE;
    inst->hwByte = 0;

}

extern "C"
{
    void ExtIntInit(void)
    {
        // ?
    }

    void _Delay5Ms(Mrf49xaMac_t* inst)
    {
        HwRfClient* client = (HwRfClient*) inst->client;

        client->device->Sleepy(5);
    }
}
