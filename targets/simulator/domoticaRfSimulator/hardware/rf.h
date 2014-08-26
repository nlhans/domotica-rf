#ifndef HARDWARE_RF_BUS
#define HARDWARE_RF_BUS

#include <stdint.h>
#include <QString>

#define RF_MAX_CLIENTS 32

class HwRfBus
{
    protected:
        uint16_t id;

    public:
        HwRfBus(uint16_t id);
        ~HwRfBus();

        void Tick();
};

class HwRfClient
{
    public:
        HwRfBus* client;

        uint8_t byteRxFifo1;
        uint8_t byteRxFifo2;

        uint8_t rxFifoOverflow;
        uint8_t txFifoEmpty;
};

class HwRfMain
{
    private:
        HwRfClient* rfClients[RF_MAX_CLIENTS];

    public:

        void Connect(HwRfBus* client);
        void Disconnect(HwRfBus* client);

        bool SignalPresent();
        bool DataQuality();

        bool BytePending(HwRfBus* client);

        void SendByte(HwRfBus* client, uint8_t byte);
        uint8_t ReceiveByte(HwRfBus* client);
};

#endif
