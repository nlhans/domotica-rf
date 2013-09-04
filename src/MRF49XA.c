#include <xc.h>
#include "mrf49xa.h"


UI08_t SPI_Read(void)
{
    UI08_t i;
    UI08_t data = 0;

    SPI_SDO = 0;
    SPI_SCK = 0;
    
    for (i = 0; i < 8; i++)
    {
        data = data << 1;

        if (SPI_SDI)
        {
            data |= 0x01;
        }
        else
        {
            data &= 0xFE;
        }

        SPI_SCK = 1;

        Nop();
        
        SPI_SCK = 0;
    }
    return data;
}

void SPI_Write(UI08_t data)
{
    UI08_t i;

    SPI_SDO = 0;
    SPI_SCK = 0;
    
    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
        {
            SPI_SDO = 1;
        }
        else
        {
            SPI_SDO = 0;
        }

        SPI_SCK = 1;
        Nop();

        SPI_SCK = 0;

        data = data << 1;
    }

    SPI_SDO = 0;

}

void SPI_Command(UI16_t cmd)
{
    SPI_CS = 0;

    SPI_Write((cmd & 0xFF00) >> 8);
    SPI_Write((cmd & 0x00FF));

    SPI_CS = 1;
}

void SPI_Write16(UI16_t data16)
{
    SPI_Write((data16 & 0xFF00) >> 8);
    SPI_Write((data16 & 0x00FF));
}

void MRF49XA_Reset_Radio()
{
    SPI_Command(PMCREG);		// turn off tx and rx
    SPI_Command(FIFORSTREG);		// reset FIFO
    SPI_Command(GENCREG);		// disable FIFO , Tx_latch
    SPI_Command(PMCREG | 0x0080);	// turn on receiver
    SPI_Command(GENCREG | 0x0040);	// enable the FIFO
    SPI_Command(FIFORSTREG | 0x0002);   // FIFO syncron latch re-enable
}

void MRF49XA_Init()
{
    UI08_t i, j;
    
    // Reset the chip
    RF_RES = 0;
    Nop();
    RF_RES = 1;

    Mrf49XaDelay(2);
    
    SPI_Command(FIFORSTREG);
    SPI_Command(FIFORSTREG | 0x0002);
    SPI_Command(GENCREG);
    SPI_Command(AFCCREG);
    SPI_Command(CFSREG);
    SPI_Command(DRSREG);
    SPI_Command(PMCREG);
    SPI_Command(RXCREG);
    SPI_Command(TXCREG);
    SPI_Command(BBFCREG);
    SPI_Command(PMCREG | 0x0020);		// turn on tx

    Mrf49XaDelay(2);
    
    SPI_Command(PMCREG | 0x0080);		// turn off Tx, turn on receiver
    SPI_Command(GENCREG | 0x0040);		// enable the FIFO
    SPI_Command(FIFORSTREG);
    SPI_Command(FIFORSTREG | 0x0002);	// enable syncron latch

    RF_FSEL = 1; // Read from SPI registers.
}

void MRF49XA_TxPacket(UI08_t *data, UI08_t size)
{
    UI08_t i, crc = 0;

    SPI_Command(PMCREG);                                // turn off the transmitter and receiver
    SPI_Command(GENCREG | 0x0080);                      // Enable the Tx register
    SPI_Command(PMCREG |0x0020);                        // turn on tx

    SPI_CS = 0;                                         // chip select low
    
    MRF49XA_WaitOnTx();     SPI_Write16(TXBREG | 0xAA);	// preamble
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

    SPI_CS = 1;						// end

    SPI_Command(FIFORSTREG);                            // FIFO Reset
    SPI_Command(PMCREG | 0x0080);                       // turn on receiver
    SPI_Command(GENCREG | 0x0040);                      // enable the FIFO
    SPI_Command(FIFORSTREG | 0x0002);                   // FIFO syncron latch re-enable

}

UI08_t MRF49XA_RxPacket(UI08_t *data)
{
    static UI08_t inPacket = 0;
    static UI08_t length = 0;
    static UI08_t index = 0;
    static UI08_t crc = 0;
    
    SPI_SDO = 0;
    SPI_CS  = 0;
    Nop();
    if(SPI_SDI)
    {
        SPI_CS  = 1;
        RF_FSEL = 0;

        if (inPacket == 0)
        {
            length = SPI_Read();

            RF_FSEL = 1;

            if (length > PACKET_SIZE_MAX)
            {
                MRF49XA_Reset_Radio();
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
        SPI_CS = 1;
        return 0;
    }
}
