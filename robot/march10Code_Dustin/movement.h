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



void driveForwardXclicks(uint32_t clicks)
{  
  encoderReset();
  uint32_t startLF = getEncoderCount(LF);
  uint32_t startRF = getEncoderCount(RF);
  uint32_t startLR = getEncoderCount(LR);
  uint32_t startRR = getEncoderCount(RR);
  
  drive4wheelSpeeds(127, 127, 127, 127);
  
  
  boolean LFstopped = false;
  boolean RFstopped = false;
  boolean LRstopped = false;
  boolean RRstopped = false;
  
  while (!(LFstopped && RFstopped && LRstopped && RRstopped))
    {
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
    delay(500);
}
void turnXdegrees(int16_t signedDegrees)
{
    
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
            int32_t LFenc;
            int32_t RFenc;
            int32_t LRenc;
            int32_t RRenc;
        drive4wheelSpeeds(-127, 127, -127, 127);        
        while (!(LFstopped && RFstopped && LRstopped && RRstopped))
        {
          if ((LFenc=getEncoderCount(LF)) <= startLF - NINETY_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(LF, 0);
            LFstopped = true;
          }
           if ((RFenc = getEncoderCount(RF)) >= startRF + NINETY_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(RF, 0);
            RFstopped = true;
          }
           if ((LRenc = getEncoderCount(LR)) <= startLR - NINETY_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(LR, 0);
            LRstopped = true;
          }
           if ((RRenc = getEncoderCount(RR)) >= startRR + NINETY_DEGREE_TURN_CLICKS)
          {
              
            driveWheelSpeed(RR, 0);
            RRstopped = true;
          }
          Serial.print("Left Front Encoder: ");
              Serial.println(getEncoderCount(LF));
              Serial.print("Right Front Encoder: ");
              Serial.println(RFenc);
              Serial.print("Left Rear Encoder: ");
              Serial.println(LRenc);
              Serial.print("Right Rear Encoder: ");
              Serial.println(RRenc);
          Serial.println();
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
    delay(500);
}

void      followRightWallLoop()
{

}
    
void      followLeftWallLoop()
{

}
        
void      turnNorthLoop()
{

}
      
void      goAroundCenterFromNearLoop()
{

}
     
void      goAroundCenterFromFarLoop()
{

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
     turn90degrees(RIGHT);  
     driveForwardXclicks(shortSide); 
     turn90degrees(RIGHT); 
     driveForwardXclicks(longSide);
     turn90degrees(RIGHT); 
     driveForwardXclicks(shortSide); 
     turn90degrees(RIGHT);
}

void      competitionFailSafeLoop()
{
    while(true)
    {
        autonomousDriveLoop(6000, 200);
    }      
}




#endif
