#ifndef temperature_h
#define temperature_h
#include "Arduino.h"

//must support operationalMode
// SEEK_TEMPERATURE 


   
void setServo(uint8_t x)// active range 0-30 which usually represents about 180 degrees, 31 stops servo pulses. The calculation is SERVO_POS*60+540uS. So the range of the servo pulse is 0.54mS to 2.34mS in 60uS steps.  
{
  if (x > 31)
    x = 31;
     Wire.beginTransmission(TPA81_ADDR);
     Wire.send(TPA81_CMD_REG);
     Wire.send(x);   
     Wire.endTransmission();
}

void setServoRange(uint8_t x)//default:120, acceptable values 20-120; The calculation for the range in uS is ((31*ServoRange)/2). Setting a range of 20 will give a range of (31*20)/2 or 310uS. Setting a range of 120 will give a range of (31*120)/2 or 1860uS. In all cases the available range is centered on the servo's mid position of 1500uS
{
     Wire.beginTransmission(TPA81_ADDR);
     Wire.send(TPA81_SERVO_RANGE_REG);
     Wire.send(x);   
     Wire.endTransmission();
}

int8_t getAmbient()
{
   Wire.beginTransmission(TPA81_ADDR);          
   Wire.send(TPA81_AMBIENT_REG);                              
   Wire.endTransmission();
   
   Wire.requestFrom(TPA81_ADDR, (uint8_t)1);            
   while(Wire.available() < 1);              
   int8_t ambient = Wire.receive(); 
   return(ambient);
}

void fillTemperatureArray(int8_t tempArray[]) //array is always length 8 
{
  for(int i = TPA81_TEMP1_REG; i <= TPA81_TEMP8_REG; i++)
  {
  Wire.beginTransmission(TPA81_ADDR);          
   Wire.send(i);                              
   Wire.endTransmission();
   
   Wire.requestFrom(TPA81_ADDR, (uint8_t)1);            
   while(Wire.available() < 1);              
   tempArray[i-TPA81_TEMP1_REG] = Wire.receive(); 
  }
}

#endif



