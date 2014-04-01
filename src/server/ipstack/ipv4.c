#include "ipstack/ethdefs.h"
#include "ipstack/ipv4.h"
#include "ipstack/icpm.h"
#include "ipstack/tcp.h"
#include "ipstack/udp.h"
#include "ipstack/arp.h"
#include "bsp/uart.h"
#include "utilities/insight.h"

#include "utilities/executiontime.h"

void ipv4HandlePacket(EthernetFrame_t* frame)
{
    EthernetIpv4_t*         ipv4Header;
    UI08_t                  headerSize;
    
    ipv4Header = (EthernetIpv4_t*) frame;
    ipv4Header->header.length = htons(ipv4Header->header.length);

    headerSize = 4 * ipv4Header->header.ihl;

    INSIGHT(IPV4_RX, ipv4Header->header.length, ipv4Header->header.protocol, htons(ipv4Header->header.crc),
    ipv4Header->header.sourceIp[0],ipv4Header->header.sourceIp[1],ipv4Header->header.sourceIp[2],ipv4Header->header.sourceIp[3]);

    switch (ipv4Header->header.protocol)
    {
        case Ipv4TCP:
            tcpHandlePacket(ipv4Header);
            break;

        case Ipv4ICMP:
            icmpHandlePacket(ipv4Header);
            break;

        case Ipv4UDP:
            udpHandlePacket(ipv4Header);
            break;

        default:
            return;
    }
    
}

UI16_t ipv4Crc(UI08_t* data, UI16_t size)
{
    UI16_t b = 0;
    UI16_t* dataUI16 = (UI16_t*) (data);
    UI32_t crc = 0;
    UI32_t sum = 0;
    UI08_t counts = 0;

    while (b < size/2)
    {
        sum += htons(dataUI16[b]);
        b += 1;
        counts++;

    }

    b = sum >> 16;
    sum = sum & 0xFFFF;
    sum += b;
    crc = ~sum;

    return (UI16_t) crc;
}

void ipv4TxReplyPacket(EthernetIpv4_t* ipv4Packet, UI08_t totalSize)
{
    execProfile(IPV4_TX_REPLY);
    totalSize += sizeof(EthernetIpv4Header_t);
    
    // Swap source/destination, insert my IP
    memcpy(ipv4Packet->header.destinationIp,    ipv4Packet->header.sourceIp     , 4);
    memcpy(ipv4Packet->header.sourceIp,         myIp                            , 4);

    // Recalculate crc
    ipv4Packet->header.crc          = 0;
    ipv4Packet->header.flags        = 0;
    ipv4Packet->header.length       = totalSize;
    ipv4Packet->frame.type          = htons(ipv4Packet->frame.type);
    ipv4Packet->header.length       = htons(ipv4Packet->header.length);
    execProfile(IPV4_CRC_S);
    ipv4Packet->header.crc          = htons(ipv4Crc((UI08_t*)(&ipv4Packet->header), 4*ipv4Packet->header.ihl ) );
    execProfile(IPV4_CRC_E);

    INSIGHT(IPV4_TX_REPLY, totalSize, ipv4Packet->header.protocol, htons(ipv4Packet->header.crc),
    ipv4Packet->header.destinationIp[0],ipv4Packet->header.destinationIp[1],ipv4Packet->header.destinationIp[2],ipv4Packet->header.destinationIp[3]);
    
    macTxReplyFrame((EthernetFrame_t*)ipv4Packet, totalSize);
}

void ipv4TxPacket(UI08_t* dstIp, UI08_t protocol, EthernetIpv4_t *ipv4Packet, UI16_t size)
{
    execProfile(IPV4_TX);
    size += sizeof(EthernetIpv4Header_t);

    //memcpy(ipv4Packet.frame.dstMac, arpResolve(dstIp), 6);
    memcpy(ipv4Packet->frame.dstMac, myGatewayMac, 6);
    memcpy(ipv4Packet->frame.srcMac, myMac, 6);
    ipv4Packet->frame.type = htons(ProtocolIPv4);

    memcpy(ipv4Packet->header.destinationIp,    dstIp,  4);
    memcpy(ipv4Packet->header.sourceIp,         myIp, 4);

    ipv4Packet->header.version      = 4;
    ipv4Packet->header.ihl          = 5;
    ipv4Packet->header.DSCP         = 0;
    ipv4Packet->header.length       = htons(size); // zeker?
    ipv4Packet->header.ID           = htons(0x1234);
    ipv4Packet->header.flags        = 0;
    ipv4Packet->header.timeToLive   = 0x80;
    ipv4Packet->header.protocol     = protocol;
    ipv4Packet->header.crc          = 0;
    execProfile(IPV4_CRC_S);
    ipv4Packet->header.crc          = htons(ipv4Crc((UI08_t*)(&ipv4Packet->header), 4*ipv4Packet->header.ihl ) );
    execProfile(IPV4_CRC_E);

    INSIGHT(IPV4_TX, size, ipv4Packet->header.protocol, htons(ipv4Packet->header.crc),
    ipv4Packet->header.destinationIp[0],ipv4Packet->header.destinationIp[1],ipv4Packet->header.destinationIp[2],ipv4Packet->header.destinationIp[3]);

    macTxFrame((EthernetFrame_t*) ipv4Packet, sizeof(EthernetFrame_t) + size);
}