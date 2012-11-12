#include <Arduino.h>
enum Wheel_t{FRONT,REAR,LEFT,RIGHT};
int wheelSpeed[] = {128, 128, 128, 128};
static const uint8_t FRONT_MD25_ADDR = 0xB0 >> 1;                    // Address of front MD25 motor control board
static const uint8_t REAR_MD25_ADDR = 0xB4 >> 1;                     // Address of rear MD25 motor control board
static const uint8_t PRIMARY_MD25_ADDR = 0xB0 >> 1;                    // Address of primary MD25 motor control board
static const uint8_t SECONDARY_MD25_ADDR = 0xB4 >> 1;                     // Address of secondary MD25 motor control board
    //MD25 Motor Driver READ/WRITE registers    
    static const uint8_t MD25_RIGHT_SPEED_REG = 1;    //Used in mode 0 and 1
    static const uint8_t MD25_LEFT_SPEED_REG = 0;   //Used in mode 0 and 1
    static const uint8_t MD25_FRONT_SPEED_REG = 0;    //Used in mode 0 and 1
    static const uint8_t MD25_REAR_SPEED_REG = 1;   //Used in mode 0 and 1
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
  static const uint8_t MD25_FRONT_MOTOR_CURRENT_REG = 11;	//The current through motor 1
  static const uint8_t MD25_REAR_MOTOR_CURRENT_REG = 12;	//The current through motor 2
  static const uint8_t MD25_LEFT_MOTOR_CURRENT_REG = 11;	//The current through motor 1
  static const uint8_t MD25_RIGHT_MOTOR_CURRENT_REG = 12;	//The current through motor 2
  static const uint8_t MD25_VERSION_REG = 13;                   //Software Revision Number
 
int8_t getMD25SpeedByteFormat(uint8_t MD25address)
{
  int8_t mode = -1;
  Wire.beginTransmission(MD25address);                      // Send byte to read mode
  Wire.write(MD25_MODE_REG);
  Wire.endTransmission();
  
  Wire.requestFrom(MD25address, (uint8_t)1);                         // Request 1 byte form MD25
  while(Wire.available() < 1);                              // Wait for byte to arrive 
  mode = Wire.read();
  return(mode);
}

void fullStop()
{
  if(0 == getMD25SpeedByteFormat(PRIMARY_MD25_ADDR) || 2 == getMD25SpeedByteFormat(PRIMARY_MD25_ADDR))
    {   
        // Function to stop motors
      Wire.beginTransmission(PRIMARY_MD25_ADDR);
      Wire.write(MD25_FRONT_SPEED_REG);
      Wire.write(128);                                  
      Wire.endTransmission();
      
      Wire.beginTransmission(PRIMARY_MD25_ADDR);
      Wire.write(MD25_REAR_SPEED_REG);
      Wire.write(128);                                          
      Wire.endTransmission();
      wheelSpeed[0] = 128;
      wheelSpeed[1] = 128;
    }
  else if(1 == getMD25SpeedByteFormat(PRIMARY_MD25_ADDR) || 3 == getMD25SpeedByteFormat(PRIMARY_MD25_ADDR))  
    {  
        // Function to stop motors
      Wire.beginTransmission(PRIMARY_MD25_ADDR);
      Wire.write(MD25_FRONT_SPEED_REG);
      Wire.write(0);                                  
      Wire.endTransmission();
      
      Wire.beginTransmission(PRIMARY_MD25_ADDR);
      Wire.write(MD25_REAR_SPEED_REG);
      Wire.write(0);                                          
      Wire.endTransmission();
      wheelSpeed[0] = 0;
      wheelSpeed[1] = 0;
    }
    
  
  if(0 == getMD25SpeedByteFormat(SECONDARY_MD25_ADDR) || 2 == getMD25SpeedByteFormat(SECONDARY_MD25_ADDR))
    { 
      Wire.beginTransmission(SECONDARY_MD25_ADDR);
      Wire.write(MD25_LEFT_SPEED_REG);
      Wire.write(128);                                  
      Wire.endTransmission();
      
      Wire.beginTransmission(SECONDARY_MD25_ADDR);
      Wire.write(MD25_RIGHT_SPEED_REG);
      Wire.write(128);                                          
      Wire.endTransmission();
      wheelSpeed[2] = 128;
      wheelSpeed[3] = 128;
    }    
  else if(1 == getMD25SpeedByteFormat(SECONDARY_MD25_ADDR) || 3 == getMD25SpeedByteFormat(SECONDARY_MD25_ADDR))
  {
      Wire.beginTransmission(SECONDARY_MD25_ADDR);
      Wire.write(MD25_LEFT_SPEED_REG);
      Wire.write(0);                                  
      Wire.endTransmission();
      
      Wire.beginTransmission(SECONDARY_MD25_ADDR);
      Wire.write(MD25_RIGHT_SPEED_REG);
      Wire.write(0);                                          
      Wire.endTransmission();
      wheelSpeed[2] = 0;
      wheelSpeed[3] = 0;
    }
}  
 
void setAutoSpeedRegulationOn(uint8_t MD25address)
{
     Wire.beginTransmission(MD25address);
     Wire.write(MD25_CMD_REG);
     Wire.write(MD25_ENABLE_AUTO_SPEEDREG_CMD);   
     Wire.endTransmission();     
}

void setAutoSpeedRegulationOff(uint8_t MD25address)
{
    Wire.beginTransmission(MD25address);
     Wire.write(MD25_CMD_REG);
     Wire.write(MD25_DISABLE_AUTO_SPEEDREG_CMD);   
     Wire.endTransmission();
}
  
void setTimeoutOn(uint8_t MD25address)
{
     Wire.beginTransmission(MD25address);
     Wire.write(MD25_CMD_REG);
     Wire.write(MD25_ENABLE_TIMEOUT_CMD);   
     Wire.endTransmission();    
}  

void setTimeoutOff(uint8_t MD25address)
{
    Wire.beginTransmission(MD25address);
     Wire.write(MD25_CMD_REG);
     Wire.write(MD25_DISABLE_TIMEOUT_CMD);   
     Wire.endTransmission();
}


uint8_t getWheelCurrent(Wheel_t wheel)
{
  uint8_t current = -1;
  switch (wheel) 
  {
  case FRONT:
      Wire.beginTransmission(PRIMARY_MD25_ADDR);                      // Send byte to read current
      Wire.write(MD25_FRONT_MOTOR_CURRENT_REG);
      Wire.endTransmission();
      
      Wire.requestFrom(PRIMARY_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
      while(Wire.available() < 1);                              // Wait for byte to arrive 
      current = Wire.read();                        // Get byte
      
      break;
  case REAR:
      Wire.beginTransmission(PRIMARY_MD25_ADDR);                      // Send byte to read current
      Wire.write(MD25_REAR_MOTOR_CURRENT_REG);
      Wire.endTransmission();
      
      Wire.requestFrom(PRIMARY_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
      while(Wire.available() < 1);                              // Wait for byte to arrive 
      current = Wire.read();                        // Get byte
      
    break;
  case LEFT:
      Wire.beginTransmission(SECONDARY_MD25_ADDR);                      // Send byte to read current
      Wire.write(MD25_LEFT_MOTOR_CURRENT_REG);
      Wire.endTransmission();
      
      Wire.requestFrom(SECONDARY_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
      while(Wire.available() < 1);                              // Wait for byte to arrive 
      current = Wire.read();                        // Get byte
      
    break;
  case RIGHT:
      Wire.beginTransmission(SECONDARY_MD25_ADDR);                      // Send byte to read current
      Wire.write(MD25_RIGHT_MOTOR_CURRENT_REG);
      Wire.endTransmission();
      
      Wire.requestFrom(SECONDARY_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
      while(Wire.available() < 1);                              // Wait for byte to arrive 
      current = Wire.read();                        // Get byte
      
    break;    
 }
 return(current);
}

uint8_t getVolts(uint8_t MD25address)
{                                               // Function to read and display battery volts as a single byte
  Wire.beginTransmission(MD25address);                      // Send byte to read volts
  Wire.write(MD25_BATTERY_VOLTS_REG);
  Wire.endTransmission();
  
  Wire.requestFrom(MD25address, (uint8_t)1);                         // Request 1 byte form MD25
  while(Wire.available() < 1);                              // Wait for byte to arrive 
  uint8_t batteryVolts = Wire.read();                        // Get byte
  return(batteryVolts);
}



void setMD25SpeedByteFormat(uint8_t MD25address, uint8_t mode)
{
  fullStop();
     Wire.beginTransmission(MD25address);
     Wire.write(MD25_MODE_REG);
     Wire.write(mode);    
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
    case FRONT:
        Wire.beginTransmission(PRIMARY_MD25_ADDR);                      // Send byte to read wheelSpeed
        Wire.write(MD25_FRONT_SPEED_REG);
        Wire.endTransmission();
        
        Wire.requestFrom(PRIMARY_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
        while(Wire.available() < 1);                              // Wait for byte to arrive 
        wheelSpeed = Wire.read();                        // Get byte
        
        break;
    case REAR:
        Wire.beginTransmission(PRIMARY_MD25_ADDR);                      // Send byte to read wheelSpeed
        Wire.write(MD25_REAR_SPEED_REG);
        Wire.endTransmission();
        
        Wire.requestFrom(PRIMARY_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
        while(Wire.available() < 1);                              // Wait for byte to arrive 
        wheelSpeed = Wire.read();                        // Get byte
        
      break;
    case LEFT:
        Wire.beginTransmission(SECONDARY_MD25_ADDR);                      // Send byte to read wheelSpeed
        Wire.write(MD25_LEFT_SPEED_REG);
        Wire.endTransmission();
        
        Wire.requestFrom(SECONDARY_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
        while(Wire.available() < 1);                              // Wait for byte to arrive 
        wheelSpeed = Wire.read();                        // Get byte
        
      break;
    case RIGHT:
        Wire.beginTransmission(SECONDARY_MD25_ADDR);                      // Send byte to read wheelSpeed
        Wire.write(MD25_RIGHT_SPEED_REG);
        Wire.endTransmission();
        
        Wire.requestFrom(SECONDARY_MD25_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
        while(Wire.available() < 1);                              // Wait for byte to arrive 
        wheelSpeed = Wire.read();                        // Get byte
        
      break;    
   }
 return(wheelSpeed);
}

void setWheelSpeed(Wheel_t wheel, int16_t speed)// safest, slightly slower response due to mode checking.  does not assume any SpeedByteFormat or valid data, checks everything.
{
    uint8_t mode;
    if(wheel == FRONT || wheel == REAR)
    {
        mode = getMD25SpeedByteFormat(PRIMARY_MD25_ADDR);
        if(( (1 == mode || 3 == mode) && (speed >= -127 && speed <= 127) )||( (0 == mode || 2 == mode) && (speed >= 0 && speed <= 255) ))//valid range
        {
            Wire.beginTransmission(PRIMARY_MD25_ADDR);
            if(wheel == FRONT)
            {
                wheelSpeed[FRONT] = speed;
                Wire.write(MD25_FRONT_SPEED_REG);
            }
            else 
            {
                wheelSpeed[REAR] = speed;
                Wire.write(MD25_REAR_SPEED_REG);
            }
            Wire.write(speed);                                  
            Wire.endTransmission();        
             
            
        }
    }
    else if(wheel == LEFT || wheel == RIGHT)
    {
        mode = getMD25SpeedByteFormat(SECONDARY_MD25_ADDR);
        if(( (1 == mode || 3 == mode) && (speed >= -127 && speed <= 127) )||( (0 == mode || 2 == mode) && (speed >= 0 && speed <= 255) ))//valid range
        {
            Wire.beginTransmission(SECONDARY_MD25_ADDR);
            if(wheel == LEFT)
            {
                wheelSpeed[LEFT] = speed;
                Wire.write(MD25_LEFT_SPEED_REG);
            }
            else 
            {
                wheelSpeed[RIGHT] = speed;
                Wire.write(MD25_RIGHT_SPEED_REG);
            }
            Wire.write(speed);                                  
            Wire.endTransmission();
        }
    }
}

void drive4wheelSpeeds(int16_t speedArray[])
{  
    // Function to DRIVE motors
  Wire.beginTransmission(PRIMARY_MD25_ADDR);
  Wire.write(MD25_FRONT_SPEED_REG);
  Wire.write(speedArray[0]);                                  
  Wire.endTransmission();
  
  Wire.beginTransmission(PRIMARY_MD25_ADDR);
  Wire.write(MD25_REAR_SPEED_REG);
  Wire.write(speedArray[1]);                                          
  Wire.endTransmission();
  
  Wire.beginTransmission(SECONDARY_MD25_ADDR);
  Wire.write(MD25_LEFT_SPEED_REG);
  Wire.write(speedArray[2]);                                  
  Wire.endTransmission();
  
  Wire.beginTransmission(SECONDARY_MD25_ADDR);
  Wire.write(MD25_RIGHT_SPEED_REG);
  Wire.write(speedArray[3]);                                          
  Wire.endTransmission();
}

void driveWheelSpeed(Wheel_t wheel, int16_t speed)// fast, potentially unsafe.  does not validate data.
{
  switch (wheel) 
    {
  case FRONT:
    wheelSpeed[FRONT] = speed;
    Wire.beginTransmission(PRIMARY_MD25_ADDR);
    Wire.write(MD25_FRONT_SPEED_REG);
    Wire.write(speed);                                  
    Wire.endTransmission();
    break;
  case REAR:
    wheelSpeed[REAR] = speed;
    Wire.beginTransmission(FRONT_MD25_ADDR);
    Wire.write(MD25_RIGHT_SPEED_REG);
    Wire.write(speed);                                  
    Wire.endTransmission();
    break;
  case LEFT:
    wheelSpeed[LEFT] = speed;
    Wire.beginTransmission(SECONDARY_MD25_ADDR);
    Wire.write(MD25_LEFT_SPEED_REG);
    Wire.write(speed);                                  
    Wire.endTransmission();    
    break;
  case RIGHT:
    wheelSpeed[RIGHT] = speed;
    Wire.beginTransmission(SECONDARY_MD25_ADDR);
    Wire.write(MD25_RIGHT_SPEED_REG);
    Wire.write(speed);                                  
    Wire.endTransmission();
    break;
  
}

}

void drive4wheelSpeeds(int16_t FRONTspeed, int16_t REARspeed, int16_t LEFTspeed, int16_t RIGHTspeed)
{  //update array
    wheelSpeed[FRONT] = FRONTspeed;
    wheelSpeed[REAR] = REARspeed;
    wheelSpeed[LEFT] = LEFTspeed;
    wheelSpeed[RIGHT] = RIGHTspeed;
    // Function to DRIVE motors
    drive4wheelSpeeds(wheelSpeed);
}


uint8_t getVersion(uint8_t device7bitAddress, uint8_t deviceVersionRegister)
{           // Function that gets the software version
  Wire.beginTransmission(device7bitAddress);               // Send byte to read software version as a single byte
  Wire.write(deviceVersionRegister);
  Wire.endTransmission();
  
  Wire.requestFrom(device7bitAddress, (uint8_t)1);                   // request 1 byte from device
  while(Wire.available() < 1);                              // Wait for it to arrive
  uint8_t version = Wire.read();                         // Read it in
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
     Wire.write(commandRegister);
     Wire.write(0xA0);    // also tried changing this arguement to 160
     transmissionStatus = Wire.endTransmission();
        
     delay(commandDelay + 1);
     
     Wire.beginTransmission(oldAddress);
     Wire.write(commandRegister);
     Wire.write(0xAA);    // also tried changing this arguement to 170
     transmissionStatus = Wire.endTransmission();
       
     delay(commandDelay + 1);
     
     Wire.beginTransmission(oldAddress);
     Wire.write(commandRegister);
     Wire.write(0xA5);    // also tried changing this arguement to 165
     transmissionStatus = Wire.endTransmission();
     
     delay(commandDelay + 1);
     
     Wire.beginTransmission(oldAddress);
     Wire.write(commandRegister);
     Wire.write(newAddress); 
     transmissionStatus = Wire.endTransmission();
    
     delay(1000);
     
    
}


uint8_t getAcceleration(uint8_t MD25address)
{
  Wire.beginTransmission(MD25address);                      // Send byte to read acceleration
  Wire.write(MD25_ACCELERATION_REG);
  Wire.endTransmission();
  
  Wire.requestFrom(MD25address, (uint8_t)1);                         // Request 1 byte form MD25
  while(Wire.available() < 1);                              // Wait for byte to arrive 
  uint8_t acceleration = Wire.read();                        // Get byte
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
  Wire.write(MD25_ACCELERATION_REG);
  Wire.write(value);
  Wire.endTransmission();
}

void setAccelerationBoth(uint8_t value)// value from 1-10.  1 = slowest acceleration, 10 = fastest acceleration
{ 
  Wire.beginTransmission(PRIMARY_MD25_ADDR);                      // Send byte to set acceleration
  Wire.write(MD25_ACCELERATION_REG);
  Wire.write(value);
  Wire.endTransmission();

  Wire.beginTransmission(SECONDARY_MD25_ADDR);                      // Send byte to set acceleration
  Wire.write(MD25_ACCELERATION_REG);
  Wire.write(value);
  Wire.endTransmission();
}

void moveForward(int speed, long time)
{
  drive4wheelSpeeds(0, 0, speed, speed);
  delay(time);
  fullStop();
}

void moveRearward(int speed, long time)
{
  drive4wheelSpeeds(0, 0, -speed, -speed);
  delay(time);
  fullStop();
}

void moveLeft(int speed, long time)
{
  drive4wheelSpeeds(-speed, -speed, 0, 0);
  delay(time);
  fullStop();
}

void moveRight(int speed, long time)
{
  drive4wheelSpeeds(speed, speed, 0, 0);
  delay(time);
  fullStop();
}

void moveLF(int speed, long time)
{
  drive4wheelSpeeds(-speed, -speed, speed, speed);
  delay(time);
  fullStop();
}

void moveRF(int speed, long time)
{
  drive4wheelSpeeds(speed, speed, speed, speed);
  delay(time);
  fullStop();
}

void moveLR(int speed, long time)
{
  drive4wheelSpeeds(-speed, -speed, -speed, -speed);
  delay(time);
  fullStop();
}

void moveRR(int speed, long time)
{
  drive4wheelSpeeds(speed, speed, -speed, -speed);
  delay(time);
  fullStop();
}
