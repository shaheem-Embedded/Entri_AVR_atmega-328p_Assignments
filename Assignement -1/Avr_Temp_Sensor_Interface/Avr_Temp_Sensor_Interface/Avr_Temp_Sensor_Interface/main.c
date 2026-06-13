/*
 * Avr_Temp_Sensor_Interface.c
 *
 * Created: 07-Jun-26 5:03:39 PM
 * Author : SHAHEEM
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include<stdint.h>
#include<util/delay.h>

#include "AVT_TEMP_SENSROR_INTERFACE.h"
#include "Avr_LCD_Interface.h"
#include "uart.h"
#include "timer1.h"


int main(void)
{ 
	uint8_t temp_flag = 0;
	float temperature;
	char buffer[20];
	//a=25.45;
	uint16_t adc_data;
	timer_1_enable();
	LED_port_enable();
	lcd_init();    // initialize the LCD always first
	ADC_init();     // initialize the ADC
	uart_init();    // initialize the UART transmission
	//char data = 'H';

    /* Replace with your application code */
    while (1)
    { 
		
		adc_data = ADC_read();                  //Get value of ADC_read function
		temperature = (adc_data * 0.488); //Temperature calculation
		
		//transmit_string(data);
		// UART transmit to PC
		//sprintf(buffer, "Atmos.Temp: %.2f C\r\n", temperature);
		uint16_t temp_whole = (uint16_t)temperature;//Taking the Integer portion
		uint16_t temp_frac = (uint16_t)((temperature - temp_whole) * 100);//Taking the fraction portion
		sprintf(buffer, "Atmos.Temp: %d.%02d C\r\n", temp_whole, temp_frac);
		transmit_string(buffer);
		_delay_ms(300);
		if(temperature>50)
		{   
			temp_flag=1;                                //set flag for condition to meet and avoid unnecessary LCD display.
			lcd_set_cursor(0, 0);
			lcd_print_string("Alarming Temp!!       ");
			lcd_set_cursor(1, 0);                      //Set Cursor to line 1 ,Column 0
			lcd_print_float(temperature);                //Print data in temperature variable
			lcd_data(0xDF);                              //Print degree
			lcd_print_string("C");                       //Print "C"
			lcd_print_string(" Red.Temp");
			PORTB ^= (1<<PORTB1);
	    	_delay_ms(500);
    }
	else if(temp_flag==1 && temperature>40 && temperature<50)//Check the condition
	{
		lcd_set_cursor(0, 0);
		lcd_print_string("Temp Redcng..      ");
		lcd_set_cursor(1, 0);                      //Set Cursor to line 1 ,Column 0
		lcd_print_float(temperature);                //Print data in temperature variable
		lcd_data(0xDF);                              //Print degree
		lcd_print_string("C          ");                       //Print "C"
		_delay_ms(300);                              //small delay after Displaying the current temperature value.
	}
	else if(temp_flag==1 && temperature>30 && temperature<40) //Check the condition
	{
		lcd_set_cursor(0, 0);
		lcd_print_string("Normal Temp.           ");  
		PORTB &= ~(1<<PORTB1);
		lcd_set_cursor(1, 0);                      //Set Cursor to line 1 ,Column 0
		lcd_print_float(temperature);                //Print data in temperature variable
		lcd_data(0xDF);                              //Print degree
		lcd_print_string("C              ");         //Print "C"
		_delay_ms(300);                              //small delay after Displaying the current temperature value.
        temp_flag=0;                                 //Set flag=0;                to make the condition back to normal
	}
	else
	{
		lcd_cmd(0x01);
		_delay_ms(5);
		lcd_set_cursor(0, 0);                      //Set Cursor to line ,Column 0
		lcd_print_string("Atmos.Temp:");           //Print in LCD
		lcd_set_cursor(1, 0);                      //Set Cursor to line 1 ,Column 0
		lcd_print_float(temperature);                //Print data in temperature variable
		lcd_data(0xDF);                              //Print degree
		lcd_print_string("C          ");                       //Print "C"
		_delay_ms(300);                              //small delay after Displaying the current temperature value.
	}
	}
}

