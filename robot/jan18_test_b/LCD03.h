// LCD03.H
// This library works with LCD03
#ifndef LCD03_H
#define LCD03_H

#define _LCDEXPANDED				// If defined turn on advanced functions
#include "Print.h"

class LCD03 : public Print 
{

public: 

  LCD03(uint8_t num_lines, uint8_t num_col, uint8_t i2c_address, uint8_t display);
  
  void command(uint8_t value);

  void init();

  void setDelay(int,int);

  virtual void write(uint8_t);

  void clear();
  
  void home();
  
  void on();
  
  void off();
  
  void cursor_on();
  
  void cursor_off();
  
  void blink_on();
  
  void blink_off();
	
  void setCursor(uint8_t Line, uint8_t Col );
	
  void backlight(uint8_t value);
	
	
	// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
	// []
	// []	Extended Functions
	// []
	// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
	
	
	
#ifdef _LCDEXPANDED		
	
	
	

	
	int status();
	
	uint8_t keypad();
	
	void load_custom_character(uint8_t char_num, uint8_t *rows);
	
	
#define LCD03_MIN_BRIGHTNESS		0
#define LCD03_MAX_BRIGHTNESS		250
#define LCD03_VALUE_OUT_OF_RANGE	1
#define LCD03_MIN_CONTRAST			0
#define LCD03_MAX_CONTRAST			100
  
  //void left();
  
  //void right();
  
  //uint8_t keypad();
 
  	// Overload the Print class function for strings because
	// the base class implementation causes problems by doing
	// an I2C I/O for every character
  //void printstr(const char[]);
	

/*
 
// Values for graphtype in calls to init_bargraph
#define LCD03_VERTICAL_BAR_GRAPH    1
#define LCD03_HORIZONTAL_BAR_GRAPH  2
#define LCD03_HORIZONTAL_LINE_GRAPH 3

  unsigned char init_bargraph(unsigned char graphtype);
  void draw_horizontal_graph(unsigned char row, unsigned char column, unsigned char len,  unsigned char pixel_col_end);
  void draw_vertical_graph(unsigned char row, unsigned char column, unsigned char len,  unsigned char pixel_col_end);

#define LCD03_NUM_CUSTOM_CHARS 8
#define LCD03_CUSTOM_CHAR_SIZE 8
  void load_custom_character(unsigned char char_num, unsigned char *rows);
  unsigned char set_backlight_brightness(unsigned char new_val);
  unsigned char set_contrast(unsigned char new_val);
  
*/
	
#endif

private:
	

};

#endif









/*

#ifndef LCD03_H
#define LCD03_H

#include <Arduino.h>

class LCD03Class
{
  public:
        uint8_t getAddress();
	uint16_t getBufferFreeBytes();//  LCD03_BUFFER_REMAINING_REG = 0;	//Number of free bytes in FIFO buffer
        uint16_t getKeypadState(); //LCD03_KEYPAD_LOW_REG = 1;	//Keypad state Low byte	
                                   //LCD03_KEYPAD_HIGH_REG = 2;	//Keypad state High byte
        uint8_t getVersion(); //LCD03_VERSION_REG = 3;	//Version
//LCD03 WRITE ONLY register
// LCD03_cmd_REG = 0; //Command register
    //Commands
        void noop();// static const uint8_t LCD03_NULL_CMD = 0;	//null (ignored)	Ignored as a no operation
        void homeCsr(); //LCD03_CURSOR_HOME_CMD = 1;	//Cursor Home	 Sets the cursor to the home position (top left)
        void setCsr(); //LCD03_SET_CURSOR_CMD = 2;	//Set cursor (1-80 or 32)	Cursor to a position specified by the next byte, where 1 is the top left and 80/32 is the bottom right
        void setCsrLC();// LCD03_SET_CURSOR_LC_CMD = 3;	//set cursor (line, column)	Sets cursor using two bytes, where first byte is the line and the second byte is the column
        void hideCSR();// LCD03_HIDE_CURSOR_CMD = 4;	//Hide cursor	stops the position cursor from appearing on the display 
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
 private:

};

extern LCD03Class LCD03;  // make an instance for the user

#endif 
*/


