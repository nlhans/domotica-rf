#include "domoticasimulator.h"
#include <QApplication>

#include "devices/device_slave.h"
#include "devices/device_hardware.h"

DeviceHardware* hardware;
DeviceSlave* slaves [8];

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DomoticaSimulator w;
    w.show();

    hardware = new DeviceHardware();
    hardware->start();

    for (int k = 0; k < 10; k++)
    {
        slaves[k] = new DeviceSlave(k, hardware);
        slaves[k]->start();
    }

    return a.exec();
}
