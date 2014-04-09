#include "utilities/ccbuf_static.h"

extern CircBufDef_t* const CCDef;

inline void _CCBufInit(void)
{
    _CCBufReset();
}

inline void _CCBufReset(void)
{
    // Reset buffer
    UI08_t i = CCDef->size;
    while (i > 0)
    {
        i--;
        CCDef->bf[i] = 0;
    }
    
    CCDef->rdPt = CCDef->size - 1;
    CCDef->wrPt = 0;
}

UI08_t _CCBufCalcPt(UI08_t entry, I08_t move)
{
    I08_t result = ((I08_t)entry) + move;

    while (result < 0) result += CCDef->size;
    while (result >= CCDef->size) result -= CCDef->size;

    return (UI08_t) result;
}

inline bool_t _CCBufCanWr(void)
{
    if (CCDef->wrPt == CCDef->rdPt) return FALSE;
    else return TRUE;
}


inline void _CCBufRdReverse(UI08_t qty)
{
    CCDef->rdPt = _CCBufCalcPt(CCDef->rdPt, 0-qty);
    if (CCDef->rdPt == CCDef->wrPt)
    {
        // We've moved it back to far
        CCDef->rdPt++;
    }
}

inline bool_t _CCBufCanRd(void)
{
    // If RD pt is done +1, is it at WR pt?
    // If that is the case, then the buffer is empty.
    if (_CCBufCalcPt(CCDef->rdPt, 1) == CCDef->wrPt) return FALSE;
    else return TRUE;
}

UI08_t _CCBufRdByte(void)
{
    if (_CCBufCanRd())
    {
        CCDef->rdPt = _CCBufCalcPt(CCDef->rdPt, 1);
        UI08_t res = CCDef->bf[CCDef->rdPt];
        //CCDef->bf[CCDef->rdPt] = 0;
        return res;
    }
    return 0;
}

UI08_t _CCBufPeekByte(void)
{
    if (_CCBufCanRd())
    {
        UI08_t res = CCDef->bf[_CCBufCalcPt(CCDef->rdPt, 1)];
        return res;
    }
    return 0;
}

UI08_t _CCBufRd(UI08_t* bf, UI08_t max)
{
    UI08_t read = 0;

    while (_CCBufCanRd() && read < max)
    {
        bf[read] = (UI08_t) _CCBufRdByte();
        read++;
    }

    return read;
}

void _CCBufWrByte(UI08_t data)
{
    if (_CCBufCanWr())
    {
        CCDef->bf[CCDef->wrPt] = data;
        CCDef->wrPt = _CCBufCalcPt(CCDef->wrPt, 1);
    }
}

void _CCBufWr(UI08_t* bf, UI08_t count)
{
    while (count > 0)
    {
        _CCBufWrByte(*bf);
        bf++;
        count--;
    }
}

UI08_t _CCBufGetRdCount(void)
{
    UI08_t distance = CCDef->wrPt - CCDef->rdPt;
    if (CCDef->rdPt > CCDef->wrPt)
    {
        distance += CCDef->size;
    }

    return distance;
}
