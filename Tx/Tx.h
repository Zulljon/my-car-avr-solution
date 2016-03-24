/*
 * main.h
 *
 * Created: 10.03.2016 12:43:59
 *  Author: Dan
 */ 


#ifndef Tx_H_
#define Tx_H_

#define F_CPU 16000000
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "stdint.h"

#include "uart_function.h"
#include "FSM_ADC.h"



#define BUFFER_MAX 8

//---------------SWITCH_word_processing-----------//
#define not_set_yet				0x0
#define SET_SERVO_RIGHT			0x1				// пока оставим для отладки в железе
#define MOTORchik				0x2
#define LEDS_B_PS				0x3
#define SERVO					0x4
#define LEDS_FRONT				0x5
#define SET_MOTOR_FREQ			0x6
#define SET_SERVO_LEFT			0x7				// пока оставим для отладки в железе
//---------------------------------------------//



#endif /* MAIN_H_ */