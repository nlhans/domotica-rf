#ifndef RFSTACK_PACKETS_H
#define RFSTACK_PACKETS_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stddefs.h"
#include "rfstack/rf_defs.h"

#include "devices/mrf49xa_defs.h"

#define PROTOCOL_SUPPORT_FIRMWARE
//#define PROTOCOL_SUPPORT_FIRMWARE_BOOTLOADER

#define FW_RUNTIME_MAJOR 0
#define FW_RUNTIME_MINOR 1

#define FW_APPLICATION_MAJOR_LOC 0x0
#define FW_APPLICATION_MINOR_LOC 0x1
#define FW_APPLICATION_VERSION 0x0

#define FW_APPLICATION_STATE 0x2

void RfSendPowerState(Mrf49xaMac_t* inst);
void RfSendSampleWeatherNode(Mrf49xaMac_t* inst, uint16_t temperature, uint16_t humidity);

void HandlePacket(Mrf49xaMac_t* inst, rfTrcvPacket_t* packet);



extern Mrf49xaMac_t* macPtr;
extern uint32_t syncedTime;



#ifdef __cplusplus
}
#endif

#endif
