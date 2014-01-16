
#define MAIN_C

#include "stddefs.h"

#include "devices/mrf49xa.h"
#include "devices/mcp9800.h"

#include "bsp/adc.h"
#include "bsp/softI2c.h"

#ifdef SERVER
#include "devices/enc28j60.h"
#include "devices/SST26VF032.h"

#include "bsp/spi.h"
#include "bsp/interrupt.h"
#include "bsp/timer.h"

#include "ipstack/arp.h"
#include "ipstack/ipv4.h"
#include "ipstack/udp.h"
#include "ipstack/tcp.h"
#include "ipstack/ntp.h"
#include "ipstack/icpm.h"

#include "webserver/router.h"
#include "profiling/executiontime.h"

#include "rtos/task.h"

UI08_t ethFrameBuffer[1100];
UI08_t mac[6]           = {0x00, 0x04, 0xA3, 0x12, 0x34, 0x56};
UI08_t ip[4]            = {192, 168, 1, 123};
UI08_t gateway[4]       = {192, 168, 1, 1};
UI08_t pc[4]            = {192, 168, 1, 147};
UI08_t ntpServer[4]     = {194, 171, 167, 130};

//const UI16_t humids30c[15] = {65535, 39000, 20000, 9800, 4700, 1310, 770, 440, 250, 170, 105, 72, 50, 36, 25 };

UI08_t* macGetPacketBuffer(void)
{
    return enc28j60GetPacketBuffer();
}
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

void initRFPorts(void)
{
    // Standard node configuration.
    TRIS_SPI_SDI 	= INPUT_PIN;
    TRIS_SPI_SDO 	= OUTPUT_PIN;
    TRIS_SPI_SCK 	= OUTPUT_PIN;
    TRIS_SPI_CS  	= OUTPUT_PIN;
    TRIS_RF_IRQ		= INPUT_PIN;
    TRIS_RF_FSEL	= OUTPUT_PIN;
    TRIS_RF_DIO		= INPUT_PIN;
    TRIS_RF_RES		= OUTPUT_PIN;
    TRIS_RF_FINT	= INPUT_PIN;
    TRIS_RF_IRQ		= INPUT_PIN;
    TRIS_RF_POWER       = OUTPUT_PIN;
    TRIS_SENSOR_PWR     = OUTPUT_PIN;

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
    
    TRISB &= ~(1<<0);
    TRISB |= 1<<1;

    PPSUnLock;
    iPPSOutput(OUT_PIN_PPS_RP0, OUT_FN_PPS_U1TX);
    iPPSInput(IN_FN_PPS_U1RX, IN_PIN_PPS_RP1);
    PPSLock;

    U1STA  = (1 << 10);
    U1BRG  = F_OSC_DIV_2/16/19200 - 1; //103; // 115k2 @ FRCPLL stock
    U1MODE = (1 << 15);
#endif
}

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

RtosTask_t ledTask;
RtosTask_t ethTask;
UI08_t ledTaskStk[128];
UI08_t ethTaskStk[768];
#define ETH_TCP_TICK 0x01
#define ETH_ENC_ISR 0x02
#define ETH_ENC_ERR 0x04

void LedTask()
{
    TRISA &= ~(1 << 9);
    while(1)
    {
        //
        PORTA |= 1 << 9;
        RtosTaskDelay(100);

        PORTA &= ~(1 << 9);
        RtosTaskDelay(100);

        RtosTaskSignalEvent(&ethTask, ETH_TCP_TICK);
    }
}

void EthernetTaskInit()
{

    // Connect up ENC28j60 ISR
    PORTB |= (1<<15);

    PPSUnLock;

    // Hook up external interrupt to enc28j60 driver
    iPPSInput(IN_FN_PPS_INT1, IN_PIN_PPS_RP15);
    ExtIntInit();
    ExtIntSetup(1, enc28j60Int, TRUE);

    PPSLock;

    // Boot the complete ethernet stack.
    spiInit(1);
    enc28j60Initialize(mac, ethFrameBuffer, sizeof(ethFrameBuffer));
    arpInit();
    arpAnnounce(mac, ip, gateway);
    ipv4Init();
    icmpInit();
    tcpInit();
    tcpListen(80, 32, httpHandleConnection, httpCloseConnection);
    
}

void EthernetTask()
{
    TRISA &= ~(1<<4);
    EthernetTaskInit();
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

        if ((PORTA & (1<<4)) != 0)
            PORTA &= ~(1<<4);
        else
            PORTA |= 1<<4;
    }
}


void enc28j60Int(UI08_t foo)
{
    if (enc28j60GetOverflowStatus() && 0) // TODO: Fix overflow situations.
    {
        RtosTaskSignalEvent(&ethTask, ETH_ENC_ERR);
        printf("Overflow occurered\r\n");
    }
    else
    {
        RtosTaskSignalEvent(&ethTask, ETH_ENC_ISR);
    }
}


void __attribute__((interrupt,no_auto_psv)) _AddressError(void)
{
    while(1);
}
void __attribute__((interrupt,no_auto_psv)) _StackError(void)
{
    while(1);
}
void __attribute__((interrupt,no_auto_psv)) _MathError(void)
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

    #else
        #warning "Building for PIC16F1508"
        //OSCCON = 0b01111000; // 16MHz
            OSCCON = 0b00001000;
            
        // ICSP ports.
        //TRISA &= ~(1<<0);
        //TRISA &= ~(1<<1);
        AdcInit();

    #endif
    SoftI2cInit();
    initRFPorts();

    RF_POWER = 1;
    SENSOR_PWR = 1;

#ifdef SERVER

    TRISA &= ~(1<<4);
    TRISC &= ~(1<<7);
    PORTC |= 1<<7;

    UartInit();

    // Profiler.
    Timer32Init(2, 0);
    execTimeReset();
    FlashInit();

    RtosTaskInit();
    RtosTaskCreate(&ethTask, "Eth", EthernetTask, 20, ethTaskStk, sizeof(ethTaskStk));
    RtosTaskCreate(&ledTask, "LED", LedTask, 1, ledTaskStk, sizeof(ledTaskStk));
    RtosTaskRun();
#else
    UI08_t bf[8];
    
    bf[0] = 0x12;
    bf[1] = 0x34;
    bf[2] = 0x56;
    bf[3] = 0x78;
    bf[4] = 0x12;
    bf[5] = 0x34;
    bf[6] = 0x56;
    bf[7] = 0x78;
    

    while (1)
    {
        SPI_Write(0x55);
    }
#endif

    //while(1);
    return 0;
}

