/* 
 * File:   ipv4.h
 * Author: Hans
 *
 * Created on March 10, 2013, 5:29 PM
 */

#ifndef IPV4_H
#define	IPV4_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stddefs.h"
#include "ethdefs.h"

#define IPV4_MAXIMUM_PROTOCOL_HANDLERS 3 // UDP, TCP, ICMP

// http://en.wikipedia.org/wiki/List_of_IP_protocol_numbers
typedef enum EthernetIpv4Protocol_e
{
    Ipv4ICMP = 0x01,
    Ipv4TCP = 0x06,
    Ipv4UDP = 0x11
} EthernetIpv4Protocol_t;

typedef struct EthernetIpv4Header_s
{
    uint8_t ihl:4;
    uint8_t version:4;
    uint8_t DSCP;
    uint16_t length;

    uint16_t ID;
    uint16_t flags;
    uint8_t timeToLive;
    uint8_t protocol;
    volatile uint16_t crc;

    uint8_t sourceIp[4];
    uint8_t destinationIp[4];

} EthernetIpv4Header_t;

typedef struct EthernetIpv4_s
{
    EthernetFrame_t frame;
    EthernetIpv4Header_t header;
} EthernetIpv4_t;

typedef void (*Ipv4PacketHandler_t) (EthernetIpv4_t* header, bool* handled);


void ipv4Init();
void ipv4RegisterHandler(Ipv4PacketHandler_t myHandler);
void ipv4UnregisterHandler(Ipv4PacketHandler_t myHandler);
void ipvFireHandlers(EthernetIpv4_t* frame, uint8_t* data, uint16_t length);
void ipv4HandlePacket(EthernetFrame_t* frame);
void ipv4TxPacket(uint8_t* dstIp, uint8_t protocol, EthernetIpv4_t *data, uint16_t size);
void ipv4TxReplyPacket(EthernetIpv4_t* ipv4Packet, uint8_t totalSize);
uint16_t ipv4Crc(uint8_t* data, uint16_t size);

#ifdef	__cplusplus
}
#endif

#endif	/* IPV4_H */

