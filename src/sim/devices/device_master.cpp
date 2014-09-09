#include "devices/device_master.h"
#include <stdio.h>
#include <unistd.h>

extern void Sleepy(uint16_t);

void* master_run(void* arg);

DeviceMaster::DeviceMaster(DeviceHardware* hw)
{
    this->hw = hw;

    this->id = 0xFF;
    this->rf = new HwRfClient((Device*)hw, this->id, hw->rfBus);

    this->hw->rfBus->Connect(this->rf);

    // Create pthread
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&this->simMain, &attr, master_run, (void*)this);
}

void* master_run(void* arg)
{
    DeviceMaster* hw = (DeviceMaster*) arg;
    rfTrcvPacket_t ping;
    int i;

    fprintf(stdout, "Hello from your beloved master\r\n");
    uint32_t counter = 0;
    while(1)
    {

        counter++;
        if (counter == 2000/5)
	{
            fprintf(stdout, "PING!\r\n");
            counter = 0;

            ping.packet.src = 1;
            ping.packet.dst = 0xFF;
            ping.packet.id = RF_PING;
            ping.packet.size = 16;
            ping.packet.opt = 0;

            ping.packet.data[0] = 1;
            for( i = 1; i < 16 ;i++)
                ping.packet.data[i] = i;

            Mrf49xaTxPacket(hw->rf->mac, &ping, false, false);
        }
        Mrf49xaTick(hw->rf->mac);

        Sleepy(5);
    }
    pthread_exit(NULL);
    return arg;
}
