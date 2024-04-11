#include <wiringPi.h>
#include <wiringPiSPI.h>

#ifndef MCP3204_H
#define MCP3204_H
#include "MCP3204.h"
#endif

#define BrightChannel 0
#define SpeedChannel 1

class BrightPotential{
    
    private:
    int channel;
    int bright;
    MCP3204 mpc;

    public:

        void setChannel(int _channel){
            this->channel = _channel;
            mpc.setChannel(_channel);
        }

        int getBright(void){
            this->bright = mpc.readAnalogRead();
            return this->bright;
        }
        
        BrightPotential(){        
        this->channel = BrightChannel;
        this->bright =0;       
        }    

};

class SpeedPotential{
    
    private:
    int channel;
    int speed;
    MCP3204 mpc;

    public:

        void setChannel(int _channel){
            this->channel = _channel;           
        }

        int getSpeed(void){
            this->speed = mpc.readAnalogRead();
            return this->speed;
        }
        
        SpeedPotential(){        
        this->channel = SpeedChannel;
        this->speed =0;       
        mpc.setChannel(this->channel);
        }    

};