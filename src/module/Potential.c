#include "Potential.h"

void BrightPotential_init(BrightPotential* bp) {
    bp->channel = BrightChannel;
    bp->bright = 0;
    MCP3204_init(&bp->mpc);
    MCP3204_setChannel(&bp->mpc, bp->channel);
}

int BrightPotential_getBright(BrightPotential* bp) {
    bp->bright = MCP3204_readAnalogRead(&bp->mpc);
    return bp->bright;
}

void SpeedPotential_init(SpeedPotential* sp) {
    sp->channel = SpeedChannel;
    sp->speed = 0;
    MCP3204_init(&sp->mpc);
    MCP3204_setChannel(&sp->mpc, sp->channel);
}

int SpeedPotential_getSpeed(SpeedPotential* sp) {
    sp->speed = MCP3204_readAnalogRead(&sp->mpc);
    return sp->speed;
}