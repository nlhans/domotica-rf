#include <QDebug>

#include "rf.h"
#include "devices/mrf49xa.h"

#include <stdio.h>

/*************************** RF HUB ******************************/

HwRfMain::HwRfMain()
{
    int i;

    for(i = 0; i < RF_MAX_CLIENTS; i++)
    {
        this->rfClients[i] = NULL;
    }
}

void HwRfMain::Tick()
{
    int i;

    this->airByte = 0;

    for(i = 0; i < RF_MAX_CLIENTS; i++)
    {
        if (this->rfClients[i] == NULL) continue;
        if (this->rfClients[i]->mode == MODE_TX)
        {
            this->dataQuality++;
            this->rfClients[i]->Tick();
            qDebug() << "Client TX";
        }
    }

    for(i = 0; i < RF_MAX_CLIENTS; i++)
    {
        if (this->rfClients[i] == NULL) continue;
        if (this->rfClients[i]->mode == MODE_RX)
        {
            this->rfClients[i]->Tick();
        }
    }

    this->msleep(1);
}

void HwRfMain::Connect(HwRfClient *client)
{
    int i;

    for(i = 0; i < RF_MAX_CLIENTS; i++)
    {
        if (this->rfClients[i] != NULL)
        {
            this->rfClients[i] = client;
            break;
        }
    }
}

void HwRfMain::Disconnect(HwRfClient *client)
{
    int i;

    for(i = 0; i < RF_MAX_CLIENTS; i++)
    {
        if (this->rfClients[i] == client)
        {
            this->rfClients[i] = NULL;
        }
    }
}

/*************************** RF CLIENT ******************************/


HwRfClient::HwRfClient(uint16_t id, HwRfMain* main)
{
    this->id = id;
    this->main = main;

    this->mac = (Mrf49xaMac_t*) malloc(sizeof(Mrf49xaMac_t));

    memset(this->mac, 0, sizeof(Mrf49xaMac_t));
    //
    // Initialize MAC
    this->mac->hwByte = 0;
    this->mac->hwRx   = this->mac->rxPacket;
    this->mac->needsReset = 0;
    this->mac->nodeId = 0;

    this->mac->rxPacket[0].state = PKT_FREE;
    this->mac->rxPacket[1].state = PKT_FREE;
}

HwRfClient::~HwRfClient()
{
    this->id = -1;

    free(this->mac);
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

