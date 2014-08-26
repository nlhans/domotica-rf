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
        uint8_t ee;
        struct
        {
            uint8_t id:6;
            uint8_t type:2;
        } ;
    } node;
    struct
    {
        uint8_t isServer:1;
    } options;

#ifdef SERVER
    struct
    {
        uint8_t sensors;
        uint16_t battery;
        uint32_t firmwareVersion;
        RtosTime_t lastWake;
        RtosTime_t nextWake;
    }entity;
#endif
#ifdef PIC24_HW
    struct
    {
        uint32_t rxCnt;
        uint32_t txCnt;
        uint32_t crcErr;
        uint32_t idErr;
        uint32_t nackErr;
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

    // Configuration manager
    RF_CFG_CMD              = 0xB0,
    RF_CFG_WRITE            = 0xB1,
    RF_CFG_READ             = 0xB2,

    // Firmware update packets
    RF_FW_CMD               = 0xC0,
    RF_FW_WRITE             = 0xC1,
    RF_FW_READ              = 0xC2,

    // Application specific
    // Sensor nodes:
    RF_APP_SAMPLE           = 0x00,
            
} RfMsg_t;

#endif
