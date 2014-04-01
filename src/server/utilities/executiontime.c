#include "utilities/executiontime.h"

typedef struct executionTimePoint_s
{
    const char * datapoint;
    UI32_t timestamp;
    bool_t called;
} executionTimePoint_t;
#ifdef EXEC_COMPILE
executionTimePoint_t points[NUM_OF_EXECUTION_POINTS] = {
    executionTimeTable(execPointsTable)
};
executionTimePoint_t* sortlist[NUM_OF_EXECUTION_POINTS];

void execTimeReset(void)
{
    UI08_t i = 0;
    //
    for (i = 0; i < NUM_OF_EXECUTION_POINTS; i++)
    {
        points[i].timestamp = 0;
        points[i].called = FALSE;
    }
    execResetTimestamp();
}

void execTimeWatch(ExecutionTimePoints_t datapoint)
{
    UI08_t ind = (UI08_t) datapoint;
    //
    points[ind].called = TRUE;
    points[ind].timestamp = execGetTimestamp();
}

void execTimeSort(void)
{
    executionTimePoint_t* swapper = NULL;
    UI08_t i = 0;
    UI08_t c = 0;

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
    UI08_t i = 0;
    UI32_t diff = 0;
    
    execTimeSort();

    printf("-----------\n");
    for (i = 0; i < NUM_OF_EXECUTION_POINTS; i++)
    {
        if(sortlist[i]->called == FALSE) continue;
        
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