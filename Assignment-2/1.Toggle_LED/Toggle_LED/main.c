/*
 * Toggle_LED.c
 *
 * Created: 14-Jun-26 6:18:44 PM
 * Author : SHAHEEM
 */

#define F_CPU 16000000UL  //Define the Clock frequency as 16Mhz
#include <avr/io.h>
#include <util/delay.h>

#define LED PORTD5       //Define macro for LED for better code usage.

int main(void)
{
	DDRD|= (1<<LED);  //Set Data direction register of PORTD.5 as output.
	PORTD |= (1<<LED);	 //LED as high initially when power turned ON.
    while (1)
    {
		_delay_ms(3000); //create 3 sec delay
		PORTD ^= (1<<LED);	    //Toggle led on every loop respective to the previous stage of the LED.
		
    }
}

