#ifndef RFSTACK_HAL_H
#define RFSTACK_HAL_H

#include "stddefs.h"

#include "rfstack/rfdefs.h"

#include "devices/mrf49xa.h"

#include "utilities/pt.h"

#ifdef PIC24_HW
#include "rtos/task.h"
#endif

typedef enum RfTransceiverState_e
{
    // Receiver states
    RX_RECV,                //0

    // Transmit states=
    TX_PREAMBLE1,           //1
    TX_PREAMBLE2,           //2
    TX_SCL1,                //3
    TX_SCL2,                //4
    TX_SIZE,                //6
    TX_DATA,                //7
    TX_CRC,
    TX_NULL1,
    TX_NULL2,
    TX_NULL3,
} RfTransceiverState_t;

// 24 bytes mean we can send 16-bytes payload FLASH data (bootloader)
// plus 8-bytes extra, for things like addresses.

typedef struct RfStatus_s
{
    UI08_t dataTransferred:1;
    UI08_t dataOverflow:1;
    UI08_t strongSignal:1;
    UI08_t goodData:1;
} RfStatus_t;

typedef struct RfTransceiverPacket_s
{
    // flags
    struct
    {
        UI08_t resends:2;
        UI08_t wait_for_ack:1;
        UI08_t acq:1;
        UI08_t tx:1;
        UI08_t proc:1;
    } flags;

    
    union
    {
        UI08_t data[24];
        
        struct
        {
            UI08_t src;
            UI08_t dst;
            UI08_t id;
            UI08_t opt;
            UI08_t* data;
        } frame;
    };
#ifdef PIC24_HW
    UI32_t timestamp;
#endif
    UI08_t crcTx;
    UI08_t crcRx;
    UI08_t size;

} RfTransceiverPacket_t;

typedef struct RfTransceiverStatus_s
{
    struct
    {
        UI08_t byteCounter;
        RfTransceiverPacket_t* txPacket;
        RfTransceiverState_t state;
    } isr;

    UI08_t inRx;
} RfTransceiverStatus_t;

typedef enum
{
    PCKT_NO_PROC = 0,
    PCKT_NEED_PROC = 1
};

// Status carriers
extern struct pt halRxBfTh;
extern struct pt halTxBfTh;

extern RfTransceiverStatus_t rfStatus;

// Maintenance
void RfHalInit(void);
void RfHalStatemachine();
PT_THREAD(RfHalTickRxTh);
PT_THREAD(RfHalTickTxTh);

// Raw API for transmit packets
bool_t RfHalTxPut(RfTransceiverPacket_t* packet, UI08_t needAck);
void RfHalTxPutAgain(void);

// Raw API for receive packets
RfTransceiverPacket_t* RfHalRxGet();

// API for allocating clean packet
RfTransceiverPacket_t* RfHalGetFree(void);

// Returns true if any packet free in buffer
bool_t RfHalAnyFree(void);

// Reset allocated packet
void RfHalGetReturn(RfTransceiverPacket_t* packet);

// TODO: MOVE
void RfTrcvMode(UI08_t tx);
bool_t RfHalInRxMode(void);
#endif