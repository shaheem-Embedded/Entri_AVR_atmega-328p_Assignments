/*
 * Timer_1_ Timer_2_LED_cntrl.c
 *
 * Created: 15-Jul-26 7:30:56 PM
 * Author : SHAHEEM
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer_1.h"
#include "timer_2.h"

volatile uint8_t compare_match_count;
#define STATUS_LED PORTB1 
#define HEARTBEAT_LED PORTB2 

int main(void)
{
	DDRB |= (1<<STATUS_LED); //Set STATUS_LED as output port;
	DDRB |= (1<<HEARTBEAT_LED); //Set HEARTBEAT_LED as output port;
	
	PORTB &= ~(1<<STATUS_LED); //Turn OFF the STATUS_LED initially
	PORTB &= ~(1<<HEARTBEAT_LED); //Turn OFF the HEARTBEAT_LED initially
    /* Replace with your application code */
	init_timer1();
	init_timer2();
    while (1)
    {
		;
    }
}
ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1<<STATUS_LED); //Toggle STATUS_LED every time a Compare match interrupt is enabled for Timer 1.
}

ISR(TIMER2_COMPA_vect)
{
	compare_match_count++;
	if(compare_match_count>=31)
	{
	PORTB ^= (1<<HEARTBEAT_LED); //Toggle HEARTBEAT_LED every time a Compare match interrupt is enabled for Timer 2.	
	compare_match_count =0;
	}
}