/*
 * Binary_count_switch.c
 *
 * Created: 27-Jun-26 6:03:06 PM
 * Author : SHAHEEM
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

#define LED1 PORTD0
#define LED2 PORTD1
#define LED3 PORTD2
#define LED4 PORTD3
#define Button PINB1

int main(void)
{
	uint8_t flag=1;
	uint8_t count=0;
	DDRD |= (1<<PORTD0)|(1<<PORTD1)|(1<<PORTD2)|(1<<PORTD3);  //Set PORTD as output for LEDs.
	DDRB &= ~(1<<PORTB1); //Set PORTB as input for Switch.
	PORTB |= (1<<PINB1);//Enable internal pull-up for Button (PIN is in open drain configuration and noisy by default)-enables internal pull-up (~50kohm to VCC)
    /* Replace with your application code */
	PORTD &= ~((1<<PORTD0)|(1<<PORTD1)|(1<<PORTD2)|(1<<PORTD3));//Turn OFF all LEDs.
    while (1)
    {
		if(!(PINB & (1<<PINB1)))
		{
			_delay_ms(5);  
			if(!(PINB & (1<<PINB1)))
			{
				count++;
				while(!(PINB &(1<<PINB1)));
				_delay_ms(5);
			}
		if(count>15)
		   {
			count =0;
           }
		PORTD = (PORTD & 0XF0)|(count & 0x0F);
}
}
}

