#include "bsp/dma.h"

#define NR_OF_DMA_CHANNELS 8

#if NR_OF_DMA_CHANNELS < 8
uint8_t dmaBusy = 0;
#else
    #if NR_OF_DMA_CHANNELS < 16
        uint16_t dmaBusy = 0;
#else
        uint32_t dmaBusy =0 ;
#endif
#endif
DmaTransferCompleteHandler_t dmaHandlers[NR_OF_DMA_CHANNELS];

void DmaDummy(uint8_t ch) {}

void DmaInit(void)
{
    uint8_t i = 0;
    for (i = 0; i < NR_OF_DMA_CHANNELS; i++)
        dmaHandlers[i] = DmaDummy;
}

void DmaSetup(uint8_t ch, uint16_t bfA, uint16_t bfB, uint16_t* hwReg, uint8_t direction, uint8_t options, uint8_t req)
{
    switch (ch)
    {
        case 1:
            DMA1CON = 0;

            DMA1CONbits.CHEN = 0;
            DMA1CONbits.SIZE = 1; // byte by default
            DMA1CONbits.DIR = direction;
            DMA1CONbits.HALF = 0;
            DMA1CONbits.NULLW = 0; // Null write, for SPI.
            DMA1CONbits.AMODE = 0;
            DMA1CONbits.MODE = 1;
            DMA1REQ = req;

            DMA1STA = (uint16_t)bfA;
            DMA1STB = (uint16_t)bfB;

            DMA1PAD = (uint16_t)hwReg;
            DMA1CNT = 0; // set in transfer

            IFS0bits.DMA1IF = 0;
            IEC0bits.DMA1IE = 1;
            break;
            
    }

    dmaBusy &= ~(1<<ch);

}

void DmaIrqCallback(uint8_t ch, DmaTransferCompleteHandler_t handler)
{
    if (ch < sizeof(dmaHandlers))
        dmaHandlers[ch] = handler;
}

bool_t DmaIsBusy(uint8_t ch)
{
    return ((dmaBusy >> ch) & 0x1);
}

void DmaTransfer(uint8_t ch, uint16_t size)
{
    switch(ch)
    {
        case 1:
            DMA1CNT = size;
            DMA1CONbits.CHEN = 1;
            break;
            
    }
    dmaBusy |= 1<<ch;
}

// Interrupts for completion of each DMA
void __attribute__((__interrupt__,no_auto_psv)) _DMA1Interrupt(void)
{
    IFS0bits.DMA1IF = 0;
    IEC0bits.DMA1IE = 0;
    DMA1CONbits.CHEN = 0;
    
    dmaHandlers[1](1);
}