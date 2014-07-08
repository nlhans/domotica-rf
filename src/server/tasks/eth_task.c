#include "tasks/eth_task.h"
#include "rtos/task.h"
#include "rtos/timer.h"

#include "bsp/interrupt.h"

#include "devices/enc28j60.h"
#include "devices/SST26VF032.h"

#include "ipstack/ethdefs.h"

#include "ipstack/arp.h"
#include "ipstack/ipv4.h"
#include "ipstack/udp.h"
#include "ipstack/tcp.h"
#include "ipstack/ntp.h"
#include "ipstack/icpm.h"

#include "webserver/router.h"

// Local functions
void EthTask(void);
void EthHwInit(void);

void ethTcpTick(void);
bool_t enc28j60Int(UI08_t foo);

// ethernet OS objects
RtosTask_t ethTask;
RtosTimer_t tcpTicker;
UI08_t ethTaskStk[768];

#define ETH_TCP_TICK 0x01
#define ETH_ENC_ISR 0x02
#define ETH_ENC_ERR 0x04

// IP stack constants
UI08_t ethFrameBuffer[ETHERNET_FRAME_SIZE];
const UI08_t myIp[4]            = {192, 168, 1, 123};
const UI08_t myMac[6]           = {0x00, 0x04, 0xA3, 0x12, 0x34, 0x66};
const UI08_t myGateway[4]       = {192, 168, 1, 1};
//const UI08_t myGatewayMac[6]    = {0xE0, 0x3F, 0x49, 0x95, 0x36, 0xA8 };
const uint8_t myGatewayMac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
//const UI08_t myGatewayMac[6]    = {0xB0, 0x48, 0x7A, 0xDB, 0x5B, 0xEA };
//const UI08_t myGatewayMac[6]    = {0xC8, 0x60, 0x00, 0xE3, 0x4F, 0xE3};

// Redirect to ENC28J60 device
void macRxFrame()
{
    enc28j60RxFrame();
}
void macTxFrame(EthernetFrame_t* packet, UI16_t length)
{
    enc28j60TxFrame(packet, length);
}
void macTxReplyFrame(EthernetFrame_t* packet, UI16_t length)
{
    enc28j60TxReplyFrame(packet, length);
}

// Webserver handling
bool_t httpHandleConnection(void* con)
{
    TcpConnection_t* connection = (TcpConnection_t*) con;
    connection->rxData = (TcpRxDataHandler_t) WebserverHandle;

    return TRUE;
}

bool_t httpCloseConnection(void* con)
{
    TcpConnection_t* connection = (TcpConnection_t*) con;
    connection->rxData = NULL;

    return TRUE;
}

// Initialize ethernet task
void EthInit(void)
{
    RtosTaskCreate(&ethTask, "Eth", EthTask, 20, ethTaskStk, sizeof(ethTaskStk));
    RtosTimerCreate(&tcpTicker, 100, ethTcpTick);
}

void EthHwInit(void)
{
    // Connect up ENC28j60 ISR
    PPSUnLock;

    // Hook up external interrupt to enc28j60 driver
    iPPSInput(IN_FN_PPS_INT1, IN_PIN_PPS_RP15);
    ExtIntSetup(1, enc28j60Int, TRUE, 2);

    PPSLock;

    // Boot the complete ethernet stack.
    enc28j60Initialize(ethFrameBuffer, sizeof(ethFrameBuffer));
    arpAnnounce();
    tcpInit();
    tcpListen(80, 32, httpHandleConnection, httpCloseConnection);

}

// ISR
void ethTcpTick(void)
{
    RtosTaskSignalEvent(&ethTask, ETH_TCP_TICK);
    RtosTimerRearm(&tcpTicker, 100);
}

bool_t enc28j60Int(UI08_t foo)
{
    RtosTaskSignalEvent(&ethTask, ETH_ENC_ISR);
    return TRUE;
}

void EthTask(void)
{
    EthHwInit();
    FlashInit();
    
    while(1)
    {
        UI16_t evt = RtosTaskWaitForEvent(
                ETH_TCP_TICK |
                ETH_ENC_ERR |
                ETH_ENC_ISR);

        if ((evt & ETH_ENC_ERR) != 0)
        {
            enc28j60ResetRxBuffer();
        }

        if ((evt & ETH_ENC_ISR) != 0)
        {
            while (enc28j60PacketPending())
            {
                macRxFrame();
            }
        }

        if ((evt & ETH_TCP_TICK) != 0)
        {
            tcpTick();
        }
    }
}
