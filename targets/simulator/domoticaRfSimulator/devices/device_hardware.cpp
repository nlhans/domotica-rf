#include "device_hardware.h"

DeviceHardware::DeviceHardware()
{
    this->rfBus = new HwRfMain();
}

DeviceHardware::~DeviceHardware()
{
    delete(this->rfBus);
}

void DeviceHardware::Sleepy(uint16_t time)
{
    this->usleep(time*1000);
}

void DeviceHardware::run()
{
    while(1)
    {
        this->rfBus->Tick();
        this->usleep(10);
    }
}
