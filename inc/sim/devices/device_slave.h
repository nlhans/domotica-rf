#ifndef DEVICE_SLAVE_H
#define DEVICE_SLAVE_H

#include <pthread.h>
#include "stdint.h"

#include "device_hardware.h"

#include "hardware/eeprom.h"
#include "hardware/rf.h"
#include "hardware/sensor.h"

class DeviceSlave : public Device
{
    public:
        // Create "fake" hardware peripherals
        HardwareEeprom_t* eeprom;          // EEPROM
        HwRfClient* rf;               // RF module
        HardwareSensor_t* sensor[16];      // up to 16 sensors
        pthread_t simMain;

        DeviceHardware* hw;

        uint16_t id;
        void Sleepy(uint16_t timeMs);
        DeviceSlave(uint16_t id, DeviceHardware* hw);

};

typedef class DeviceSlave DeviceSlave_t;

#endif // DEVICE_SLAVE_H
