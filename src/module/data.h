#ifndef DATA_H
#define DATA_H

#include "Potential.h"

#define Water_Header 110
#define IN_Temper_Header 120
#define IN_Dust_Header 130
#define IN_Bright_Header 140

#define ULTRA_SONIC_Header 210
#define OUT_Temper_Header 220
#define OUT_Dust_Header 230
#define OUT_Bright_Header 240



#define OPEN 250
#define CLOSE 900
#define BRIGHT_MAX 5
#define BRIGHT_MOD ((CLOSE-OPEN)/BRIGHT_MAX)
#define ADC_MAX 4096
#define SPEED_MAX 120



extern int water_level;
extern int in_dust_level;
extern int in_bright_level;
extern int out_dust_level;
extern int ultra_sonic_length;
extern int user_bright_level;
extern int user_speed_level;


static int header_flag = 0; // header flag
static int tail_flag = 0; // tail flag
static int len = 0; // length of data
static int answer = 0;
static int data_0 = 0; // sending data
static int value = 0; // calculate sending data
static int check_error = 0;

int update_data();
int update_safe_data();
int getSensorData(int req_num);

#endif