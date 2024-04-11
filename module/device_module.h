
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
#define TILT_MAX 0
#define MOV_MAX 0


class Device_driver{
    private:
        int device;
        char buf[BUF_SIZE];
    public:
        Device_driver(char *dv);
        Device_driver(uint8_t);
        ~Device_driver();
        int write_dv(int);
        uint8_t getdevice();
};

class Moter: public Device_driver{
    private:
        int min;
        int max;
        int currunt;
    public:
        Moter(int max_v,char *dv):Device_driver(dv),min(0),max(max_v){};
        void run(int); //-1 close, 1 open, 0 stop;
        int ismax();
        int ismin();   
};


class Switch: public Device_driver{
    private:
        uint32_t pushtime;
        uint8_t state;
    public:
        Switch(uint8_t pin);
        uint8_t read();
        static void interrupt_handlr(void *);
        static void interrupt_handlr_falling2(void *);
        static void interrupt_handlr_rising2(void *);
        static void set_ISR1(int pin,Device_controller * dc);
        static void set_ISR2(int pin,Device_controller * dc);
        void modifystate(uint32_t);
        
        
};


class Potentiometer: public Device_driver{
    public:
        int read();

};

class Device_controller{
    public:
        Device_controller(char *,char *,char *,int,int,int,int,int,int);
        ~Device_controller();
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