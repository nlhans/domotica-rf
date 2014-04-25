#include "bsp/uart.h"
void UartInit(uint8_t port, const uint32_t baud)
{
    switch (port)
    {
        case 1:
            U1MODE = 0;
            U1STA  = (1 << 10);
            U1BRG  = F_OSC_DIV_2/16/baud - 1;
            U1MODE = (1 << 15);
            break;

        default:
            break;
    }
}

void UartTxByte(uint8_t port, uint8_t byte)
{
    switch (port)
    {
        case 1:
            while(U1STAbits.UTXBF == 1);
            U1TXREG = byte;
            break;

        default:
            break;
    }
}

void UartTxStr(uint8_t port, const char * str)
{
    switch (port)
    {
        case 1:
            while(*str != '\0')
            {
                U1TXREG = *str;
                str++;
                while (U1STAbits.UTXBF == 1);
            }
            break;

        default:
            break;
    }
}

void UartTxArr(uint8_t port, unsigned char * bf, uint16_t size)
{
    uint16_t i = 0;

    switch (port)
    {
        case 1:
            while(size > i)
            {
                U1TXREG = bf[i];
                i++;
                while (U1STAbits.UTXBF == 1);
            }
            break;

        default:
            break;
    }
}

#ifdef dsPIC33
// PIC24 doesn't support DMA, unfortunately.
#include "bsp/dma.h"
uint8_t uartToDma[BSP_UART_COUNT];

void UartTxDma(uint8_t port, uint8_t dmaCh, unsigned char * bf, uint16_t size)
{
    uint16_t* hwReg;
    if (port == 1)          hwReg = &U1TXREG;
    else if (port == 2)     hwReg = &U2TXREG;
    else return;
    
    DmaSetup(dmaCh, bf, NULL, hwReg, 0, 0);
    DmaTransfer(dmaCh, size);

    uartToDma[port] = dmaCh;
}

bool_t UartTxDmaStatus(uint8_t port)
{
    return DmaIsBusy(uartToDma[port]);
}
#endif