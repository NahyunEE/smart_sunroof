#include <wiringPi.h>
#include <wiringPiSPI.h>

#ifndef MCP_H

#define MCP_H
#define SPI_CS 6
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000

typedef struct MCP3204 {
    int channel;
    int analogRead;
} MCP3204;

void MCP3204_init(MCP3204* mcp);

void MCP3204_setChannel(MCP3204* mcp, int _channel);

int MCP3204_getChannel(MCP3204* mcp);

int MCP3204_readAnalogRead(MCP3204* mcp);

#endif