/*
 * trafficlight_with_int.c
 *
 * Created: 05-Jul-26 1:40:53 PM
 * Author : SHAHEEM
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer_1.h"
#include "INT_0.h"

#define GREEN_LED PORTB0
#define ORANGE_LED PORTB1
#define RED_LED PORTB2
#define EMERGENCY_BUTTON PIND2
volatile uint8_t compare_match_count;
volatile uint8_t flag = 0;

void GREEN_LED_ON(void);
void ORANGE_LED_ON(void);
void RED_LED_ON(void);

//Implement Finite state machine logic
typedef enum
{
	STATE_GREEN,
	STATE_ORANGE,
	STATE_RED,
	STATE_EMERGENCY,
}Trafficstate_t;

volatile Trafficstate_t current_state =STATE_GREEN;

int main()
{
DDRB |= (1<<GREEN_LED)|(1<<ORANGE_LED)|(1<<RED_LED);  // Enable all port pins as outputs
PORTB &= ~((1<<GREEN_LED)|(1<<ORANGE_LED)|(1<<RED_LED)); // Turn all LEDs OFF initially
DDRD &= ~(1<<EMERGENCY_BUTTON);//Enable EMERGENCY_BUTTON as input
PORTD |= (1<<EMERGENCY_BUTTON); //Enable internal pull-up for Button (PIN is in open drain configuration and noisy by default)-enables internal pull-up (~50kohm to VCC)

timer1_init(); //initialize Timer1;
interrupt_init(); //Initialize External interrupt;
//START GREEN_STATE
GREEN_LED_ON();

    while (1)
    {
	switch (current_state)      
	{
	case STATE_GREEN:          //STATE GREEN Implemented
	if(compare_match_count >= 10) //Even if Flag =1, Safe limit will be covered before switching to Emergency state
	{
		compare_match_count=0;  
		if(flag==1)
		{
			GREEN_LED_ON();
			current_state = STATE_EMERGENCY; 
		}
		else
		{
		ORANGE_LED_ON();
		current_state = STATE_ORANGE;
		}
	}
	break;
	
	 case STATE_ORANGE:    //STATE_ORANGE Implemented
	 if(compare_match_count >= 3) //Even if Flag =1, Safe limit will be covered before switching to Emergency state
	 {
		 compare_match_count=0;
		 if(flag==1)
		 {
			 GREEN_LED_ON();
			 current_state = STATE_EMERGENCY;
		 }
		 else
		 {
			 RED_LED_ON();
			 current_state = STATE_RED;
		 }
	 }
	 break;
	 
	case STATE_RED:         //STATE_RED Implemented
	if(compare_match_count >= 10) //Even if Flag =1, Safe limit will be covered before switching to Emergency state
	{
		compare_match_count=0;
		if(flag==1)
		{
			 GREEN_LED_ON();
			 current_state = STATE_EMERGENCY;
		}
		else
		{
			GREEN_LED_ON();
			current_state = STATE_GREEN;
		}
	}
	break;
	
	case STATE_EMERGENCY:   //STATE EMERGENCY Implemented
	if(compare_match_count >= 8) //Additional 25 sec of Time delay implemented for EMERGENCY STATE.
	{
		compare_match_count=0;
		flag=0;
		GREEN_LED_ON();
        current_state = STATE_GREEN;
	}
	break;
	}
}
}
ISR(TIMER1_COMPA_vect) 
{
	compare_match_count ++;  // Increment the Count based on Timer capture
}

ISR(INT0_vect)
{
	flag=1;  // Set emergency flag — state change handled in Timer ISR;
}

void GREEN_LED_ON(void)
{
	PORTB |= (1<<GREEN_LED); //Turn GREEN_LED ON.
	PORTB &= ~(1<<ORANGE_LED); //Turn ORANGE_LED OFF.
	PORTB &= ~(1<<RED_LED); //Turn RED_LED OFF.
}

void ORANGE_LED_ON(void) 
{
	PORTB &= ~(1<<GREEN_LED);//Turn OFF GREEN LED After 10sec;
	PORTB |= (1<<ORANGE_LED);//Turn ON ORANGE_LED;
	PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED;
}
void RED_LED_ON(void)
{
	PORTB &= ~(1<<ORANGE_LED);//Turn OFF ORANGE_LED After 13sec;
	PORTB &= ~(1<<GREEN_LED);//Turn OFF GREEN LED;
	PORTB |=  (1<<RED_LED);//Turn ON RED_LED After 13sec;
}