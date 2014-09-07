#ifndef DEVICE_HARDWARE_H
#define DEVICE_HARDWARE_H

#include <QThread>

#include "hardware/rf.h"
#include "device.h"

class DeviceHardware : public QThread, Device
{
    Q_OBJECT

public:

    HwRfMain* rfBus;

    DeviceHardware();
    ~DeviceHardware();

    void Sleepy(uint16_t time);

protected:
    void run();
};

#endif // DEVICE_HARDWARE_H
