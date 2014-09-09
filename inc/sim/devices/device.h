#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>

class Device
{
public:
    virtual void Sleepy(uint16_t time) { }
};

#endif // DEVICE_H
