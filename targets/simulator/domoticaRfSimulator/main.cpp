#include "domoticasimulator.h"
#include <QApplication>

#include "devices/device_slave.h"

DeviceSlave* slaves [8];

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DomoticaSimulator w;
    w.show();

    for (int k = 0; k < 8; k++)
    {
        slaves[k] = new DeviceSlave(k);
        slaves[k]->start();
    }

    return a.exec();
}
