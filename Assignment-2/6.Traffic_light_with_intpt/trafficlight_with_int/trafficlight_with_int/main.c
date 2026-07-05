/*
 * trafficlight_with_int.c
 *
 * Created: 05-Jul-26 1:40:53 PM
 * Author : SHAHEEM
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Timer_1.h"
#include "INT_0.h"

#define GREEN_LED PORTB0
#define ORANGE_LED PORTB1
#define RED_LED PORTB2
#define EMERGENCY_BUTTON PIND7
volatile uint8_t compare_match_count;
volatile uint8_t flag = 0;
int main()
{
DDRB |= (1<<GREEN_LED)|(1<<ORANGE_LED)|(1<<RED_LED);  // Enable all port pins as outputs
PORTB &= ~((1<<GREEN_LED)|(1<<ORANGE_LED)|(1<<RED_LED)); // Turn all LEDs OFF initially
DDRD &= ~(1<<EMERGENCY_BUTTON);//Enable EMERGENCY_BUTTON as input
PORTD |= (1<<EMERGENCY_BUTTON); //Enable internal pull-up for Button (PIN is in open drain configuration and noisy by default)-enables internal pull-up (~50kohm to VCC)

timer1_init(); //initialize Timer1;
interrupt_init(); //Initialize External interrupt;

PORTB |= (1<<GREEN_LED); //Turn GREEN_LED ON.
PORTB &= ~(1<<ORANGE_LED); //Turn ORANGE_LED OFF.
PORTB &= ~(1<<RED_LED); //Turn RED_LED OFF.
/*---------------------------------------------------------------------------------------------------
	 pre-scalar value 1024  /Calculation. [Methode 1]
	 T=1/f, 1 clock periode is 1/16mhz = 62.5ns.
	 Tick time = 62.5 ns × 1024.
	 = 4 microseconds.(1 counter increment = 64 µs)
	 [total time delay required =10sec = 10,000,000 microsecond]
	        Total count required =10,000,000/64x10^-3 =156250.
		-->Total count of a 16 bit counter is 65535 counts,

	 (as in execution load OCR1AH & OCR1AL with 156250 and copmare woth TCNT1 value,use interrupt service routine for compare match interrupt)
//-------------------------------------------------------------------------------------------------- */
    while (1)
    {
		if(PIND & (1<<EMERGENCY_BUTTON))
		{
			_delay_ms(10);
			if(!(PIND & (1<<EMERGENCY_BUTTON)))
			{
				  while(!(PINB &(1<<PINB1)));
				  _delay_ms(5);
            }
         }
	}
}

ISR(TIMER1_COMPA_vect) 
{
	compare_match_count ++; //Increase the count every time a compare match occurs,
	if(flag==0)
	{
	if(compare_match_count ==10)
	{ 
			PORTB &= ~(1<<GREEN_LED);//Turn OFF GREEN LED After 10sec;
			PORTB |= (1<<ORANGE_LED);//Turn ON ORANGE_LED;
			PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED;
		
	}
	else if(compare_match_count ==13)
	{
			PORTB &= ~(1<<ORANGE_LED);//Turn OFF ORANGE_LED After 13sec;
			PORTB &= ~(1<<GREEN_LED);//Turn OFF GREEN LED;
			PORTB |= (1<<RED_LED);//Turn ON RED_LED After 13sec;
	}
	else if(compare_match_count ==23)
	{
			compare_match_count = 0;
			PORTB &= ~(1<<ORANGE_LED);//Turn OFF ORANGE_LED;
			PORTB |= (1<<GREEN_LED);//Turn ON GREEN LED;
			PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED After 23sec;
	}
else if(flag==1)
{
	compare_match_count = 0;
	if(compare_match_count ==7)
	{
		PORTB &= ~(1<<ORANGE_LED);//Turn OFF ORANGE_LED;
		PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED;
		PORTB |= (1<<GREEN_LED);//Turn ON GREEN LED;
	}
}
}
}

ISR(INT0_vect)
{
	flag=1;// Set emergency flag — state change handled in Timer ISR
}