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
//#include "E:\Micro_Cirquit\projects\avr\MY CAR (bt+avr+pc)\MY CAR (avr solution)\uart_functions.c"

volatile union {
	//байтовая переменная
	uint8_t word;
	
	//------сeрвопривод------//
	struct {
		uint8_t angle:5;
		//uint8_t turn_side:1;
		//uint8_t needs_turn:1;
		uint8_t assignation:3;
	} servo;
	
	//------двигатель------//
	struct {
		uint8_t speed			:4;
		uint8_t spin_rotation	:1;
		uint8_t assignation	:3;
	} motor;
	
	//------светодиоды------//
	//фары
	struct {
		uint8_t p_w_m:4;
		uint8_t on_off:1;
		uint8_t assignation:3;
	} front_leds;
	// задние огни, поворотники, подсветка снизу
	struct {
		uint8_t blue:1;
		uint8_t red:1;
		uint8_t parking_lights_right:1;
		uint8_t parking_lights_left:1;
		uint8_t neon_light:1;
		uint8_t assignation:3;
	} back_leds;
	
	//установка частоты шима двигателя
	struct {
		uint8_t top_value:3;
		uint8_t prescaller:2;
		uint8_t assignation:3;
	} motor_freq;
	
	// установка крайнего левого/правого положения серво
	struct {
		uint8_t values:5;
		uint8_t assignation:3;
	} set_servo__left;
	
	struct {
		uint8_t values:5;
		uint8_t assignation:3;
	} set_servo__right;
	
} outbound_processing ;

uint8_t		buffer[BUFFER_MAX];
uint8_t		buffer_read=0,
			buffer_write=0;

uint8_t F_buffer_read(uint8_t n){		// юзаем в вечном цикле, читаем и пихаем в уарт/радиомодуль
	uint8_t word;
	if (n == BUFFER_MAX){
	buffer_read = 0;}				// добавить флаг надобности чтения из буфера с установкой из функции записи
	else {
		word = buffer[n];
		++n;}
	return word;
	//return buffer[n];
}

void F_buffer_write(uint8_t n, uint8_t word){
	if (n == BUFFER_MAX){
		buffer_write = 0;}
	else {
		buffer[n] = word;
		++n;}
}

void interupt_processing(){
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
	
	uint8_t asd1;
	
    while(1)
    {
        
		asd1 = F_buffer_read(outbound_processing.word);
		//interupt_processing();
		
		//Finit state machine
		FSM_ADC();
		
		
    }
}