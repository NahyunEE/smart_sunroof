#include <wiringPi.h>


///쾌적모드
class Comfort_Mode_Btn {
private:
    int BtnNum;
    
public:   
    Comfort_Mode_Btn(int btnNum) : BtnNum(btnNum) {
        pinMode(BtnNum, INPUT);
        pullUpDnControl(BtnNum, PUD_DOWN);        
        // 클래스의 정적 멤버 함수를 전달하는 방식으로 수정
        if (wiringPiISR(BtnNum, INT_EDGE_FALLING, &buttonPressedStaticISR) < 0) {          
           printf("Error\n");
        }
    }
    void setButtonNum(int _BtnNum) {
        this->BtnNum = _BtnNum;
    }
   static void buttonPressedStaticISR() {
        printf("ComforMode Button On\n");
}
};

//채광모드
class Light_Mode_Btn {
private:
    int BtnNum;
    
public:   
    Light_Mode_Btn(int btnNum) : BtnNum(btnNum) {
        pinMode(BtnNum, INPUT);
        pullUpDnControl(BtnNum, PUD_DOWN);        
        // 클래스의 정적 멤버 함수를 전달하는 방식으로 수정
        if (wiringPiISR(BtnNum, INT_EDGE_FALLING, &buttonPressedStaticISR) < 0) {          
           printf("Error\n");
        }
    }
    void setButtonNum(int _BtnNum) {
        this->BtnNum = _BtnNum;
    }
   static void buttonPressedStaticISR() {
        printf("Light Mode On\n");
}
};

//유리막 UP
class Glass_Up_Btn {
private:
    int BtnNum;
    
public:   
    Glass_Up_Btn(int btnNum) : BtnNum(btnNum) {
        pinMode(BtnNum, INPUT);
        pullUpDnControl(BtnNum, PUD_DOWN);        
        // 클래스의 정적 멤버 함수를 전달하는 방식으로 수정
        if (wiringPiISR(BtnNum, INT_EDGE_FALLING, &buttonPressedStaticISR) < 0) {          
           printf("Error\n");
        }
    }
    void setButtonNum(int _BtnNum) {
        this->BtnNum = _BtnNum;
    }
   static void buttonPressedStaticISR() {
        printf("Glass Up\n");
}
};

//유리막 Down
class Glass_Down_Btn {
private:
    int BtnNum;
    
public:   
    Glass_Down_Btn(int btnNum) : BtnNum(btnNum) {
        pinMode(BtnNum, INPUT);
        pullUpDnControl(BtnNum, PUD_DOWN);        
        // 클래스의 정적 멤버 함수를 전달하는 방식으로 수정
        if (wiringPiISR(BtnNum, INT_EDGE_FALLING, &buttonPressedStaticISR) < 0) {          
           printf("Error\n");
        }
    }
    void setButtonNum(int _BtnNum) {
        this->BtnNum = _BtnNum;
    }
   static void buttonPressedStaticISR() {
        printf("Glass Down\n");
}
};

//가림막 UP
class Sheild_Up_Btn {
private:
    int BtnNum;
    
public:   
     Sheild_Up_Btn(int btnNum) : BtnNum(btnNum) {
        pinMode(BtnNum, INPUT);
        pullUpDnControl(BtnNum, PUD_DOWN);        
        // 클래스의 정적 멤버 함수를 전달하는 방식으로 수정
        if (wiringPiISR(BtnNum, INT_EDGE_FALLING, &buttonPressedStaticISR) < 0) {          
           printf("Error\n");
        }
    }
    void setButtonNum(int _BtnNum) {
        this->BtnNum = _BtnNum;
    }
   static void buttonPressedStaticISR() {
        printf("Sheild Up\n");
}
};

//가림막 Down

class Sheild_Down_Btn {
private:
    int BtnNum;
    
public:   
    Sheild_Down_Btn(int btnNum) : BtnNum(btnNum) {
        pinMode(BtnNum, INPUT);
        pullUpDnControl(BtnNum, PUD_DOWN);        
        // 클래스의 정적 멤버 함수를 전달하는 방식으로 수정
        if (wiringPiISR(BtnNum, INT_EDGE_FALLING, &buttonPressedStaticISR) < 0) {          
           printf("Error\n");
        }
    }
    void setButtonNum(int _BtnNum) {
        this->BtnNum = _BtnNum;
    }
   static void buttonPressedStaticISR() {
        printf("Sheild Down\n");
}
};


class Drive_Btn {
private:
    int BtnNum;
    int lastState; 
    
public:   
    Drive_Btn(int btnNum) : BtnNum(btnNum), lastState(LOW) {
        pinMode(BtnNum, INPUT);
        pullUpDnControl(BtnNum, PUD_DOWN);        
    }
    
    void update() {
        int currentState = digitalRead(BtnNum); 
        if (currentState != lastState) { 
            if (currentState == HIGH) {
                printf("Drive ON\n"); 
            } else {
                printf("Drive OFF\n"); 
            }
            lastState = currentState; 
        }
    }

    void setButtonNum(int _BtnNum) {
        this->BtnNum = _BtnNum;
        lastState = LOW; 
    }
};
