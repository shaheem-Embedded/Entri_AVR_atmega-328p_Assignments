/*
 * timer_1.c
 *
 * Created: 15-Jul-26 7:54:57 PM
 *  Author: SHAHEEM
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer_1.h"
#include "timer_2.h"

void init_timer1()
{
	//Enable Normal port of operation for Timer 1
	TCCR1A &= ~(1<<COM1A1|1<<COM1A0);
	//Enable CTC mode of operation for Timer 1
	TCCR1A &= ~(1<<WGM10|1<<WGM11);
	TCCR1B &= ~(1<<WGM13);
	TCCR1B |=  (1<<WGM12);

	/*---------------------------------------------------------------------------------------------------
	 Pre-scalar value 1024  /Calculation. [Methode 1]
	 T=1/f, 1 clock period is 1/16mhz = 62.5ns.
	 Tick time = 62.5 ns × 1024.
	 = 4 microseconds.(1 counter increment = 64 µs)
	 [total time delay required =10sec = 10,000,000 microsecond]
	        Total count required =10,000,000/64x10^-6 =156250.
			
			(so, calculate for 2 sec is ,
			Total count required =2,000,000/64x10^-6 =31250)
			
		-->Total count of a 16 bit counter is 65535 counts,

	 (as in execution load OCR1AH & OCR1AL with 31250-1 = 31249, and compare with TCNT1 value,use interrupt service routine for compare match interrupt)
//-------------------------------------------------------------------------------------------------- */
	//Enable 1024 Pre-scalar value
	TCCR1B |= (1<<CS10 | 1<<CS12);
	TCCR1B &= ~(1<<CS11);
	//Load Capture value on OCR1A for compare capture interrupt
	OCR1A =31249; //2 sec delay
	TCNT1 = 0; //Enable Timer1 with 0 initial value
	PRR     &=~(1<<PRTIM1); //To enable the Timer/Counter 1 without power shut down;
	TIMSK1 |=(1<<OCIE1A); //Enable Output Compare A Match Interrupt for Timer1;
	sei();
}
