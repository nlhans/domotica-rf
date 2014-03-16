#include "utilities/ccbuf.h"


void CCBufInit(CircBufDef_t* CCDef, UI08_t* bf, UI16_t size, UI08_t options)
{
    CCDef->size = size;
    CCDef->bf = bf;
    CCBufReset(CCDef);
}

void CCBufReset(CircBufDef_t* CCDef)
{
    memset(CCDef->bf, 0, CCDef->size);

    CCDef->rdPt = CCDef->size - 1;
    CCDef->wrPt = 0;

    CCDef->faults = 0;
}

UI08_t CCBufGetFaultStatus(CircBufDef_t* CCDef)
{
    return CCDef->faults;
}

UI16_t CCBufCalcPt(CircBufDef_t* CCDef, UI16_t entry, I16_t move)
{
    I32_t result = (I32_t)entry + (I32_t)move;

    if (result < 0) result += CCDef->size;
    if (result < 0) return CCBUF_CALC_ERROR_UNDER;

    if (result >= CCDef->size) result -= CCDef->size;
    if (result >= CCDef->size) return CCBUF_CALC_ERROR_OVER;

    return (UI16_t) result;
}

bool_t CCBufCanWr(CircBufDef_t* CCDef)
{
    if ((CCDef->faults & CCBUF_FLT_OVERFLOW) != 0) return FALSE;
    if ((CCDef->faults & CCBUF_FLT_BF_ERR) != 0) return FALSE;
    if (CCDef->wrPt > CCDef->size)
    {
        CCDef->faults |= CCBUF_FLT_BF_ERR;
    }

    if (CCDef->wrPt == CCDef->rdPt) return FALSE;
    else return TRUE;
}

bool_t CCBufCanRd(CircBufDef_t* CCDef)
{
    if ((CCDef->faults & CCBUF_FLT_BF_ERR) != 0) return FALSE;
    if (CCDef->rdPt > CCDef->size)
    {
        CCDef->faults |= CCBUF_FLT_BF_ERR;
    }

    // If RD pt is done +1, is it at WR pt?
    // If that is the case, then the buffer is empty.
    if (CCBufCalcPt(CCDef, CCDef->rdPt, 1) == CCDef->wrPt) return FALSE;
    else return TRUE;
}

UI16_t CCBufRdByte(CircBufDef_t* CCDef)
{
    if (CCBufCanRd(CCDef))
    {
        CCDef->rdPt = CCBufCalcPt(CCDef, CCDef->rdPt, 1);
        UI08_t res = CCDef->bf[CCDef->rdPt];
        CCDef->bf[CCDef->rdPt] = 0;
        return res;
    }
    else
    {
        printf("[CCBuf] Read error\r\n");
        return CCBUF_READ_ERROR;
    }
}

UI16_t CCBufPeekByte(CircBufDef_t* CCDef)
{
    if (CCBufCanRd(CCDef))
    {
        UI08_t res = CCDef->bf[CCBufCalcPt(CCDef, CCDef->rdPt, 1)];
        return res;
    }
    else
    {
        printf("[CCBuf] Read error\r\n");
        return CCBUF_READ_ERROR;
    }
}

UI16_t CCBufRd(CircBufDef_t* CCDef, UI08_t* bf, UI16_t max)
{
    UI16_t read = 0;

    while (CCBufCanRd(CCDef) && read < max)
    {
        bf[read] = (UI08_t) CCBufRdByte(CCDef);
        read++;
    }

    return read;
}

bool_t CCBufWrByte(CircBufDef_t* CCDef, UI08_t data)
{
    if (CCBufCanWr(CCDef))
    {
        CCDef->bf[CCDef->wrPt] = data;
        CCDef->wrPt = CCBufCalcPt(CCDef, CCDef->wrPt, 1);

        return TRUE;
    }
    else if ((CCDef->options & CCDEF_OPT_ALLOW_OVERFLOW) == 0)
    {
        CCDef->faults |= CCBUF_FLT_OVERFLOW;
    }
    return FALSE;

}

bool_t CCBufWr(CircBufDef_t* CCDef, UI08_t* bf, UI16_t count)
{
    bool_t result = TRUE;
    UI16_t index = 0;

    while (result && index < count)
    {
        result &= CCBufWrByte(CCDef, bf[index]);
        index++;
    }

    return result;
}

UI16_t CCBufGetRdCount(CircBufDef_t* CCDef)
{
    UI16_t distance = CCDef->wrPt - CCDef->rdPt;
    if (CCDef->rdPt > CCDef->wrPt)
    {
        distance += CCDef->size;
    }

    return distance;
}
