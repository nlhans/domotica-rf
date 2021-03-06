#include "ipstack/udp.h"
#include "ipstack/ipv4.h"
#include "bsp/uart.h"

#include "utilities/insight.h"
#include "utilities/executiontime.h"

typedef struct UDPSocketHandlerInfo_s
{
    uint16_t port;
    UDPSocketHandler_t handler;
}UDPSocketHandlerInfo_t;

UDPSocketHandlerInfo_t handlers[UDP_MAX_HANDLERS];

void udpInit()
{
    uint8_t i = 0;

    while (i < UDP_MAX_HANDLERS)
    {
        handlers[i].port = 0xFFFF; // not used
        i++;
    }
}

void udpFirePacket(UDPPacket_t* packet)
{
    uint8_t i =0 ;
    bool done = false;
    
    while (i < UDP_MAX_HANDLERS && !done)
    {
        if(handlers[i].port == packet->udp.portDestination) // it matches our port
        {
            handlers[i].handler(packet, &done);
        }
        i++;
    }
}

void udpRegisterHandler(UDPSocketHandler_t handler, uint16_t port)
{
    uint8_t i =0 ;
    while (i < UDP_MAX_HANDLERS)
    {
        if(handlers[i].port == 0xFFFF) // it matches our port
        {
            handlers[i].port = port;
            handlers[i].handler = handler;
            break;
        }
        i++;
    }
}

void udpHandlePacket (EthernetIpv4_t* ipv4)
{
    UDPPacket_t* packet = (UDPPacket_t*)ipv4;

    packet->udp.portSource = htons(packet->udp.portSource);
    packet->udp.portDestination = htons(packet->udp.portDestination);
    packet->udp.length = htons(packet->udp.length);

    INSIGHT(UDP_RX, packet->udp.portSource, packet->udp.portDestination, packet->udp.crc, packet->udp.length);
    udpFirePacket(packet);

}
void udpTxPacket(UDPPacket_t* packet, uint16_t size, uint8_t* ip, uint16_t port)
{
    execProfile(UDP_TX);
    size += sizeof(UDPPacketHeader_t);
    
    packet->udp.length = htons(size);
    packet->udp.portDestination = htons( port );
    packet->udp.portSource =  htons( port );
    packet->udp.crc = 0;

    INSIGHT(UDP_TX, port, port, 0, size);
    ipv4TxPacket(ip, Ipv4UDP, (EthernetIpv4_t*)packet, size);
}