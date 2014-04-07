
#include "stddefs.h"

#include "bsp/adc.h"
#include "bsp/interrupt.h"

#include "rfstack/hal.h"
#include "rfstack/packets.h"

UI08_t dl1, dl2;
volatile UI08_t isr = 0;
UI08_t worried = 0;

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
volatile UI08_t rfPkResets = 0;

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
        
        // Abort & reset
        if (rfTrcvStatus.flags.msb.por || (rfTrcvStatus.flags.msb.signalPresent && rfTrcvStatus.flags.msb.overflow))
        {
            RfTrcvSetup(0);
            rfPkResets++;
        }
        
    } while (rfTrcvStatus.flags.msb.por || rfTrcvStatus.flags.msb.fifoTxRx);

    return (RF_IRQ == 1) ? 1 : 0;
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
        if (rfTrcvStatus.flags.lsb.clockLock == 0 && rfStatus.inRx == 1)
            worried++;

        dl1 = 33;
        isr = 0;
        while (dl1 > 0 && isr == 0)
        {
            dl2 = 0xFF;
            while (dl2 != 1 && isr == 0) dl2--;
            dl1--;
        }

        if (isr == 0)
        {
            RfTrcvStatus();
            if (worried ==  1 && rfTrcvStatus.flags.lsb.clockLock == 0 && rfStatus.inRx == 1)
            {
                RfTrcvSetup(0);
            }
            else if (worried == 5)
            {
                if (rfTrcvStatus.byte[0] == 0 || rfTrcvStatus.byte[0] == 0x02)
                {
                    // Re-boot chip
                    RF_RES = 0;
                    Nop();

                    MRF49XAInit();
                }
            }
        }
        else
        {
            worried = 0;
        }
    }

}
