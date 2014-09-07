#include "device_slave.h"

#include <stdio.h>

#include <QDebug>

#include "hardware/rf.h"

#include "devices/mrf49xa.h"
#include "devices/device.h"

#include "rfstack/packets.h"

#include "hardware/power.h"
#include "bsp/adc.h"

DeviceSlave::DeviceSlave(uint16_t id, DeviceHardware* hw)
{
    this->hw = hw;

    this->id = id;
    this->rf = new HwRfClient((Device*)hw, id, hw->rfBus);

    this->hw->rfBus->Connect(this->rf);
}

void DeviceSlave::Sleepy(uint16_t time)
{
    this->usleep(time*500);
}

void DeviceSlave::run()
{
    uint16_t powerStatusTicker;
    Mrf49xaMac_t* macPtr = this->rf->mac;

    Sleepy(this->id*334);

    while(1)
    {
        Mrf49xaTick(this->rf->mac);
        Sleepy(1);
    }

    while(1)
    {
        // 30.3s:
        //Sleepy(24576);
        Sleepy(5000);

        PwrSensorWake();
        PwrI2cWake();

        Mcp9800Start(Mcp9800_9bit);

        PwrAdcWake();
        uint16_t humidity = AdcSample(BSP_HUMIDITY_CHANNEL);
        Sleepy(100);
        uint16_t temperature = Mcp9800Read();

        PwrSensorSleep();
        PwrI2cSleep();

        PwrRfWake();

        if (macPtr->txPacket.state != PKT_FREE)
        {
            Mrf49xaNeedsReset(macPtr);
            Mrf49xaTick(macPtr);
        }

        powerStatusTicker++;

        if (powerStatusTicker >= 15)
        {
            powerStatusTicker = 0;

            RfSendPowerState(macPtr);
            do
            {
                Mrf49xaTick(macPtr);
                Sleepy(1);
            }
            while (macPtr->txPacket.state != PKT_FREE);
        }

        RfSendSampleWeatherNode(macPtr, temperature, humidity);
        do
        {
            Mrf49xaTick(macPtr);
            Sleepy(1);
        }
        while (macPtr->txPacket.state != PKT_FREE);

        PwrRfSleep();
        //Mrf49xaTick(this->rf->mac);
    }
}
