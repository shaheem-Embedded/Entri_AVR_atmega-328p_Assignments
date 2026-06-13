/*
 * uart.c
 *
 * Created: 02-Jun-26 9:10:20 PM
 *  Author: SHAHEEM
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

void uart_init()
{
	/*Load value in UART Baud rate registers for 9600 baud rate per second.
	F CPU =16000000
	Required B rate =9600
	UBRR value to be loaded = F_CPU/(16XBaud rate)-1;
	                        = 16000000/(16x9600)
							=103.*/
	UBRR0L = 103;
	UBRR0H = 0;
	// Enable Tx and Rx for UART communication
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	//Mode select-Asynchronous mode
	UCSR0C &= ~((1<<UMSEL00)|(1<<UMSEL01));
	//Enable Frame format for UART transmission-8bit data transmission
	UCSR0B &= ~(1<<UCSZ02);
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	//Parity selection-Disabled
	UCSR0C &= ~((1<<UPM00)|(1<<UPM01));
	//Stop bits selection -1 bit
	UCSR0C &= ~(1<<USBS0);
}
/*void transmit_data(char data)
{
	//check if UDRE0 flag is not set -if so means UDR Register is empty and can transfer the data;
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	_delay_ms(10);
}*/
void transmit_string(char *str)
{
	while(*str != '\0')
	{
		while(!(UCSR0A & (1<<UDRE0)));   //check if UDRE data register Empty flag or not 
		UDR0 = *str;                     //If empty push the next data to UDR0 data register
		str++;                           //Increase the Base value of the pointer
	}
}
