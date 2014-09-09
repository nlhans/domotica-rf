#include "ipstack/icpm.h"
#include "ipstack/ipv4.h"
#include "bsp/spi.h"
#include "bsp/uart.h"
#include "ipstack/ethdefs.h"
#include "utilities/insight.h"

void icmpHandlePacket (EthernetIpv4_t* header)
{
    ICMPPacket_t* packet = (ICMPPacket_t*) header;

    if (packet->icmp.type == 8 && packet->icmp.code == 0) // echo request
    {
        packet->icmp.type = 0;
        packet->icmp.crc = 0;
        packet->icmp.crc = htons( ipv4Crc( (uint8_t*) (&packet->icmp), header->header.length - sizeof(EthernetIpv4Header_t)) );

        INSIGHT(ICMP_PINGPONG);
        ipv4TxReplyPacket((EthernetIpv4_t*) packet, header->header.length - sizeof(EthernetIpv4Header_t) );
    }
}
