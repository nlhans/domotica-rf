#define MAIN_C

#define COMPILE_ETHERNET

#include "stddefs.h"

#include "tasks/rf_task.h"
#include "tasks/eth_task.h"
#include "rtos/task.h"

#include "bsp/interrupt.h"
#include "bsp/spi.h"
#include "bsp/uart.h"

//const uint16_t humids30c[15] = {65535, 39000, 20000, 9800, 4700, 1310, 770, 440, 250, 170, 105, 72, 50, 36, 25 };

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

// 8CC
// 214

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
    #if defined(__PIC24FJ64GB004__)
    AD1PCFG = 0xFFFF;
    #warning "Building for PIC24FJ64GB004"
    #else
        #if defined (__PIC24FJ64GA004__)
        AD1PCFG = 0xFFFF;
        #warning "Building for PIC24FJ64GA004(sim)"
        #else
        ADPCFG = 0xFFFF; // Ports as digital, not analog
        #warning "Building for dsPIC33FJ128GP804"
        #endif
    #endif

    ETH_CS = 1;
    RF_SPI_CS = 1;
    FLASH_CS1 = 1;
    FLASH_CS2 = 1;

    SysInitGpio();

    RF_POWER = 0;
    SENSOR_PWR = 0;

    // Setup UART1 to ICSP pins
    PPSUnLock;
    iPPSOutput(OUT_PIN_PPS_RP0, OUT_FN_PPS_U1TX);
    iPPSInput(IN_FN_PPS_U1RX, IN_PIN_PPS_RP1);
    PPSLock;

    ExtIntInit();
    
    //spiInit(1);
    spiInit(2);

    RF_POWER = 1;

    UartInit(1, 38400);
    printf("Hello world!\r\n");

    RtosTaskInit();
    
#ifdef COMPILE_ETHERNET
    EthInit();
#endif
    RfInit();
    
    RtosTaskRun();

    //while(1);
    return 0;
}

