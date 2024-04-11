#include <stdio.h>
#include <wiringPi.h>

#define BUZZER_PIN_NUM 25 // GPIO26 in RaspberryPi

class Buzzer{

    private:
        int PinNum;

    public:

    void setPinNum(int _pinNum){
        this ->PinNum = _pinNum;        
    }

    Buzzer(){
        this->PinNum = BUZZER_PIN_NUM;
        pinMode(this->PinNum, OUTPUT);
    }

    void SoundOn(){
         digitalWrite(this->PinNum, HIGH);        
    }  

    void SoundOff(){
        digitalWrite(this->PinNum, LOW);
    }


};