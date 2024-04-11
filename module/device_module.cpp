#include "device_module.h"


Device_driver::Device_driver(char *dv){
    device = open(dv,O_RDWR);
    memset(buf,0,sizeof(char)*BUF_SIZE);
}

Device_driver::~Device_driver(){
    close(device);
}

int Device_driver::write_dv(int val){
    sprintf(buf,"%d",val);
    write(device,buf,sizeof(buf));
}





uint8_t Switch::read(){
    return state;
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
