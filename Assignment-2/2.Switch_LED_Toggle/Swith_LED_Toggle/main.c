/*
 * Swith_LED_Toggle.c
 *
 * Created: 14-Jun-26 8:00:11 PM
 * Author : SHAHEEM
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define GREEN_LED PORTD5      //Define macro for GREEN_LED
#define RED_LED PORTD6       //Define macro for RED_LED
#define STATUS_LED PORTD4  //Define macro for STATUS_LED
#define BUTTON PINB1        //Define macro for switch


int main(void)
{
 DDRD |= (1<<PORTD5)|(1<<PORTD6)|(1<<PORTD4);  //Set PORTD5 & PORTD6 as OUTPUT for LED
 DDRB &= ~(1<<PORTB1);            //Set PORTB1 as Input for switch
 PORTB |= (1<<PINB1);            //Enable internal pull up for Button (PIN is in open drain configuration and noisy by default)-enables internal pull-up (~50k? to VCC)
 
 PORTD |= (1<<RED_LED);         //RED LED Turn ON; Initially after Power ON.
 PORTD &= ~(1<<GREEN_LED);     //GREEN_LED Turn OFF; Initially after Power ON.
    while (1)
    {
		PORTD ^= (1<<STATUS_LED);  //Toggle Status LED
		_delay_ms(100);
		
		if(!(PINB & (1<<BUTTON)))   //If enabled internal pull up -means- PIN is active high initially =1, when Button pressed PIN is Active low=0;
		{
			_delay_ms(10);              // debounce delay
			if(!(PINB & (1<<BUTTON)))   // confirm still pressed
			{
			PORTD ^= (1<<RED_LED);  
			PORTD ^= (1<<GREEN_LED);
			while(!(PINB & 1<<BUTTON)); //Check the condition to avoid debounce;and wait for button release.
			}
		}
    }
}

