#ifndef DRIVERS_CCBUF_H
#define DRIVERS_CCBUF_H

#define CCBUF_READ_ERROR 0x5A00
#define CCBUF_CALC_ERROR_UNDER 0x5B00
#define CCBUF_CALC_ERROR_OVER 0x5C00

#define CCDEF_OPT_ALLOW_OVERFLOW 0x01

#define CCBUF_FLT_OVERFLOW 0x01
#define CCBUF_FLT_BF_ERR 0x02

#include "stddefs.h"

typedef struct CircBufDef_s
{
    uint8_t* bf;
    uint16_t size;
    uint16_t wrPt;
    uint16_t rdPt;
    uint8_t options;
    uint8_t faults;
} CircBufDef_t;

void CCBufInit(CircBufDef_t* CCDef, uint8_t* bf, uint16_t size, uint8_t options);
void CCBufReset(CircBufDef_t* CCDef);
uint8_t CCBufGetFaultStatus(CircBufDef_t* CCDef);

uint16_t CCBufCalcPt(CircBufDef_t* CCDef, uint16_t entry, int16_t move);
bool CCBufCanWr(CircBufDef_t* CCDef);
bool CCBufCanRd(CircBufDef_t* CCDef);
uint16_t CCBufRdByte(CircBufDef_t* CCDef);
uint16_t CCBufPeekByte(CircBufDef_t* CCDef);
void CCBufRdReverse(CircBufDef_t* CCDef, uint16_t qty);

uint16_t CCBufRd(CircBufDef_t* CCDef, uint8_t* bf, uint16_t max);
bool CCBufWrByte(CircBufDef_t* CCDef, uint8_t data);
bool CCBufWr(CircBufDef_t* CCDef, uint8_t* bf, uint16_t count);

uint16_t CCBufGetRdCount(CircBufDef_t* CCDef);
// TODO: CCBufGetWrCount

#endif