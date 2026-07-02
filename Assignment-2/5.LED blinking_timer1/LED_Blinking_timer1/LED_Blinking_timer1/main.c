/*
 * LED_Blinking_timer1.c(Using Timer 1 compare match interrupt)
 *
 * Created: 28-Jun-26 7:06:15 PM
 * Author : SHAHEEM
 */
#define F_CPU 16000000UL
#include <avr/io.h>

#define GREEN_LED PORTB0
#define ORANGE_LED PORTB1
#define RED_LED PORTB2
volatile uint8_t compare_match_count;
int main(void)
{
PORTB |= (1<<GREEN_LED|1<<ORANGE_LED|1<RED_LED);  //Set PORTB as Output ports.
timer_1_enable();
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
		
		
    }
}

ISR(TIMER1_COMPA_vect) 
{
	compare_match_count ++; //Increase the count every time a compare match occurs,
	
	if(compare_match_count >=10)
	{
		PORTB &= ~(1<<GREEN_LED);//Turn OFF GREEN LED After 10sec;
		PORTB |= (1<<ORANGE_LED);//Turn ON ORANGE_LED;
		PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED;
	}
	if(compare_match_count >=13)
	{
		PORTB &= ~(1<<ORANGE_LED);//Turn OFF ORANGE_LED After 3sec;
		PORTB &= ~(1<<GREEN_LED);//Turn OFF GREEN LED;
		PORTB |= (1<<PORTB);//Turn OFF GREEN LED After 10sec;
	}
	PORTB |= (1<<RED_LED); //Turn RED_LED ON.
	if(compare_match_count >=10)
	{
		PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED After 10sec;
	}
}