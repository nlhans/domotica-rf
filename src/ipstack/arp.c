#include "ipstack/arp.h"
#include "bsp/uart.h"
#include "ipstack/ethdefs.h"
#include "insight.h"

const UI08_t const onesMac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const UI08_t const zerosMac[6] = {0, 0, 0, 0, 0, 0};

void arpBuildPacket(UI08_t* senderMac, UI08_t* senderIp, UI08_t* targetMac, UI08_t* targetIp, bool_t reply);

void arpInit()
{
    // Register my handler
    /*if (! enc28j60RegisterTxHandler(arpProcessPacket))
    {
        uartTxString("Couldn't register ARP handler");
    }*/
}

void arpBuildPacket(UI08_t* senderMac, UI08_t* senderIp, UI08_t* targetMac, UI08_t* targetIp, bool_t reply)
{
    ArpPacket_t arp;

    arp.htype = htons(1);                  // ETHERNET
    arp.ptype = htons(0x0800);             // IPV4
    arp.hlen  = 6;                  // Length of MAC
    arp.plen  = 4;                  // Length of IP
    arp.oper  = htons( ((reply) ? 2 : 1) );  // request or reply

    memcpy(arp.sha, senderMac, 6);       // My MAC
    memcpy(arp.spa, senderIp, 4);        // requested IP
    memcpy(arp.tha, targetMac, 6);       // 00:00:00:00:00:00
    memcpy(arp.tpa, targetIp, 4);        // 192.168.1.1?

    memcpy(arp.frame.dstMac, onesMac, 6);
    memcpy(arp.frame.srcMac, myMac, 6);
    arp.frame.type = htons(ProtocolARP);

    macTxFrame((EthernetFrame_t*) &arp, sizeof(ArpPacket_t));
}

void arpAnnounce()
{
    arpBuildPacket(myMac, myIp, (UI08_t*)zerosMac, myGateway, FALSE);

    INSIGHT(ARP_ANNOUNCE, myIp[0], myIp[1], myIp[2], myIp[3]);
}

void arpProcessPacket(EthernetFrame_t* frame, bool_t* handled)
{
    ArpPacket_t* arp;
    if (frame -> type == 0x0806)
    {
        *handled = TRUE;

        arp = (ArpPacket_t*) frame;
        // decode its data
        arp->htype = htons(arp->htype);
        arp->ptype = htons(arp->ptype);
        arp->oper  = htons(arp->oper);
        
        if (arp->oper != 2) // this is a request
        {
            INSIGHT(ARP_WHOHAS, arp->tpa[0],arp->tpa[1],arp->tpa[2],arp->tpa[3], (memcmp(arp->tpa, myIp, 4) == 0)?1:0,
                                arp->spa[0],arp->spa[1],arp->spa[2],arp->spa[3])

            if (memcmp(arp->tpa, myIp, 4) == 0)
            {
                // It's a match; meaning requesting a MAC address for this 'machine'
                arpBuildPacket(myMac, myIp, arp->sha, arp->spa, TRUE);
            }
        }

    }
}

UI08_t* arpResolve(UI08_t* ip)
{
    return (UI08_t*) &(onesMac[0]);
}