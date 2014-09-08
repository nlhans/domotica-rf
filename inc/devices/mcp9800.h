#ifndef MCP9800_h
#define MCP9800_h

#include "stddefs.h"

typedef enum Mcp9800Resolution_e
{
    Mcp9800_9bit  = 0,
    Mcp9800_10bit = 0b00100000,
    Mcp9800_11bit = 0b01000000,
    Mcp9800_12bit = 0b01100000,
} Mcp9800Resolution_t;


void Mcp9800Start(Mcp9800Resolution_t resolution);
uint8_t Mcp9800Ready(void);
uint16_t Mcp9800Read(void);

#endif