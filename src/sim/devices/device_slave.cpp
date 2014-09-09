#include "devices/device_slave.h"

#include <stdio.h>
#include <unistd.h>

#include "hardware/rf.h"

#include "devices/mrf49xa.h"
#include "devices/device.h"

#include "rfstack/packets.h"

#include "hardware/power.h"
#include "bsp/adc.h"

void* device_run(void* arg);

DeviceSlave::DeviceSlave(uint16_t id, DeviceHardware* hw)
{
    this->hw = hw;

    this->id = id;
    this->rf = new HwRfClient((Device*)hw, id, hw->rfBus);

    this->hw->rfBus->Connect(this->rf);
    
    // Create pthread
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&this->simMain, &attr, device_run, (void*)this);
}

void DeviceSlave::Sleepy(uint16_t time)
{
    usleep(time*500);
}

void Sleepy(uint16_t time)
{
    usleep(time*500);
}

void* device_run(void* arg)
{
    DeviceSlave* thr = (DeviceSlave*) arg;

    uint16_t powerStatusTicker;
    Mrf49xaMac_t* macPtr = thr->rf->mac;
    fprintf(stdout, "Hello from %d\r\n", thr->id);
    Sleepy(thr->id*334);

    while(1)
    {
        Mrf49xaTick(thr->rf->mac);
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
    pthread_exit(NULL);
    return arg;
}
