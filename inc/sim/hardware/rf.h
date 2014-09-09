#ifndef HARDWARE_RF_BUS
#define HARDWARE_RF_BUS

#include <stdint.h>
#include <unistd.h>

#include "devices/mrf49xa.h"
#include "devices/device.h"

#define RF_MAX_CLIENTS 32

/*
    struct
    {
        uint8_t signalPresent:1;    // Y
        uint8_t fifoEmpty:1;        // Y
        uint8_t lowBat:1;           // NO
        uint8_t extIntPin:1;        // NO
        uint8_t wakeup:1;           // NO
        uint8_t overflow:1;         // HMM
        uint8_t por:1;              // HMM
        uint8_t fifoTxRx:1;         // Y
    } msb;
    struct
    {
        uint8_t offset:4;           // NO
        uint8_t offsetSign:1;       // NO
        uint8_t afc:1;              // NO
        uint8_t clockLock:1;        // NO
        uint8_t dataQualityOK:1;    // Y
    } lsb;
    */

class HwRfMain;
class HwRfClient
{
    protected:
        uint16_t id;

        uint8_t phyByte;

        HwRfMain* main;

    public:
        Mrf49xaMac_t* mac;
        mrf49xaStatus_t status;
        Device* device;

        HwRfClient(Device* device, uint16_t id, HwRfMain* main);
        ~HwRfClient();
        void SwitchBuffer(bool tx);
        void Tick();
};

class HwRfMain
{
    private:
        HwRfClient* rfClients[RF_MAX_CLIENTS];

    public:
        uint8_t airByte;
        uint8_t dataQuality;
        bool sof;

        HwRfMain();

        void Tick();

        void Connect(HwRfClient* client);
        void Disconnect(HwRfClient* client);

        bool SignalPresent();
        bool DataQuality();

        bool BytePending(HwRfClient* client);

        void TxPacket(HwRfClient* client, rfTrcvPacket_t* packet);
        uint8_t RxPacket(HwRfClient* client, rfTrcvPacket_t* packet);

        static void msleep(unsigned long msecs)
        {
		usleep(msecs*1000);
        }
};

#endif
