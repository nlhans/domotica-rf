#ifndef MRF49XA_BSP
#define MRF49XA_BSP

#define eepromRxBytes(a,b,c)
extern uint32_t syncedTime;

#define HandlePacket HandlePacketClient
#define Delay5Ms() usleep(5000)

#define mrf49Inst inst

#endif
