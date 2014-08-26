#include "devices/mrf49xa.h"

extern Mrf49xaMac_t rfTrcvStatus;

// Serve MRf49XA chipset when requires attention.
#ifdef PIC24_HW
bool_t Mrf49xaServe(uint8_t foo)
#else
bool_t Mrf49xaServe(void)
#endif
{
    uint8_t data;
#ifdef MRF49XA_POWER_SWITCH
    if (rfTrcvStatus.state == POWERED_OFF)
        return FALSE;
#endif

    if (rfTrcvStatus.needsReset)
        return FALSE;

    Mrf49RxSts();

    if (mrf49Status.byte[0] == 0xFF && mrf49Status.byte[1] == 0xFF)
        return FALSE;

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

                // Clear fifo data
                data = Mrf49RxByte();
                data = Mrf49RxByte();

                // Reset HW & SW rx
                Mrf49xaModeRx();

                // TODO: Wait until end of this packet burst is done.

                break;
#ifdef MRF49XA_POWER_SWITCH
            case POWERED_OFF:
                Mrf49xaNeedsReset();
                break;
#endif
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
#ifdef MRF49XA_POWER_SWITCH
            case POWERED_OFF:
                Mrf49xaNeedsReset();
                break;
#endif

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

                rfTrcvStatus.hwRx->packet.size = data;
                rfTrcvStatus.hwRx->crc = 0;
                rfTrcvStatus.hwRx->state = PKT_HW_BUSY_RX;

                rfTrcvStatus.state = RECV_DATA;
                rfTrcvStatus.hwByte = 1;

                break;

            case RECV_DATA:

                data = Mrf49RxByte();

                // Truncate data if quality is bad
                // Reset radio & wait for sync byte. Current pattern is rubbish data.
                if (mrf49Status.flags.lsb.dataQualityOK == 0)
                {
                    rfTrcvStatus.hwRx->state = PKT_FREE;
                    Mrf49xaModeRx();
                    break;
                }

                if (rfTrcvStatus.hwByte == rfTrcvStatus.hwRx->packet.size)
                {
                    rfTrcvStatus.hwRx->crc = data;

                    // TODO: Check CRC
                    // TODO: Check node ID (broadcast/myself)
                    rfTrcvStatus.hwRx->state = PKT_HW_READY_RX;
#ifdef dsPIC33
                    packetRx->timestamp = RtosTimestamp;
#endif

                    // Reset modem
                    Mrf49xaModeRx();

                }
                else
                {
                    rfTrcvStatus.hwRx->raw[rfTrcvStatus.hwByte++] = data;
                }

                break;

            case TX_PACKET:
                rfTrcvStatus.hwByte++;

                if (rfTrcvStatus.hwByte == rfTrcvStatus.txPacket.packet.size)
                    rfTrcvStatus.hwByte = 49;
                
                switch (rfTrcvStatus.hwByte)
                {
                    case 100:
                        Mrf49TxByte(RF_NETWORKID1);
                        break;

                    case 101:
                        Mrf49TxByte(RF_NETWORKID2);
                        rfTrcvStatus.hwByte = 0x7F;
                        break;

                        // 4..packet size
                    default:
                        Mrf49TxByte(rfTrcvStatus.txPacket.raw[rfTrcvStatus.hwByte]);
                        break;

                    case 49: // crc
                        Mrf49TxByte(rfTrcvStatus.txPacket.crc);
                        break;

                    case 50:
                        Mrf49TxByte(0x00);
                        break;

                    case 51:
                        Mrf49TxByte(0x00);
                        Mrf49xaModeRx();

                        rfTrcvStatus.txPacket.retry = 0;

                        if (rfTrcvStatus.txPacket.needAck == NEED_ACK)
                            rfTrcvStatus.txPacket.state = PKT_WAITING_FOR_ACK;
                        else
                            rfTrcvStatus.txPacket.state = PKT_FREE;
                        break;
                }


                break;
        }
    }

    // TODO: Wake-up timer
    // On second thought, this is not very attractive.
    // The wake-up needs a shadow PMC register as the bit needs to be set
    // to 0 and back to 1 for it to retrigger.
    // An internal timer is more economic, as this bit reset/set costs
    // ~120us on PIC16 + extra RAM/Code.

    // Use the wake-up timer to signal packet timeouts & base tick
    // For example, we could transmit only 1 packet every 15ms - 20ms.
    // If a packet isn't completely received within that period, the WUT flag
    // occurs & signals the RX statemachine to abort.

    return RF_IRQ == 1 ? TRUE : FALSE;
}