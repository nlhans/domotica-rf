#include "stddefs.h"
#include "bsp/adc.h"
#ifdef ADC16_C
void AdcInit(void)
{
    FVRCON = 0b11100001; // Voltage reference 1.024V

    ADCON2 = 0b00000000;
    ADCON1 = 0b11110000;
    ADCON0 = 0b00000000;

    ADCON0 = 0b00010011;
}

void AdcDeinit(void)
{
    FVRCON = 0; // Voltage reference 1.024V

    ADCON2 = 0;
    ADCON1 = 0;
    ADCON0 = 0;
}

inline uint16_t AdcGetResult(void)
{
    return ((ADRESH << 8) | ADRESL);
}

void AdcGo(void)
{
    ADCON0 |= 1<<1;
}

uint8_t AdcIsBusy(void)
{
    return ((ADCON0 >> 1) & 1);
}

void AdcPinEnable(uint8_t port, uint8_t portNumber)
{
    //
    switch (port)
    {
        case PA:
            ANSELA |= 1<<portNumber;
            TRISA |= 1<<portNumber;
            break;
        case PB:
            ANSELB |= 1<<portNumber;
            TRISB |= 1<<portNumber;
            break;
        case PC:
            ANSELC |= 1<<portNumber;
            TRISC |= 1<<portNumber;
            break;
    }
}

void AdcPinDisable(uint8_t port, uint8_t portNumber)
{
    //
    switch (port)
    {
        case PA:
            ANSELA &= ~(1<<portNumber);
            break;
        case PB:
            ANSELB &= ~(1<<portNumber);
            break;
        case PC:
            ANSELC &= ~(1<<portNumber);
            break;
    }
}

void AdcChSelect(AdcChannel_t channel)
{
    ADCON0 = channel << 2 | 1; // enable ADC
}

uint16_t AdcSample(uint8_t ch)
{
    AdcChSelect(ch);

    // Start 1st conversion
    AdcGo();
    __delay_us(200);            // charge internal capacitor @ 16MHz = 200us.
    while (AdcIsBusy());
    AdcGo();                    // Resample
    while (AdcIsBusy());

    return AdcGetResult();
}
#endif