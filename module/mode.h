#include <stdint.h>
#include "device_module.h"
#include "state_sensor.h"
#define USERMODE 0
#define CLEANMODE 1
#define BRIGHTMODE 2

class MainController{
    private:
        bool drive;
    public:
        template <typename T>
        void moderun(T *mode);
        bool isdrive();
        void modifydrive();
};

class Mode{
    public:
    virtual void run(); 
};

class Usermode: public Mode{
    public:
    void run(Device_controller * dc);
};

class Cleanmode: public Mode{
    private:
        uint32_t industthresh;
        uint32_t outdustthresh;
        uint32_t temperthresh;
    public:
    void run(Device_controller * dc, Sensordata * sensor);
};

class Brightmode: public Mode{
    private:
        uint32_t userbright;
    public:
    void run(Device_controller * dc,Sensordata * sensor);
};


