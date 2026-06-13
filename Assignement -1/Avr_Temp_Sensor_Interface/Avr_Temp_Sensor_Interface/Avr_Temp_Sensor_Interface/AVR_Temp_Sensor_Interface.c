/*
 * AVR_Temp_Sensor_Interface.c
 *
 * Created: 07-Jun-26 5:20:24 PM
 *  Author: SHAHEEM
 */ 
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include<util/delay.h>
#include "AVT_TEMP_SENSROR_INTERFACE.h"

void ADC_init()
{
	//Selecting Ref Voltage as AVCC
	ADMUX |= (1<<REFS0);
	//ADMUX &= ~(1<<REFS1); 
	//Select the ADC0 Channel
	ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3)); 
	/*Select the prescalar mode for Frequency selection ,
	our frequency for operation is 125Khz(for better precision and sampling rate)
	
	    ADC frequency = Fosc/prescalar value 
		               =16000000/128
					   =125000HZ,125Khz.*/
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);//prescalar value -128.   
	//ADLAR bit set 0 for ADC data to be left shifted
	ADMUX &= ~(1<<ADLAR);
}

uint16_t ADC_read()
{
	ADCSRA |= (1<<ADEN); //Set ADEN bit to 1 for ADC enable operation
	ADCSRA |= (1<<ADSC); //Set ADSC to start the ADC conversion 
    //channel = channel & 0X07; //Channel limited to 7.
    //ADMUX   = (ADMUX & 0xF8)|channel; //Mux register & with 0XF8 for not altering other values in ADMUX register.
	while (!(ADCSRA & (1<<ADIF)));//  wait until conversion complete flag set
	ADCSRA |= (1<<ADIF);         // Clear flag by writing 1
    return(ADC);                 // Return the Value of ADC register(ADCL & ADCH)
}
