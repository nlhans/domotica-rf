#include "stddefs.h"
#include "rfstack/hal.h"
#include "rfstack/packets.h"

RfTransceiverPacket_t rfPackets[RF_PACKET_BUFFER_DEPTH];
RfTransceiverStatus_t rfStatus;

void RfHalInit(void)
{
    //
    rfStatus.byteCounter = 0;
    rfStatus.intermediateCrc = 0;
    rfStatus.packet = &(rfPackets[0]);
    rfStatus.state = RX_RECV_SYNC;
}

void RfHalStatemachine(RfStatus_t status)
{
    if (status.dataTransferred || 1)
    {
        switch(rfStatus.state)
        {
            // Transmit states
            case TX_WAITING:
                // Lalala
                break;
            case TX_PREAMBLE1:
                RfTrcvPut(0xAA);
                rfStatus.state = TX_PREAMBLE2;
                break;
            case TX_PREAMBLE2:
                RfTrcvPut(0xAA);
                rfStatus.state = TX_SCL1;
                break;
            case TX_SCL1:
                RfTrcvPut(RF_NETWORKID1);
                rfStatus.state = TX_SCL2;
                break;
            case TX_SCL2:
                RfTrcvPut(RF_NETWORKID2);
                rfStatus.state = TX_SIZE;
                break;
            case TX_SIZE:
                RfTrcvPut(rfStatus.packet->size);
                rfStatus.state = TX_DATA;
                break;
            case TX_DATA:
                RfTrcvPut(rfStatus.packet->data[rfStatus.byteCounter]);
                rfStatus.intermediateCrc = RfTrcvCrcTick(rfStatus.intermediateCrc,
                                       rfStatus.packet->data[rfStatus.byteCounter]);
                rfStatus.byteCounter++;
                if(rfStatus.byteCounter == rfStatus.packet->size)
                    rfStatus.state = TX_CRC;
                break;
            case TX_CRC:
                RfTrcvPut(rfStatus.intermediateCrc);
                rfStatus.packet->crc = rfStatus.intermediateCrc;
                rfStatus.state = TX_NULL1;
                break;
            case TX_NULL1:
                RfTrcvPut(0);
                rfStatus.state = TX_NULL2;
                break;
            case TX_NULL2:
                RfTrcvPut(0);
                rfStatus.state = TX_NULL3;
                break;
            case TX_NULL3:
                RfTrcvPut(0);
                rfStatus.state = TX_WAITING;
                break;

            // Receiver states
            case RX_RECV_SYNC:
                if (RfTrcvGet() == 0x6B)
                {
                    rfStatus.state = RX_RECV_HEADER;
                }
                break;
            case RX_RECV_HEADER:
                // This is the hardware header, consisting of 1 byte.
                rfStatus.packet->size = RfTrcvGet();
                if (rfStatus.packet->size != 0 && rfStatus.packet->size < 24)
                {
                    rfStatus.intermediateCrc = 0;
                    rfStatus.byteCounter = 0;
                    rfStatus.state = RX_RECV_DATA;
                }
                else
                {
                    rfStatus.state = RX_RECV_SYNC;
                }
                break;
            case RX_RECV_DATA:
                rfStatus.packet->data[rfStatus.byteCounter] = RfTrcvGet();

                printf("D: %X\r\n", rfStatus.packet->data[rfStatus.byteCounter]);
                rfStatus.intermediateCrc = RfTrcvCrcTick(rfStatus.intermediateCrc,
                                       rfStatus.packet->data[rfStatus.byteCounter]);
                rfStatus.byteCounter++;

                if (rfStatus.byteCounter == rfStatus.packet->size)
                    rfStatus.state = RX_RECV_CRC;
                break;
            case RX_RECV_CRC:
                if (rfStatus.intermediateCrc != RfTrcvGet())
                {
                    // TODO: Raise CRC error
                    printf("CRC error. Calculated: %d, Received: %d\r\n", rfStatus.intermediateCrc, RfTrcvGet());
                }
                else
                {
                    // Sent packet up to packet handlers
                    printf("New packet of %d bytes.\r\n", rfStatus.packet->size);
                    RfTrcvRearm();
                }
                rfStatus.state = RX_RECV_SYNC;
                break;
        }
    }
    //printf(",%d", rfStatus.state);
}