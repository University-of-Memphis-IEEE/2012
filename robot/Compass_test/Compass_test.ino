#include <Wire.h>

#define compass  0x60



void setup(){
  Wire.begin();
  Serial.begin(9600);
}

void loop(){
  byte highByte;
  byte lowByte;
  delay(15);
  Wire.beginTransmission(compass);
  Wire.send(2);
  Wire.endTransmission();
  
  Wire.requestFrom(compass, 2);
  while(Wire.available() < 2);
    highByte = Wire.receive();
    lowByte = Wire.receive();
    int bearing = ((highByte<<8)+lowByte)/10;
    
    Serial.println(bearing);
  
    }
