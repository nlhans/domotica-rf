#include "stddefs.h"
#include "power.h"

#include "bsp/adc.h"

#include "devices/mrf49xa.h"
#include "devices/mcp9800.h"

#include "rfstack/packets.h"

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = SWDTEN       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF         // Low-Voltage Programming Enable (Low-voltage programming enabled)

void main(void)
{
    #warning "Building for PIC16F1508"
    OSCCON = 0b01111000; // 16MHz

    PwrAdcInit();
    PwrSensorInit();
    PwrI2cInit();
    PwrRfInit();

    CfgInit();

    PwrAdcSleep();
    PwrSensorSleep();
    PwrI2cSleep();
    PwrRfSleep();

    while(1)
    {
        // 30.3s:
        //Sleepy(24576);
        Sleepy(1000);
        
        PwrSensorWake();
        PwrI2cWake();

        Mcp9800Start(Mcp9800_12bit);

        PwrAdcWake();
        uint16_t humidity = AdcSample(BSP_HUMIDITY_CHANNEL);
        Sleepy(300);
        uint16_t temperature = Mcp9800Read();

        PwrSensorSleep();
        PwrI2cSleep();

        PwrRfWake();

        if (rfTrcvStatus.txPacket.state != PKT_FREE)
        {
            Mrf49xaNeedsReset();
            Mrf49xaTick();
        }

        //RfSendPowerState();
        do
        {
            Mrf49xaTick();
        }
        while (rfTrcvStatus.txPacket.state != PKT_FREE);

        RfSendSampleWeatherNode(temperature, humidity);
        do
        {
            Mrf49xaTick();
        }
        while (rfTrcvStatus.txPacket.state != PKT_FREE);

        PwrRfSleep();
    }
}
