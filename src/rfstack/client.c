#include "rfstack/packets.h"

void RfSendPor(void)
{
    rfTrcvPacket_t* packet = Mrf49xaAllocPacket();

    packet->packet.size = 2;
    packet->packet.id = RF_POR;
    packet->packet.dst = 0xFF;
    
    packet->packet.data[0] = 0x55;
    packet->packet.data[1] = 0xAA;

    Mrf49xaTxPacket(packet, FALSE, TRUE);
}

void HandlePacket(rfTrcvPacket_t* packet)
{
    bool_t sendMsg = FALSE;
    bool_t sendAck = FALSE;
    bool_t needAck = FALSE;

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
            packet->packet.data[0] = 2;
            sendMsg = TRUE;
            break;

        case RF_TIMESYNC:
            syncedTime = *((uint32_t*) packet->packet.data);
            sendAck = TRUE;
            break;
    }

    // TODO: RF data response statemachine
    if (sendMsg)
        Mrf49xaTxPacket(packet, TRUE, needAck);
    else if (sendAck)
        Mrf49xaTxAck(packet);
    else
        Mrf49xaFreePacket(packet);
}