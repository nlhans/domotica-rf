#include "rfstack/packets.h"
#include "devices/mrf49xa.h"
#include "devices/24aa64.h"

#include "config.h"

#ifdef PROTOCOL_SUPPORT_FIRMWARE
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
#ifdef PROTOCOL_SUPPORT_FIRMWARE_BOOTLOADER
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
#endif

    }
}

#ifdef PROTOCOL_SUPPORT_FIRMWARE_BOOTLOADER
void handleFwWrite(rfTrcvPacket_t* packet)
{
    UI16_t address = (packet->packet.data[2] << 8) | packet->packet.data[3];
    UI16_t* packetData = (UI16_t*) &(packet->packet.data[8]);
    address=0;
    // TODO: Handle encryption
    eepromTxBytes(address, packet->packet.data+8, 8);

    // Wait 5ms for EEPROM write cycle
    __delay_ms(5);

    eepromRxBytes(address, packet->packet.data+8, 8);

    // use address for checksum calculation
    address = 0xCAFE;

    for (uint8_t i = 0; i < 4; i++)
    {
        address = address ^ (packetData[i] ^ 0x5AA5);
    }

    packet->packet.data[8] = address >> 8;
    packet->packet.data[9] = address & 0xFF;

    packet->packet.size = 10;

}

void handleFwRead(rfTrcvPacket_t* packet)
{
    packet->packet.size = 16;
    UI16_t address = (packet->packet.data[2] << 8) | packet->packet.data[3];
    address=0;

    // This call costs about 3.2ms.
    // Each byte costs about 200us to receive, but the function transmits
    // device adress 2x, start 2x, eeprom address 2 bytes, and ack bits 1 byte
    // This results in a high overhead. 
    eepromRxBytes(address, packet->packet.data+8, 8);

}
#endif
#endif

#ifdef PROTCOL_SUPPORT_CONFIG
void handleCfgRead(rfTrcvPacket_t* packet)
{
    uint8_t index = packet->packet.data[0];
    uint8_t nrOfBytes = CfgGetSizeByType(parameters[index].type);

    packet->packet.size = nrOfBytes + 2;
    packet->packet.id = RF_CFG_READ;

    packet->packet.data[1] = parameters[index].id;

    memcpy(packet->packet.data + 2, parameters[index].ptr, nrOfBytes);
}

void handleCfgWrite(rfTrcvPacket_t* packet)
{
    uint8_t index = packet->packet.data[0];
    uint8_t nrOfBytes = CfgGetSizeByType(parameters[index].type);

    memcpy(parameters[index].ptr, packet->packet.data + 1, nrOfBytes);

}

void handleCfgCmd(rfTrcvPacket_t* packet)
{
    switch (packet->packet.data[0])
    {
        case 1:
            CfgSave();
            break;

        case 2:
            CfgLoad();
            break;

        case 3:
            packet->packet.size = 2;
            packet->packet.data[1] = CfgParameterCount;
            break;

        case 4:
            packet->packet.size = 3;
            packet->packet.data[1] = cfgRam.checksum >> 8;
            packet->packet.data[2] = cfgRam.checksum & 0xFF;
            break;
    }
}
#endif

void HandlePacketClient(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet)
{
    // Compact these booleans:
    struct
    {
        bool reset:1;
        bool needAck:1;
        bool sendAck:1;
        bool sendMsg:1;
    } response;
    
    // Ping-pong
    switch (packet->packet.id)
    {
        case RF_PING:
            packet->packet.data[0] = 2;
            response.sendMsg = true;
            break;

        case RF_ACK:
            if (mrf49Inst->txPacket.crc == packet->packet.data[1] &&
                mrf49Inst->txPacket.packet.id == packet->packet.data[0])
            {
                mrf49Inst->txPacket.needAck = ACK_RECEIVED;
            }
            break;

        case RF_TIME_SYNC:
            syncedTime = *((uint32_t*) packet->packet.data);
            response.sendAck = false;
            break;

        case RF_POWER_STATUS:
            // Ignore, we're a client!
            break;

#ifdef PROTCOL_SUPPORT_CONFIG

            // Command
        case RF_CFG_CMD:
            handleCfgCmd(packet);
            response.sendMsg = TRUE;
            break;

            // Write reports a read action back.
        case RF_CFG_WRITE:
            handleCfgWrite(packet);
        case RF_CFG_READ:
            handleCfgRead(packet);
            response.sendMsg = TRUE;
           break;
#endif
           
#ifdef PROTOCOL_SUPPORT_FIRMWARE
        case RF_FW_CMD:
            handleFwCmd(packet);
            response.sendMsg = true;
            break;

#ifdef PROTOCOL_SUPPORT_FIRMWARE_BOOTLOADER
        case RF_FW_WRITE:
            handleFwWrite(packet);
            sendMsg = TRUE;
            break;

        case RF_FW_READ:
            handleFwRead(packet);
            sendMsg = TRUE;
            break;
            
#endif
#endif

#ifdef PROTOCOL_SUPPORT_EEPROM
      // TODO: Support these commands
#endif
    }

    response.reset = true;

    // TODO: RF data response statemachine
    if (response.sendMsg)
        response.reset = Mrf49xaTxPacket(mrf49Inst, packet, true, response.needAck);
    else if (response.sendAck)
        response.reset = Mrf49xaTxAck(mrf49Inst, packet);
    else
        response.reset = false;

    if (!response.reset)
        Mrf49xaFreePacket(mrf49Inst, packet);
}
