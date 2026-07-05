/*
 * INT_0.c
 *
 * Created: 05-Jul-26 6:08:43 PM
 *  Author: SHAHEEM
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Timer_1.h"
#include "INT_0.h"

void interrupt_init()
{
	//Enable Any logical change on INT0 generates an interrupt request.
	EICRA &= ~(1<<ISC00); 
	EICRA |= (1<<ISC01);
	//External Interrupt Request 0 Enable
	EIMSK|=(1<<INT0);
}