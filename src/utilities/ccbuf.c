#include "utilities/ccbuf.h"


void CCBufInit(CircBufDef_t* CCDef, uint8_t* bf, uint16_t size, uint8_t options)
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

uint8_t CCBufGetFaultStatus(CircBufDef_t* CCDef)
{
    return CCDef->faults;
}

uint16_t CCBufCalcPt(CircBufDef_t* CCDef, uint16_t entry, int16_t move)
{
    int32_t result = (int32_t)entry + (int32_t)move;

    if (result < 0) result += CCDef->size;
    if (result < 0) return CCBUF_CALC_ERROR_UNDER;

    if (result >= CCDef->size) result -= CCDef->size;
    if (result >= CCDef->size) return CCBUF_CALC_ERROR_OVER;

    return (uint16_t) result;
}

bool CCBufCanWr(CircBufDef_t* CCDef)
{
    if ((CCDef->faults & CCBUF_FLT_OVERFLOW) != 0) return false;
    if ((CCDef->faults & CCBUF_FLT_BF_ERR) != 0) return false;
    if (CCDef->wrPt > CCDef->size)
    {
        CCDef->faults |= CCBUF_FLT_BF_ERR;
    }

    if (CCDef->wrPt == CCDef->rdPt) return false;
    else return true;
}

void CCBufRdReverse(CircBufDef_t* CCDef, uint16_t qty)
{
    CCDef->rdPt = CCBufCalcPt(CCDef, CCDef->rdPt, 0-qty);
}

bool CCBufCanRd(CircBufDef_t* CCDef)
{
    if ((CCDef->faults & CCBUF_FLT_BF_ERR) != 0) return false;
    if (CCDef->rdPt > CCDef->size)
    {
        CCDef->faults |= CCBUF_FLT_BF_ERR;
    }

    // If RD pt is done +1, is it at WR pt?
    // If that is the case, then the buffer is empty.
    if (CCBufCalcPt(CCDef, CCDef->rdPt, 1) == CCDef->wrPt) return false;
    else return true;
}

uint16_t CCBufRdByte(CircBufDef_t* CCDef)
{
    if (CCBufCanRd(CCDef))
    {
        CCDef->rdPt = CCBufCalcPt(CCDef, CCDef->rdPt, 1);
        uint8_t res = CCDef->bf[CCDef->rdPt];
        CCDef->bf[CCDef->rdPt] = 0;
        return res;
    }
    else
    {
        printf("[CCBuf] Read error\r\n");
        return CCBUF_READ_ERROR;
    }
}

uint16_t CCBufPeekByte(CircBufDef_t* CCDef)
{
    if (CCBufCanRd(CCDef))
    {
        uint8_t res = CCDef->bf[CCBufCalcPt(CCDef, CCDef->rdPt, 1)];
        return res;
    }
    else
    {
        printf("[CCBuf] Read error\r\n");
        return CCBUF_READ_ERROR;
    }
}

uint16_t CCBufRd(CircBufDef_t* CCDef, uint8_t* bf, uint16_t max)
{
    uint16_t read = 0;

    while (CCBufCanRd(CCDef) && read < max)
    {
        bf[read] = (uint8_t) CCBufRdByte(CCDef);
        read++;
    }

    return read;
}

bool CCBufWrByte(CircBufDef_t* CCDef, uint8_t data)
{
    if (CCBufCanWr(CCDef))
    {
        CCDef->bf[CCDef->wrPt] = data;
        CCDef->wrPt = CCBufCalcPt(CCDef, CCDef->wrPt, 1);

        return true;
    }
    else if ((CCDef->options & CCDEF_OPT_ALLOW_OVERFLOW) == 0)
    {
        printf("[CCBuf] Cannot write; overflow\n");
        CCDef->faults |= CCBUF_FLT_OVERFLOW;
    }
    return false;

}

bool CCBufWr(CircBufDef_t* CCDef, uint8_t* bf, uint16_t count)
{
    bool result = true;
    uint16_t index = 0;

    while (result && index < count)
    {
        result &= CCBufWrByte(CCDef, bf[index]);
        index++;
    }

    return result;
}

uint16_t CCBufGetRdCount(CircBufDef_t* CCDef)
{
    uint16_t distance = CCDef->wrPt - CCDef->rdPt;
    if (CCDef->rdPt > CCDef->wrPt)
    {
        distance += CCDef->size;
    }

    return distance;
}
