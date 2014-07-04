#include "config.h"
#include <string.h>

#include "devices/24aa64.h"
#include "power.h"
#include "rfstack/rf_defs.h"

CfgRam_t cfgRam;

#define NR_OF_PARAMETERS ((uint8_t) (sizeof(parameters)/sizeof(CfgParameter_t)))

const CfgParameter_t parameters[] = {
    { CFG_TYPE_INT8,    1,        &cfgRam.nodeId},
    { CFG_TYPE_INT16,   2,        &cfgRam.checksum},
};

const uint8_t CfgParameterCount = NR_OF_PARAMETERS;

void CfgLoad()
{
    eepromRxBytes(CFG_EEPROM_ADDRESS, (uint8_t*) &cfgRam, sizeof(CfgRam_t));
}

void CfgSave()
{
    eepromTxBytes(CFG_EEPROM_ADDRESS, (uint8_t*) &cfgRam, sizeof(CfgRam_t));
}

uint8_t CfgGetSizeByType(CfgParameterType_t type)
{
    switch(type)
    {
        case CFG_TYPE_INT8: return sizeof(uint8_t);
        case CFG_TYPE_INT16: return sizeof(uint16_t);
        case CFG_TYPE_INT32: return sizeof(uint32_t);
        default: return 0;
    }
}