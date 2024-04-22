#include "main.h"
#include "module/LCD.h"
#include "module/mode.h"
#include "module/interrupt_switch.h"
#include "module/data.h"



#define SER 23
#define RCLK 24
#define SRCLK 25
#define SAFE 0
#define UPDATE_HZ 500000
#define UPDATE_SAFE_HZ 200000
#define UPDATE_HZ_TEMP 1000000000000
 
// the event counter

/*
D. Thiebaut
based on isr.c from the WiringPi library, authored by Gordon Henderson
https://github.com/WiringPi/WiringPi/blob/master/examples/isr.c
Compile as follows:
gcc -o isr4pi isr4pi.c -lwiringPi
Run as follows:
sudo ./isr4pi
*/
 

// -------------------------------------------------------------------------
// myInterrupt:  called every time an event occurs





int initial_code();

int main(void) {
  // sets up the wiringPi library
  int errno_in = initial_code();
  int last_update_time;
  int last_update_time_safe;

  if(errno_in==-1){
    return -1;
  }
  
  printf("Ready\n");
  while(!Drive_state);
  //Scheduling
  while(Drive_state){
    if(micros()-last_update_time > UPDATE_HZ){
      last_update_time = update_data();
    }
    if(micros()-last_update_time_safe > UPDATE_SAFE_HZ){
      last_update_time_safe = update_safe_data();
    }
    if((safe_state = safe_check()) == SAFE){
      switch(state){
        case USER_MODE:
          user_mode();
          break;
        case CLEAN_MODE:
          clean_mode();
          break;
        case BRIGHT_MODE:
          bright_mode();
          break;
      }
    }
    else{
      safe_mode(safe_state);
    }
    updateLCD(state, safe_state, user_speed_level, user_bright_level);
  }
  closing();
  return 0;
}

int initial_code(){

  if(wiringPiSetup() == -1){return -1;}
  if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1){return -1;}
  if((fd = wiringPiI2CSetup(ARDUINO_SLAVE)) ==-1){return -1;}
  if((fd_lcd = wiringPiI2CSetup(I2C_ADDR)) == -1){return -1;}
  else {printf("##############FD: %d\n", fd);}
  

  lcd_init();

  pinMode(Clean_Mode_Btn_Num,INPUT);
  pullUpDnControl(Clean_Mode_Btn_Num,PUD_DOWN);
  pinMode(Bright_Mode_Btn_Num,INPUT);
  pullUpDnControl(Bright_Mode_Btn_Num,PUD_DOWN);
  pinMode(Glass_Up_Btn_Num,INPUT);
  pullUpDnControl(Glass_Up_Btn_Num,PUD_DOWN);
  pinMode(Glass_Down_Btn_Num,INPUT);
  pullUpDnControl(Glass_Down_Btn_Num,PUD_DOWN);
  pinMode(Sheild_Up_Btn_Num,INPUT);
  pullUpDnControl(Sheild_Up_Btn_Num,PUD_DOWN);
  pinMode(Sheild_Down_Btn_Num,INPUT);
  pullUpDnControl(Sheild_Down_Btn_Num,PUD_DOWN);
  pinMode(Drive_Btn_Num,INPUT);
  pullUpDnControl(Drive_Btn_Num,PUD_DOWN);

  if(wiringPiISR(Glass_Up_Btn_Num,INT_EDGE_BOTH,&Interrupt_Glass_up)<0){
    printf("wiringPi Fali\n");
  }
  if(wiringPiISR(Glass_Down_Btn_Num,INT_EDGE_BOTH,&Interrupt_Glass_down)<0){
    printf("wiringPi Fali\n");
  }
  if(wiringPiISR(Sheild_Up_Btn_Num,INT_EDGE_BOTH,&Interrupt_Sheild_up)<0){
    printf("wiringPi Fali\n");
  }
  if(wiringPiISR(Sheild_Down_Btn_Num,INT_EDGE_BOTH,&Interrupt_Sheild_down)<0){
    printf("wiringPi Fali\n");
  }
  if(wiringPiISR(Bright_Mode_Btn_Num,INT_EDGE_BOTH,&Interrupt_Bright_Mode)<0){
    printf("wiringPi Fali\n");
  }
  if(wiringPiISR(Clean_Mode_Btn_Num,INT_EDGE_BOTH,&Interrupt_Clean_Mode)<0){
    printf("wiringPi Fali\n");
  }
  if(wiringPiISR(Drive_Btn_Num,INT_EDGE_BOTH,&Interrupt_Drive_Mode)<0){
    printf("wiringPi Fali\n");
  }
    // ADC Potential
  BrightPotential_init(&bp);
  SpeedPotential_init(&sp);

  //Step Moter
  GlassDriver = open("/dev/GlassMotorDriver", O_RDWR);
  ShieldDriver = open("/dev/ShieldMotorDriver", O_RDWR);
  TiltDriver = open("/dev/TiltMotorDriver", O_RDWR);

  update_data();
  update_safe_data();

return 0;

}


