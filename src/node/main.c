#include "stddefs.h"

#include "bsp/adc.h"
#include "bsp/interrupt.h"

#include "rfstack/hal.h"

void SysInitGpio(void)
{
    SYS_GPIO_INIT_PORTA();
    SYS_GPIO_INIT_PORTB();
    SYS_GPIO_INIT_PORTC();

    // Enable humidity analog function
    //AdcPinEnable(BSP_HUMIDITY_ANALOG_PIN);
}

void main(void)
{
    #warning "Building for PIC16F1508"
    OSCCON = 0b01111000; // 16MHz
    AdcInit();


    SysInitGpio();

    RF_POWER = 0;
    SENSOR_PWR = 0;
    
    ExtIntInit();


    while(1)
    {
        RfHalTickRxTh(&halRxBfTh);
        RfHalTickTxTh(&halTxBfTh);
    }

}