/*
 * Brigntness_Control_PWM.c
 *
 * Created: 20-Jul-26 8:35:25 PM
 * Author : SHAHEEM
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "fast_pwm.h"
#define LED PORTD6  //Initialize macro for LED
#define BUTTON PINB1 //Initialize macro for BUTTON
volatile int count=0;

int main(void)
{
	//Enable OC0A pin PORTD6 pin as ouput for LED;
	DDRD |= (1<<LED);
	//Enable the Push Button as input
	DDRD &= ~(1<<BUTTON);
	//Enable internal Pull up configuration for Push button
    PORTD |= (1<<BUTTON);//Enable internal pull-up for Button (PIN is in open drain configuration and noisy by default)-enables internal pull-up (~50kohm to VCC)
	
	init_timer0_PWM();
	set_duty_cycle();
    /* Replace with your application code */
    while (1)
    {
	 if (!(PINB & (1<<BUTTON)))
	 {
		 _delay_ms(5);
		 if(!(PINB & (1<<BUTTON)))
		 {
			 count++;
			 while(!(PINB &(1<<BUTTON)));
			 _delay_ms(5);
		 }	
    }
	if(count ==1)
	{
		OCR0A = 60;
	}
	else if(count ==2)
	{
		OCR0A = 128;
	}
	else if(count ==3)
	{
		OCR0A = 175;
	}
	else if(count ==4)
	{
		OCR0A = 255;
	}
	if(count>4)
	{
		count =0;
	}
}
}

