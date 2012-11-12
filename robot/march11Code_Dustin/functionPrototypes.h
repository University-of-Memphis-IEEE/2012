//     Left side pins                         GND
static const uint8_t TONE_PIN            =     27;
//                             I2C   SCL        0
//                             I2C   SDA        1
static const uint8_t FRONT_DIGITAL_IR_PIN =     2; // or    Camera Rx  comment out line if camera attached
static const uint8_t START_PIN           =      3; // or    Camera Tx  comment out line if camera attached
static const uint8_t ICP_PIN             =      4;
static const uint8_t REAR_SRF05_ECHO_PIN =      5;
static const uint8_t TEENSY_LED_PIN      =      6;
static const uint8_t FRONT_POWER_PIN     =      7;
static const uint8_t REAR_POWER_PIN      =      8;
//static const uint8_t START_PIN           =      9; // remove beginning comment if sensor attached here
static const uint8_t RELAY_A_PIN         =     10;
static const uint8_t RELAY_B_PIN         =     11;
//static const uint8_t FRONT_DIGITAL_IR_PIN =    12; // remove beginning comment if sensor attached here
static const uint8_t TASK_CAP_LOW_PIN    =     13; // resistor side, green wire
static const uint8_t REF_CAP_LOW_PIN     =     14; // resistor side, green wire
static const uint8_t TASK_CAP_HIGH_PIN   =     15; // no resistor, comparator +
static const uint8_t REF_CAP_HIGH_PIN    =     16; // no resistor, comparator -
static const uint8_t CAP_RESULT_PIN      =     17; // 

//    Right side Pins                         +5V
static const uint8_t FRONT_SRF05_ECHO_PIN =    26;
static const uint8_t LEFT_SRF05_ECHO_PIN  =    25;
static const uint8_t RIGHT_SRF05_ECHO_PIN =    24;
static const uint8_t FRONT_SRF05_TRIGGER_PIN = 23;
static const uint8_t LEFT_SRF05_TRIGGER_PIN =  22;
static const uint8_t RIGHT_SRF05_TRIGGER_PIN = 21;
static const uint8_t REAR_SRF05_TRIGGER_PIN =  20;
static const uint8_t LEFT_BUMP_SWITCH_PIN =    19;
static const uint8_t RIGHT_BUMP_SWITCH_PIN =   18;
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

int16_t getTemperaturePixel(uint8_t pixelNum);
int16_t getAmbient();
void turnMinimum(Direction_t direction);
void driveForwardXclicks(uint32_t clicks);
void turn90degrees(Direction_t direction);
static const boolean cameraConnected = false;
void begin();
void setCsrLC(uint8_t line, uint8_t column);
 void backlightOn();
void zeroCompass();
void sonarSetup();
uint16_t getBearingDegrees();
uint8_t getBearing();
void displayWheelSpeeds();
void displayWheelEncoders();
void displaySonars();
void displayWheelCurrents();
void displayVolts();
void displayCompass();
void LCDdisplay();
void fullStop();
void driveWheelSpeed(Wheel_t wheel, int16_t speed);
void drive4wheelSpeeds(int16_t LFspeed, int16_t RFspeed, int16_t LRspeed, int16_t RRspeed);
void encoderReset();
int32_t getEncoderCount(Wheel_t wheel);
uint16_t getDistanceToFrontObject();
uint16_t getDistanceToLeftObject();
uint16_t getDistanceToRightObject();
uint16_t getDistanceToRearObject();
uint8_t getWheelCurrent(Wheel_t);
uint8_t getVolts(uint8_t MD25address);

uint8_t compassOffset;

static const uint8_t NORTH_HEADING =            0  ;// heading divides the unit circle into 256 parts 0-255
static const uint8_t NORTHEAST_HEADING =  256 * 1/8;
static const uint8_t EAST_HEADING =       256 * 2/8;	  
static const uint8_t SOUTHEAST_HEADING =  256 * 3/8;
static const uint8_t SOUTH_HEADING =      256 * 4/8;
static const uint8_t SOUTHWEST_HEADING =  256 * 5/8;
static const uint8_t WEST_HEADING =	  256 * 6/8;
static const uint8_t NORTHWEST_HEADING =  256 * 7/8;
 	  
  
	  
  


static const uint8_t GPIO14_ADDR = 0x40 >> 1; // Address of GPIO14 
    // GPIO read registers
    static const uint8_t GPIO14_FIRMWARE_REVISION_REG = 0;
    static const uint8_t GPIO14_RESULT_HIGH_BYTE_REG =  1;
    static const uint8_t GPIO14_RESULT_LOW_BYTE_REG = 2;
    static const uint8_t GPIO14_AD_CONTROL_REG = 3;
    static const uint8_t GPIO14_PORT_A_REG = 4;
    static const uint8_t GPIO14_PORT_B_REG = 5;
    static const uint8_t GPIO14_PWM_REG = 6;
    static const uint8_t GPIO14_ZERO_REG = 7;
    // GPIO write registers
    static const uint8_t GPIO14_COMMAND_REG = 0;
    static const uint8_t GPIO14_PORT_A_IO_REG =  1;
    static const uint8_t GPIO14_PORT_B_IO_REG = 2;
//    static const uint8_t GPIO14_AD_CONTROL_REG = 3;
//    static const uint8_t GPIO14_PORT_A_REG = 4;
//    static const uint8_t GPIO14_PORT_B_REG = 5;
//    static const uint8_t GPIO14_PWM_REG = 6;
    static const uint8_t GPIO14_ADDRESS_CHANGE_REG = 7;
    // commands
 /*   static const uint8_t GPIO14_
    static const uint8_t GPIO14_
    GET_S4A	8 (0x08)	Get Range of SRF04 A
GET_S4B	9 (0x09)	Get Range of SRF04 B
GET_S5A	10 (0x0A)	Get Range of SRF05 A
GET_S5B	11 (0x0B)	Get Range of SRF05 B
SET_US	12 (0x0C)	Set ranging in uS
SET_CM	13 (0x0D)	Set ranging in centimeters
SET_IN	14 (0x0E)	Set ranging in Inches
*/
    
static const uint8_t CMPS10_ADDR = 0xC0 >> 1;                              // Address of CMPS10 compass
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


static const uint8_t LCD03_ADDR = 0xC6 >> 1;
//LCD03 READ ONLY registers
static const uint8_t LCD03_BUFFER_REMAINING_REG = 0;	//Number of free bytes in FIFO buffer
static const uint8_t LCD03_KEYPAD_LOW_REG = 1;	//Keypad state Low byte	
static const uint8_t LCD03_KEYPAD_HIGH_REG = 2;	//Keypad state High byte
static const uint8_t LCD03_VERSION_REG = 3;	//Version
//LCD03 WRITE ONLY register
static const uint8_t LCD03_CMD_REG = 0; //Command register
    //Commands
    static const uint8_t LCD03_NULL_CMD = 0;	//null (ignored)	Ignored as a no operation
    static const uint8_t LCD03_CURSOR_HOME_CMD = 1;	//Cursor Home	 Sets the cursor to the home position (top left)
    static const uint8_t LCD03_SET_CURSOR_CMD = 2;	//Set cursor (1-80 or 32)	Cursor to a position specified by the next byte, where 1 is the top left and 80/32 is the bottom right
    static const uint8_t LCD03_SET_CURSOR_LC_CMD = 3;	//set cursor (line, column)	Sets cursor using two bytes, where first byte is the line and the second byte is the column
    static const uint8_t LCD03_HIDE_CURSOR_CMD = 4;	//Hide cursor	stops the position cursor from appearing on the display 
    static const uint8_t LCD03_UNDERLINE_CURSOR_CMD = 5;	//Show underline cursor	Changes the cursor to the underline type 
    static const uint8_t LCD03_BLINK_CURSOR_CMD = 6;	//Show blinking cursor	Changes the cursor to the blinking type
    static const uint8_t LCD03_BACKSPACE_CMD = 8;	//Backspace	deletes the preceding character from the current position on the display
    static const uint8_t LCD03_TAB_HORIZONTAL_CMD = 9;	//Horizontal tab (by tab set)	Moves the current position across by the tab space set by command 18 (default tab space 4)
    static const uint8_t LCD03_LINE_FEED_CMD = 10;	//Smart line feed	Moves the cursor down one line to the position beneath in the same column
    static const uint8_t LCD03_TAB_VERTICAL_CMD = 11;	//Vertical tab	Moves the cursor up one line to the position above in the same column 
    static const uint8_t LCD03_CLEAR_SCREEN_CMD = 12;	//Clear screen	Clears the screen and sets cursor to the home position
    static const uint8_t LCD03_RETURN_CMD = 13;	        //Carriage Return	Moves the cursor to the start of the next line
    static const uint8_t LCD03_CLEAR_COLUMN_CMD = 17;	//Clear Column	Clears the contents of the current column and moves cursor right by one column
    static const uint8_t LCD03_SET_TAB_SIZE_CMD = 18;	//Tab set	Sets the required tab size, the following byte can be a size of between 1 and 10
    static const uint8_t LCD03_BACKLIGHT_ON_CMD = 19;	//Backlight on 	Turns the backlight of the LCD03 on
    static const uint8_t LCD03_BACKLIGHT_OFF_CMD = 20;	//Backlight off (default)	Turns the backlight of the LCD03 off
    static const uint8_t LCD03_CHANGE_ADDR_CMD = 25;     //First byte of sequence to change LCD03 address (see changing address, software V4+)       
    //Version 4 and above of the LCD03 software contains the facility to easily change the modules address on the I2C bus system in the range of 0xC6 - 0xCE ( even numbers only ). This is achieved by sending the following sequence:
    //0x19     ( 1st byte of change address command )
    //0xA0     ( 2nd byte of change address command )
    //0xAA     ( 3rd byte of change address command )
    //0xA5     ( 4th byte of change address command )
    //0xC6, 0xC8,0xCA,0xCC or 0xCE    ( new address to map LCD03 at )
    //Version 4+ also displays the current address on the display every time the module is first powered
    static const uint8_t LCD03_GENERATE_CHARACTER_CMD = 27;  //First byte of sequence to create a custom character. Allows 8 custom chars to be mapped at positions 128-135.
        /*followed by
        128 (location to be filled)
        128 (byte 0)
        132 (byte1)
        142 (byte2)
        149 (byte3)
        132 (byte 4)
        132 (byte 5)
        132 (byte 6)
        128 (byte 7)27	Custom char generator	allows 8 custom chars to be built. See custom char generator below
        */
    static const uint8_t LCD03_KEYSCAN_20HZ_CMD = 28;	//Double keypad scan rate	Increases the frequency of the keypad scan to 20hz (software V3+)
    static const uint8_t LCD03_KEYSCAN_10HZ_CMD = 29;	//Normal keypad scan rate	Returns to the default keypad scan frequency of 10hz (software V3+)
    /* the LCD03 module will automatically scan a 4 x 3 Keypad at regular intervals. The status of the keys are provided in two bytes, shown by the diagram below. Each bit represents the row and column of each button on the keypad. The second row is the keypad characters when using example keypad.
 	 	 	High	byte	 	 	 	 	 	 	 	Low	byte	 	 	 
0        0       0	0	4/3	4/2	4/1	3/3	        	3/2	3/1	2/3	2/2	2/1	1/3	1/2	1/1
0        0	 0	0	#	0	*	9		        8	7	6	5	4	3	2	1
Any key press will result in the corresponding bit in the byte being driven high. In I2C mode these bytes are available for reading from registers one and two.
In serial mode, just send 16 to the LCD03 and it will reply with the two bytes as above with the low byte first.
*/
 
//  static const uint8_t LCD03_ASCII_CMD = 32-255;	//Writes ASCII chars straight to the display


static const uint8_t FRONT_MD25_ADDR = 0xB4 >> 1;                    // Address of front MD25 motor control board
    static const uint8_t REAR_MD25_ADDR = 0xB0 >> 1;                     // Address of rear MD25 motor control board
    //MD25 Motor Driver READ/WRITE registers
    static const uint8_t MD25_RIGHT_SPEED_REG = 1;    //Used in mode 0 and 1
    static const uint8_t MD25_LEFT_SPEED_REG = 0;   //Used in mode 0 and 1
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

static const uint8_t TPA81_ADDR = 0xD0 >> 1;                          // Address of TPA81 thermopile array
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
   


