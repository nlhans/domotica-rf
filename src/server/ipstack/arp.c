#include "ipstack/arp.h"
#include "bsp/uart.h"
#include "ipstack/ethdefs.h"
#include "utilities/insight.h"

void arpBuildPacket(uint8_t* targetMac, uint8_t* targetIp, bool reply);

void arpBuildPacket(uint8_t* targetMac, uint8_t* targetIp, bool reply)
{
    ArpPacket_t* arp = (ArpPacket_t*) ethFrameBuffer;

    arp->htype = htons(1);                  // ETHERNET
    arp->ptype = htons(0x0800);             // IPV4
    arp->hlen  = 6;                  // Length of MAC
    arp->plen  = 4;                  // Length of IP
    arp->oper  = htons( ((reply) ? 2 : 1) );  // request or reply

    memcpy(arp->tha, arp->sha, 6);       // 00:00:00:00:00:00
    memcpy(arp->tpa, targetIp, 4);        // 192.168.1.1?
    memcpy(arp->sha, myMac, 6);           // My MAC
    memcpy(arp->spa, myIp, 4);            // My IP

    memcpy(arp->frame.dstMac, myGatewayMac, 6);
    memcpy(arp->frame.srcMac, myMac, 6);
    arp->frame.type = htons(ProtocolARP);

    macTxFrame((EthernetFrame_t*) arp, sizeof(ArpPacket_t));
}

void arpAnnounce()
{
    uint8_t zerosMac[6] = { 0, 0, 0, 0, 0, 0 };
    arpBuildPacket(zerosMac, (uint8_t*)myGateway, false);

    INSIGHT(ARP_ANNOUNCE, myIp[0], myIp[1], myIp[2], myIp[3]);
}

void arpProcessPacket(EthernetFrame_t* frame)
{
    ArpPacket_t* arp = (ArpPacket_t*) frame;
    
    if (htons(arp->oper) != 2) // this is a request
    {
        INSIGHT(ARP_WHOHAS, arp->tpa[0],arp->tpa[1],arp->tpa[2],arp->tpa[3], (memcmp(arp->tpa, myIp, 4) == 0)?1:0,
                            arp->spa[0],arp->spa[1],arp->spa[2],arp->spa[3])

        if (memcmp(arp->tpa, myIp, 4) == 0)
        {
            // It's a match; meaning requesting a MAC address for this 'machine'
            arpBuildPacket(arp->sha, arp->spa, true);
        }
    }
}