#include "device_module.h"
#include <wiringPi.h>

Device_driver::Device_driver(char *dv){
    device = open(dv,O_RDWR);
    memset(buf,0,sizeof(char)*BUF_SIZE);
}

Device_driver::Device_driver(int pin){
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_DOWN);
}

Device_driver::~Device_driver(){
    close(device);
}

int Device_driver::write_dv(int val){
    sprintf(buf,"%d",val);
    write(device,buf,sizeof(buf));
}

uint8_t Device_driver::getdevice(){
    return device;
}

Switch::Switch(uint8_t pin):Device_driver(pin){}

void Switch::interrupt_handlr(void * dc){
    Device_controller * dc_ = reinterpret_cast<Device_controller*>(dc);
    static uint8_t flag_before = 0b00;
    uint8_t pin[2] = {dc_->clmd_swtich->getdevice(),dc_->blmd_swtich->getdevice()};
    static uint8_t flag =0b00;

    for(int i=0;i<2;i++){
        flag |= digitalRead(pin[i])<<i;            
    }
    if(flag!=3){
        dc_->clmd_swtich->modifystate(!!(flag & 1));
        dc_->blmd_swtich->modifystate(!!(flag & 2));
    }
}

void Switch::set_ISR1(int pin,Device_controller * dc){
    wiringPiISR(pin, INT_EDGE_FALLING, &Switch::interrupt_handlr, dc);
}


void Switch::set_ISR2(int pin,Device_controller * dc){
    wiringPiISR(pin, INT_EDGE_FALLING, &Switch::interrupt_handlr_falling2, dc);
    wiringPiISR(pin, INT_EDGE_RISING, &Switch::interrupt_handlr_rising2, dc);
}


uint8_t Switch::read(){
    return state;
}
void Switch::modifystate(uint32_t val){
    state = val;
}

int Moter::ismax(){
    return currunt==max;
}

int Moter::ismin(){
    return currunt==min;
}

void Moter::run(int dir){
    write_dv(dir);
}


Device_controller::Device_controller(char * glass,char * blind,char * tilt,
                            int glass_op,int glass_cl,
                            int blind_op,int blind_cl,
                            int tilt_op,int tilt_cl){
    glass_moter = new Moter(MOV_MAX, glass);
    blind_moter = new Moter(MOV_MAX, blind);
    tilting_moter = new Moter(MOV_MAX, tilt);
    glass_opswtich = new Switch(glass_op);
    glass_clswtich = new Switch(glass_cl);
    blind_opswtich = new Switch(blind_op);
    blind_clswtich = new Switch(blind_cl);
    clmd_switch = new Switch(tilt_op);
    blmd_swtich = new Switch(tilt_cl);
}

Device_controller::~Device_controller(){
    delete glass_moter;
    delete blind_moter;
    delete tilting_moter;
    delete glass_opswtich;
    delete glass_clswtich;
    delete blind_opswtich;
    delete blind_clswtich;
    delete clmd_switch;
    delete blmd_swtich;
}