#include "stddefs.h"
#include "rfstack/hal.h"
#include "rfstack/packets.h"
#ifdef SERVER
#include "tasks/rf_task.h"
#endif

#ifdef SERVER
#include "utilities/ccbuf.h"
#else
#include "utilities/ccbuf_static.h"
#endif

PT_THREAD(RfHalTickRxTh);
PT_THREAD(RfHalTickTxTh);

struct pt halRxBfTh;
struct pt halTxBfTh;

bool_t RfHalTxGet();
bool_t RfHalRxPut(RfTransceiverPacket_t* rfPacket);

RfTransceiverPacket_t rfPackets[RF_PACKET_BUFFER_DEPTH];
RfTransceiverStatus_t rfStatus;

UI08_t rfRxBf[48]; // Rx buffer

CircBufDef_t rfRxCC = { 
    rfRxBf, sizeof(rfRxBf)
};

volatile UI08_t rfPkCrc=0;
volatile UI08_t rfPkTime=0;
volatile UI08_t rfPk=0;

#ifndef SERVER
CircBufDef_t* const CCDef = &rfRxCC;
#endif

void RfHalInit(void)
{
    //
    rfStatus.isr.byteCounter = 0;
    rfStatus.isr.txPacket = rfPackets;
    rfStatus.isr.state = RX_RECV;

    UI08_t i = 0;
    for (i = 0; i < RF_PACKET_BUFFER_DEPTH * sizeof(RfTransceiverPacket_t); i++)
        ((UI08_t*) rfPackets)[i] = 0;

    CCBufInit(&rfRxCC, rfRxBf, sizeof(rfRxBf), 0);

    PT_INIT(&halRxBfTh);
    PT_INIT(&halPkTh);

    RfTrcvMode(0);
}

void RfTrcvMode(UI08_t tx)
{
    rfStatus.inRx = 1 - tx;
    RfTrcvSetup(tx);

    if (tx == 1)
    {
        rfStatus.isr.state = TX_PREAMBLE1;
        rfStatus.isr.byteCounter = 0;
    }
}

PT_THREAD(RfHalTickTxTh)
{
    PT_BEGIN(pt);

    while(1)
    {
        // Any packets for TX?
        // Do CSMA test
        PT_WAIT_UNTIL(pt, RfHalTxGet() == TRUE);

        do
        {
            PT_WAIT_UNTIL(pt, RfTrcvCarrierPresent() == 0);
        } while (rfStatus.isr.state != RX_RECV);

        // We're ready for TX
        RfTrcvMode(1);
        //printf("[RF] Air seems carry free - proceeding to TX\n");

        PT_WAIT_UNTIL(pt, rfStatus.isr.state == RX_RECV);

        RfHalGetReturn(rfStatus.isr.txPacket);
        //printf("[RF] TX done\n");
    }
    
    PT_END(pt);
}

PT_THREAD(RfHalTickRxTh)
{
    static UI08_t rxByteTimeout;
    static UI08_t pktRxByteIndex;
    static RfTransceiverPacket_t* packet;

    rxByteTimeout++;

    PT_BEGIN(pt);

    while (1)
    {
        // Wait until we can read a byte.
        PT_WAIT_UNTIL(pt, CCBufCanRd(&rfRxCC));
            
        UI08_t pktLength = CCBufPeekByte(&rfRxCC);

        if (pktLength > 5 && pktLength <= sizeof(packet->data) + 1)
        {
            PT_WAIT_UNTIL(pt, RfHalAnyFree());
            packet = RfHalGetFree();
            
            // Store Size
            packet->size = CCBufRdByte(&rfRxCC) - 1;
            packet->crcTx = 0;
            rxByteTimeout = 0;

            // Store Data
            for (pktRxByteIndex = 0; pktRxByteIndex < packet->size; pktRxByteIndex++)
            {
                PT_WAIT_UNTIL(pt, CCBufCanRd(&rfRxCC) || rxByteTimeout > 25);
                if(rxByteTimeout > 25) break; // abort, CRC read falls through instantly, and packet check will be done
                rxByteTimeout = 0;
                packet->data[pktRxByteIndex] = CCBufRdByte(&rfRxCC);
                packet->crcTx = RfTrcvCrcTick(packet->crcTx, packet->data[pktRxByteIndex]);
            }

            if (pktRxByteIndex == packet->size)
            {
                // Store CRC
                PT_WAIT_UNTIL(pt, CCBufCanRd(&rfRxCC) || rxByteTimeout > 25);
                packet->crcRx = CCBufRdByte(&rfRxCC);
            }

            rfPk++;
            
            // CRC error?
            if(rxByteTimeout > 25)
            {
                // Buffer error.
                // Reverse buffer , it may very well be an underrun
                //printf("[RF] Timeout\n");
                CCBufRdReverse(&rfRxCC, pktRxByteIndex);
                RfHalGetReturn(packet);
                rfPkTime++;
            }
            else if (0 && packet->crcRx != packet->crcTx)
            {
                //printf("[RF] CRC error %02X/%02X\n", rxPacket.crcRx, rxPacket.crcTx);
                CCBufRdReverse(&rfRxCC, pktRxByteIndex);
                RfHalGetReturn(packet);
                rfPkCrc++;
            }
            else
            {
            // Store timestamp
#ifdef PIC24_HW
                packet->timestamp = RtosTimestamp;
#endif

                // Store packet
                PT_WAIT_UNTIL(pt, RfHalRxPut(packet));

            // Signal OS
#ifdef PIC24_HW
                RtosTaskSignalEvent(&rfTask, RF_RX_PACKET);
#endif
            }
        }
        else
        {
            CCBufRdByte(&rfRxCC);
            //printf("[MRF49] Packet header dropped\n");
        }

    }
    
    PT_END(pt);
        
}

void RfHalGetReturn(RfTransceiverPacket_t* packet)
{
    packet->flags.acq = 0;
    packet->flags.tx = 0;
    packet->flags.proc = PCKT_NO_PROC;
}

bool_t RfHalAnyFree(void)
{
#ifdef PIC24_HW
#error "Need to implement"
#else
    if ((rfPackets[0].flags.proc == PCKT_NO_PROC && rfPackets[0].flags.acq == 0)
     || (rfPackets[1].flags.proc == PCKT_NO_PROC && rfPackets[0].flags.acq == 0))
        return TRUE;
    else
        return FALSE;
#endif
}

RfTransceiverPacket_t* RfHalGetFree(void)
{
#ifdef PIC24_HW
    UI08_t i = 0;

    for (i = 0; i < RF_PACKET_BUFFER_DEPTH; i++)
    {
        if (rfPackets[i].flags.proc == PCKT_NO_PROC && rfPackets[i].flags.acq == 0)
        {
            rfPackets[i].flags.acq = 1;
            return &(rfPackets[i]);
        }
    }
    return NULL;
#else
    if (rfPackets[0].flags.proc == PCKT_NO_PROC && rfPackets[0].flags.acq == 0)
    {
        rfPackets[0].flags.acq = 1;
        return &(rfPackets[0]);
    }
    if (rfPackets[1].flags.proc == PCKT_NO_PROC && rfPackets[0].flags.acq == 0)
    {
        rfPackets[0].flags.acq = 1;
        return &(rfPackets[1]);
    }
    return FALSE;
#endif
}

bool_t RfHalRxPut(RfTransceiverPacket_t* packet)
{
#ifdef PIC24_HW
    UI08_t i = 0;

    for (i = 0; i < RF_PACKET_BUFFER_DEPTH; i++)
    {
        if (rfPackets[i].flags.proc == PCKT_NO_PROC && rfPackets[i].flags.tx == 0)
        {
            memcpy(&(rfPackets[i]), packet, sizeof(RfTransceiverPacket_t));
            rfPackets[i].flags.proc = PCKT_NEED_PROC;
            rfPackets[i].flags.acq = 0;
            rfPackets[i].flags.tx = 0;
            return TRUE;
        }
    }

    return FALSE;
#else
    packet->flags.proc = PCKT_NEED_PROC;
    packet->flags.acq = 0;
    packet->flags.tx = 0;
    return TRUE;
#endif
}

RfTransceiverPacket_t* RfHalRxGet()
{
#ifdef PIC24_HW
    UI08_t i = 0;

    for (i = 0; i < RF_PACKET_BUFFER_DEPTH; i++)
    {
        if (rfPackets[i].flags.proc == PCKT_NEED_PROC && rfPackets[i].flags.tx == 0)
        {
            rfPackets[i].flags.proc = PCKT_NO_PROC;
            return &(rfPackets[i]);
        }
    }

    return FALSE;
#else
    if (rfPackets[0].flags.proc == PCKT_NEED_PROC && rfPackets[0].flags.tx == 0)
    {
        rfPackets[0].flags.proc = PCKT_NO_PROC;
        return &(rfPackets[0]);
    }
    if (rfPackets[1].flags.proc == PCKT_NEED_PROC && rfPackets[1].flags.tx == 0)
    {
        rfPackets[1].flags.proc = PCKT_NO_PROC;
        return &(rfPackets[1]);
    }
    return FALSE;
#endif
}

bool_t RfHalTxGet()
{
#ifndef PIC24_HW
    UI08_t i = 0;
    
    for (i = 0; i < RF_PACKET_BUFFER_DEPTH; i++)
    {
        if (rfPackets[i].flags.proc == PCKT_NEED_PROC && rfPackets[i].flags.tx == 1)
        {
            if (rfPackets[i].flags.wait_for_ack == 0)
                rfPackets[i].flags.proc = PCKT_NO_PROC;
            rfPackets[i].flags.acq = 1;
            rfStatus.isr.txPacket = &(rfPackets[i]);
            return TRUE;
        }
    }

    return FALSE;
#else
    if (rfPackets[0].flags.proc == PCKT_NEED_PROC && rfPackets[0].flags.tx == 1)
    {
        if (rfPackets[0].flags.wait_for_ack == 0)
            rfPackets[0].flags.proc = PCKT_NO_PROC;
        rfPackets[0].flags.acq = 1;
        rfStatus.isr.txPacket = &(rfPackets[0]);
        return TRUE;
    }
    if (rfPackets[1].flags.proc == PCKT_NEED_PROC && rfPackets[1].flags.tx == 1)
    {
        if (rfPackets[1].flags.wait_for_ack == 0)
            rfPackets[1].flags.proc = PCKT_NO_PROC;
        rfPackets[1].flags.acq = 1;
        rfStatus.isr.txPacket = &(rfPackets[1]);
        return TRUE;
    }
    return FALSE;
#endif
}

bool_t RfHalTxPut(RfTransceiverPacket_t* packet, UI08_t needAck)
{
#ifdef PIC24_HW
    UI08_t i;
    
    // Store in packet storage
    for (i = 0; i < RF_PACKET_BUFFER_DEPTH; i++)
    {
        if (rfPackets[i].flags.proc == PCKT_NO_PROC)
        {
            memcpy(&(rfPackets[i]), packet, sizeof(RfTransceiverPacket_t));
            rfPackets[i].flags.proc = PCKT_NEED_PROC;
            rfPackets[i].flags.tx = 1;
            rfPackets[i].flags.acq = 0;
            rfPackets[i].flags.resends = 0 ;
            rfPackets[i].flags.wait_for_ack = (needAck != 0 ? 1 : 0);
            return TRUE;
        }
    }

    // No slot found.
    return FALSE;
#else
    packet->flags.acq = 0;
    packet->flags.proc = PCKT_NEED_PROC;
    packet->flags.tx = 1;
    packet->flags.resends = 0;
    packet->flags.wait_for_ack = (needAck != 0 ? 1 : 0);
    return TRUE;
#endif
}

void RfHalTxPutAgain(void)
{
    rfStatus.isr.txPacket->flags.resends++;
    rfStatus.isr.txPacket->flags.tx = 1; // mark as TX again
    rfStatus.isr.txPacket->flags.acq = 1;
    
}

void RfHalStatemachine()
{
    switch (rfStatus.isr.state)
    {
        // Receive bytes to RX queue
        case RX_RECV:
            CCBufWrByte(&rfRxCC, RfTrcvGet());
            break;

        // Transmit states
        case TX_PREAMBLE1:
        case TX_PREAMBLE2:
            RfTrcvPut(0xAA);
            rfStatus.isr.state++;
            break;
            
        case TX_SCL1:
            RfTrcvPut(RF_NETWORKID1);
            rfStatus.isr.state++;
            break;
        case TX_SCL2:
            RfTrcvPut(RF_NETWORKID2);
            rfStatus.isr.state++;
            break;
        case TX_SIZE:
            RfTrcvPut(rfStatus.isr.txPacket->size);
            rfStatus.isr.state++;
            break;
        case TX_DATA:
            RfTrcvPut(rfStatus.isr.txPacket->data[rfStatus.isr.byteCounter]);
            rfStatus.isr.txPacket->crcTx = RfTrcvCrcTick(rfStatus.isr.txPacket->crcTx, rfStatus.isr.txPacket->data[rfStatus.isr.byteCounter]);
            rfStatus.isr.byteCounter++;
            if(rfStatus.isr.byteCounter >= rfStatus.isr.txPacket->size)
                rfStatus.isr.state = TX_CRC;
            break;
        case TX_CRC:
            RfTrcvPut(rfStatus.isr.txPacket->crcTx);
            rfStatus.isr.state++;
            break;
            
        case TX_NULL1:
        case TX_NULL2:
            RfTrcvPut(0);
            rfStatus.isr.state++;
            break;
        case TX_NULL3:
            RfTrcvPut(0);
            rfStatus.isr.state = RX_RECV;
#ifdef SERVER
            RtosTaskSignalEvent(&rfTask, RF_TX_PACKET);
#else
      // TODO: wake CPU
#endif
            RfTrcvMode(0);
            break;

    }
    
}