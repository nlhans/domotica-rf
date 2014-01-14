
#define MAIN_C

#include "stddefs.h"

#include "devices/enc28j60.h"
#include "devices/mrf49xa.h"
#include "devices/mcp9800.h"
#include "devices/SST26VF032.h"

#include "bsp/adc.h"
#include "bsp/spi.h"
#include "bsp/interrupt.h"
#include "bsp/softI2c.h"
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

const UI08_t const mac[6]           = {0x00, 0x04, 0xA3, 0x12, 0x34, 0x56};
const UI08_t const ip[4]            = {192, 168, 1, 123};
const UI08_t const gateway[4]       = {192, 168, 1, 1};
const UI08_t const pc[4]            = {192, 168, 1, 147};
const UI08_t const ntpServer[4]     = {194, 171, 167, 130};

//const UI16_t humids30c[15] = {65535, 39000, 20000, 9800, 4700, 1310, 770, 440, 250, 170, 105, 72, 50, 36, 25 };

void macRxFrame(UI08_t* packet, UI16_t length)
{
    enc28j60RxFrame(packet, length);
}
void macTxFrame(EthernetFrame_t* packet, UI16_t length)
{
    enc28j60TxFrame(packet, length);
}
void macTxReplyFrame(EthernetFrame_t* packet, UI16_t length)
{
    enc28j60TxReplyFrame(packet, length);
}

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
    connection->rxData = WebserverHandle;

    return TRUE;
}

bool_t httpCloseConnection(void* con)
{
    TcpConnection_t* connection = (TcpConnection_t*) con;
    connection->rxData = NULL;

    return TRUE;
}

bool_t ipStackTick(UI08_t i, UI16_t c)
{
    if (c == 50)
    {
        if ((PORTA & (1<<4)) == 0)
            PORTA |= 1<<4;
        else
            PORTA &= ~(1<<4);
        tcpTick();
        return TRUE;
    }
    return FALSE;
}

RtosTask_t ledTask;
RtosTask_t ethTask;
UI08_t ledTaskStk[512];
UI08_t ethTaskStk[2048];

void LedTask()
{
    TRISA &= ~(1 << 9);
    while(1)
    {
        //
        PORTA |= 1 << 9;
        RtosTaskDelay(500);
        PORTA &= ~(1 << 9);
        RtosTaskDelay(500);
    }
}


void EthernetTask()
{
    UI16_t count = 0;
    while(1)
    {
        //printf("Ethernet rocks\n");
        enc28j60Int(0);
        RtosTaskDelay(50);
        if (ipStackTick(0, count))
            count = 0;
        else
            count += 10;
    }
}

void __attribute__((interrupt, no_auto_psv)) _AddressError(void)
{
    SR = 32;
    while(1);
}
void __attribute__((interrupt, no_auto_psv)) _StackError(void)
{
    SR = 32;
    while(1);
}

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
        OSCCON = 0b01111000;

        // ICSP ports.
        //TRISA &= ~(1<<0);
        //TRISA &= ~(1<<1);
        AdcInit();

    #endif
    TRISA &= ~(1<<4);
    TRISC &= ~(1<<7);
    PORTC |= 1<<7;

    UartInit();

    ExtIntInit();
    SoftI2cInit();
    initRFPorts();
    //TimerInitPeriodic16Isr(1, 1000, ipStackTick);

    PORTB |= (1<<15);

    PPSUnLock;

    // Hook up external interrupt to enc28j60 driver
    iPPSInput(IN_FN_PPS_INT1, IN_PIN_PPS_RP15);
    //ExtIntSetup(1, enc28j60Int, TRUE);
    
    PPSLock;

    spiInit(1);
    //FlashInit();
    enc28j60Initialize(mac);
    arpInit();
    arpAnnounce(mac, ip, gateway);
    ipv4Init();
    icmpInit();
    tcpInit();
    tcpListen(80, 32, httpHandleConnection, httpCloseConnection);
    
    // Profiler.
    Timer32Init(2, 0);
    execTimeReset();

    //ntpInit();
    
    RF_POWER = 1;
    SENSOR_PWR = 1;

    RtosTaskInit();
    RtosTaskCreate(&ethTask, "Eth", EthernetTask, 20, ethTaskStk, sizeof(ethTaskStk));
    RtosTaskCreate(&ledTask, "LED", LedTask, 1, ledTaskStk, sizeof(ledTaskStk));
    RtosTaskRun();

#define TRANSMITTER
    while (1)
    {
        #ifdef TRANSMITTER

        #else

        i = MRF49XA_RxPacket(buffer);

        if (i != 0)
        {
            if ((i & 0x80) == 0)
            {
                printf("CRC Y\t");
            }
            else
            {
                printf("CRC N\t");
            }
            
            for(j = 0; j < (i&0x7F); j++)
            {
                printf("0x%02X ", buffer[j]);
            }

            printf("\r\n");
        }
        #endif

    }
}

