//no include guard
#include "Arduino.h"

#ifdef DEBUG
  #define TRACE(name, variable)  \
    Serial.print(name);     \
    Serial.print(" == ");   \
    Serial.println(variable);
  #define DEBUG_BEGIN(x)    Serial.begin(x)
  #define DEBUG_PRINT(x)     Serial.print (x)
  #define DEBUG_PRINTDEC(x)     Serial.print (x, DEC)
  #define DEBUG_PRINTLN(x)  Serial.println (x)
  #define DEBUG_PRINT_AT(str)    \
    Serial.print(millis());     \
    Serial.print(": ");         \
    Serial.print(__PRETTY_FUNCTION__); \
    Serial.print(' ');          \
    Serial.print(__FILE__);     \
    Serial.print(':');          \
    Serial.print(__LINE__);     \
    Serial.print(' ');          \
    Serial.println(str);
  #define DEBUG_SPDELAY    delay(250)
  #define DEBUG_DELAY(x)
  #define DEBUG_I2C(x) printI2Cstatus(x)
#else
  #define TRACE(name, variable)
  #define DEBUG_BEGIN(x)
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINT_AT(str)
  #define DEBUG_SPDELAY
  #define DEBUG_DELAY(x) 
  #define DEBUG_I2C(x)
#endif

void printI2Cstatus(uint8_t I2Cstatus)
		{
			switch (I2Cstatus) 
			{
			case 0:
			  Serial.println("0 Success");
			  break;
			case 1:
			  Serial.println("1 data too long to fit in transmit buffer");
			  break;
			case 2:
			  Serial.println("2 received NACK on transmit of address");
			  break;
			case 3:
			  Serial.println("3 received NACK on transmit of data");
			  break;
			case 4:
			  Serial.println("4 other error");
			  break;
			case 255:
			  Serial.println("255 default transmissionStatus");
			  break;  
			default: 
			  // if nothing else matches, do the default
			  Serial.print(I2Cstatus);
			  Serial.println(" unrecognized value ");
			}
		}


