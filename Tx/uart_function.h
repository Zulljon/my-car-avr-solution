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
#include "Tx.h"


//������� �������� ����� � �����,
void USART_Transmit( uint8_t dataT );

// ������� ������ ����� � �����, ���������� �������� ����� (UDR0)
uint8_t USART_Receive( void );

void USART_Init(uint16_t UBRR);

#endif /* UART_FUNCTION_H_ */