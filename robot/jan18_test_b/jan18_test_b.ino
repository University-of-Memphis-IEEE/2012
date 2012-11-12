
#include "ServoDecode.h"
#include "Wire.h"
#include "constants.h"
#include "functions.h"
#include "configure.h"
#include <LCDi2cR.h>

LCDi2cR lcd = LCDi2cR(4,40,0x63,0);                  // Creates variable called lcd used for communication with LCD03

void setup()			  // run once, when the sketch starts
{
  Serial.begin(19200);  
  pinMode(RADIO_GOOD_LED_PIN,OUTPUT);//teensy LED
  pinMode(STOP_LED_PIN, OUTPUT);//red LED
  pinMode(BOW_LIGHT_PIN, INPUT);//high impedance state.  Only change to output when actually switching on or off.
  pinMode(SETUP_PIN, INPUT);
  ServoDecode.begin();
  ServoDecode.setFailsafe(2,1200); // set channel 2 failsafe pulsewidth. left vertical stick
  ServoDecode.setFailsafe(3,1200); // set channel 3 failsafe pulsewidth. right vertical stick
  ServoDecode.setFailsafe(5,1200); // set channel 5 failsafe pulsewidth. left buttons, use to activate bowlight
  ServoDecode.setFailsafe(6,1200); // set channel 6 failsafe pulsewidth. right buttons, use to override soft stop remotely
  if(!digitalRead(SETUP_PIN))//jumper SETUP_PIN to ground prior to reset of Arduino to activate
  configure();
}// end setup()

void loop()			   // run over and over again
{  
  if( !digitalRead(E_STOP_PIN)  ||  (ServoDecode.getState()== READY_state && ServoDecode.GetChannelPulseWidth(5) < 600 ))
  e_stop_activated = true;
  else
  e_stop_activated = false;
  
  if(e_stop_activated)
  {
      digitalWrite(STOP_LED_PIN, HIGH);//brake light on
      leftSpd = 0;
      rightSpd = 0;
      applySpeed_Sabertooth_simplifiedSerial();
      digitalWrite(PARKING_BRAKE_PIN, LOW);//apply parking brake
  }
  else if(!digitalRead(SOFT_STOP_PIN))// seated actor stood up
  {
      digitalWrite(PARKING_BRAKE_PIN, HIGH);//release parking brake
      digitalWrite(STOP_LED_PIN, HIGH);//brake light on
      if(leftSpd != 0 || rightSpd != 0)// some speed is still commanded
      {//decelerate to a stop
          if(abs(leftSpd) <= INSTANT_STOP_THRESHOLD)leftSpd = 0;
          if(abs(rightSpd) <= INSTANT_STOP_THRESHOLD)rightSpd = 0;
          leftSpd *= SLOW_PCT/100.0; 
          rightSpd *= SLOW_PCT/100.0;//TODO: check that this works as intended.  Adjust constants untill satisfactory stop is achieved.
      }
      applySpeed_Sabertooth_simplifiedSerial();
          
  }
  else //STOP not engaged
  {
      digitalWrite(STOP_LED_PIN, LOW);//off
      digitalWrite(PARKING_BRAKE_PIN, HIGH);//release parking brake
      if(ServoDecode.getState()== READY_state) //Radio Control is functioning properly and stop not engaged
      {// drive under radio control
        leftPulsewidth = ServoDecode.GetChannelPulseWidth(2);
        rightPulsewidth = ServoDecode.GetChannelPulseWidth(3);
    	leftSpd = map(leftPulsewidth, 750, 2500, -255, 255);// adjust 2nd/3rd arguements to reflect actual received min/max pulsewidths.       
        rightSpd = map(rightPulsewidth, 750, 2500, -255, 255);    
      }    
      else // Something is wrong with Radio Control.  stop not engaged. Use onboard joystick.
      {
          updateJoystick();
          //transfer from x,y to l,r
          leftSpd = throttle + steering;
          rightSpd = throttle - steering;
      }  
      
      // optional section to tailor stick behaviors.  Affects any stick used
      leftSpd = map(leftSpd, -255, 255, -255, 255);// lower the absolute value of 4th/5th arguements to limit top speed and decrease stick sensitivity.  
      rightSpd = map(rightSpd, -255, 255, -255, 255);// Top speed occurs at edges of stick travel. slope
      //or
      // TODO: write exponential acceleration function
      // Stick will have decreased sensitivity around centerpoint, increased sensitivity toward edges.  
      // or
      constrain(leftSpd,-255, 255); // lower the absolute value of these numbers to limit top speed.
      constrain(rightSpd,-255, 255);// Will not change stick sensitivity.  Top speed will occur before edge of stick travel.
      
      applySpeed_Sabertooth_simplifiedSerial();
   }  
}//end loop()



