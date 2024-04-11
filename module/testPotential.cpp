#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "Potential.h"


int main(){

    

    if(wiringPiSetup() == -1){return -1;}


    if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1){return -1;}

         
    
    BrightPotential bp;
    SpeedPotential sp;
    while(1){
        int bright = bp.getBright();
        int speed = sp.getSpeed();
        printf("Bright %d, Speed %d \n", bright, speed);

         delay(100);
    }

return 0;

}