#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringShift.h>
#include <fcntl.h>
#include <unistd.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include "module/Potential.h"

#ifndef MAIN_H
#define MAIN_H

#define I2C_ADDR   0x27
#define ARDUINO_SLAVE 0x10


int fd;
int fd_lcd;

int Glass_up_state;
int Glass_down_state;
int Sheild_up_state;
int Sheild_down_state;
int state;
int Drive_state;
int safe_state;

int water_level;
int in_dust_level;
int in_bright_level;
int out_dust_level;
int ultra_sonic_length;
int user_bright_level;
int user_speed_level;

int glass_moter_cur;
int shield_moter_cur;
int tilt_moter_cur;

int GlassDriver;
int ShieldDriver;
int TiltDriver;

int glass_state;
int shield_state;

BrightPotential bp;
SpeedPotential sp;

#endif
