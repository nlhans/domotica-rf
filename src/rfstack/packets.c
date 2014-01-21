#include "rfstack/packets.h"

typedef enum EepromMemoryMap_e
{
    EE_NODE_ID = 0x7FFF
} EepromMemoryMap_t;
#define eepromRead(a) 0 // TODO: Implement EEPROM.

typedef struct RfNodeInfo_s
{
    union {
        UI08_t ee;
        struct
        {
            UI08_t id:6;
            UI08_t type:2;
        };
    } node;
    UI08_t sensors;
} RfNodeInfo_t;

RfNodeInfo_t rfNode;


void RfStackPacketsInit()
{
    //
    rfNode.node.ee = eepromRead(EE_NODE_ID);
    
}