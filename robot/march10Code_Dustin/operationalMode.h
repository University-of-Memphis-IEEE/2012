//START
void startSetup()//competition start function
{
  sonarSetup();
  while(!digitalRead(START_PIN))
  { // wait in empty loop till start button is pressed   
  }
  delay(100);
  zeroCompass();
  encoderReset();
}

void competitionFailSafeSetup()
{
  sonarSetup();
  while(!digitalRead(START_PIN))
  { // wait in empty loop till start button is pressed   
  }
  delay(100);
  zeroCompass();
  encoderReset();
  driveForwardXclicks(300);
}



void autonomousDriveSetup()
{
  sonarSetup();
  while(!digitalRead(START_PIN))
  { // wait in empty loop till start button is pressed   
  }
  delay(100);
  zeroCompass();
  encoderReset();
}

void otherTestSetup()
{  
  encoderReset();
  
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






//**********************************************************  SETUP  ********************************************************************

void operationalModeSetup()
{
    motorPowerLoss();  
  
    blinkNtimes(operationalMode);
    
    switch (operationalMode) 
    {
    case LCD_TEST:
      LCDdisplay();
      break;
    case STATIC_VOLTAGE_TEST: 

      break;
    case STATIC_CAPACITANCE_TEST:
      
      break;
    case STATIC_TEMPERATURE_TEST:
      
      break;
    case STATIC_SIGNAL_TEST:
      
      break;
    case OTHER_TEST:
      //turn90degrees(LEFT);
      //autonomousDriveLoop(2000, 180);
      break;
      
    case QUANTIFY_SPEEDS_TEST:
      quantifySpeeds(1);
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
//**********************************************************  LOOP   **********************************************************************************

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
      
    case LCD_TEST:
      LCDdisplay();
      break;
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
    case OTHER_TEST:
    
      
      break;
    case RADIO_CONTROL_DRIVE_TEST:
      radioControlLoop();
      break;
    case AUTONOMOUS_DRIVE_TEST:
      autonomousDriveLoop(2010, 210);
      break;
    case FOLLOW_RIGHT_WALL:
      followRightWallLoop();
      break;
    case FOLLOW_LEFT_WALL:
      followLeftWallLoop();
      break;
    case DRIVE_STRAIGHT_X_CLICKS:
      driveForwardXclicks(600);
      break;
    case TURN_90_DEGREES:
      turn90degrees(RIGHT);
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
      blinkNtimes(1);// should not happen unless an invalid operationalMode is selected
      
      
    }

}






