/*
 * uart.h
 *
 * Created: 02-Jun-26 9:09:08 PM
 *  Author: SHAHEEM
 */ 


#ifndef UART_H_
#define UART_H_

void uart_init(void);
//void transmit_data(char data);
void transmit_string(char *str);

#endif /* UART_H_ */