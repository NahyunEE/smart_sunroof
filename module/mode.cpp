#include "mode.h"

while (1) {


    // 채광모드 //
    sensorBrightness = getbright();
    userBrightness = modifyuserbright();  //가변저항에 의한 센서(가변저항 입력)

    if (brightModeSwitch) { // 밝기 모드가 활성화되어 있을 때
        if (userBrightness >= sensorBrightness) {
            if (ismax()) {
                break; // 모터 정지
            }
            else {
                if (motorState != open()) {
                    openmax(); // 모터 열기
                    motorState = open();
                }
            }
        }
        else {
            if (ismin()) {
                break; // 
            }
            else {
                if (motorState != open()) {
                    closemin(); // 모터 닫기  close min 이상함
                    motorState = open();
                }
            }
        }
    }

    updateMotorState(); // 모터의 상태를 주기적으로 업데이트
}
