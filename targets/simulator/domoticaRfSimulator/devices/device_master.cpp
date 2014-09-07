#include <QDebug>

#include "device_master.h"


DeviceMaster::DeviceMaster(DeviceHardware* hw)
{
    this->hw = hw;

    this->id = 0xFF;
    this->rf = new HwRfClient((Device*)hw, this->id, hw->rfBus);

    this->hw->rfBus->Connect(this->rf);
}

void DeviceMaster::Sleepy(uint16_t time)
{
    this->usleep(time*500);
}

void DeviceMaster::run()
{
    rfTrcvPacket_t ping;
    int i;

    uint32_t counter = 0;
    while(1)
    {

        counter++;
        if (counter == 2000/5)
        {
            qDebug() << "S PING!";
            counter = 0;

            ping.packet.src = 1;
            ping.packet.dst = 0xFF;
            ping.packet.id = RF_PING;
            ping.packet.size = 16;
            ping.packet.opt = 0;

            ping.packet.data[0] = 1;
            for( i = 1; i < 16 ;i++)
                ping.packet.data[i] = i;

            Mrf49xaTxPacket(this->rf->mac, &ping, false, false);
        }
        Mrf49xaTick(this->rf->mac);

        Sleepy(5);
    }
}
