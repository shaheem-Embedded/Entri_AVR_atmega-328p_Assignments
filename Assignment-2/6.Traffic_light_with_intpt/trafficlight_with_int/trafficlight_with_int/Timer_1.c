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