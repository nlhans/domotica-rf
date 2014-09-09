#ifndef DEVICE_HARDWARE_H
#define DEVICE_HARDWARE_H

#include "hardware/rf.h"
#include "device.h"
#include <pthread.h>

class DeviceHardware
{
public:

    HwRfMain* rfBus;
        pthread_t simMain;

    DeviceHardware();
    ~DeviceHardware();
};

#endif // DEVICE_HARDWARE_H
