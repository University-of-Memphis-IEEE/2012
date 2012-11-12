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
static const uint16_t WALL_FOLLOW_END_OF_WALL_THRESHOLD = 233;
static const uint16_t WALL_FOLLOW_MAX_DISTANCE_FROM_WALL = 100;
static const uint16_t WALL_FOLLOW_MIN_DISTANCE_TO_WALL = 58;
static const uint16_t SPEED_ADJUST_STEP = 6;
static const uint16_t BUMP_STOP_THRESHOLD = 20;
static const uint16_t MAX_uS = 15000;
void turnTo(uint8_t direction)
{

}


void sonarSetup()
{
  pinMode(FRONT_SRF05_ECHO_PIN, INPUT);
  pinMode(FRONT_SRF05_TRIGGER_PIN, OUTPUT);
  
  pinMode(LEFT_SRF05_ECHO_PIN, INPUT);
  pinMode(LEFT_SRF05_TRIGGER_PIN, OUTPUT);
  
  pinMode(RIGHT_SRF05_ECHO_PIN, INPUT);
  pinMode(RIGHT_SRF05_TRIGGER_PIN, OUTPUT);
  
  pinMode(REAR_SRF05_ECHO_PIN, INPUT);
  pinMode(REAR_SRF05_TRIGGER_PIN, OUTPUT);
}



uint16_t getTimeToFrontObject()
{
  
  digitalWrite(FRONT_SRF05_TRIGGER_PIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(FRONT_SRF05_TRIGGER_PIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(FRONT_SRF05_TRIGGER_PIN, LOW);                   // Send pin low again
  
  uint16_t time = pulseIn(FRONT_SRF05_ECHO_PIN, HIGH, MAX_uS);        // Read in times pulse
                         // Calculate distance from time of pulse
  return(time);                      
}

uint16_t getTimeToRearObject()
{
  
  digitalWrite(REAR_SRF05_TRIGGER_PIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(REAR_SRF05_TRIGGER_PIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(REAR_SRF05_TRIGGER_PIN, LOW);                   // Send pin low again
  
  uint16_t time = pulseIn(REAR_SRF05_ECHO_PIN, HIGH, MAX_uS);        // Read in times pulse
                         // Calculate distance from time of pulse
  return(time);                      
}

uint16_t getDistanceToFrontObject()
{
  
  digitalWrite(FRONT_SRF05_TRIGGER_PIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(FRONT_SRF05_TRIGGER_PIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(FRONT_SRF05_TRIGGER_PIN, LOW);                   // Send pin low again
  
  uint16_t wheelDistanceUnits = pulseIn(FRONT_SRF05_ECHO_PIN, HIGH, MAX_uS);        // Read in times pulse
                         // Calculate distance from time of pulse
  return(wheelDistanceUnits);                      
}

uint16_t getDistanceToLeftObject()
{
  
  digitalWrite(LEFT_SRF05_TRIGGER_PIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(LEFT_SRF05_TRIGGER_PIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(LEFT_SRF05_TRIGGER_PIN, LOW);                   // Send pin low again
  
  uint16_t wheelDistanceUnits = pulseIn(FRONT_SRF05_ECHO_PIN, HIGH, MAX_uS);        // Read in times pulse
                         // Calculate distance from time of pulse
  return(wheelDistanceUnits);
}  
 
uint16_t getDistanceToRightObject()
{
  
  digitalWrite(RIGHT_SRF05_TRIGGER_PIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(RIGHT_SRF05_TRIGGER_PIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(RIGHT_SRF05_TRIGGER_PIN, LOW);                   // Send pin low again
  
  uint16_t wheelDistanceUnits = pulseIn(FRONT_SRF05_ECHO_PIN, HIGH, MAX_uS);        // Read in times pulse
                         // Calculate distance from time of pulse
  return(wheelDistanceUnits);
}

uint16_t getDistanceToRearObject()//  get code from 
{
  
  digitalWrite(REAR_SRF05_TRIGGER_PIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(REAR_SRF05_TRIGGER_PIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(REAR_SRF05_TRIGGER_PIN, LOW);                   // Send pin low again
  
  uint16_t wheelDistanceUnits = pulseIn(FRONT_SRF05_ECHO_PIN, HIGH, MAX_uS);        // Read in times pulse
                         // Calculate distance from time of pulse
  return(wheelDistanceUnits);
}

boolean bumpCheck()// returns true if about to run into an object, false otherwise
{
    if(getDistanceToFrontObject() <= BUMP_STOP_THRESHOLD)
    return true;
    else
    return false;
}

void followRightWall(uint8_t direction)// until closest wall ends
{
    uint16_t distance;
    //drive4wheelSpeeds(int16_t LFspeed, int16_t RFspeed, int16_t LRspeed, int16_t RRspeed);
    //turn in place till pointing in correct direction.
    turnTo(direction);// EAST_HEADING, NORTH_HEADING, WEST_HEADING, SOUTH_HEADING
    drive4wheelSpeeds(127, 127, 127, 127);
    while( (distance = getDistanceToRightObject()) < WALL_FOLLOW_END_OF_WALL_THRESHOLD && !bumpCheck() )// end of wall not reached, not about to run into something.
    {
        
        if(distance < WALL_FOLLOW_MIN_DISTANCE_TO_WALL)// too close to wall
        {
            if(127 == wheelSpeed[RF])//right side speed maxed
            {
                drive4wheelSpeeds(wheelSpeed[LF] - SPEED_ADJUST_STEP, wheelSpeed[RF], wheelSpeed[LR] - SPEED_ADJUST_STEP, wheelSpeed[RR]);//slow down left side
            }
            else
            {
                drive4wheelSpeeds(wheelSpeed[LF], wheelSpeed[RF] + SPEED_ADJUST_STEP, wheelSpeed[LR], wheelSpeed[RR]  + SPEED_ADJUST_STEP);//speed up right side
            }
        }
        else if(distance > WALL_FOLLOW_MAX_DISTANCE_FROM_WALL)// too far from wall
        {
            if(127 == wheelSpeed[LF])//left side speed maxed
            {
                drive4wheelSpeeds(wheelSpeed[LF], wheelSpeed[RF] - SPEED_ADJUST_STEP, wheelSpeed[LR], wheelSpeed[RR] - SPEED_ADJUST_STEP);//slow down right side
            }
            else
            {
                drive4wheelSpeeds(wheelSpeed[LF] + SPEED_ADJUST_STEP, wheelSpeed[RF], wheelSpeed[LR] + SPEED_ADJUST_STEP, wheelSpeed[RR]);//speed up left side
            }
        }
    }
    drive4wheelSpeeds(0, 0, 0, 0);  //stop
}

void calibrateSonar()// start with bot against a wall
{
    fullStop();
    delay(1000);
    encoderReset();
    drive4wheelSpeeds(-127,-127,-127,-127);
    delay(1000);
    fullStop();
    delay(1000);
    uint16_t pinguS = getTimeToFrontObject();
    int32_t leftWheel = getEncoderCount(LR);
    int32_t rightWheel = getEncoderCount(RR);
    int32_t distanceTraveled = (leftWheel+rightWheel)/2;
    float conversionFactor = (float)distanceTraveled/pinguS;
    Serial.print("Left Encoder : ");
    Serial.println(leftWheel, DEC);
    Serial.print("Right Encoder : ");
    Serial.println(rightWheel, DEC);
    Serial.print("ping time in uS : ");
    Serial.println(pinguS, DEC);
    Serial.print("distance traveled in wheel clicks over 1 second at max speed : ");
    Serial.println(distanceTraveled, DEC);
    Serial.print("speed : ");
    Serial.println(distanceTraveled * .000872665, DEC);
    Serial.print("conversionFactor : ");
    Serial.println(conversionFactor, DEC);
    
    
}

void GPIO14setup()
{

}



#endif



