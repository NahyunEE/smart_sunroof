
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <string.h>

#define NOT_PUSH 0
#define PUSH 1
#define PUSH_LONG 2
#define BUF_SIZE 255

class Device_driver{
    private:
        int device;
        char buf[BUF_SIZE];
    public:
        Device_driver(char *dv);
        ~Device_driver();
        int write_dv(int);
};

class Moter: public Device_driver{
    private:
        int min;
        int max;
        int currunt;
    public:
        Moter(int min_v,int max_v,char *dv):Device_driver(dv),min(min_v),max(max_v){};
        void run(int); //-1 close, 1 open, 0 stop;
        int ismax();
        int ismin();   
};


class Switch: public Device_driver{
    private:
        uint8_t state;
    public:
        uint8_t read();
        void modifystate(int);
};


class Potentiometer: public Device_driver{
    public:
        int read();

};

class Device_controller{
    public:
        Moter * glass_moter;
        Moter * blind_moter;
        Moter * tilting_moter;
        Switch * glass_opswtich;
        Switch * glass_clswtich;
        Switch * blind_opswtich;
        Switch * blind_clswtich;
        Switch * clmd_switch;
        Switch * blmd_swtich; 
};