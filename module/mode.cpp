#include "mode.h"

while (1) {
    sensorBrightness = getbright();
    userBrightness = modifyuserbright();  //가변저항에 의한 센서

    if (brightModeSwitch) { // 밝기 모드가 활성화되어 있을 때
        if (userBrightness >= sensorBrightness) {
            if (ismax()) {
                break; // 모터 정지
            }
            else {
                if (motorState != MOTOR_OPENING) {
                    openmax(); // 모터 열기
                    motorState = MOTOR_OPENING;
                }
            }
        }
        else {
            if (ismin()) {
                break; // 
            }
            else {
                if (motorState != MOTOR_CLOSING) {
                    closemin(); // 모터 닫기  close min 이상함
                    motorState = MOTOR_CLOSING;
                }
            }
        }
    }

    updateMotorState(); // 모터의 상태를 주기적으로 업데이트
}
