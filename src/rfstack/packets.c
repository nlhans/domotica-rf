#include "rfstack/packets.h"
#include "devices/mrf49xa.h"

#include "bsp/adc.h"
#include "power.h"


uint8_t coldBoot = 1;
uint32_t syncedTime;

// TODO: These are all client-specific packets
// Seperate them?

void RfSendPowerState(Mrf49xaMac_t* inst)
{
    rfTrcvPacket_t* packet = Mrf49xaAllocPacket(inst);

    packet->packet.size = 4;
    packet->packet.id = RF_POWER_STATUS;
    packet->packet.dst = 0xFF;

    packet->packet.data[0] = coldBoot;          coldBoot = 0;
    packet->packet.data[1] = 0;

    PwrAdcWake();
    uint16_t s = AdcSample(ADC_FVR);
    PwrAdcSleep();
    packet->packet.data[2] = s & 0xFF;
    packet->packet.data[3] = s >> 8;

    Mrf49xaTxPacket(inst, packet, FALSE, TRUE);
}

void RfSendSampleWeatherNode(Mrf49xaMac_t* inst, uint16_t temperature, uint16_t humidity)
{
    rfTrcvPacket_t* packet = Mrf49xaAllocPacket(inst);

    packet->packet.size = 10;
    packet->packet.id = RF_APP_SAMPLE;
    packet->packet.dst = 0xFF; // TODO: Find coordinator

    packet->packet.data[0] = 0; // TODO: Enter timestamp
    packet->packet.data[1] = 0; // TODO: Enter timestamp
    packet->packet.data[2] = 0; // TODO: Enter timestamp
    packet->packet.data[3] = 0; // TODO: Enter timestamp

    packet->packet.data[4] = 0; // Temperature is channel 0

    packet->packet.data[6] = temperature >> 8;
    packet->packet.data[5] = temperature & 0xFF;

    packet->packet.data[7] = 1; // Humidity is channel 1

    packet->packet.data[9] = humidity >> 8;
    packet->packet.data[8] = humidity & 0xFF;

    Mrf49xaTxPacket(inst, packet, FALSE, TRUE);
}