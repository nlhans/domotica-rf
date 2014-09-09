#include "devices/device_hardware.h"
#include <stdio.h>
#include <unistd.h>
extern void Sleepy(uint16_t);

void* hardware_run(void* arg);

DeviceHardware::DeviceHardware()
{
    this->rfBus = new HwRfMain();

    // Create pthread
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&this->simMain, &attr, hardware_run, (void*)this);
}

DeviceHardware::~DeviceHardware()
{
    delete(this->rfBus);
}

void* hardware_run(void* arg)
{
    DeviceHardware* hw = (DeviceHardware*) arg;
    while(1)
    {
        hw->rfBus->Tick();
        usleep(10);
    }
    pthread_exit(NULL);
    return arg;
}
