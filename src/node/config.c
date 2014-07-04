#include "config.h"
#include <string.h>

#include "devices/24aa64.h"
#include "power.h"

typedef enum CfgParameterType_e
{
    CFG_TYPE_INT8,
    CFG_TYPE_INT16,
    CFG_TYPE_INT32
} CfgParameterType_t;

typedef struct CfgParameter_s
{
    uint8_t type;
    uint8_t id;
    uint8_t* ptr;
} CfgParameter_t;

CfgRam_t cfgRam;

const CfgParameter_t parameters[] = {
    { CFG_TYPE_INT8,    1,        &cfgRam.nodeId},
    { CFG_TYPE_INT16,   2,        &cfgRam.checksum},
};

#define NR_OF_PARAMETERS ((uint8_t) (sizeof(parameters)/sizeof(CfgParameter_t)))


uint8_t cfgGetSizeByType(CfgParameterType_t type);

void CfgInit()
{
    eepromRxBytes(CFG_EEPROM_ADDRESS, (uint8_t*) &cfgRam, sizeof(CfgRam_t));
}

void CfgSave()
{
    eepromTxBytes(CFG_EEPROM_ADDRESS, (uint8_t*) &cfgRam, sizeof(CfgRam_t));
}

void CfgReport(uint8_t id)
{
    for (uint8_t i = 0; i < NR_OF_PARAMETERS; i++)
    {
        if (parameters[i].id == id)
        {
            uint8_t nrOfBytes = cfgGetSizeByType(parameters[i].type);

        }
    }
}

void CfgModify(uint8_t id, void* data)
{
    for (uint8_t i = 0; i < NR_OF_PARAMETERS; i++)
    {
        if (parameters[i].id == id)
        {
            uint8_t nrOfBytes = cfgGetSizeByType(parameters[i].type);//1;

            //if (parameters[i].options.type == 2) nrOfBytes = 2;
            //else if (parameters[i].options.type == 3) nrOfBytes = 4;
            
            memcpy(parameters[i].ptr, data, nrOfBytes);
        }
    }
}

uint8_t cfgGetSizeByType(CfgParameterType_t type)
{
    switch(type)
    {
        case CFG_TYPE_INT8: return sizeof(uint8_t);
        case CFG_TYPE_INT16: return sizeof(uint16_t);
        case CFG_TYPE_INT32: return sizeof(uint32_t);
        default: return 0;
    }
}

void CfgReportAll()
{
    uint8_t i = 0;
    for(i = 0 ; i < NR_OF_PARAMETERS; i++)
    {
        CfgReport(i);
    }
}