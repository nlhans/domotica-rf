#include "rf.h"

#include "devices/mrf49xa.h"

HwRfClient::HwRfClient(uint16_t id)
{
    this->id = id;

    this->mac = (Mrf49xaMac_t*) malloc(sizeof(Mrf49xaMac_t));
}

HwRfClient::~HwRfClient()
{
    this->id = -1;

    free(this->mac);
}

void HwRfMain::Tick()
{
    int i;

    this->airByte = 0;

    for(i = 0; i < RF_MAX_CLIENTS; i++)
    {
        if (this->rfClients[i]->mode == MODE_TX)
        {
            this->dataQuality++;
            this->rfClients[i]->Tick();
        }
    }

    for(i = 0; i < RF_MAX_CLIENTS; i++)
    {
        if (this->rfClients[i]->mode == MODE_RX)
        {
            this->rfClients[i]->Tick();
        }
    }

    usleep(100);
}

void HwRfClient::Tick()
{
    // act as hardware first
    if (this->mode == MODE_RX)
    {
        this->phyByte = this->main->airByte;

        // update status
    }
    else
    {
        this->main->airByte |= this->phyByte;
    }
}

