/*
 * timer1.c
 *
 * Created: 12-Jun-26 4:08:46 PM
 *  Author: SHAHEEM
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "timer1.h"

volatile uint8_t overflow_count=0;
void LED_port_enable()
{
	//Enable initially to 0;
//	DDRD |= (1<<DDD0|1<<DDD5); //Set Data diraction register as output for PORTD; 
	DDRB |= (1<<DDB0|DDB1);//Set Data diraction register as output for PORTB; 
	//PORTD  &=~(1<<PORTD0);//Enable initially to 0;
//	PORTD  &=~(1<<PORTD1);//Enable initially to 0;
	PORTB  &=~((1<<PORTB0)|(1<<PORTB1));//Enable initially to 0;
}
/*---------------------------------------------------------------------------------------------------
	 pre-scalar value 64  /Calculation. [Methode 1]
	 T=1/f, 1 clock periode is 1/16mhz = 62.5ns.
	 Tick time = 62.5 ns × 64.
	 = 4 microseconds.(1 counter increment = 4 µs)
	 [total time delay required =0.5sec = 500,000 microsecond]
	        Total count required =500,000/4 =125,000.
		-->Total count of a 16 bit counter is 65535 counts,
		 .
		. .	The total count for 0.5 sec is 	  65535 & (125,000-65535);
	 (as in execution wait for TCNT1- 1 Overflow i.e 65535 and reload TCNT1 for 59464 counts.
	 so for 59464 counts, you need to preload TCNT1 with value =(65536-59464)= 6072. And repeat the process for continuous operation)
//-------------------------------------------------------------------------------------------------- */
void timer_1_enable()
{
     TCNT1 = 0; //Enable Timer1 with 0 initial value;
	 TCCR1A  &= ~(1<<COM1A1| 1<<COM1A0|1<<COM1B1|1<<COM1B0); //Enable T1 in the normal non PWM mode of operation.
	 PRR     &=~(1<<PRTIM1); ////To enable the Timer/Counter 1 without power shut down;
	 TCCR1A  &=~(1<<WGM10|1<<WGM11); //Enable Waveform generation mode as normal;
	 TCCR1B  &=~(1<<WGM12|1<<WGM13);//Enable Waveform generation mode as normal;
	 //Enable 64 prescalar for timer 1
	 TCCR1B &=~(1<<CS12);
	 TCCR1B |= (1<<CS10|1<<CS11);
	 TIMSK1 |=(1<<TOIE1); //Enable Timer 1 overflow Interrupt; 
	 sei();
}

ISR(TIMER1_OVF_vect)
{
	 overflow_count++;
	 if (overflow_count==1)
	 {
		 TCNT1 = 6072;   //pre-load for remaining time	 
	 }
	 if(overflow_count>=2)
	 {
		 PORTB ^= (1<<PORTB0);
		 overflow_count = 0;
		 TCNT1 = 0;
	 }
}
