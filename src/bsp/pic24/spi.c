#include "bsp/spi.h"

void spiInit(UI08_t port)
{
    switch(port)
    {
        case 1:
            PPSUnLock;
#ifdef dsPIC33
            iPPSOutput(OUT_PIN_PPS_RP7, OUT_FN_PPS_SCK1);
#else
            iPPSOutput(OUT_PIN_PPS_RP7, OUT_FN_PPS_SCK1OUT);
#endif
            iPPSOutput(OUT_PIN_PPS_RP8, OUT_FN_PPS_SDO1);
            iPPSInput(IN_FN_PPS_SDI1, IN_PIN_PPS_RP20);
            PPSLock;

            IFS0bits.SPI1IF = 0;
            IEC0bits.SPI1IE = 0;

            SPI1STAT = 0;
            SPI1CON1 = 0;
            SPI1CON2 = 0;
            
            SPI1CON1 = 0b0000000100111010;
            
            SPI1STAT |= 0x1 << 15;
            break;
        case 2:
            PPSUnLock;
#ifdef dsPIC33
#warning "SPI2 sck pin not good?"
            iPPSOutput(OUT_PIN_PPS_RP14, OUT_FN_PPS_SCK2);
#else
            iPPSOutput(OUT_PIN_PPS_RP14, OUT_FN_PPS_SCK2OUT);
#endif
            iPPSOutput(OUT_PIN_PPS_RP16, OUT_FN_PPS_SDO2);
            iPPSInput(IN_FN_PPS_SDI2, IN_PIN_PPS_RP18);
            PPSLock;

            IFS2bits.SPI2IF = 0;
            IEC2bits.SPI2IE = 0;

            SPI2STAT = 0;
            SPI2CON1 = 0;
            SPI2CON2 = 0;

            SPI2CON1 = 0b0000000100111011;
            
            SPI2STAT |= 0x1 << 15;
            break;
    }
}

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

bool_t spiBusy1()
{
    return (SPI1STATbits.SPIRBF == 0);
}
volatile UI16_t spiDummy;

void spiTx1(UI08_t byte)
{
    SPI1BUF = byte;
    while(SPI1STATbits.SPIRBF == 0);
    spiDummy = SPI1BUF;
}
void spiTx2(UI08_t byte)
{
    SPI2BUF = byte;
    while(SPI2STATbits.SPIRBF == 0);
    spiDummy = SPI2BUF;

    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
}

UI08_t spiRx1()
{
    SPI1BUF = 0;
    while(SPI1STATbits.SPIRBF == 0);
    return SPI1BUF;
}
UI08_t spiRx2()
{
    SPI2BUF = 0;
    while(SPI2STATbits.SPIRBF == 0);

    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    
    return SPI2BUF;
}

UI08_t spiTxRx1(UI08_t byte)
{
    SPI1BUF = byte;
    while(SPI1STATbits.SPIRBF == 0);
    return SPI1BUF;
}
UI08_t spiTxRx2(UI08_t byte)
{
    SPI2BUF = byte;
    while(SPI2STATbits.SPIRBF == 0);
    return SPI2BUF;
}

#ifndef spiTxByte
void spiTxByte(UI08_t port, UI08_t byte)
{
    switch(port)
    {
        case 1:
            spiTx1(byte);
            break;
        case 2:
            spiTx2(byte);
            break;
    }
}
#endif

#ifndef spiRxByte
UI08_t spiRxByte(UI08_t port)
{
    switch(port)
    {
        case 1:
            spiRx1();
            break;
        case 2:
            spiRx2();
        default:
            return 0x5A;
    }
}
#endif

#ifndef spiTxRxByte
UI08_t spiTxRxByte(UI08_t port, UI08_t byte)
{
    switch(port)
    {
        case 1:
            return spiTxRx1(byte);
        case 2:
            return spiTxRx2(byte);

        default:
            return 0;
    }
}
#endif
void spiTxRxBytes(UI08_t port, UI08_t *dataTx, UI08_t *dataRx, UI16_t size)
{
    UI16_t i = 0;
    if (dataRx == NULL)
    {
        while (size > 0)
        {
            spiTxByte(port, *dataTx);
            dataTx++;
            size--;
        }
    }
    else if (dataTx == NULL)
    {
        while (size > 0)
        {
            *dataRx = spiRxByte(port);
            dataRx++;
            size--;
        }
    }
    else
    {
        while(size> i)
        {
            dataRx[i] = spiTxRxByte(port, dataTx[i]);
            i++;
        }
    }
    //
}
