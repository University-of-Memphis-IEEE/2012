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

//Set up all task functions to return -1 for left, +1 for right, 0 if unable to determine

typedef enum {VOLTAGE = 1, CAPACITANCE, TEMPERATURE, SIGNAL} task_t;
task_t lastTask;
typedef enum {YELLOW = 1, BLUE, GREEN, RED} taskColor_t;

int8_t getYellowVoltageDirection()
{
    int8_t voltage = analogRead(38);
   
    return(voltage);
}

int8_t getBlueCapacitanceDirection()
{
    int8_t capacitance = analogRead(38);
   
    return(capacitance);
}

int8_t getGreenTemperatureDirection()
{
  Direction_t direction;
  int8_t tempArray[8];
  int8_t ambient = getAmbient();
  int8_t tendegreesambient;
  int8_t temperature;
  fillTemperatureArray(tempArray);
    if (temperature < tendegreesambient)
    {
    	/* bot turn left */
        temperature = -1;
    }
    else /*temperature is greater than 10 degrees ambient*/
    {
    	/* bot turn right */
        temperature = +1;
    }
   
    return(temperature);
}

int8_t getRedSignalDirection()
{
    int8_t signal = analogRead(38);
   
    return(signal);
}

#endif
