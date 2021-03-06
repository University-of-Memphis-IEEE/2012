//START
void startSetup()//competition start function
{
    //zero compass etc...
}

void radioControlSetup()
{
  ServoDecode.begin();
  ServoDecode.setFailsafe(1,1500); // set channel 1 failsafe pulsewidth. right horizontal stick
  ServoDecode.setFailsafe(2,1500); // set channel 2 failsafe pulsewidth. right vertical stick
  ServoDecode.setFailsafe(3,1500); // set channel 3 failsafe pulsewidth. left vertical stick
  ServoDecode.setFailsafe(4,1500); // set channel 4 failsafe pulsewidth. left horizontal stick
  ServoDecode.setFailsafe(5,1500); // set channel 5 failsafe pulsewidth. left buttons, use to activate bowlight
  ServoDecode.setFailsafe(6,1500); // set channel 6 failsafe pulsewidth. right buttons, use to override soft stop remotely
}

void autonomousDriveSetup()
{

}

void otherTestSetup()
{

}

void competitionFailSafeSetup()
{

}


//LOOP
void     staticVoltageLoop()
{

}

void     staticCapacitanceLoop()
{

}
 
void      staticTemperatureLoop()
{

}

void      staticSignalLoop()
{

}

    
void      followRightWallLoop()
{

}
    
void      followLeftWallLoop()
{

}
     
void      driveStraightXinchesLoop()
{

}
     
void      turn90degreesLoop()
{
    uint8_t distance;
    static const int32_t ninetyDegreeTurn = 187;

      fullStop();
      delay(1000);
      
    uint8_t startLF = getEncoderCount(LF);
    uint8_t startRF = getEncoderCount(RF);
    uint8_t startLR = getEncoderCount(LR);
    uint8_t startRR = getEncoderCount(RR);

    wheelSpeed[LF] = 127;
    wheelSpeed[RF] = -127;
    wheelSpeed[LR] = 127;
    wheelSpeed[RR] = -127;

    boolean LFstopped = false;
    boolean RFstopped = false;
    boolean LRstopped = false;
    boolean RRstopped = false;

    while (!(LFstopped && RFstopped && LRstopped && RRstopped))
    {
      if (getEncoderCount(LF) >= startLF+ninetyDegreeTurn);
      {
        driveWheelSpeed(LF, 0);
        LFstopped = true;
      }
       if (getEncoderCount(RF) <= startRF-ninetyDegreeTurn);
      {
        driveWheelSpeed(RF, 0);
        RFstopped = true;
      }
       if (getEncoderCount(LR) >= startLR+ninetyDegreeTurn);
      {
        driveWheelSpeed(LR, 0);
        LRstopped = true;
      }
       if (getEncoderCount(RR) <= startRR-ninetyDegreeTurn);
      {
        driveWheelSpeed(RR, 0);
        RRstopped = true;
      }

      drive4wheelSpeeds(wheelSpeed);
    }
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
     
void      competitionFailSafeLoop()
{

}
     
void      startLoop(){}//should never be entered.  Start is only called once from setup().  Use for debug only.
     
void      pullUpToYellowBoxLoop()
{

}
     
void      readVoltageLoop()
{

}
     
void      goAroundYellowBoxLoop()
{

}
    
void      pullUpToBlueBoxLoop()
{

}
     
void      readCapacitanceLoop()
{

}
     
void      goAroundBlueBoxLoop()
{

}
     
void      goAroundCenterBoardSeekTemperatureLoop()
{

}
     
void      pullUpToGreenBoxLoop()
{

}
     
void      readTemperatureLoop()
{

}
     
void      goAroundGreenBoxLoop()
{

}
    
void      pullUpToRedBoxLoop()
{

}
     
void      readSignalLoop()
{

}
     
void      goAroundRedBoxLoop()
{

}
    
void      goAroundCenterBoardLoop()
{

}
    
//  FINISH_LAP
      


void radioControlLoop()
{
    if(ServoDecode.getState()== READY_state) //Radio Control is functioning properly
      {         
       // drive under radio control
        int16_t leftButtonMin = 2250;
        int16_t leftButtonMax = 750;
        int16_t rightButtonMin = 2250;
        int16_t rightButtonMax = 750;

        int16_t leftVertical = ServoDecode.GetChannelPulseWidth(3);
        int16_t rightVertical = ServoDecode.GetChannelPulseWidth(2);
        int16_t leftHorizontal = ServoDecode.GetChannelPulseWidth(4);
        int16_t rightHorizontal = ServoDecode.GetChannelPulseWidth(1);
        int16_t leftButtons = ServoDecode.GetChannelPulseWidth(5);
        int16_t rightButtons = ServoDecode.GetChannelPulseWidth(6);
        
        if(leftButtons < leftButtonMin)
        leftButtonMin = leftButtons;
        if(leftButtons > leftButtonMax)
        leftButtonMax = leftButtons;
        
        if(rightButtons < rightButtonMin)
        rightButtonMin = rightButtons;
        if(rightButtons > rightButtonMax)
        rightButtonMax = rightButtons;
        
        Serial.println("leftButtons: ");
        Serial.println(leftButtons);
        Serial.println("leftButtonMin: ");
        Serial.println(leftButtonMin);
        Serial.println("leftButtonMax: ");
        Serial.println(leftButtonMax);
        
        Serial.println("rightButtons: ");
        Serial.println(rightButtons);
        Serial.println("rightButtonMin: ");
        Serial.println(rightButtonMin);
        Serial.println("rightButtonMax: ");
        Serial.println(rightButtonMax);
        
    	leftVertical = map(leftVertical, 750, 2250, -127, 127);       
       rightVertical = map(rightVertical, 750, 2250, -127, 127); 
        leftHorizontal = map(leftHorizontal, 750, 2250, -127, 127);       
       rightHorizontal = map(rightHorizontal, 750, 2250, -127, 127);      
     
         //int8_t strafe = leftHorizontal + rightHorizontal;
         //constrain(strafe, -127, 127);
         
         wheelSpeed[LF] =  leftVertical;// - strafe;
         wheelSpeed[RF] =  rightVertical;// + strafe;
         wheelSpeed[LR] =  leftVertical;// + strafe;
         wheelSpeed[RR] =  rightVertical;// - strafe;
         
         drive4wheelSpeeds(wheelSpeed);
      }
      else if(ServoDecode.getState()== FAILSAFE_state)// radio not ready
      {         
            fullStop(); 
      } 
      else
        fullStop();     
}




void autonomousDriveLoop()
{

}

void endlessBlink()
{
      while(true)
      {
          digitalWrite(TEENSY_LED_PIN, HIGH);
          delay(400);          
          digitalWrite(TEENSY_LED_PIN, LOW);
          delay(750);
      }
}

void blinkWhile(boolean condition)
{
    while(condition)
      {
          digitalWrite(TEENSY_LED_PIN, HIGH);
          delay(250);          
          digitalWrite(TEENSY_LED_PIN, LOW);
          delay(250);
      }
}

void blinkNtimes(uint16_t N)
{
    
    for(uint16_t i = 0; i < N; i++)
      {
          digitalWrite(TEENSY_LED_PIN, HIGH);
          delay(500);          
          digitalWrite(TEENSY_LED_PIN, LOW);
          delay(250);
      }
    
}

void motorPowerLoss()
{
  while(!(digitalRead(FRONT_POWER_PIN)) && !(digitalRead(REAR_POWER_PIN))) //wait here for power to appear at both motor controllers
  {
      blinkNtimes(1);// blink until power is good
  }
  encoderReset();
  fullStop();
  if(getMD25SpeedByteFormat(FRONT_MD25_ADDR) != 1)
  setMD25SpeedByteFormat(FRONT_MD25_ADDR, 1);  
  if(getMD25SpeedByteFormat(REAR_MD25_ADDR) != 1)
  setMD25SpeedByteFormat(REAR_MD25_ADDR, 1);  
  //frontSpeedByteFormat = getMD25SpeedByteFormat(FRONT_MD25_ADDR);
  //rearSpeedByteFormat = getMD25SpeedByteFormat(REAR_MD25_ADDR);
  fullStop(); 
  setAutoSpeedRegulationOn(FRONT_MD25_ADDR);
  setAutoSpeedRegulationOn(REAR_MD25_ADDR);
  setTimeoutOn(FRONT_MD25_ADDR);
  setTimeoutOn(REAR_MD25_ADDR);
}

void operationalModeSetup()
{
    motorPowerLoss();  
  
    blinkNtimes(operationalMode);
    
    switch (operationalMode) 
    {
    case STATIC_VOLTAGE_TEST: 

      break;
    case STATIC_CAPACITANCE_TEST:
      
      break;
    case STATIC_TEMPERATURE_TEST:
      
      break;
    case STATIC_SIGNAL_TEST:
      
      break;
    case RADIO_CONTROL_DRIVE_TEST:
      radioControlSetup();
      break;
    case AUTONOMOUS_DRIVE_TEST:
      autonomousDriveSetup();
      break;      
    case COMPETITION_FAIL_SAFE:
      competitionFailSafeSetup();
      break;
    case START:
      startSetup();
      break;
    default: 
      // if nothing else matches, blink led indicating a problem      
      blinkNtimes(1);
    }
}

void operationalModeLoop()
{// operational modes:
/*
STATIC_VOLTAGE_TEST , STATIC_CAPACITANCE_TEST , STATIC_TEMPERATURE_TEST , STATIC_SIGNAL_TEST , RADIO_CONTROL_DRIVE_TEST, AUTONOMOUS_DRIVE_TEST, 
FOLLOW_RIGHT_WALL, FOLLOW_LEFT_WALL, DRIVE_STRAIGHT_X_INCHES, TURN_90DEGREES, TURN_TO_NORTH, GO_AROUND_CENTER_FROM_NEAR, GO_AROUND_CENTER_FROM_FAR,
GO_AROUND_BOX_LEFT_FROM_RIGHT, GO_AROUND_BOX_RIGHT_FROM_LEFT, CONTINUE_STRAIGHT_LEFT, CONTINUE_STRAIGHT_RIGHT,
COMPETITION_FAIL_SAFE,
START,
PULL_UP_TO_YELLOW_BOX, READ_VOLTAGE, GO_AROUND_YELLOW_BOX, 
PULL_UP_TO_BLUE_BOX, READ_CAPACITANCE, GO_AROUND_BLUE_BOX, GO_AROUND_CENTER_BOARD_SEEK_TEMPERATURE,
PULL_UP_TO_GREEN_BOX, READ_TEMPERATURE, GO_AROUND_GREEN_BOX,
PULL_UP_TO_RED_BOX, READ_SIGNAL, GO_AROUND_RED_BOX, GO_AROUND_CENTER_BOARD,
FINISH_LAP,
 

// operations we probably wont have time to write
LINE_FOLLOW, SEEK_YELLOW, SEEK_BLUE, SEEK_GREEN, SEEK_RED, SEEK_TEMPERATURE
*/
    
        
    switch (operationalMode) 
    {
    case STATIC_VOLTAGE_TEST:
      staticVoltageLoop();
      break;
    case STATIC_CAPACITANCE_TEST:
      staticCapacitanceLoop();
      break;
    case STATIC_TEMPERATURE_TEST:
      staticTemperatureLoop();
      break;
    case STATIC_SIGNAL_TEST:
      staticSignalLoop();
      break;
    case RADIO_CONTROL_DRIVE_TEST:
      radioControlLoop();
      break;
    case AUTONOMOUS_DRIVE_TEST:
      autonomousDriveLoop();
      break;
    case FOLLOW_RIGHT_WALL:
      followRightWallLoop();
      break;
    case FOLLOW_LEFT_WALL:
      followLeftWallLoop();
      break;
    case DRIVE_STRAIGHT_X_INCHES:
      driveStraightXinchesLoop();
      break;
    case TURN_90DEGREES:
      turn90degreesLoop();
      break;
    case TURN_TO_NORTH:
      turnNorthLoop();
      break;
    case GO_AROUND_CENTER_FROM_NEAR:
      goAroundCenterFromNearLoop();
      break;
    case GO_AROUND_CENTER_FROM_FAR:
      goAroundCenterFromFarLoop();
      break;
    case GO_AROUND_BOX_LEFT_FROM_RIGHT:
      goAroundBoxLeftFromRightLoop();
      break;
    case GO_AROUND_BOX_RIGHT_FROM_LEFT:
      goAroundBoxRightFromLeftLoop();
      break;
    case CONTINUE_STRAIGHT_LEFT:
      continueStraightLeftLoop();
      break;
    case CONTINUE_STRAIGHT_RIGHT:
      continueStraightRightLoop();
      break;
    case COMPETITION_FAIL_SAFE:
      competitionFailSafeLoop();
      break;
    case START:
      startLoop();//should never be entered.  Start is only called once from setup().  Use for debug only.
      break;
    case PULL_UP_TO_YELLOW_BOX:
      pullUpToYellowBoxLoop();
      break;
    case READ_VOLTAGE:
      readVoltageLoop();
      break;
    case GO_AROUND_YELLOW_BOX:
      goAroundYellowBoxLoop();
      break;
    case PULL_UP_TO_BLUE_BOX:
      pullUpToBlueBoxLoop();
      break;
    case READ_CAPACITANCE:
      readCapacitanceLoop();
      break;
    case GO_AROUND_BLUE_BOX:
      goAroundBlueBoxLoop();
      break;
    case GO_AROUND_CENTER_BOARD_SEEK_TEMPERATURE:
      goAroundCenterBoardSeekTemperatureLoop();
      break;
    case PULL_UP_TO_GREEN_BOX:
      pullUpToGreenBoxLoop();
      break;
    case READ_TEMPERATURE:
      readTemperatureLoop();
      break;
    case GO_AROUND_GREEN_BOX:
      goAroundGreenBoxLoop();
      break;
    case PULL_UP_TO_RED_BOX:
      pullUpToRedBoxLoop();
      break;
    case READ_SIGNAL:
      readSignalLoop();
      break;
    case GO_AROUND_RED_BOX:
      goAroundRedBoxLoop();
      break;
    case GO_AROUND_CENTER_BOARD:
      goAroundCenterBoardLoop();
      break;
    case FINISH_LAP:
      break;
    
      
    default: 
      // if nothing else matches, blink led indicating a problem      
      blinkNtimes(1);// should never happen
      
      
    }

}




