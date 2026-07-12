/*
 * Timer_1.c
 *
 * Created: 05-Jul-26 6:08:30 PM
 *  Author: SHAHEEM
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Timer_1.h"
#include "INT_0.h"

void timer1_init()
{
	TCNT1 = 0; //Enable Timer1 with 0 initial value;-corresponding to 1sec time delay on compare match.
	OCR1A  = 15624;  // 1 second at 1024 prescaler, 16MHz
	/*---------------------------------------------------------------------------------------------------
	 pre-scalar value 1024  /Calculation. [Methode 1]
	 T=1/f, 1 clock periode is 1/16mhz = 62.5ns.
	 Tick time = 62.5 ns × 1024.
	 = 4 microseconds.(1 counter increment = 64 µs)
	 [total time delay required =10sec = 10,000,000 microsecond]
	        Total count required =10,000,000/64x10^-3 =156250.
			
			(so, calculate for 1 sec is ,
			Total count required =1,000,000/64x10^-3 =15625)
			
		-->Total count of a 16 bit counter is 65535 counts,

	 (as in execution load OCR1AH & OCR1AL with 15625-1 = 15624, and compare with TCNT1 value,use interrupt service routine for compare match interrupt)
//-------------------------------------------------------------------------------------------------- */
	TCCR1A  &= ~((1<<COM1A1| 1<<COM1A0|1<<COM1B1|1<<COM1B0)); //Enable T1 in the normal non PWM mode of operation./OC1A/OC1B disconnected)
	PRR     &=~(1<<PRTIM1); //To enable the Timer/Counter 1 without power shut down;
	//Enable CTC mode.
	TCCR1A  &=~((1<<WGM10|1<<WGM11)); 
	TCCR1B  |= (1<<WGM12);
	TCCR1B  &=~(1<<WGM13);//Enable CTC mode.
	//Enable 1024 pre-scaler for timer 1
	TCCR1B &=~(1<<CS11);
	TCCR1B |= (1<<CS10|1<<CS12);
	TIMSK1 |=(1<<OCIE1A); //Enable Output Compare A Match Interrupt;
	sei();
}