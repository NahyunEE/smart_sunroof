#include "../module/device_module.h"
#include "../module/mode.h"
#include "../module/state_sensor.h"
#include <wiringPi.h>

#define Clean_Mode_Btn_Num 0 //GPIO17 in RaspberryPI
#define Bright_Mode_Btn_Num 2 //GPIO27 in RaspberryPI
#define Glass_Up_Btn_Num 3 //GPIO22 in RaspberryPI
#define Glass_Down_Btn_Num 30 //GPIO0 in RaspberryPI
#define Sheild_Up_Btn_Num 21//GPIO5 in RaspberryPI
#define Sheild_Down_Btn_Num 22 //GPIO6 in RaspberryPI
#define Drive_Btn_Num 23 //GPIO13 in RaspberryPI
//타이머 인터럽트 코드



uint32_t rateTimer;
uint32_t now;
uint32_t controlPeriod = 1000000; // 1초

int main() {
    if (wiringPiSetup() == -1)
        return 1;
    rateTimer = micros();
    now = rateTimer;
    int counter = 0;
    while (1) {
        
    }
    return 0;
}


int main() {
    if (wiringPiSetup() == -1)
        return 1;
    MainController con;
    Usermode user;
    Cleanmode clean;
    Brightmode bright;
    State state;
    Sensordata sensor(0x04);
    Device_controller dc("","","",0,0,0,0,0,0);
    Switch::set_ISR1(Clean_Mode_Btn_Num, &dc);
    Switch::set_ISR1(Bright_Mode_Btn_Num, &dc);
    Switch::set_ISR2(Glass_Up_Btn_Num, &dc);
    Switch::set_ISR2(Glass_Down_Btn_Num, &dc);
    Switch::set_ISR2(Sheild_Up_Btn_Num, &dc);
    Switch::set_ISR2(Sheild_Down_Btn_Num, &dc);
    rateTimer = micros();
    while(true){
        now = micros();
        if ((now - rateTimer) > controlPeriod){
            sensor.updatedata();
            rateTimer = now; // 현재 시간을 다시 rateTimer에 할당하여 1초를 측정하기 위해 초기화합니다.
        }
        if(state.issafety()){

            switch(state.getmodestate()){
                case USERMODE:
                    con.moderun(&user);
                    break;
                case CLEANMODE:
                    con.moderun(&clean);
                    break;
                case BRIGHTMODE:
                    con.moderun(&bright);
                    break;
            }
        }
    }
    
    return 0;
}