#ifndef INTER_H
#define INTER_H

#define Clean_Mode_Btn_Num 0 //GPIO17 in RaspberryPI
#define Bright_Mode_Btn_Num 2 //GPIO27 in RaspberryPI
#define Glass_Up_Btn_Num 3 //GPIO22 in RaspberryPI
#define Glass_Down_Btn_Num 30 //GPIO0 in RaspberryPI
#define Sheild_Up_Btn_Num 21//GPIO5 in RaspberryPI
#define Sheild_Down_Btn_Num 22 //GPIO6 in RaspberryPI
#define Drive_Btn_Num 23 //GPIO13 in RaspberryPI
#define SWITCH_TH 200000

extern int Glass_up_state;
extern int Glass_down_state;
extern int Sheild_up_state;
extern int Sheild_down_state;
extern int state;
extern int Drive_state;


void Interrupt_Glass_up(void);
void Interrupt_Glass_down(void);
void Interrupt_Sheild_up(void);
void Interrupt_Sheild_down(void);
void Interrupt_Clean_Mode(void);
void Interrupt_Bright_Mode(void);
void Interrupt_Drive_Mode(void);

#endif