#include "rfstack/hal.h"
#include "rfstack/packets.h"
#include "rfstack/rfdefs.h"

#define RF_PING_REQUEST  1
#define RF_PING_RESPONSE 2

struct pt halPkTh;

void RfPacketsHandleServer(RfTransceiverPacket_t* packet);
void RfPacketsHandleClient(RfTransceiverPacket_t* packet);

typedef enum EepromMemoryMap_e
{
    EE_NODE_ID = 0x7FFF
} EepromMemoryMap_t;
#define eepromRead(a) 0 // TODO: Implement EEPROM.

RfNodeInfo_t rfNode;

#ifdef PIC24_HW
RfNodeInfo_t nodes[RF_NR_OF_NODES];
#else
RfNodeInfo_t rfServer;
#endif

void RfPacketSimpleReply(RfTransceiverPacket_t* packet, RfMsg_t msg, UI08_t needAck)
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
    RfHalTxPut(packet, needAck);
}

void RfPacketTransmit(UI08_t dst, RfMsg_t msg, UI08_t* data, UI08_t length, UI08_t opt, UI08_t needAck)
{
    UI08_t i;
    
    RfTransceiverPacket_t* packet = RfHalGetFree();
    if (packet == NULL) return;

    for (i = 0; i < length; i++)
        packet->data[4+i] = data[i];
    //memcpy(&(packet.data[4]), data, length);

    packet->frame.dst = dst;
    packet->frame.src = 0x5A;
    packet->frame.id = msg;
    packet->frame.opt = opt;

    packet->size = length+4;
#ifdef PIC24_HW
    printf("[RF] TX Node %d -> %d | Msg ID %02X Opt %02X | Data:", packet.frame.src, packet.frame.dst, packet.frame.id, packet.frame.opt);
    for (i = 0; i < packet.size - 4; i++)
        printf("%02X ", packet.data[4+i]);

    printf("\n");
#endif
    
    RfHalTxPut(packet, needAck);
}
void RfPacketReply(RfTransceiverPacket_t* packet, RfMsg_t msg, UI08_t size, UI08_t needAck)
{
    // Swap src&dst
    UI08_t nodeTmp = packet->frame.src;
    packet->frame.src = packet->frame.dst;
    packet->frame.dst = nodeTmp;
    packet->frame.id = msg;
    
    packet->size = size + 4;

#ifdef PIC24_HW
    UI08_t i;
    
    printf("[RF] TX Node %d -> %d | Msg ID %02X Opt %02X | Data:", packet->frame.src, packet->frame.dst, packet->frame.id, packet->frame.opt);
    for (i = 0; i < packet->size - 4; i++)
        printf("%02X ", packet->data[4+i]);

    printf("\n");
#endif
    
    RfHalTxPut(packet, needAck);

}

void RfPacketsHandleServer(RfTransceiverPacket_t* packet)
{
    // Handle frame
    switch(packet->frame.id)
    {
        case RF_POR:
#ifdef PIC24_HW
            printf("[RF] Power-on-Reset message from node %d\n[RF]Adding node to table\n", packet->frame.src);
#endif
            packet->frame.data[0] = 0x55;
            packet->frame.data[1] = 0xAA;

            RfPacketReply(packet, RF_ACK, 2, TRUE);
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
            RfPacketSimpleReply(packet, RF_PING, FALSE);
            break;

        default:

            break;
    }
}

void RfPacketsHandleClient(RfTransceiverPacket_t* packet)
{
    switch(packet->frame.id)
    {
        case RF_PING:
            packet->frame.data[0] = RF_PING_RESPONSE;
            RfPacketSimpleReply(packet, RF_PING, FALSE);
            break;

        case RF_ACK:
            // Ack on previous rx message?
            if (packet->frame.data[0] == rfStatus.isr.txPacket->crcTx)
            {
                // Yes! Free-up in the buffer.
                packet->flags.wait_for_ack = 0;
                packet->flags.proc = PCKT_NO_PROC;
            }
            else
            {
                // Well, maybe we haven't sent this packet..
            }
            break;
    }
}

PT_THREAD(RfPacketsTickTh)
{
    static UI08_t timeout;
    static RfTransceiverPacket_t* packet;

    timeout++;

    PT_BEGIN(pt);

    while(1)
    {
        // Grab the packet
        PT_WAIT_UNTIL(pt, (packet = RfHalRxGet()) != FALSE || timeout > 25);

        if (packet)
        {
            // Print packet
            /*printf("[RF] RX Node %d -> %d | Msg ID %02X Opt %02X | Data:", packet->frame.src, packet->frame.dst, packet->frame.id, packet->frame.opt);

            for (i = 0; i < packet->size - 4; i++)
                printf("%02X ", packet->data[4+i]);

            printf("\n");*/
#ifdef PIC24_HW
            RfPacketsHandleServer(packet);
#else
            RfPacketsHandleClient(packet);
#endif
        }

        if (timeout > 25)
        {
            // Timeout on RX packet.
            if (packet->flags.proc == PCKT_NEED_PROC)
            {
                RfHalTxPutAgain();
            }
        }

        timeout = 0;
    }

    PT_END(pt);
}

void RfPacketsInit()
{
    //
    rfNode.node.ee = eepromRead(EE_NODE_ID);
    
}