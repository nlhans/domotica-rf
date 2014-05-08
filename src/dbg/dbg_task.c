#include "stddefs.h"

#include "bsp/uart.h"

#include "rtos/task.h"
#include "rtos/timer.h"

#include "dbg/dbg_task.h"


void DbgTransfer(void);
void DbgTick(void);
void DbgTask(void);

void dbgTransferTick(void);
void dbgSwapBuffer(void);

#define DBG_TICK 0x01
#define DBG_TRANSFER 0x02

/******* RTOS INFORMATION *******/
RtosTimer_t dbgTicker;
RtosTimer_t dbgTransfer;
RtosTask_t dbgTask;
uint8_t dbgTaskStk[512];

/******* BUFFER *******/

uint8_t dmaBf[2048] __attribute__((space(dma)));
rfTrcvPacket_t historyA[HISTORY_SIZE];
rfTrcvPacket_t historyB[HISTORY_SIZE];
rfTrcvPacket_t* bfHw;
rfTrcvPacket_t* bfSw;
uint16_t bfSwPacket = 0;


uint16_t bfHwSize = 0;
uint16_t bfHwOffset = 0;
uint8_t bfTransferBusy = 0;
uint8_t bfHwNo;

void DbgInit(void)
{
    RtosTaskCreate(&dbgTask, "DBG", DbgTask, 50, dbgTaskStk, sizeof(dbgTaskStk));
    RtosTimerCreate(&dbgTicker, 10, DbgTick);
    RtosTimerCreate(&dbgTransfer, 100, DbgTransfer);
    
    dbgSwapBuffer();
}

void DbgTick(void)
{
    RtosTaskSignalEvent(&dbgTask, DBG_TICK);

    RtosTimerRearm(&dbgTicker, 10);
}

void DbgTransfer(void)
{
    RtosTaskSignalEvent(&dbgTask, DBG_TRANSFER);

    RtosTimerRearm(&dbgTransfer, 100);
}

void DbgTransferPackets(void)
{
    RtosTaskSignalEvent(&dbgTask, DBG_TRANSFER);
}

void dbgSwapBuffer(void)
{
    bfSwPacket = 0;
    if (bfHwNo == 0)
    {
        bfHw = historyA;
        bfSw = historyB;
    }
    else
    {
        bfHw = historyB;
        bfSw = historyA;
    }
    bfHwNo = 1 - bfHwNo;
}

void dbgTransferStart(void)
{
    if (bfSwPacket > 0)
    {
        bfHwSize = bfSwPacket * sizeof(rfTrcvPacket_t);
        bfHwOffset = 0;

        dbgSwapBuffer();

        bfTransferBusy = 1;

        UartTxByte(1, '$');
        UartTxByte(1, '#');
        UartTxByte(1, bfHwSize & 0xFF);
        UartTxByte(1, bfHwSize >> 8);
        dbgTransferTick();
    }
}

void dbgTransferTick(void)
{
    uint16_t transferSize;
    uint8_t* transferBfPt;

    // End of buffer reached?
    if (bfHwOffset >= bfHwSize)
    {
        bfTransferBusy = 0;
        return;
    }

    // DMA busy?
    if (UartTxDmaStatus(1) == TRUE)
        return;

    // Cap each transfer segment to 2k
    if (bfHwSize >= 2048)
    {
        transferSize = 2048;
    }
    else
    {
        transferSize = bfHwSize;
    }

    // Calculate BF location.
    transferBfPt = ((uint8_t*)bfHw) + bfHwOffset;

    // Copy to DMA SRAM
    memcpy(dmaBf, transferBfPt, transferSize);

    // Offset buffer
    bfHwOffset += transferSize;

    // Transmit over uart using DMA
    UartTxDma(1, 1, __builtin_dmaoffset(dmaBf), transferSize);
}

void DbgTask(void)
{
    while(1)
    {
        UI16_t evt = RtosTaskWaitForEvent(
                            DBG_TICK |
                            DBG_TRANSFER);

        if (evt & DBG_TICK)
        {
            dbgTransferTick();
        }

        if (evt & DBG_TRANSFER)
        {
            dbgTransferStart();
        }
    }
}