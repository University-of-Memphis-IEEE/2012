

uint16_t getBearingDegrees()
uint8_t getBearing()
void displayWheelSpeeds()
void displayWheelEncoders()
void displaySonars()
void displayWheelCurrents()
void displayVolts()
void displayCompass()
void LCDdisplay()
// fullStop()
// driveWheelSpeed(Wheel_t wheel, int16_t speed)
// drive4wheelSpeeds(int16_t LFspeed, int16_t RFspeed, int16_t LRspeed, int16_t RRspeed)
// encoderReset()
// int32_t getEncoderCount(Wheel_t wheel)
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
