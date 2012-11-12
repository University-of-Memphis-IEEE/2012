#ifndef movement_h
#define movement_h
#include "Arduino.h"

//must support operationalModes
/*
GO_AROUND_BOX_LEFT_FROM_RIGHT
GO_AROUND_BOX_RIGHT_FROM_LEFT
GO_AROUND_CENTER_FROM_NEAR
GO_AROUND_CENTER_FROM_FAR
LINE_FOLLOW
*/

// Useful information  for writing functions in this section
// 
// fullStop()
// driveWheelSpeed(Wheel_t wheel, int16_t speed)
// drive4wheelSpeeds(int16_t LFspeed, int16_t RFspeed, int16_t LRspeed, int16_t RRspeed)
// encoderReset()
// int32_t getEncoderCount(Wheel_t wheel)

// distance between wheel centers = 208mm = 8.189" = 238 wheel units

// inches = wheel units * 0.0343569
// mm = wheel units * 0.87266462599716478846184538424431
// wheel units = mm * 1.1459155902616464175359630962821
// wheel units = " * 29.1
// wheel diameter      = 100mm     = 3.937"  =  115 wheel units
// wheel circumference = 314.15mm  = 12.368" = 360 wheel units
//                                                                                     Turn in place
// circumference of minimum turning circle 360   degrees =   0 binary angle measure = 748 wheel units
//                                         180   degrees = 128 binary angle measure = 374 wheel units
//                                         90    degrees =  64 binary angle measure = 187 wheel units
//                                         45    degrees =  32 binary angle measure =  93 wheel units
//                                         30    degrees =  21 binary angle measure =  62 wheel units
//                                         22.5  degrees =  16 binary angle measure =  47 wheel units
//                                         15    degrees =  11 binary angle measure =  31 wheel units
//                                         11.25 degrees =   8 binary angle measure =  23 wheel units
//                                          5.625degrees =   4 binary angle measure =  10 wheel units



void driveForwardXclicks(int32_t clicks)
{  
  encoderReset();
  int32_t startLF = getEncoderCount(LF);
  int32_t startRF = getEncoderCount(RF);
  int32_t startLR = getEncoderCount(LR);
  int32_t startRR = getEncoderCount(RR);
  
  drive4wheelSpeeds(127, 127, 127, 127);  
  
  boolean LFstopped = false;
  boolean RFstopped = false;
  boolean LRstopped = false;
  boolean RRstopped = false;
  
  while (!LFstopped && !RFstopped && !LRstopped && !RRstopped)
    {
        displayWheelEncoders();  
      if (getEncoderCount(LF) >= startLF + clicks)
        {
          driveWheelSpeed(LF, 0);
          LFstopped = true;
        }
      if (getEncoderCount(RF) >= startRF + clicks)
        {
          driveWheelSpeed(RF, 0);
          RFstopped = true;
        }
      if (getEncoderCount(LR) >= startLR + clicks)
        {
          driveWheelSpeed(LR, 0);
          LRstopped = true;
        }
        if (getEncoderCount(RR) >= startRR + clicks)
        {
          driveWheelSpeed(RR, 0);
          RRstopped = true;
        } 
          
    }    
}

void turn90degrees(Direction_t direction)
{ 
    encoderReset();
    int32_t startLF = getEncoderCount(LF);
    int32_t startRF = getEncoderCount(RF);
    int32_t startLR = getEncoderCount(LR);
    int32_t startRR = getEncoderCount(RR);
    
    boolean LFstopped = false;
    boolean RFstopped = false;
    boolean LRstopped = false;
    boolean RRstopped = false;
    
    static const int32_t NINETY_DEGREE_TURN_CLICKS = 143;
    if(direction == LEFT)
    {   
        drive4wheelSpeeds(-127, 127, -127, 127);        
        while (!(LFstopped && RFstopped && LRstopped && RRstopped))
        {
          if (getEncoderCount(LF) <= startLF - NINETY_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(LF, 0);
            LFstopped = true;
          }
           if (getEncoderCount(RF) >= startRF + NINETY_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(RF, 0);
            RFstopped = true;
          }
           if (getEncoderCount(LR) <= startLR - NINETY_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(LR, 0);
            LRstopped = true;
          }
           if (getEncoderCount(RR) >= startRR + NINETY_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(RR, 0);
            RRstopped = true;
          }
          
        }
        
    }
    else if(direction == RIGHT)
    {
        drive4wheelSpeeds(127, -127, 127, -127);
        while (!(LFstopped && RFstopped && LRstopped && RRstopped))
        {
          if (getEncoderCount(LF) >= startLF + NINETY_DEGREE_TURN_CLICKS)
          {
            driveWheelSpeed(LF, 0);
            LFstopped = true;
          }
           if (getEncoderCount(RF) <= startRF - NINETY_DEGREE_TURN_CLICKS)
          {
            driveWheelSpeed(RF, 0);
            RFstopped = true;
          }
           if (getEncoderCount(LR) >= startLR + NINETY_DEGREE_TURN_CLICKS)
          {
            driveWheelSpeed(LR, 0);
            LRstopped = true;
          }
           if (getEncoderCount(RR) <= startRR - NINETY_DEGREE_TURN_CLICKS)
          {
            driveWheelSpeed(RR, 0);
            RRstopped = true;
          }
        }
    }
    else
    {
        
    }
    delay(200);
}

void turn45degrees(Direction_t direction)
{ 
    encoderReset();
    int32_t startLF = getEncoderCount(LF);
    int32_t startRF = getEncoderCount(RF);
    int32_t startLR = getEncoderCount(LR);
    int32_t startRR = getEncoderCount(RR);
    
    boolean LFstopped = false;
    boolean RFstopped = false;
    boolean LRstopped = false;
    boolean RRstopped = false;
    
    static const int32_t FORTYFIVE_DEGREE_TURN_CLICKS = 72;
    if(direction == LEFT)
    {   
        drive4wheelSpeeds(-127, 127, -127, 127);        
        while (!(LFstopped && RFstopped && LRstopped && RRstopped))
        {
          if (getEncoderCount(LF) <= startLF - FORTYFIVE_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(LF, 0);
            LFstopped = true;
          }
           if (getEncoderCount(RF) >= startRF + FORTYFIVE_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(RF, 0);
            RFstopped = true;
          }
           if (getEncoderCount(LR) <= startLR - FORTYFIVE_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(LR, 0);
            LRstopped = true;
          }
           if (getEncoderCount(RR) >= startRR + FORTYFIVE_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(RR, 0);
            RRstopped = true;
          }
          
        }
        
    }
    else if(direction == RIGHT)
    {
        drive4wheelSpeeds(127, -127, 127, -127);
        while (!(LFstopped && RFstopped && LRstopped && RRstopped))
        {
          if (getEncoderCount(LF) >= startLF + FORTYFIVE_DEGREE_TURN_CLICKS)
          {
            driveWheelSpeed(LF, 0);
            LFstopped = true;
          }
           if (getEncoderCount(RF) <= startRF - FORTYFIVE_DEGREE_TURN_CLICKS)
          {
            driveWheelSpeed(RF, 0);
            RFstopped = true;
          }
           if (getEncoderCount(LR) >= startLR + FORTYFIVE_DEGREE_TURN_CLICKS)
          {
            driveWheelSpeed(LR, 0);
            LRstopped = true;
          }
           if (getEncoderCount(RR) <= startRR - FORTYFIVE_DEGREE_TURN_CLICKS)
          {
            driveWheelSpeed(RR, 0);
            RRstopped = true;
          }
        }
    }    
}

void      followRightWallLoop()
{

}
    
void      followLeftWallLoop()
{

}
        
void  turnNorthLoop()
{
  Direction_t turn;
  uint8_t currentPosition;
  while (!((currentPosition = getBearing()) < 3 || currentPosition > 252 ))// not within NORTH tolerance
  {
	  if(currentPosition > SOUTH_HEADING)
	  {
		turn = RIGHT;
/*
		//very coarse turn
		if(currentPosition < WEST_HEADING)
		{
			turn90degrees(turn);
			continue;
		}
		//course turn
		else if(currentPosition < NORTHWEST_HEADING)
		{
			turn45degrees(turn);
			continue;
		}
		//fine turn
		else
*/
		{
			turnMinimum(turn);
		}		
	  }
	  else
	  {
		turn = LEFT;
/*
		//very coarse turn
		if(currentPosition > EAST_HEADING)
		{
			turn90degrees(turn);
			continue;
		}
		//course turn
		else if(currentPosition > NORTHEAST_HEADING)
		{
			turn45degrees(turn);
			continue;
		}
		//fine turn
		else
*/
		{		
			turnMinimum(turn);
		}		
	  }
  } 
}
 
void turnMinimum(Direction_t direction)// turn the minimum amount that we reliably can.
{
    setAccelerationBoth(2);
    
    if(direction == LEFT)
    {   
        drive4wheelSpeeds(-30, 30, -30, 30);        
        delay(100);
        drive4wheelSpeeds(0,0,0,0);
    }
    else if(direction == RIGHT)
    {
        drive4wheelSpeeds(30, -30, 30, -30);
        delay(100);
        drive4wheelSpeeds(0,0,0,0);
    } 
  setAccelerationBoth(6);  
}



void      goAroundCenterFromNearLoop()
{
    //driveForwardXclicks(100);
    while(getEncoderCount(LF) <= 1080)
    {
        drive4wheelSpeeds(127,30,127,30);
    }
    
    //driveForwardXclicks(100);

}
     
void      goAroundCenterFromFarLoop()
{
    //driveForwardXclicks(50);
    turn45degrees(RIGHT);
    delay(100);
    while(getEncoderCount(LF) <= 1600)
    {
        drive4wheelSpeeds(127,85,127,85);
    }
    delay(100);
    turn45degrees(RIGHT);
    //driveForwardXclicks(50);

}
     
void      goAroundBoxLeftFromRightLoop()
{

}
     
void      goAroundBoxRightFromLeftLoop()
{

}
     
void      continueStraightLeftLoop()
{

}
     
void      continueStraightRightLoop()
{

}
    
void autonomousDriveLoop(uint32_t longSide, uint32_t shortSide)
{    
     driveForwardXclicks(longSide);
     delay(500);
     turn90degrees(RIGHT);
   delay(500);  
     driveForwardXclicks(shortSide); 
     delay(500);
     turn90degrees(RIGHT); 
     delay(500);
     driveForwardXclicks(longSide);
     delay(500);
     turn90degrees(RIGHT); 
     delay(500);
     driveForwardXclicks(shortSide); 
     delay(500);
     turn90degrees(RIGHT);
     delay(500);
}

void      competitionFailSafeLoop()
{
    while(true)
    {
        autonomousDriveLoop(1772, 300);
    }      
}

// interrupt handlers

void startButtonFallingHandler() // button pushed
{
    
    digitalWrite(TEENSY_LED_PIN, HIGH);
    //tone(TONE_PIN, 440);
}
    
void startButtonRisingHandler() // button released
{    
    startButtonBeenPushed = true;
    digitalWrite(TEENSY_LED_PIN, LOW);
    //noTone(TONE_PIN);
}

void frontIRrisingHandler() // IR sensor within range
{
    digitalWrite(TEENSY_LED_PIN, HIGH);
    //tone(TONE_PIN, 2200);
}
 
void frontIRfallingHandler() // IR sensor out of range
{
    digitalWrite(TEENSY_LED_PIN, LOW);
    //noTone(TONE_PIN);
}
  
void leftBumperSwitchFallingHandler()// left whisker made contact
{
    digitalWrite(TEENSY_LED_PIN, HIGH);
    //tone(TONE_PIN, 600);
}
    
void leftBumperSwitchRisingHandler()// left whisker released contact
{
    digitalWrite(TEENSY_LED_PIN, LOW);
    //noTone(TONE_PIN);
}
    
void rightBumperSwitchFallingHandler()// right whisker made contact
{
    digitalWrite(TEENSY_LED_PIN, HIGH);
    //tone(TONE_PIN, 1200);
    
}

void rightBumperSwitchRisingHandler()// right whisker released contact
{
    digitalWrite(TEENSY_LED_PIN, LOW);
    //noTone(TONE_PIN);
}

#endif
