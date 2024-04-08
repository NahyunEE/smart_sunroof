#include <stdint.h>

class State{
    private:
        uint8_t modestate;
        bool safestate;

    public:
        bool issafety();
        void modifysafestate();
};

class Sensordata{
    private:
        uint32_t bright;
        uint32_t temper;
        uint32_t dust;
        uint32_t length;
        uint32_t water;
    public:
        void update(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
        uint32_t getbright();
        uint32_t gettempper();
        uint32_t getdust();
        uint32_t getlength();
        uint32_t getwater();
        void modifybright(uint32_t);
        void modifytemper(uint32_t);
        void modifydust(uint32_t);
        void modifylength(uint32_t);
        void modifywater(uint32_t);
};