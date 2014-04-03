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

UI16_t mrfStat;
UI16_t mrf49State;

bool_t mrf49XaIsr()
{
    do
    {
        mrfStat = mrf49State;
        mrf49State = MRF49XAReadStatus();

        if ((mrf49State & (1<<15)) != 0)
        {
            if (rfStatus.inRx ==1 && (mrf49State & (1<<7)) == 0)
            {
            }
            else
            {
                RfHalStatemachine();
            }
        }
        else if((mrf49State & (1<<14)) != 0)
        {
            MRF49XAReset();
        }

    } while ((mrf49State & 0xC000) != 0);

    return (RF_IRQ == 1)?1:0;
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
    RfHalInit();

    while(1)
    {
        RfHalTickRxTh(&halRxBfTh);
        RfHalTickTxTh(&halTxBfTh);

        RfPacketsTickTh(&halPkTh);
    }

}
