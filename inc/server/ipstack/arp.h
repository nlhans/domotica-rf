/* 
 * File:   arp.h
 * Author: Hans
 *
 * Created on March 10, 2013, 9:06 AM
 */

#ifndef ARP_H
#define	ARP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stddefs.h"
#include "ethdefs.h"

typedef struct ArpPacket_s
{
    EthernetFrame_t frame;
    
    uint16_t htype;
    uint16_t ptype;
    uint8_t hlen;
    uint8_t plen;
    uint16_t oper;
    uint8_t sha[6]; // mac
    uint8_t spa[4]; // ip
    uint8_t tha[6]; // mac
    uint8_t tpa[4]; // ip
} ArpPacket_t;

void arpAnnounce();
void arpProcessPacket(EthernetFrame_t* frame);

extern  uint8_t thisIp[4];
extern  uint8_t thisMac[6];

#ifdef	__cplusplus
}
#endif

#endif	/* ARP_H */

