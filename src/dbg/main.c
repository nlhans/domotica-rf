#define MAIN_C

#include "stddefs.h"

#include "tasks/rf_task.h"
#include "rtos/task.h"

#include "bsp/interrupt.h"
#include "bsp/spi.h"

void SysInitGpio(void)
{
    SYS_GPIO_INIT_PORTA();
    SYS_GPIO_INIT_PORTB();
    SYS_GPIO_INIT_PORTC();

    // Enable humidity analog function
    //AdcPinEnable(BSP_HUMIDITY_ANALOG_PIN);
}

void UartTxStr(char * str)
{
    while(*str != '\0')
    {
        U1TXREG = *str;
        while ((U1STA & (1<<9)) != 0);
    }
}

void UartTxByte(char c)
{
    while(U1STAbits.UTXBF == 1);
    U1TXREG = c;
}

void UartInit()
{
#ifdef PIC24_HW
    U1MODE = 0;

    PPSUnLock;
    iPPSOutput(OUT_PIN_PPS_RP0, OUT_FN_PPS_U1TX);
    iPPSInput(IN_FN_PPS_U1RX, IN_PIN_PPS_RP1);
    PPSLock;

    U1STA  = (1 << 10);
    U1BRG  = F_OSC_DIV_2/16/38400 - 1;
    U1MODE = (1 << 15); // high baud
#endif
}


#define TRAP_ISR __attribute__((naked, no_auto_psv,__interrupt__))
int StkAddrLo;  // order matters
int StkAddrHi;
char TrapMsgBuf[24];

void TRAP_ISR _AddressError(void)
{
    asm("mov #_StkAddrHi,w1\n\tpop [w1--]\n\tpop [w1++]\n\tpush [w1--]\n\tpush [w1++]");
    // TODO: Write StkAddrLo & Hi to EEPROM
    while(1);
}
void TRAP_ISR _StackError(void)
{
    while(1);
}
void TRAP_ISR _MathError(void)
{
    while(1);
}

int main(void)
{
    ADPCFG = 0xFFFF; // Ports as digital, not analog
    #warning "Building for dsPIC33FJ128GP804"

    RF_SPI_CS = 1;

    SysInitGpio();

    RF_POWER = 0;
    SENSOR_PWR = 0;

    ExtIntInit();
    spiInit(1);
    UartInit();
    printf("Hello world!\r\n");

    // Interrupts..
    INTCON1bits.NSTDIS = 1;

    RtosTaskInit();

    RfInit();

    RtosTaskRun();

    //while(1);
    return 0;
}