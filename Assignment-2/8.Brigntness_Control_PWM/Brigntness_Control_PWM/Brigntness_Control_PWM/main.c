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
	DDRB &= ~(1<<BUTTON);
	//Enable internal Pull up configuration for Push button
    PORTB |= (1<<BUTTON);//Enable internal pull-up for Button (PIN is in open drain configuration and noisy by default)-enables internal pull-up (~50kohm to VCC)
	
	init_timer0_PWM();

    /* Replace with your application code */
    while (1)
    {
	 if (!(PINB & (1<<BUTTON)))
	 {
		 _delay_ms(5);
		 if(!(PINB & (1<<BUTTON)))
		 {
			 count++;
			 if(count > 4)
			 {
				 count =0;
			 }
			 set_duty_cycle(count);
			 while(!(PINB &(1<<BUTTON)));
			 _delay_ms(5);
		 }	
    }
}
	}

