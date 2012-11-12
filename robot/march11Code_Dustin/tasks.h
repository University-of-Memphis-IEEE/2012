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

static const uint16_t tenVoltADCequivalent = 586;
static const uint16_t sawADCequivalent = 586;

void setupTaskBoardNeutral()
{
    pinMode(RELAY_A_PIN, OUTPUT);
    pinMode(RELAY_B_PIN, OUTPUT);    
    pinMode(CAP_RESULT_PIN, INPUT);
    pinMode(TASK_CAP_LOW_PIN, OUTPUT);  
    pinMode(REF_CAP_LOW_PIN, OUTPUT);   
    pinMode(TASK_CAP_HIGH_PIN, OUTPUT);  
    pinMode(REF_CAP_HIGH_PIN, OUTPUT);
    
    digitalWrite(RELAY_A_PIN, LOW);    
    digitalWrite(RELAY_B_PIN, LOW);
    digitalWrite(TASK_CAP_LOW_PIN, LOW);    
    digitalWrite(REF_CAP_LOW_PIN, LOW);
     digitalWrite(TASK_CAP_LOW_PIN, LOW);    
    digitalWrite(REF_CAP_LOW_PIN, LOW);     
    
}


Direction_t getYellowVoltageDirection()
{
    // if the magnitude of the voltage is greater than 11V, go right, if less than 9V, go left.
    digitalWrite(RELAY_A_PIN, LOW);    
    digitalWrite(RELAY_B_PIN, HIGH);
    delay(10);
    digitalWrite(RELAY_B_PIN, LOW);
    
    
  
  uint16_t taskVoltage = analogRead(VOLT_SIGNAL_ADC_PIN);
  if (taskVoltage < tenVoltADCequivalent)
  {
      return LEFT;
  }
  else
  {
      return RIGHT;
  }     
}

Direction_t getBlueCapacitanceDirection()
{
    // if the capacitance is greater than 1 μF, then go right, if it is less than 100 nF, go left
    
    //drive relay
    digitalWrite(RELAY_A_PIN, HIGH);    
    digitalWrite(RELAY_B_PIN, LOW);
     delay(10);
    digitalWrite(RELAY_A_PIN, LOW);
    //discharge caps to known ground level
    digitalWrite(TASK_CAP_LOW_PIN, LOW);   
    digitalWrite(REF_CAP_LOW_PIN, LOW);   
    digitalWrite(TASK_CAP_HIGH_PIN, LOW);  
    digitalWrite(REF_CAP_HIGH_PIN, LOW);
    delay(50); // 14mS minimum = 10uF * 220 Ohm * 6 time constants
    //charge caps
    digitalWrite(TASK_CAP_HIGH_PIN, HIGH);  
    digitalWrite(REF_CAP_HIGH_PIN, HIGH);
    delayMicroseconds(110);//  = 1 time constant of 500 nF REF_CAP, area of rapid rate of change and near median voltage value.
    // stop driving all charge pins and set to high impedance state
    pinMode(TASK_CAP_LOW_PIN, INPUT);  
    pinMode(REF_CAP_LOW_PIN, INPUT);   
    pinMode(TASK_CAP_HIGH_PIN, INPUT);  
    pinMode(REF_CAP_HIGH_PIN, INPUT);
    
    if(digitalRead(CAP_RESULT_PIN) == HIGH)// Task Cap higher voltage than Ref Cap, thus Task Cap has lower Capacitance
    {
        return LEFT;
    }    
    else
    {
        return RIGHT;// Task Cap lower voltage than Ref Cap, thus Task Cap has higher Capacitance
    }
}

Direction_t getGreenTemperatureDirection()
{
    // if it is 10°F greater than ambient temperature, go right, if it is 10°F less than ambient temperature, go left
  
  //int16_t tempArray[8];
  int16_t ambient = getAmbient();
  boolean isCold = false;
  //fillTemperatureArray(tempArray);
  uint8_t i;
  for(i = 1; i <= 8; i++)
  {
      int16_t temp = getTemperaturePixel(i);
      temp = toF(temp);
      if(getTemperaturePixel(i) <= ambient - 6)
      {
        isCold = true;
      }
      
  }
  if(isCold)
  {
      return LEFT;
  }
  else
  {  
      return RIGHT; 
  }
}

Direction_t getRedSignalDirection()
{
    // if it is a square wave, go right, if it is a saw-tooth wave, go left.
    digitalWrite(RELAY_A_PIN, LOW);    
    digitalWrite(RELAY_B_PIN, HIGH);
    delay(10);
    digitalWrite(RELAY_B_PIN, LOW);
    
    
  
  uint16_t taskVoltage = analogRead(VOLT_SIGNAL_ADC_PIN);
  if (taskVoltage > sawADCequivalent)
  {
      return LEFT;
  }
  else
  {
      return RIGHT;
  }     
  return(RIGHT);
}

#endif



