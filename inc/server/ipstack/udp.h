/* 
 * File:   udp.h
 * Author: Hans
 *
 * Created on March 11, 2013, 9:10 PM
 */

#ifndef UDP_H
#define	UDP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stddefs.h"
#include "ipv4.h"

#define UDP_MAX_HANDLERS 8

typedef struct UDPPacketHeader_s
{
    uint16_t portSource;
    uint16_t portDestination;

    uint16_t length;
    uint16_t crc;
} UDPPacketHeader_t;

typedef struct UDPPacket_s
{
    EthernetIpv4_t ipv4;
    UDPPacketHeader_t udp;
} UDPPacket_t;

typedef void (*UDPSocketHandler_t) (UDPPacket_t* udp, bool* handled);

void udpInit();
void udpHandlePacket (EthernetIpv4_t* ipv4);

void udpRegisterHandler(UDPSocketHandler_t handler, uint16_t port);
void udpTxPacket(UDPPacket_t* packet, uint16_t size, uint8_t* ip, uint16_t port);

#ifdef	__cplusplus
}
#endif

#endif	/* UDP_H */

