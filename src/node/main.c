
#include "stddefs.h"

#include "bsp/adc.h"
#include "bsp/interrupt.h"

#include "rfstack/hal.h"
#include "rfstack/packets.h"

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

bool_t mrf49XaIsr()
{
    Mrf49xaTick();

    return RF_IRQ == 1 ? TRUE : FALSE;
}

void main(void)
{
    #warning "Building for PIC16F1508"
    OSCCON = 0b01111000; // 16MHz
    WPUAbits.WPUA2 = 1;

    SysInitGpio();
    AdcInit();
    ExtIntInit();
    uint8_t i, j;
    RF_RES = 0;
    RF_POWER = 1;
    for (i = 0; i < 250; i++)
    {
        if (i == 125)
            RF_RES = 1;
        for (j = 0; j < 250; j++) asm ("nop");
    }

    RF_FSEL = 1; // Read from SPI registers.
    RF_INT = 1;
    
    Mrf49xaInit();

    while(1)
    {
        
    }

}
