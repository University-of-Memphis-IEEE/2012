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

void turnTo(uint8_t intendedDirection)
{
    drive4wheelSpeeds(0,0,0,0);
    uint8_t currentDirection = getBearing();
    
    
}



