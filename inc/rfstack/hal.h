#ifndef RFSTACK_HAL_H
#define RFSTACK_HAL_H

#include "stddefs.h"

#include "devices/mrf49xa.h"

#ifdef PIC16
#define RF_PACKET_BUFFER_DEPTH 2
#else
#define RF_PACKET_BUFFER_DEPTH 16
#endif

typedef struct RfStatus_s
{
    UI08_t dataTransferred:1;
    UI08_t dataOverflow:1;
    UI08_t strongSignal:1;
    UI08_t goodData:1;
} RfStatus_t;

typedef enum RfTransceiverState_e
{
    // Transmit states
    TX_WAITING,
    TX_PREAMBLE1,
    TX_PREAMBLE2,
    TX_SCL1,
    TX_SCL2,
    TX_SIZE,
    TX_DATA,
    TX_CRC,
    TX_NULL1,
    TX_NULL2,
    TX_NULL3,

    // Receiver states
    RX_RECV_SYNC,
    RX_RECV_HEADER,
    RX_RECV_DATA,
    RX_RECV_CRC,
} RfTransceiverState_t;

// 24 bytes mean we can send 16-bytes payload FLASH data (bootloader)
// plus 8-bytes extra, for things like addresses.

typedef struct RfTransceiverPacket_s
{
    UI08_t size;
    UI08_t node;
    UI08_t packetType;
    UI08_t crc;
#ifdef PIC24
    UI32_t timestamp;
#endif
    UI08_t data[24];
} RfTransceiverPacket_t;

typedef struct RfTransceiverStatus_s
{
    RfTransceiverState_t state;
    UI08_t byteCounter;
    UI08_t intermediateCrc;
    RfTransceiverPacket_t* packet;
} RfTransceiverStatus_t;



void RfHalInit(void);
void RfHalStatemachine(RfStatus_t status);

#endif