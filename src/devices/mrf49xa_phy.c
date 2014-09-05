#include "devices/mrf49xa.h"

// Serve MRf49XA chipset when requires attention.
#ifdef PIC24_HW
bool_t Mrf49xaServe(uint8_t foo)
#else
bool_t Mrf49xaServe(Mrf49xaMac_t* inst)
#endif
{
    uint8_t data;
#ifdef MRF49XA_POWER_SWITCH
    if (mrf49Inst->state == POWERED_OFF)
        return FALSE;
#endif

    if (mrf49Inst->needsReset)
        return FALSE;

    Mrf49RxSts(mrf49Inst);

    if (mrf49Inst->status.byte[0] == 0xFF && mrf49Inst->status.byte[1] == 0xFF)
        return FALSE;

    // Power-on-Reset
    if (mrf49Inst->status.flags.msb.por == 1)
    {
        // TODO: Software reset?
    }

    // TXOWRXOF (RX overrun / TX underrun)
    if (mrf49Inst->status.flags.msb.overflow == 1)
    {
        switch(mrf49Inst->state)
        {
            case RECV_IDLE:
            case RECV_DATA:

                // Clear fifo data
                data = Mrf49RxByte();
                data = Mrf49RxByte();

                // Reset HW & SW rx
                Mrf49xaModeRx(mrf49Inst);

                // TODO: Wait until end of this packet burst is done.

                break;
#ifdef MRF49XA_POWER_SWITCH
            case POWERED_OFF:
                Mrf49xaNeedsReset(mrf49Inst);
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
    if (mrf49Inst->status.flags.msb.fifoTxRx == 1)
    {
        // Depending on the driver status.
        switch (mrf49Inst->state)
        {
#ifdef MRF49XA_POWER_SWITCH
            case POWERED_OFF:
                Mrf49xaNeedsReset(mrf49Inst);
                break;
#endif

            case RECV_IDLE:
                data = Mrf49RxByte();

                // Truncate data if quality is bad
                // Reset radio & wait for sync byte. Current pattern is rubbish data.
                if (mrf49Inst->status.flags.lsb.dataQualityOK == 0)
                {
                    Mrf49xaModeRx(mrf49Inst);
                    break;
                }

                if (mrf49Inst->rxPacket[0].state == PKT_FREE) mrf49Inst->hwRx = &(mrf49Inst->rxPacket[0]);
                else if (mrf49Inst->rxPacket[1].state == PKT_FREE) mrf49Inst->hwRx = &(mrf49Inst->rxPacket[1]);
                else
                {
                    // Error, no space in RX buffers.
                    // Reset radio. Drop this packet.
                    Mrf49xaModeRx(mrf49Inst);
                    break;
                }

                mrf49Inst->hwRx->packet.size = data;
                mrf49Inst->hwRx->crc = 0;
                mrf49Inst->hwRx->state = PKT_HW_BUSY_RX;

                mrf49Inst->state = RECV_DATA;
                mrf49Inst->hwByte = 1;

                break;

            case RECV_DATA:

                data = Mrf49RxByte();

                // Truncate data if quality is bad
                // Reset radio & wait for sync byte. Current pattern is rubbish data.
                if (mrf49Inst->status.flags.lsb.dataQualityOK == 0)
                {
                    mrf49Inst->hwRx->state = PKT_FREE;
                    Mrf49xaModeRx(mrf49Inst);
                    break;
                }

                if (mrf49Inst->hwByte == mrf49Inst->hwRx->packet.size)
                {
                    mrf49Inst->hwRx->crc = data;

                    // TODO: Check CRC
                    // TODO: Check node ID (broadcast/myself)
                    mrf49Inst->hwRx->state = PKT_HW_READY_RX;
#ifdef dsPIC33
                    packetRx->timestamp = RtosTimestamp;
#endif

                    // Reset modem
                    Mrf49xaModeRx(mrf49Inst);

                }
                else
                {
                    mrf49Inst->hwRx->raw[mrf49Inst->hwByte++] = data;
                }

                break;

            case TX_PACKET:
                mrf49Inst->hwByte++;

                if (mrf49Inst->hwByte == mrf49Inst->txPacket.packet.size)
                    mrf49Inst->hwByte = 49;
                
                switch (mrf49Inst->hwByte)
                {
                    case 100:
                        Mrf49TxByte(RF_NETWORKID1);
                        break;

                    case 101:
                        Mrf49TxByte(RF_NETWORKID2);
                        mrf49Inst->hwByte = 0x7F;
                        break;

                        // 4..packet size
                    default:
                        Mrf49TxByte(mrf49Inst->txPacket.raw[mrf49Inst->hwByte]);
                        break;

                    case 49: // crc
                        Mrf49TxByte(mrf49Inst->txPacket.crc);
                        break;

                    case 50:
                        Mrf49TxByte(0x00);
                        break;

                    case 51:
                        Mrf49TxByte(0x00);
                        Mrf49xaModeRx(mrf49Inst);

                        mrf49Inst->txPacket.retry = 0;

                        if (mrf49Inst->txPacket.needAck == NEED_ACK)
                            mrf49Inst->txPacket.state = PKT_WAITING_FOR_ACK;
                        else
                            mrf49Inst->txPacket.state = PKT_FREE;
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