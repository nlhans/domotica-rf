#include "device_slave.h"

#include <stdio.h>

#include <QDebug>

#include "hardware/rf.h"

DeviceSlave::DeviceSlave(uint16_t id)
{
    this->id = id;
    this->rf = new HwRfBus(id);
}

void DeviceSlave::run()
{
    while(1)
    {
        this->rf->Tick();
        //qDebug() << "Boo!";
        //sleep(1);
    }
}
