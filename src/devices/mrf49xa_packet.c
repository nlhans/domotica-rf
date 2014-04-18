#include "devices/mrf49xa.h"

#include "rfstack/packets.h"

bool_t Mrf49xaPacketPending(void)
{
    if (rfTrcvStatus.rxPacket[0].state == PKT_HW_READY_RX ||
        rfTrcvStatus.rxPacket[1].state == PKT_HW_READY_RX)
        return TRUE;
    else
        return FALSE;
}

void Mrf49xaTxAck(rfTrcvPacket_t* packet)
{

    packet->packet.data[0] = packet->packet.id;
    packet->packet.data[1] = packet->crc;

    // Send acknowledgement
    packet->packet.id = RF_ACK;
    packet->packet.size = 2;

    Mrf49xaTxPacket(packet, TRUE, FALSE);
}

bool_t Mrf49xaTxPacket(rfTrcvPacket_t* packet, bool_t response, bool_t needAck)
{
    uint8_t i;

    // Packet in buffer is ready for transmission.
    if (rfTrcvStatus.txPacket.state != PKT_FREE)
    {
        // TODO: Error buffer is full
        return FALSE;
    }
    else
    {
        if (response)
        {
            packet->packet.dst = packet->packet.src;
            packet->packet.src = rfTrcvStatus.src;
        }

        packetTx.state = PKT_READY_FOR_TX;
        packetTx.crc = 0;
        packetTx.retry = 0;
        packetTx.retransmit = 0;
        packetTx.needAck = (needAck == TRUE) ? NEED_ACK : NO_ACK;

        packet->state = PKT_FREE;

        // Copy complete packet.
        for (i = 0; i <= packet->packet.size; i++)
             packetTx.raw[i] = packet->raw[i];

        return TRUE;
    }
}

void Mrf49xaFreePacket(rfTrcvPacket_t* packet)
{
    packet->state = PKT_FREE;
}

rfTrcvPacket_t* Mrf49xaRxPacket(void)
{
    if (rfTrcvStatus.rxPacket[0].state == PKT_HW_READY_RX)
    {
        rfTrcvStatus.rxPacket[0].state = PKT_SW_BUSY;
        return &(rfTrcvStatus.rxPacket[0]);
    }

    if (rfTrcvStatus.rxPacket[1].state == PKT_HW_READY_RX)
    {
        rfTrcvStatus.rxPacket[1].state = PKT_SW_BUSY;
        return &(rfTrcvStatus.rxPacket[1]);
    }

    return NULL;
}

void Mrf49xaTick(void)
{
    if (Mrf49xaPacketPending())
    {
        rfTrcvPacket_t* packet = Mrf49xaRxPacket();

        // Is this packet for this node?
        if (packet->packet.dst == RF_BROADCAST || packet->packet.dst == rfTrcvStatus.src)
        {
            HandlePacket(packet);
        }
        else
        {
            Mrf49xaFreePacket(packet);
        }
    }

    if (packetTx.state == PKT_WAITING_FOR_ACK)
    {
        if (packetTx.needAck == ACK_RECEIVED)
        {
            packetTx.state = PKT_FREE;
        }
        else if (packetTx.retry == 10)
        {
            if (packetTx.retransmit == 3)
            {
                // TODO: Add statistics.
                // Packet failed to deliver..
                packetTx.state = PKT_FREE;
            }
            else
            {
                // mark for new tx
                packetTx.retry = 0;
                packetTx.retransmit++;
                packetTx.state = PKT_READY_FOR_TX;
            }
        }
        else
        {
            packetTx.retry++;
            Delay5Ms();
        }
    }

    if (packetTx.state == PKT_READY_FOR_TX &&
        rfTrcvStatus.state == RECV_IDLE)
    {
        if (packetTx.retry >= 10)
        {
            // Attempt to retransmit..
            packetTx.retry = 0;
            packetTx.state = PKT_WAITING_FOR_ACK;
            return;
        }
        
        // Do a collision avoidence check.
        // TODO: This may need improvement & alot of testing.
        uint8_t timeout = 0;
        do
        {
            Mrf49RxSts();

            if (rfTrcvStatus.state == RECV_IDLE && mrf49Status.flags.msb.signalPresent == 0)
            {
                // Succes!
                break;
            }

            Delay5Ms();
            timeout++;

            if (timeout > 10)
            {
                packetTx.retry++;
                return;
            }
            
        }
        // Remain in here while a signal is present.
        while (1);

        // We've obtained air mission control.
        MRF_DISABLE_INT;
        Mrf49xaModeTx();
        MRF_ENABLE_INT;
    }
}