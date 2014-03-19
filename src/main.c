#define MAIN_C

#define COMPILE_ETHERNET

#include "stddefs.h"

#include "rfstack/rf_task.h"

#ifdef SERVER
#include "devices/enc28j60.h"
#include "devices/SST26VF032.h"

#include "bsp/spi.h"
#include "bsp/interrupt.h"
#include "bsp/timer.h"

#include "profiling/executiontime.h"
#include "rtos/task.h"


#ifdef COMPILE_ETHERNET
#include "ipstack/ethdefs.h"

#include "ipstack/arp.h"
#include "ipstack/ipv4.h"
#include "ipstack/udp.h"
#include "ipstack/tcp.h"
#include "ipstack/ntp.h"
#include "ipstack/icpm.h"

#include "webserver/router.h"


UI08_t ethFrameBuffer[ETHERNET_FRAME_SIZE];
const UI08_t myIp[4]            = {192, 168, 2, 123};
const UI08_t myMac[6]           = {0x00, 0x04, 0xA3, 0x12, 0x34, 0x56};
const UI08_t myGateway[4]       = {192, 168, 2, 100};
//const UI08_t myGatewayMac[6]    = {0xB0, 0x48, 0x7A, 0xDB, 0x5B, 0xEA };
const UI08_t myGatewayMac[6] = {0xC8, 0x60, 0x00, 0xE3, 0x4F, 0xE3};
// PC's in network
UI08_t pc[4]            = {192, 168, 2, 122};
UI08_t ntpServer[4]     = {194, 171, 167, 130};

//const UI16_t humids30c[15] = {65535, 39000, 20000, 9800, 4700, 1310, 770, 440, 250, 170, 105, 72, 50, 36, 25 };

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

#endif

#endif

void SysInitGpio(void)
{
    SYS_GPIO_INIT_PORTA();
    SYS_GPIO_INIT_PORTB();
    SYS_GPIO_INIT_PORTC();
    
    // Enable humidity analog function
    //AdcPinEnable(BSP_HUMIDITY_ANALOG_PIN);

#ifdef SERVER
    // Pins only dedicated on server, for like FLASH and Ethernet
#endif
}

#ifdef SERVER
void UartTxStr(char * str)
{
    while(*str != '\0')
    {
        U1TXREG = *str;
        while ((U1STA & (1<<9)) != 0);
    }
}

void UartInit()
{
#ifdef PIC24_HW
    U1MODE = 0;
    
    PPSUnLock;
    iPPSOutput(OUT_PIN_PPS_RP0, OUT_FN_PPS_U1TX);
    iPPSInput(IN_FN_PPS_U1RX, IN_PIN_PPS_RP1);
    PPSLock;

    U1STA  = (1 << 10);
    U1BRG  = F_OSC_DIV_2/16/38400 - 1; //103; // 115k2 @ FRCPLL stock
    U1MODE = (1 << 15);
#endif
}

#ifdef COMPILE_ETHERNET
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

RtosTask_t ethTask;
UI08_t ethTaskStk[768];

#define ETH_TCP_TICK 0x01
#define ETH_ENC_ISR 0x02
#define ETH_ENC_ERR 0x04

#endif

RtosTask_t ledTask;
UI08_t ledTaskStk[128];

void LedTask()
{
    while(1)
    {
        //
        SYS_DBG_LED = 1;
        RtosTaskDelay(250);

        SYS_DBG_LED = 0;
        RtosTaskDelay(250);

#ifdef COMPILE_ETHERNET
        RtosTaskSignalEvent(&ethTask, ETH_TCP_TICK);
#endif
    }
}

#ifdef COMPILE_ETHERNET

void enc28j60Int(UI08_t foo)
{
    if (0) //enc28j60GetOverflowStatus() && 0) // TODO: Fix overflow situations.
    {
        RtosTaskSignalEvent(&ethTask, ETH_ENC_ERR);
        printf("Overflow occurered\r\n");
    }
    else
    {
        RtosTaskSignalEvent(&ethTask, ETH_ENC_ISR);
    }
}

void EthernetTaskInit()
{
    // Connect up ENC28j60 ISR
    PPSUnLock;

    // Hook up external interrupt to enc28j60 driver
    iPPSInput(IN_FN_PPS_INT1, IN_PIN_PPS_RP15);
    ExtIntSetup(1, enc28j60Int, TRUE, 5);

    PPSLock;

    // Boot the complete ethernet stack.
    enc28j60Initialize(ethFrameBuffer, sizeof(ethFrameBuffer));
    arpInit();
    arpAnnounce();
    tcpInit();
    tcpListen(80, 32, httpHandleConnection, httpCloseConnection);
    
}

void EthernetTask()
{
    EthernetTaskInit();
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
            //printf("[Eth] RX\n");
        }

        if ((evt & ETH_TCP_TICK) != 0)
        {
            tcpTick();
            //printf("[Eth] Tick\n");
        }
    }
}

#endif

#define TRAP_ISR __attribute__((naked, no_auto_psv,__interrupt__))
int StkAddrLo;  // order matters
int StkAddrHi;
char TrapMsgBuf[24];

void TRAP_ISR _AddressError(void)
{
    asm("mov #_StkAddrHi,w1\n\tpop [w1--]\n\tpop [w1++]\n\tpush [w1--]\n\tpush [w1++]");
    // TODO: Write StkAddrLo & Hi to EEPROM
    while(1);
}
void TRAP_ISR _StackError(void)
{
    while(1);
}
void TRAP_ISR _MathError(void)
{
    while(1);
}
#endif

int main(void)
{
    #ifdef PIC24_HW
        #if defined(__PIC24FJ64GB004__)
        AD1PCFG = 0xFFFF;
        #warning "Building for PIC24FJ64GB004"
        #else
            #if defined (__PIC24FJ64GA004__)
            AD1PCFG = 0xFFFF;
            #warning "Building for PIC24FJ64GA004"
            #else
            ADPCFG = 0xFFFF; // Ports as digital, not analog
            #warning "Building for dsPIC33FJ128GP804"
            #endif
        #endif

        ETH_CS = 1;
        RF_SPI_CS = 1;
        FLASH_CS1 = 1;
        FLASH_CS2 = 1;
    
    #else
    UI08_t i, j, k;
        #warning "Building for PIC16F1508"
        OSCCON = 0b01111000; // 16MHz
        AdcInit();
    #endif
    SysInitGpio();

    RF_POWER = 0;
    SENSOR_PWR = 0;

#ifdef SERVER

    ExtIntInit();
    spiInit(1);
    UartInit();
    printf("Hello world!\r\n");

    // Interrupts..
    INTCON1bits.NSTDIS = 1;

    RtosTaskInit();
    
#ifdef COMPILE_ETHERNET
    RtosTaskCreate(&ethTask, "Eth", EthernetTask, 20, ethTaskStk, sizeof(ethTaskStk));
#endif
    RfInit();

    RtosTaskCreate(&ledTask, "LED", LedTask, 1, ledTaskStk, sizeof(ledTaskStk));
    RtosTaskRun();



#else
#define dl() for (i = 0; i < 250; i++) \
            for(j = 0; j < 250; j++) \
                asm("nop"); \
    // i = 0, j = 0, k = 0;
    MRF49XA_Init();
    dl();
    dl();
    MRF49XA_Reset_Radio();
    while (1)
    {
        MRF49XA_TxPacket(bf, sizeof(bf));
        for (k = 0; k < 5; k++)
            dl();

    }
#endif

    //while(1);
    return 0;
}

