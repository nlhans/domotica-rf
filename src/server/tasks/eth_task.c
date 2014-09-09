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
bool enc28j60Int(uint8_t foo);

// ethernet OS objects
RtosTask_t ethTask;
RtosTimer_t tcpTicker;
uint8_t ethTaskStk[768];

#define ETH_TCP_TICK 0x01
#define ETH_ENC_ISR 0x02
#define ETH_ENC_ERR 0x04

// IP stack constants
uint8_t ethFrameBuffer[ETHERNET_FRAME_SIZE];
const uint8_t myIp[4]            = {192, 168, 1, 123};
const uint8_t myMac[6]           = {0x00, 0x04, 0xA3, 0x12, 0x34, 0x66};
const uint8_t myGateway[4]       = {192, 168, 1, 1};
//const uint8_t myGatewayMac[6]    = {0xE0, 0x3F, 0x49, 0x95, 0x36, 0xA8 };
const uint8_t myGatewayMac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
//const uint8_t myGatewayMac[6]    = {0xB0, 0x48, 0x7A, 0xDB, 0x5B, 0xEA };
//const uint8_t myGatewayMac[6]    = {0xC8, 0x60, 0x00, 0xE3, 0x4F, 0xE3};

// Redirect to ENC28J60 device
void macRxFrame()
{
    enc28j60RxFrame();
}
void macTxFrame(EthernetFrame_t* packet, uint16_t length)
{
    enc28j60TxFrame(packet, length);
}
void macTxReplyFrame(EthernetFrame_t* packet, uint16_t length)
{
    enc28j60TxReplyFrame(packet, length);
}

// Webserver handling
bool httpHandleConnection(void* con)
{
    TcpConnection_t* connection = (TcpConnection_t*) con;
    connection->rxData = (TcpRxDataHandler_t) WebserverHandle;

    return true;
}

bool httpCloseConnection(void* con)
{
    TcpConnection_t* connection = (TcpConnection_t*) con;
    connection->rxData = NULL;

    return true;
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
    ExtIntSetup(1, enc28j60Int, true, 2);

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

bool enc28j60Int(uint8_t foo)
{
    RtosTaskSignalEvent(&ethTask, ETH_ENC_ISR);
    return true;
}

volatile uint8_t econ1, econ2, estat, aha;
volatile uint8_t v = 0;

void EthTask(void)
{
    EthHwInit();
    FlashInit();
    
    while(1)
    {
        uint16_t evt = RtosTaskWaitForEvent(
                ETH_TCP_TICK |
                ETH_ENC_ERR |
                ETH_ENC_ISR);

        if ((evt & ETH_ENC_ERR) != 0)
        {
            enc28j60ResetRxBuffer();
        }

        if ((evt & ETH_ENC_ISR) != 0)
        {
            uint8_t isrPending = enc28j60ReadRegisterUint8(EIR);

            if ((isrPending & (1<<0)) != 0)
            {
                enc28j60NeedsReset();
            }
            else if ((isrPending & (1<<6)) != 0)
            {
                while (enc28j60PacketPending())
                {
                    macRxFrame();
                }
            }

            if (enc28j60IsDirty())
                enc28j60Initialize();
        }

        if ((evt & ETH_TCP_TICK) != 0)
        {
            uint8_t isrPending = enc28j60ReadRegisterUint8(EIR);

            if ((isrPending & (1<<0)) != 0 || enc28j60IsDirty())
            {
                enc28j60Initialize();
            }

            econ1 = enc28j60ReadRegisterUint8(ECON1);
            econ2 = enc28j60ReadRegisterUint8(ECON2);
            estat = enc28j60ReadRegisterUint8(ESTAT);
            aha = enc28j60ReadRegisterUint8(v);
            
            tcpTick();
        }
    }
}
