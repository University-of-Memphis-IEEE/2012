#ifndef tasks_h
#define tasks_h
#include "Arduino.h"

//must support operationalModes
/*
READ_VOLTAGE
READ_CAPACITANCE
READ_TEMPERATURE
READ_SIGNAL
*/

typedef enum {UNKNOWN, LEFT, RIGHT} direction_t;
typedef enum {VOLTAGE = 1, CAPACITANCE, TEMPERATURE, SIGNAL} task_t;
task_t lastTask;
typedef enum {YELLOW = 1, BLUE, GREEN, RED} taskColor_t;

direction_t getYellowVoltageDirection()
{
    
   
    return(RIGHT);
}

direction_t getBlueCapacitanceDirection()
{
    
   
    return(RIGHT);
}

direction_t getGreenTemperatureDirection()
{
  //direction_t direction;
  int8_t tempArray[8];
  int8_t ambient = getAmbient();
  fillTemperatureArray(tempArray);
  return(RIGHT); 
}

direction_t getRedSignalDirection()
{
  return(RIGHT);
}

#endif



