#ifndef RFSTACK_PACKETS_H
#define RFSTACK_PACKETS_H

#include "stddefs.h"
#include "rfstack/rfdefs.h"

#include "utilities/pt.h"

PT_THREAD(RfPacketsTickTh);
extern struct pt halPkTh;

void RfPacketTransmit(UI08_t dst, RfMsg_t msg, UI08_t* data, UI08_t length, UI08_t opt);
void RfPacketSimpleReply(RfTransceiverPacket_t* packet, RfMsg_t msg);
void RfPacketReply(RfTransceiverPacket_t* packet, RfMsg_t msg, UI08_t* data, UI08_t length, UI08_t opt);

#endif