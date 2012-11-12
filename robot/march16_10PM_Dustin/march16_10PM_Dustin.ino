
//external libraries
#include "Wire.h"
#include "HardwareSerial.h"

//global variables 
enum Wheel_t {LF,RF,LR,RR}; 
int16_t wheelSpeed[4];
enum Direction_t {UNKNOWN, LEFT, RIGHT} ;
enum Task_t {VOLTAGE = 1, CAPACITANCE, TEMPERATURE, SIGNAL} ;
Task_t task;
//Task_t previousTask;
Direction_t taskDirection;
enum TaskColor_t {YELLOW = 1, BLUE, GREEN, RED} ;
boolean startButtonBeenPushed = false;
enum OperationalMode_t {LCD_TEST, STATIC_VOLTAGE_TEST , STATIC_CAPACITANCE_TEST , STATIC_TEMPERATURE_TEST , STATIC_SIGNAL_TEST , DISPLAY_ADC_TEST, DISPLAY_COMPASS_TEST, DISPLAY_SONAR_TEST, INTERRUPT_TEST, OTHER_TEST, RADIO_CONTROL_DRIVE_TEST, AUTONOMOUS_DRIVE_TEST, QUANTIFY_SPEEDS_TEST,
FOLLOW_RIGHT_WALL, FOLLOW_LEFT_WALL, DRIVE_STRAIGHT_X_CLICKS, TURN_MINIMUM, TURN_45_DEGREES, TURN_90_DEGREES, TURN_180_DEGREES, TURN_TO_NORTH, GO_AROUND_CENTER_FROM_NEAR, GO_AROUND_CENTER_FROM_FAR,
GO_AROUND_BOX_LEFT_FROM_RIGHT, GO_AROUND_BOX_RIGHT_FROM_LEFT, CONTINUE_STRAIGHT_LEFT, CONTINUE_STRAIGHT_RIGHT,
COMPETITION_FAIL_SAFE,
START, 
PULL_UP_TO_YELLOW_BOX, READ_VOLTAGE, GO_AROUND_YELLOW_BOX, 
PULL_UP_TO_BLUE_BOX, READ_CAPACITANCE, GO_AROUND_BLUE_BOX, GO_AROUND_CENTER_BOARD_SEEK_TEMPERATURE,
PULL_UP_TO_GREEN_BOX, READ_TEMPERATURE, GO_AROUND_GREEN_BOX,
PULL_UP_TO_RED_BOX, READ_SIGNAL, GO_AROUND_RED_BOX, GO_AROUND_CENTER_BOARD, 
FINISH_LAP,
// operations we probably wont have time to write
LINE_FOLLOW, SEEK_YELLOW, SEEK_BLUE, SEEK_GREEN, SEEK_RED, SEEK_TEMPERATURE };

OperationalMode_t operationalMode =  START;  // testing mode
//OperationalMode_t operationalMode = COMPETITION_FAIL_SAFE;  // competition hail mary mode.  If something goes horribly wrong with operationalMode switching.
//OperationalMode_t operationalMode = START;                  // competition mode.

static const uint16_t DISPLAY_INTERVAL = 1500;
static const uint8_t NUM_DISPLAY_SCREENS = 7; 
    // create elapsedMillis outside loop(), to
    // retain its value each time loop() runs.
    // // "sinceXXX" variables auto-increase
    elapsedMillis sinceDisplayCompass = sinceDisplayCompass + (DISPLAY_INTERVAL * 7);
    elapsedMillis sinceDisplayWheelSpeeds = sinceDisplayWheelSpeeds + (DISPLAY_INTERVAL * 6);   
    elapsedMillis sinceDisplayWheelCurrents = sinceDisplayWheelCurrents + (DISPLAY_INTERVAL * 5);
    elapsedMillis sinceDisplaySonars = sinceDisplaySonars + (DISPLAY_INTERVAL * 4);     
    elapsedMillis sinceDisplayWheelEncoders = sinceDisplayWheelEncoders + (DISPLAY_INTERVAL * 3);     
    elapsedMillis sinceDisplayTemperatures = sinceDisplayTemperatures + (DISPLAY_INTERVAL * 2);
    elapsedMillis sinceDisplayTask = sinceDisplayTask + (DISPLAY_INTERVAL * 1);

//functional header files saved in sketch folder
#include "functionPrototypes.h"
#include "debug.h"
#include "lcd.h"
#include "ServoDecode.h"
#include "motor.h"
#include "compass.h"
#include "sonar.h"
#include "temperature.h"
#include "tasks.h"
#include "camera.h"
#include "movement.h"
#include "operationalMode.h"




void setup()			  // run once, when the sketch starts 
{
  Wire.begin();
  Serial.begin(57600);  
  HardwareSerial camera = HardwareSerial();
  lcd.begin();  
  setAccelerationBoth(6);
  setupTaskBoardNeutral();
  pinMode(START_PIN, INPUT_PULLUP);
  pinMode(TEENSY_LED_PIN,OUTPUT);//teensy LED
  pinMode(LED_SCANNER_PIN,OUTPUT);//teensy LED
  digitalWrite(LED_SCANNER_PIN, HIGH);
  sonarSetup();// set pinmode, etc
  boolean startButtonBeenPushed = false;
  attachInterrupt(3, startButtonFallingHandler, FALLING); // start button made contact
  attachInterrupt(3, startButtonRisingHandler, RISING); // start button released contact
  attachInterrupt(2, frontIRrisingHandler, RISING); // IR sensor within range
  attachInterrupt(2, frontIRfallingHandler, FALLING); // IR sensor out of range
  attachInterrupt(7, leftBumperSwitchFallingHandler, FALLING); // left whisker made contact
  attachInterrupt(7, leftBumperSwitchRisingHandler, RISING); // left whisker released contact
  attachInterrupt(6, rightBumperSwitchFallingHandler, FALLING); // right whisker made contact
  attachInterrupt(6, rightBumperSwitchRisingHandler, RISING); // right whisker released contact
  interrupts();  
  lcd.clear();
  lcd.setCsrLC(1,1);  
  lcd.print("U of Memphis");
  lcd.setCsrLC(2, 1);
  lcd.print("IEEE student branch");
  lcd.setCsrLC(3, 1);
  lcd.print("TigerBot 2012");
  delay(2000);

  
  
  operationalModeSetup();  
  
  
}// end setup()


void loop()			   // run over and over again
{
   
    motorPowerLoss();//reset critical parameters
    
    // if the selected operationalMode is listed before START it will not change, and be rerun each time loop begins again.
    if(operationalMode >= START)// all operational modes that must be performed while doing a lap should be enumerated sequentially between START and FINISH_LAP
    {
        operationalMode = (OperationalMode_t) ((uint8_t)operationalMode + 1) ;// equivalent to   operationalMode++
        if(operationalMode == FINISH_LAP)
        {
            operationalMode = (OperationalMode_t) ((uint8_t)START + 1); //start a new lap.  Equivalent to   operationalMode = (START + 1);
        }
    }
    operationalModeLoop();
 
}//end loop()

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
