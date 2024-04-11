#include <stdio.h>  
#include <errno.h>  
#include <wiringPiI2C.h> 

#define Water_Header 110
#define Temper_Header 120
#define Dust_Header 130
#define Bright_Header 140

#define Tail 255

int header = 0; // header flag
int tail = 0; // tail flag
int term = 0;

int Recv_data = 0; // sending data
int value = 0; // calculate sending data

int fd = wiringPiI2CSetup(0x04);

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

uint32_t getbright()
{
    return bright;
}

uint32_t gettempper()
{
    return temper;
}

uint32_t getdust()
{
    return dust;
}

uint32_t getlength()
{
    return length;
}

uint32_t getwater()
{
    return water;
}

void Sensordata::modifybright(uint32_t)
{
    wiringPiI2CWrite(fd, Bright_Header);

    for (int i = 0; i < 4; i++) {
        Recv_data = wiringPiI2CRead(fd);

        // header
        if (Recv_data == Bright_Header) {
            header = 1;
            continue;
        }

        // tail & Error check
        if (Recv_data == Tail) {
            tail = 1;
            header = 0;
        }

        if (header == 1) {
            if (term == 0) value = Recv_data * 100;
            else value += Recv_data;
            term++;
        }

        if (tail == 1) {
            printf("%d\n", value);
            bright = value; // set private variable
            tail = 0; // tail initailize
            term = 0;
        }
    }
}

void Sensordata::modifytemper(uint32_t)
{
    wiringPiI2CWrite(fd, Temper_Header);

    for (int i = 0; i < 4; i++) {
        Recv_data = wiringPiI2CRead(fd);

        // header
        if (Recv_data == Temper_Header) {
            header = 1;
            continue;
        }

        // tail
        if (Recv_data == Tail) {
            tail = 1;
            header = 0;
        }

        if (header == 1) {
            if (term == 0) value = Recv_data * 100;
            else value += Recv_data;
            term++;
        }

        if (tail == 1) {
            printf("%d\n", value);
            temper = value; // set private variable
            tail = 0; // tail initailize
            term = 0;
        }
    }
}

void Sensordata::modifydust(uint32_t)
{
    wiringPiI2CWrite(fd, Dust_Header);

    for (int i = 0; i < 4; i++) {
        Recv_data = wiringPiI2CRead(fd);

        // header
        if (Recv_data == Dust_Header) {
            header = 1;
            continue;
        }

        // tail
        if (Recv_data == Tail) {
            tail = 1;
            header = 0;
        }

        if (header == 1) {
            if (term == 0) value = Recv_data * 100;
            else value += Recv_data;
            term++;
        }

        if (tail == 1) {
            printf("%d\n", value);
            dust = value; // set private variable
            tail = 0; // tail initailize
            term = 0;
        }
    }
}

void Sensordata::modifywater(uint32_t)
{
    wiringPiI2CWrite(fd, Water_Header);

    for (int i = 0; i < 4; i++) {
        Recv_data = wiringPiI2CRead(fd);

        // header
        if (Recv_data == Water_Header) {
            header = 1;
            continue;
        }

        // tail
        if (Recv_data == Tail) {
            tail = 1;
            header = 0;
        }

        if (header == 1) {
            if (term == 0) value = Recv_data * 100;
            else value += Recv_data;
            term++;
        }

        if (tail == 1) {
            printf("%d\n", value);
            water = value; // set private variable
            tail = 0; // tail initailize
            term = 0;
        }
    }
}