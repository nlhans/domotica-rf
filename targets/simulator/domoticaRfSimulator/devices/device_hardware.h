#ifndef DEVICE_HARDWARE_H
#define DEVICE_HARDWARE_H

#include <QThread>

#include "hardware/rf.h"

class DeviceHardware : public QThread
{
    Q_OBJECT

public:

    HwRfMain* rfBus;

    DeviceHardware();
    ~DeviceHardware();

protected:
    void run();
};

#endif // DEVICE_HARDWARE_H
