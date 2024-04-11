#include <stdio.h>  
#include <errno.h>  
#include <wiringPiI2C.h> 
#include "state_sensor.h"
#include "device_module.h"

#define Water_Header 110
#define Temper_Header 120
#define Dust_Header 130
#define Bright_Header 140

#define Tail 255


class Sensordata{
    private:
        uint32_t bright;
        uint32_t temper;
        uint32_t dust;
        uint32_t length;
        uint32_t water;
    public:
        void update(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
        uint32_t getbright();
        uint32_t gettempper();
        uint32_t getdust();
        uint32_t getlength();
        uint32_t getwater();
        void modifybright(uint32_t);
        void modifytemper(uint32_t);
        void modifydust(uint32_t);
        void modifylength(uint32_t);
        void modifywater(uint32_t);
};


uint8_t State::getmodestate(){
    this.modifymodestate();
    return modestate;
}
void State::updatedata(){
    modifyvalue(Water_Header);
    modifyvalue(Temper_Header);
    modifyvalue(Dust_Header);
    modifyvalue(Bright_Header);
    ///// TODO :: modifyvalue(Water_Header);
}
bool State::issafety(){
    return this.safestate
}

void State::modifymodestate(Device_controller * dc){
    if(dc->blmd_swtich){
        modestate = 1;
    }
    else if(dc->clmd_switch){
        modestate = 2;
    }
    else{
        modestate = 0;
    }
}

void State::modifysafestate(Sensordata *sensor){
    if(sensor->getwater()){
        this.safestate = 0;
    }
    else if(sensor->getlength()>this.lengthresh){
        this.safestate = 0;
    }
    else if(sensor->getspeed()>this.speedthresh){
        this.safestate = 0;
    }
    else{
        this.safestate = 1;
    }
}

Sensordata::Sensordata(int fd_ad)
{
    fd = wiringPiI2CSetup(fd_ad);
}

uint32_t Sensordata::getbright(){
    return bright;
}
uint32_t Sensordata::gettemper(){
    return temper;
}
uint32_t Sensordata::getindust(){
    return indust;
}
uint32_t Sensordata::getoutdust(){
    return outdust;
}
uint32_t Sensordata::getlength(){
    return length;
}
uint32_t Sensordata::getwater(){
    return water;
}
uint32_t Sensordata::getspeed(){
    return speed;
}
uint32_t Sensordata::getuserbright(){
    return userbright;
}


void Sensordata::modifyvalue(uint32_t header)
{
    int head_flg = 0; // header flag
    int tail = 0; // tail flag
    int term = 0;

    int Recv_data = 0; // sending data
    int value = 0; // calculate sending data

    wiringPiI2CWrite(fd, header);

    for (int i = 0; i < 4; i++) {
        Recv_data = wiringPiI2CRead(fd);

        // header
        if (Recv_data == header) {
            head_flg = 1;
            continue;
        }

        // tail & Error check
        if (Recv_data == Tail) {
            tail = 1;
            head_flg = 0;
        }

        if (head_flg == 1) {
            if (term == 0) value = Recv_data * 100;
            else value += Recv_data;
            term++;
        }

        if (tail == 1) {
            printf("%d\n", value);
            switch(header){
                case Water_Header:
                    water = value;
                    break;
                case Temper_Header:
                    temper = value;
                    break;
                case Indust_Header: // TODO Header 만들기
                    indust = value;
                    break;
                case Bright_Header:
                    bright = value;
                    break;
                case Outdust_Header: // TODO
                    outdust = value;
                    break;
                case default:
                    break;
            }
        }
    }
}
