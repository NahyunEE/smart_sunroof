#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "MCP3204.h"

#ifndef POTENT_H

#define POTENT_H

#define BrightChannel 0
#define SpeedChannel 1

typedef struct {
    int channel;
    int bright;
    MCP3204 mpc;
} BrightPotential;

typedef struct {
    int channel;
    int speed;
    MCP3204 mpc;
} SpeedPotential;

void BrightPotential_init(BrightPotential* bp);
int BrightPotential_getBright(BrightPotential* bp);
void SpeedPotential_init(SpeedPotential* sp);
int SpeedPotential_getSpeed(SpeedPotential* sp);

#endif