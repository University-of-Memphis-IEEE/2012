
//external libraries
#include "Wire.h"

//     Left side pins                         GND
//                                             27
//                             I2C   SCL        0
//                             I2C   SDA        1
//      camera will use serial pins   Rx        2 
//                                    Tx        3
static const uint8_t ICP_PIN =                  4;	   // this interrupt handler must use pin D4 on Teensy ++
static const uint8_t REAR_SRF05_ECHO_PIN =      5;
static const uint8_t TEENSY_LED_PIN      =      6;
static const uint8_t FRONT_POWER_PIN     =      7;
static const uint8_t REAR_POWER_PIN      =      8;
static const uint8_t START_PIN           =      9;
//                                             10
//                                             11
//                                             12
//                                             13
//                                             14
//                                             15
//                                             16
//                                             17

//    Right side Pins                         +5V
static const uint8_t FRONT_SRF05_ECHO_PIN =    26;
static const uint8_t LEFT_SRF05_ECHO_PIN =     25;
static const uint8_t RIGHT_SRF05_ECHO_PIN =    24;
static const uint8_t FRONT_SRF05_TRIGGER_PIN = 23;
static const uint8_t LEFT_SRF05_TRIGGER_PIN =  22;                        // Pin for SRF05 sonar
static const uint8_t RIGHT_SRF05_TRIGGER_PIN = 21;                       // Pin for SRF05 sonar
static const uint8_t REAR_SRF05_TRIGGER_PIN =  20;                        // Pin for SRF05 sonar
//                                             19
//                                             18
//                                            GND
//                                           AREF
static const uint8_t VOLT_SIGNAL_ADC_PIN =     38; // A0 
//                                             39  // A1
//                                             40  // A2
//                                             41  // A3
//                                             42  // A4
//                                             43  // A5
//                                             44  // A6
//                                             45  // A7


//global variables available in all modes
enum Wheel_t{LF,RF,LR,RR}; 
int16_t wheelSpeed[4];
enum OperationalMode_t{STATIC_VOLTAGE_TEST , STATIC_CAPACITANCE_TEST , STATIC_TEMPERATURE_TEST , STATIC_SIGNAL_TEST , RADIO_CONTROL_DRIVE_TEST, AUTONOMOUS_DRIVE_TEST, 
FOLLOW_RIGHT_WALL, FOLLOW_LEFT_WALL, DRIVE_STRAIGHT_X_INCHES, TURN_90DEGREES, TURN_TO_NORTH, GO_AROUND_CENTER_FROM_NEAR, GO_AROUND_CENTER_FROM_FAR,
COMPETITION_FAIL_SAFE,
START,
PULL_UP_TO_YELLOW_BOX, READ_VOLTAGE, GO_AROUND_YELLOW_BOX, 
PULL_UP_TO_BLUE_BOX, READ_CAPACITANCE, GO_AROUND_BLUE_BOX, GO_AROUND_CENTER_BOARD_SEEK_TEMPERATURE,
PULL_UP_TO_GREEN_BOX, READ_TEMPERATURE, GO_AROUND_GREEN_BOX,
PULL_UP_TO_RED_BOX, READ_SIGNAL, GO_AROUND_RED_BOX, GO_AROUND_CENTER_BOARD,
GO_AROUND_BOX_LEFT_FROM_RIGHT, GO_AROUND_BOX_RIGHT_FROM_LEFT, CONTINUE_STRAIGHT_LEFT, CONTINUE_STRAIGHT_RIGHT, 
FINISH_LAP,
// operations we probably wont have time to write
LINE_FOLLOW, SEEK_YELLOW, SEEK_BLUE, SEEK_GREEN, SEEK_RED, SEEK_TEMPERATURE };


OperationalMode_t operationalMode = TURN_90DEGREES; //RADIO_CONTROL_DRIVE_TEST; // testing mode
//OperationalMode_t operationalMode = COMPETITION_FAIL_SAFE;  // competition hail mary mode.  If something goes horribly wrong with operationalMode switching.
//OperationalMode_t operationalMode = START;                  // competition mode.

//functional header files saved in sketch folder
#include "debug.h"
#include "ServoDecode.h"
#include "motor.h"
#include "compass.h"
//#include "sonar.h"
#include "temperature.h"
#include "lcd.h"
//#include "tasks.h"
#include "camera.h"
#include "operationalMode.h"

void setup()			  // run once, when the sketch starts 
{
  

  Wire.begin();
  Serial.begin(57600);  
  pinMode(TEENSY_LED_PIN,OUTPUT);//teensy LED
  
  lcd.clear();
  lcd.setCsrLC(0, 0);
  lcd.print("Entering Setup");
  
  operationalModeSetup();

  lcd.clear();
  lcd.setCsrLC(0, 0);
  lcd.print("Exting Setup");  
}// end setup()

void loop()			   // run over and over again
{
    if(!(digitalRead(FRONT_POWER_PIN)) && !(digitalRead(REAR_POWER_PIN)))// power to motors is lost
    {motorPowerLoss();}//reset critical parameters
    
    // if the selected operationalMode is listed before START it will not change, and be rerun each time loop begins again.
    if(operationalMode >= START)// all operational modes that must be performed while doing a lap should be enumerated sequentially between START and FINISH_LAP
    {
        operationalMode = (OperationalMode_t) ((uint8_t)operationalMode + 1) ;// equivalent to   operationalMode++
        if(operationalMode = FINISH_LAP)
        {
            operationalMode = (OperationalMode_t) ((uint8_t)START + 1); //start a new lap.  Equivalent to   operationalMode = (START + 1);
        }
    }
    operationalModeLoop();
 
}//end loop()

