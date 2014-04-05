#include "stddefs.h"
#include <xc.h>
#include "devices/mrf49xa.h"
#include "rfstack/hal.h"

#include "bsp/spi.h"

mrf49xaStatus_t rfTrcvStatus;

// Write TX byte
void RfTrcvPut(UI08_t byte)
{
    MRF49XACommand(TXBREG | byte);
}

// Read RX byte
UI08_t RfTrcvGet(void)
{
    RF_CS_ACQ();
    
    SPI_Write(0xB0);
    UI08_t b = SPI_Read();

    RF_CS_REL();
    
    return b;
}

// Write word
void MRF49XACommand(UI16_t cmd)
{
    RF_CS_ACQ();

    SPI_Write((cmd & 0xFF00) >> 8);
    SPI_Write((cmd & 0x00FF));

    RF_CS_REL();
}

// Read word
void RfTrcvStatus()
{
    RF_CS_ACQ();

    rfTrcvStatus.byte[0] = SPI_Read();
    rfTrcvStatus.byte[1] = SPI_Read();

    RF_CS_REL();
}

bool_t RfTrcvCarrierPresent()
{
    RfTrcvStatus();
    return rfTrcvStatus.flags.msb.signalPresent;
}

inline UI08_t RfTrcvCrcTick(UI08_t initial, UI08_t data)
{
    return (initial ^ data);
}
void RfTrcvSetup(UI08_t tx)
{
    if (tx)
    {
        MRF49XACommand(PMCREG);                                // turn off the transmitter and receiver
        MRF49XACommand(GENCREG | 0x0080);                      // Enable the Tx register
        MRF49XACommand(PMCREG |0x0020);                        // turn on tx

        // put 1 byte into TX to trigger ISR
        RfTrcvPut(0x55);
    }
    else
    {
        MRF49XACommand(PMCREG);		// turn off tx and rx
        MRF49XACommand(FIFORSTREG);		// reset FIFO
        MRF49XACommand(GENCREG);		// disable FIFO , Tx_latch
        MRF49XACommand(PMCREG | 0x0080);	// turn on receiver
        MRF49XACommand(GENCREG | 0x0040);	// enable the FIFO
        MRF49XACommand(FIFORSTREG | 0x0002);   // FIFO syncron latch re-enable
    }
}

void MRF49XAInit()
{
#ifndef SERVER
    UI08_t i, j;
#endif
    // Reset the chip
    RF_POWER = 1;
    RF_RES = 0;
    RF_INT = 0;
    Nop();
    RF_RES = 1;
    RF_INT = 1;

    RF_FSEL = 1; // Read from SPI registers.

#ifdef SERVER
    RtosTaskDelay(25);
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
    RtosTaskDelay(25);
#else
    for (i = 0; i < 250; i++) for (j = 0; j < 250; j++) asm ("nop");
#endif

    MRF49XACommand(PMCREG | 0x0080);		// turn off Tx, turn on receiver
    MRF49XACommand(GENCREG | 0x0040);		// enable the FIFO
    MRF49XACommand(FIFORSTREG);
    MRF49XACommand(FIFORSTREG | 0x0002);	// enable syncron latch

    RfTrcvSetup(0);

#ifdef SERVER
    // Pull-up IRQ/INT signals
    CNPU2bits.CN21PUE = 1;
    CNPU2bits.CN30PUE = 1;

#else
    WPUAbits.WPUA2 = 1;
#endif
}

//#ifdef PIC16
// 16MHz PIC16
// -> 267kHz SPI clock with loop
// -> ~460kHz SPI clockc without loop
#define SPI_UNROLL_LOOP

UI08_t SPI_Read(void)
{
#ifdef SERVER
    return spiRx1();
#endif
    UI08_t data = 0;
    RF_SPI_SCK = 0;
    RF_SPI_SDO = 0;
#ifdef SPI_UNROLL_LOOP
    #define SPI_RX_TICK(a) do { if (RF_SPI_SDI) data |= (1<<a); \
    RF_SPI_SCK = 1; \
    RF_SPI_SCK = 0; } while (0);

    SPI_RX_TICK(7);
    SPI_RX_TICK(6);
    SPI_RX_TICK(5);
    SPI_RX_TICK(4);
    SPI_RX_TICK(3);
    SPI_RX_TICK(2);
    SPI_RX_TICK(1);
    SPI_RX_TICK(0);
#else
    UI08_t i;

    RF_SPI_SDO = 0;
    RF_SPI_SCK = 0;
    
    for (i = 0; i < 8; i++)
    {
        data = data << 1;

        if (RF_SPI_SDI != 0)
        {
            data |= 0x01;
        }

        RF_SPI_SCK = 1;

        Nop();
        
        RF_SPI_SCK = 0;
    }
#endif
    return data;
}

void SPI_Write(UI08_t data)
{
#ifdef SERVER
    spiTx1(data);
    return;
#endif
    
    RF_SPI_SCK = 0;

#ifdef SPI_UNROLL_LOOP
    #define SPI_TX_TICK(a) do { if ((data & (1<<a)) != 0) RF_SPI_SDO = 1; else RF_SPI_SDO = 0; \
    RF_SPI_SCK = 1; \
    RF_SPI_SCK = 0; } while (0);
    
    SPI_TX_TICK(7);
    SPI_TX_TICK(6);
    SPI_TX_TICK(5);
    SPI_TX_TICK(4);
    SPI_TX_TICK(3);
    SPI_TX_TICK(2);
    SPI_TX_TICK(1);
    SPI_TX_TICK(0);
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