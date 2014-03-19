#include "stddefs.h"
#ifdef ADC16_C
void AdcInit(void)
{
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;

    FVRCON = 0b11100001; // Voltage reference 1.024V

    ADCON2 = 0b00000000;
    ADCON1 = 0b11110000;
    ADCON0 = 0b00000000;

    ADCON0 = 0b00010011;
}

inline UI16_t AdcGetResult(void)
{
    return ((ADRESH << 8) | ADRESL);
}

void AdcGo(void)
{
    ADCON0 |= 1<<1;
}

UI08_t AdcIsBusy(void)
{
    return ((ADCON0 >> 1) & 1);
}

void AdcPinEnable(UI08_t port, UI08_t portNumber)
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

void AdcPinDisable(UI08_t port, UI08_t portNumber)
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

UI16_t AdcSample(UI08_t ch)
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