#ifndef tasks_h
#define tasks_h
#include "temperature.h"
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

int8_t analogpin = 38; //tasks pin
int8_t voltage, capacitance, temperature, signal;
int8_t picofarad = pow(10, -6);
int8_t nanofarad = pow(10, -9);

int8_t getVoltage()
{
    digitalWrite(RELAY_COIL_P, HIGH);
    digitalWrite(RELAY_COIL_N, LOW);
    voltage = analogRead(analogpin);
    Serial.println(voltage);

    if (voltage > 5 && voltage < 9)
    {
    	/*bot turn left*/
        voltage = -1;
    }
    else /*greater then 9V and greater than 11V*/
    {
    	/*bot turn right*/
        voltage = +1;
    }
   
    return(voltage);
}

int8_t getCapacitance()
{
    digitalWrite(RELAY_COIL_P, LOW);
    digitalWrite(RELAY_COIL_N, HIGH;
    capacitance = analogRead(analogpin);
    Serial.println(capacitance);

    if (capacitance > 10*nanofarad && capacitance < 100*nanofarad)
    {
    	/* bot turn left */
        capacitance = -1;
    }
    else /*capacitance is greater then 100nF*/
    {
    	/* bot turn right */
        capacitance = +1;
    }
   
    return(capacitance);
}

int8_t getTemperature()
{
    temperature = analogRead(analogpin);
    Serial.println(temperature);

    if (temperature < 10-ambient)
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

int8_t getSignal()
{
    signal = analogRead(analogpin);
    Serial.println(signal);
    if (signal => 1.6 && signal <= 1.9) // saw_tooth_wave
    {
        /* bot turn left */
        signal = -1;
    }

    if (signal => .800 && signal <= .850) // square_wave
    {
        /* bot turn right */
        signal = +1;
    }
   
    return(signal);
}

#endif