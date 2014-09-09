#include "devices/mrf49xa.h"
#include "hardware/rf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    this->dataQuality = 0;
    this->airByte = 0;
    this->sof = false;

    for(i = 0; i < RF_MAX_CLIENTS; i++)
    {
        if (this->rfClients[i] == NULL) continue;
        if (this->rfClients[i]->mac->state == TX_PACKET)
        {
            this->dataQuality++;
            this->rfClients[i]->Tick();
        }
    }

    for(i = 0; i < RF_MAX_CLIENTS; i++)
    {
        if (this->rfClients[i] == NULL) continue;
        if (this->rfClients[i]->mac->state != TX_PACKET)
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
        if (this->rfClients[i] == NULL)
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


HwRfClient::HwRfClient(Device* dev, uint16_t id, HwRfMain* main)
{
    this->device = dev;

    this->id = id;
    this->main = main;

    this->mac = (Mrf49xaMac_t*) malloc(sizeof(Mrf49xaMac_t));

    this->mac->client = (void*) this;
    Mrf49xaInit(this->mac);

    this->SwitchBuffer(0);
}

HwRfClient::~HwRfClient()
{
    this->id = -1;

    free(this->mac);
}

void HwRfClient::SwitchBuffer(bool tx)
{
    if (tx)
    {
        this->mac->txPacket.crc = 0;
        this->mac->txPacket.state = PKT_WAITING_FOR_ACK;
    }
    else if(this->mac->hwRx != NULL)
    {
        this->mac->hwRx->state = PKT_HW_READY_RX;
        this->mac->hwRx->crc = 0;
    }

    this->mac->hwByte = 0;

    if (this->mac->rxPacket[0].state == PKT_FREE)
    {
        this->mac->hwRx = &(this->mac->rxPacket[0]);
        memset(this->mac->hwRx, 0, sizeof(rfTrcvPacket_t));
        this->mac->hwRx->state = PKT_HW_BUSY_RX;
    }
    else if (this->mac->rxPacket[1].state == PKT_FREE)
    {
        this->mac->hwRx = &(this->mac->rxPacket[1]);
        memset(this->mac->hwRx, 0, sizeof(rfTrcvPacket_t));
        this->mac->hwRx->state = PKT_HW_BUSY_RX;
    }
}

void HwRfClient::Tick()
{
    static uint8_t crcTx;

    // act as hardware first
    switch (this->mac->state)
    {
        case RECV_IDLE:

            if (this->main->dataQuality > 0 && this->main->sof)
            {
                this->mac->hwRx->raw[0] = this->main->airByte;
                this->mac->hwByte = 1;

                this->mac->hwRx->crc = this->main->airByte;

                this->mac->state = RECV_DATA;
            }

            break;

        case RECV_DATA:
            // Receive byte to buffer
            if (this->mac->hwByte >= this->mac->hwRx->packet.size + 1 &&
                this->mac->hwRx->packet.size != 0) // we've received length; switch buffer
            {
                if (this->mac->hwRx->crc != this->main->airByte)
                {
                    fprintf(stderr, "RX packet CRC fail %02X expected %02X calculated!\r\n", this->main->airByte, this->mac->hwRx->crc);
                }
                else
                {
                    fprintf(stdout, "RX packet!\r\n");
                }

                this->mac->state = RECV_IDLE;
                this->SwitchBuffer(0);
            }
            else if (this->main->dataQuality == 0)
            {
                fprintf(stderr, "RX error; lost signal! %d of %d\r\n", this->mac->hwByte, this->mac->hwRx->packet.size);

                memset(this->mac->hwRx->raw, 0, RF_PACKET_LENGTH);
                this->mac->hwByte = 0;

                this->mac->state = RECV_IDLE;
            }
            else
            {
                this->mac->hwRx->raw[this->mac->hwByte] = this->main->airByte;
                this->mac->hwByte++;

                this->mac->hwRx->crc = this->mac->hwRx->crc ^ this->main->airByte;
            }

            break;
        case TX_PACKET:

            this->main->sof |= (this->mac->hwByte == 0) ? true : false;

            if (this->mac->hwByte == this->mac->txPacket.packet.size)
            {
                this->main->airByte |= this->mac->txPacket.crc;
            }
            else
            {
                if (this->mac->hwByte == 0)
                    this->mac->txPacket.crc = 0 ^ this->mac->txPacket.raw[0];
                else
                    this->mac->txPacket.crc = this->mac->txPacket.crc ^ this->mac->txPacket.raw[this->mac->hwByte];

                this->main->airByte |= this->mac->txPacket.raw[this->mac->hwByte];
            }

            this->mac->hwByte++;

            if (this->mac->hwByte >= this->mac->txPacket.packet.size + 1 &&
                this->mac->txPacket.packet.size != 0)
            {
                fprintf(stdout, "TX packet; quality %d, CRC %02X\r\n", this->mac->hwByte, this->mac->hwRx->packet.size);

                this->SwitchBuffer(1);
                this->mac->txPacket.state = PKT_FREE;

                this->mac->state = RECV_IDLE;
                this->mac->txPacket.crc = 0;
            }
            break;
    }

    // Update status!
    this->status.flags.lsb.dataQualityOK = (this->main->dataQuality == 1);
    this->status.flags.msb.signalPresent = (this->main->dataQuality != 0);
}

