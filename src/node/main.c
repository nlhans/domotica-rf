
#define _XTAL_FREQ 4000000

#include "stddefs.h"

#include "bsp/adc.h"
#include "bsp/interrupt.h"

#include "rfstack/hal.h"
#include "rfstack/packets.h"

UI16_t delay = 1000;
volatile UI08_t isr = 0;

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
    do
    {
        RfTrcvStatus();
        isr++;

        if (rfTrcvStatus.flags.msb.fifoTxRx)
        {
            if (rfStatus.inRx ==1 && rfTrcvStatus.flags.lsb.dataQualityOK == 0)
            {
                // Skip RX + bad data
            }
            else
            {
                RfHalStatemachine();
            }
        }
        if (rfTrcvStatus.flags.msb.por)
        {
            RfTrcvSetup(0);
        }

    } while (rfTrcvStatus.flags.msb.por || rfTrcvStatus.flags.msb.fifoTxRx);

    return (RF_IRQ == 1) ? 1 : 0;
}
bool_t mrf49XaIsr2(UI08_t foo)
{
    return TRUE;
}

void main(void)
{
    #warning "Building for PIC16F1508"
    OSCCON = 0b01111000; // 16MHz

    SysInitGpio();
    AdcInit();
    
    ExtIntInit();

    MRF49XAInit();
    RfHalInit();

    while(1)
    {
        if (RF_IRQ == 0) mrf49XaIsr();
        
        RfHalTickRxTh(&halRxBfTh);

        RfPacketsTickTh(&halPkTh);

        RfHalTickTxTh(&halTxBfTh);
        
        RfTrcvStatus();

        delay=1000;
        isr = 0;
        while(delay-- > 0 && isr == 0) Nop();
    }

}
