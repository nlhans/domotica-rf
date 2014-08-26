#include "rf.h"

HwRfBus::HwRfBus(uint16_t id)
{
    // Connect to Dbus:
    this->id = id;
}

HwRfBus::~HwRfBus()
{
    //
    this->id = -1;
}

void HwRfBus::Tick()
{
    //
}
