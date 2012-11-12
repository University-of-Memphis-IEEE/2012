#include <Wire.h>
#include "configure.h"

int loopCount = 0;

void setup()
{
  Wire.begin();  
  Serial.begin(9600);
  
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  Serial.println("Print something.  Anything.");
  
setAutoSpeedRegulationOn(PRIMARY_MD25_ADDR);
setAutoSpeedRegulationOn(SECONDARY_MD25_ADDR);
setTimeoutOff(PRIMARY_MD25_ADDR);
setTimeoutOff(SECONDARY_MD25_ADDR);
setMD25SpeedByteFormat(PRIMARY_MD25_ADDR, 1);
setMD25SpeedByteFormat(SECONDARY_MD25_ADDR, 1);

Serial.println("End of Setup()");

Serial.print("Loop:");
Serial.println(loopCount);
digitalWrite(6, LOW);
delay(2000);
}

void loop()
{
  digitalWrite(6, HIGH);
  loopCount++;
  
  Serial.print("Loop:");
  Serial.println(loopCount);
  // speed  -128 (Full Reverse)   0 (Stop)   127 (Full Forward)
fullStop();
delay(3000);
/*
setWheelSpeed(FRONT, 127);
delay(3000);
fullStop();
setWheelSpeed(REAR, 127);
delay(3000);
fullStop();
setWheelSpeed(LEFT, 127);
delay(3000);
fullStop();
setWheelSpeed(RIGHT, 127);
delay(3000);
fullStop();
delay(2000);
setWheelSpeed(FRONT, -127);
delay(3000);
fullStop();
setWheelSpeed(REAR, -127);
delay(3000);
fullStop();
setWheelSpeed(LEFT, -127);
delay(3000);
fullStop();
setWheelSpeed(RIGHT, -127);
delay(3000);
fullStop();
*/
moveForward(127, 1000);
delay(300);
moveRF(127, 1000);
delay(300);
moveRight(127, 1000);
delay(300);
moveRR(127, 1000);
delay(300);
moveRearward(127, 1000);
delay(300);
moveLR(127, 1000);
delay(300);
moveLeft(127, 1000);
delay(300);
moveLF(127, 1000);
digitalWrite(6, LOW);
delay(1000);
}

