#ifndef DRIVERS__CCBuf_H
#define DRIVERS__CCBuf_H

#include "stddefs.h"

typedef struct CircBufDef_s
{
    UI08_t* const  bf;
    const UI08_t size;
    UI08_t wrPt;
    UI08_t rdPt;
} CircBufDef_t;

#define CCBufInit(def, bf, size, opt) _CCBufInit()
#define CCBufReset(def) _CCBufReset()

#define CCBufCalcPt(def, e, m) _CCBufCalcPt(e, M)
#define CCBufCanWr(def) _CCBufCanWr()
#define CCBufCanRd(def) _CCBufCanRd()
#define CCBufPeekByte(def) _CCBufPeekByte()
#define CCBufRdReverse(def, q) _CCBufRdReverse(q)

#define CCBufRdByte(def) _CCBufRdByte()
#define CCBufRd(def, bf, m) _CCBufRd(bf, m)
#define CCBufWrByte(def, b) _CCBufWrByte(b)
#define CCBufWr(def, bf, c) _CCBufWr(bf, c)
#define CCBufGetRdCount(def) _CCBufGetRdCount()

inline void _CCBufInit(void);
inline void _CCBufReset(void);

UI08_t _CCBufCalcPt(UI08_t entry, I08_t move);
inline bool_t _CCBufCanWr(void);
inline bool_t _CCBufCanRd(void);
UI08_t _CCBufPeekByte(void);
inline void _CCBufRdReverse(UI08_t qty);

UI08_t _CCBufRdByte(void);
UI08_t _CCBufRd(UI08_t* bf, UI08_t max);
void _CCBufWrByte(UI08_t data);
void _CCBufWr(UI08_t* bf, UI08_t count);

UI08_t _CCBufGetRdCount(void);
// TODO: _CCBufGetWrCount

#endif