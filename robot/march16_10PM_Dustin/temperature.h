#ifndef temperature_h
#define temperature_h
#include "Arduino.h"

//must support operationalMode
// SEEK_TEMPERATURE 

// readings will be correct approx 40mS after the sensor points to a new position.

int16_t getTemperature()
{
    delay(40);
   Wire.beginTransmission(00);          
   Wire.send(2);                              
   Wire.endTransmission();
   int8_t temperature = -1;
   Wire.requestFrom(00, 1);        
   while(Wire.available())
   {   
      temperature  = Wire.receive();
   } 
   
   
   return temperature;
}


int16_t toF(int8_t C)
{
    //F = (C * 9.0/5.0) + 32.0
    int16_t F = (C * 1.8) + 32;
    return F;
}
   
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

int16_t getAmbient()
{
    delay(40);
   Wire.beginTransmission(TPA81_ADDR);          
   Wire.send(TPA81_AMBIENT_REG);                              
   Wire.endTransmission();
   int8_t ambient = 127;
   Wire.requestFrom(TPA81_ADDR, (uint8_t)1);        
   while(Wire.available())
   {   
       ambient = Wire.receive();
   } 
   
   ambient =  toF(ambient);
   return ambient;
}

int16_t getTemperaturePixel(uint8_t pixelNum)// takes 0 - 8, otherwise returns -127
{
    delay(40);
    if(pixelNum <= 8)
    {
        pixelNum++;  // function input starts at 0, ambient is register 1, pixel 1 is register 2.  TPA81 pixels start at 2
        Wire.beginTransmission(TPA81_ADDR);          
        Wire.send(pixelNum);                              
        Wire.endTransmission();
        int16_t pixel = 127;
        Wire.requestFrom(TPA81_ADDR, (uint8_t)1);            
        while(Wire.available())
        {        
            pixel = Wire.receive(); 
        }
        pixel = toF(pixel);
        return 255;
    }
    else
    {
        return 127;
    }

}

void fillTemperatureArray(int16_t tempArray[]) //array is always length 8 
{
    delay(40);
    uint8_t i;
  for(i = TPA81_TEMP1_REG; i <= TPA81_TEMP8_REG; i++)
  {
  Wire.beginTransmission(TPA81_ADDR);          
   Wire.send(i);                              
   Wire.endTransmission();
   
   Wire.requestFrom(TPA81_ADDR, (uint8_t)1);    
   
   while(Wire.available())
   {   
       tempArray[i-TPA81_TEMP1_REG] = Wire.receive(); 
   }
   tempArray[i-TPA81_TEMP1_REG] = toF(tempArray[i-TPA81_TEMP1_REG]);
  }
}

#endif



