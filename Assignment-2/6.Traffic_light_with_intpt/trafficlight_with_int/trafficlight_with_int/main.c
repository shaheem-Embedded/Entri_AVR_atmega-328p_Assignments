/*
 * trafficlight_with_int.c
 *
 * Created: 05-Jul-26 1:40:53 PM
 * Author : SHAHEEM
 */

#define GREEN_LED PORTB0
#define ORANGE_LED PORTB1
#define RED_LED PORTB2
#define EMERGENCY_BUTTON PIND2
volatile uint8_t compare_match_count;
volatile uint8_t flag = 0;

typedef enum
{
	STATE_GREEN,
	STATE_ORANGE,
	STATE_RED,
	STATE_EMERGENCY,
}Trafficstate_t;

volatile Trafficstate_t Current_state =STATE_GREEN;
	
	
int main()
{
DDRB |= (1<<GREEN_LED)|(1<<ORANGE_LED)|(1<<RED_LED);  // Enable all port pins as outputs
PORTB &= ~((1<<GREEN_LED)|(1<<ORANGE_LED)|(1<<RED_LED)); // Turn all LEDs OFF initially
DDRD &= ~(1<<EMERGENCY_BUTTON);//Enable EMERGENCY_BUTTON as input
PORTD |= (1<<EMERGENCY_BUTTON); //Enable internal pull-up for Button (PIN is in open drain configuration and noisy by default)-enables internal pull-up (~50kohm to VCC)

timer1_init(); //initialize Timer1;
interrupt_init(); //Initialize External interrupt;

PORTB |= (1<<GREEN_LED); //Turn GREEN_LED ON.
PORTB &= ~(1<<ORANGE_LED); //Turn ORANGE_LED OFF.
PORTB &= ~(1<<RED_LED); //Turn RED_LED OFF.

    while (1)
    {
	compare_match_count++;
	switch (Current_state)
	{
	case STATE_GREEN:
	if(compare_match_count >= 10)
	{
		if(flag==1)
		{
			Current_state = STATE_EMERGENCY;
		}
		else
		{
		PORTB &= ~(1<<GREEN_LED);//Turn OFF GREEN LED After 10sec;
		PORTB |= (1<<ORANGE_LED);//Turn ON ORANGE_LED;
		PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED;
		compare_match_count=0;
		}
	}
	break;
	
	 case STATE_ORANGE:
	 if(compare_match_count >= 3)
	 {
		 if(flag==1)
		 {
			 Current_state = STATE_EMERGENCY;
		 }
		 else
		 {
			 PORTB &= ~(1<<ORANGE_LED);//Turn OFF ORANGE_LED After 3sec;
			 PORTB &= ~(1<<GREEN_LED);//Turn OFF GREEN LED;
			 PORTB |=  (1<<RED_LED);//Turn ON RED_LED;
			 compare_match_count=0;
		 }
	 break;
	 
	case STATE_RED:
	if(compare_match_count >= 10)
	{
		PORTB &= ~(1<<ORANGE_LED);//Turn OFF ORANGE_LED;
		PORTB |= (1<<GREEN_LED);//Turn ON GREEN LED;
		PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED After 10 sec;
		compare_match_count=0;
	}
	break;
	
	case STATE_EMERGENCY:
	if(compare_match_count >= 25)
	{
		PORTB &= ~(1<<ORANGE_LED);//Turn OFF ORANGE_LED;
		PORTB |= (1<<GREEN_LED);//Turn ON GREEN LED;
		PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED;
		compare_match_count=0;
		flag=0;
	}
	break;
	}
}

ISR(TIMER1_COMPA_vect) 
{
	compare_match_count ++;//Increase the count every time a compare match occurs,
/*	compare_match_count ++; //Increase the count every time a compare match occurs,
	if(flag==0)
	{
	if(compare_match_count ==10)
	{ 
			PORTB &= ~(1<<GREEN_LED);//Turn OFF GREEN LED After 10sec;
			PORTB |= (1<<ORANGE_LED);//Turn ON ORANGE_LED;
			PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED;	
	}
	else if(compare_match_count ==13)
	{
			PORTB &= ~(1<<ORANGE_LED);//Turn OFF ORANGE_LED After 13sec;
			PORTB &= ~(1<<GREEN_LED);//Turn OFF GREEN LED;
			PORTB |=  (1<<RED_LED);//Turn ON RED_LED After 13sec;
	}
	else if(compare_match_count ==23)
	{
			compare_match_count = 0;
			PORTB &= ~(1<<ORANGE_LED);//Turn OFF ORANGE_LED;
			PORTB |= (1<<GREEN_LED);//Turn ON GREEN LED;
			PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED After 23sec;
	}
	}
else if(flag==1)
{
	// Emergency — show GREEN for 7 seconds then resume normal
	
	if(compare_match_count ==7)
	{
		flag=0;
		compare_match_count=0;
		PORTB &= ~(1<<ORANGE_LED);//Turn OFF ORANGE_LED;
		PORTB &= ~(1<<RED_LED);//Turn OFF RED_LED;
		PORTB |= (1<<GREEN_LED);//Turn ON GREEN LED;
	}
}*/
}

ISR(INT0_vect)
{
	flag=1;// Set emergency flag — state change handled in Timer ISR;
}