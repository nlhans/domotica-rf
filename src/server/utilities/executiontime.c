#include "utilities/executiontime.h"

typedef struct executionTimePoint_s
{
    const char * datapoint;
    uint32_t timestamp;
    bool called;
} executionTimePoint_t;
#ifdef EXEC_COMPILE
executionTimePoint_t points[NUM_OF_EXECUTION_POINTS] = {
    executionTimeTable(execPointsTable)
};
executionTimePoint_t* sortlist[NUM_OF_EXECUTION_POINTS];

void execTimeReset(void)
{
    uint8_t i = 0;
    //
    for (i = 0; i < NUM_OF_EXECUTION_POINTS; i++)
    {
        points[i].timestamp = 0;
        points[i].called = false;
    }
    execResetTimestamp();
}

void execTimeWatch(ExecutionTimePoints_t datapoint)
{
    uint8_t ind = (uint8_t) datapoint;
    //
    points[ind].called = true;
    points[ind].timestamp = execGetTimestamp();
}

void execTimeSort(void)
{
    executionTimePoint_t* swapper = NULL;
    uint8_t i = 0;
    uint8_t c = 0;

    // Sort the list
    for (i = 0; i < NUM_OF_EXECUTION_POINTS; i++)
    {
        sortlist[i] = points + i;
    }

    //
    do
    {
        c = 0;
        i = 0;
        while(i < NUM_OF_EXECUTION_POINTS - 1)
        {
            if(sortlist[i]->timestamp > sortlist[i+1]->timestamp)
            {
                c = 1;
                
                swapper = sortlist[i+1];

                sortlist[i+1] = sortlist[i];
                sortlist[i] = swapper;
            }
            i++;
        }
    } while(c != 0);
}

void execTimePrint(void)
{
    uint8_t i = 0;
    uint32_t diff = 0;
    
    execTimeSort();

    printf("-----------\n");
    for (i = 0; i < NUM_OF_EXECUTION_POINTS; i++)
    {
        if(sortlist[i]->called == false) continue;
        
        diff = sortlist[i]->timestamp - diff;

        printf("%04lu | +%04lu | %s\n",
                sortlist[i]->timestamp,
                diff,
                sortlist[i]->datapoint);
        
        diff = sortlist[i]->timestamp;

    }
    printf("-----------\n\n");

}
#else

void execTimeReset(void) {}
void execTimePrint(void) {}

#endif