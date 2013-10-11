
#define MAIN_C

#include "stddefs.h"

#include "devices/enc28j60.h"
#include "devices/mrf49xa.h"
#include "devices/mcp9800.h"
#include "devices/SST26VF032.h"

#include "bsp/adc.h"
#include "bsp/spi.h"
#include "bsp/softI2c.h"

#include "ipstack/arp.h"
#include "ipstack/ipv4.h"
#include "ipstack/udp.h"
#include "ipstack/tcp.h"
#include "ipstack/ntp.h"
#include "ipstack/icpm.h"

UI08_t mac[6]           = {0x00, 0x04, 0xA3, 0x12, 0x34, 0x56};
UI08_t ip[4]            = {192, 168, 1, 123};
UI08_t gateway[4]       = {192, 168, 1, 1};
UI08_t pc[4]       = {192, 168, 1, 147};
UI08_t ntpServer[4] = {194, 171, 167, 130};

const UI16_t humids30c[15] = {65535, 39000, 20000, 9800, 4700, 1310, 770, 440, 250, 170, 105, 72, 50, 36, 25 };

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

void UartInit()
{
#ifdef PIC24_HW
    U1MODE = 0b1000000000000000;
    U1STA = 0b0000010000000000;
    U1BRG = 51; // 115k2 @ FRCPLL stock
    PORTB &= ~(1<<0);
    PORTB |= 1<<1;
    PPSUnLock;
    iPPSOutput(OUT_PIN_PPS_RP0, OUT_FN_PPS_U1TX);
    iPPSInput(IN_FN_PPS_U1RX, IN_PIN_PPS_RP1);
    PPSLock;
#endif
}

UI08_t buffer[16];
#include "math.h"
void AdcConvert(void)
{
    UI16_t temp;
/*
    sensor = AdcSample(BSP_HUMIDITY_CHANNEL);
    buffer[0] = sensor >> 8;
    buffer[1] = sensor & 0xFF;
    
    temp = AdcSample(ADC_FVR);
    buffer[2] = temp >> 8;
    buffer[3] = temp & 0xFF;

    temp = (AdcSample(ADC_TEMP) - 480) * 100 / 120 - 43;
    buffer[4] = temp >> 8;
    buffer[5] = temp & 0xFF;

    // Lock in to 29C.
    temp = 27;

    // Temperature in C
    buffer[6] = temp;
*/
    __delay_ms(120);
    temp = Mcp9800Read();
    buffer[6] = temp >> 8;
    buffer[7] = temp & 0xFF;
    
    //SENSOR_PWR = 0;

    /*float voltage               = (sensor/1023.0);
    float ntcResistance         = 47*pow(1/1.044, buffer[6]-25);
    float humidityResistance    = (1/(1/voltage - 1)) * ntcResistance * 10;

    UI16_t iHumidityResistance  = (UI16_t) humidityResistance;
    
    buffer[7] = iHumidityResistance >> 8;
    buffer[8] = iHumidityResistance & 0xFF;

    UI08_t ii = 0;

    while(ii < 14)
    {
        if (humids30c[ii+1] <= iHumidityResistance && humids30c[ii] >= ii)
        {
            // GOOD
            float part = ((float)humids30c[ii] - humidityResistance) / ((float)humids30c[ii+1] - (float)humids30c[ii]);
            float humidity = (1-part)*5 + 15 + ii * 5;
            buffer[9] = (UI08_t) humidity;
            break;
        }
        ii++;
    }*/
}
UI08_t frameBf[512];

const char* httpGetStr = "GET";
const char* httpPostStr = "POST";
const char* httpVersionStr = "HTTP/";

const char* errorPage= "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\nError in parsing URL.";
const char* urlImageStr = "/image.png";
const UI08_t image[539] = { 137, 80, 78, 71, 13, 10, 26, 10, 0, 0, 0, 13, 73, 72, 68, 82, 0, 0, 0, 14, 0, 0, 0, 28, 8, 3, 0, 0, 0, 102, 136, 126, 115, 0, 0, 0, 225, 80, 76, 84, 69, 9, 132, 181, 8, 129, 177, 10, 145, 190, 10, 143, 187, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 44, 155, 199, 24, 145, 193, 28, 159, 203, 10, 138, 189, 11, 152, 199, 51, 168, 207, 34, 150, 196, 18, 155, 201, 39, 152, 197, 53, 159, 201, 61, 172, 209, 65, 173, 210, 56, 160, 202, 16, 141, 191, 20, 143, 192, 46, 166, 206, 40, 163, 205, 23, 157, 202, 51, 158, 201, 38, 152, 197, 61, 162, 197, 46, 151, 186, 40, 139, 178, 40, 164, 206, 53, 170, 209, 53, 150, 189, 167, 213, 231, 68, 166, 205, 43, 151, 194, 29, 147, 195, 76, 170, 207, 180, 219, 235, 180, 217, 230, 182, 224, 238, 22, 130, 174, 59, 161, 203, 25, 143, 182, 62, 173, 210, 55, 154, 188, 23, 136, 181, 31, 135, 176, 67, 166, 205, 75, 178, 213, 90, 166, 197, 36, 147, 184, 95, 175, 203, 72, 177, 212, 26, 149, 190, 168, 218, 235, 181, 224, 238, 80, 176, 209, 98, 188, 218, 48, 167, 207, 93, 178, 212, 74, 165, 202, 49, 157, 200, 57, 170, 208, 43, 154, 198, 47, 143, 180, 179, 219, 235, 177, 213, 227, 50, 163, 202, 34, 161, 204, 82, 181, 214, 169, 104, 4, 227, 0, 0, 0, 10, 116, 82, 78, 83, 200, 205, 200, 205, 19, 13, 1, 4, 20, 6, 80, 99, 25, 182, 0, 0, 0, 223, 73, 68, 65, 84, 120, 94, 133, 207, 69, 118, 196, 48, 16, 69, 81, 53, 89, 81, 9, 205, 216, 28, 100, 102, 102, 216, 255, 130, 82, 174, 246, 209, 52, 111, 242, 207, 29, 126, 22, 48, 227, 67, 112, 147, 231, 249, 250, 122, 222, 102, 56, 19, 38, 73, 146, 143, 175, 207, 4, 51, 2, 249, 138, 1, 108, 226, 16, 165, 220, 154, 207, 95, 118, 164, 148, 196, 56, 142, 47, 1, 158, 113, 136, 97, 24, 158, 1, 156, 191, 135, 33, 81, 41, 117, 0, 112, 168, 212, 118, 199, 211, 21, 21, 177, 44, 203, 13, 128, 93, 28, 98, 129, 77, 198, 227, 73, 81, 180, 236, 25, 95, 79, 48, 62, 26, 174, 117, 13, 71, 156, 5, 92, 248, 120, 192, 130, 190, 245, 245, 241, 145, 205, 178, 108, 58, 205, 218, 44, 62, 178, 105, 154, 158, 236, 237, 167, 152, 21, 200, 55, 12, 224, 2, 135, 232, 220, 247, 108, 246, 240, 235, 156, 35, 86, 85, 117, 13, 240, 136, 67, 172, 235, 250, 10, 224, 230, 169, 174, 137, 90, 235, 35, 128, 99, 173, 127, 58, 222, 174, 168, 137, 77, 211, 220, 1, 220, 227, 16, 35, 108, 177, 92, 46, 162, 168, 229, 192, 250, 6, 255, 60, 250, 3, 156, 140, 31, 18, 9, 154, 221, 83, 0, 0, 0, 0, 73, 69, 78, 68, 174, 66, 96, 130 };
const char* responseImage = "HTTP/1.1 200 OK\r\nContent-type: image/png\r\n\r\n";
const char* response = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n<meta http-equiv=\"refresh\" content=\"5\">Hello wonderful TCP world!\r\nVisit count: %d / Temperature: %.1f C<br/>URL: %s<br /><pre>%s</pre><br/>"; //<img src=\"image.png\">";
char bfResponse[1024];
UI16_t counter = 0;

typedef enum HttpRequestType_e
{
    HttpGet,
    HttpPost,
    //etc.
} HttpRequestType_t;
typedef struct HttpRequest_s
{
    HttpRequestType_t type;
    UI08_t* url;
    UI16_t urlLength;
} HttpRequest_t;

static HttpRequest_t currentRequest;

void httpHandleData(void* con, bool_t push, UI08_t* d, UI16_t s)
{
    char* request = (char*) d;
    UI08_t url[64];
    UI32_t addr = 0;
    memset(url, 0, 64);
    
    float tempF;
    if (push)
    {
        TcpFlags_t fl ;
        fl.bits.ack = 1;
        fl.bits.fin = 1;
        fl.bits.psh = 1;

        if(strncmp(httpGetStr, request, 3) == 0)
        {
            currentRequest.type = HttpGet;
            currentRequest.url = d + 4;
        }
        else if(strncmp(httpPostStr, request, 4) == 0)
        {
            currentRequest.type = HttpPost;
            currentRequest.url = d + 5;
        }
        else
        {
            // ERROR
            tcpTxPacket((UI08_t*) errorPage, strlen(errorPage), fl, ((TcpConnection_t*) con));
            return;
        }

        char* foundHttpVersion = strstr(request, httpVersionStr) - 1; // minus space
        if (foundHttpVersion == NULL)
        {
            foundHttpVersion = strchr(currentRequest.url, ' ');
            if(foundHttpVersion)
            {
                // ERROR
                tcpTxPacket((UI08_t*) errorPage, strlen(errorPage), fl, ((TcpConnection_t*) con));
                return;
            }
        }

        currentRequest.urlLength = ((UI16_t)foundHttpVersion) - ((UI16_t)currentRequest.url);

        if(currentRequest.urlLength > 0)
            strncpy(url, currentRequest.url, currentRequest.urlLength);
        else
            strcpy(url, "Error");
        
        if (strncmp(urlImageStr, url, strlen(urlImageStr)) == 0)
        {
            tcpTxPacket((UI08_t*) responseImage, strlen(responseImage), fl, ((TcpConnection_t*) con));

            fl.bits.fin = 1;
            fl.bits.psh = 1;

            tcpTxPacket((UI08_t*) image, 539, fl, ((TcpConnection_t*) con));
            return;
        }
        counter++;
        tempF = ((float)Mcp9800Read())/256.0f;

        char memDump[256];
        for(addr = 0x1000; addr < 0x1000 + 16; addr++)
            sprintf(memDump, "%s 0x%02X", memDump, FlashRxByte(addr));

        UI08_t* id = FlashReadId();
        sprintf(memDump, "%s\nID: %X %X %X", memDump, id[0], id[1], id[2]);
        
        sprintf(bfResponse, response, counter, tempF, url, memDump);
        
        Mcp9800Start(Mcp9800_12bit);
    

        tcpTxPacket((UI08_t*) bfResponse, strlen(bfResponse), fl, ((TcpConnection_t*) con));

        memset(d, 0, s);
        //TcpTx(con, response, strlen(response));
        //TcpClose(con);
    }
}

bool_t httpHandleConnection(void* con)
{
    TcpConnection_t* connection = (TcpConnection_t*) con;
    connection->rxData = httpHandleData;

    return TRUE;
}

int main ( void ){
    UI16_t i, j;
    UI08_t bf[256];
    #ifdef PIC24_HW
        #if defined(__PIC24FJ64GB004__)
        AD1PCFG = 0xFFFF;
        #warning "Building for PIC24FJ64GB004"
        #else
        ADPCFG = 0xFFFF; // Ports as digital, not analog
        #warning "Building for dsPIC33FJ128GP804"
        #endif

    #else
        #warning "Building for PIC16F1508"
        OSCCON = 0b01111000;

        // ICSP ports.
        //TRISA &= ~(1<<0);
        //TRISA &= ~(1<<1);
        AdcInit();

    #endif
    TRISC &= ~(1<<7);
    PORTC |= 1<<7;

    UartInit();
    SoftI2cInit();
    initRFPorts();


    spiInit(1);
    FlashInit();
    /*if (FlashRxByte(0) == 0xFF)
    {
        printf("Uploading flash data.");
        for(i = 0; i < 256; i++)
        {
            bf[i] = i;
        }
        FlashTxBytes(0, bf, 256);
    }*/
    enc28j60Initialize(mac);
    arpInit();
    arpAnnounce(mac, ip, gateway);
    ipv4Init();
    icmpInit();
    tcpInit();
    tcpListen(1234, 32, httpHandleConnection);
    //ntpInit();
    RF_POWER = 1;

    SENSOR_PWR = 1;

    Mcp9800Start(Mcp9800_12bit);
    
    //MRF49XA_Init();
    
    //Mrf49XaDelay(2);
    //Mrf49XaDelay(2);
    
    //MRF49XA_Reset_Radio();
#define TRANSMITTER
    while (1)
    {

        while (!enc28j60PacketPending());
            enc28j60RxFrame(frameBf, sizeof(frameBf));
            continue;
        #ifdef TRANSMITTER

        //AdcConvert();

        /*for (addr = 0; addr < 0xFF; addr ++)
        {
            //
            buffer[0] = addr;
            buffer[2] = 0;
            buffer[3] = 0;

            SoftI2cStart();
            buffer[1] = SoftI2cTxByte(addr);
            SoftI2cStop();

            if(buffer[1] != 0)
                printf("Addr %X\r\n", addr);
            //if(buffer[1] != 0)
            //MRF49XA_TxPacket(buffer, 4);
        */

    UI16_t temp = Mcp9800Read();
    printf("Temperature: %d\r\n",temp);
        //while(1);
        //MRF49XA_TxPacket(buffer, 10);
        
        Mrf49XaDelay(2);

        //printf("Tx\r\n"); 
        
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

