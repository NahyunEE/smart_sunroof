#include <iostream>  
#include <errno.h>  
#include <wiringPiI2C.h>  
#include <stdio.h>  
    
using namespace std;  
    
int main()  
{  
    int fd, result;  
    
    fd = wiringPiI2CSetup(0x04);  
    
    cout << "Init result: " << fd << endl;  
    
    for (int i = 0; i < 0xffffffff; i++)  
    {  
    
        result = wiringPiI2CWrite(fd, i);  
        //result = wiringPiI2CWriteReg16(fd, 0x40, i );  
    
        if (result == -1)  
        {  
            cout << "Error.  Errno is: " << errno << endl;  
        }  
        int data = wiringPiI2CRead(fd);  
        if (data == -1)  
        {  
            printf("No data\n");  
        }  
        else  
        {  
            printf("data=%d\n", data);  
        }  
    }  
}  
