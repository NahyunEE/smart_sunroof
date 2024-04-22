#include "mode.h"

void closing(){
    while(glass_moter_cur) glass_moter_cur = write(GlassDriver,"2",1);
    while(shield_moter_cur) shield_moter_cur = write(ShieldDriver,"2",1);
    while(tilt_moter_cur) tilt_moter_cur = write(TiltDriver,"2",1);
}

void user_mode(){
  if(tilt_moter_cur){
    tilt_moter_cur = write(TiltDriver,"2",1);
  }
  else{
    if(Glass_up_state){
      if(glass_state != 1){
        glass_moter_cur = write(GlassDriver,"1",1);
        glass_state = 1;
      }
    }
    else if(Glass_down_state){
      if(glass_state != 2){
        glass_moter_cur = write(GlassDriver,"2",1);
        glass_state = 2;
      }
    }
    else{
      if(glass_state != 0){
        glass_moter_cur = write(GlassDriver,"0",1);
        glass_state = 0;
      }
    }
    if(Sheild_up_state){
      if(shield_state != 1){
        shield_moter_cur = write(ShieldDriver,"1",1);
        shield_state = 1;
      }
    }
    else if(Sheild_down_state){
      if(shield_state != 2){
        shield_moter_cur = write(ShieldDriver,"2",1);
        shield_state = 2;
      }
    }
    else{
      if(shield_state != 0){
        shield_moter_cur = write(ShieldDriver,"0",1);
        shield_state = 0;
      }
    }
  }
}

int safe_check(){
  if(ultra_sonic_length < LENGTH_THRESH){
    return 2;
  }
  if(water_level ==1){
    return 1;
  }
  if(user_speed_level > 80){
    return 1;
  }
  return 0;
}


void clean_mode(){
  if(glass_moter_cur > 0){
    glass_moter_cur = write(GlassDriver,"2",1);
  }
  else if (out_dust_level > OUT_DUST_THRESH) {
  // else if (0) {
    if(tilt_moter_cur > 0){
      tilt_moter_cur = write(TiltDriver,"2",1);
    }
    else{
      tilt_moter_cur = write(TiltDriver,"0",1);
    }
  }
  else if(in_dust_level > IN_DUST_THRESH){
    if(tilt_moter_cur < TILT_MAX){
      tilt_moter_cur = write(TiltDriver,"1",1);
    }
    else{
      tilt_moter_cur = write(TiltDriver,"0",1);
    }
  }
  else{
    tilt_moter_cur = write(TiltDriver,"2",1);
  }
}

void bright_mode()
{
    if (user_bright_level > in_bright_level) {
      if(shield_state !=1){
        shield_moter_cur = write(ShieldDriver,"1",1);
        shield_state = 1;
      }
    }
    else if(user_bright_level < in_bright_level){
      if(shield_state !=2){
        shield_moter_cur = write(ShieldDriver,"2",2);
        shield_state = 2;
      }
    }
    else{
      if(shield_state !=0){
        shield_moter_cur = write(ShieldDriver,"0",2);
        shield_state = 0;
      }
    }
}

void safe_mode(int safe_state){
  switch(safe_state){
        case 1:
          glass_moter_cur = write(GlassDriver,"2",1);
          shield_moter_cur = write(ShieldDriver,"2",1);
          tilt_moter_cur = write(TiltDriver,"2",1);
          glass_state = 2;
          shield_state = 2;
          break;
        case 2:
          glass_moter_cur = write(GlassDriver,"0",1);
          shield_moter_cur = write(ShieldDriver,"0",1);
          tilt_moter_cur = write(TiltDriver,"0",1);
          glass_state = 0;
          shield_state = 0;
          break;
  } 
}