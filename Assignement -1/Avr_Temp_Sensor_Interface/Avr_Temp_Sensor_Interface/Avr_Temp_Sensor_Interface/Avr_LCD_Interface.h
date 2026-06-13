/*
 * Avr_LCD_Interface.h
 *
 * Created: 04-Jun-26 7:13:42 PM
 *  Author: SHAHEEM
 */ 


#ifndef AVR_LCD_INTERFACE_H_
#define AVR_LCD_INTERFACE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// define some macros for the pins used
// for RS pin
#define LCD_RS_PORT PORTB
#define LCD_RS_DDR  DDRB
#define LCD_RS_PIN  PB4
// define some macros for the pins used
// for EN pin
#define LCD_EN_PORT   PORTB
#define LCD_EN_DDR    DDRB
#define LCD_EN_PIN    PB3
// Pins definition for data/commands
#define LCD_D_PORT    PORTD
#define LCD_D_DDR     DDRD
#define LCD_D7_PIN    PD2
#define LCD_D6_PIN    PD3
#define LCD_D5_PIN    PD4
#define LCD_D4_PIN    PD5
  
void lcd_init(void);  					              // for initialization sequence
void lcd_cmd(uint8_t cmd);				             // for commands(instructions
void lcd_data(uint8_t data);				             // for data
void lcd_set_cursor(uint8_t row,uint8_t col);           // for setting cursor(row: 0 or 1, col: 0..15)
void lcd_clear(void);					            // to clear_lcd
void lcd_home(void);					            // to return cursor to origin (row=0. Column =0)
void lcd_print_uint(uint16_t value);              // to print an integer value
void lcd_print_float(float value);               // to print an integer value
void lcd_print_string(const char *s);           // to print string

void lcd_print_uint16(uint16_t v);		// to print an integer value
void lcd_print_float(float value);     // to print an float value

#endif /* AVR_LCD_INTERFACE_H_ */