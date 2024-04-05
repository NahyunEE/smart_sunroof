


class Device_driver{
    private:
        int device;
    public:
        int open();
        int close();
};

class Moter: public Device_driver{
    private:
        int min;
        int max;
        int currunt;
    public:
        void run();
        int ismax();
        int ismin();   
};


class Switch: public Device_driver{
    public:
        int read();
};


class Potentiometer: public Device_driver{
    public:
        int read();

};