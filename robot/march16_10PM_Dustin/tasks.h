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

static const uint16_t tenVoltADCequivalent = 600;
static const uint16_t sawADCequivalent = 450;// test for greater than sawtooth 474-607  square 280-321

void setRelay()// capacitance
{
    digitalWrite(RELAY_A_PIN, LOW);    
    digitalWrite(RELAY_B_PIN, HIGH);
    delay(10);
    digitalWrite(RELAY_B_PIN, LOW);
}

void resetRelay()// voltage or signal
{
    digitalWrite(RELAY_A_PIN, HIGH);    
    digitalWrite(RELAY_B_PIN, LOW);
    delay(10);
    digitalWrite(RELAY_A_PIN, LOW);
}


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
   resetRelay();  
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
    pinMode(CAP_TEST_TRIGGER_PIN, OUTPUT);
    digitalWrite(CAP_TEST_TRIGGER_PIN, HIGH);
    delay(10);
    pinMode(CAP_TEST_TRIGGER_PIN, INPUT);
    
    
    
    
/* code moved to secondary Duemilanove
    // if the capacitance is greater than 1 μF, then go right, if it is less than 100 nF, go left
    
    //drive relay
    setRelay();
    
    digitalWrite(TASK_CAP_LOW_PIN, LOW);   
    digitalWrite(REF_CAP_LOW_PIN, LOW);   
    digitalWrite(TASK_CAP_HIGH_PIN, LOW);  
    digitalWrite(REF_CAP_HIGH_PIN, LOW);
    delay(50); 
    digitalWrite(TASK_CAP_HIGH_PIN, HIGH);  
    digitalWrite(REF_CAP_HIGH_PIN, HIGH);
    delayMicroseconds(10);// or 11uS = 1 time constant of REF_CAP
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
        return RIGHT;
    }
*/
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
      isCold = true;
      
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
    resetRelay();
    
    
  
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

uint16_t calibrateVoltageTask()
{
    lcd.clear();
    lcd.print("connect whiskers");
    lcd.print("to 10V source");
    uint16_t taskVoltage = analogRead(VOLT_SIGNAL_ADC_PIN);
    

}

uint16_t calibrateSawtoothSignalTask()
{
    lcd.clear();
    lcd.print("connect whiskers");
    lcd.setCsrLC(2, 1);
    lcd.print("to Sawtooth 5Vrms source");
    delay(2000);
    
    uint16_t min = 1023;
    uint16_t max = 0;
    uint16_t taskVoltage = analogRead(VOLT_SIGNAL_ADC_PIN);
    if(taskVoltage > max)
    {max = taskVoltage;}
    if(taskVoltage < min)
    {max = taskVoltage;}
    lcd.setCsrLC(3, 6);
    lcd.print("ADC: ");
    lcd.print(taskVoltage, DEC);
    lcd.setCsrLC(4, 1);
    lcd.print("min: ");
    lcd.print(min, DEC);
    lcd.setCsrLC(4, 11);
    lcd.print("max: ");
    lcd.print(max, DEC);
}

uint16_t calibrateSquarewaveSignalTask()
{
    lcd.clear();
    lcd.print("connect whiskers");
    lcd.print("to Square wave 5Vrms source");
    uint16_t taskVoltage = analogRead(VOLT_SIGNAL_ADC_PIN);
}



#endif



