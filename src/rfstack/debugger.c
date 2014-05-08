#include "rfstack/packets.h"
#include "dbg/dbg_task.h"

void HandlePacket(rfTrcvPacket_t* packet)
{
    memcpy(& (bfSw[bfSwPacket]), packet, sizeof(rfTrcvPacket_t));
    bfSwPacket++;

    if (bfSwPacket == HISTORY_SIZE)
        DbgTransferPackets();

    Mrf49xaFreePacket(packet);
}