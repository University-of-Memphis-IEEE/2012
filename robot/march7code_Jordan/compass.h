#ifndef compass_h
#define compass_h

#include "Arduino.h"
uint8_t compassOffset;
uint8_t currentHeading;

static const uint8_t EAST_HEADING = 	  0  ;// heading divides the unit circle into 256 parts 0-255
static const uint8_t NORTHEAST_HEADING =  256 * 1/8;
static const uint8_t NORTH_HEADING =	  256 * 2/8;
static const uint8_t NORTHWEST_HEADING =  256 * 3/8;
static const uint8_t WEST_HEADING = 	  256 * 4/8;
static const uint8_t SOUTHWEST_HEADING =  256 * 5/8;
static const uint8_t SOUTH_HEADING =	  256 * 6/8;
static const uint8_t SOUTHEAST_HEADING =  256 * 7/8;


static const uint8_t CMPS10_ADDR = 0x60;                              // Address of CMPS10 compass
    //Compass registers, read only
    static const uint8_t CMPS10_VERSION_REG = 0;	    //Software version
    static const uint8_t CMPS10_BEARING_BYTE_REG = 1;  	    //Compass Bearing as a byte, i.e. 0-255 for a full circle
    static const uint8_t CMPS10_BEARING_DEGREE_HIGH_REG = 2;  	//Compass Bearing as a word, i.e. 0-3599 for a full circle, representing 0-359.9 degrees.
    static const uint8_t CMPS10_BEARING_DEGREE_LOW_REG = 3;  	//Compass Bearing as a word, i.e. 0-3599 for a full circle, representing 0-359.9 degrees.
    static const uint8_t CMPS10_PITCH_REG = 4;   	    //Pitch angle - signed byte giving angle in degrees from the horizontal plane
    static const uint8_t CMPS10_ROLL_REG = 5; 	            //Roll angle - signed byte giving angle in degrees from the horizontal plane
   // 6	Unused
   // 7	Unused
   // 8	Unused
   // 9	Unused
    static const uint8_t CMPS10_MAG_X_RAW_HIGH_REG = 10;    //Magnetometer X axis raw output, 16 bit signed integer with register 10 being the upper 8 bits
    static const uint8_t CMPS10_MAG_X_RAW_LOW_REG = 11;     //Magnetometer X axis raw output, 16 bit signed integer with register 11 being the lower 8 bits
    static const uint8_t CMPS10_MAG_Y_RAW_HIGH_REG = 12;    //Magnetometer Y axis raw output, 16 bit signed integer with register 12 being the upper 8 bits
    static const uint8_t CMPS10_MAG_Y_RAW_LOW_REG = 13;	    //Magnetometer Y axis raw output, 16 bit signed integer with register 13 being the lower 8 bits
    static const uint8_t CMPS10_MAG_Z_RAW_HIGH_REG = 14;    //Magnetometer Z axis raw output, 16 bit signed integer with register 14 being the upper 8 bits
    static const uint8_t CMPS10_MAG_Z_RAW_LOW_REG = 15;	    //Magnetometer Z axis raw output, 16 bit signed integer with register 15 being the lower 8 bits
    static const uint8_t CMPS10_ACCEL_X_RAW_HIGH_REG = 16;	//Accelerometer  X axis raw output, 16 bit signed integer with register 16 being the upper 8 bits
    static const uint8_t CMPS10_ACCEL_X_RAW_LOW_REG = 17;	//Accelerometer  X axis raw output, 16 bit signed integer with register 17 being the lower 8 bits
    static const uint8_t CMPS10_ACCEL_Y_RAW_HIGH_REG =  18;	//Accelerometer  Y axis raw output, 16 bit signed integer with register 18 being the upper 8 bits
    static const uint8_t CMPS10_ACCEL_Y_RAW_LOW_REG =  19;	//Accelerometer  Y axis raw output, 16 bit signed integer with register 19 being the lower 8 bits
    static const uint8_t CMPS10_ACCEL_Z_RAW_HIGH_REG =  20;	//Accelerometer  Z axis raw output, 16 bit signed integer with register 20 being the upper 8 bits
    static const uint8_t CMPS10_ACCEL_Z_RAW_LOW_REG =  21;	//Accelerometer  Z axis raw output, 16 bit signed integer with register 21 being the lower 8 bits   
    static const uint8_t CMPS10_CMD_REG = 22;    //Command register
    
uint8_t getBearing()
{
   Wire.beginTransmission(CMPS10_ADDR);           //starts communication with CMPS10
   Wire.send(CMPS10_BEARING_BYTE_REG);                              //Sends the register we wish to start reading from
   Wire.endTransmission();

   Wire.requestFrom(CMPS10_ADDR, (uint8_t)1);              // Request 1 byte from CMPS10
   while(Wire.available() < 1);               // Wait for bytes to become available
   uint8_t bearing = Wire.receive(); 
   return(bearing - compassOffset);  
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

void zeroCompass()
{
    compassOffset = 0;
    compassOffset = getBearing();  
}
#endif
