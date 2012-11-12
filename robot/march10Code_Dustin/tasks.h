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



Direction_t getYellowVoltageDirection()
{
    
   
    return(RIGHT);
}

Direction_t getBlueCapacitanceDirection()
{
    
    //drive relay
    digitalWrite(RELAY_A_PIN, LOW);    
    digitalWrite(RELAY_B_PIN, HIGH);
    
    
    
   
    return(RIGHT);
}

Direction_t getGreenTemperatureDirection()
{
  //direction_t direction;
  int8_t tempArray[8];
  int8_t ambient = getAmbient();
  fillTemperatureArray(tempArray);
  return(RIGHT); 
}

Direction_t getRedSignalDirection()
{
  return(RIGHT);
}

#endif



