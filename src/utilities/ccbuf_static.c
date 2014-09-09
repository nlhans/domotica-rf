#include "utilities/ccbuf_static.h"

extern CircBufDef_t* const CCDef;

inline void _CCBufInit(void)
{
    _CCBufReset();
}

inline void _CCBufReset(void)
{
    // Reset buffer
    uint8_t i = CCDef->size;
    while (i > 0)
    {
        i--;
        CCDef->bf[i] = 0;
    }
    
    CCDef->rdPt = CCDef->size - 1;
    CCDef->wrPt = 0;
}

uint8_t _CCBufCalcPt(uint8_t entry, I08_t move)
{
    I08_t result = ((I08_t)entry) + move;

    while (result < 0) result += CCDef->size;
    while (result >= CCDef->size) result -= CCDef->size;

    return (uint8_t) result;
}

inline bool _CCBufCanWr(void)
{
    if (CCDef->wrPt == CCDef->rdPt) return false;
    else return true;
}


inline void _CCBufRdReverse(uint8_t qty)
{
    CCDef->rdPt = _CCBufCalcPt(CCDef->rdPt, 0-qty);
    if (CCDef->rdPt == CCDef->wrPt)
    {
        // We've moved it back to far
        CCDef->rdPt++;
    }
}

inline bool _CCBufCanRd(void)
{
    // If RD pt is done +1, is it at WR pt?
    // If that is the case, then the buffer is empty.
    if (_CCBufCalcPt(CCDef->rdPt, 1) == CCDef->wrPt) return false;
    else return true;
}

uint8_t _CCBufRdByte(void)
{
    if (_CCBufCanRd())
    {
        CCDef->rdPt = _CCBufCalcPt(CCDef->rdPt, 1);
        uint8_t res = CCDef->bf[CCDef->rdPt];
        //CCDef->bf[CCDef->rdPt] = 0;
        return res;
    }
    return 0;
}

uint8_t _CCBufPeekByte(void)
{
    if (_CCBufCanRd())
    {
        uint8_t res = CCDef->bf[_CCBufCalcPt(CCDef->rdPt, 1)];
        return res;
    }
    return 0;
}

uint8_t _CCBufRd(uint8_t* bf, uint8_t max)
{
    uint8_t read = 0;

    while (_CCBufCanRd() && read < max)
    {
        bf[read] = (uint8_t) _CCBufRdByte();
        read++;
    }

    return read;
}

void _CCBufWrByte(uint8_t data)
{
    if (_CCBufCanWr())
    {
        CCDef->bf[CCDef->wrPt] = data;
        CCDef->wrPt = _CCBufCalcPt(CCDef->wrPt, 1);
    }
}

void _CCBufWr(uint8_t* bf, uint8_t count)
{
    while (count > 0)
    {
        _CCBufWrByte(*bf);
        bf++;
        count--;
    }
}

uint8_t _CCBufGetRdCount(void)
{
    uint8_t distance = CCDef->wrPt - CCDef->rdPt;
    if (CCDef->rdPt > CCDef->wrPt)
    {
        distance += CCDef->size;
    }

    return distance;
}
