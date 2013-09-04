
#define MAIN_C

#include "stddefs.h"
#include "mrf49xa.h"
#include "mcp9800.h"

#include "bsp/adc.h"
#include "bsp/softI2c.h"

const UI16_t humids30c[15] = {65535, 39000, 20000, 9800, 4700, 1310, 770, 440, 250, 170, 105, 72, 50, 36, 25 };
 
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
    AdcPinEnable(BSP_HUMIDITY_ANALOG_PIN);

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
    UI16_t sensor;

    sensor = AdcSample(BSP_HUMIDITY_CHANNEL);
    buffer[0] = ADRESH;
    buffer[1] = ADRESL;
    
    temp = AdcSample(ADC_FVR);
    buffer[2] = ADRESH;
    buffer[3] = ADRESL;

    temp = (AdcSample(ADC_TEMP) - 480) * 100 / 120 - 43;
    buffer[4] = ADRESH;
    buffer[5] = ADRESL;

    // Lock in to 29C.
    temp = 27;

    // Temperature in C
    buffer[6] = temp;

    __delay_ms(120);
    UI16_t temp = Mcp9800Read();
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
int main ( void ){
    UI08_t i, j, k;
    #ifdef PIC24_HW
        #if defined(__PIC24FJ64GB004__)
        AD1PCFG = 0xFFFF;
        #else
        ADPCFG = 0xFFFF; // Ports as digital, not analog
        #endif
    #else
        OSCCON = 0b01111000;

        // ICSP ports.
        //TRISA &= ~(1<<0);
        //TRISA &= ~(1<<1);
        
    #endif

    AdcInit();
    UartInit();
    SoftI2cInit();
    initRFPorts();
    
    RF_POWER = 1;

    SENSOR_PWR = 1;

    Mcp9800Start(Mcp9800_9bit);

    MRF49XA_Init();
    
    Mrf49XaDelay(2);
    Mrf49XaDelay(2);
    
    MRF49XA_Reset_Radio();
#define TRANSMITTER
    while (1)
    {
        #ifdef TRANSMITTER

        AdcConvert();

        MRF49XA_TxPacket(buffer, 10);
        
        for(k=0;k<3;k++)
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

