#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "devices/device_slave.h"
#include "devices/device_hardware.h"
#include "devices/device_master.h"

#include <stdio.h>

DeviceHardware* hardware;
DeviceSlave* slaves [8];
DeviceMaster* master;


int main(int argc, char** argv)
{
	fprintf(stdout, "Hello world!");

    hardware = new DeviceHardware();
    master = new DeviceMaster(hardware);

    for (int k = 0; k < 16; k++)
    {
	fprintf(stdout, "Creating slave %d\r\n", k);
        slaves[k] = new DeviceSlave(k, hardware);
    }

	usleep(5000000);

	return 0;
}
