#include "devices/mrf49xa.h"
#include "config.h"
#include "stddefs.h"

#include "bsp/interrupt.h"
#include "rfstack/packets.h"

bool Mrf49xaPacketPending(Mrf49xaMac_t* inst)
{
    if (mrf49Inst->rxPacket[0].state == PKT_HW_READY_RX ||
        mrf49Inst->rxPacket[1].state == PKT_HW_READY_RX)
        return true;
    else
        return false;
}

bool Mrf49xaTxPacket(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet, bool response, bool needAck)
{
    uint8_t i, crc = 0;

    if (&(mrf49Inst->txPacket) == packet)
    {
        if (response)
        {
            mrf49Inst->txPacket.packet.dst = mrf49Inst->txPacket.packet.src;
        }
        mrf49Inst->txPacket.packet.src = mrf49Inst->nodeId;
        mrf49Inst->txPacket.packet.size += 5;

        mrf49Inst->txPacket.state = PKT_READY_FOR_TX;
        mrf49Inst->txPacket.retry = 0;
        mrf49Inst->txPacket.retransmit = 0;
        mrf49Inst->txPacket.needAck = (needAck == true) ? NEED_ACK : NO_ACK;
        mrf49Inst->txPacket.crc = 0;
        return true;
    }

    // Packet in buffer is ready for transmission.
    if (mrf49Inst->txPacket.state != PKT_FREE)
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
        packet->packet.src = mrf49Inst->nodeId;
        packet->packet.size += 5;

        packet->state = PKT_FREE;

        // Copy complete packet.
        for (i = 0; i < RF_PACKET_LENGTH; i++)
        {
            mrf49Inst->txPacket.raw[i] = packet->raw[i];
        }
        for (i = 0; i < packet->packet.size; i++)
        {
            crc = crc ^ mrf49Inst->txPacket.raw[i];
        }

        mrf49Inst->txPacket.state = PKT_READY_FOR_TX;
        mrf49Inst->txPacket.retry = 0;
        mrf49Inst->txPacket.retransmit = 0;
        mrf49Inst->txPacket.needAck = (needAck == true) ? NEED_ACK : NO_ACK;

        mrf49Inst->txPacket.crc = crc;
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

    return Mrf49xaTxPacket(mrf49Inst, packet, true, false);
}

void Mrf49xaFreePacket(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet)
{
    packet->state = PKT_FREE;
}

rfTrcvPacket_t* Mrf49xaRxPacket(Mrf49xaMac_t* inst)
{
    if (mrf49Inst->rxPacket[0].state == PKT_HW_READY_RX)
    {
        mrf49Inst->rxPacket[0].state = PKT_SW_BUSY;
        return &(mrf49Inst->rxPacket[0]);
    }

    if (mrf49Inst->rxPacket[1].state == PKT_HW_READY_RX)
    {
        mrf49Inst->rxPacket[1].state = PKT_SW_BUSY;
        return &(mrf49Inst->rxPacket[1]);
    }

    return NULL;
}

rfTrcvPacket_t* Mrf49xaAllocPacket(Mrf49xaMac_t* inst)
{
    if (mrf49Inst->rxPacket[0].state == PKT_FREE)
    {
        mrf49Inst->rxPacket[0].state = PKT_SW_BUSY;
        return &(mrf49Inst->rxPacket[0]);
    }

    if (mrf49Inst->rxPacket[1].state == PKT_FREE)
    {
        mrf49Inst->rxPacket[1].state = PKT_SW_BUSY;
        return &(mrf49Inst->rxPacket[1]);
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
            mrf49Inst->state == TX_PACKET)
    {
        Mrf49xaNeedsReset();
    }
#endif
    if (mrf49Inst->rxPacket[0].state == PKT_HW_BUSY_RX &&
        mrf49Inst->rxPacket[1].state == PKT_HW_BUSY_RX)
    {
        Mrf49xaNeedsReset(mrf49Inst);
    }
    if (mrf49Inst->needsReset)
    {
        Mrf49xaInit(mrf49Inst);
        ExtIntInit();
        return;
    }


    if (Mrf49xaPacketPending(mrf49Inst))
    {
        rfTrcvPacket_t* packet = Mrf49xaRxPacket(mrf49Inst);

#ifdef RF_DEBUG
        rfHistoryPut(packet);
#endif

        // Is this packet for this node?
#ifndef RF_NO_ID_FILTER
        if (packet->packet.dst == RF_BROADCAST || packet->packet.dst == mrf49Inst->nodeId)
        {
            packet->packet.size -= 5;

#endif
            HandlePacket(mrf49Inst, packet);
#ifndef RF_NO_ID_FILTER
        }
        else
        {
            Mrf49xaFreePacket(mrf49Inst, packet);
        }
#else
        Mrf49xaFreePacket(packet);
#endif
    }

    if (mrf49Inst->txPacket.state == PKT_WAITING_FOR_ACK)
    {
        if (mrf49Inst->txPacket.needAck == ACK_RECEIVED)
        {
            mrf49Inst->txPacket.state = PKT_FREE;
        }
        else if (mrf49Inst->txPacket.retry == 10)
        {
            if (mrf49Inst->txPacket.retransmit == 1)
            {
                // TODO: Add statistics.
                // Packet failed to deliver..
                mrf49Inst->txPacket.state = PKT_FREE;
            }
            else
            {
                // mark for new tx
                mrf49Inst->txPacket.retry = 0;
                mrf49Inst->txPacket.retransmit++;
                mrf49Inst->txPacket.state = PKT_READY_FOR_TX;
            }
        }
        else
        {
            mrf49Inst->txPacket.retry++;
            Delay5Ms();
        }
    }

    if (mrf49Inst->txPacket.state == PKT_READY_FOR_TX &&
        mrf49Inst->state == RECV_IDLE)
    {
        if (mrf49Inst->txPacket.retry >= 10)
        {
            // Attempt to retransmit..
            mrf49Inst->txPacket.retry = 0;
            mrf49Inst->txPacket.state = PKT_WAITING_FOR_ACK;
            return;
        }
        
        // Do a collision avoidence check.
        // TODO: This may need improvement & alot of testing.
        uint8_t timeout = 0;

        // Remain in here while a signal is present.
        do
        {
            Mrf49RxSts(mrf49Inst);

            if (mrf49Inst->state == RECV_IDLE && mrf49Inst->status.flags.msb.signalPresent == 0)
            {
                // Succes!
                break;
            }

            Delay5Ms();
            timeout++;

            if (timeout > 10)
            {
                mrf49Inst->txPacket.retry++;
                return;
            }
            
        }
        while (1);

#ifdef RF_DEBUG
        rfHistoryPut(&packetTx);
#endif

        //printf("\nTx %X\n", mrf49Inst->txPacket.packet.id);

        // We've obtained air mission control.
        MRF_DISABLE_INT;
        Mrf49xaModeTx(mrf49Inst);
        mrf49Inst->txPacket.state = PKT_HW_BUSY_TX;
#ifdef PIC24GB
        TransmissionStart = RtosTimestamp;
#endif
        MRF_ENABLE_INT;
    }
}
