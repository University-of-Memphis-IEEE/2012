#include <arduino.h>

//#include "constants.h"
#ifdef DEBUG
  #define TRACE(name, variable) \
    Serial.print(name);     \
    Serial.print(" == ");   \
    Serial.println(variable);
  #define DEBUG_BEGIN(x)    Serial.begin(x)
  #define DEBUG_PRINT(x)     Serial.print (x)
  #define DEBUG_PRINTDEC(x)     Serial.print (x, DEC)
  #define DEBUG_PRINTLN(x)  Serial.println (x)
  #define DEBUG_PRINT_@(str)    \
    Serial.print(millis());     \
    Serial.print(": ");         \
    Serial.print(__PRETTY_FUNCTION__); \
    Serial.print(' ');          \
    Serial.print(__FILE__);     \
    Serial.print(':');          \
    Serial.print(__LINE__);     \
    Serial.print(' ');          \
    Serial.println(str);
  #define DEBUG_SPDELAY    delay(250) // usually placed at end of loop to keep serial monitor output readable
  #define DEBUG_DELAY(x)
  #define DEBUG_I2C(x) printI2Cstatus(x)
#else
  #define TRACE(name, variable)
  #define DEBUG_BEGIN(x)
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINT_@(str)
  #define DEBUG_SPDELAY  
  #define DEBUG_DELAY(x) 
  #define DEBUG_I2C(x)
#endif

uint16_t getDistanceToFrontObject()//uses Vex sensors.  get code from Blake
{}

uint16_t getDistanceToRearObject()//uses Vex sensors.  get code from Blake
{}

uint16_t getDistanceToLeftObject()
{
  uint16_t leftSRF05distance;                          // Stores distance
  uint16_t leftSRF05duration;                          // Stores duratiuon of pulse in
  pinMode(LEFT_SRF05_PIN, OUTPUT);
  digitalWrite(LEFT_SRF05_PIN, LOW);           // Make sure pin is low before sending a short high to trigger ranging
  delayMicroseconds(2);
  digitalWrite(LEFT_SRF05_PIN, HIGH);          // Send a short 10 microsecond high burst on pin to start ranging
  delayMicroseconds(10);
  digitalWrite(LEFT_SRF05_PIN, LOW);           // Send pin low again before waiting for pulse back in
  pinMode(LEFT_SRF05_PIN, INPUT);
  leftSRF05duration = pulseIn(LEFT_SRF05_PIN, HIGH);    // Reads echo pulse in from SRF05 in micro seconds
  leftSRF05distance = leftSRF05duration/58;              // Dividing this by 58 gives us a distance in cm
  return(leftSRF05distance);
}  
 
uint16_t getDistanceToRightObject()
{
  uint16_t rightSRF05distance;                          // Stores distance
  uint16_t rightSRF05duration;                          // Stores duratiuon of pulse in
  pinMode(RIGHT_SRF05_PIN, OUTPUT);
  digitalWrite(RIGHT_SRF05_PIN, LOW);           // Make sure pin is low before sending a short high to trigger ranging
  delayMicroseconds(2);
  digitalWrite(RIGHT_SRF05_PIN, HIGH);          // Send a short 10 microsecond high burst on pin to start ranging
  delayMicroseconds(10);
  digitalWrite(RIGHT_SRF05_PIN, LOW);           // Send pin low again before waiting for pulse back in
  pinMode(RIGHT_SRF05_PIN, INPUT);
  rightSRF05duration = pulseIn(RIGHT_SRF05_PIN, HIGH);    // Reads echo pulse in from SRF05 in micro seconds
  rightSRF05distance = rightSRF05duration/58;              // Dividing this by 58 gives us a distance in cm
  return(rightSRF05distance);
}
  

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

uint8_t getBearing()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_BEARING_BYTE_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();

   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   while(Wire.available() < 1);               // Wait for bytes to become available
   uint8_t bearing = Wire.receive(); 
   return(bearing);  
}

int8_t getPitch()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_PITCH_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();
   
   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   while(Wire.available() < 1);               // Wait for bytes to become available
   int8_t pitch = Wire.receive(); 
   return(pitch);
}

int8_t getRoll()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_ROLL_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();
   
   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   while(Wire.available() < 1);               // Wait for bytes to become available
   int8_t roll = Wire.receive(); 
   return(roll);
}

 
int8_t getSpeed(Wheel wheel)
{ 
  int8_t wheelSpeed; 
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
        
int32_t getEncoderCount(Wheel wheel)
{        
  int32_t count;
  uint8_t firstByte;                          // Get four bytes highest byte first
  uint8_t secondByte;
  uint8_t thirdByte;
  uint8_t fourthByte;
  switch (wheel) 
  {
  case LF:
    Wire.beginTransmission(FRONT_MD25_ADDR);                      // Send byte to get a reading from encoder                  
    Wire.send(MD25_LEFT_ENCODER_A_REG);
    Wire.endTransmission();
    
    Wire.requestFrom(FRONT_MD25_ADDR, (uint8_t)4);                         // Request 4 bytes from MD25
    while(Wire.available() < 4);                              // Wait for 4 bytes to become available
    firstByte = Wire.receive();                          // Get four bytes highest byte first
    secondByte = Wire.receive();
    thirdByte = Wire.receive();
    fourthByte = Wire.receive();
    
    count = firstByte|(secondByte<<8)|(thirdByte<<16)|(fourthByte<<24);// Put them together    
    break;
    
  case RF:
    Wire.beginTransmission(FRONT_MD25_ADDR);                      // Send byte to get a reading from encoder                   
    Wire.send(MD25_RIGHT_ENCODER_A_REG);
    Wire.endTransmission();
    
    Wire.requestFrom(FRONT_MD25_ADDR, (uint8_t)4);                         // Request 4 bytes from MD25
    while(Wire.available() < 4);                              // Wait for 4 bytes to become available
    firstByte = Wire.receive();                          // Get four bytes highest byte first
    secondByte = Wire.receive();
    thirdByte = Wire.receive();
    fourthByte = Wire.receive();
    
    count = (firstByte << 24) + (secondByte << 16) + (thirdByte << 8) + fourthByte;  // Put them together    
    break;
    
    case LR:
    Wire.beginTransmission(REAR_MD25_ADDR);                      // Send byte to get a reading from encoder                  
    Wire.send(MD25_LEFT_ENCODER_A_REG);
    Wire.endTransmission();
    
    Wire.requestFrom(REAR_MD25_ADDR, (uint8_t)4);                         // Request 4 bytes from MD25
    while(Wire.available() < 4);                              // Wait for 4 bytes to become available
    firstByte = Wire.receive();                          // Get four bytes highest byte first
    secondByte = Wire.receive();
    thirdByte = Wire.receive();
    fourthByte = Wire.receive();
    
    count = (firstByte << 24) + (secondByte << 16) + (thirdByte << 8) + fourthByte;  // Put them together    
    break;
    
  case RR:
    Wire.beginTransmission(REAR_MD25_ADDR);                      // Send byte to get a reading from encoder                  
    Wire.send(MD25_RIGHT_ENCODER_A_REG);
    Wire.endTransmission();
    
    Wire.requestFrom(REAR_MD25_ADDR, (uint8_t)4);                         // Request 4 bytes from MD25
    while(Wire.available() < 4);                              // Wait for 4 bytes to become available
    firstByte = Wire.receive();                          // Get four bytes highest byte first
    secondByte = Wire.receive();
    thirdByte = Wire.receive();
    fourthByte = Wire.receive();
    
    count = (firstByte << 24) + (secondByte << 16) + (thirdByte << 8) + fourthByte;  // Put them together    
    break;
  }   
  return(count);                                            // Returns encoder position as a long
}

uint8_t getCurrent(Wheel wheel)
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

void encoderReset(){                                         // This function resets ALL encoder values to 0
  Wire.beginTransmission(FRONT_MD25_ADDR);
  Wire.send(MD25_CMD_REG);
  Wire.send(MD25_ENCODER_RESET_CMD);                                          // Putting the value 0x20 to reset encoders
  Wire.endTransmission(); 
  
  Wire.beginTransmission(REAR_MD25_ADDR);
  Wire.send(MD25_CMD_REG);
  Wire.send(MD25_ENCODER_RESET_CMD);                                          // Putting the value 0x20 to reset encoders
  Wire.endTransmission(); 
}

int8_t getMD25mode(uint8_t MD25address)
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
void setMD25mode(uint8_t MD25address, uint8_t mode)
{
     Wire.beginTransmission(MD25address);
     Wire.send(MD25_MODE_REG);
     Wire.send(mode);    
     Wire.endTransmission();
    /*
    The mode register selects which mode of operation and I2C data input type the user requires. The options being:
    0,    (Default Setting) If a value of 0 is written to the mode register then the meaning of the speed registers is literal speeds in the range of 0 (Full Reverse)  128 (Stop)   255 (Full Forward).

    1,    Mode 1 is similar to Mode 0, except that the speed registers are interpreted as signed values. The meaning of the speed registers is literal speeds in the range of -128 (Full Reverse)   0 (Stop)   127 (Full Forward).

    2,    Writing a value of  2 to the mode register will make speed1 control both motors speed, and speed2 becomes the turn value. 
    Data is in the range of 0 (Full Reverse)  128 (Stop)  255 (Full  Forward).

    3,    Mode 3 is similar to Mode 2, except that the speed registers are interpreted as signed values. 
    Data is in the range of -128  (Full Reverse)  0 (Stop)   127 (Full Forward)
    */
}


void drive(int8_t LFspeed, int8_t RFspeed, int8_t LRspeed, int8_t RRspeed)
{  
    // Function to DRIVE motors
  Wire.beginTransmission(FRONT_MD25_ADDR);
  Wire.send(MD25_LEFT_SPEED_REG);
  Wire.send(LFspeed);                                  
  Wire.endTransmission();
  
  Wire.beginTransmission(FRONT_MD25_ADDR);
  Wire.send(MD25_RIGHT_SPEED_REG);
  Wire.send(RFspeed);                                          
  Wire.endTransmission();
  
  Wire.beginTransmission(REAR_MD25_ADDR);
  Wire.send(MD25_LEFT_SPEED_REG);
  Wire.send(LRspeed);                                  
  Wire.endTransmission();
  
  Wire.beginTransmission(REAR_MD25_ADDR);
  Wire.send(MD25_RIGHT_SPEED_REG);
  Wire.send(RRspeed);                                          
  Wire.endTransmission();
}  

void fullStop()
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
  
  Wire.beginTransmission(REAR_MD25_ADDR);
  Wire.send(MD25_LEFT_SPEED_REG);
  Wire.send(0);                                  
  Wire.endTransmission();
  
  Wire.beginTransmission(REAR_MD25_ADDR);
  Wire.send(MD25_RIGHT_SPEED_REG);
  Wire.send(0);                                          
  Wire.endTransmission();
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
     DEBUG_PRINTLN("Entered changeI2Caddress function");
        
     Wire.beginTransmission(oldAddress);
     Wire.send(commandRegister);
     Wire.send(0xA0);    // also tried changing this arguement to 160
     transmissionStatus = Wire.endTransmission();
     DEBUG_PRINTLN("First byte sent");
     DEBUG_I2C(transmissionStatus);     
     delay(commandDelay + 1);
     
     Wire.beginTransmission(oldAddress);
     Wire.send(commandRegister);
     Wire.send(0xAA);    // also tried changing this arguement to 170
     transmissionStatus = Wire.endTransmission();
     DEBUG_PRINTLN("Second byte sent");
     DEBUG_I2C(transmissionStatus);     
     delay(commandDelay + 1);
     
     Wire.beginTransmission(oldAddress);
     Wire.send(commandRegister);
     Wire.send(0xA5);    // also tried changing this arguement to 165
     transmissionStatus = Wire.endTransmission();
     DEBUG_PRINTLN("Third byte sent");
     DEBUG_I2C(transmissionStatus);     
     delay(commandDelay + 1);
     
     Wire.beginTransmission(oldAddress);
     Wire.send(commandRegister);
     Wire.send(newAddress); 
     transmissionStatus = Wire.endTransmission();
     DEBUG_PRINTLN("New address sent");
     DEBUG_I2C(transmissionStatus);
     delay(1000);
     
     DEBUG_PRINTLN("Leaving changeI2Caddress function");
}

void printI2Cstatus(int I2Cstatus)
{
    switch (I2Cstatus) 
    {
    case 0:
      Serial.println("0: Success");
      break;
    case 1:
      Serial.println("1: data too long to fit in transmit buffer");
      break;
    case 2:
      Serial.println("2: received NACK on transmit of address");
      break;
    case 3:
      Serial.println("3: received NACK on transmit of data");
      break;
    case 4:
      Serial.println("4: other error");
      break;
    default: 
      // if nothing else matches, do the default
      Serial.print(I2Cstatus);
      Serial.println(": undefined value");
      
    }
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

void setAcceleration(uint8_t MD25address, uint8_t value)
{
  Wire.beginTransmission(MD25address);                      // Send byte to set acceleration
  Wire.send(MD25_ACCELERATION_REG);
  Wire.send(value);
  Wire.endTransmission();
}

void joystickDrive()// capture joystick position, compute speeds, send to wheels
{      
    uint16_t throttle, steering, rotation;
    uint16_t xraw, yraw, twistraw;
    yraw = analogRead(JOYSTICK_Y_PIN);
    xraw = analogRead(JOYSTICK_X_PIN);
    twistraw = analogRead(JOYSTICK_TWIST_PIN);
    DEBUG_PRINT("x joystick value is: ");
    DEBUG_PRINTLN(xraw);
    DEBUG_PRINT("y joystick value is: ");
    DEBUG_PRINTLN(yraw);
    DEBUG_PRINT("twist joystick value is: ");
    DEBUG_PRINTLN(twistraw);
    DEBUG_PRINT("throttle is: ");
    DEBUG_PRINTLN(throttle);
    DEBUG_PRINT("steering is: ");
    DEBUG_PRINTLN(steering);
    DEBUG_PRINT("rotation is: ");
    DEBUG_PRINTLN(rotation);
    DEBUG_PRINT("left front speed is: ");
    DEBUG_PRINTLN(leftFrontSpd);
    DEBUG_PRINT("right front speed is: ");
    DEBUG_PRINTLN(rightFrontSpd); 
    DEBUG_PRINT("left rear speed is: ");
    DEBUG_PRINTLN(leftRearSpd);
    DEBUG_PRINT("right rear speed is: ");
    DEBUG_PRINTLN(rightRearSpd);
    DEBUG_SPDELAY;
        
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
    
      if(twistraw > TWISTRAW_CENTERED + HALF_DEADBAND)//twist left
      {
        rotation = map(twistraw, TWISTRAW_CENTERED + HALF_DEADBAND, 1023, -0, -255);// reverse pot coordinates to agree with cartesian        
      }
      else if(twistraw < TWISTRAW_CENTERED - HALF_DEADBAND)//twist right
      {
        rotation = map(twistraw, TWISTRAW_CENTERED - HALF_DEADBAND, 0, 0, 255);// reverse pot coordinates to agree with cartesian        
      }
      else// in Twist deadband
      {
        rotation = 0;
      }
      
  //convert x,y,theta to lf,rf,lr,rr   
  //leftSpd and rightSpd will contain a number from -255 to 255 that gets updated each time the loop runs.
  //-255 equates to full reverse. 0 equates to anywhere within the deadband.  255 is full forward.
    int8_t wheelSpeed[] = {0,0,0,0};
    //compute desired wheel speeds
     wheelSpeed[0] = (throttle + steering + rotation)/2; //leftFrontSpd 
     wheelSpeed[1] = (throttle - steering - rotation)/2; //rightFrontSpd
     wheelSpeed[2] = (throttle - steering + rotation)/2; //leftRearSpd 
     wheelSpeed[3] = (throttle + steering - rotation)/2; // rightRearSpd
    
    drive(wheelSpeed[0], wheelSpeed[1], wheelSpeed[2], wheelSpeed[3]);
}//end joystickDrive()

void displayVolts()
{
  LCD03.print(LCD03_MOVE_CURSOR, BYTE);
  LCD03.print(61, BYTE);                                   // Move cursor to space 61
  LCD03.print("Batt Volts = ");
  LCD03.print(batteryVolts/10, DEC);                       // Print batery volts / 10 to give you the number of whole volts
  LCD03.print(".");                                        // As arduino has truncates floating point numbers we print a . here to act as a decimal point
  LCD03.print(batteryVolts%10, DEC);                       // Prints Battery volts % 10 to give us the 
  
  delay(50);                                             // Wait to make sure everything is sent
}
