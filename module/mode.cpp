#include "mode.h"

template <typename T>
void MainController::moderun(T * mode){
    mode->run();
}

bool MainController::isdrive(){
    return drive;
}
uint16_t MainController::getspeed(){
    return speed;
}
void MainController::modifydrive(){

}



void Usermode::run(Device_controller * dc){
    if(dc->glass_opswtich->read()!=NOT_PUSH){
        if(dc->glass_moter->ismax()){
            dc->glass_moter->run(0);
            if(dc->glass_opswtich->read()==PUSH){
            dc->glass_opswtich->modifystate(NOT_PUSH);
            }
        }
        else{
            dc->glass_moter->run(1);
        }
    }
    if(dc->glass_clswtich->read()!=NOT_PUSH){
        if(dc->glass_moter->ismin()){
            dc->glass_moter->run(0);
            if(dc->glass_clswtich->read()==PUSH){
            dc->glass_clswtich->modifystate(NOT_PUSH);
            }
        }
        else{
            dc->glass_moter->run(-1);
        }
    }
    if(dc->blind_opswtich->read()!=NOT_PUSH){
        if(dc->glass_moter->ismax()){
            dc->glass_moter->run(0);
            if(dc->blind_opswtich->read()==PUSH){
            dc->blind_opswtich->modifystate(NOT_PUSH);
            }
        }
        else{
            dc->glass_moter->run(1);
        }
    }
    if(dc->blind_clswtich->read()!=NOT_PUSH){
        if(dc->glass_moter->ismin()){
            dc->glass_moter->run(0);
            if(dc->blind_clswtich->read()==PUSH){
            dc->blind_clswtich->modifystate(NOT_PUSH);
            }
        }
        else{
            dc->glass_moter->run(-1);
        }
    }
    

}

void Cleanmode::run(Device_controller * dc,Sensordata * sensor){
    if(!(dc->glass_moter->ismin())){
        dc->glass_moter->run(-1);
    }
    else if(sensor->getoutdust() > outdustthresh ){
        if(dc->tilting_moter->ismin()){
            dc->tilting_moter->run(0);
        }
        else{
            dc->tilting_moter->run(-1);
        }
    }
    else if(sensor->getindust() > industthresh || sensor->gettemper() > temperthresh){
        if(dc->tilting_moter->ismax()){
            dc->tilting_moter->run(0);
        }
        else{
            dc->tilting_moter->run(1);
        }
    }
}

void Brightmode::run(Device_controller * dc,Sensordata * sensor){
    if(sensor->getbright() < userbright ){
        if(dc->blind_moter->ismax()){
            dc->blind_moter->run(0);
        }
        else{
            dc->blind_moter->run(1);
        }
    }
    else{
        if(dc->blind_moter->ismin()){
            dc->blind_moter->run(0);
        }
        else{
            dc->blind_moter->run(-1);
        }
    }
}

