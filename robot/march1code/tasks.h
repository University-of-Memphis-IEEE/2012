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

int8_t getVoltage()
{
    voltage = analog.read(38);
   
    return(voltage);
}

int8_t getCapacitance()
{
    capacitance = analog.read(38);
   
    return(capacitance);
}

int8_t getTemperature()
{
    temperature = analog.read(38);
   
    return(temperature);
}

int8_t getSignal()
{
    signal = analog.read(38);
   
    return(signal);
}

#endif
