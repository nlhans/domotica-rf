#define MAIN_C

#include "stddefs.h"

#include "bsp/interrupt.h"
#include "bsp/spi.h"
#include "bsp/uart.h"

#include "tasks/rf_task.h"
#include "dbg/dbg_task.h"
#include "rtos/task.h"

void SysInitGpio(void)
{
    SYS_GPIO_INIT_PORTA();
    SYS_GPIO_INIT_PORTB();
    SYS_GPIO_INIT_PORTC();

    // Enable humidity analog function
    //AdcPinEnable(BSP_HUMIDITY_ANALOG_PIN);
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

    ETH_CS = 1;
    RF_SPI_CS = 1;
    FLASH_CS1 = 1;
    FLASH_CS2 = 1;

    SysInitGpio();

    RF_POWER = 0;
    SENSOR_PWR = 0;
    CNPU2bits.CN21PUE = 1;

    // Setup UART1 to ICSP pins
    PPSUnLock;
    iPPSOutput(OUT_PIN_PPS_RP0, OUT_FN_PPS_U1TX);
    iPPSInput(IN_FN_PPS_U1RX, IN_PIN_PPS_RP1);
    PPSLock;

    ExtIntInit();
    spiInit(1);
    UartInit(1, 115200*2);
    printf("Hello world!\r\n");

    // Disable nested ISR
    INTCON1bits.NSTDIS = 1;

    RtosTaskInit();

    RfInit();
    DbgInit();
    
    RtosTaskRun();

    //while(1);
    return 0;
}