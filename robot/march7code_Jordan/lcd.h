#ifndef lcd_h
#define lcd_h
#include "Arduino.h"
#include "Print.h"
//4 Line x 20 Column display
static const uint8_t LCD03_ADDR = 0xC6;
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

class LCD03class : public Print
{
  public:
   LCD03class(){}
          
   uint8_t init()
          {
            _transmissionStatus = 255;
              //TODO write code to load generated character sets from flash(progmem) into LCD

          }
          
  uint8_t begin()
          {
            init();
            clear();
            homeCsr();
            hideCsr();
            backlightOn();
          
          }

          
  uint8_t getAddress()
		{
			return(LCD03_ADDR);
		}
		
  uint8_t getBufferFreeBytes()
		{  
			
			Wire.beginTransmission(LCD03_ADDR);                      // Send byte to read reg
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_BUFFER_REMAINING_REG);
			Wire.endTransmission();
		  
			Wire.requestFrom(LCD03_ADDR, (uint8_t)1);                         // Request 1 byte form MD25
			while(Wire.available() < 1);                              // Wait for byte to arrive 
			uint8_t freeBytes = Wire.receive();
			return(freeBytes);
		}	
			
		
  uint16_t getKeypadState()
		{
			uint16_t keypad;
			Wire.beginTransmission(LCD03_ADDR);                      // Send byte to read reg
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_KEYPAD_HIGH_REG);			
			Wire.endTransmission();
		  
			Wire.requestFrom(LCD03_ADDR, (uint8_t)1);                         // Request HIGH byte from LCD
			while(Wire.available() < 1);  
			keypad = Wire.receive();  // receive high byte 
			keypad = keypad << 8;    // shift high byte to be high 8 bits
								
			Wire.beginTransmission(LCD03_ADDR);                      // Send byte to read reg
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_KEYPAD_LOW_REG);			
			Wire.endTransmission();
		  
			Wire.requestFrom(LCD03_ADDR, (uint8_t)1);                         // Request LOW byte from LCD
			while(Wire.available() < 1); 
			keypad |= Wire.receive(); // receive low byte as lower 8 bits
			return(keypad); 
		}
		
  uint8_t getVersion() //LCD03_VERSION_REG = 3;	
		{
			uint16_t version;
			Wire.beginTransmission(LCD03_ADDR);                      // Send byte to read reg
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_VERSION_REG);			
			Wire.endTransmission();
		  
			Wire.requestFrom(LCD03_ADDR, (uint8_t)1);                         // Request version byte from LCD
			while(Wire.available() < 1);  
			version = Wire.receive();  // receive high byte 
			return(version);
		}
		
  inline void command(uint8_t value) 
		{	
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(value);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("command transmissionStatus");
                        DEBUG_I2C(_transmissionStatus);
					
		}
  void send()// called by Print::print
          {
          
          }
		
      //LCD03 WRITE ONLY registers
      //LCD03_CMD_REG = 0; //Command register
          //Commands
  void noop()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_NULL_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("noop transmissionStatus");  
                        DEBUG_I2C(_transmissionStatus);
			
		}
		// static const uint8_t LCD03_NULL_CMD = 0;	//null (ignored)	Ignored as a no operation
		
		
  void homeCsr()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_CURSOR_HOME_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("homeCsr transmissionStatus");
                        DEBUG_I2C(_transmissionStatus);
			 
		}
		//LCD03_CURSOR_HOME_CMD = 1;	//Cursor Home	 Sets the cursor to the home position (top left)
		
  void setCsr(uint8_t position)
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_SET_CURSOR_CMD);
			Wire.send(position);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("setCsr transmissionStatus");
                        DEBUG_I2C(_transmissionStatus);
			
		}
		//LCD03_SET_CURSOR_CMD = 2;	//Set cursor (1-80 or 32)	Cursor to a position specified by the next byte, where 1 is the top left and 80/32 is the bottom right
  
  void setCsrLC(uint8_t line, uint8_t column)
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_SET_CURSOR_LC_CMD);
			Wire.send(line);
			Wire.send(column);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("setCsrLC transmissionStatus");  
                        DEBUG_I2C(_transmissionStatus);
			
		}
		// LCD03_SET_CURSOR_LC_CMD = 3;	//set cursor (line, column)	Sets cursor using two bytes, where first byte is the line and the second byte is the column
  
  void hideCsr()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_HIDE_CURSOR_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("hideCsr transmissionStatus"); 
                        DEBUG_I2C(_transmissionStatus);
			
		}
		// LCD03_HIDE_CURSOR_CMD = 4;	//Hide cursor	stops the position cursor from appearing on the display 

	
  void underlineCsr()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_UNDERLINE_CURSOR_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("underlineCsr transmissionStatus"); 
                        DEBUG_I2C(_transmissionStatus);
			 
		}
		//LCD03_UNDERLINE_CURSOR_CMD = 5;	//Show underline cursor	Changes the cursor to the underline type 

  void blinkCsr()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_BLINK_CURSOR_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("blinkCsr transmissionStatus");
                        DEBUG_I2C(_transmissionStatus);
			
		}
		//LCD03_BLINK_CURSOR_CMD = 6;	//Show blinking cursor	Changes the cursor to the blinking type
		
  void backspace()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_BACKSPACE_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("backspace transmissionStatus");
                        DEBUG_I2C(_transmissionStatus);
			
		}
		//LCD03_BACKSPACE_CMD = 8;	//Backspace	deletes the preceding character from the current position on the display
		
  void tab()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_TAB_HORIZONTAL_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("tab transmissionStatus"); 
                        DEBUG_I2C(_transmissionStatus);
			
		}
		//LCD03_TAB_HORIZONTAL_CMD = 9;	//Horizontal tab (by tab set)	Moves the current position across by the tab space set by command 18 (default tab space 4)

  void down()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_LINE_FEED_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("down transmissionStatus");
                        DEBUG_I2C(_transmissionStatus);
			 
		}
		//LCD03_LINE_FEED_CMD = 10;	//Smart line feed	Moves the cursor down one line to the position beneath in the same column

  void up()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_TAB_VERTICAL_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("up transmissionStatus");   
                        DEBUG_I2C(_transmissionStatus);
			 
		}
		//LCD03_TAB_VERTICAL_CMD = 11;	//Vertical tab	Moves the cursor up one line to the position above in the same column 
		
		void left()
		{}
		
		void right()
		{}

  void clear()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_CLEAR_SCREEN_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("clear transmissionStatus"); 
                        DEBUG_I2C(_transmissionStatus);
			
		}
		//LCD03_CLEAR_SCREEN_CMD = 12;	//Clear screen	Clears the screen and sets cursor to the home position
		
  void bink()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_RETURN_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("bink transmissionStatus");
                        DEBUG_I2C(_transmissionStatus);
			 
		}
		//LCD03_RETURN_CMD = 13;	        //Carriage Return	Moves the cursor to the start of the next line

  void clearColumn()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_CLEAR_COLUMN_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("clearColumn transmissionStatus");
                        DEBUG_I2C(_transmissionStatus);
			
		}
		//LCD03_CLEAR_COLUMN_CMD = 17;	//Clear Column	Clears the contents of the current column and moves cursor right by one column

  void setTab(uint8_t size)
		{
			if(size >= 1 && size <=10)
			{
				Wire.beginTransmission(LCD03_ADDR);
				Wire.send(LCD03_CMD_REG);
				Wire.send(LCD03_SET_TAB_SIZE_CMD);
				Wire.send(size);
				_transmissionStatus = Wire.endTransmission();
				DEBUG_PRINTLN("setTab transmissionStatus");
                                DEBUG_I2C(_transmissionStatus);
				
			}
		}
		//LCD03_SET_TAB_SIZE_CMD = 18;	//Tab set	Sets the required tab size, the following byte can be a size of between 1 and 10
		
  void backlightOn()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_BACKLIGHT_ON_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("backlightOn transmissionStatus");  
                        DEBUG_I2C(_transmissionStatus);
			
		}
		//LCD03_BACKLIGHT_ON_CMD = 19;	//Backlight on 	Turns the backlight of the LCD03 on
		
  void backlightOff()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_BACKLIGHT_OFF_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("backlightOff transmissionStatus");
                        DEBUG_I2C(_transmissionStatus);
			 
		}
		//LCD03_BACKLIGHT_OFF_CMD = 20;	//Backlight off (default)	Turns the backlight of the LCD03 off

  void changeAddress(uint8_t newAddress)
		{
			//must be run with ONLY the device whose address is to be changed connected to the I2C bus
			DEBUG_PRINTLN("");                                 DEBUG_I2C(_transmissionStatus);Serial.println("Entered changeI2Caddress function");
			if(newAddress == 0xC6 || newAddress == 0xC8 || newAddress == 0xCA || newAddress == 0xCC ||newAddress ==  0xCE)//8 bit addresses
			newAddress = newAddress >> 1;
			if(newAddress == 0xC6  >> 1 || newAddress == 0xC8  >> 1 || newAddress == 0xCA  >> 1 || newAddress == 0xCC  >> 1 || newAddress ==  0xCE  >> 1)//7 bit addresses
			{		 
			 DEBUG_PRINTLN("");                                 DEBUG_I2C(_transmissionStatus);Serial.println("Valid address received");
			 Wire.beginTransmission(LCD03_ADDR);
			 Wire.send(LCD03_CMD_REG);
			 Wire.send(LCD03_CHANGE_ADDR_CMD);    
			 _transmissionStatus = Wire.endTransmission();
			 DEBUG_PRINTLN("Address change command sent");                                 \
                         DEBUG_I2C(_transmissionStatus);
			 
			 delay(10);
			 
			 Wire.beginTransmission(LCD03_ADDR);
			 Wire.send(LCD03_CMD_REG);
			 Wire.send(0x19);    
			 _transmissionStatus = Wire.endTransmission();
			 DEBUG_PRINTLN("First byte sent"); 
                         DEBUG_I2C(_transmissionStatus);
			    
			 delay(10);
			 
			 Wire.beginTransmission(LCD03_ADDR);
			 Wire.send(LCD03_CMD_REG);
			 Wire.send(0xA0);   
			 _transmissionStatus = Wire.endTransmission();
			 DEBUG_PRINTLN("Second byte sent");
                         DEBUG_I2C(_transmissionStatus);
			     
			 delay(10);
			 
			 Wire.beginTransmission(LCD03_ADDR);
			 Wire.send(LCD03_CMD_REG);
			 Wire.send(0xAA);   
			 _transmissionStatus = Wire.endTransmission();
			 DEBUG_PRINTLN("Third byte sent");
                         DEBUG_I2C(_transmissionStatus);
			  
			 delay(10);
			 
			 Wire.beginTransmission(LCD03_ADDR);
			 Wire.send(LCD03_CMD_REG);
			 Wire.send(0xA5);   
			 _transmissionStatus = Wire.endTransmission();
			 DEBUG_PRINTLN("Fourth byte sent");
                         DEBUG_I2C(_transmissionStatus);
			    
			 delay(10);
			 
			 Wire.beginTransmission(LCD03_ADDR);
			 Wire.send(LCD03_CMD_REG);
			 Wire.send(newAddress); 
			 _transmissionStatus = Wire.endTransmission();
			 DEBUG_PRINTLN("New address sent");
                         DEBUG_I2C(_transmissionStatus);
			 
			 delay(1000);
			 DEBUG_PRINT("Attention! Be sure to change code constant LCD03_ADDR to equal ");
			 DEBUG_PRINTLN(newAddress);
                         DEBUG_PRINTLN("Leaving changeAddress function");
                         
			}
			else
			DEBUG_PRINTLN("Invalid address received");
				//LCD03_CHANGE_ADDR_CMD = 25;     //First byte of sequence to change LCD03 address (see changing address, software V4+)       
			//Version 4 and above of the LCD03 software contains the facility to easily change the modules address on the I2C bus system in the range of 0xC6 - 0xCE ( even numbers only ). This is achieved by sending the following sequence:
			//0x19     ( 1st byte of change address command )
			//0xA0     ( 2nd byte of change address command )
			//0xAA     ( 3rd byte of change address command )
			//0xA5     ( 4th byte of change address command )
			//0xC6, 0xC8,0xCA,0xCC or 0xCE    ( new address to map LCD03 at )
			//Version 4+ also displays the current address on the display every time the module is first powered
		}
/* TODO finish this
	void generateCharacter(uint8_t characterNumber, uint8_t *rows)
		{
			if(characterNumber >= 1 && characterNumber <=8)
			characterNumber = characterNumber + 127;
			if(characterNumber >= 128 && characterNumber <=135)
			{
				Wire.beginTransmission(LCD03_ADDR);
				Wire.send(LCD03_CMD_REG);
				Wire.send(LCD03_GENERATE_CHARACTER_CMD);
				Wire.send(characterNumber);
				for (uint8_t i = 0; i < 8; i++)
				Wire.send(rows[i]&B10000000);
				_transmissionStatus = Wire.endTransmission();
				DEBUG_PRINTLN("generateCharacter transmissionStatus"); 
                                DEBUG_I2C(_transmissionStatus);
				
			}
			else if(characterNumber == 0)//clear all custom characters
			{
				Wire.beginTransmission(LCD03_ADDR);
				Wire.send(LCD03_CMD_REG);
				Wire.send(LCD03_GENERATE_CHARACTER_CMD);
				Wire.send(characterNumber);
				for (uint8_t i = 0; i < 8; i++)
				Wire.send(B10000000);
				_transmissionStatus = Wire.endTransmission();
				DEBUG_PRINTLN("generateCharacter transmissionStatus"); 
                                DEBUG_I2C(_transmissionStatus);
				 
			}			 	
		
		}
		
   void createCharacterSet(uint8_t setNumber,  )//TODO finish this
		{
			uint8_t bufferRows[8];
			for (uint8_t characterNumber = 0; characterNumber < 8; characterNumber++)
			{
				generateCharacter(characterNumber,  bufferRows)
				for (uint8_t j = 0; j < 8; j++)
			 {// read from prog_uchar characterSet[][8][8] =  //[characterSet][characterNumber][characterRow]
				memcpy_P(bufferRows, (uint_8*)pgm_read_byte(&(characterSet[chosenSet][i][j])));
				
			 }
				generateCharacter(characterNumber,  bufferRows)
			}
		}
	void sendCharacterSet(uint8_t chosenSet)
		{
			uint8_t bufferRows[8];
			for (uint8_t characterNumber = 0; characterNumber < 8; characterNumber++)
			{
				generateCharacter(characterNumber,  bufferRows)
				for (uint8_t j = 0; j < 8; j++)
			 {// read from prog_uchar characterSet[][8][8] =  //[characterSet][characterNumber][characterRow]
				memcpy_P(bufferRows, (uint_8*)pgm_read_byte(&(characterSet[chosenSet][i][j])));
				
			 }
				generateCharacter(characterNumber,  bufferRows)
			}
		}
*/

	void keyscan20Hz()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_KEYSCAN_20HZ_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("keyscan20Hz transmissionStatus"); 
                        DEBUG_I2C(_transmissionStatus);
			
		}
		//LCD03_KEYSCAN_20HZ_CMD = 28;	//Double keypad scan rate	Increases the frequency of the keypad scan to 20hz (software V3+)

	void keyscan10Hz()
		{
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_KEYSCAN_10HZ_CMD);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("keyscan10Hz transmissionStatus");
                        DEBUG_I2C(_transmissionStatus);
			
		}
		//LCD03_KEYSCAN_10HZ_CMD = 29;	//Normal keypad scan rate	Returns to the default keypad scan frequency of 10hz (software V3+)
		
	void printASCII(char character)
		{
			if(character >= 32 && character <= 255)//valid printable character
			{
				Wire.beginTransmission(LCD03_ADDR);
				Wire.send(LCD03_CMD_REG);
				Wire.send(character);
				Wire.endTransmission();                              
				
			}
                        else
                        {
                                Wire.beginTransmission(LCD03_ADDR);
				Wire.send(LCD03_CMD_REG);
				Wire.send('?');
				Wire.endTransmission();
                        }		
		}
 private:
        uint8_t _transmissionStatus;
	
        //Required virtual functions called by Print::print and Print::println         
        inline size_t write(uint8_t character)
                {
                  Wire.beginTransmission(LCD03_ADDR);
		  Wire.send(LCD03_CMD_REG);
		  Wire.send(character);
		  Wire.endTransmission();
                  return 1; // assume sucess
                }
                
        inline size_t write(const uint8_t *buffer, size_t size)
                {
                  Wire.beginTransmission(LCD03_ADDR);
		  Wire.send(LCD03_CMD_REG);
                  for(uint8_t i = 0; i < size; i++)
		    Wire.send(buffer[i]);
		  Wire.endTransmission();
                  return 1; // assume sucess
                }
          
};//LCD03class end

// make one instance for the user
extern LCD03class lcd = LCD03class() ;

// functions that use the LCD
void displayVolts()
{
  uint8_t batteryVolts = getVolts(FRONT_MD25_ADDR);      //get the voltage reading of the front motor controller
  lcd.setCsrLC(0, 0);                                        //move cursor to first line, first column
  lcd.print("Batt Volts = ");
  lcd.print(batteryVolts/10, DEC);                       // Print batery volts / 10 to give you the number of whole volts
  lcd.print(".");                                        // As arduino has truncates floating point numbers we print a . here to act as a decimal point
  lcd.print(batteryVolts%10, DEC);                       // Prints Battery volts % 10 to give us the 
  
  
}

void  displayStatus1();
void displayStatus2();
void displaySpeeds();
void displayWheelSpeeds();
void displayWheelEncoders();

void LCDdisplay()
{   
      if (sinceDisplayStatus1 >= 1500) 
      {
        sinceDisplayStatus1 = sinceDisplayStatus1 - 1500;
        displayStatus1();
      }
      
      if (sinceDisplayStatus2 >= 1500) 
      {
        sinceDisplayStatus2 = sinceDisplayStatus2 - 1500;
        displayStatus2();
      }
      
      if (sinceDisplayWheelSpeeds >= 1500) 
      {
        sinceDisplayWheelSpeeds = sinceDisplayWheelSpeeds - 1500;
        displayWheelSpeeds();
      }
      
      if (sinceDisplayWheelEncoders >= 1500) 
      {
        sinceDisplayWheelEncoders = sinceDisplayWheelEncoders - 1300;
        displayWheelEncoders();
      }
}

void  displayStatus1()
{

}

void displayStatus2()
{
  
}

void displayWheelSpeeds ()
{
  
}

void displaySpeeds()
{

}

void displayWheelEncoders()
{

}

void displaySonar()
{

}
    


#endif





/*
//PRINTABLE ASCII
                                                    HTML
DEC	OCT	HEX	BIN	    Symbol	Number   Name	Description
32	040	20	00100000	 	&#32;	 	Space
33	041	21	00100001	!	&#33;	 	Exclamation mark
34	042	22	00100010	"	&#34;	&quot;	Double quotes (or speech marks)
35	043	23	00100011	#	&#35;	 	Number
36	044	24	00100100	$	&#36;	 	Dollar
37	045	25	00100101	%	&#37;	 	Procenttecken
38	046	26	00100110	&	&#38;	&amp;	Ampersand
39	047	27	00100111	'	&#39;	 	Single quote
40	050	28	00101000	(	&#40;	 	Open parenthesis (or open bracket)
41	051	29	00101001	)	&#41;	 	Close parenthesis (or close bracket)
42	052	2A	00101010	*	&#42;	 	Asterisk
43	053	2B	00101011	+	&#43;	 	Plus
44	054	2C	00101100	,	&#44;	 	Comma
45	055	2D	00101101	-	&#45;	 	Hyphen
46	056	2E	00101110	.	&#46;	 	Period, dot or full stop
47	057	2F	00101111	/	&#47;	 	Slash or divide
48	060	30	00110000	0	&#48;	 	Zero
49	061	31	00110001	1	&#49;	 	One
50	062	32	00110010	2	&#50;	 	Two
51	063	33	00110011	3	&#51;	 	Three
52	064	34	00110100	4	&#52;	 	Four
53	065	35	00110101	5	&#53;	 	Five
54	066	36	00110110	6	&#54;	 	Six
55	067	37	00110111	7	&#55;	 	Seven
56	070	38	00111000	8	&#56;	 	Eight
57	071	39	00111001	9	&#57;	 	Nine
58	072	3A	00111010	:	&#58;	 	Colon
59	073	3B	00111011	;	&#59;	 	Semicolon
60	074	3C	00111100	<	&#60;	&lt;	Less than (or open angled bracket)
61	075	3D	00111101	=	&#61;	 	Equals
62	076	3E	00111110	>	&#62;	&gt;	Greater than (or close angled bracket)
63	077	3F	00111111	?	&#63;	 	Question mark
64	100	40	01000000	@	&#64;	 	At symbol
65	101	41	01000001	A	&#65;	 	Uppercase A
66	102	42	01000010	B	&#66;	 	Uppercase B
67	103	43	01000011	C	&#67;	 	Uppercase C
68	104	44	01000100	D	&#68;	 	Uppercase D
69	105	45	01000101	E	&#69;	 	Uppercase E
70	106	46	01000110	F	&#70;	 	Uppercase F
71	107	47	01000111	G	&#71;	 	Uppercase G
72	110	48	01001000	H	&#72;	 	Uppercase H
73	111	49	01001001	I	&#73;	 	Uppercase I
74	112	4A	01001010	J	&#74;	 	Uppercase J
75	113	4B	01001011	K	&#75;	 	Uppercase K
76	114	4C	01001100	L	&#76;	 	Uppercase L
77	115	4D	01001101	M	&#77;	 	Uppercase M
78	116	4E	01001110	N	&#78;	 	Uppercase N
79	117	4F	01001111	O	&#79;	 	Uppercase O
80	120	50	01010000	P	&#80;	 	Uppercase P
81	121	51	01010001	Q	&#81;	 	Uppercase Q
82	122	52	01010010	R	&#82;	 	Uppercase R
83	123	53	01010011	S	&#83;	 	Uppercase S
84	124	54	01010100	T	&#84;	 	Uppercase T
85	125	55	01010101	U	&#85;	 	Uppercase U
86	126	56	01010110	V	&#86;	 	Uppercase V
87	127	57	01010111	W	&#87;	 	Uppercase W
88	130	58	01011000	X	&#88;	 	Uppercase X
89	131	59	01011001	Y	&#89;	 	Uppercase Y
90	132	5A	01011010	Z	&#90;	 	Uppercase Z
91	133	5B	01011011	[	&#91;	 	Opening bracket
92	134	5C	01011100	\	&#92;	 	Backslash
93	135	5D	01011101	]	&#93;	 	Closing bracket
94	136	5E	01011110	^	&#94;	 	Caret - circumflex
95	137	5F	01011111	_	&#95;	 	Underscore
96	140	60	01100000	`	&#96;	 	Grave accent
97	141	61	01100001	a	&#97;	 	Lowercase a
98	142	62	01100010	b	&#98;	 	Lowercase b
99	143	63	01100011	c	&#99;	 	Lowercase c
100	144	64	01100100	d	&#100;	 	Lowercase d
101	145	65	01100101	e	&#101;	 	Lowercase e
102	146	66	01100110	f	&#102;	 	Lowercase f
103	147	67	01100111	g	&#103;	 	Lowercase g
104	150	68	01101000	h	&#104;	 	Lowercase h
105	151	69	01101001	i	&#105;	 	Lowercase i
106	152	6A	01101010	j	&#106;	 	Lowercase j
107	153	6B	01101011	k	&#107;	 	Lowercase k
108	154	6C	01101100	l	&#108;	 	Lowercase l
109	155	6D	01101101	m	&#109;	 	Lowercase m
110	156	6E	01101110	n	&#110;	 	Lowercase n
111	157	6F	01101111	o	&#111;	 	Lowercase o
112	160	70	01110000	p	&#112;	 	Lowercase p
113	161	71	01110001	q	&#113;	 	Lowercase q
114	162	72	01110010	r	&#114;	 	Lowercase r
115	163	73	01110011	s	&#115;	 	Lowercase s
116	164	74	01110100	t	&#116;	 	Lowercase t
117	165	75	01110101	u	&#117;	 	Lowercase u
118	166	76	01110110	v	&#118;	 	Lowercase v
119	167	77	01110111	w	&#119;	 	Lowercase w
120	170	78	01111000	x	&#120;	 	Lowercase x
121	171	79	01111001	y	&#121;	 	Lowercase y
122	172	7A	01111010	z	&#122;	 	Lowercase z
123	173	7B	01111011	{	&#123;	 	Opening brace
124	174	7C	01111100	|	&#124;	 	Vertical bar
125	175	7D	01111101	}	&#125;	 	Closing brace
126	176	7E	01111110	~	&#126;	 	Equivalency sign - tilde
127	177	7F	01111111		&#127;	 	Delete
//EXTENDED ASCII
                                                    HTML
DEC	OCT	HEX	BIN	    Symbol	Number   Name	Description
128	200	80	10000000	€	&#128;	&euro;	Euro sign
129	201	81	10000001	 	 	 	 
130	202	82	10000010	‚	&#130;	&sbquo;	Single low-9 quotation mark
131	203	83	10000011	ƒ	&#131;	&fnof;	Latin small letter f with hook
132	204	84	10000100	„	&#132;	&bdquo;	Double low-9 quotation mark
133	205	85	10000101	…	&#133;	&hellip;	Horizontal ellipsis
134	206	86	10000110	†	&#134;	&dagger;	Dagger
135	207	87	10000111	‡	&#135;	&Dagger;	Double dagger
136	210	88	10001000	ˆ	&#136;	&circ;	Modifier letter circumflex accent
137	211	89	10001001	‰	&#137;	&permil;	Per mille sign
138	212	8A	10001010	Š	&#138;	&Scaron;	Latin capital letter S with caron
139	213	8B	10001011	‹	&#139;	&lsaquo;	Single left-pointing angle quotation
140	214	8C	10001100	Œ	&#140;	&OElig;	Latin capital ligature OE
141	215	8D	10001101	 	 	 	 
142	216	8E	10001110	Ž	&#142;	 	Latin captial letter Z with caron
143	217	8F	10001111	 	 	 	 
144	220	90	10010000	 	 	 	 
145	221	91	10010001	‘	&#145;	&lsquo;	Left single quotation mark
146	222	92	10010010	’	&#146;	&rsquo;	Right single quotation mark
147	223	93	10010011	“	&#147;	&ldquo;	Left double quotation mark
148	224	94	10010100	”	&#148;	&rdquo;	Right double quotation mark
149	225	95	10010101	•	&#149;	&bull;	Bullet
150	226	96	10010110	–	&#150;	&ndash;	En dash
151	227	97	10010111	—	&#151;	&mdash;	Em dash
152	230	98	10011000	˜	&#152;	&tilde;	Small tilde
153	231	99	10011001	™	&#153;	&trade;	Trade mark sign
154	232	9A	10011010	š	&#154;	&scaron;	Latin small letter S with caron
155	233	9B	10011011	›	&#155;	&rsaquo;	Single right-pointing angle quotation mark
156	234	9C	10011100	œ	&#156;	&oelig;	Latin small ligature oe
157	235	9D	10011101	 	 	 	 
158	236	9E	10011110	ž	&#158;	 	Latin small letter z with caron
159	237	9F	10011111	Ÿ	&#159;	&yuml;	Latin capital letter Y with diaeresis
160	240	A0	10100000	 	&#160;	&nbsp;	Non-breaking space
161	241	A1	10100001	¡	&#161;	&iexcl;	Inverted exclamation mark
162	242	A2	10100010	¢	&#162;	&cent;	Cent sign
163	243	A3	10100011	£	&#163;	&pound;	Pound sign
164	244	A4	10100100	¤	&#164;	&curren;	Currency sign
165	245	A5	10100101	¥	&#165;	&yen;	Yen sign
166	246	A6	10100110	¦	&#166;	&brvbar;	Pipe, Broken vertical bar
167	247	A7	10100111	§	&#167;	&sect;	Section sign
168	250	A8	10101000	¨	&#168;	&uml;	Spacing diaeresis - umlaut
169	251	A9	10101001	©	&#169;	&copy;	Copyright sign
170	252	AA	10101010	ª	&#170;	&ordf;	Feminine ordinal indicator
171	253	AB	10101011	«	&#171;	&laquo;	Left double angle quotes
172	254	AC	10101100	¬	&#172;	&not;	Not sign
173	255	AD	10101101		&#173;	&shy;	Soft hyphen
174	256	AE	10101110	®	&#174;	&reg;	Registered trade mark sign
175	257	AF	10101111	¯	&#175;	&macr;	Spacing macron - overline
176	260	B0	10110000	°	&#176;	&deg;	Degree sign
177	261	B1	10110001	±	&#177;	&plusmn;	Plus-or-minus sign
178	262	B2	10110010	²	&#178;	&sup2;	Superscript two - squared
179	263	B3	10110011	³	&#179;	&sup3;	Superscript three - cubed
180	264	B4	10110100	´	&#180;	&acute;	Acute accent - spacing acute
181	265	B5	10110101	µ	&#181;	&micro;	Micro sign
182	266	B6	10110110	¶	&#182;	&para;	Pilcrow sign - paragraph sign
183	267	B7	10110111	·	&#183;	&middot;	Middle dot - Georgian comma
184	270	B8	10111000	¸	&#184;	&cedil;	Spacing cedilla
185	271	B9	10111001	¹	&#185;	&sup1;	Superscript one
186	272	BA	10111010	º	&#186;	&ordm;	Masculine ordinal indicator
187	273	BB	10111011	»	&#187;	&raquo;	Right double angle quotes
188	274	BC	10111100	¼	&#188;	&frac14;	Fraction one quarter
189	275	BD	10111101	½	&#189;	&frac12;	Fraction one half
190	276	BE	10111110	¾	&#190;	&frac34;	Fraction three quarters
191	277	BF	10111111	¿	&#191;	&iquest;	Inverted question mark
192	300	C0	11000000	À	&#192;	&Agrave;	Latin capital letter A with grave
193	301	C1	11000001	Á	&#193;	&Aacute;	Latin capital letter A with acute
194	302	C2	11000010	Â	&#194;	&Acirc;	Latin capital letter A with circumflex
195	303	C3	11000011	Ã	&#195;	&Atilde;	Latin capital letter A with tilde
196	304	C4	11000100	Ä	&#196;	&Auml;	Latin capital letter A with diaeresis
197	305	C5	11000101	Å	&#197;	&Aring;	Latin capital letter A with ring above
198	306	C6	11000110	Æ	&#198;	&AElig;	Latin capital letter AE
199	307	C7	11000111	Ç	&#199;	&Ccedil;	Latin capital letter C with cedilla
200	310	C8	11001000	È	&#200;	&Egrave;	Latin capital letter E with grave
201	311	C9	11001001	É	&#201;	&Eacute;	Latin capital letter E with acute
202	312	CA	11001010	Ê	&#202;	&Ecirc;	Latin capital letter E with circumflex
203	313	CB	11001011	Ë	&#203;	&Euml;	Latin capital letter E with diaeresis
204	314	CC	11001100	Ì	&#204;	&Igrave;	Latin capital letter I with grave
205	315	CD	11001101	Í	&#205;	&Iacute;	Latin capital letter I with acute
206	316	CE	11001110	Î	&#206;	&Icirc;	Latin capital letter I with circumflex
207	317	CF	11001111	Ï	&#207;	&Iuml;	Latin capital letter I with diaeresis
208	320	D0	11010000	Ð	&#208;	&ETH;	Latin capital letter ETH
209	321	D1	11010001	Ñ	&#209;	&Ntilde;	Latin capital letter N with tilde
210	322	D2	11010010	Ò	&#210;	&Ograve;	Latin capital letter O with grave
211	323	D3	11010011	Ó	&#211;	&Oacute;	Latin capital letter O with acute
212	324	D4	11010100	Ô	&#212;	&Ocirc;	Latin capital letter O with circumflex
213	325	D5	11010101	Õ	&#213;	&Otilde;	Latin capital letter O with tilde
214	326	D6	11010110	Ö	&#214;	&Ouml;	Latin capital letter O with diaeresis
215	327	D7	11010111	×	&#215;	&times;	Multiplication sign
216	330	D8	11011000	Ø	&#216;	&Oslash;	Latin capital letter O with slash
217	331	D9	11011001	Ù	&#217;	&Ugrave;	Latin capital letter U with grave
218	332	DA	11011010	Ú	&#218;	&Uacute;	Latin capital letter U with acute
219	333	DB	11011011	Û	&#219;	&Ucirc;	Latin capital letter U with circumflex
220	334	DC	11011100	Ü	&#220;	&Uuml;	Latin capital letter U with diaeresis
221	335	DD	11011101	Ý	&#221;	&Yacute;	Latin capital letter Y with acute
222	336	DE	11011110	Þ	&#222;	&THORN;	Latin capital letter THORN
223	337	DF	11011111	ß	&#223;	&szlig;	Latin small letter sharp s - ess-zed
224	340	E0	11100000	à	&#224;	&agrave;	Latin small letter a with grave
225	341	E1	11100001	á	&#225;	&aacute;	Latin small letter a with acute
226	342	E2	11100010	â	&#226;	&acirc;	Latin small letter a with circumflex
227	343	E3	11100011	ã	&#227;	&atilde;	Latin small letter a with tilde
228	344	E4	11100100	ä	&#228;	&auml;	Latin small letter a with diaeresis
229	345	E5	11100101	å	&#229;	&aring;	Latin small letter a with ring above
230	346	E6	11100110	æ	&#230;	&aelig;	Latin small letter ae
231	347	E7	11100111	ç	&#231;	&ccedil;	Latin small letter c with cedilla
232	350	E8	11101000	è	&#232;	&egrave;	Latin small letter e with grave
233	351	E9	11101001	é	&#233;	&eacute;	Latin small letter e with acute
234	352	EA	11101010	ê	&#234;	&ecirc;	Latin small letter e with circumflex
235	353	EB	11101011	ë	&#235;	&euml;	Latin small letter e with diaeresis
236	354	EC	11101100	ì	&#236;	&igrave;	Latin small letter i with grave
237	355	ED	11101101	í	&#237;	&iacute;	Latin small letter i with acute
238	356	EE	11101110	î	&#238;	&icirc;	Latin small letter i with circumflex
239	357	EF	11101111	ï	&#239;	&iuml;	Latin small letter i with diaeresis
240	360	F0	11110000	ð	&#240;	&eth;	Latin small letter eth
241	361	F1	11110001	ñ	&#241;	&ntilde;	Latin small letter n with tilde
242	362	F2	11110010	ò	&#242;	&ograve;	Latin small letter o with grave
243	363	F3	11110011	ó	&#243;	&oacute;	Latin small letter o with acute
244	364	F4	11110100	ô	&#244;	&ocirc;	Latin small letter o with circumflex
245	365	F5	11110101	õ	&#245;	&otilde;	Latin small letter o with tilde
246	366	F6	11110110	ö	&#246;	&ouml;	Latin small letter o with diaeresis
247	367	F7	11110111	÷	&#247;	&divide;	Division sign
248	370	F8	11111000	ø	&#248;	&oslash;	Latin small letter o with slash
249	371	F9	11111001	ù	&#249;	&ugrave;	Latin small letter u with grave
250	372	FA	11111010	ú	&#250;	&uacute;	Latin small letter u with acute
251	373	FB	11111011	û	&#251;	&ucirc;	Latin small letter u with circumflex
252	374	FC	11111100	ü	&#252;	&uuml;	Latin small letter u with diaeresis
253	375	FD	11111101	ý	&#253;	&yacute;	Latin small letter y with acute
254	376	FE	11111110	þ	&#254;	&thorn;	Latin small letter thorn
255	377	FF	11111111	ÿ	&#255;	&yuml;	Latin small letter y with diaeresis
*/
