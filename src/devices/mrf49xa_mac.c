#include "devices/mrf49xa.h"
#include "config.h"
#include "stddefs.h"

#include "bsp/interrupt.h"
#include "rfstack/packets.h"

bool Mrf49xaPacketPending(Mrf49xaMac_t* inst)
{
    if (inst->rxPacket[0].state == PKT_HW_READY_RX ||
        inst->rxPacket[1].state == PKT_HW_READY_RX)
        return true;
    else
        return false;
}

bool Mrf49xaTxPacket(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet, bool response, bool needAck)
{
    uint8_t i, crc = 0;

    if (&(inst->txPacket) == packet)
    {
        if (response)
        {
            inst->txPacket.packet.dst = inst->txPacket.packet.src;
        }
        inst->txPacket.packet.src = inst->nodeId;
        inst->txPacket.packet.size += 5;

        inst->txPacket.state = PKT_READY_FOR_TX;
        inst->txPacket.retry = 0;
        inst->txPacket.retransmit = 0;
        inst->txPacket.needAck = (needAck == true) ? NEED_ACK : NO_ACK;
        inst->txPacket.crc = 0;
        return true;
    }

    // Packet in buffer is ready for transmission.
    if (inst->txPacket.state != PKT_FREE)
    {
        // TODO: Error buffer is full
        return false;
    }
    else
    {
        if (response)
        {
            packet->packet.dst = packet->packet.src;
        }
        packet->packet.src = inst->nodeId;
        packet->packet.size += 5;

        packet->state = PKT_FREE;

        // Copy complete packet.
        for (i = 0; i < RF_PACKET_LENGTH; i++)
        {
            inst->txPacket.raw[i] = packet->raw[i];
        }
        for (i = 0; i < packet->packet.size; i++)
        {
            crc = crc ^ inst->txPacket.raw[i];
        }

        inst->txPacket.state = PKT_READY_FOR_TX;
        inst->txPacket.retry = 0;
        inst->txPacket.retransmit = 0;
        inst->txPacket.needAck = (needAck == true) ? NEED_ACK : NO_ACK;

        inst->txPacket.crc = crc;
        return true;
    }
}

bool Mrf49xaTxAck(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet)
{
    packet->packet.data[0] = packet->packet.id;
    packet->packet.data[1] = packet->crc;

    // Send acknowledgement
    packet->packet.id = RF_ACK;
    packet->packet.size = 2;

    return Mrf49xaTxPacket(inst, packet, true, false);
}

void Mrf49xaFreePacket(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet)
{
    packet->state = PKT_FREE;
}

rfTrcvPacket_t* Mrf49xaRxPacket(Mrf49xaMac_t* inst)
{
    if (inst->rxPacket[0].state == PKT_HW_READY_RX)
    {
        inst->rxPacket[0].state = PKT_SW_BUSY;
        return &(inst->rxPacket[0]);
    }

    if (inst->rxPacket[1].state == PKT_HW_READY_RX)
    {
        inst->rxPacket[1].state = PKT_SW_BUSY;
        return &(inst->rxPacket[1]);
    }

    return NULL;
}

rfTrcvPacket_t* Mrf49xaAllocPacket(Mrf49xaMac_t* inst)
{
    if (inst->rxPacket[0].state == PKT_FREE)
    {
        inst->rxPacket[0].state = PKT_SW_BUSY;
        return &(inst->rxPacket[0]);
    }

    if (inst->rxPacket[1].state == PKT_FREE)
    {
        inst->rxPacket[1].state = PKT_SW_BUSY;
        return &(inst->rxPacket[1]);
    }

    return NULL;
}

#ifdef PIC24GB
RtosTime_t TransmissionStart;
#endif

void Mrf49xaTick(Mrf49xaMac_t* inst)
{
#ifdef PIC24GB
    if ((RtosTimestamp - TransmissionStart) > 250 &&
            inst->state == TX_PACKET)
    {
        Mrf49xaNeedsReset();
    }
#endif
    if (inst->rxPacket[0].state == PKT_HW_BUSY_RX &&
        inst->rxPacket[1].state == PKT_HW_BUSY_RX)
    {
        Mrf49xaNeedsReset();
    }
    if (inst->needsReset)
    {
        Mrf49xaInit();
        ExtIntInit();
        return;
    }


    if (Mrf49xaPacketPending(inst))
    {
        rfTrcvPacket_t* packet = Mrf49xaRxPacket(inst);

#ifdef RF_DEBUG
        rfHistoryPut(packet);
#endif

        // Is this packet for this node?
#ifndef RF_NO_ID_FILTER
        if (packet->packet.dst == RF_BROADCAST || packet->packet.dst == inst->nodeId)
        {
            packet->packet.size -= 5;

#endif
            HandlePacket(inst, packet);
#ifndef RF_NO_ID_FILTER
        }
        else
        {
            Mrf49xaFreePacket(inst, packet);
        }
#else
        Mrf49xaFreePacket(packet);
#endif
    }

    if (inst->txPacket.state == PKT_WAITING_FOR_ACK)
    {
        if (inst->txPacket.needAck == ACK_RECEIVED)
        {
            inst->txPacket.state = PKT_FREE;
        }
        else if (inst->txPacket.retry == 10)
        {
            if (inst->txPacket.retransmit == 1)
            {
                // TODO: Add statistics.
                // Packet failed to deliver..
                inst->txPacket.state = PKT_FREE;
            }
            else
            {
                // mark for new tx
                inst->txPacket.retry = 0;
                inst->txPacket.retransmit++;
                inst->txPacket.state = PKT_READY_FOR_TX;
            }
        }
        else
        {
            inst->txPacket.retry++;
            Delay5Ms();
        }
    }

    if (inst->txPacket.state == PKT_READY_FOR_TX &&
        inst->state == RECV_IDLE)
    {
        if (inst->txPacket.retry >= 10)
        {
            // Attempt to retransmit..
            inst->txPacket.retry = 0;
            inst->txPacket.state = PKT_WAITING_FOR_ACK;
            return;
        }
        
        // Do a collision avoidence check.
        // TODO: This may need improvement & alot of testing.
        uint8_t timeout = 0;

        // Remain in here while a signal is present.
        do
        {
            Mrf49RxSts();

            if (inst->state == RECV_IDLE && mrf49Status.flags.msb.signalPresent == 0)
            {
                // Succes!
                break;
            }

            Delay5Ms();
            timeout++;

            if (timeout > 10)
            {
                inst->txPacket.retry++;
                return;
            }
            
        }
        while (1);

#ifdef RF_DEBUG
        rfHistoryPut(&packetTx);
#endif

        //printf("\nTx %X\n", rfTrcvStatus.txPacket.packet.id);

        // We've obtained air mission control.
        MRF_DISABLE_INT;
        Mrf49xaModeTx();
        inst->txPacket.state = PKT_HW_BUSY_TX;
#ifdef PIC24GB
        TransmissionStart = RtosTimestamp;
#endif
        MRF_ENABLE_INT;
    }
}
