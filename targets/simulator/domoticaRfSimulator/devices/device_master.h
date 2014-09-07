#ifndef DEVICE_MASTER_H
#define DEVICE_MASTER_H

#include <QThread>
#include "device.h"

#include "hardware/eeprom.h"
#include "hardware/ethernet.h"
#include "hardware/rf.h"
#include "hardware/power.h"
#include "hardware/sensor.h"

#include "devices/device_hardware.h"

class DeviceMaster : public QThread, Device
{
    // Create "fake" hardware peripherals
    HardwareEeprom_t* eeprom;          // EEPROM
    HwRfClient* rf;               // RF module
    HardwareSensor_t* sensor[16];      // up to 16 sensors

    DeviceHardware* hw;

    public:
        uint16_t id;
        void Sleepy(uint16_t timeMs);
        DeviceMaster(DeviceHardware* hw);

    protected:
        void run();
};

#endif // DEVICE_MASTER_H
