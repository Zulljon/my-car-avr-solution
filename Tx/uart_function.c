/*
 * uart_function.c
 *
 * Created: 10.03.2016 13:18:04
 *  Author: Dan
 */ 

#include "uart_function.h"


//функция передачи байта с УАРТа,
void USART_Transmit( unsigned char dataT ){
	/* Wait for empty transmit buffer */
	while ( !(UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = dataT;
}

// функция приема байта с УАРТа, возвращает значения байта (UDR0)
unsigned char USART_Receive( void ){
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

/*
//инициализация апаратного USART
//настраивам регистры
void USART_Init(unsigned int UBRR)
{
	//Set baud rate
	UBRR0H = (unsigned char)(UBRR>>8);
	UBRR0L = (unsigned char)UBRR;
	UCSR0A = (0<<RXC0)|(0<<TXC0)|(1<<UDRE0)|(0<<FE0)|(0<<DOR0)|(0<<UPE0)|(0<<U2X0)|(0<<MPCM0);
	//Enable receiver and transmitter
	UCSR0B=(1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02)|(0<<RXB80)|(0<<TXB80);
	// Set frame format: 8data, 2stop bit
	UCSR0C=(0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0);
}
*/

void USART_Init(unsigned int UBRR)
{
	//Set baud rate
	UBRR0H = (unsigned char)(UBRR>>8);
	UBRR0L = (unsigned char)UBRR;
	UCSR0A = (0<<RXC0)|(0<<TXC0)|(1<<UDRE0)|(0<<FE0)|(0<<DOR0)|(0<<UPE0)|(0<<U2X0)|(0<<MPCM0);
	//Enable receiver and transmitter
	UCSR0B=(0<<RXCIE0)|(1<<TXCIE0)|(0<<UDRIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02)|(0<<RXB80)|(0<<TXB80);
	// Set frame format: 8data, 2stop bit
	UCSR0C=(0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0);
}
