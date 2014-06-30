
#include "stddefs.h"

#include "bsp/adc.h"
#include "bsp/interrupt.h"
#include "bsp/softI2c.h"

#include "rfstack/packets.h"

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
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
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

void SysInitGpio(void)
{
    SYS_GPIO_INIT_PORTA();
    SYS_GPIO_INIT_PORTB();
    SYS_GPIO_INIT_PORTC();

    RF_POWER = 0;
    SENSOR_PWR = 0;

    // Enable humidity analog function
    //AdcPinEnable(BSP_HUMIDITY_ANALOG_PIN);
}
#include "devices/24aa64.h"
void main(void)
{
    #warning "Building for PIC16F1508"
    OSCCON = 0b01111000; // 16MHz
    WPUAbits.WPUA2 = 1;

    SysInitGpio();
    SoftI2cInit();
    AdcInit();
    ExtIntInit();

    /* Eeprom test program
char bf[16];
    uint8_t i = 0;
    for(i=0;i<16;i++)
        bf[i] = 0x55-i;
    eepromTxBytes(0, bf, 16);
    for(i=0;i<16;i++)
        bf[i] = 0;
    __delay_ms(5);
    eepromRxBytes(0, bf, 16);

    for(i=0;i<16;i++)
        if ((0x55-i) != bf[i])
            while(1);

            while(1);
*/
            
    Mrf49xaInit();

    uint8_t k = 1;
    
    while(1)
    {
        Mrf49xaTick();
        if (k)
        {
            RfSendPowerState();
            k = 0;
        }
    }


}
