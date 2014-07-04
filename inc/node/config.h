#ifndef CONFIG_H
#define CONFIG_H

#include "stddefs.h"


typedef struct CfgRam_s
{
    uint8_t nodeId;

    uint16_t checksum;
} CfgRam_t;

extern CfgRam_t cfgRam;

#define CFG_EEPROM_ADDRESS 0x0

void CfgInit();
void CfgModify(uint8_t id, void* data);
void CfgReport(uint8_t id);
void CfgReportAll();

#endif