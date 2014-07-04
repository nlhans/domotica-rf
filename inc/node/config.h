#ifndef CONFIG_H
#define CONFIG_H

#include "stddefs.h"

#define PROTCOL_SUPPORT_CONFIG

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


extern const uint8_t CfgParameterCount;
extern const CfgParameter_t parameters[];

typedef struct CfgRam_s
{
    uint8_t nodeId;

    uint16_t sensorRate;
    uint16_t tempResolution;
    uint16_t tempSleepTime;



    uint16_t checksum;
} CfgRam_t;

extern CfgRam_t cfgRam;

#define CFG_EEPROM_ADDRESS 0x0

void CfgLoad();
void CfgSave();

uint8_t CfgGetSizeByType(CfgParameterType_t type);

#endif