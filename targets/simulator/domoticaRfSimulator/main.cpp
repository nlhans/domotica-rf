#include "domoticasimulator.h"
#include <QApplication>

#include "devices/device_slave.h"
#include "devices/device_hardware.h"
#include "devices/device_master.h"

#include <stdio.h>

DeviceHardware* hardware;
DeviceSlave* slaves [8];
DeviceMaster* master;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DomoticaSimulator w;
    w.show();

    /*hardware = new DeviceHardware();
    hardware->start();

    master = new DeviceMaster(hardware);
    master->start();*/

    for (int k = 0; k < 1; k++)
    {
fprintf(stdout, "Creating thread %d", k);
        slaves[k] = new DeviceSlave(k, hardware);
        slaves[k]->start();
    }

    return a.exec();
}
