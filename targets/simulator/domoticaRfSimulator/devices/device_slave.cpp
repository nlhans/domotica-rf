#include "device_slave.h"

#include <stdio.h>

#include <QDebug>

#include "hardware/rf.h"

#include "devices/mrf49xa.h"

DeviceSlave::DeviceSlave(uint16_t id)
{
    this->id = id;
    this->rf = new HwRfClient(id);
}

void DeviceSlave::run()
{
    while(1)
    {
        this->rf->Tick();

        Mrf49xaTick(this->rf->mac);

        usleep(1000);
    }
}
