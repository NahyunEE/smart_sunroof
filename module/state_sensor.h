#include <stdint.h>

class State{
    private:
        uint8_t modestate;
        bool safestate;
        Sensordata * sensor;
        uint32_t lengthresh;
        uint32_t speedthresh;

    public:
        bool issafety();
        void modifysafestate();
        uint8_t getmodestate();
};

class Sensordata{
    private:
        uint32_t bright;
        uint32_t temper;
        uint32_t indust;
        uint32_t outdust;
        uint32_t length;
        uint32_t water;
        uint32_t speed;
        uint32_t userbright;
        int fd;
    public:
        Sensordata(int fd_ad);
        uint32_t getbright();
        uint32_t gettemper();
        uint32_t getindust();
        uint32_t getoutdust();
        uint32_t getlength();
        uint32_t getwater();
        uint32_t getspeed();
        uint32_t getuserbright();
        void modifyuserbright();
        void modifyspeed();
        void modifyvalue(uint32_t);
};