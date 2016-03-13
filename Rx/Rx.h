/*
 * Rx.h
 *
 * Created: 10.03.2016 13:08:17
 *  Author: Dan
 */ 


#ifndef RX_H_
#define RX_H_

#define F_CPU 16000000
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "uart_function.h"

#define BUFFER_MAX 8

//---------------SWITCH--------------------------//
#define NEON					0x0
#define SET_SERVO_RIGHT			0x1				// пока оставим для отладки в железе
#define MOTORchik				0x2
#define LEDS_PS					0x3
#define SERVO					0x4
#define LED_HEADLIGHTS			0x5
#define SET_MOTOR_FREQ			0x6
#define SET_SERVO_LEFT			0x7				// пока оставим для отладки в железе
//---------------------------------------------//

//-------------использованые ножки МК-----------//
#define P_MOTOR_SIDE			PORTB0
#define P_NEON_GREEN			// на таймере2 А OC2A
#define P_NEON_BLUE				// на таймере2 В OC2B
#define P_PARKING_LIGHT_1		PORTD|=1<<PORTD4
#define P_PARKING_LIGHT_0		PORTD&=~(1<<PORTD4)
#define P_HEADLIGHTS			//передние фары на 16 битном таймере В

//---------------------------------------------//

void init_variables_main(void);
float set_servo_math(char a);
void init_variables(void);
unsigned char PWM_speed_math(unsigned char pwm_speeeds);
unsigned int servo_angle(unsigned char r);
unsigned char processing( unsigned char resive_word );
void LEDs_manipulations(void);
void init_pwm_2 (void);
void init_pwm_1 (void);
void init_pwm_0 (void);
void init_I_O (void);


#endif /* RX_H_ */