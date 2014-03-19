#ifndef PROFILING_EXECUTIONTIME_PROJECT
#define PROFILING_EXECUTIONTIME_PROJECT

#include "stddefs.h"
//#include "profiling/executiontime.h"

#define execGetTimestamp() ((UI32_t)(TMR2 | (TMR3 << 16)) / (F_OSC_DIV_2/1000000) )
#define execResetTimestamp() do { TMR2 = 0; TMR3 = 0;} while(0);

#define EXEC_ENABLE 0

#define executionTimeTable(point) \
    point(ENC_START_PACKET, "ENC28J60: ISR rx'ed packet") \
    point(ENC_RX_PACKET, "ENC28J60: SPI read buffer") \
    point(ENC_RX_PACKET_DONE, "ENC28J60: SPI read buffer done") \
    point(ENC_TX_BUFFER, "ENC28J60: SPI write buffer start") \
    point(ENC_TX_SEND, "ENC28J60: SPI write buffer done / mac send start()") \
    point(ENC_TX_DONE, "ENC28J60: mac send done()") \
    point(ENC_TX_FRAME, "ENC28J60: tx frame()") \
    point(ENC_TX_REPLY_FRAME, "ENC28J60: tx reply frame()") \
    point(ENC_READ_PACKET, "ENC28J60 SPI read buffer") \
    point(IPV4_HANDLE, "IP Stack: IPv4 handle()") \
    point(TCP_HANDLE, "IP Stack: TCP handle()") \
    point(TCP_STATE_MACHINE, "IP Stack: TCP statemachine()") \
    point(TCP_RX_DATA_B, "IP Stack: TCP app Rx data handle (start)") \
    point(TCP_RX_DATA_E, "IP Stack: TCP app Rx data handle (end)") \
    point(TCP_TX_REPLY, "IP Stack: TCP TX Reply packet") \
    point(TCP_TX, "IP Stack: TCP TX packet") \
    point(TCP_CLOSE, "IP Stack: TCP close connection") \
    point(TCP_CRC_S, "IP Stack: TCP CRC calc start") \
    point(TCP_CRC_E, "IP Stack: TCP CRC calc end") \
    point(IPV4_TX_REPLY, "IP Stack: IPv4 TX Reply packet") \
    point(IPV4_TX, "IP Stack: IPv4 TX packet") \
    point(IPV4_CRC_S, "IP Stack: IPv4 CRC calc start") \
    point(IPV4_CRC_E, "IP Stack: IPv4 CRC calc end") \
    point(UDP_TX, "IP Stack: UDP TX packet") \


#endif