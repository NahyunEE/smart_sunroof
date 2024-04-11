#include <stdio.h>
#include <stdlib.h> // exit 함수 사용을 위해 추가
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include "Btn.h"
#include "Potential.h"


#define BUTTON_PIN 8 // wiringPi 핀 번호 8, 물리적인 GPIO 2번 핀에 해당

#define WRITE_BUF_SIZE 10
#define MOTOR_OFF '0'
#define MOTOR_FORWARD '1'
#define MOTOR_BACKWARD '2'

char buf_to_GlassMotor[WRITE_BUF_SIZE] ={'9'};
char buf_to_ShieldMotor[WRITE_BUF_SIZE] = {'9'};

int main() {
    char option;
    int GlassDriver;
    int ShieldDriver;
    if (wiringPiSetup() == -1) {
        printf("wiringPiSetup failed. Exiting...\n");
        return 1;
    }

    if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1){return -1;}
    BrightPotential bp;
    SpeedPotential sp;
    GlassDriver = open("/dev/GlassMotorDriver", O_RDWR);
    ShieldDriver = open("/dev/ShieldMotorDriver", O_RDWR);
    
    Comfort_Mode_Btn(Comfort_Mode_Btn_Num);
    Light_Mode_Btn(Light_Mode_Btn_Num);
    Glass_Up_Btn(Glass_Up_Btn_Num);
    Glass_Down_Btn(Glass_Down_Btn_Num);
    Sheild_Up_Btn(Sheild_Up_Btn_Num);
    Sheild_Down_Btn(Sheild_Down_Btn_Num);
    Drive_Btn driveButton(Drive_Btn_Num);


    //Check Driver Connection is Valid
    if(GlassDriver == -1) {
        printf("Cannot Open Motor Driver File\n");
        return 0;
    }


    if(ShieldDriver == -1) {
        printf("Cannot Open Motor Driver File\n");
        return 0;
    }

    while(1) {

        driveButton.update();

        int bright = bp.getBright();
        int speed = sp.getSpeed();
        printf("Bright %d, Speed %d \n", bright, speed);


        printf("--------------------------\n");
        printf("      Select Option       \n");
        printf("      1. Glass Motor Off        \n");
        printf("      2. Glass Motor Forward    \n");
        printf("      3. Glass Motor Backward   \n");
        printf("      4. Shield Motor off        \n");
        printf("      5. Shield Motor Forward        \n");
        printf("      6. Shield Motor Backward        \n");
        printf("      7. Stop Both Motor        \n");
        printf("      8. End Test        \n");

        printf("--------------------------\n");

        scanf(" %c", &option);
        getchar(); // 개행 문자 소비

        switch(option) {
            case '1':
                buf_to_GlassMotor[0] = MOTOR_OFF;
                break;
            case '2':
                buf_to_GlassMotor[0] = MOTOR_FORWARD;
                break;
            case '3':
                buf_to_GlassMotor[0] = MOTOR_BACKWARD;
                break;

            case '4':
                buf_to_ShieldMotor[0] = MOTOR_OFF;
                break;
            
            case '5':
                buf_to_ShieldMotor[0] = MOTOR_FORWARD;
                break;
            
            case '6':
                buf_to_ShieldMotor[0] = MOTOR_BACKWARD;
                break;
            
            case '7':
                buf_to_ShieldMotor[0] = MOTOR_OFF;
                buf_to_GlassMotor[0] = MOTOR_OFF;
                break;

            case '8':
                buf_to_GlassMotor[0] = MOTOR_OFF;
                buf_to_ShieldMotor[0] = MOTOR_OFF;
                printf("Test Off\n");
                write(GlassDriver, buf_to_GlassMotor, 1);
                write(ShieldDriver,  buf_to_ShieldMotor, 1);
                close(GlassDriver);
                close(ShieldDriver);

                exit(1);
            default:
                printf("Enter Valid Option\n");
                continue; 
        }

        //Only Send MSB to Driver ( buf_to_GlassMotor [0])
        if(write(GlassDriver, buf_to_GlassMotor, 1) < 1) {
            printf("Error in Glass Motor Control\n");
            close(GlassDriver);
            return 0;
        }

        //Only Send MSB to Driver ( buf_to_ShieldMotor [0])
        if(write(ShieldDriver, buf_to_ShieldMotor, 1) < 1) {
            printf("Error in Sheild Motor Control\n");
            close(ShieldDriver);
            return 0;
        }



        printf("Command sent: %c\n", option);

        
    }

     close(GlassDriver);
     close(ShieldDriver);
    return 0;
}

