#ifndef BSP_INTERRUPT
#define BSP_INTERRUPT

#include <stdint.h>
#include "stddefs.h"

typedef bool (*ExtIntHandler_t) (uint8_t ind);

typedef struct ExtIntInstance_s
{
    ExtIntHandler_t callback;
} ExtIntInstance_t;

void ExtIntInit(void);
void ExtIntDeinit(void);

void ExtIntSetup(uint8_t ind, ExtIntHandler_t callback, bool fallingEdge, uint8_t prio);


#endif
