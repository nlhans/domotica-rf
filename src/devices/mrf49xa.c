#include "stddefs.h"
#include <xc.h>
#include "devices/mrf49xa.h"
#include "rtos/task.h"
#include "rfstack/hal.h"

void RfTrcvPut(UI08_t byte)
{
    RF_SPI_CS = 0;
    SPI_Write(TXBREG >> 8);
    SPI_Write(byte);
    RF_SPI_CS = 1;
}
UI08_t RfTrcvGet(void)
{
    RF_FSEL = 0;
    RF_SPI_CS = 0;
    UI08_t b = SPI_Read();
    RF_SPI_CS = 1;
    RF_FSEL = 1;
    return b;
}
UI08_t RfTrcvCrcTick(UI08_t initial, UI08_t data)
{
    return (initial ^ data);
}
void RfTrcvRearm(void)
{
    MRF49XAReset();
}

void MRF49XAInit()
{
#ifndef SERVER
    UI08_t i, j;
#endif
    // Reset the chip
    RF_RES = 0;
    Nop();
    RF_RES = 1;

#ifdef SERVER
    RtosTaskDelay(250); // TODO: Determine good timestamp.
#else
    for (i = 0; i < 250; i++) for (j = 0; j < 250; j++) asm ("nop");
#endif

    MRF49XACommand(FIFORSTREG);
    MRF49XACommand(FIFORSTREG | 0x0002);
    MRF49XACommand(GENCREG);
    MRF49XACommand(AFCCREG);
    MRF49XACommand(CFSREG);
    MRF49XACommand(DRSREG);
    MRF49XACommand(PMCREG);
    MRF49XACommand(RXCREG);
    MRF49XACommand(TXCREG);
    MRF49XACommand(BBFCREG);
    MRF49XACommand(PMCREG | 0x0020);		// turn on tx

#ifdef SERVER
    RtosTaskDelay(250); // TODO: Determine good timestamp.
#else
    for (i = 0; i < 250; i++) for (j = 0; j < 250; j++) asm ("nop");
#endif

    MRF49XACommand(PMCREG | 0x0080);		// turn off Tx, turn on receiver
    MRF49XACommand(GENCREG | 0x0040);		// enable the FIFO
    MRF49XACommand(FIFORSTREG);
    MRF49XACommand(FIFORSTREG | 0x0002);	// enable syncron latch

    RF_FSEL = 1; // Read from SPI registers.

#ifdef SERVER

    CNEN2bits.CN21IE = 1;
    CNEN2bits.CN30IE = 1;

    CNPU2bits.CN21PUE = 1;
    CNPU2bits.CN30PUE = 1;

    IEC1bits.CNIE = 1;
    IFS1bits.CNIF = 0;

#endif
}

void MRF49XAReset()
{
    MRF49XACommand(PMCREG);		// turn off tx and rx
    MRF49XACommand(FIFORSTREG);		// reset FIFO
    MRF49XACommand(GENCREG);		// disable FIFO , Tx_latch
    MRF49XACommand(PMCREG | 0x0080);	// turn on receiver
    MRF49XACommand(GENCREG | 0x0040);	// enable the FIFO
    MRF49XACommand(FIFORSTREG | 0x0002);   // FIFO syncron latch re-enable
}

void MRF49XACommand(UI16_t cmd)
{
    RF_SPI_CS = 0;

    SPI_Write((cmd & 0xFF00) >> 8);
    SPI_Write((cmd & 0x00FF));

    RF_SPI_CS = 1;
}

UI16_t MRF49XAReadStatus()
{
    UI16_t w = 0;

    RF_SPI_CS = 0;
    w = SPI_Read() << 8;
    w |= SPI_Read();
    RF_SPI_CS = 1;

    return w;

}

void __attribute__((interrupt,no_auto_psv)) _CNInterrupt(void)
{
    if (RF_IRQ == 0)
    {
        UI16_t mrf49State = MRF49XAReadStatus();
        RfStatus_t mrf49Status;
        mrf49Status.dataTransferred = 1; // (mrf49State & (1<<15))?1:0;

        RfHalStatemachine(mrf49Status);
    }
    IFS1bits.CNIF = 0;
}
//#ifdef PIC16
// 16MHz PIC16
// -> 267kHz SPI clock with loop
// -> ~460kHz SPI clockc without loop
//#define SPI_UNROLL_LOOP

UI08_t SPI_Read(void)
{
    UI08_t i;
    UI08_t data = 0;

    RF_SPI_SDO = 0;
    RF_SPI_SCK = 0;
    
    for (i = 0; i < 8; i++)
    {
        data = data << 1;

        if (RF_SPI_SDI)
        {
            data |= 0x01;
        }
        else
        {
            data &= 0xFE;
        }

        RF_SPI_SCK = 1;

        Nop();
        
        RF_SPI_SCK = 0;
    }
    return data;
}

void SPI_Write(UI08_t data)
{

    RF_SPI_SCK = 0;

#ifdef SPI_UNROLL_LOOP
    #define SPI_TICK(a) do { if ((data & (1<<a)) != 0) RF_SPI_SDO = 1; else RF_SPI_SDO = 0; \
    RF_SPI_SCK = 1; \
    RF_SPI_SCK = 0; } while (0);
    
    SPI_TICK(7);
    SPI_TICK(6);
    SPI_TICK(5);
    SPI_TICK(4);
    SPI_TICK(3);
    SPI_TICK(2);
    SPI_TICK(1);
    SPI_TICK(0);
#else
    UI08_t i;
    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
        {
            RF_SPI_SDO = 1;
        }
        else
        {
            RF_SPI_SDO = 0;
        }

        RF_SPI_SCK = 1;
        data = data << 1;
        RF_SPI_SCK = 0;
    }
#endif
}
//#endif

/*
void MRF49XA_TxPacket(UI08_t *data, UI08_t size)
{
    UI08_t i, crc = 0;

    MRF49XACommand(PMCREG);                                // turn off the transmitter and receiver
    MRF49XACommand(GENCREG | 0x0080);                      // Enable the Tx register
    MRF49XACommand(PMCREG |0x0020);                        // turn on tx

    RF_SPI_CS = 0;                                         // chip select low

    //MRF49XA_WaitOnTx();     SPI_Write16(TXBREG | 0xAA);	// preamble
    MRF49XA_WaitOnTx();     SPI_Write(TXBREG >> 8); SPI_Write(0xAA);	// preamble
    MRF49XA_WaitOnTx();     SPI_Write(0xAA);            // preamble
    MRF49XA_WaitOnTx();     SPI_Write(0x2D);            // sync byte 1
    MRF49XA_WaitOnTx();     SPI_Write(0xD4);            // sync byte 2
    MRF49XA_WaitOnTx();     SPI_Write(size + 1); // Data length
    
    for (i = 0; i < size; i++)
    {
        MRF49XA_WaitOnTx();
        SPI_Write(data[i]);                   // write payload data
        crc = crc ^ data[i];
    }

    MRF49XA_WaitOnTx();     SPI_Write(crc);	// checksum
    MRF49XA_WaitOnTx();     SPI_Write(0x00);            // write a dummy byte
    MRF49XA_WaitOnTx();     SPI_Write(0x00);            // write a dummy byte
    MRF49XA_WaitOnTx();     SPI_Write(0x00);            // write a dummy byte
    MRF49XA_WaitOnTx();

    RF_SPI_CS = 1;						// end

    MRF49XACommand(FIFORSTREG);                            // FIFO Reset
    MRF49XACommand(PMCREG | 0x0080);                       // turn on receiver
    MRF49XACommand(GENCREG | 0x0040);                      // enable the FIFO
    MRF49XACommand(FIFORSTREG | 0x0002);                   // FIFO syncron latch re-enable

}
 */

UI08_t MRF49XA_RxPacket(UI08_t *data)
{
    static UI08_t inPacket = 0;
    static UI08_t length = 0;
    static UI08_t index = 0;
    static UI08_t crc = 0;
    
    RF_SPI_SDO = 0;
    RF_SPI_CS  = 0;
    Nop();
    return 0;
    if(RF_SPI_SDI)
    {
        RF_SPI_CS  = 1;
        RF_FSEL    = 0;

        if (inPacket == 0)
        {
            length = SPI_Read();

            RF_FSEL = 1;
            
            if (length > PACKET_SIZE_MAX)
            {
                MRF49XAReset();
            }
            else
            {
                inPacket = 1;
                index = 0;
                crc = 0;
            }
            
            return 0;
        }
        else
        {
            data[index] = SPI_Read();
            crc = crc ^ data[index];
            index++;
            
            RF_FSEL = 1;

            if (index >= length)
            {
                inPacket = 0;

                if (length == 0)
                    return 0;
                
                if(crc != data[index])
                    return length | 0x80;
                else
                    return length;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        RF_SPI_CS = 1;
        return 0;
    }
}
