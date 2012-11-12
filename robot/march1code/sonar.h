#ifndef sonar_h
#define sonar_h
#include "Arduino.h"

//must support operationalModes
/*
FOLLOW_RIGHT_WALL
FOLLOW_LEFT_WALL
CONTINUE_STRAIGHT_LEFT
CONTINUE_STRAIGHT_RIGHT
*/

static const uint8_t LEFT_SRF05_PIN = 20;                        // Pin for SRF05 sonar
static const uint8_t RIGHT_SRF05_PIN = 21;                       // Pin for SRF05 sonar
static const uint8_t REAR_SRF05_PIN = 22;                        // Pin for SRF05 sonar
//static const uint8_t FRONT_VEX_SONAR_PIN = 2;                        // Pin for Vex sonar
//static const uint8_t REAR_VEX_SONAR_PIN = 2;                        
uint16_t getDistanceToFrontObject()//uses Vex sensors.  get code from Blake
{}

uint16_t getDistanceToRearObject()//  get code from 
{}

uint16_t getDistanceToLeftObject()
{
  uint16_t leftSRF05distance;                          // Stores distance
  uint16_t leftSRF05duration;                          // Stores duratiuon of pulse in
  pinMode(LEFT_SRF05_PIN, OUTPUT);
  digitalWrite(LEFT_SRF05_PIN, LOW);           // Make sure pin is low before sending a short high to trigger ranging
  delayMicroseconds(2);
  digitalWrite(LEFT_SRF05_PIN, HIGH);          // Send a short 10 microsecond high burst on pin to start ranging
  delayMicroseconds(10);
  digitalWrite(LEFT_SRF05_PIN, LOW);           // Send pin low again before waiting for pulse back in
  pinMode(LEFT_SRF05_PIN, INPUT);
  leftSRF05duration = pulseIn(LEFT_SRF05_PIN, HIGH);    // Reads echo pulse in from SRF05 in micro seconds
  leftSRF05distance = leftSRF05duration/58;              // Dividing this by 58 gives us a distance in cm
  return(leftSRF05distance);
}  
 
uint16_t getDistanceToRightObject()
{
  uint16_t rightSRF05distance;                          // Stores distance
  uint16_t rightSRF05duration;                          // Stores duratiuon of pulse in
  pinMode(RIGHT_SRF05_PIN, OUTPUT);
  digitalWrite(RIGHT_SRF05_PIN, LOW);           // Make sure pin is low before sending a short high to trigger ranging
  delayMicroseconds(2);
  digitalWrite(RIGHT_SRF05_PIN, HIGH);          // Send a short 10 microsecond high burst on pin to start ranging
  delayMicroseconds(10);
  digitalWrite(RIGHT_SRF05_PIN, LOW);           // Send pin low again before waiting for pulse back in
  pinMode(RIGHT_SRF05_PIN, INPUT);
  rightSRF05duration = pulseIn(RIGHT_SRF05_PIN, HIGH);    // Reads echo pulse in from SRF05 in micro seconds
  rightSRF05distance = rightSRF05duration/58;              // Dividing this by 58 gives us a distance in cm
  return(rightSRF05distance);
}

#endif
