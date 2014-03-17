#include "stddefs.h"
#include "rfstack/hal.h"
#include "rfstack/packets.h"
#include "rfstack/rf_task.h"

#include "utilities/ccbuf.h"

#define RF_SYNC_BYTE_3

PT_THREAD(RfHalTickRxTh);
PT_THREAD(RfHalTickTxTh);

struct pt halRxBfTh;
struct pt halTxBfTh;

bool_t RfHalRxPut(RfTransceiverPacket_t* rfPacket);

RfTransceiverPacket_t rfPackets[RF_PACKET_BUFFER_DEPTH];
RfTransceiverStatus_t rfStatus;

UI08_t rfRxBf[256]; // 128 bytes of Rx buffer
UI08_t rfRxBf2[32];
CircBufDef_t rfRxCC;
UI08_t rfTrcvRxEn; // is in RX mode

void RfHalInit(void)
{
    //
    rfStatus.isr.byteCounter = 0;
    rfStatus.isr.txPacket = &(rfPackets[0]);
    rfStatus.isr.state = RX_RECV;

    memset(rfPackets, 0, RF_PACKET_BUFFER_DEPTH * sizeof(RfTransceiverPacket_t));

    CCBufInit(&rfRxCC, rfRxBf, sizeof(rfRxBf), 0);

    PT_INIT(&halRxBfTh);
    PT_INIT(&halPkTh);

    RfTrcvMode(0);
}

void RfTrcvMode(UI08_t tx)
{
    if (tx == 0)
    {
        MRF49XAReset();
    }
    else
    {
        MRF49XACommand(PMCREG);                                // turn off the transmitter and receiver
        MRF49XACommand(GENCREG | 0x0080);                      // Enable the Tx register
        MRF49XACommand(PMCREG |0x0020);                        // turn on tx

        // Start TX
        RfTrcvPut(0xAA);
        rfStatus.isr.state = TX_PREAMBLE1;
    }
}

volatile UI08_t txDone = 0;
void RfHalTxDone()
{
    txDone = 1;
}

PT_THREAD(RfHalTickTxTh)
{
    static RfTransceiverPacket_t* txPacket;
    
    PT_BEGIN(pt);

    // Any packets for TX?
    // Do CSMA test
    PT_WAIT_UNTIL(pt, rfStatus.txInQueue > 0);

    printf("[RF] Setting up TX\n");
    txPacket = RfHalTxGet();

    if (txPacket == NULL)
    {
        printf("[RF] Dropping TX packet - returned NULL\n");
        PT_RESTART(pt);
    }

    do
    {
        PT_WAIT_UNTIL(pt, RfTrcvCarrierPresent() == 0);
    } while (rfStatus.isr.state != RX_RECV);

    // We're ready for TX
    RfTrcvMode(1);
    printf("[RF] Air seems carry free - proceeding to TX\n");

    txDone = 0;

    PT_WAIT_UNTIL(pt, rfStatus.isr.state == RX_RECV);

    PT_END(pt);
}

PT_THREAD(RfHalTickRxTh)
{
    static UI08_t pktRxByteIndex;
    static RfTransceiverPacket_t rxPacket;
    UI16_t pktLength = 0;
    
    PT_BEGIN(pt);

    while (CCBufCanRd(&rfRxCC))
    {
        // Search for start byte
        if (CCBufRdByte(&rfRxCC) == RF_NETWORKID3)
        {
            PT_WAIT_UNTIL(pt, CCBufCanRd(&rfRxCC));
            
            pktLength = CCBufPeekByte(&rfRxCC);
            
            if(pktLength > 0 && pktLength <= PACKET_SIZE_MAX + 1)
            {
                // Store Size
                rxPacket.size = CCBufRdByte(&rfRxCC) - 1;
                rxPacket.crcTx = 0;

                // Store Data
                for (pktRxByteIndex = 0; pktRxByteIndex < rxPacket.size; pktRxByteIndex++)
                {
                    PT_WAIT_UNTIL(pt, CCBufCanRd(&rfRxCC));
                    rxPacket.data[pktRxByteIndex] = CCBufRdByte(&rfRxCC);
                    rxPacket.crcTx = RfTrcvCrcTick(rxPacket.crcTx, rxPacket.data[pktRxByteIndex]);
                }

                // Store CRC
                PT_WAIT_UNTIL(pt, CCBufCanRd(&rfRxCC));
                rxPacket.crcRx = CCBufRdByte(&rfRxCC);

                // Store timestamp
#ifdef PIC24_HW
                rxPacket.timestamp = RtosTimestamp;
#endif

                // Store packet
                PT_WAIT_UNTIL(pt, RfHalRxPut(&rxPacket));

                // Signal OS
#ifdef PIC24_HW
                RtosTaskSignalEvent(&rfTask, RF_RX_PACKET);
#endif
            }
            else
            {
                printf("[MRF49] Packet header dropped\n");
            }
        }

    }
    
    PT_END(pt);
        
}

bool_t RfHalRxPut(RfTransceiverPacket_t* rfPacket)
{
    UI08_t i = 0;

    for (i = 0; i < RF_PACKET_BUFFER_DEPTH; i++)
    {
        if (rfPackets[i].proc == 0 && rfPackets[i].tx == 0)
        {
            memcpy(&(rfPackets[i]), rfPacket, sizeof(RfTransceiverPacket_t));
            rfPackets[i].proc = 1;
            rfStatus.rxInQueue++;
            return TRUE;
        }
    }

    return FALSE;
}


RfTransceiverPacket_t* RfHalRxGet()
{
    UI08_t i = 0;
    if (rfStatus.rxInQueue == 0)
        return FALSE;

    for (i = 0; i < RF_PACKET_BUFFER_DEPTH; i++)
    {
        if (rfPackets[i].proc != 0 && rfPackets[i].tx == 0)
        {
            rfPackets[i].proc = 0;
            rfStatus.rxInQueue--;
            
            return &(rfPackets[i]);
        }
    }

    rfStatus.rxInQueue = 0;
    return FALSE;
}

RfTransceiverPacket_t* RfHalTxGet()
{
    UI08_t i = 0;
    if (rfStatus.txInQueue == 0)
        return FALSE;

    for (i = 0; i < RF_PACKET_BUFFER_DEPTH; i++)
    {
        if (rfPackets[i].proc == 1 && rfPackets[i].tx == 1)
        {
            rfPackets[i].proc = 0;
            rfStatus.txInQueue--;
            
            return &(rfPackets[i]);
        }
    }

    rfStatus.txInQueue = 0;
    return FALSE;
}

bool_t RfHalTxPut(RfTransceiverPacket_t* packet)
{
    UI08_t i;
    
    // Calculate CRC
    packet->crcTx = 0;

    for (i = 0; i < packet->size; i++)
        packet->crcTx = RfTrcvCrcTick(packet->crcTx, packet->data[i]);

    // Store in packet storage
    for (i = 0; i < RF_PACKET_BUFFER_DEPTH; i++)
    {
        if (rfPackets[i].proc == 0)
        {
            memcpy(&(rfPackets[i]), packet, sizeof(RfTransceiverPacket_t));
            rfPackets[i].proc = 1;
            rfPackets[i].tx = 1;
            
            rfStatus.txInQueue++;

            return TRUE;
        }
    }

    // No slot found.
    return FALSE;
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
            RfTrcvPut(0xAA);
            rfStatus.isr.state = TX_PREAMBLE2;
            break;
        case TX_PREAMBLE2:
            RfTrcvPut(0xAA);
            rfStatus.isr.state = TX_SCL1;
            break;
        case TX_SCL1:
            RfTrcvPut(RF_NETWORKID1);
            rfStatus.isr.state = TX_SCL2;
            break;
        case TX_SCL2:
            RfTrcvPut(RF_NETWORKID2);
            rfStatus.isr.state = TX_SCL3;
            break;
        case TX_SCL3:
            RfTrcvPut(RF_NETWORKID3);
            rfStatus.isr.state = TX_SIZE;
            break;
        case TX_SIZE:
            RfTrcvPut(rfStatus.isr.txPacket->size);
            rfStatus.isr.state = TX_DATA;
            break;
        case TX_DATA:
            RfTrcvPut(rfStatus.isr.txPacket->data[rfStatus.isr.byteCounter]);
            rfStatus.isr.byteCounter++;
            if(rfStatus.isr.byteCounter >= rfStatus.isr.txPacket->size)
                rfStatus.isr.state = TX_CRC;
            break;
        case TX_CRC:
            RfTrcvPut(rfStatus.isr.txPacket->crcTx);
            rfStatus.isr.state = TX_NULL1;
            break;
        case TX_NULL1:
            RfTrcvPut(0);
            rfStatus.isr.state = TX_NULL2;
            break;
        case TX_NULL2:
            RfTrcvPut(0);
            rfStatus.isr.state = TX_NULL3;
            break;
        case TX_NULL3:
            RfTrcvPut(0);
            rfStatus.isr.state = RX_RECV;

            RtosTaskSignalEvent(&rfTask, RF_TX_PACKET);
            RfTrcvMode(0);
            break;

    }
    
}