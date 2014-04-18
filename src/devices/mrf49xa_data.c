#include "devices/mrf49xa.h"

// Serve MRf49XA chipset when requires attention.
bool_t Mrf49xaServe(void)
{
    uint8_t data;
#ifdef MRF49XA_POWER_SWITCH
    if (rfTrcvStatus.state == POWERED_OFF)
        return;
#endif

    Mrf49RxSts();
    // Power-on-Reset
    if (mrf49Status.flags.msb.por == 1)
    {
        // TODO: Software reset?
    }

    // TXOWRXOF (RX overrun / TX underrun)
    if (mrf49Status.flags.msb.overflow == 1)
    {
        switch(rfTrcvStatus.state)
        {
            case RECV_IDLE:
            case RECV_DATA:
            case RECV_TIMEOUT:

                // Clear fifo data
                data = Mrf49RxByte();
                data = Mrf49RxByte();

                // Reset HW & SW rx
                Mrf49xaModeRx();

                // TODO: Wait until end of this packet burst is done.

                break;

            case TX_PACKET:
                // According to the datasheet, fifoTxRx is also always set.
                // So we don't have to do anything, as after this the
                // data-statemachine will run.
                break;
        }
    }

    // TODO: Logic external interrupt
    // This is probably never going to be used.

    // TODO: Low battery threshold detect
    // The system has it's own battery monitor.

    // TXRXFIFO flag raised
    if (mrf49Status.flags.msb.fifoTxRx == 1)
    {
        // Depending on the driver status.
        switch (rfTrcvStatus.state)
        {
            case RECV_IDLE:
                data = Mrf49RxByte();

                // Truncate data if quality is bad
                // Reset radio & wait for sync byte. Current pattern is rubbish data.
                if (mrf49Status.flags.lsb.dataQualityOK == 0)
                {
                    Mrf49xaModeRx();
                    break;
                }

                if (rfTrcvStatus.rxPacket[0].state == PKT_FREE) rfTrcvStatus.hwRx = &(rfTrcvStatus.rxPacket[0]);
                else if (rfTrcvStatus.rxPacket[1].state == PKT_FREE) rfTrcvStatus.hwRx = &(rfTrcvStatus.rxPacket[1]);
                else
                {
                    // Error, no space in RX buffers.
                    // Reset radio. Drop this packet.
                    Mrf49xaModeRx();
                    break;
                }
                packetRx->packet.size = data;
                packetRx->crc = 0;
                packetRx->state = PKT_HW_BUSY_RX;

                rfTrcvStatus.state = RECV_DATA;
                rfTrcvStatus.hwByte = 1;

                break;

            case RECV_DATA:

                data = Mrf49RxByte();

                // Truncate data if quality is bad
                // Reset radio & wait for sync byte. Current pattern is rubbish data.
                if (mrf49Status.flags.lsb.dataQualityOK == 0)
                {
                    packetRx->state = PKT_HW_READY_RX;
                    Mrf49xaModeRx();
                    break;
                }

                if (rfTrcvStatus.hwByte == packetRx->packet.size)
                {
                    packetRx->crc = data;

                    // TODO: Check CRC
                    // TODO: Check node ID (broadcast/myself)
                    packetRx->state = PKT_HW_READY_RX;

                    // Reset modem
                    Mrf49xaModeRx();

                    // flag scope
                    SENSOR_PWR = 1;
                    SENSOR_PWR = 0;

                }
                else
                {
                    packetRx->raw[rfTrcvStatus.hwByte++] = data;
                }

                break;

            case TX_PACKET:
                rfTrcvStatus.hwByte++;

                switch (rfTrcvStatus.hwByte)
                {
                    case 100:
                        Mrf49TxByte(RF_NETWORKID1);
                        break;

                    case 101:
                        Mrf49TxByte(RF_NETWORKID2);
                        rfTrcvStatus.hwByte = -1;
                        break;

                        // 4..packet size
                    default:
                        Mrf49TxByte(packetTx.raw[rfTrcvStatus.hwByte]);
                        packetTx.crc = packetTx.crc ^ packetTx.raw[rfTrcvStatus.hwByte];
                        if (rfTrcvStatus.hwByte == packetTx.packet.size)
                        {
                            rfTrcvStatus.hwByte = 48;
                        }
                        break;

                    case 49: // crc
                        Mrf49TxByte(packetTx.crc);
                        break;

                    case 50:
                        Mrf49TxByte(0x00);
                        break;

                    case 51:
                        Mrf49TxByte(0x00);
                        Mrf49xaModeRx();
                        packetTx.state = PKT_FREE;
                        break;
                }


                break;
        }
    }

    // TODO: Wake-up timer
    // On second thought, the underneath is not very attractive.
    // The wake-up needs shadow PMC register as the bit needs to be set
    // to 0 and back to 1 for it to retrigger.
    // An internal timer is more economic, as this bit reset/set costs
    // ~120us on PIC16.

    // Use the wake-up timer to signal packet timeouts & base tick
    // For example, we could transmit only 1 packet every 15ms - 20ms.
    // If a packet isn't completely received within that period, the WUT flag
    // occurs & signals the RX statemachine to abort.

    return RF_IRQ == 1 ? TRUE : FALSE;
}