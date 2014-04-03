#include "rfstack/hal.h"
#include "rfstack/packets.h"
#include "rfstack/rfdefs.h"

PT_THREAD(RfHalTickPkTh);
struct pt halPkTh;

typedef enum EepromMemoryMap_e
{
    EE_NODE_ID = 0x7FFF
} EepromMemoryMap_t;
#define eepromRead(a) 0 // TODO: Implement EEPROM.

RfNodeInfo_t rfNode;
RfNodeInfo_t nodes[RF_NR_OF_NODES];

void RfPacketSimpleReply(RfTransceiverPacket_t* packet, RfMsg_t msg)
{
    // Swap src&dst
    UI08_t nodeTmp = packet->frame.src;
    packet->frame.src = packet->frame.dst;
    packet->frame.dst = nodeTmp;

    packet->frame.id = msg;
    
    /*printf("[RF] TX Node %d -> %d | Msg ID %02X Opt %02X | Data:", packet->frame.src, packet->frame.dst, packet->frame.id, packet->frame.opt);
    for (i = 0; i < packet->size - 4; i++)
        printf("%02X ", packet->data[4+i]);

    printf("\n");*/
    RfHalTxPut(packet);
}

void RfPacketTransmit(UI08_t dst, RfMsg_t msg, UI08_t* data, UI08_t length, UI08_t opt)
{
    UI08_t i;
    
    RfTransceiverPacket_t packet;

    memcpy(&(packet.data[4]), data, length);

    packet.frame.dst = dst;
    packet.frame.src = 0x5A;
    packet.frame.id = msg;
    packet.frame.opt = opt;

    packet.size = length+4;
#ifdef PIC24_HW
    printf("[RF] TX Node %d -> %d | Msg ID %02X Opt %02X | Data:", packet.frame.src, packet.frame.dst, packet.frame.id, packet.frame.opt);
    for (i = 0; i < packet.size - 4; i++)
        printf("%02X ", packet.data[4+i]);

    printf("\n");
#endif
    
    RfHalTxPut(&packet);
}
void RfPacketReply(RfTransceiverPacket_t* packet, RfMsg_t msg, UI08_t* data, UI08_t length, UI08_t opt)
{
    UI08_t i;
    
    // Swap src&dst
    UI08_t nodeTmp = packet->frame.src;
    packet->frame.src = packet->frame.dst;
    packet->frame.dst = nodeTmp;

    packet->frame.id = msg;
    packet->frame.opt = opt;
    memcpy(packet->data+4, data, length);

    packet->size = length + 4;

#ifdef PIC24_HW
    printf("[RF] TX Node %d -> %d | Msg ID %02X Opt %02X | Data:", packet->frame.src, packet->frame.dst, packet->frame.id, packet->frame.opt);
    for (i = 0; i < packet->size - 4; i++)
        printf("%02X ", packet->data[4+i]);

    printf("\n");
#endif
    
    RfHalTxPut(packet);

}
PT_THREAD(RfPacketsTickTh)
{
    static RfTransceiverPacket_t* packet;
    PT_BEGIN(pt);

    UI08_t scratchpad[4];

    while(1)
    {
        // Grab the packet
        PT_WAIT_UNTIL(pt, (packet = RfHalRxGet()) != FALSE);

        // Print crc check
        if (packet->crcRx != packet->crcTx)
        {
#ifdef PIC24_HW
            printf("[RF] CRC error | RX %02X | CALC %02X\n", packet->crcRx, packet->crcTx);
#endif
        }

        // Print packet
        /*printf("[RF] RX Node %d -> %d | Msg ID %02X Opt %02X | Data:", packet->frame.src, packet->frame.dst, packet->frame.id, packet->frame.opt);

        for (i = 0; i < packet->size - 4; i++)
            printf("%02X ", packet->data[4+i]);

        printf("\n");*/

        // Handle frame
        switch(packet->frame.id)
        {
            case RF_POR:
#ifdef PIC24_HW
                printf("[RF] Power-on-Reset message from node %d\n[RF]Adding node to table\n", packet->frame.src);
#endif
                scratchpad[0] = 0x55;
                scratchpad[1] = 0xAA;
                RfPacketReply(packet, RF_ACK, scratchpad, 2, 0);
                break;

#ifdef PIC24_HW
            case RF_SHDN:
                printf("[RF] RF node %d is going down\n", packet->frame.src);
                break;

            case RF_ACK:
                printf("[RF] Got ACK from node %d\n", packet->frame.src);
                break;
#endif

            case RF_PING:
                //printf("[RF] Ping from %d\n", packet->frame.src);
                
                packet->data[4] = 2;
                RfPacketSimpleReply(packet, RF_PING);
                break;

            default:
                RfPacketReply(packet, RF_ACK, scratchpad, 2, 0);
                break;
        }
    }

    PT_END(pt);
}

void RfPacketsInit()
{
    //
    rfNode.node.ee = eepromRead(EE_NODE_ID);
    
}