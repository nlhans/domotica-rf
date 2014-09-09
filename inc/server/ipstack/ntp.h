/* 
 * File:   ntp.h
 * Author: Hans
 *
 * Created on March 11, 2013, 9:30 PM
 */

#ifndef NTP_H
#define	NTP_H

#include "stddefs.h"
#include "udp.h"

typedef struct NTPPacketContent_s
{
    uint8_t flags;
    uint8_t stratum;
    uint8_t interval;
    uint8_t precision;
    uint32_t rootdelay;
    uint32_t rootdispersion;
    uint32_t id;

    uint32_t stampRef[2];
    uint32_t stampOrigin[2];
    uint32_t stampReceive[2];
    uint32_t stampTransmit[2];

} NTPPacketContent_t;

typedef struct NTPPacket_s
{
    UDPPacket_t udp;
    NTPPacketContent_t ntp;
} NTPPacket_t;

extern uint32_t ntpTimestamp;

void ntpInit();
void ntpRequest(uint8_t* ip);
void ntpHandle (UDPPacket_t* packet);

#endif	/* NTP_H */

