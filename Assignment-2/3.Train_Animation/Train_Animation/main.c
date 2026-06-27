/*
 * Train_Animation.c
 *
 * Created: 14-Jun-26 10:38:36 PM
 * Author : SHAHEEM
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define GREEN_LED PORTD1      //Define macro for GREEN_LED
#define RED_LED PORTD2      //Define macro for RED_LED
#define BLUE_LED PORTD3      //Define macro for BLUE_LED
#define YELLOW_LED PORTD4      //Define macro for YELLOW_LED
#define WHITE_LED PORTD5     //Define macro for WHITE_LED

uint8_t train[]=
{
	(1<<GREEN_LED),
	(1<<RED_LED),
	(1<<BLUE_LED),
	(1<<YELLOW_LED),
	(1<<WHITE_LED)
	};
int main(void)
{
    DDRD |= (1<<GREEN_LED)|(1<<RED_LED)|(1<<BLUE_LED)|(1<<YELLOW_LED)|(1<<WHITE_LED); //Set PORTD pins as ouput pins.
    while (1)
    {
		for(int i=0;i<5;i++)
		{
			PORTD = train[i];
			_delay_ms(500);  //implemented delay for LED transition.
    }
}
}

