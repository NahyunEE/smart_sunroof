#include "../module/device_module.h"
#include "../module/mode.h"
#include "../module/state_sensor.h"

int main() {
    MainController con;
    Usermode user;
    Cleanmode clean;
    Brightmode bright;
    State state;
    Sensordata sensor(0x04);
    while(true){
        if(state.issafety()){
            switch(state.getmodestate()){
                case USERMODE:
                    con.moderun(&user);
                    break;
                case CLEANMODE:
                    con.moderun(&clean);
                    break;
                case BRIGHTMODE:
                    con.moderun(&bright);
                    break;
            }
        }
    }
    
    return 0;
}