#include <xc.h>
#include "IOConfig.h"
#include "MRF49XA.h"

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

void Mrf49xaReset()
{
    UI16_t i, j;
    
    RF_RES = 0;
    Mrf49XaDelay(10);
    RF_RES = 1;
    Mrf49XaDelay(10);
    
}

void MRF49XA_Init()
{
    UI16_t i, j;
    Mrf49xaReset();
    
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

    Mrf49XaDelay(5);
    
    SPI_Command(PMCREG | 0x0080);		// turn off Tx, turn on receiver
    SPI_Command(GENCREG | 0x0040);		// enable the FIFO
    SPI_Command(FIFORSTREG);
    SPI_Command(FIFORSTREG | 0x0002);	// enable syncron latch

    RF_FSEL = 1; // Read from SPI registers.
}


void MRF49XA_Send_Packet(TRFData *RFData)
{
    UI08_t i;

    SPI_Command(PMCREG);                                // turn off the transmitter and receiver
    SPI_Command(GENCREG | 0x0080);                      // Enable the Tx register
    SPI_Command(PMCREG |0x0020);                        // turn on tx

    SPI_CS = 0;                                         // chip select low
    
    MRF49XA_WaitOnTx();     SPI_Write16(TXBREG | 0xAA);	// preamble
    MRF49XA_WaitOnTx();     SPI_Write(0xAA);            // preamble
    MRF49XA_WaitOnTx();     SPI_Write(0x2D);            // sync byte 1
    MRF49XA_WaitOnTx();     SPI_Write(0xD4);            // sync byte 2
    MRF49XA_WaitOnTx();     SPI_Write(RFData->index + 1); // Data length
    
    for (i = 0; i < RFData->index; i++)
    {
        MRF49XA_WaitOnTx();
        SPI_Write(RFData->buffer[i]);                   // write payload data
    }

    MRF49XA_WaitOnTx();     SPI_Write(CalChkSum(RFData->buffer, RFData->index));	// checksum
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

UI08_t MRF49XA_Receive_Packet(TRFData *RFData)
{
    SPI_SDO = 0;
    SPI_CS  = 0;					// chip select low

    if(SPI_SDI)                                     // SDI = 1? Data in FIFO
    {
        SPI_CS  = 1;
        RF_FSEL = 0;                            // Read from FIFO instead of SPI registers

        if (RFData->len == 0)                    // Is this our first byte after sync? Then cover length
        {
            RFData->len = SPI_Read();

            RF_FSEL = 1;

            if (RFData->len < 0 || RFData->len > PACKET_SIZE_MAX)
            {
                RFData->len = 0;
                MRF49XA_Reset_Radio();
                return RX_STATE_NONE;
            }
            else
            {
                RFData->index = 0;
                return RX_STATE_DATA;
            }
        }
        else
        {
            RFData->buffer[RFData->index] = SPI_Read();
            RFData->ChkSum = RFData->ChkSum ^ RFData->buffer[RFData->index];
            RF_FSEL = 0;

            RFData->index++;

            if (RFData->index >= RFData->len)
            {
                return RX_STATE_PACKET;
            }
            else
            {
                return RX_STATE_DATA;
            }
        }
    }
    else
    {
        SPI_CS = 1;
        return RX_STATE_NONE;
    }
}

void AddRFData(TRFData *RFData, unsigned char data){
    
    RFData->buffer[RFData->index] = data;
    RFData->index++;
    RFData->ChkSum = RFData->ChkSum ^ data;
}


void InitRFData(TRFData *RFData)
{
	RFData->index       = 0;
	RFData->len         = 0;
	RFData->ChkSum      = 0;
}

unsigned char CalChkSum(unsigned char *buffer, unsigned char len)
{
  unsigned char i;
  unsigned char Received = 0;
  
  for (i=0;i<len;i++) {
  	Received = Received ^ buffer[i];
  }
  return Received;

}

