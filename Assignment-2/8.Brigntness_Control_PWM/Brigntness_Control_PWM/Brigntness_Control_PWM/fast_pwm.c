/*
 * fast_pwm.c
 *
 * Created: 20-Jul-26 9:06:44 PM
 *  Author: SHAHEEM
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "fast_pwm.h"

void init_timer0_PWM()
{
	//Configure (Enable as 0) Power saver mode for Timer 0;
	PRR &=~(1<<PRTIM0);
	//Enable the PWM mode timer 0
	TCCR0A &= ~(1<<COM0A0);   // Clear on compare match
	TCCR0A |=  (1<<COM0A1);   // Non-inverting Fast PWM
	//Enable FAST PWM mode of waveform generation- PWM
	TCCR0A |= (1<<WGM00|1<<WGM01);
    TCCR0B &= ~(1<<WGM02);
	//Prescalar value selection 64.
	TCCR0B |= (1<<CS00 | 1<<CS01);
	TCCR0B &= ~(1<<CS02);
	
	/*Calculate % Duty cycle requirements.
	
	  Duty cycle =   Tonx100/Time period :(Time period = Ton + Toff)
	  
	  Duty cycle % = OCR0x X 100/(TOP)
	            i.e OCR0x = (Duty cycle x 255)/100   :( Here top value is 0XFF -255)
				    OCR0x =  50 x (255)/100
					OCR0x = 128.
	--------------------------------------------------------------------------------------
	Frequency of PWM Wave signal at OC0A Pin calculation:
	PWM frequency = fclk/N(510)  
	              = 16x10^6/(64x510)
				  = 490hz.(Suitable for LED)  / N-prescalar value;
				  -----------------------------------------------------------------------------
				    25%  ? OCR0A = (25  × 255)/100 = 64
				    50%  ? OCR0A = (50  × 255)/100 = 128
				    75%  ? OCR0A = (75  × 255)/100 = 191
				    OFF  ? OCR0A = 0  (100% OFF = 0% duty cycle)
   ----------------------------------------------------------------------------------------*/
  // OCR0A = 128;         //Value to be loaded IN OCR0x for phase correct PWM signal with 50% duty cycle.
  

}
