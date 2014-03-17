#include "stddefs.h"
#include "rfstack/hal.h"
#include "rfstack/packets.h"
#include "rfstack/rf_task.h"

#include "utilities/ccbuf.h"
#include "utilities/pt.h"

#define RF_SYNC_BYTE_3

PT_THREAD(RfHalTickBfTh);
PT_THREAD(RfHalTickPkTh);

bool_t RfHalRxStore(RfTransceiverPacket_t* rfPacket);

RfTransceiverPacket_t rfPackets[RF_PACKET_BUFFER_DEPTH];
RfTransceiverStatus_t rfStatus;

UI08_t rfRxBf[256]; // 128 bytes of Rx buffer
UI08_t rfRxBf2[32];
CircBufDef_t rfRxCC;
UI08_t rfTrcvRxEn; // is in RX mode

struct pt halRxBfTh;
struct pt halPkTh;

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
}

void RfHalTick(void)
{
    // Tick RX buffer procces thread
    RfHalTickBfTh(&halRxBfTh);

    // Tick RX packet process thread
    RfHalTickPkTh(&halPkTh);
}


PT_THREAD(RfHalTickPkTh)
{
    return;
    PT_BEGIN(pt);

    while(1)
    {
        PT_WAIT_UNTIL(pt, rfStatus.rx.queued == 1);
        //
        PT_YIELD(pt);
    }

    PT_END(pt);
}

PT_THREAD(RfHalTickBfTh)
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
            
            if(pktLength > 0 && pktLength < PACKET_SIZE_MAX)
            {
                rxPacket.size = CCBufRdByte(&rfRxCC);
                
                for (pktRxByteIndex = 0; pktRxByteIndex < rxPacket.size; pktRxByteIndex++)
                {
                    PT_WAIT_UNTIL(pt, CCBufCanRd(&rfRxCC));
                    rxPacket.data[pktRxByteIndex] = CCBufRdByte(&rfRxCC);
                    rxPacket.crc = RfTrcvCrcTick(rxPacket.crc, rxPacket.data[pktRxByteIndex]);
                    printf("%02X ", rxPacket.data[pktRxByteIndex]);
                }

                // Wait until there is storage space.
                //PT_WAIT_UNTIL(pt, RfHalRxStore(&rxPacket));
                
                rfStatus.rx.queued = 1;

                //
                printf("packet %d!\n\n", rxPacket.size);
            }
            else
            {
                printf("[MRF49] Packet header dropped\n");
            }
        }

    }
    
    PT_END(pt);
        
}

bool_t RfHalRxStore(RfTransceiverPacket_t* rfPacket)
{
    UI08_t i = 0;

    for (i = 0; i < RF_PACKET_BUFFER_DEPTH; i++)
    {
        if (rfPackets[i].size == 0)
        {
            memcpy(&(rfPackets[i]), rfPacket, sizeof(RfTransceiverPacket_t));
            return TRUE;
        }
    }

    return FALSE;
}

void RfHalTxDisable(void)
{
    
}
void RfHalTxEnable(RfTransceiverPacket_t* packet)
{
    // TODO: Setup state machine etc.
}

bool_t RfHalTxQueue(RfTransceiverPacket_t* packet)
{
    UI08_t i;

    packet->crc = 0;

    // Calculate CRC
    for (i = 0; i < packet->size; i++)
        packet->crc = RfTrcvCrcTick(packet->crc, packet->data[i]);

    // TODO: Set as TX packet

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
            if(rfStatus.isr.byteCounter == rfStatus.isr.txPacket->size)
                rfStatus.isr.state = TX_CRC;
            break;
        case TX_CRC:
            RfTrcvPut(rfStatus.isr.txPacket->crc);
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
            rfStatus.isr.state = TX_WAITING;

            RtosTaskSignalEvent(&rfTask, RF_TX_PACKET);
            break;

        case TX_WAITING:
            // TX done; waiting for more TX or return to RX

            break;

    }
    
}