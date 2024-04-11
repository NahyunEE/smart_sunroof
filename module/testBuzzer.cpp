#include <stdio.h>
#include <wiringPi.h>

#include "Buzzer.h"

int main(){
    if (wiringPiSetup() == -1) {
        printf("wiringPiSetup failed. Exiting...\n");
        return 1;
    }
    Buzzer bz;
    while(1){
       // bz.SoundOn();
        delay(1000);
        bz.SoundOff();
        delay(1000);
        
    }
}