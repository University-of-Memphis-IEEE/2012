#ifndef compass_h
#define compass_h

#include "Arduino.h"



    
uint8_t getBearing()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_BEARING_BYTE_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();

   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   uint8_t bearing;
   elapsedMillis waiting;     // "waiting" starts at zero
  while (waiting < 1000) // Wait for bytes to become available
  {
    if (Wire.available()) 
    {
      bearing = Wire.receive();
      return(bearing - compassOffset);
                 
    }
  }
   return 0; //should only be reached if i2c communication fails  
}

uint16_t getBearingDegrees()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_BEARING_DEGREE_HIGH_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();

   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   uint16_t degree;
   elapsedMillis waiting;     // "waiting" starts at zero
  while (waiting < 500) // Wait for bytes to become available
  {
    if (Wire.available()) 
    {
      degree = Wire.receive(); 
      degree = degree << 8;
      waiting = 1001;           // end wait loop
    }
  }
   
   
   
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_BEARING_DEGREE_HIGH_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();

   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   
   waiting = 0;     // "waiting" starts at zero
  while (waiting < 500) // Wait for bytes to become available
  {
    if (Wire.available()) 
    {
       degree += Wire.receive();  
       return(degree); 
      
    }
  }   
return 0; //should only be reached if i2c communication fails  
}

int8_t getPitch()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_PITCH_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();
   
   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   int8_t pitch;
   elapsedMillis waiting;     // "waiting" starts at zero
  while (waiting < 1000) // Wait for bytes to become available
  {
    if (Wire.available()) 
    {
       pitch = Wire.receive(); 
       return pitch;
      waiting = 1001;           // end wait loop
    }
  }  
return 0; //should only be reached if i2c communication fails  
}

int8_t getRoll()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_ROLL_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();
   
   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   int8_t roll;
   elapsedMillis waiting;     // "waiting" starts at zero
  while (waiting < 1000) // Wait for bytes to become available
  {
    if (Wire.available()) 
    {
       roll = Wire.receive();  
       return(roll);
      
    }
  }    
return 0; //should only be reached if i2c communication fails  
}

void zeroCompass()
{
    compassOffset = 0;
    compassOffset = getBearing();  
}

#endif



