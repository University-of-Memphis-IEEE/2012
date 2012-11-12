#ifndef temperature_h
#define temperature_h
#include "Arduino.h"

//must support operationalMode
// SEEK_TEMPERATURE 

static const uint8_t TPA81_ADDR = 0x68;                          // Address of TPA81 thermopile array
    //Thermopile array READ registers
    static const uint8_t TPA81_VERSION_REG = 0;  //Software Revision
    static const uint8_t TPA81_AMBIENT_REG = 1;  //Ambient Temperature ÃƒÂ¯Ã‚Â¿Ã‚Â½C
    static const uint8_t TPA81_TEMP1_REG = 2;	 //Pixel 1 Temperature ÃƒÂ¯Ã‚Â¿Ã‚Â½C
    static const uint8_t TPA81_TEMP2_REG = 3;	 //Pixel 2 Temperature ÃƒÂ¯Ã‚Â¿Ã‚Â½C
    static const uint8_t TPA81_TEMP3_REG = 4;	 //Pixel 3 Temperature ÃƒÂ¯Ã‚Â¿Ã‚Â½C
    static const uint8_t TPA81_TEMP4_REG = 5;	 //Pixel 4 Temperature ÃƒÂ¯Ã‚Â¿Ã‚Â½C
    static const uint8_t TPA81_TEMP5_REG = 6;	 //Pixel 5 Temperature ÃƒÂ¯Ã‚Â¿Ã‚Â½C
    static const uint8_t TPA81_TEMP6_REG = 7;	 //Pixel 6 Temperature ÃƒÂ¯Ã‚Â¿Ã‚Â½C
    static const uint8_t TPA81_TEMP7_REG = 8;	 //Pixel 7 Temperature ÃƒÂ¯Ã‚Â¿Ã‚Â½C
    static const uint8_t TPA81_TEMP8_REG = 9;	 //Pixel 8 Temperature ÃƒÂ¯Ã‚Â¿Ã‚Â½C
    //Thermopile array WRITE registers
    static const uint8_t TPA81_CMD_REG = 0;    //Command Register
        //Commands
            //Servo Position, Commands 0 to 30 set the servo position. There are 31 steps (0-30) which typically represent 180ÃƒÂ¯Ã‚Â¿Ã‚Â½ rotation on a Hitec HS311 servo. The calculation is SERVO_POS*60+540uS. So the range of the servo pulse is 0.54mS to 2.34mS in 60uS steps. Writing any other value to the command register will stop the servo pulses. 
//            Decimal	Hex
//                0	0x00	 Set servo position to minimum
//                nn	nn	 Set servo position
//                31	0x1F	 Set servo position to maximum
//           //Change address 	 	 
//                160	0xA0	1st in sequence to change I2C address
//                165	0xA5	3rd in sequence to change I2C address
//                170	0xAA	2nd in sequence to change I2C address
    static const uint8_t TPA81_SERVO_RANGE_REG = 1;    //Servo Range (V6 or higher only)
   
   
void setServo(uint8_t x)// active range 0-30 which usually represents about 180 degrees, 31 stops servo pulses. The calculation is SERVO_POS*60+540uS. So the range of the servo pulse is 0.54mS to 2.34mS in 60uS steps.  
{
  if (x > 31)
    x = 31;
     Wire.beginTransmission(TPA81_ADDR);
     Wire.send(TPA81_CMD_REG);
     Wire.send(x);   
     Wire.endTransmission();
}

void setServoRange(uint8_t x)//default:120, acceptable values 20-120; The calculation for the range in uS is ((31*ServoRange)/2). Setting a range of 20 will give a range of (31*20)/2 or 310uS. Setting a range of 120 will give a range of (31*120)/2 or 1860uS. In all cases the available range is centered on the servo's mid position of 1500uS
{
     Wire.beginTransmission(TPA81_ADDR);
     Wire.send(TPA81_SERVO_RANGE_REG);
     Wire.send(x);   
     Wire.endTransmission();
}

int8_t getAmbient()
{
   Wire.beginTransmission(TPA81_ADDR);          
   Wire.send(TPA81_AMBIENT_REG);                              
   Wire.endTransmission();
   
   Wire.requestFrom(TPA81_ADDR, (uint8_t)1);            
   while(Wire.available() < 1);              
   int8_t ambient = Wire.receive(); 
   return(ambient);
}

void fillTemperatureArray(int8_t tempArray[]) //array is always length 8 
{
  for(int i = TPA81_TEMP1_REG; i <= TPA81_TEMP8_REG; i++)
  {
  Wire.beginTransmission(TPA81_ADDR);          
   Wire.send(i);                              
   Wire.endTransmission();
   
   Wire.requestFrom(TPA81_ADDR, (uint8_t)1);            
   while(Wire.available() < 1);              
   tempArray[i-TPA81_TEMP1_REG] = Wire.receive(); 
  }
}

#endif



