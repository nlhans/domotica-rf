#ifndef RFSTACK_RFDEFS
#define RFSTACK_RFDEFS

#include "stddefs.h"

#ifdef PIC24_HW
#include "rtos/task.h"
#ifndef dsPIC33
//#define RF_DEBUG
#define RF_HISTORY_DEPTH 2
#else
#undef RF_DEBUG
#endif
#endif

#ifdef dsPIC33
#define RF_NO_ID_FILTER
#endif

#define RF_DATA_LENGTH      16
#define RF_PACKET_LENGTH    (RF_DATA_LENGTH + 5)

// Configuration
#define RF_NETWORKID1 0x2D
#define RF_NETWORKID2 0xD4

// Standard types

typedef struct RfNodeInfo_s
{
    union {
        UI08_t ee;
        struct
        {
            UI08_t id:6;
            UI08_t type:2;
        } ;
    } node;
    struct
    {
        UI08_t isServer:1;
    } options;

#ifdef SERVER
    struct
    {
        UI08_t sensors;
        UI16_t battery;
        UI32_t firmwareVersion;
        RtosTime_t lastWake;
        RtosTime_t nextWake;
    }entity;
#endif
#ifdef PIC24_HW
    struct
    {
        UI32_t rxCnt;
        UI32_t txCnt;
        UI32_t crcErr;
        UI32_t idErr;
        UI32_t nackErr;
    } stats;
#endif
} RfNodeInfo_t;

typedef enum
{
    // Network management packets
    RF_PING                 = 0xA0,
    RF_ACK                  = 0xA1,
    RF_TIME_SYNC            = 0xA2,
    RF_POWER_STATUS         = 0xA3,

    // Firmware update packets
    RF_FW_CMD               = 0xC0,
    RF_FW_WRITE             = 0xC1,
    RF_FW_READ              = 0xC2,

} RfMsg_t;

#endif
