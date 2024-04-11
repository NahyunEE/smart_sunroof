#include <stdio.h>
#include <wiringPi.h>

#include "Btn.h"

#define BUTTON_PIN 8 // wiringPi 핀 번호 8, 물리적인 GPIO 2번 핀에 해당

#define Comfort_Mode_Btn_Num 0 //GPIO17 in RaspberryPI
#define Light_Mode_Btn_Num 2 //GPIO27 in RaspberryPI
#define Glass_Up_Btn_Num 3 //GPIO22 in RaspberryPI
#define Glass_Down_Btn_Num 30 //GPIO0 in RaspberryPI
#define Sheild_Up_Btn_Num 21//GPIO5 in RaspberryPI
#define Sheild_Down_Btn_Num 22 //GPIO6 in RaspberryPI
#define Drive_Btn_Num 23 //GPIO13 in RaspberryPI

int main(void) {
    // wiringPi 라이브러리 초기화
    if (wiringPiSetup() == -1) {
        printf("wiringPiSetup failed. Exiting...\n");
        return 1;
    }

    Comfort_Mode_Btn(Comfort_Mode_Btn_Num);
    Light_Mode_Btn(Light_Mode_Btn_Num);
    Glass_Up_Btn(Glass_Up_Btn_Num);
    Glass_Down_Btn(Glass_Down_Btn_Num);
    Sheild_Up_Btn(Sheild_Up_Btn_Num);
    Sheild_Down_Btn(Sheild_Down_Btn_Num);
    Drive_Btn driveButton(Drive_Btn_Num);

    // 무한 루프, 실제 프로그램에서는 여기에 다른 로직이 들어갈 수 있습니다.
    while (1) {
        driveButton.update();
        delay(10); // CPU 사용을 줄이기 위해 1초 지연
    }

    return 0;
}
#include <stdio.h>
#include <wiringPi.h>

#include "Btn.h"

#define BUTTON_PIN 8 // wiringPi 핀 번호 8, 물리적인 GPIO 2번 핀에 해당

#define Comfort_Mode_Btn_Num 0 //GPIO17 in RaspberryPI
#define Light_Mode_Btn_Num 2 //GPIO27 in RaspberryPI
#define Glass_Up_Btn_Num 3 //GPIO22 in RaspberryPI
#define Glass_Down_Btn_Num 30 //GPIO0 in RaspberryPI
#define Sheild_Up_Btn_Num 21//GPIO5 in RaspberryPI
#define Sheild_Down_Btn_Num 22 //GPIO6 in RaspberryPI
#define Drive_Btn_Num 23 //GPIO13 in RaspberryPI

int main(void) {
    // wiringPi 라이브러리 초기화
    if (wiringPiSetup() == -1) {
        printf("wiringPiSetup failed. Exiting...\n");
        return 1;
    }

    Comfort_Mode_Btn(Comfort_Mode_Btn_Num);
    Light_Mode_Btn(Light_Mode_Btn_Num);
    Glass_Up_Btn(Glass_Up_Btn_Num);
    Glass_Down_Btn(Glass_Down_Btn_Num);
    Sheild_Up_Btn(Sheild_Up_Btn_Num);
    Sheild_Down_Btn(Sheild_Down_Btn_Num);
    Drive_Btn driveButton(Drive_Btn_Num);

    // 무한 루프, 실제 프로그램에서는 여기에 다른 로직이 들어갈 수 있습니다.
    while (1) {
        driveButton.update();
        delay(10); // CPU 사용을 줄이기 위해 1초 지연
    }

    return 0;
}
