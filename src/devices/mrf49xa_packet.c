#include "devices/mrf49xa.h"

bool_t Mrf49xaPacketPending(void)
{
    if (rfTrcvStatus.rxPacket[0].state == PKT_HW_READY_RX ||
        rfTrcvStatus.rxPacket[1].state == PKT_HW_READY_RX)
        return TRUE;
    else
        return FALSE;
}

bool_t Mrf49xaTxPacket(rfTrcvPacket_t* packet, bool_t swapSrcDst)
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
        if (swapSrcDst)
        {
            packet->packet.dst = packet->packet.src;
            packet->packet.src = rfTrcvStatus.src;
        }

        packetTx.state = PKT_READY_FOR_TX;
        packetTx.crc = 0;
        packetTx.retry = 0;

        packet->state = PKT_FREE;

        // Copy complete packet.
        for (i = 0; i < packet->packet.size+1; i++)
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
    uint8_t i, j;
    if (Mrf49xaPacketPending())
    {
        rfTrcvPacket_t* packet = Mrf49xaRxPacket();

        // Ping-pong
        if (packet->packet.id == 0xA0)
        {
            packet->packet.data[0] = 2;
        }


        // TODO: RF data response statemachine
        Mrf49xaTxPacket(packet, TRUE);
    }

    if (rfTrcvStatus.txPacket.state == PKT_READY_FOR_TX &&
        rfTrcvStatus.state == RECV_IDLE)
    {
        uint8_t timeout = 0;
        
        // Do a collision avoidence check.
        // TODO: This may need improvement & alot of testing.
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
        //rfTrcvStatus.state = TX_PACKET;
        MRF_DISABLE_INT;
        Mrf49xaModeTx();
        Mrf49TxByte(0xAA);
        Mrf49TxByte(0xAA);
        MRF_ENABLE_INT;
    }
}