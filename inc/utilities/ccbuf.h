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
    UI08_t* bf;
    UI16_t size;
    UI16_t wrPt;
    UI16_t rdPt;
    UI08_t options;
    UI08_t faults;
} CircBufDef_t;

void CCBufInit(CircBufDef_t* CCDef, UI08_t* bf, UI16_t size, UI08_t options);
void CCBufReset(CircBufDef_t* CCDef);
UI08_t CCBufGetFaultStatus(CircBufDef_t* CCDef);

UI16_t CCBufCalcPt(CircBufDef_t* CCDef, UI16_t entry, I16_t move);
bool_t CCBufCanWr(CircBufDef_t* CCDef);
bool_t CCBufCanRd(CircBufDef_t* CCDef);
UI16_t CCBufRdByte(CircBufDef_t* CCDef);
UI16_t CCBufPeekByte(CircBufDef_t* CCDef);
void CCBufRdReverse(CircBufDef_t* CCDef, UI16_t qty);

UI16_t CCBufRd(CircBufDef_t* CCDef, UI08_t* bf, UI16_t max);
bool_t CCBufWrByte(CircBufDef_t* CCDef, UI08_t data);
bool_t CCBufWr(CircBufDef_t* CCDef, UI08_t* bf, UI16_t count);

UI16_t CCBufGetRdCount(CircBufDef_t* CCDef);
// TODO: CCBufGetWrCount

#endif