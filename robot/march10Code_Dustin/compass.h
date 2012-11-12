#ifndef compass_h
#define compass_h

#include "Arduino.h"



    
uint8_t getBearing()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_BEARING_BYTE_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();

   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   while(Wire.available() < 1);               // Wait for bytes to become available
   uint8_t bearing = Wire.receive(); 
   return(bearing - compassOffset);  
}

uint16_t getBearingDegrees()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_BEARING_DEGREE_HIGH_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();

   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   while(Wire.available() < 1);               // Wait for bytes to become available
   uint16_t degree = Wire.receive(); 
   degree = degree << 8;
   
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_BEARING_DEGREE_HIGH_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();

   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   while(Wire.available() < 1);               // Wait for bytes to become available
   degree += Wire.receive(); 
   
   return(degree);  
}

int8_t getPitch()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_PITCH_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();
   
   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   while(Wire.available() < 1);               // Wait for bytes to become available
   int8_t pitch = Wire.receive(); 
   return(pitch);
}

int8_t getRoll()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_ROLL_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();
   
   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   while(Wire.available() < 1);               // Wait for bytes to become available
   int8_t roll = Wire.receive(); 
   return(roll);
}

void zeroCompass()
{
    compassOffset = 0;
    compassOffset = getBearing();  
}
#endif



