#ifndef camera_h
#define camera_h
#include "Arduino.h"

//must support operationalModes
//Will use the RX TX pins which are 2 & 3
//typedef enum {YELLOW = 1, BLUE, GREEN, RED} taskColor_t;



//SEEK_YELLOW
boolean seekYellow()
{
    boolean found = false;
    if(cameraConnected)
    {
    
    }
    else
    {
        found = false;
    }
    return found;
}
//SEEK_BLUE
boolean seekBlue()
{
    boolean found = false;
    //TODO
    return found;
}
//SEEK_GREEN
boolean seekGreen()
{
    boolean found = false;
    //TODO
    return found;
}
//SEEK_RED
boolean seekRed()
{
    boolean found = false;
    //TODO
    return found;
}




#endif



