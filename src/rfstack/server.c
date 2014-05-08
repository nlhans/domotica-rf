#include "rfstack/packets.h"

void HandlePacket(rfTrcvPacket_t* packet)
{
    bool_t sendMsg = FALSE;
    bool_t sendAck = FALSE;

    // Ping-pong
    switch (packet->packet.id)
    {
        case RF_ACK:
            if (packetTx.crc == packet->packet.data[1] &&
                packetTx.packet.id == packet->packet.data[0])
            {
                packetTx.needAck = ACK_RECEIVED;
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

        case RF_POR:
            //TODO: Add node to client list
            sendMsg = FALSE;
            sendAck = TRUE;
            break;

        case RF_TIMESYNC:
            syncedTime = *((uint32_t*) packet->packet.data);
            sendMsg = FALSE;
            sendAck = TRUE;
            break;
    }

    // TODO: RF data response statemachine
    if (sendMsg)
        Mrf49xaTxPacket(packet, TRUE, sendAck);
    else if (sendAck)
        Mrf49xaTxAck(packet);
    else
        Mrf49xaFreePacket(packet);
}