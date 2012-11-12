//START
void startSetup()//competition start function
{
  sonarSetup();
  digitalWrite(TEENSY_LED_PIN, HIGH);
  while(HIGH == digitalRead(START_PIN))
  { // wait in empty loop till start button is pressed   
  }
  digitalWrite(TEENSY_LED_PIN, LOW);
  digitalWrite(LED_SCANNER_PIN, HIGH);
  zeroCompass();
  encoderReset();
  currentSide = RIGHT;
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
  driveForwardXclicks((int32_t)300);
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
  
  
}




//LOOP
void     staticVoltageLoop()
{
  lcd.clear();
  delay(250);
   bool  result;
  result = getYellowVoltageDirection();
  
  if(result == LEFT)
  {
  
  lcd.print("LEFT");
  }
  else
  {
    lcd.setCsrLC(1, 8);
    lcd.print("RIGHT");
  }
  delay(1000);
}

void     staticCapacitanceLoop()
{
  lcd.clear();
  delay(250);
  bool  result;
  result = getBlueCapacitanceDirection();
  
  if(result == LEFT)
  {
  
  lcd.print("capacitance LEFT");
  }
  else
  {
    lcd.setCsrLC(1, 8);
    lcd.print("capacitance RIGHT");
  }
  delay(1000);
      
}
 
void      staticTemperatureLoop()
{
  lcd.clear();
  delay(250);
  bool  result;
  result = getGreenTemperatureDirection();
  
  if(result == LEFT)
  {
  
  lcd.print("temperature LEFT");
  }
  else
  {
    lcd.setCsrLC(1, 8);
    lcd.print("temperature RIGHT");
  }
  delay(1000);
}

void      staticSignalLoop()
{
  lcd.clear();
  delay(250);
   bool  result;
  result = getRedSignalDirection();
  
  if(result == LEFT)
  {
  
  lcd.print("Signal LEFT");
  }
  else
  {
    lcd.setCsrLC(1, 8);
    lcd.print("Signal RIGHT");
  }
  delay(1000);
}
    

     
void      startLoop(){}//should never be entered.  Start is only called once from setup().  Use for debug only.
     
void      pullUpToYellowBoxLoop()
{
    driveForwardXclicks(100);
}
     
void      readVoltageLoop()
{

}
     
void      goAroundYellowBoxLoop()
{

}
    
void      pullUpToBlueBoxLoop()
{
    driveForwardXclicks(100);
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
    driveForwardXclicks(100);
}
     
void      readTemperatureLoop()
{

}
     
void      goAroundGreenBoxLoop()
{

}
    
void      pullUpToRedBoxLoop()
{
    driveForwardXclicks(100);
}
     
void      readSignalLoop()
{
uint16_t result;
result = calibrateSawtoothSignalTask();

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
bool result;
void operationalModeSetup()
{
    motorPowerLoss();   
    //blinkNtimes(operationalMode);
    setupTaskBoardNeutral();
    
    switch (operationalMode) 
    {
    case LCD_TEST:
      LCDdisplay();
      break;
    case STATIC_VOLTAGE_TEST: 
      setupTaskBoardNeutral();
      break;
    case STATIC_CAPACITANCE_TEST:
      setupTaskBoardNeutral();
      break;
    case STATIC_TEMPERATURE_TEST:
      setupTaskBoardNeutral();  
      break;   
    case STATIC_SIGNAL_TEST:
      setupTaskBoardNeutral();
      break;
    case DISPLAY_ADC_TEST:
      setupTaskBoardNeutral();
      break;
    case OTHER_TEST:
      
      
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
{
        
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
    case DISPLAY_ADC_TEST:
      displayADC();
      break;
    case DISPLAY_COMPASS_TEST:
      displayCompass();
      break; 
    case DISPLAY_SONAR_TEST:
      displaySonars();
      //delay(100);
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
    case TURN_MINIMUM:
      turnMinimum(RIGHT);
      delay(100);
      break;
    case DRIVE_STRAIGHT_X_CLICKS:
      driveForwardXclicks((int32_t)600);
      break;
    case TURN_90_DEGREES:
      
      turn90degrees(RIGHT);
      //displayWheelEncoders();
      delay(500);
      break;
    case TURN_45_DEGREES:
      turn45degrees(RIGHT);
      delay(500);
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
    
     driveForwardXclicks(25);
      break;
    case READ_VOLTAGE:
      
      
      break;
    case GO_AROUND_YELLOW_BOX:
    if(getYellowVoltageDirection() != currentSide)
      {
          turn90degrees(!currentSide);
          driveForwardXclicks(boxFaceClicks);
          turn90degrees(currentSide);
          driveForwardXclicks(boxSideClicks);
          currentSide = !currentSide;
      }
    else
      {
         driveForwardXclicks(boxSideClicks);
      }
      turnNorthLoop();
     // goAroundYellowBoxLoop();
      break;
    case PULL_UP_TO_BLUE_BOX:
      //pullUpToBlueBoxLoop();
      break;
    case READ_CAPACITANCE:
     // readCapacitanceLoop();
      break;
    case GO_AROUND_BLUE_BOX:
    if(getBlueCapacitanceDirection() != currentSide)
      {
          turn90degrees(!currentSide);
          driveForwardXclicks(boxFaceClicks);
          turn90degrees(currentSide);
          driveForwardXclicks(boxSideClicks);
          currentSide = !currentSide;
      }
    else
      {
         driveForwardXclicks(boxSideClicks);
      }
      turnNorthLoop();
     // goAroundBlueBoxLoop();
      break;
    case GO_AROUND_CENTER_BOARD_SEEK_TEMPERATURE:
    if(currentSide == RIGHT)
    {
    goAroundCenterFromNearLoop();
    }
    else
    {
    goAroundCenterFromFarLoop();
    currentSide == RIGHT;
    }
    turnSouthLoop();
     // goAroundCenterBoardSeekTemperatureLoop();
      break;
    case PULL_UP_TO_GREEN_BOX:
     // pullUpToGreenBoxLoop();
      break;
    case READ_TEMPERATURE:
     // readTemperatureLoop();
      break;
    case GO_AROUND_GREEN_BOX:
    if(getGreenTemperatureDirection() != currentSide)
      {
          turn90degrees(!currentSide);
          driveForwardXclicks(boxFaceClicks);
          turn90degrees(currentSide);
          driveForwardXclicks(boxSideClicks);
          currentSide = !currentSide;
      }
    else
      {
         driveForwardXclicks(boxSideClicks);
      }
      turnSouthLoop();
      //goAroundGreenBoxLoop();
      break;
    case PULL_UP_TO_RED_BOX:
     // pullUpToRedBoxLoop();
      break;
    case READ_SIGNAL:
     // readSignalLoop();
      break;
    case GO_AROUND_RED_BOX:
      if(getRedSignalDirection() != currentSide)
      {
          turn90degrees(!currentSide);
          driveForwardXclicks(boxFaceClicks);
          turn90degrees(currentSide);
          driveForwardXclicks(boxSideClicks);
          currentSide = !currentSide;
      }
    else
      {
         driveForwardXclicks(boxSideClicks);
      }
     // goAroundRedBoxLoop();
      break;
    case GO_AROUND_CENTER_BOARD:
    if(currentSide == RIGHT)
    {
    goAroundCenterFromNearLoop();
    }
    else
    {
    goAroundCenterFromFarLoop();
    currentSide == RIGHT;
    }
     // goAroundCenterBoardLoop();
     turnNorthLoop();
      break;
    case FINISH_LAP:
      break;
    
      
    default: 
      // if nothing else matches, blink led indicating a problem      
      blinkNtimes(1);// should not happen unless an invalid operationalMode is selected
      
      
    }

}

/*
case LCD_TEST:
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
      break;
case RADIO_CONTROL_DRIVE_TEST:
      break;
case AUTONOMOUS_DRIVE_TEST:
      break;
case QUANTIFY_SPEEDS_TEST:
      break;
case FOLLOW_RIGHT_WALL:
      break;
case FOLLOW_LEFT_WALL:
      break;
case DRIVE_STRAIGHT_X_CLICKS:
      break;
case TURN_MINIMUM:
      break;
case TURN_45_DEGREES:
      break;
case TURN_90_DEGREES:
      break;
case TURN_180_DEGREES:
      break;
case TURN_TO_NORTH:
      break;
case GO_AROUND_CENTER_FROM_NEAR:
      break;
case GO_AROUND_CENTER_FROM_FAR:
      break;
case GO_AROUND_BOX_LEFT_FROM_RIGHT:
      break;
case GO_AROUND_BOX_RIGHT_FROM_LEFT:
      break;
case CONTINUE_STRAIGHT_LEFT:
      break;
case CONTINUE_STRAIGHT_RIGHT:
      break;
case COMPETITION_FAIL_SAFE:
      break;
case START:
      break; 
case PULL_UP_TO_YELLOW_BOX:
      break;
case READ_VOLTAGE:
      break;
case GO_AROUND_YELLOW_BOX:
      break;
case PULL_UP_TO_BLUE_BOX:
      break;
case READ_CAPACITANCE:
      break;
case GO_AROUND_BLUE_BOX:
      break;
case GO_AROUND_CENTER_BOARD_SEEK_TEMPERATURE:
      break;
case PULL_UP_TO_GREEN_BOX:
      break;
case READ_TEMPERATURE:
      break;
case GO_AROUND_GREEN_BOX:
      break;
case PULL_UP_TO_RED_BOX:
      break;
case READ_SIGNAL:
      break;
case GO_AROUND_RED_BOX:
      break;
case GO_AROUND_CENTER_BOARD:
      break; 
case FINISH_LAP:
      break;
case LINE_FOLLOW:
      break;
case SEEK_YELLOW:
      break;
case SEEK_BLUE:
      break;
case SEEK_GREEN:
      break;
case SEEK_RED:
      break;
case SEEK_TEMPERATURE:
      break;
*/

