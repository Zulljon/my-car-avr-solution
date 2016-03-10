/*
 * uart_function.h
 *
 * Created: 10.03.2016 13:18:58
 *  Author: Dan
 */ 


#ifndef UART_FUNCTION_H_
#define UART_FUNCTION_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Rx.h"


//������� �������� ����� � �����,
void USART_Transmit( unsigned char dataT );

// ������� ������ ����� � �����, ���������� �������� ����� (UDR0)
unsigned char USART_Receive( void );

void USART_Init(unsigned int UBRR);

#endif /* UART_FUNCTION_H_ */