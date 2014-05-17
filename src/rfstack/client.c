#include "rfstack/packets.h"

#include "devices/24aa64.h"

void RfSendPowerState(void)
{
    rfTrcvPacket_t* packet = Mrf49xaAllocPacket();

    packet->packet.size = 2;
    packet->packet.id = RF_POWER_STATUS;
    packet->packet.dst = 0xFF;
    
    packet->packet.data[0] = 0x55;
    packet->packet.data[1] = 0xAA;

    Mrf49xaTxPacket(packet, FALSE, TRUE);
}

void handleFwCmd(rfTrcvPacket_t* packet)
{
    switch(packet->packet.data[0])
    {
        // NOP
        case 0:
            break;

        case 1:
            packet->packet.size = 5;
            packet->packet.data[1] = FW_RUNTIME_MAJOR;
            packet->packet.data[2] = FW_RUNTIME_MINOR;

            eepromRxBytes(FW_APPLICATION_VERSION, &(packet->packet.data[3]), 2);

            break;

        case 2:
            packet->packet.size = 2;
            eepromRxBytes(FW_APPLICATION_STATE, &(packet->packet.data[1]), 1);
            //packet->packet.data[1] = eepromRxByte(FW_APPLICATION_STATE);

            break;

        case 3:
            // TODO: Handle EEPROM preparation
            break;

        case 4:
            // TODO: Handle FLASH runtime command
            break;

        case 5:
            // TODO: Handle FLASH application command
            break;

        case 6:
            // TODO: Handle Boot application command
            break;

        case 7:
            // TODO: Handle Application run status
            break;

    }
}

void handleFwWrite(rfTrcvPacket_t* packet)
{
    UI16_t address = (packet->packet.data[2] << 8) | packet->packet.data[3];
    UI16_t* packetData = (UI16_t*) &(packet->packet.data[8]);

    // TODO: Handle encryption
    eepromTxBytes(address, packet->packet.data+8, 8);

    eepromRxBytes(address, packet->packet.data+8, 8);

    // use address for checksum calculation
    address = 0xCAFE;

    for (uint8_t i = 0; i < 4; i++)
    {
        address = address ^ packetData[i];
    }

    packet->packet.data[8] = address >> 8;
    packet->packet.data[9] = address & 0xFF;

    packet->packet.size = 10;

}

void handleFwRead(rfTrcvPacket_t* packet)
{
    packet->packet.size = 16;
    UI16_t address = (packet->packet.data[2] << 8) | packet->packet.data[3];
    
    eepromRxBytes(address, packet->packet.data+8, 8);

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

        case RF_TIME_SYNC:
            syncedTime = *((uint32_t*) packet->packet.data);
            sendAck = TRUE;
            break;

        case RF_POWER_STATUS:
            // Ignore, we're a client!
            break;

        case RF_FW_CMD:
            handleFwCmd(packet);
            sendMsg = TRUE;
            break;

        case RF_FW_WRITE:
            handleFwWrite(packet);
            sendMsg = TRUE;
            break;

        case RF_FW_READ:
            handleFwRead(packet);
            sendMsg = TRUE;
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