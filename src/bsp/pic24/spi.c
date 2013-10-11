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

            SPI1CON1 = 0b0000000100111010;
            SPI1CON2 = 0b0;
            SPI1STAT |= 0x1 << 15;
            break;
        case 2:
            TRISB &= ~(1<<14);   // sck
            TRISC &= ~(1<<0);    // mosi
            TRISC |= (1<<2);     // miso
            
            TRISA &= ~(1<<0);   // CS1
            TRISA &= ~(1<<7);   // CS2

            PPSUnLock;
            iPPSOutput(OUT_PIN_PPS_RP14, OUT_FN_PPS_SCK2OUT);   // OUT_FN_PPS_NULL
            iPPSOutput(OUT_PIN_PPS_RP16, OUT_FN_PPS_SDO2);
            iPPSInput(IN_FN_PPS_SDI2, IN_PIN_PPS_RP18);
            PPSLock;

            IFS2bits.SPI2IF = 0;
            IEC2bits.SPI2IE = 0;

            SPI2CON1 = 0b0000000100111010;
            SPI2CON2 = 0b0;
            SPI2STAT |= 0x1 << 15;
            break;
    }
}

void spiTxByte(UI08_t port, UI08_t byte)
{
    volatile UI16_t aha = 0;
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
    UI08_t rxB=0;
    UI16_t i = 0;
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
    //
}

/********* SQI FUNCTIONS FOR ST26 FLASH *********/
void sqiEnable(UI08_t port)
{
    spiDeinit(port);
}
void sqiDisable(UI08_t port)
{
    spiInit(port);
    LATB |= 1<<13;
    LATC |= 1<<1;
}
void sqiMode(UI08_t port, bool_t isOutput)
{
    switch(port)
    {
        case 2:
            // Set data IO to output
            if (isOutput)
            {
                TRISC &= ~((1<<0) | (1<<1) | (1<<2));
                TRISB &= ~(1<<13);
            }
            else
            {
                TRISC |= (1<<0) | (1<<1) | (1<<2);
                TRISB |= 1<<13;
            }
            break;

    }
}

#define sqiBitChk(byte, bit) ((byte & (1<<bit)) != 0)
void sqiTxByte(UI08_t port, UI08_t byte)
{
    sqiMode(port, TRUE);
    
    switch(port)
    {
        case 2:
                // b0 = rc0
                // b2 = rc1
                // b1 = rc2
                // b3 = rb13
                // sck = rb14
            PORTB &= ~(1<<14);
            if (sqiBitChk(byte, 4)) LATC |= 1<<0; else LATC &= ~(1<<0);
            if (sqiBitChk(byte, 5)) LATC |= 1<<2; else LATC &= ~(1<<2);
            if (sqiBitChk(byte, 6)) LATC |= 1<<1; else LATC &= ~(1<<1);
            if (sqiBitChk(byte, 7)) LATB |= 1<<13; else LATB &= ~(1<<13);
            PORTB |= (1<<14);
            asm("nop");
            PORTB &= ~(1<<14);
            if (sqiBitChk(byte, 0)) LATC |= 1<<0; else LATC &= ~(1<<0);
            if (sqiBitChk(byte, 1)) LATC |= 1<<2; else LATC &= ~(1<<2);
            if (sqiBitChk(byte, 2)) LATC |= 1<<1; else LATC &= ~(1<<1);
            if (sqiBitChk(byte, 3)) LATB |= 1<<13; else LATB &= ~(1<<13);
            PORTB |= (1<<14);
            asm("nop");
            PORTB &= ~(1<<14);
            break;
    }
    
}
UI08_t sqiRxByte(UI08_t port)
{
    UI08_t byte = 0;
    
    sqiMode(port, FALSE);

    switch(port)
    {
        case 2:
            PORTB &= ~(1<<14);
            PORTB |= (1<<14);

            if (sqiBitChk(PORTC, 0)) byte |= 1 << 4; // check bit 0
            if (sqiBitChk(PORTC, 2)) byte |= 1 << 5; // check bit 0
            if (sqiBitChk(PORTC, 1)) byte |= 1 << 6; // check bit 0
            if (sqiBitChk(PORTB, 13)) byte |= 1 << 7; // check bit 0

            PORTB &= ~(1<<14);
            PORTB |= (1<<14);

            if (sqiBitChk(PORTC, 0)) byte |= 1 << 0; // check bit 0
            if (sqiBitChk(PORTC, 2)) byte |= 1 << 1; // check bit 0
            if (sqiBitChk(PORTC, 1)) byte |= 1 << 2; // check bit 0
            if (sqiBitChk(PORTB, 13)) byte |= 1 << 3; // check bit 0


            PORTB &= ~(1<<14);
            break;
    }
    
    return byte;
}

void sqiTxRxBytes(UI08_t port, UI08_t *txBf, UI08_t *rxBf, UI16_t size)
{
    UI16_t i = 0;
    if (txBf != NULL)
    {
        while (size > i)
        {
            sqiTxByte(port, txBf[i]);
            i++;
        }
    }
    else if (rxBf != NULL)
    {
        while (size > i)
        {
            rxBf[i] = sqiRxByte(port);
            i++;
        }
    }
    else
    {
        // ERROR
    }
}
