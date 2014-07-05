#ifndef ETHDEFS_H
#define ETHDEFS_H

#include "stddefs.h"

#define TCP_DEBUG

#define ETHERNET_FRAME_SIZE 1100

#define TCP_MAX_LISTEN_PORTS 2
#define TCP_MAX_CONNECTIONS 4

// http://en.wikipedia.org/wiki/Ethernet_frame
typedef struct EthernetFrame_s
{
    UI08_t dstMac[6];
    UI08_t srcMac[6];
    UI16_t type;
} EthernetFrame_t;

typedef enum EthernetProtocol_e
{
    ProtocolIPv4 = 0x0800,
    ProtocolARP  = 0x0806,

} EthernetProtocol_t;

typedef void (*EthernetPacketHandler_t) (EthernetFrame_t* frame, bool_t* handled);

#define htonl(x) ( ((x & 0xFF000000) >> 24) | ((x & 0x00FF0000) >> 8) | ((x & 0x0000FF00) << 8) | ((x & 0x000000FF) << 24) )
#define htons(x) ( (( x & 0xFF00) >> 8) | ((x & 0xFF) << 8))

extern void macTxFrame(EthernetFrame_t* frame, UI16_t size);
extern void macTxReplyFrame(EthernetFrame_t* frame, UI16_t size);
extern void macRxFrame();

extern const UI08_t myIp[4];
extern const UI08_t myMac[6];
extern const UI08_t myGateway[4];
extern const UI08_t myGatewayMac[6];

extern UI08_t ethFrameBuffer[ETHERNET_FRAME_SIZE];

#endif