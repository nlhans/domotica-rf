#ifndef RFSTACK_HAL_H
#define RFSTACK_HAL_H

#include "stddefs.h"
#include "devices/mrf49xa.h"

typedef enum RfTransceiverState_e
{
    NOPE
} RfTransceiverState_t;

// 24 bytes mean we can send 16-bytes payload FLASH data (bootloader)
// plus 8-bytes extra, for things like addresses.

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

#endif