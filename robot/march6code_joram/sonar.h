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

/*
static const uint8_t FRONT_SRF05_TRIGGER_PIN = 23;						            // Pin for SRF05 sonar
static const uint8_t LEFT_SRF05_TRIGGER_PIN =  22;                        // Pin for SRF05 sonar
static const uint8_t RIGHT_SRF05_TRIGGER_PIN = 21;                        // Pin for SRF05 sonar
static const uint8_t REAR_SRF05_TRIGGER_PIN =  20;                        // Pin for SRF05 sonar
*/

uint16_t dtfo, dtlo, dtro, dtrro;
                 
uint16_t getDistanceToFrontObject()
{
  dtfo = analogRead(23);
  Serial.println(dtfo);

  return(dtfo)
}

uint16_t getDistanceToLeftObject()
{
  dtlo = analogRead(22);
  Serial.println(dtlo);

  return(dtlo);
}  
 
uint16_t getDistanceToRightObject()
{
  dtro = analogRead(22);
  Serial.println(dtro);

  return(dtro);
}

uint16_t getDistanceToRearObject()//  get code from 
{
  dtrro = analogRead(22);
  Serial.println(dtrro);

  return(dtrro);
}

#endif