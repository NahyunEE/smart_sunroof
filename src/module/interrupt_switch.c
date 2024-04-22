#include "interrupt_switch.h"


void Interrupt_Glass_up(void) {
  static int flag = 0;
  static int now = 0;
  state = 0;
  int cur = digitalRead(Glass_Up_Btn_Num);
  // printf("Glass up interrupt %d %d\n",Glass_up_state,Glass_down_state);
  if(cur && !flag){
    now = micros();
    Glass_up_state = 1;
    Glass_down_state = 0;
    // printf("Glass up on interrupt %d %d\n",Glass_up_state,Glass_down_state);
    
  }
  if(!cur && flag){
    if(micros()-now>SWITCH_TH){
      Glass_up_state = 0;
      // printf("Glass up off interrupt %d %d\n",Glass_up_state,Glass_down_state);
    }
    else{
      Glass_up_state = 1;
      Glass_down_state = 0;
      // printf("Glass up short interrupt %d %d\n",Glass_up_state,Glass_down_state);
    }
  }
  flag = cur;
}

void Interrupt_Glass_down(void) {
  static int flag = 0;
  static int now = 0;
  state = 0;
  int cur = digitalRead(Glass_Down_Btn_Num);
  // printf("Glass down interrupt %d %d\n",Glass_up_state,Glass_down_state);
  if(cur && !flag){
    now = micros();
    Glass_down_state = 1;
    Glass_up_state = 0;
    // printf("Glass down on interrupt %d %d\n",Glass_up_state,Glass_down_state);
  }
  if(!cur && flag){
    if(micros()-now>SWITCH_TH){
      Glass_down_state = 0;
      // printf("Glass down off interrupt %d %d\n",Glass_up_state,Glass_down_state);
    }
    else{
      Glass_down_state = 1;
      Glass_up_state = 0;
      // printf("Glass down short interrupt %d %d\n",Glass_up_state,Glass_down_state);
    }
  }
  flag = cur;
}

void Interrupt_Sheild_up(void) {
  static int flag = 0;
  static int now = 0;
  state = 0;
  int cur = digitalRead(Sheild_Up_Btn_Num);
  // printf("Sheild up interrupt %d %d\n",Sheild_up_state,Sheild_down_state);
  if(cur && !flag){
    now = micros();
    Sheild_up_state = 1;
    Sheild_down_state = 0;
    // printf("Sheild up on interrupt %d %d\n",Sheild_up_state,Sheild_down_state);
  }
  if(!cur && flag){
    if(micros()-now>SWITCH_TH){
      Sheild_up_state = 0;
      // printf("Sheild up off interrupt %d %d\n",Sheild_up_state,Sheild_down_state);
    }
    else{
      Sheild_up_state = 1;
      Sheild_down_state = 0;
      // printf("Sheild up short interrupt %d %d\n",Sheild_up_state,Sheild_down_state);
    }
  }
  flag = cur;
}

void Interrupt_Sheild_down(void) {
  volatile static int flag = 0;
  volatile static int now = 0;
  state = 0;
  int cur = digitalRead(Sheild_Down_Btn_Num);
  // printf("Sheild down interrupt %d %d\n",Sheild_up_state,Sheild_down_state);
  if(cur && !flag){
    now = micros();
    Sheild_down_state = 1;
    Sheild_up_state = 0;
    // printf("Sheild down on interrupt %d %d\n",Sheild_up_state,Sheild_down_state);
  }
  if(!cur && flag){
    if(micros()-now>SWITCH_TH){
      Sheild_down_state = 0;
      // printf("Sheild down off interrupt %d %d\n",Sheild_up_state,Sheild_down_state);
    }
    else{
      Sheild_down_state = 1;
      Sheild_up_state = 0;
      // printf("Sheild down short interrupt %d %d\n",Sheild_up_state,Sheild_down_state);
    }
  }
  flag = cur;
}

void Interrupt_Clean_Mode(void) {
  volatile static int flag = 0;
  volatile int cur = digitalRead(Clean_Mode_Btn_Num);
  // printf("State 1 interrupt %d %d %d\n",state, cur, flag);
  if(cur && !flag){
    state = 1;
    // printf("State 1 on interrupt %d \n",state);
  }
  flag = cur;
}

void Interrupt_Bright_Mode(void) {
  volatile static int flag = 0;
  volatile int cur = digitalRead(Bright_Mode_Btn_Num);
  // printf("State 2 interrupt %d %d %d \n",state, cur, flag);
  if(cur && !flag){
    state = 2;
    // printf("State 2 on interrupt %d \n",state);
  }
  flag = cur;
}

void Interrupt_Drive_Mode(void) {
  volatile static int flag = 0;
  volatile int cur = digitalRead(Drive_Btn_Num);
  if(cur && !flag){
    Drive_state = 1;
  }
  if(!cur && flag){
    Drive_state = 0;
  }
  flag = cur;
}