#ifndef MODE_H
#define MODE_H

#define USER_MODE   0
#define CLEAN_MODE  1
#define BRIGHT_MODE 2

#define OUT_DUST_THRESH 1
#define IN_DUST_THRESH 240
#define TEMP_THRESH 25
#define LENGTH_THRESH 30

#define TILT_MAX 2048
#define MOTER_MAX 8192

extern int glass_moter_cur;
extern int shield_moter_cur;
extern int tilt_moter_cur;

extern int GlassDriver;
extern int ShieldDriver;
extern int TiltDriver;

extern int glass_state;
extern int shield_state;

extern int water_level;
extern int in_dust_level;
extern int in_bright_level;
extern int out_dust_level;
extern int ultra_sonic_length;
extern int user_bright_level;
extern int user_speed_level;

extern int Glass_up_state;
extern int Glass_down_state;
extern int Sheild_up_state;
extern int Sheild_down_state;
extern int state;
extern int Drive_state;


void user_mode();
void clean_mode();
void bright_mode();
int safe_check();
void closing();
void safe_mode(int);

#endif