#ifndef BSP_INTERRUPT
#define BSP_INTERRUPT

#include "stddefs.h"

typedef  void (*ExtIntHandler_t) (UI08_t ind);

typedef struct ExtIntInstance_s
{
    ExtIntHandler_t callback;
} ExtIntInstance_t;

void ExtIntInit(void);
void ExtIntSetup(UI08_t ind, ExtIntHandler_t callback, bool_t fallingEdge, UI08_t prio);


#endif