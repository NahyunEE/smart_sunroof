#include "data.h"

extern int fd;
extern BrightPotential bp;
extern SpeedPotential sp;

int update_data(){
  static int last_update_time;
  last_update_time = micros();
  in_dust_level = getSensorData(IN_Dust_Header);
  in_bright_level = getSensorData(IN_Bright_Header);
  in_bright_level = ((CLOSE-in_bright_level)/BRIGHT_MOD);
  out_dust_level = getSensorData(OUT_Dust_Header);
  user_bright_level = (BrightPotential_getBright(&bp));
  user_speed_level = SpeedPotential_getSpeed(&sp);
  user_bright_level = (user_bright_level/(ADC_MAX/BRIGHT_MAX));       
  user_speed_level = user_speed_level/(ADC_MAX/SPEED_MAX); 

  return last_update_time;
}

int update_safe_data(){
  static int last_update_time;
  last_update_time = micros();
  water_level = getSensorData(Water_Header);
  ultra_sonic_length = getSensorData(ULTRA_SONIC_Header);
  return last_update_time;
}


int getSensorData(int req_num)  
{  
  int count=0;
    while (1) { 
        wiringPiI2CWrite(fd, req_num);

        for (int i = 0; i < 4; i++) {
            data_0 = wiringPiI2CRead(fd);

            // header
            if(i==0){
              if (data_0 == req_num) {
                header_flag = 1;
                len = 0;
                check_error = 0;
                continue;
              }
              else {
                  i--;
                  count++;
                  if(count==1000){
                    wiringPiI2CWrite(fd, req_num);
                    count = 0;
                  }
                  continue;
              }
            }
            

            // tail & Error check : sum check
            if (i == 3) {
                tail_flag = 1;
                header_flag = 0;
                // if (data_0 != check_error) {
                //     i = 0;
                //     continue;
                // }
            }

            if (header_flag == 1) {
                check_error += data_0;

                if (len == 0) value = data_0 * 100;
                else value += data_0;

                len++;
            }

            if (tail_flag == 1) {
                tail_flag = 0; // tail initailize

                return value;
            }
        }
    }  
}

