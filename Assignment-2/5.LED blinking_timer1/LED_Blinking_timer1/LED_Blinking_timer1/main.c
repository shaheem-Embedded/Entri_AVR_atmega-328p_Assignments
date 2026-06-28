/*
 * LED_Blinking_timer1.c
 *
 * Created: 28-Jun-26 7:06:15 PM
 * Author : SHAHEEM
 */
#define F_CPU 16000000UL
#include <avr/io.h>

#define GREEN_LED PORTB0
#define ORANGE_LED PORTB1
#define RED_LED PORTB2

int main(void)
{
PORTB |= (1<<PORTB0|1<<PORTB1|1<<1<<PORTB2);  //Set PORTB as Output ports.

timer_1_enable();
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
	 so for 59464 counts, you need to preload TCNT1 with value =(65536?59464) 6072. And repeat the process for continuous operation)
//-------------------------------------------------------------------------------------------------- */


    while (1)
    {
		
		
    }
}

