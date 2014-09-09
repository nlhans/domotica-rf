/* 
 * File:   tcp.h
 * Author: Hans
 *
 * Created on March 12, 2013, 7:35 PM
 */

#ifndef TCP_H
#define	TCP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stddefs.h"
#include "ipv4.h"
#include "ethdefs.h"

typedef union TcpFlags_u
{
    struct
    {
        uint8_t fin:1;
        uint8_t syn:1;
        uint8_t rst:1;
        uint8_t psh:1;
        uint8_t ack:1;
        uint8_t urg:1;
        uint8_t ece:1;
        uint8_t cwr:1;
        uint8_t ns:1;
        uint8_t resvr:3;
        uint8_t dataOffset:4;
    }bits;
    uint16_t data;
} TcpFlags_t;
typedef struct TcpPacketHeader_s
{
    uint16_t portSource;          // 2
    uint16_t portDestination;     // 4
    uint32_t sequenceNumber;      // 8
    uint32_t acknowledgement;     // 12
    TcpFlags_t flags;           // 14?
    uint16_t length;              // 16
    uint16_t crc;                 // 18
    uint16_t urgPointer;          // 20

} TcpPacketHeader_t;

typedef struct TcpPacket_s
{
    EthernetIpv4_t ipv4;
    TcpPacketHeader_t tcp;
} TcpPacket_t;

// http://userpages.umbc.edu/~jeehye/cmsc491b/lectures/tcpstate/sld001.htm
typedef enum TcpState_e
{
            // server: listen
            // client: syn tx
    TcpClosed,

            // wait for new connection
            // goto synRx
    TcpListen,

            // received sync, send sync+ack, wait for it's ack
            // goto established
    TcpSynRx,

            // establishing connection, send syn, wait for syn+ack, send ack
            // goto established
    TcpSynTx,

            // data pumping mode
    TcpEstablished,

            // sent close() , wait for others fin
    TcpFinWait1,

            // received fin, send ack
    TcpFinWait2,

            // Send ack, wait for ack, goto timewait
    TcpClosing,
    TcpTimeWait,

    TcpCloseWait,
    TcpLastAck,

    NUM_OF_TCP_STATES
} TcpState_t;

#ifdef TCP_DEBUG
extern const char * const TcpStateStrings[NUM_OF_TCP_STATES];
#endif

typedef bool (*TcpConnectedHandler_t) (void* connectionHandle);
typedef void (*TcpRxDataHandler_t) (void* connectionHandle, bool push, uint8_t* data, uint16_t length);

typedef struct TcpListener_s
{
    bool InUse;
    uint8_t maxConnections;
    uint16_t localPort;
    TcpConnectedHandler_t acceptConnectionHandler;
    TcpConnectedHandler_t closeConnectionHandler;
} TcpListener_t;

typedef struct TcpConnection_s
{
    uint32_t lastSequenceNumber;
    uint32_t lastAcknowledgeNumber;
    TcpListener_t* listener;
    TcpState_t state;
    uint8_t remoteIp[4];
    uint8_t remoteMac[6];
    uint16_t remotePort;
    uint16_t timer;
    TcpRxDataHandler_t rxData;
} TcpConnection_t;

extern TcpConnection_t tcpConnections[TCP_MAX_CONNECTIONS];

void tcpInit();
void tcpHandlePacket(EthernetIpv4_t* ipv4);
bool tcpListen(uint16_t port, uint8_t maxConnections, TcpConnectedHandler_t accept, TcpConnectedHandler_t close);

void tcpTxReplyPacket(uint16_t dataSize, TcpFlags_t flags, TcpPacket_t* packet, TcpConnection_t* connection);
void tcpTxPacket(uint16_t dataSize, TcpFlags_t flags, TcpConnection_t* connection);

char* tcpGetDataPtr();

void tcpTick(void);
void tcpCloseObj(TcpConnection_t* connection);

#ifdef	__cplusplus
}
#endif

#endif	/* TCP_H */

