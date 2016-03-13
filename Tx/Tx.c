/*
 * Tx.c
 *
 * Created: 24.02.2016 17:58:12
 *  Author: Dan
 */ 

#include "Tx.h"
/*
#include "E:\Micro_Cirquit\projects\avr\MY CAR (bt+avr+pc)\MY CAR (avr solution)\defines.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
*/
#include "E:\Micro_Cirquit\projects\avr\MY CAR (bt+avr+pc)\MY CAR (avr solution)\uart_functions.c"

volatile union {
	//байтовая переменная
	unsigned char word;
	
	//------сeрвопривод------//
	struct {
		unsigned char angle:5;
		//unsigned char turn_side:1;
		//unsigned char needs_turn:1;
		unsigned char assignation:3;
	} servo;
	
	//------двигатель------//
	struct {
		unsigned char speed			:4;
		unsigned char spin_rotation	:1;
		unsigned char assignation	:3;
	} motor;
	
	//------светодиоды------//
	//фары
	struct {
		unsigned char p_w_m:4;
		unsigned char on_off:1;
		unsigned char assignation:3;
	} front_leds;
	// задние огни, поворотники, подсветка снизу
	struct {
		unsigned char blue:1;
		unsigned char red:1;
		unsigned char parking_lights_right:1;
		unsigned char parking_lights_left:1;
		unsigned char neon_light:1;
		unsigned char assignation:3;
	} back_leds;
	
	//установка частоты шима двигателя
	struct {
		unsigned char top_value:3;
		unsigned char prescaller:2;
		unsigned char assignation:3;
	} motor_freq;
	
	// установка крайнего левого/правого положения серво
	struct {
		unsigned char values:5;
		unsigned char assignation:3;
	} set_servo__left;
	
	struct {
		unsigned char values:5;
		unsigned char assignation:3;
	} set_servo__right;
	
} outbound_processing ;

unsigned char		buffer[BUFFER_MAX];
unsigned char		buffer_read=0,
			buffer_write=0;

char F_buffer_read(char n){		// юзаем в вечном цикле, читаем и пихаем в уарт/радиомодуль
	unsigned char word;
	if (n == BUFFER_MAX){
	buffer_read = 0;}				// добавить флаг надобности чтения из буфера с установкой из функции записи
	else {
		word = buffer[n];
	++n;}
	return buffer[n];
}

char F_buffer_write(char n, char word){
	if (n == BUFFER_MAX){
		buffer_write = 0;}
	else {
		buffer[n] = word;
		++n;}
}

char interupt_processing(){
	//выключить интерапты
	F_buffer_write(buffer_write,UDRE0);
	//включить интерапты
}

void init_ADC(void){
	ADMUX = (1<<REFS1)|(1<<REFS0)|(1<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
	ADCSRA = (0<<ADEN)|(1<<ADSC)|(0<<ADATE)|(0<<ADIF)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	//ADCSRB = (0<<ACME)|(0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0);
	DIDR0 = (0<<ADC5D)|(1<<ADC4D)|(0<<ADC3D)|(0<<ADC1D)|(0<<ADC0D);
}

void init_pwm(void){
	TCCR2A = (0<<COM2A1)|(1<<COM2A0)|(0<<COM2B1)|(0<<COM2B0)|(0<<WGM21)|(1<<WGM20);
	TCCR2B = (0<<FOC2A)|(0<<FOC2B)|(1<<WGM22)|(1<<CS22)|(1<<CS21)|(1<<CS20);
	TIMSK2 = (0<<OCIE2B)|(1<<OCIE2A)|(1<<TOIE2);
	TIFR2 = (0<<OCF2B)|(1<<OCF2A)|(1<<TOV2);
	ASSR = (1<<EXCLK)|(1<<AS2);//|(0<<TCN2UB)|(0<<OCR2AUB)|(0<<OCR2BUB)|(0<<TCR2AUB)(0<<TCR2BUB);
	//OCR2A = 0;
	
}

void init_I_O(void){
	PORTB=(0<<PORTB0)|(0<<PORTB1)|(0<<PORTB2)|(1<<PORTB3)|(0<<PORTB4)|(0<<PORTB5);
	DDRB= (0<<DDB0)|(0<<DDB1)|(1<<DDB2)|(1<<DDB3)|(0<<DDB4)|(0<<DDB5);
}

//инициализация апаратного USART
//настраивам регистры
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

ISR(TIMER0_OVF_vect){
	
}

ISR(ADC_vect){
	// обрабатывать по двум АЦП вперед/назад, влево/вправо
}

int main(void)
{
	init_I_O();
	init_pwm();
	init_ADC();
	USART_Init(MYUBRR);
	sei(); 
	
	unsigned char asd1;
	
    while(1)
    {
        
		asd1 = F_buffer_read(outbound_processing.word);
		//interupt_processing();
		
		//Finit state machine
		FSM_ADC();
		
		
    }
}