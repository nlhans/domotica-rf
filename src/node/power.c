#include "power.h"

#include "devices/mrf49xa.h"
#include "bsp/interrupt.h"
#include "bsp/softI2c.h"
#include "bsp/adc.h"

/*******************************************************************************
 * The system has 4 major blocks which can be operated:
 * - RF
 * - Sensors
 *
 * - "I2C"
 * - ADC
 *
 * For reading the humidity sensor; both sensors and analog need to be enabled
 * For reading the temperature sensor; both sensors and I2C need to be enabled
 * For interfacing witht the EEPROM; only I2C needs to be enabled
 * For transmitting data; only the RF modem has to be enabled
 *
 * All blocks contain their own SysInit(), SysWake() and SysSleep() methods.
 *
 * It is recommended that the use of delay_ms is minimalized and LoseTime() is
 * used instead. This function uses the watchdog and sleep opcode to shutdown.
 * LoseTime() will return prematurely if an interrupt is fired. As of now, only
 * the RF modem can issue an (external) interrupt to wake the PIC. There is no
 * feedback mechanism in place to detect an ISR has woken up the PIC.
 * Further more; interrupts will be delayed because the PIC has to restart
 * it's oscillator module. This takes 5-8us.
 *
 * The board will use ~5.5uA (4.5uA PIC + 0.5uA RF + 0.5uA E2PROM) in deep sleep
 * The RF modem will consume 13mA in RX, and 25mA in TX mode.
 * The sensors module can consume up to 200 + 70 uA.
 * The PIC running at 16MHz consumes approximately 880uA (with I/O).
 *
 * All in all: it is recommended to keep the RF modem operational for as
 * little time as possible.
 * The sensors should be sampled in as little time as possible. Due to long
 * conversion times (Up 150ms @ 10-bit) it may be wise to put the PIC into sleep
 ******************************************************************************/
void Sleepy(uint16_t ms)
{
    uint8_t b = 0;

    while (ms != 0)
    {
        if ((ms & 1) != 0)
        {
            WDTCONbits.WDTPS = b; // 0=~800/sec, 7=7.8/sec 10=once/sec?
            WDTCONbits.SWDTEN = 1;

            asm("sleep");

            WDTCONbits.SWDTEN = 0;
        }
        ms = ms >> 1;
        b++;
    }
}

void PwrI2cInit(void)
{
    SoftI2cInit();

    TRISBbits.TRISB4 = GPIO_OUTPUT;
    TRISBbits.TRISB6 = GPIO_OUTPUT;

    TRISBbits.TRISB5 = GPIO_INPUT; // UART: not used
    PORTBbits.RB5 = 1;
}

void PwrI2cSleep(void)
{
    I2C_SCL = 1;
    I2C_SDA = 1;
    
    TRIS_I2C_SCL = OUTPUT_PIN;
    TRIS_I2C_SDA = OUTPUT_PIN;
}

void PwrI2cWake(void)
{
    
}


void PwrRfInit(void)
{
    TRISAbits.TRISA2 = GPIO_INPUT;
    TRISAbits.TRISA4 = GPIO_OUTPUT;
    TRISAbits.TRISA5 = GPIO_OUTPUT;

    TRISBbits.TRISB7 = GPIO_OUTPUT;

    TRISCbits.TRISC1 = GPIO_OUTPUT;
    TRISCbits.TRISC4 = GPIO_OUTPUT;
    TRISCbits.TRISC6 = GPIO_OUTPUT;
    TRISCbits.TRISC7 = GPIO_OUTPUT;
    TRISCbits.TRISC3 = GPIO_INPUT;
    TRISCbits.TRISC5 = GPIO_INPUT;

    RF_POWER = RF_PWR_ON;

    RF_RES = 0;
    RF_INT = 0;
    RF_FSEL = 0;
    RF_SPI_CS = 1;
    RF_SPI_SCK = 0;
    RF_SPI_SDO = 0;

    WPUAbits.WPUA2 = 1;
    Sleepy(10);

    Mrf49xaInit();
    ExtIntInit();
}

void PwrRfSleep(void)
{
    Mrf49xaShutdown();
    MRF_ENABLE_INT
}

void PwrRfWake(void)
{
    MRF_DISABLE_INT
    Mrf49xaReboot();
}


void PwrSensorInit(void)
{
    TRISCbits.TRISC2 = GPIO_OUTPUT;

    SENSOR_PWR = 0;
}

void PwrSensorSleep(void)
{
    SENSOR_PWR = 0;
}

void PwrSensorWake(void)
{
    SENSOR_PWR = 1;
}


void PwrAdcInit(void)
{
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;

    PORTCbits.RC0 = 1;
    TRISCbits.TRISC0 = 0;
}

void PwrAdcSleep(void)
{
    ANSELC = 0;
    PORTCbits.RC0 = 1;
    TRISCbits.TRISC0 = 0;

    AdcDeinit();
}

void PwrAdcWake(void)
{
    ANSELC = (1<<0);
    TRISCbits.TRISC0 = 1;

    AdcInit();
}
