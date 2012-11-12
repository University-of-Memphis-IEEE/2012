#include <Arduino.h>
//#include "ServoDecode.h"




String stateStrings[] = {
  "NOT_SYNCHED", "ACQUIRING", "READY", "in Failsafe"};

uint16_t xraw, yraw;// onboard single joystick raw values
int16_t throttle, steering;// onboard single joystick conditioned values
uint16_t leftPulsewidth, rightPulsewidth;// R/C joystick raw values channel 2,3
int leftSpd, rightSpd;
boolean e_stop_activated;
// end global declarations

//functions

void configure()//used for debugging, testing, and capturing typical values for setting up constants
{
    int pulsewidth;
    while(!digitalRead(SETUP_PIN))
    {   
        // print the decoder state
      if( ServoDecode.getState()!= READY_state) {
        Serial.print("The decoder is ");
        Serial.println(stateStrings[ServoDecode.getState()]);
        for ( int i =0; i <=MAX_CHANNELS; i++ ){ // print the status of the first four channels
    	Serial.print("Cx "); // if you see this, the decoder does not have a valid signal
    	Serial.print(i);
    	Serial.print(" invalid pulsewidth : ");
    	pulsewidth = ServoDecode.GetChannelPulseWidth(i);
    	Serial.print(pulsewidth);
    	Serial.print("  ");
        }
        Serial.println("");
      }
      else {
        // decoder is ready, print the channel pulse widths
        for ( int i =1; i <=MAX_CHANNELS; i++ ){ // print the status of the first four channels
    	Serial.print("Channel ");
    	Serial.print(i);
    	Serial.print(" pulsewidth : ");
    	pulsewidth = ServoDecode.GetChannelPulseWidth(i);
    	Serial.print(pulsewidth);
    	Serial.print("  ");
        }
        Serial.println("");        
      }
      Serial.print("Onboard Joystick X axis : ");
      Serial.print(analogRead(JOYSTICK_X_PIN));
      Serial.println("");
      Serial.print("Onboard Joystick Y axis : ");
      Serial.print(analogRead(JOYSTICK_Y_PIN));
      Serial.println("");
      Serial.print("Joystick button: ");
      Serial.print((digitalRead(JOYSTICK_BUTTON_PIN)) ? "not pushed" : "pushed");
      Serial.println("");
      Serial.print("E Stop button: ");
      Serial.print((digitalRead(E_STOP_PIN)) ? "not pushed" : "pushed");
      Serial.println("");
      Serial.print("Soft Stop button: ");
      Serial.print((digitalRead(SOFT_STOP_PIN)) ? "not pushed" : "pushed");
    
    
      delay(500); // update 2 times a second
    }
}
 

void updateJoystick()
{    
// capture joystick position
    //digitalRead(JOY_BUTTON_PIN);
    yraw = analogRead(JOYSTICK_Y_PIN);
    xraw = analogRead(JOYSTICK_X_PIN);
    
    // scale x and y axis so that both are zeroed at natural center of potentiometer, implement deadband
    if(yraw > YRAW_CENTERED + HALF_DEADBAND)//forward
    {
      throttle = map(yraw, YRAW_CENTERED + HALF_DEADBAND, 1023, 0, 255);      
      if(xraw > XRAW_CENTERED + HALF_DEADBAND)//left
      {
        steering = map(xraw, XRAW_CENTERED + HALF_DEADBAND, 1023, -0, -255);// reverse pot coordinates to agree with cartesian        
      }
      else if(xraw < XRAW_CENTERED - HALF_DEADBAND)// right
      {
        steering = map(xraw, XRAW_CENTERED - HALF_DEADBAND, 0, 0, 255);// reverse pot coordinates to agree with cartesian        
      }
      else // in X deadband
      {
        steering = 0;
      }
    }
    
    else if(yraw < YRAW_CENTERED - HALF_DEADBAND)//reverse
    {
      throttle = map(yraw, YRAW_CENTERED - HALF_DEADBAND, 0, -0, -255);      
      if(xraw > XRAW_CENTERED + HALF_DEADBAND)//left
      {
        steering = map(xraw, XRAW_CENTERED + HALF_DEADBAND, 1023, -0, -255);// reverse pot coordinates to agree with cartesian        
      }
      else if(xraw < XRAW_CENTERED - HALF_DEADBAND)// right
      {
        steering = map(xraw, XRAW_CENTERED - HALF_DEADBAND, 0, 0, 255);// reverse pot coordinates to agree with cartesian        
      }
      else// in X deadband
      {
        steering = 0;
      }
    }
    else //in Y deadband
    {
      throttle = 0;
      if(xraw > XRAW_CENTERED + HALF_DEADBAND)//left
      {
        steering = map(xraw, XRAW_CENTERED + HALF_DEADBAND, 1023, -0, -255);// reverse pot coordinates to agree with cartesian        
      }
      else if(xraw < XRAW_CENTERED - HALF_DEADBAND)// right
      {
        steering = map(xraw, XRAW_CENTERED - HALF_DEADBAND, 0, 0, 255);// reverse pot coordinates to agree with cartesian        
      }
      else// in X deadband
      {
        steering = 0;
      }
    }  
}

void updateRC()
{

}

void applySpeed_Sabertooth_simplifiedSerial()
{
// motor 1 is left  polarity determined by function
// motor 2 is right
//   Required  Sabertooth DIP switch Settings
//  1   2   3   4   5   6 
// on  off on   x   x   x
/*   Mode 3: Simplified serial.
 There is a Slave Select mode which allows the use of multiple
Sabertooth 2x25 from a single microcontroller serial port.
The transmit line from the host is connected to S1.
Sabertooth controls two motors with one 8 byte character, when operating in Simplified
Serial mode, each motor has 7 bits of resolution. Sending a character between 1 and 127 will
control motor 1. 1 is full reverse, 64 is stop and 127 is full forward. Sending a character between
128 and 255 will control motor 2. 128 is full reverse, 192 is stop and 255 is full forward.
Character 0 (hex 0x00) is a special case. Sending this character will shut down both motors.
Simplified Serial operates with an 8N1 protocol – 8 data bytes, no parity bits and one stop bit.
Serial data is sent to input S1. The baud rate is selected
with switches 4 and 5. Commands are sent as single bytes.
Sending a value of 1-127 will command motor 1 Sending a
value of 128-255 will command motor 2. Sending a value
of 0 will shut down both motors.  The maximum update speed on the Sabertooth is approximately 2000
commands per second.
9600 Baud: 01x10x 
//  1   2   3   4   5   6 
// on  off on  off on  on
19200 Baud: 01x01x
//  1   2   3   4   5   6 
// on  off on  on  off on
38400 Baud: 01x11x
//  1   2   3   4   5   6 
// on  off on  off off on
*/
    if(e_stop_activated)// sudden emergency stop requested
    {
        Serial.write((byte)0); //all stop motor driver
        digitalWrite(PARKING_BRAKE_PIN, LOW);//engage parking brake
    }
    else
    {
        int16_t driveValue = -1;
        // left 1-64-127
        if(leftSpd < 0)//reverse commanded
        {//map(value, fromLow, fromHigh, toLow, toHigh)
            driveValue = map(leftSpd, -1, -255, 63, 1);
            constrain(driveValue, 1, 63);
            Serial.write((byte)driveValue);
        }
        else if(leftSpd > 0)//forward commanded
        {
            driveValue = map(leftSpd, 1, 255, 65, 127);
            constrain(driveValue, 65, 127);
            Serial.write((byte)driveValue);
        }
        else//stop commanded
        Serial.write((byte)64);
        
        //right 128-192-255
        if(rightSpd < 0)//reverse commanded
        {//map(value, fromLow, fromHigh, toLow, toHigh)
            driveValue = map(leftSpd, -1, -255, 191, 128);
            constrain(driveValue, 128, 191);
            Serial.write((byte)driveValue);
        }
        if(rightSpd > 0)//forward commanded
        {
            driveValue = map(leftSpd, 1, 255, 193, 255);
            constrain(driveValue, 193, 255);
            Serial.write((byte)driveValue);
        }
        else//stop commanded
        Serial.write((byte)192);
    }
}
