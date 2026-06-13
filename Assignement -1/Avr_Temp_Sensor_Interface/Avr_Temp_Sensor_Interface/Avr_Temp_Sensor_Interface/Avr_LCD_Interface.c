/*
 * Avr_LCD_Interface.c
 *
 * Created: 04-Jun-26 7:26:39 PM
 *  Author: SHAHEEM
 */ 

#define F_CPU 16000000UL
#include "Avr_LCD_Interface.h"
void lcd_enable_pulse();
static void lcd_send_byte(uint8_t value, uint8_t rs);
//void send_nibble(uint8_t nib);

void lcd_init(void)
{
		// Make control and data pins outputs
		LCD_RS_DDR  |= (1<<LCD_RS_PIN);
     	LCD_EN_DDR  |= (1<<LCD_EN_PIN);
	    LCD_D_DDR   |= (1<<LCD_D7_PIN |1<<LCD_D6_PIN |1<<LCD_D5_PIN |1<<LCD_D4_PIN);
		_delay_ms(20);									// power-up wait.
		LCD_RS_PORT &= ~(1<<LCD_RS_PIN);  //Set RS pin as 0 initially
		LCD_EN_PORT &= ~(1<<LCD_EN_PIN); //Set EN pin as 0 initially (to latch EN=0 and EN=1 transition required)
		//After restart LCD wake up as 8 bit mode
		send_nibble(0x03); //Load only upper nibble of 0X30 only
		_delay_ms(5);
		send_nibble(0x03);
		_delay_ms(125);
		send_nibble(0x03);
		_delay_ms(125);
		//Switch to 4-bit
		send_nibble(0x02);//Load only upper nibble of 0X20 only
		_delay_us(150);
		//Function set: 4-bit, 2 lines, 5x8 font
		lcd_cmd(0x28);
		//Display off
		lcd_cmd(0x08);
		//Clear
		lcd_cmd(0x01);
		_delay_ms(5);
		//Entry mode: increment, no shift
		lcd_cmd(0x06);
		// Display on, cursor off, blink off
		lcd_cmd(0x0C);
}
void send_nibble(uint8_t nib)
{
	LCD_D_PORT &= ~((1<<LCD_D7_PIN)|(1<<LCD_D6_PIN)|(1<<LCD_D5_PIN)|(1<<LCD_D4_PIN)); //Set all pins value as 0 initially;
	if(nib & 0x08)
	{
		LCD_D_PORT |= (1<<LCD_D7_PIN);   //check select the D7 pin only if data is 00001000
	}
	if(nib & 0x04)
	{
		LCD_D_PORT |= (1<<LCD_D6_PIN);  //check select the D7 pin only if data is 00000100
	}
	if(nib & 0x02)
	{
		LCD_D_PORT |= (1<<LCD_D5_PIN); //check select the D7 pin only if data is 00000010
	}
	if(nib & 0x01)
	{
		LCD_D_PORT |= (1<<LCD_D4_PIN); //check select the D7 pin only if data is 000000001
	}
	lcd_enable_pulse();
}

static void lcd_send_byte(uint8_t value, uint8_t rs)  	  // here we receive data and rs value
{
	// checking if it is data or command based on the RS value and making it high and low accrodingly
	if (rs == 1)
	{
		LCD_RS_PORT |=  (1<<LCD_RS_PIN);  		 // It's a Data. SO RS pin =1
	}
	else
	{
		LCD_RS_PORT &= ~(1<<LCD_RS_PIN); 			 // it's a Command. So RS pin = 0
	}
	send_nibble(value >> 4);                   // sending upper nibble value
	send_nibble(value & 0x0F);                //  sending lower nibble value
}

void lcd_enable_pulse()
{
	LCD_EN_PORT |= (1<<LCD_EN_PIN);  // enable pin =1
	_delay_us(1);                                      // these delay values come from data sheet
	LCD_EN_PORT &= ~(1<<LCD_EN_PIN);  // enable pin =0
	_delay_us(50); 									   // allow LCD to latch
}

void lcd_set_cursor(uint8_t row, uint8_t col)				// receives row and column value 2X16 LCD
{
	uint8_t addr = (row ? 0x40 : 0x00) + (col & 0x0F);		// this is a ternary operator.
	lcd_cmd(0x80 | addr);                                   // send (80 + addr) as a command. if row=1 ,addr = 0x40+0x80 >0xc0 (row starts from 1).
}   
                                                        //   if row=0 ,addr = 0x00+0x80 >0x00 (row starts from 0).
														
void lcd_clear(void)
{
	lcd_cmd(0x01);  //LCD Display clear command
}

// this function allows us to return the cursor to home
void lcd_home(void)
{
	lcd_cmd(0x02); //LCD set cursor to home
}														
void lcd_cmd(uint8_t cmd)
{
	lcd_send_byte(cmd, 0); //rs = 0
	// Clear (0x01) and Return Home (0x02) need longer delays in write-only mode
	if (cmd == 0x01 || cmd == 0x02)//all other commands required only 37us.
	_delay_ms(2);
}
void lcd_print_string(const char *s)   //pointer based string printing operation
{
	while(*s)
	{
		lcd_data((uint8_t)*s++);   //Increase the base address
	}
}
void lcd_data(uint8_t data)
{
	lcd_send_byte(data, 1); //rs = 0
}
void lcd_print_uint16(uint16_t v)                        //        lcd_print_uint1(1432);
{
	if (v >= 10)
	{
		lcd_print_uint16(v / 10);  		                 // print higher digits first
	}
	lcd_data('0' + (v % 10));       					// then print the last digit
}

void lcd_print_float(float value)
{
	// Handle negative numbers
	if (value < 0)
	{
		lcd_data('-');
		value = -value;                        
	}
	
	// Integer part
	uint16_t int_part = (uint16_t)value;
	lcd_print_uint16(int_part);

	lcd_data('.');

	// Fractional part (2 digits)
	float frac = value - int_part;
	frac = frac * 100.f;       // scale to 1 decimal places
	uint16_t frac_part = (uint16_t)(frac + 0.5f);  // rounding

	// Handle leading zero after decimal (e.g., 3.05)
	if (frac_part < 10)
	lcd_data('0');

	lcd_print_uint16(frac_part);
}