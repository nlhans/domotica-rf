#ifndef PROFILING_EXECUTIONTIME_H
#define PROFILING_EXECUTIONTIME_H
#include "stddefs.h"

#include "profiling/executiontime_project.h"

#ifdef EXEC_ENABLE
    #if EXEC_ENABLE == 1
        #define EXEC_COMPILE
    #endif
#endif

#ifdef EXEC_COMPILE
    #define execProfile(def) execTimeWatch( strConcat(EXEC_POINT_, def) );
#else 
    #define execProfile(def)
#endif

// table operations
#define execPointsTable(def, str) { str, 0, FALSE }, 
#define execPointsEnum(def, str) strConcat(EXEC_POINT_, def),

typedef enum ExecutionTimePoints_e
{
    executionTimeTable(execPointsEnum)
    NUM_OF_EXECUTION_POINTS
} ExecutionTimePoints_t;

void execTimeReset(void);
void execTimeWatch(ExecutionTimePoints_t datapoint);
void execTimePrint(void);

#endif