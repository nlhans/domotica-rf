#ifndef PROFILING_EXECUTIONTIME_PROJECT
#define PROFILING_EXECUTIONTIME_PROJECT

#include "stddefs.h"
//#include "profiling/executiontime.h"

#define execGetTimestamp() ((UI32_t)(TMR2 | (TMR3 << 16)) / (F_OSC_DIV_2/1000000) )
#define execResetTimestamp() do { TMR2 = 0; TMR3 = 0;} while(0);

#define EXEC_ENABLE 1

#define executionTimeTable(point) \
    point(ENC_START_PACKET, "[ENC] Start RX packet") \
    point(ENC_RX_PACKET, "[ENC] rd bf [start]") \
    point(ENC_RX_PACKET_DONE, "[ENC] rd bf [done]") \
    point(ENC_RX_SKIPPED, "[ENC] skipped") \
    point(ENC_TX_BUFFER, "[ENC] SPI write buffer start") \
    point(ENC_TX_SEND, "[ENC] SPI write buffer done / mac send start()") \
    point(ENC_TX_DONE, "[ENC] mac send done()") \
    point(ENC_TX_FRAME, "[ENC] tx frame()") \
    point(ENC_TX_REPLY_FRAME, "[ENC] tx reply frame()") \
    point(ENC_READ_PACKET, "[ENC] SPI read buffer") \
    point(IPV4_HANDLE, "[IP]  IPv4 handle()") \
    point(TCP_HANDLE, "[IP]  TCP handle()") \
    point(TCP_STATE_MACHINE, "[IP]  TCP statemachine()") \
    point(TCP_RX_DATA_B, "[IP]  TCP app Rx data handle (start)") \
    point(TCP_RX_DATA_E, "[IP]  TCP app Rx data handle (end)") \
    point(TCP_TX_REPLY, "[IP]  TCP TX Reply packet") \
    point(TCP_TX, "[IP]  TCP TX packet") \
    point(TCP_CLOSE, "[IP]  TCP close connection") \
    point(TCP_CRC_S, "[IP]  TCP CRC calc start") \
    point(TCP_CRC_E, "[IP]  TCP CRC calc end") \
    point(IPV4_TX_REPLY, "[IP]  IPv4 TX Reply packet") \
    point(IPV4_TX, "[IP]  IPv4 TX packet") \
    point(IPV4_CRC_S, "[IP]  IPv4 CRC calc start") \
    point(IPV4_CRC_E, "[IP]  IPv4 CRC calc end") \
    point(UDP_TX, "[IP]  UDP TX packet") \


#endif