#include "MCP3204.h"


void MCP3204_init(MCP3204* mcp) {
    mcp->channel = 0;
    mcp->analogRead = 0;
    pinMode(SPI_CS, OUTPUT);
}

void MCP3204_setChannel(MCP3204* mcp, int _channel) {
    mcp->channel = _channel;
}

int MCP3204_getChannel(MCP3204* mcp) {
    return mcp->channel;
}

int MCP3204_readAnalogRead(MCP3204* mcp) {
    unsigned char buf[3];
    buf[0] = 0x06 | ((mcp->channel & 0x07) >> 2);
    buf[1] = ((mcp->channel & 0x07) << 6);
    buf[2] = 0x00;
    digitalWrite(SPI_CS, LOW);
    wiringPiSPIDataRW(SPI_CHANNEL, buf, 3);
    buf[1] = 0x0F & buf[1];
    mcp->analogRead = (buf[1] << 8) | buf[2];
    digitalWrite(SPI_CS, HIGH);
    return mcp->analogRead;
}
