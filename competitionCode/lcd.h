#ifndef lcd_h
#define lcd_h
#include "Arduino.h"
#include "Print.h"
//4 Line x 20 Column display

class LCD03class : public Print
{
  public:
   LCD03class(){}
          
   void init()
          {
            _transmissionStatus = 255;
              //TODO write code to load generated character sets from flash(progmem) into LCD
             

          }
          
  void begin()
          {
            delay(600);
            clear();
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
		        uint8_t freeBytes;
			Wire.requestFrom(LCD03_ADDR, (uint8_t)1);                         // Request 1 byte 			 
                        while(Wire.available()) 
                        {
			freeBytes = Wire.receive();
                        }
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
			  
                        while(Wire.available()) 
                        {			
			keypad = Wire.receive();  // receive high byte 
                        }
			keypad = keypad << 8;    // shift high byte to be high 8 bits
								
			Wire.beginTransmission(LCD03_ADDR);                      // Send byte to read reg
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_KEYPAD_LOW_REG);			
			Wire.endTransmission();
		  
			Wire.requestFrom(LCD03_ADDR, (uint8_t)1);                         // Request LOW byte from LCD
			
                        while(Wire.available()) 
                        {			
			keypad |= Wire.receive(); // receive low byte as lower 8 bits
                        }
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
			while(Wire.available())
                        {
			    version = Wire.receive();  // receive high byte
                        }
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
                        if(position >=1 && position <= 80)
                        {
			Wire.beginTransmission(LCD03_ADDR);
			Wire.send(LCD03_CMD_REG);
			Wire.send(LCD03_SET_CURSOR_CMD);
			Wire.send(position);
			_transmissionStatus = Wire.endTransmission();
			DEBUG_PRINTLN("setCsr transmissionStatus");
                        DEBUG_I2C(_transmissionStatus);
                        }
			
		}
		//LCD03_SET_CURSOR_CMD = 2;	//Set cursor (1-80 or 32)	Cursor to a position specified by the next byte, where 1 is the top left and 80/32 is the bottom right
  
  void setCsrLC(uint8_t line, uint8_t column)
		{
                        if(line >= 1 && line <=4 && column >= 1 && column <= 20)
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
		
	void printToASCIIvalue(const char character)
		{
			if((int)character >= 32 && (int)character <= 255)//valid printable character
			{
				Wire.beginTransmission(LCD03_ADDR);
				Wire.send(LCD03_CMD_REG);
				Wire.send('character');
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
void printFromASCIIvalue(uint8_t characterValue)
{
    if(characterValue >= 32 && characterValue <= 255)//valid printable character
			{
				Wire.beginTransmission(LCD03_ADDR);
				Wire.send(LCD03_CMD_REG);
				Wire.send(characterValue);
				Wire.endTransmission();                              
				
			}
}

//Required virtual functions called by Print::print and Print::println         
        inline size_t write(unsigned char character)
                {
                  
                  Wire.beginTransmission(LCD03_ADDR);
		  Wire.send(LCD03_CMD_REG);
		  Wire.send(character);
		  Wire.endTransmission();
                  delay(1);
                  return 1; // assume sucess
                }
 // as called from C:\arduino_1\arduino-1.0\hardware\arduino\cores\arduino  Print::write
/* default implementation: may be overridden */
// size_t Print::write(const char *buffer, size_t size)

 // as called from C:\arduino_1\arduino-1.0\hardware\teensy\cores\teensy Print::write
// write((const uint8_t *)str, strlen(str)); 
//      size_t count = 0;
//	while (size--)
//        {
//          count += write(*buffer++);
//        }
//	return count;

        inline size_t write(const char *buffer, size_t size)
                {
                  uint8_t freeBytes = getBufferFreeBytes();  
                  if(size > freeBytes)
                  {
                      size_t count = 0;
                	while (size--)
                        {
                          count += write(*buffer++);
                        }
                	return count;
                
                      Wire.beginTransmission(LCD03_ADDR);
		      Wire.send(LCD03_CMD_REG);
                      for(uint8_t i = 0; i < freeBytes; i++)
                      {                         
    		          Wire.send(buffer[i]);
                      }
                      Wire.endTransmission();
                      return freeBytes;
                  }
		  else                  
                  {
                      Wire.beginTransmission(LCD03_ADDR);
    		      Wire.send(LCD03_CMD_REG);
                      for(uint8_t i = 0; i < size; i++)
                         {
    		             Wire.send(buffer[i]);
                         }                      
		      Wire.endTransmission();
                      return size; 
                }
                }
 private:
        uint8_t _transmissionStatus;
        void _printI2Cstatus()
		{
			switch (_transmissionStatus) 
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
			  Serial.println("255 initialized but unchanged transmissionStatus");
			  break;  
			default: 
			  // if nothing else matches
			  Serial.print(_transmissionStatus);
			  Serial.println(" unrecognized value ");
			}
		}
	
        
          
};//LCD03class end

LCD03class lcd = LCD03class();

// functions that use the LCD

void displayADC()
{
    lcd.clear();
    static uint16_t min = 1023;
    static uint16_t max = 0;
   // pinMode(VOLT_SIGNAL_ADC_PIN, OUTPUT);
   // digitalWrite(VOLT_SIGNAL_ADC_PIN, LOW);
    //delay(1);// discharge peak hold cap
    pinMode(VOLT_SIGNAL_ADC_PIN, INPUT);
    //delay(5);// give time for peak hold cap to charge to current voltage
    uint16_t taskVoltage = analogRead(VOLT_SIGNAL_ADC_PIN);
    if(taskVoltage > max)
    {max = taskVoltage;}
    if(taskVoltage < min)
    {min = taskVoltage;}
    lcd.setCsrLC(3, 6);
    lcd.print("ADC: ");
    lcd.print(taskVoltage, DEC);
    lcd.setCsrLC(4, 1);
    lcd.print("min: ");
    lcd.print(min, DEC);
    lcd.setCsrLC(4, 11);
    lcd.print("max: ");
    lcd.print(max, DEC);
    delay(250);
}

void testLCD1()
{
    lcd.clear();
        uint8_t j = 1;
        for(uint8_t i = 32; i <= 255; i++)
        {
            delay(1);
            lcd.setCsr(j);
            j++;
            if(j == 81)
                j = 1;
            if(i == 255)
                i = 32;
            delay(1);
            lcd.printFromASCIIvalue(i);
        }
    
}

void testLCD2()
{
        lcd.clear();
        lcd.homeCsr();
        int i;
        //row 1
        for(i = 1; i <=20; i++)
        {
            lcd.setCsr(i);
            lcd.write(1);
        }
        //row 2        
        for(i = 21; i <=40; i++)
        {
            lcd.setCsr(i);
            lcd.write(2);
        }
        //row 3        
        for(i = 31; i <=60; i++)
        {
            lcd.setCsr(i);
            lcd.write(3);
        }
        //row 4        
        for(i = 41; i <=80; i++)
        {
            lcd.setCsr(i);
            lcd.write(4);
        }
        
}


void  displayTask()
{//  Next task, Last task measurement, Last task direction, color, side of course
  lcd.clear();
  lcd.setCsrLC(1, 1);//lcd.setCsrLC(0, 8);                     //move cursor to first line 
  lcd.print("Next Task: "); 
  
}



void  displayTemperatures()
{// ambient temp, temp Array
    lcd.clear();
    lcd.print("Ambient: ");
    lcd.print(getAmbient(), DEC);
    lcd.print(" T1: ");
    lcd.println(getTemperaturePixel(1), DEC);
    lcd.print("T2: ");
    lcd.print(getTemperaturePixel(2), DEC);
    lcd.print(" T3: ");
    lcd.print(getTemperaturePixel(3), DEC);
    lcd.println(" T4: ");
    lcd.print(getTemperaturePixel(4), DEC);
    lcd.print("T5: ");
    lcd.print(getTemperaturePixel(5), DEC);
    lcd.print(" T6:");
    lcd.print(getTemperaturePixel(6), DEC);
    lcd.print(" T7:");
    lcd.print(getTemperaturePixel(7), DEC);
    lcd.print(" T8:");
    lcd.print(getTemperaturePixel(8), DEC);
}

void displayWheelSpeeds()
{
  lcd.clear();
  lcd.setCsrLC(1, 1);//lcd.setCsrLC(0, 8);                     //move cursor to first line 
  lcd.print("LF Speed: "); 
  lcd.print(wheelSpeed[LF], DEC);                       
  lcd.setCsrLC(2, 1);// lcd.setCsrLC(1, 0);                  //move cursor to second line 
  lcd.print("RF Speed: ");
  lcd.print(wheelSpeed[RF], DEC);                       
  lcd.setCsrLC(3, 1);// lcd.setCsrLC(1, 16);                //move cursor to second line
  lcd.print("LR Speed: "); 
  lcd.print(wheelSpeed[LR], DEC);                       
  lcd.setCsrLC(4, 1);//lcd.setCsrLC(2, 8);                  //move cursor to third line 
  lcd.print("RR Speed: ");
  lcd.print(wheelSpeed[RR], DEC);
}

void displayWheelEncoders()
{
  lcd.clear();
  lcd.setCsrLC(1, 1);//lcd.setCsrLC(0, 8);                     //move cursor to first line 
  lcd.print("LF count:"); 
  lcd.print(getEncoderCount(LF), DEC);                       
  lcd.setCsrLC(2, 1);// lcd.setCsrLC(1, 0);                  //move cursor to second line 
  lcd.print("RF count:");
  lcd.print(getEncoderCount(RF), DEC);                       
  lcd.setCsrLC(3, 1);// lcd.setCsrLC(1, 16);                //move cursor to second line
  lcd.print("LR count:"); 
  lcd.print(getEncoderCount(LR), DEC);                       
  lcd.setCsrLC(4, 1);//lcd.setCsrLC(2, 8);                  //move cursor to third line 
  lcd.print("RR count:");
  lcd.print(getEncoderCount(RR), DEC);                        

}

void displaySonars()
{
    delay(50);
  lcd.clear();
  lcd.setCsrLC(1, 8);
  lcd.print("Sonar");
  lcd.setCsrLC(2, 8);//lcd.setCsrLC(0, 8);                         //move cursor to first line, 8th column  
  lcd.print(getDistanceToFrontObject(), DEC);                       // distance to front object in number of wheel degrees
  delay(50);
  lcd.setCsrLC(3, 1);// lcd.setCsrLC(1, 0);                                        //move cursor to second line, 1st column  
  lcd.print(getDistanceToLeftObject(), DEC);                       // distance to left object in number of wheel degrees
  delay(50);
  lcd.setCsrLC(3, 16);// lcd.setCsrLC(1, 16);                                        //move cursor to second line, 16th column  
  lcd.print(getDistanceToRightObject(), DEC);                       // distance to right object in number of wheel degrees
  delay(50);
  lcd.setCsrLC(4, 8);//lcd.setCsrLC(2, 8);                                        //move cursor to third line, 8th column  
  lcd.print(getDistanceToRearObject(), DEC);                       // distance to rear object in number of wheel degrees 
  
  
}

void displayWheelCurrents()
{
  lcd.clear();
  lcd.setCsrLC(1, 1);//lcd.setCsrLC(0, 8);                     //move cursor to first line 
  lcd.print("LF current: "); 
  lcd.print(getWheelCurrent(LF), DEC);                       
  lcd.setCsrLC(2, 1);// lcd.setCsrLC(1, 0);                  //move cursor to second line 
  lcd.print("RF current: ");
  lcd.print(getWheelCurrent(RF), DEC);                       
  lcd.setCsrLC(3, 1);// lcd.setCsrLC(1, 16);                //move cursor to second line
  lcd.print("LR current: "); 
  lcd.print(getWheelCurrent(LR), DEC);                       
  lcd.setCsrLC(4, 1);//lcd.setCsrLC(2, 8);                  //move cursor to third line 
  lcd.print("RR current: ");
  lcd.print(getWheelCurrent(RR), DEC);                        

}

void displayVolts()
{
    lcd.clear();
  uint8_t batteryVolts = getVolts(FRONT_MD25_ADDR);      //get the voltage reading of the front motor controller
  lcd.setCsrLC(1, 1);   // lcd.setCsrLC(0, 0);                                        //move cursor to first line, first column
  lcd.print("Batt Volts: ");
  lcd.print(batteryVolts/10, DEC);                       // Print batery volts / 10 to give you the number of whole volts
  lcd.print(".");                                        // As arduino has truncates floating point numbers we print a . here to act as a decimal point
  lcd.print(batteryVolts%10, DEC);                       // Prints Battery volts % 10 to give us the 
}

void displayCompass()
{
    delay(250);
    lcd.clear();
  uint8_t bam = getBearing();      
  lcd.setCsrLC(2, 1);                                          
  lcd.print("Heading: ");
  lcd.print(bam, DEC); 
/*  
  lcd.print(".");                                        
  lcd.print(degrees%10, DEC);
  
  degrees = getBearing();
  lcd.setCsrLC(3, 1);
  lcd.print(degrees, DEC); 
  */
  if(bam > NORTHEAST_HEADING && bam < NORTHWEST_HEADING)
  {// north
      lcd.setCsrLC(3, 1);
      lcd.print("North");
  }
  else if(bam > SOUTHWEST_HEADING && bam < SOUTHEAST_HEADING)
  {// south
      lcd.setCsrLC(3, 1);
      lcd.print("South");
  }
  else if(bam <= SOUTHWEST_HEADING && bam >= NORTHWEST_HEADING)
  {// west
      lcd.setCsrLC(3, 1);
      lcd.print("West");
  }
  else 
  {// east
      lcd.setCsrLC(3, 1);
      lcd.print("East");
  }
  
}

void LCDdisplay()
{   
    
    
      if (sinceDisplayCompass >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 1 screen
      {// battery volts, compass direction
        sinceDisplayCompass = sinceDisplayCompass - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayVolts();
        displayCompass();
      }
      if (sinceDisplayWheelSpeeds >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 2 screens
      {
        sinceDisplayWheelSpeeds = sinceDisplayWheelSpeeds - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayWheelSpeeds();
      }
      if (sinceDisplayWheelCurrents >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 3 screens
      {
        sinceDisplayWheelCurrents = sinceDisplayWheelCurrents - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayWheelCurrents();
      }
      if (sinceDisplaySonars >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 4 screens
      {
        sinceDisplaySonars = sinceDisplaySonars - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displaySonars();
      }      
      if (sinceDisplayWheelEncoders >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 5 screens
      {
        sinceDisplayWheelEncoders = sinceDisplayWheelEncoders - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayWheelEncoders();
      }
      if (sinceDisplayTemperatures >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 6 screens
      {
        sinceDisplayTemperatures = sinceDisplayTemperatures - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayTemperatures();
      }     
      if (sinceDisplayTask >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 7 screens
      {
        sinceDisplayTask = sinceDisplayTask - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayTask();
      }      
}


/*
void  displayTask()
{//  current task, current task measurement, current task decision, color, side of course
    

}



void  displayTemperatures()
{// ambient temp, temp Array

}

void displayWheelSpeeds()
{
  lcd.setCsrLC(0, 0);//lcd.setCsrLC(0, 8);                     //move cursor to first line 
  lcd.print("LF Speed: "); 
  lcd.print(wheelSpeed[LF], DEC);                       
  lcd.setCsrLC(1, 0);// lcd.setCsrLC(1, 0);                  //move cursor to second line 
  lcd.print("RF Speed: ");
  lcd.print(wheelSpeed[RF], DEC);                       
  lcd.setCsrLC(2, 0);// lcd.setCsrLC(1, 16);                //move cursor to second line
  lcd.print("LR Speed: "); 
  lcd.print(wheelSpeed[LR], DEC);                       
  lcd.setCsrLC(3, 0);//lcd.setCsrLC(2, 8);                  //move cursor to third line 
  lcd.print("RR Speed: ");
  lcd.print(wheelSpeed[RR], DEC);
}

void displayWheelEncoders()
{
  lcd.setCsrLC(0, 0);//lcd.setCsrLC(0, 8);                     //move cursor to first line 
  lcd.print("LF: "); 
  lcd.print(getEncoderCount(LF), DEC);                       
  lcd.setCsrLC(1, 0);// lcd.setCsrLC(1, 0);                  //move cursor to second line 
  lcd.print("RF: ");
  lcd.print(getEncoderCount(RF), DEC);                       
  lcd.setCsrLC(2, 0);// lcd.setCsrLC(1, 16);                //move cursor to second line
  lcd.print("LR:"); 
  lcd.print(getEncoderCount(LR), DEC);                       
  lcd.setCsrLC(3, 0);//lcd.setCsrLC(2, 8);                  //move cursor to third line 
  lcd.print("RR:");
  lcd.print(getEncoderCount(RR), DEC);                        

}

void displaySonars()
{
  lcd.setCsrLC(0, 8);
  lcd.print("Sonar");
  lcd.setCsrLC(1, 8);//lcd.setCsrLC(0, 8);                         //move cursor to first line, 8th column  
  lcd.print(getDistanceToFrontObject(), DEC);                       // distance to front object in number of wheel degrees
  lcd.setCsrLC(2, 0);// lcd.setCsrLC(1, 0);                                        //move cursor to second line, 1st column  
  lcd.print(getDistanceToLeftObject(), DEC);                       // distance to left object in number of wheel degrees
  lcd.setCsrLC(2, 16);// lcd.setCsrLC(1, 16);                                        //move cursor to second line, 16th column  
  lcd.print(getDistanceToRightObject(), DEC);                       // distance to right object in number of wheel degrees
  lcd.setCsrLC(3, 8);//lcd.setCsrLC(2, 8);                                        //move cursor to third line, 8th column  
  lcd.print(getDistanceToRearObject(), DEC);                       // distance to rear object in number of wheel degrees  
}

void displayWheelCurrents()
{
    uint8_t LFcurrent = getWheelCurrent(LF);
    uint8_t RFcurrent = getWheelCurrent(RF);
    uint8_t LRcurrent = getWheelCurrent(LR);
    uint8_t RRcurrent = getWheelCurrent(RR);
    
  lcd.setCsrLC(0, 0);                   //move cursor to first line 
  lcd.print("LF current: "); 
  lcd.print(LFcurrent, DEC);                       
  lcd.setCsrLC(1, 0);                 //move cursor to second line 
  lcd.print("RF current: ");
  lcd.print(RFcurrent, DEC);                       
  lcd.setCsrLC(2, 0);                //move cursor to second line
  lcd.print("LR current: "); 
  lcd.print(LRcurrent, DEC);                       
  lcd.setCsrLC(3, 0);                  //move cursor to third line 
  lcd.print("RR current: ");
  lcd.print(RRcurrent, DEC);                        

}

void displayVolts()
{
  uint8_t batteryVolts = getVolts(FRONT_MD25_ADDR);      //get the voltage reading of the front motor controller
  lcd.setCsrLC(0, 0);   // lcd.setCsrLC(0, 0);                                        //move cursor to first line, first column
  lcd.print("Batt Volts: ");
  lcd.print(batteryVolts/10, DEC);                       // Print batery volts / 10 to give you the number of whole volts
  lcd.print(".");                                        // As arduino has truncates floating point numbers we print a . here to act as a decimal point
  lcd.print(batteryVolts%10, DEC);                       // Prints Battery volts % 10 to give us the 
}

void displayCompass()
{
  uint16_t degrees = getBearingDegrees();      
  lcd.setCsrLC(1, 0);   // lcd.setCsrLC(0, 0);                                        
  lcd.print("Heading; ");
  lcd.print(degrees/10, DEC);                       
  lcd.print(".");                                        
  lcd.print(degrees%10, DEC);                       
  degrees = getBearing();
  if(degrees > NORTHEAST_HEADING && degrees < NORTHWEST_HEADING)
  {// north
      lcd.setCsrLC(2, 0);
      lcd.print("North");
  }
  else if(degrees > SOUTHWEST_HEADING && degrees < SOUTHEAST_HEADING)
  {// south
      lcd.setCsrLC(2, 0);
      lcd.print("South");
  }
  else if(degrees <= SOUTHWEST_HEADING && degrees >= NORTHWEST_HEADING)
  {// west
      lcd.setCsrLC(2, 0);
      lcd.print("West");
  }
  else 
  {// east
      lcd.setCsrLC(2, 0);
      lcd.print("East");
  }
  
}

void LCDdisplay()
{   
    
    
      if (sinceDisplayCompass >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 1 screen
      {// battery volts, compass direction
        sinceDisplayCompass = sinceDisplayCompass - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayVolts();
        displayCompass();
      }
      if (sinceDisplayWheelSpeeds >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 2 screens
      {
        sinceDisplayWheelSpeeds = sinceDisplayWheelSpeeds - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayWheelSpeeds();
      }
      if (sinceDisplayWheelCurrents >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 3 screens
      {
        sinceDisplayWheelCurrents = sinceDisplayWheelCurrents - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayWheelCurrents();
      }
      if (sinceDisplaySonars >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 4 screens
      {
        sinceDisplaySonars = sinceDisplaySonars - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displaySonars();
      }      
      if (sinceDisplayWheelEncoders >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 5 screens
      {
        sinceDisplayWheelEncoders = sinceDisplayWheelEncoders - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayWheelEncoders();
      }
      if (sinceDisplayTemperatures >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 6 screens
      {
        sinceDisplayTemperatures = sinceDisplayTemperatures - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayTemperatures();
      }     
      if (sinceDisplayTask >= (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS)) // 7 screens
      {
        sinceDisplayTask = sinceDisplayTask - (DISPLAY_INTERVAL * NUM_DISPLAY_SCREENS);
        displayTask();
      }      
}


    
*/

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
128	200	80	10000000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#128;	&euro;	Euro sign
129	201	81	10000001	 	 	 	 
130	202	82	10000010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#130;	&sbquo;	Single low-9 quotation mark
131	203	83	10000011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#131;	&fnof;	Latin small letter f with hook
132	204	84	10000100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#132;	&bdquo;	Double low-9 quotation mark
133	205	85	10000101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#133;	&hellip;	Horizontal ellipsis
134	206	86	10000110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#134;	&dagger;	Dagger
135	207	87	10000111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#135;	&Dagger;	Double dagger
136	210	88	10001000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#136;	&circ;	Modifier letter circumflex accent
137	211	89	10001001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#137;	&permil;	Per mille sign
138	212	8A	10001010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#138;	&Scaron;	Latin capital letter S with caron
139	213	8B	10001011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#139;	&lsaquo;	Single left-pointing angle quotation
140	214	8C	10001100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#140;	&OElig;	Latin capital ligature OE
141	215	8D	10001101	 	 	 	 
142	216	8E	10001110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#142;	 	Latin captial letter Z with caron
143	217	8F	10001111	 	 	 	 
144	220	90	10010000	 	 	 	 
145	221	91	10010001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#145;	&lsquo;	Left single quotation mark
146	222	92	10010010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#146;	&rsquo;	Right single quotation mark
147	223	93	10010011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#147;	&ldquo;	Left double quotation mark
148	224	94	10010100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#148;	&rdquo;	Right double quotation mark
149	225	95	10010101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#149;	&bull;	Bullet
150	226	96	10010110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#150;	&ndash;	En dash
151	227	97	10010111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#151;	&mdash;	Em dash
152	230	98	10011000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#152;	&tilde;	Small tilde
153	231	99	10011001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#153;	&trade;	Trade mark sign
154	232	9A	10011010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#154;	&scaron;	Latin small letter S with caron
155	233	9B	10011011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#155;	&rsaquo;	Single right-pointing angle quotation mark
156	234	9C	10011100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#156;	&oelig;	Latin small ligature oe
157	235	9D	10011101	 	 	 	 
158	236	9E	10011110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#158;	 	Latin small letter z with caron
159	237	9F	10011111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#159;	&yuml;	Latin capital letter Y with diaeresis
160	240	A0	10100000	 	&#160;	&nbsp;	Non-breaking space
161	241	A1	10100001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#161;	&iexcl;	Inverted exclamation mark
162	242	A2	10100010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#162;	&cent;	Cent sign
163	243	A3	10100011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#163;	&pound;	Pound sign
164	244	A4	10100100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#164;	&curren;	Currency sign
165	245	A5	10100101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#165;	&yen;	Yen sign
166	246	A6	10100110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#166;	&brvbar;	Pipe, Broken vertical bar
167	247	A7	10100111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#167;	&sect;	Section sign
168	250	A8	10101000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#168;	&uml;	Spacing diaeresis - umlaut
169	251	A9	10101001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#169;	&copy;	Copyright sign
170	252	AA	10101010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#170;	&ordf;	Feminine ordinal indicator
171	253	AB	10101011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#171;	&laquo;	Left double angle quotes
172	254	AC	10101100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#172;	&not;	Not sign
173	255	AD	10101101		&#173;	&shy;	Soft hyphen
174	256	AE	10101110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#174;	&reg;	Registered trade mark sign
175	257	AF	10101111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#175;	&macr;	Spacing macron - overline
176	260	B0	10110000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#176;	&deg;	Degree sign
177	261	B1	10110001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#177;	&plusmn;	Plus-or-minus sign
178	262	B2	10110010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#178;	&sup2;	Superscript two - squared
179	263	B3	10110011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#179;	&sup3;	Superscript three - cubed
180	264	B4	10110100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#180;	&acute;	Acute accent - spacing acute
181	265	B5	10110101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#181;	&micro;	Micro sign
182	266	B6	10110110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#182;	&para;	Pilcrow sign - paragraph sign
183	267	B7	10110111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#183;	&middot;	Middle dot - Georgian comma
184	270	B8	10111000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#184;	&cedil;	Spacing cedilla
185	271	B9	10111001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#185;	&sup1;	Superscript one
186	272	BA	10111010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#186;	&ordm;	Masculine ordinal indicator
187	273	BB	10111011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#187;	&raquo;	Right double angle quotes
188	274	BC	10111100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#188;	&frac14;	Fraction one quarter
189	275	BD	10111101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#189;	&frac12;	Fraction one half
190	276	BE	10111110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#190;	&frac34;	Fraction three quarters
191	277	BF	10111111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#191;	&iquest;	Inverted question mark
192	300	C0	11000000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#192;	&Agrave;	Latin capital letter A with grave
193	301	C1	11000001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#193;	&Aacute;	Latin capital letter A with acute
194	302	C2	11000010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#194;	&Acirc;	Latin capital letter A with circumflex
195	303	C3	11000011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#195;	&Atilde;	Latin capital letter A with tilde
196	304	C4	11000100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#196;	&Auml;	Latin capital letter A with diaeresis
197	305	C5	11000101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#197;	&Aring;	Latin capital letter A with ring above
198	306	C6	11000110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#198;	&AElig;	Latin capital letter AE
199	307	C7	11000111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#199;	&Ccedil;	Latin capital letter C with cedilla
200	310	C8	11001000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#200;	&Egrave;	Latin capital letter E with grave
201	311	C9	11001001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#201;	&Eacute;	Latin capital letter E with acute
202	312	CA	11001010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#202;	&Ecirc;	Latin capital letter E with circumflex
203	313	CB	11001011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#203;	&Euml;	Latin capital letter E with diaeresis
204	314	CC	11001100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#204;	&Igrave;	Latin capital letter I with grave
205	315	CD	11001101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#205;	&Iacute;	Latin capital letter I with acute
206	316	CE	11001110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#206;	&Icirc;	Latin capital letter I with circumflex
207	317	CF	11001111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#207;	&Iuml;	Latin capital letter I with diaeresis
208	320	D0	11010000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#208;	&ETH;	Latin capital letter ETH
209	321	D1	11010001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#209;	&Ntilde;	Latin capital letter N with tilde
210	322	D2	11010010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#210;	&Ograve;	Latin capital letter O with grave
211	323	D3	11010011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#211;	&Oacute;	Latin capital letter O with acute
212	324	D4	11010100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#212;	&Ocirc;	Latin capital letter O with circumflex
213	325	D5	11010101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#213;	&Otilde;	Latin capital letter O with tilde
214	326	D6	11010110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#214;	&Ouml;	Latin capital letter O with diaeresis
215	327	D7	11010111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#215;	&times;	Multiplication sign
216	330	D8	11011000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#216;	&Oslash;	Latin capital letter O with slash
217	331	D9	11011001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#217;	&Ugrave;	Latin capital letter U with grave
218	332	DA	11011010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#218;	&Uacute;	Latin capital letter U with acute
219	333	DB	11011011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#219;	&Ucirc;	Latin capital letter U with circumflex
220	334	DC	11011100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#220;	&Uuml;	Latin capital letter U with diaeresis
221	335	DD	11011101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#221;	&Yacute;	Latin capital letter Y with acute
222	336	DE	11011110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#222;	&THORN;	Latin capital letter THORN
223	337	DF	11011111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#223;	&szlig;	Latin small letter sharp s - ess-zed
224	340	E0	11100000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#224;	&agrave;	Latin small letter a with grave
225	341	E1	11100001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#225;	&aacute;	Latin small letter a with acute
226	342	E2	11100010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#226;	&acirc;	Latin small letter a with circumflex
227	343	E3	11100011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#227;	&atilde;	Latin small letter a with tilde
228	344	E4	11100100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#228;	&auml;	Latin small letter a with diaeresis
229	345	E5	11100101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#229;	&aring;	Latin small letter a with ring above
230	346	E6	11100110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#230;	&aelig;	Latin small letter ae
231	347	E7	11100111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#231;	&ccedil;	Latin small letter c with cedilla
232	350	E8	11101000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#232;	&egrave;	Latin small letter e with grave
233	351	E9	11101001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#233;	&eacute;	Latin small letter e with acute
234	352	EA	11101010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#234;	&ecirc;	Latin small letter e with circumflex
235	353	EB	11101011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#235;	&euml;	Latin small letter e with diaeresis
236	354	EC	11101100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#236;	&igrave;	Latin small letter i with grave
237	355	ED	11101101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#237;	&iacute;	Latin small letter i with acute
238	356	EE	11101110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#238;	&icirc;	Latin small letter i with circumflex
239	357	EF	11101111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#239;	&iuml;	Latin small letter i with diaeresis
240	360	F0	11110000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#240;	&eth;	Latin small letter eth
241	361	F1	11110001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#241;	&ntilde;	Latin small letter n with tilde
242	362	F2	11110010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#242;	&ograve;	Latin small letter o with grave
243	363	F3	11110011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#243;	&oacute;	Latin small letter o with acute
244	364	F4	11110100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#244;	&ocirc;	Latin small letter o with circumflex
245	365	F5	11110101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#245;	&otilde;	Latin small letter o with tilde
246	366	F6	11110110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#246;	&ouml;	Latin small letter o with diaeresis
247	367	F7	11110111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#247;	&divide;	Division sign
248	370	F8	11111000	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#248;	&oslash;	Latin small letter o with slash
249	371	F9	11111001	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#249;	&ugrave;	Latin small letter u with grave
250	372	FA	11111010	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#250;	&uacute;	Latin small letter u with acute
251	373	FB	11111011	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#251;	&ucirc;	Latin small letter u with circumflex
252	374	FC	11111100	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#252;	&uuml;	Latin small letter u with diaeresis
253	375	FD	11111101	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#253;	&yacute;	Latin small letter y with acute
254	376	FE	11111110	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#254;	&thorn;	Latin small letter thorn
255	377	FF	11111111	ÃƒÂ¯Ã‚Â¿Ã‚Â½	&#255;	&yuml;	Latin small letter y with diaeresis
*/



