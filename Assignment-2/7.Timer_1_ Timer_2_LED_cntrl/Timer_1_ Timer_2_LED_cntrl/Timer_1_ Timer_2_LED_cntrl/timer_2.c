/*
 * timer_2.c
 *
 * Created: 15-Jul-26 7:55:11 PM
 *  Author: SHAHEEM
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer_1.h"
#include "timer_2.h"

void init_timer2()
{
	//Enable Normal port of operation for Timer 2
	TCCR2A &= ~(1<<COM2A0|1<<COM2A1);
	TCCR2A &= ~(1<<WGM20);
	TCCR2A |= (1<<WGM21);
	TCCR2B &= ~(1<<WGM22);
	/*---------------------------------------------------------------------------------------------------
	 Pre-scalar value 1024  /Calculation. [Methode 1]
	 T=1/f, 1 clock period is 1/16mhz = 62.5ns.
	 Tick time = 62.5 ns × 1024.
	 = 4 microseconds.(1 counter increment = 64 µs)
	 [calculate total time delay required for =500ms
	        Total count required =500x10^-3/64x10^-6 =7812.5.
			Timer 2 on the ATmega328P is an 8-bit timer, its maximum hardware count is only 255.
			=7812.5/250 = 31.25 OVERFLOWS in timer 2 required.
			(so, calculate for 500 milli sec is 7812.5.
			Total count required =500x10^-3/64x10^-6 =31250)
			
		-->Total count of a 16 bit counter is 65535 counts,

	 (as in execution load OCR1AH & OCR1AL with 31250-1 = 31249, and compare with TCNT1 value,use interrupt service routine for compare match interrupt)
//-------------------------------------------------------------------------------------------------- */
	//Enable 1024 Prescalar value
	TCCR2B |= (1<<CS20|1<<CS21|1<<CS22);
	
	//Load Capture value on OCR2A for compare capture interrupt
	OCR2A =250; //2 sec delay
	TCNT2 = 0; //Enable Timer1 with 0 initial value
	PRR     &=~(1<<PRTIM2); //To enable the Timer/Counter 2 without power shut down;
	TIMSK2 |=(1<<OCIE2A); //Enable Output Compare A Match Interrupt for Timer2;
	sei();
}
