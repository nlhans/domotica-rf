#include "bsp/spi.h"

void spiDeinit(UI08_t port)
{
    switch(port)
    {
        case 1:
            PPSUnLock;
            iPPSOutput(OUT_PIN_PPS_RP7, OUT_FN_PPS_NULL);
            iPPSOutput(OUT_PIN_PPS_RP8, OUT_FN_PPS_NULL);
            iPPSInput(IN_FN_PPS_SDI1, IN_PIN_PPS_RP0);
            PPSLock;

            IFS0bits.SPI1IF = 0;
            IEC0bits.SPI1IE = 0;

            SPI1STAT = 0;
            break;
        case 2:
            PPSUnLock;
            iPPSOutput(OUT_PIN_PPS_RP14, OUT_FN_PPS_NULL);   //
            iPPSOutput(OUT_PIN_PPS_RP16, OUT_FN_PPS_NULL);
            iPPSInput(IN_FN_PPS_SDI2, IN_PIN_PPS_RP0);
            PPSLock;

            IFS2bits.SPI2IF = 0;
            IEC2bits.SPI2IE = 0;
            
            SPI2STAT = 0;
            break;
    }
}

void spiInit(UI08_t port)
{
    switch(port)
    {
        case 1:
            TRISC |= (1<<4);   // miso
            TRISB &= ~(1<<8);   // mosi
            TRISB &= ~(1<<7);   // sck
            TRISC &= ~(1<<8);   // Eth CS
            TRISC &= ~(1<<7);   // Eth reset

            PPSUnLock;
            iPPSOutput(OUT_PIN_PPS_RP7, OUT_FN_PPS_SCK1OUT);
            iPPSOutput(OUT_PIN_PPS_RP8, OUT_FN_PPS_SDO1);
            iPPSInput(IN_FN_PPS_SDI1, IN_PIN_PPS_RP20);
            PPSLock;

            IFS0bits.SPI1IF = 0;
            IEC0bits.SPI1IE = 0;

            SPI1CON1 = 0b0000000100111011;
            //SPI1CON2 = 0b0;
            SPI1STAT |= 0x1 << 15;
            break;
        case 2:
            TRISB &= ~(1<<14);   // sck
            TRISC &= ~(1<<0);    // mosi
            TRISC |= (1<<2);     // miso

            PORTAbits.RA0 = 1;
            PORTAbits.RA7 = 1;
            TRISA &= ~(1<<0);   // CS1
            TRISA &= ~(1<<7);   // CS2

            PPSUnLock;
            iPPSOutput(OUT_PIN_PPS_RP14, OUT_FN_PPS_SCK2OUT);   // OUT_FN_PPS_NULL
            iPPSOutput(OUT_PIN_PPS_RP16, OUT_FN_PPS_SDO2);
            iPPSInput(IN_FN_PPS_SDI2, IN_PIN_PPS_RP18);
            PPSLock;

            IFS2bits.SPI2IF = 0;
            IEC2bits.SPI2IE = 0;

            SPI2STAT = 0;
            SPI2CON1 = 0;
            //SPI2CON1 = (1<<5) | (1<<8); // master SPI, output active->idle clock
            //SPI2CON1 |= 0b11011;

            SPI2CON1 = 0b0000000100111011;
            SPI2CON2 = 0b0;
            SPI2STAT |= 0x1 << 15;
            break;
    }
}

void spiTxByte(UI08_t port, UI08_t byte)
{
    UI16_t aha = 0;
    switch(port)
    {
        case 1:
            SPI1BUF = byte;
            while(SPI1STATbits.SPIRBF == 0);
            aha = SPI1BUF;
            break;
        case 2:
            SPI2BUF = byte;
            while(SPI2STATbits.SPIRBF == 0);
            aha = SPI2BUF;
            break;
    }
}
UI08_t spiRxByte(UI08_t port)
{
    switch(port)
    {
        case 1:
            SPI1BUF = 0;
            while(SPI1STATbits.SPIRBF == 0);
            return SPI1BUF;
        case 2:
            SPI2BUF = 0;
            while(SPI2STATbits.SPIRBF == 0);
            return SPI2BUF;
        default:
            return 0x5A;
    }
}
UI08_t spiTxRxByte(UI08_t port, UI08_t byte)
{
    switch(port)
    {
        case 1:
            SPI1BUF = byte;
            while(SPI1STATbits.SPIRBF == 0);
            return SPI1BUF;

        case 2:
            SPI2BUF = byte;
            while(SPI2STATbits.SPIRBF == 0);
            return SPI2BUF;

        default:
            return 0xFF;
    }
}
void spiTxRxBytes(UI08_t port, UI08_t *dataTx, UI08_t *dataRx, UI16_t size)
{
    UI08_t rxB = 0;
    UI16_t i = 0;
    if (dataRx == NULL || 0)
    {
        while (size > i)
        {
            spiTxByte(port, *dataTx);
            dataTx++;
            i++;
        }
    }
    else
    {
        while(size> i)
        {
            if(dataTx == NULL)
                rxB = spiTxRxByte(port, 0x00);
            else
                rxB = spiTxRxByte(port, dataTx[i]);

            if(dataRx != NULL)
                dataRx[i] = rxB;

            i++;
        }
    }
    //
}
