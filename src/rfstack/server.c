#include "rfstack/packets.h"

#include "devices/mrf49xa.h"

void HandlePacketServer(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet)
{
    bool sendMsg = false;
    bool sendAck = false;

    // Ping-pong
    switch (packet->packet.id)
    {
        case RF_ACK:
            if (inst->txPacket.crc == packet->packet.data[1] &&
                inst->txPacket.packet.id == packet->packet.data[0])
            {
                inst->txPacket.needAck = ACK_RECEIVED;
            }
            break;
            
        case RF_PING:
            if (packet->packet.data[0] == 1)
            {
                packet->packet.data[0] = 2;
                sendMsg = true;
                printf("Ping-pong\n");
            }
            else
            {
                //printf("Got ping back from %d\n", packet->packet.src);
            }
            break;

        case RF_POWER_STATUS:
            //TODO: Add node to client list
            sendMsg = false;
            sendAck = true;
            break;

        case RF_TIME_SYNC:
            syncedTime = *((uint32_t*) packet->packet.data);
            sendMsg = false;
            sendAck = true;
            break;

        case RF_APP_SAMPLE:
            sendAck = true;
            break;
    }

    // TODO: RF data response statemachine
    if (sendMsg)
        Mrf49xaTxPacket(inst, packet, true, sendAck);
    else if (sendAck)
        Mrf49xaTxAck(inst, packet);
    else
        Mrf49xaFreePacket(inst, packet);
}
