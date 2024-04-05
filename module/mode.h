#include <stdint.h>
#include "device_module.h"



class MainController{
    private:
        bool drive;
        uint16_t userbright;
        uint16_t speed;

    public:
        void moderun(Mode *mode);
        uint16_t getuserbright();
        bool isdrive();
        uint16_t getspeed();
        void modifydrive();
        void modifyuserbright();
        void modifyspeed();
};

class Mode{
    public:
    virtual void run(); 
};

class Usermode: public Mode{
    public:
    void run(Moter *,Moter *);
};

class Cleanmode: public Mode{
    public:
    void run(Moter *);
};

class Brightmode: public Mode{
    public:
    void run(Moter *,Moter *);
};


