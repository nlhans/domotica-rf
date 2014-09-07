#include "rfstack/packets.h"

#include "devices/mrf49xa.h"

void HandlePacket(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet)
{
    bool_t sendMsg = FALSE;
    bool_t sendAck = FALSE;

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
                sendMsg = TRUE;
                printf("Ping-pong\n");
            }
            else
            {
                //printf("Got ping back from %d\n", packet->packet.src);
            }
            break;

        case RF_POWER_STATUS:
            //TODO: Add node to client list
            sendMsg = FALSE;
            sendAck = TRUE;
            break;

        case RF_TIME_SYNC:
            syncedTime = *((uint32_t*) packet->packet.data);
            sendMsg = FALSE;
            sendAck = TRUE;
            break;

        case RF_APP_SAMPLE:
            sendAck = TRUE;
            break;
    }

    // TODO: RF data response statemachine
    if (sendMsg)
        Mrf49xaTxPacket(inst, packet, TRUE, sendAck);
    else if (sendAck)
        Mrf49xaTxAck(inst, packet);
    else
        Mrf49xaFreePacket(inst, packet);
}