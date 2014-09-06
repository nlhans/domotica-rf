#include "device_hardware.h"

DeviceHardware::DeviceHardware()
{
    this->rfBus = new HwRfMain();
}

DeviceHardware::~DeviceHardware()
{
    delete(this->rfBus);
}

void DeviceHardware::run()
{
    this->rfBus->Tick();
    usleep(1000);
}
