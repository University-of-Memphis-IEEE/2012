#ifndef motor_h
#define motor_h
#include "Arduino.h"



    static const uint8_t FRONT_MD25_ADDR = 0x58;                    // Address of front MD25 motor control board
    static const uint8_t REAR_MD25_ADDR = 0x5a;                     // Address of rear MD25 motor control board
    //MD25 Motor Driver READ/WRITE registers
    static const uint8_t MD25_LEFT_SPEED_REG = 1;    //Used in mode 0 and 1
    static const uint8_t MD25_RIGHT_SPEED_REG = 0;   //Used in mode 0 and 1
    static const uint8_t MD25_TURN_REG = 1;        //Used in mode 2 and 3 only
    static const uint8_t MD25_SPEED1_REG = 0;    //Alternative name for right speed reg
    static const uint8_t MD25_SPEED2_REG = 1;    //Alternative name for left speed reg
    static const uint8_t MD25_ACCELERATION_REG = 14;	 //Acceleration rate	 Optional Acceleration register 
    static const uint8_t MD25_MODE_REG = 15;  	    //Mode	 Mode of operation (see below)
    /*
    The mode register selects which mode of operation and I2C data input type the user requires. The options being:
    0,    (Default Setting) If a value of 0 is written to the mode register then the meaning of the speed registers is literal speeds in the range of 0 (Full Reverse)  128 (Stop)   255 (Full Forward).

    1,    Mode 1 is similar to Mode 0, except that the speed registers are interpreted as signed values. The meaning of the speed registers is literal speeds in the range of -128 (Full Reverse)   0 (Stop)   127 (Full Forward).

    2,    Writing a value of  2 to the mode register will make speed1 control both motors speed, and speed2 becomes the turn value. 
    Data is in the range of 0 (Full Reverse)  128 (Stop)  255 (Full  Forward).

    3,    Mode 3 is similar to Mode 2, except that the speed registers are interpreted as signed values. 
    Data is in the range of -128  (Full Reverse)  0 (Stop)   127 (Full Forward)
    */
    static const uint8_t MD25_CMD_REG = 16;	 //Command	 Used for reset of encoder counts and module address changes, follow with a command
     // commands
          static const uint8_t MD25_ENCODER_RESET_CMD = 32;	        //20 Hex	Resets the encoder registers to zero
          static const uint8_t MD25_DISABLE_AUTO_SPEEDREG_CMD  = 48;	//30 Hex	Disables automatic speed regulation
          static const uint8_t MD25_ENABLE_AUTO_SPEEDREG_CMD  = 49;	//31 Hex	Enables automatic speed regulation (default)
          static const uint8_t MD25_DISABLE_TIMEOUT_CMD = 50;       	//32 Hex	Disables 2 second timeout of motors (Version 2 onwards only)
          static const uint8_t MD25_ENABLE_TIMEOUT_CMD = 51;        	//33 Hex	Enables 2 second timeout of motors when no I2C comms (default) (Version 2 onwards only)
          static const uint8_t MD25_ADDRESS_CHANGE_1_CMD = 160;	//A0 Hex	1st in sequence to change I2C address
          static const uint8_t MD25_ADDRESS_CHANGE_2_CMD = 170;	//AA Hex	2nd in sequence to change I2C address
          static const uint8_t MD25_ADDRESS_CHANGE_3_CMD = 165;	//A5 Hex	3rd in sequence to change I2C address
           
         
 //MD25  Motor Driver READ ONLY registers
  static const uint8_t MD25_LEFT_ENCODER_A_REG = 2;	 //Encoder 1 position, 1st byte (highest), capture count when read
  static const uint8_t MD25_LEFT_ENCODER_B_REG = 3;    	 //Encoder 1 position, 2nd byte
  static const uint8_t MD25_LEFT_ENCODER_C_REG = 4;	 //Encoder 1 position, 3rd byte
  static const uint8_t MD25_LEFT_ENCODER_D_REG = 5;	 //Encoder 1 position, 4th (lowest byte)
  
  static const uint8_t MD25_RIGHT_ENCODER_A_REG = 6;	 //Ecoder 2 position, 1st  byte (highest), capture count when read
  static const uint8_t MD25_RIGHT_ENCODER_B_REG = 7;	 //Encoder 2 position, 2nd byte
  static const uint8_t MD25_RIGHT_ENCODER_C_REG = 8;	 //Encoder 2 position, 3rd byte
  static const uint8_t MD25_RIGHT_ENCODER_D_REG = 9;	 //Encoder 2 position, 4th byte (lowest byte)
  
  static const uint8_t MD25_BATTERY_VOLTS_REG = 10;	//The supply battery voltage
  static const uint8_t MD25_LEFT_MOTOR_CURRENT_REG = 11;	//The current through motor 1
  static const uint8_t MD25_RIGHT_MOTOR_CURRENT_REG = 12;	//The current through motor 2
  static const uint8_t MD25_VERSION_REG = 13;                   //Software Revision Number

void setAutoSpeedRegulationOn(uint8_t MD25address)
{
     Wire.beginTransmission(MD25address);
     Wire.send(MD25_CMD_REG);
     Wire.send(MD25_ENABLE_AUTO_SPEEDREG_CMD);   
     Wire.endTransmission();     
}

void setAutoSpeedRegulationOff(uint8_t MD25address)
{
    Wire.beginTransmission(MD25address);
     Wire.send(MD25_CMD_REG);
     Wire.send(MD25_DISABLE_AUTO_SPEEDREG_CMD);   
     Wire.endTransmission();
}
  
void setTimeoutOn(uint8_t MD25address)
{
     Wire.beginTransmission(MD25address);
     Wire.send(MD25_CMD_REG);
     Wire.send(MD25_ENABLE_TIMEOUT_CMD);   
     Wire.endTransmission();    
}  

void setTimeoutOff(uint8_t MD25address)
{
    Wire.beginTransmission(MD25address);
     Wire.send(MD25_CMD_REG);
     Wire.send(MD25_DISABLE_TIMEOUT_CMD);   
     Wire.endTransmission();
}
  
int32_t getEncoderCount(Wheel_t wheel)
{        
  int32_t count = 0; 
  switch (wheel) 
  {
  case LF:
    Wire.beginTransmission(FRONT_MD25_ADDR);                      // Send byte to get a reading from encoder                  
    Wire.send(MD25_LEFT_ENCODER_A_REG);
    Wire.endTransmission();
    
    Wire.requestFrom(FRONT_MD25_ADDR, (uint8_t)4);                         // Request 4 bytes from MD25     
    break;
    
  case RF:
    Wire.beginTransmission(FRONT_MD25_ADDR);                      // Send byte to get a reading from encoder                   
    Wire.send(MD25_RIGHT_ENCODER_A_REG);
    Wire.endTransmission();
    
    Wire.requestFrom(FRONT_MD25_ADDR, (uint8_t)4);                         // Request 4 bytes from MD25  
    break;
    
  case LR:
    Wire.beginTransmission(REAR_MD25_ADDR);                      // Send byte to get a reading from encoder                  
    Wire.send(MD25_LEFT_ENCODER_A_REG);
    Wire.endTransmission();
    
    Wire.requestFrom(REAR_MD25_ADDR, (uint8_t)4);                         // Request 4 bytes from MD25  
    break;
    
  case RR:
    Wire.beginTransmission(REAR_MD25_ADDR);                      // Send byte to get a reading from encoder                  
    Wire.send(MD25_RIGHT_ENCODER_A_REG);
    Wire.endTransmission();
    
    Wire.requestFrom(REAR_MD25_ADDR, (uint8_t)4);                         // Request 4 bytes from MD25    
    break;
  }   
  while(Wire.available() < 4);                              // Wait for 4 bytes to become available
    
    count = Wire.receive();                                 // First byte for encoder 1, HH.
    count <<= 8;
    count += Wire.receive();                                     // Second byte for encoder 1, HL
    count <<= 8;
    count += Wire.receive();                                     // Third byte for encoder 1, LH
    count <<= 8;
    count  +=Wire.receive();                                     // Fourth byte for encoder 1, LL
  return(count);                                            // Returns encoder position as a long
}

uint8_t getWheelCurrent(Wheel_t wheel)
{
  uint8_t current = -1;
  switch (wheel) 
  {
  case LF:
      Wire.beginTransmission(FRONT_MD25_ADDR);                      // Send byte to read current
      Wire.send(MD25_LEFT_MOTOR_CURRENT_REG);
      Wire.endTransmission();
      
      Wire.requestFrom(FRONT_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
      while(Wire.available() < 1);                              // Wait for byte to arrive 
      current = Wire.receive();                        // Get byte
      
      break;
  case RF:
      Wire.beginTransmission(FRONT_MD25_ADDR);                      // Send byte to read current
      Wire.send(MD25_RIGHT_MOTOR_CURRENT_REG);
      Wire.endTransmission();
      
      Wire.requestFrom(FRONT_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
      while(Wire.available() < 1);                              // Wait for byte to arrive 
      current = Wire.receive();                        // Get byte
      
    break;
  case LR:
      Wire.beginTransmission(REAR_MD25_ADDR);                      // Send byte to read current
      Wire.send(MD25_LEFT_MOTOR_CURRENT_REG);
      Wire.endTransmission();
      
      Wire.requestFrom(REAR_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
      while(Wire.available() < 1);                              // Wait for byte to arrive 
      current = Wire.receive();                        // Get byte
      
    break;
  case RR:
      Wire.beginTransmission(REAR_MD25_ADDR);                      // Send byte to read current
      Wire.send(MD25_RIGHT_MOTOR_CURRENT_REG);
      Wire.endTransmission();
      
      Wire.requestFrom(REAR_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
      while(Wire.available() < 1);                              // Wait for byte to arrive 
      current = Wire.receive();                        // Get byte
      
    break;    
 }
 return(current);
}

uint8_t getVolts(uint8_t MD25address)
{                                               // Function to read and display battery volts as a single byte
  Wire.beginTransmission(MD25address);                      // Send byte to read volts
  Wire.send(MD25_BATTERY_VOLTS_REG);
  Wire.endTransmission();
  
  Wire.requestFrom(MD25address, (uint8_t)1);                         // Request 1 byte form MD25
  while(Wire.available() < 1);                              // Wait for byte to arrive 
  uint8_t batteryVolts = Wire.receive();                        // Get byte
  return(batteryVolts);
}

void encoderReset()
{                                         // This function resets ALL encoder values to 0
  Wire.beginTransmission(FRONT_MD25_ADDR);
  Wire.send(MD25_CMD_REG);
  Wire.send(MD25_ENCODER_RESET_CMD);                                          // Putting the value 0x20 to reset encoders
  Wire.endTransmission(); 
  
  Wire.beginTransmission(REAR_MD25_ADDR);
  Wire.send(MD25_CMD_REG);
  Wire.send(MD25_ENCODER_RESET_CMD);                                          // Putting the value 0x20 to reset encoders
  Wire.endTransmission(); 
}

int8_t getMD25SpeedByteFormat(uint8_t MD25address)
{
  int8_t mode = -1;
  Wire.beginTransmission(MD25address);                      // Send byte to read mode
  Wire.send(MD25_MODE_REG);
  Wire.endTransmission();
  
  Wire.requestFrom(MD25address, (uint8_t)1);                         // Request 1 byte form MD25
  while(Wire.available() < 1);                              // Wait for byte to arrive 
  mode = Wire.receive();
  return(mode);
}
void setMD25SpeedByteFormat(uint8_t MD25address, uint8_t mode)
{
     Wire.beginTransmission(MD25address);
     Wire.send(MD25_MODE_REG);
     Wire.send(mode);    
     Wire.endTransmission();
    /*
    The SpeedByteFormat(mode) register selects which mode of operation and I2C data input type the user requires. The options being:
    0, unsigned bytes, speed1 speed2;   (Default Setting) If a value of 0 is written to the mode register then the meaning of the speed registers is literal speeds in the range of 0 (Full Reverse)  128 (Stop)   255 (Full Forward).

    1,  signed bytes, speed1 speed2;  Mode 1 is similar to Mode 0, except that the speed registers are interpreted as signed values. The meaning of the speed registers is literal speeds in the range of -128 (Full Reverse)   0 (Stop)   127 (Full Forward).

    2,  unsigned bytes, speed steer;  Writing a value of  2 to the mode register will make speed1 control both motors speed, and speed2 becomes the turn value. 
    Data is in the range of 0 (Full Reverse)  128 (Stop)  255 (Full  Forward).

    3,  signed bytes, speed steer;  Mode 3 is similar to Mode 2, except that the speed registers are interpreted as signed values. 
    Data is in the range of -128  (Full Reverse)  0 (Stop)   127 (Full Forward)
    */
}

int16_t getWheelSpeed(Wheel_t wheel)
{ 
  int8_t wheelSpeed = 0; 
  switch (wheel) 
    {
    case LF:
        Wire.beginTransmission(FRONT_MD25_ADDR);                      // Send byte to read wheelSpeed
        Wire.send(MD25_LEFT_SPEED_REG);
        Wire.endTransmission();
        
        Wire.requestFrom(FRONT_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
        while(Wire.available() < 1);                              // Wait for byte to arrive 
        wheelSpeed = Wire.receive();                        // Get byte
        
        break;
    case RF:
        Wire.beginTransmission(FRONT_MD25_ADDR);                      // Send byte to read wheelSpeed
        Wire.send(MD25_RIGHT_SPEED_REG);
        Wire.endTransmission();
        
        Wire.requestFrom(FRONT_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
        while(Wire.available() < 1);                              // Wait for byte to arrive 
        wheelSpeed = Wire.receive();                        // Get byte
        
      break;
    case LR:
        Wire.beginTransmission(REAR_MD25_ADDR);                      // Send byte to read wheelSpeed
        Wire.send(MD25_LEFT_SPEED_REG);
        Wire.endTransmission();
        
        Wire.requestFrom(REAR_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
        while(Wire.available() < 1);                              // Wait for byte to arrive 
        wheelSpeed = Wire.receive();                        // Get byte
        
      break;
    case RR:
        Wire.beginTransmission(REAR_MD25_ADDR);                      // Send byte to read wheelSpeed
        Wire.send(MD25_RIGHT_SPEED_REG);
        Wire.endTransmission();
        
        Wire.requestFrom(REAR_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
        while(Wire.available() < 1);                              // Wait for byte to arrive 
        wheelSpeed = Wire.receive();                        // Get byte
        
      break;    
   }
 return(wheelSpeed);
}

void setWheelSpeed(Wheel_t wheel, int16_t speed)// safest, slightly slower response due to mode checking.  does not assume any SpeedByteFormat or valid data, checks everything.
{
    uint8_t mode;
    if(wheel == LF || wheel == RF)
    {
        mode = getMD25SpeedByteFormat(FRONT_MD25_ADDR);
        if(( (1 == mode || 3 == mode) && (speed >= -127 && speed <= 127) )||( (0 == mode || 2 == mode) && (speed >= 0 && speed <= 255) ))//valid range
        {
            Wire.beginTransmission(FRONT_MD25_ADDR);
            if(wheel == LF)
            {
                wheelSpeed[LF] = speed;
                Wire.send(MD25_LEFT_SPEED_REG);
            }
            else 
            {
                wheelSpeed[RF] = speed;
                Wire.send(MD25_RIGHT_SPEED_REG);
            }
            Wire.send(speed);                                  
            Wire.endTransmission();        
             
            
        }
    }
    else if(wheel == LR || wheel == RR)
    {
        mode = getMD25SpeedByteFormat(REAR_MD25_ADDR);
        if(( (1 == mode || 3 == mode) && (speed >= -127 && speed <= 127) )||( (0 == mode || 2 == mode) && (speed >= 0 && speed <= 255) ))//valid range
        {
            Wire.beginTransmission(REAR_MD25_ADDR);
            if(wheel == LR)
            {
                wheelSpeed[LR] = speed;
                Wire.send(MD25_LEFT_SPEED_REG);
            }
            else 
            {
                wheelSpeed[RR] = speed;
                Wire.send(MD25_RIGHT_SPEED_REG);
            }
            Wire.send(speed);                                  
            Wire.endTransmission();
        }
    }
}

void drive4wheelSpeeds(int16_t speedArray[])
{  
    // Function to DRIVE motors
  Wire.beginTransmission(FRONT_MD25_ADDR);
  Wire.send(MD25_LEFT_SPEED_REG);
  Wire.send(speedArray[LF]);                                  
  Wire.endTransmission();
  
  Wire.beginTransmission(FRONT_MD25_ADDR);
  Wire.send(MD25_RIGHT_SPEED_REG);
  Wire.send(speedArray[RF]);                                          
  Wire.endTransmission();
  
  Wire.beginTransmission(REAR_MD25_ADDR);
  Wire.send(MD25_LEFT_SPEED_REG);
  Wire.send(speedArray[LR]);                                  
  Wire.endTransmission();
  
  Wire.beginTransmission(REAR_MD25_ADDR);
  Wire.send(MD25_RIGHT_SPEED_REG);
  Wire.send(speedArray[RR]);                                          
  Wire.endTransmission();
}

void driveWheelSpeed(Wheel_t wheel, int16_t speed)// fast, potentially unsafe.  does not validate data.
{
  switch (wheel) 
    {
  case LF:
    wheelSpeed[LF] = speed;
    Wire.beginTransmission(FRONT_MD25_ADDR);
    Wire.send(MD25_LEFT_SPEED_REG);
    Wire.send(speed);                                  
    Wire.endTransmission();
    break;
  case RF:
    wheelSpeed[RF] = speed;
    Wire.beginTransmission(FRONT_MD25_ADDR);
    Wire.send(MD25_RIGHT_SPEED_REG);
    Wire.send(speed);                                  
    Wire.endTransmission();
    break;
  case LR:
    wheelSpeed[LR] = speed;
    Wire.beginTransmission(REAR_MD25_ADDR);
    Wire.send(MD25_LEFT_SPEED_REG);
    Wire.send(speed);                                  
    Wire.endTransmission();    
    break;
  case RR:
    wheelSpeed[RR] = speed;
    Wire.beginTransmission(REAR_MD25_ADDR);
    Wire.send(MD25_RIGHT_SPEED_REG);
    Wire.send(speed);                                  
    Wire.endTransmission();
    break;
  
}

}

void drive4wheelSpeeds(int16_t LFspeed, int16_t RFspeed, int16_t LRspeed, int16_t RRspeed)
{  //update array
    wheelSpeed[LF] = LFspeed;
    wheelSpeed[RF] = RFspeed;
    wheelSpeed[LR] = LRspeed;
    wheelSpeed[RR] = RRspeed;
    // Function to DRIVE motors
    drive4wheelSpeeds(wheelSpeed);
}  




void fullStop()
{
  // paste the following 2 lines into global area, then uncomment
  //int8_t frontSpeedByteFormat = -1;
  //int8_t rearSpeedByteFormat = -1;
  
  //paste the following 2 lines into setup()following Wire.begin(); then uncomment
  //frontMode = getMD25mode(FRONT_MD25_ADDR);
  //rearMode = getMD25mode(REAR_MD25_ADDR);
  
  // the next line in setup() should call fullStop();
  
  if(0 == getMD25SpeedByteFormat(FRONT_MD25_ADDR) || 2 == getMD25SpeedByteFormat(FRONT_MD25_ADDR))
    {   
        // Function to stop motors
      Wire.beginTransmission(FRONT_MD25_ADDR);
      Wire.send(MD25_LEFT_SPEED_REG);
      Wire.send(128);                                  
      Wire.endTransmission();
      
      Wire.beginTransmission(FRONT_MD25_ADDR);
      Wire.send(MD25_RIGHT_SPEED_REG);
      Wire.send(128);                                          
      Wire.endTransmission();
    }
  else if(1 == getMD25SpeedByteFormat(FRONT_MD25_ADDR) || 3 == getMD25SpeedByteFormat(FRONT_MD25_ADDR))  
    {  
        // Function to stop motors
      Wire.beginTransmission(FRONT_MD25_ADDR);
      Wire.send(MD25_LEFT_SPEED_REG);
      Wire.send(0);                                  
      Wire.endTransmission();
      
      Wire.beginTransmission(FRONT_MD25_ADDR);
      Wire.send(MD25_RIGHT_SPEED_REG);
      Wire.send(0);                                          
      Wire.endTransmission();
    }
    
  
  if(0 == getMD25SpeedByteFormat(REAR_MD25_ADDR) || 2 == getMD25SpeedByteFormat(REAR_MD25_ADDR))
    { 
      Wire.beginTransmission(REAR_MD25_ADDR);
      Wire.send(MD25_LEFT_SPEED_REG);
      Wire.send(128);                                  
      Wire.endTransmission();
      
      Wire.beginTransmission(REAR_MD25_ADDR);
      Wire.send(MD25_RIGHT_SPEED_REG);
      Wire.send(128);                                          
      Wire.endTransmission();
    }    
  else if(1 == getMD25SpeedByteFormat(REAR_MD25_ADDR) || 3 == getMD25SpeedByteFormat(REAR_MD25_ADDR))
  {
      Wire.beginTransmission(REAR_MD25_ADDR);
      Wire.send(MD25_LEFT_SPEED_REG);
      Wire.send(0);                                  
      Wire.endTransmission();
      
      Wire.beginTransmission(REAR_MD25_ADDR);
      Wire.send(MD25_RIGHT_SPEED_REG);
      Wire.send(0);                                          
      Wire.endTransmission();
    }
}  

uint8_t getVersion(uint8_t device7bitAddress, uint8_t deviceVersionRegister)
{           // Function that gets the software version
  Wire.beginTransmission(device7bitAddress);               // Send byte to read software version as a single byte
  Wire.send(deviceVersionRegister);
  Wire.endTransmission();
  
  Wire.requestFrom(device7bitAddress, (uint8_t)1);                   // request 1 byte from device
  while(Wire.available() < 1);                              // Wait for it to arrive
  uint8_t version = Wire.receive();                         // Read it in
  return(version);
}


void changeI2Caddress(uint8_t oldAddress, uint8_t newAddress, uint8_t commandRegister, uint8_t commandDelay) //must be run with ONLY the device whose address is to be changed connected to the I2C bus
{
  /*
  example: changeI2Caddress(0x58, 0xB4, 16, 5); //change default md25 address 
  example: changeI2Caddress(0x60, 0xC4, 22, 5); //change default cmps10 address
  example: changeI2Caddress(0x60, 0xC4, 0, 100); //change default tpa81 address
  */
     uint8_t transmissionStatus = -1;

        
     Wire.beginTransmission(oldAddress);
     Wire.send(commandRegister);
     Wire.send(0xA0);    // also tried changing this arguement to 160
     transmissionStatus = Wire.endTransmission();
        
     delay(commandDelay + 1);
     
     Wire.beginTransmission(oldAddress);
     Wire.send(commandRegister);
     Wire.send(0xAA);    // also tried changing this arguement to 170
     transmissionStatus = Wire.endTransmission();
       
     delay(commandDelay + 1);
     
     Wire.beginTransmission(oldAddress);
     Wire.send(commandRegister);
     Wire.send(0xA5);    // also tried changing this arguement to 165
     transmissionStatus = Wire.endTransmission();
     
     delay(commandDelay + 1);
     
     Wire.beginTransmission(oldAddress);
     Wire.send(commandRegister);
     Wire.send(newAddress); 
     transmissionStatus = Wire.endTransmission();
    
     delay(1000);
     
    
}


uint8_t getAcceleration(uint8_t MD25address)
{
  Wire.beginTransmission(MD25address);                      // Send byte to read acceleration
  Wire.send(MD25_ACCELERATION_REG);
  Wire.endTransmission();
  
  Wire.requestFrom(MD25address, (uint8_t)1);                         // Request 1 byte form MD25
  while(Wire.available() < 1);                              // Wait for byte to arrive 
  uint8_t acceleration = Wire.receive();                        // Get byte
  return(acceleration);
}

void setAcceleration(uint8_t MD25address, uint8_t value)// value from 1-10.  1 = slowest acceleration, 10 = fastest acceleration
{ 
/*to calculate the time (in seconds) for the acceleration to complete :

if new speed > current speed
steps = (new speed - current speed) / acceleration register

if new speed < current speed
steps = (current speed - new speed) / acceleration register

time = steps * 25ms 

For example :

Acceleration register	Time/step	Current speed	New speed	Steps	Acceleration  time
1	25ms	0	255	255	6.375s
2	25ms	127	255	64	1.6s
3	25ms	80	0	27	0.675s
5 (default)	25ms	0	255	51	1.275s
10	25ms	255	0	26	0.65s

*/

  Wire.beginTransmission(MD25address);                      // Send byte to set acceleration
  Wire.send(MD25_ACCELERATION_REG);
  Wire.send(value);
  Wire.endTransmission();
}

void setAccelerationBoth(uint8_t value)// value from 1-10.  1 = slowest acceleration, 10 = fastest acceleration
{ 
  Wire.beginTransmission(FRONT_MD25_ADDR);                      // Send byte to set acceleration
  Wire.send(MD25_ACCELERATION_REG);
  Wire.send(value);
  Wire.endTransmission();

  Wire.beginTransmission(REAR_MD25_ADDR);                      // Send byte to set acceleration
  Wire.send(MD25_ACCELERATION_REG);
  Wire.send(value);
  Wire.endTransmission();
}

void quantifySpeeds(uint8_t acceleration)// runs robot forward, then back at each possible speed, prints results
{
    fullStop();
    uint8_t oldAccel = getAcceleration(FRONT_MD25_ADDR); //save existing acceleration rate
    setAccelerationBoth(acceleration);//adjust rate
    delay(6000);// be sure bot has had time to come to a complete stop
    uint8_t speedStep;//0-127
    for (speedStep = 127; speedStep > 0; speedStep--)// step through each possible speed setting and record the actual speed.
    {
        int32_t distanceToSpeed[4][128];//index1 = wheel, index2 = speedStep, value = distance(in clicks) required to get up to speed.  Compare the reported distance to the actual measured distance to discover wheel slip and maximum slip free acceleration.
        int32_t overshoot[4][128];//distance it takes to slow down, 
        int32_t clicksPerSecond[4][128];
        fullStop();
        encoderReset();
        drive4wheelSpeeds(speedStep, speedStep, speedStep, speedStep);//drive forward
        delay((speedStep/acceleration) * 25);//ms. wait for bot to get up to speed.
        distanceToSpeed[LF][speedStep] = getEncoderCount(LF);
        distanceToSpeed[RF][speedStep] = getEncoderCount(RF);
        distanceToSpeed[LR][speedStep] = getEncoderCount(LR);
        distanceToSpeed[RR][speedStep] = getEncoderCount(RR);
        delay(1000);
        clicksPerSecond[LF][speedStep] = getEncoderCount(LF) - distanceToSpeed[LF][speedStep];
        clicksPerSecond[RF][speedStep] = getEncoderCount(RF) - distanceToSpeed[RF][speedStep];
        clicksPerSecond[LR][speedStep] = getEncoderCount(LR) - distanceToSpeed[LR][speedStep];
        clicksPerSecond[RR][speedStep] = getEncoderCount(RR) - distanceToSpeed[RR][speedStep];
        drive4wheelSpeeds(-speedStep, -speedStep, -speedStep, -speedStep);//drive reverse, stop at 0.
        
        boolean testLF;
        boolean testRF;
        boolean testLR;
        boolean testRR;
        
        do
        {            
            overshoot[LF][speedStep] = getEncoderCount(LF);
            overshoot[RF][speedStep] = getEncoderCount(RF);
            overshoot[LR][speedStep] = getEncoderCount(LR);
            overshoot[RR][speedStep] = getEncoderCount(RR);
            if((testLF = (overshoot[LF][speedStep]) <= 0))
                driveWheelSpeed(LF, 0);
            if((testRF = (overshoot[LF][speedStep]) <= 0))
                driveWheelSpeed(RF, 0);
            if((testLR = (overshoot[LF][speedStep]) <= 0))
                driveWheelSpeed(LR, 0);
            if((testRR = (overshoot[LF][speedStep]) <= 0))
                driveWheelSpeed(RR, 0);
        }while(!(testLF && testRF && testLR && testRR));//while at least one encoder is still above zero
        
        delay(((speedStep/acceleration) * 25) + 250);//ms. wait for bot to slow to a stop
        overshoot[LF][speedStep] = getEncoderCount(LF);
        overshoot[RF][speedStep] = getEncoderCount(RF);
        overshoot[LR][speedStep] = getEncoderCount(LR);
        overshoot[RR][speedStep] = getEncoderCount(RR);
        
    }
    setAccelerationBoth(oldAccel); //restore acceleration factor to its previous value,
}

void quantifyAcceleration()
{
    uint8_t i;
    for(i = 10; i >= 1; i--)
    {
        quantifySpeeds(i);
    }

}

void displayVolts()
{
  uint8_t batteryVolts = getVolts(FRONT_MD25_ADDR);      //get the voltage reading of the front motor controller
  lcd.setCursor(0, 0);   // lcd.setCsrLC(0, 0);                                        //move cursor to first line, first column
  lcd.print("Batt Volts = ");
  lcd.print(batteryVolts/10, DEC);                       // Print batery volts / 10 to give you the number of whole volts
  lcd.print(".");                                        // As arduino has truncates floating point numbers we print a . here to act as a decimal point
  lcd.print(batteryVolts%10, DEC);                       // Prints Battery volts % 10 to give us the 
  
  
}

#endif



