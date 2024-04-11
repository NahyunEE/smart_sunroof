#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CS 6
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000

class MCP3204{
    private:
      
    int channel;
    int analogRead;

    public:

    void setChannel(int _channel){
        this->channel = _channel;
    }

    int getChannel(void){
        return this->channel;
    }

    int getAnalogRead(void){
        return this->analogRead;
    }
    MCP3204(){
        this->channel=0;
        this->analogRead =0;
        pinMode(SPI_CS, OUTPUT);
       
    }
    int readAnalogRead();

};

int MCP3204::readAnalogRead(){
        unsigned char buf[3];    
        buf[0] = 0x06 | ((this->channel & 0x07) >> 2);
        buf[1] = ((this->channel & 0x07) << 6);
        buf[2] = 0x00;
        digitalWrite(SPI_CS, LOW);
        wiringPiSPIDataRW(SPI_CHANNEL, buf, 3);
        buf[1] = 0x0F & buf[1];
        this->analogRead = (buf[1] << 8) | buf[2];
        digitalWrite(SPI_CS, HIGH);       
        return this->analogRead;
}